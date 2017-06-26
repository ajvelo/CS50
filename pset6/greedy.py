#!/usr/bin/env python3

import cs50
import math

def main():
    
    coins = 0
    print('How much change is owed? ', end = '')
    money = cs50.get_float()
    
    while money < 0:
        print('Please provide a value greater than zero: ', end = '')
        money = cs50.get_float()
        
    change = math.floor(money * 100)
    
    while change > 0:
        
        if change >= 25:
            change = change - 25
            
        elif change >= 10:
            change = change - 10
        
        elif change >= 5:
            change = change - 5
        
        else:
            change = change -1
        
        coins = coins + 1
        
    print(coins)
            
        
    

if __name__ == "__main__":
    main()