from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import gettempdir

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = gettempdir()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    
    entry_symbols = db.execute("SELECT shares, symbol FROM entry WHERE id = :id", \
                                    id=session["user_id"])
    
    net_worth = 0
    
    for entry_symbol in entry_symbols:
        symbol = entry_symbol["symbol"]
        shares = entry_symbol["shares"]
        stock = lookup(symbol)
        total = shares * stock["price"]
        net_worth += total
        db.execute("UPDATE entry SET price=:price, total=:total WHERE id=:id AND symbol=:symbol", \
                    price=usd(stock["price"]), total=usd(total), id=session["user_id"], symbol=symbol)
    
    updated_cash = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])
    
    net_worth += updated_cash[0]["cash"] 
    
    updated_entry = db.execute("SELECT * from entry WHERE id=:id", id=session["user_id"])
                                    
    return render_template("index.html", stocks=updated_entry, \
                            cash=usd(updated_cash[0]["cash"]), total = usd(net_worth) )

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    
    if request.method == "GET":
        return render_template("buy.html")
    else:
        stock = lookup(request.form.get("symbol"))
        if not stock:
            return apology("Incorrect Symbol")
        
    shares = float(request.form.get("shares",))

    if shares < 1 or shares != int(shares):
        return apology("You must input an integer greater than zero!")
        
    money = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
    
    if not money or float(money[0]["cash"]) < stock["price"] * shares:
        return apology("Not enough funds for transaction")
    
    db.execute("INSERT INTO histories (symbol, shares, price, id) \
                VALUES(:symbol, :shares, :price, :id)", \
                symbol=stock["symbol"], shares=shares, \
                price=usd(stock["price"]), id=session["user_id"])
                   
    db.execute("UPDATE users SET cash = cash - :purchase WHERE id = :id", \
                id=session["user_id"], \
                purchase=stock["price"] * float(shares))
                    
    user_shares = db.execute("SELECT shares FROM entry \
                       WHERE id = :id AND symbol=:symbol", \
                       id=session["user_id"], symbol=stock["symbol"])
                       
    if not user_shares:
        db.execute("INSERT INTO entry (name, shares, price, total, symbol, id) \
                    VALUES(:name, :shares, :price, :total, :symbol, :id)", \
                    name=stock["name"], shares=shares, price=usd(stock["price"]), \
                    total=usd(shares * stock["price"]), \
                    symbol=stock["symbol"], id=session["user_id"])
                    
    else:
        shares_total = user_shares[0]["shares"] + shares
        db.execute("UPDATE entry SET shares=:shares \
                    WHERE id=:id AND symbol=:symbol", \
                    shares=shares_total, id=session["user_id"], \
                    symbol=stock["symbol"])
    
    return redirect(url_for("index"))
    

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    histories = db.execute("SELECT * from histories WHERE id=:id", id=session["user_id"])
    
    return render_template("history.html", histories=histories)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("Must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("Must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users \
                           WHERE username = :username", \
                           username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    
    if request.method == "POST":
        check = lookup(request.form.get("symbol"))
        
        if not check:
            return apology("Incorrect Symbol")
            
        return render_template("quotefound.html", stock=check)
    
    else:
        return render_template("quote.html")
    

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""
    
    if request.method == "POST":
        
        if not request.form.get("username"):
            return apology("Must provide username")
            
        elif not request.form.get("password"):
            return apology("Must provide password")
        
        elif request.form.get("password") != request.form.get("passwordconfirm"):
            return apology("passwords do not match")
        
        result = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)", \
                             username=request.form.get("username"), hash=pwd_context.encrypt(request.form.get("password")))
                 
        if not result:
            return apology("Username taken")
        
        session["user_id"] = result

        return redirect(url_for("index"))
    
    else:
        return render_template("register.html")                

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    
    if request.method == "GET":
        return render_template("sell.html")
    else:
        stock = lookup(request.form.get("symbol"))
        if not stock:
            return apology("Incorrect Symbol")
        
    shares = float(request.form.get("shares",))

    if shares < 1 or shares != int(shares):
        return apology("You must input an integer greater than zero!")
        
    user_shares = db.execute("SELECT shares FROM entry \
                             WHERE id = :id AND symbol=:symbol", \
                             id=session["user_id"], symbol=stock["symbol"])
    
    if not user_shares or int(user_shares[0]["shares"]) < shares:
        return apology("Not enough shares")
    
    db.execute("INSERT INTO histories (symbol, shares, price, id) \
                VALUES(:symbol, :shares, :price, :id)", \
                symbol=stock["symbol"], shares=-shares, \
                price=usd(stock["price"]), id=session["user_id"])
            
    db.execute("UPDATE users SET cash = cash + :purchase WHERE id = :id", \
                id=session["user_id"], \
                purchase=stock["price"] * float(shares))
                    
    shares_total = user_shares[0]["shares"] - shares
    
    if shares_total == 0:
        db.execute("DELETE FROM entry \
                    WHERE id=:id AND symbol=:symbol", \
                    id=session["user_id"], \
                    symbol=stock["symbol"])
    else:
        db.execute("UPDATE entry SET shares=:shares \
                WHERE id=:id AND symbol=:symbol", \
                shares=shares_total, id=session["user_id"], \
                symbol=stock["symbol"])
    
    return redirect(url_for("index"))
    
@app.route("/addcash", methods=["GET", "POST"])
@login_required
def addcash():
    """Add cash to your account."""
    
    if request.method == "POST":
        
        add_cash = float(request.form.get("addcash"))
    
        if add_cash < 1.00:
            return apology("You must input a value greater than zero")
        
        elif add_cash > 1000000:
            return apology("You cannot withdraw that much!")
        
        db.execute("UPDATE users SET cash = cash + :add_cash WHERE id = :id", \
                    add_cash=add_cash, id=session["user_id"])
    
        return apology("Funds have been added to your account!")
    
    else:
        return render_template("addcash.html")
