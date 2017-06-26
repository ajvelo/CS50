#include <stdio.h>
#include <cs50.h>
 
int main(void)
{
    
    int height;
    
    do {
        printf("Please enter the height of your pyramid! ");
        height = get_int();
    } 
    
    while (height > 23 || height < 0); 
    
    for (int i = 0; i < height; i++)
    {
    	for (int j = 0; j < height - i - 1;  j++)
    	{
    		printf(" ");
    	}
    
    	for (int j = 0; j <= i;  j++)
    	{
    		printf("#");
    	}
    
    	printf("  ");
    
    	for (int j = 0; j <= i;  j++)
    	{
    		printf("#");
    	}
    
    	printf("\n");
    }
}