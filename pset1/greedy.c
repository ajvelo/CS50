#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
  
  float money;
  int coins = 0;
  
  do {
     printf("How much change is owed?\n");
     money = get_float();
  } while (money < 0);
  
  int change = round(money * 100);
  
  while (change > 0)
	{   
	    if (change >= 25)
	    {
	        change -= 25;    
	    }
	    else if (change >= 10)
	    {
	        change -= 10;    
	    }
	    else if (change >= 5)
	    {
	        change -= 5;    
	    }
	    else
	    {
	        change -= 1;
	    }
	    
	    coins++;
	}
    
  printf("%i\n", coins);
  
}