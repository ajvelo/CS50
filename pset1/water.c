#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("How long, in minutes, do you take when you shower?\n");
    
    int minutes = get_int();
    
    // since a 1-minute shower is equal to 12 bottles of water then:
    
    printf("That's the equivalent to %i bottles of water!\n", minutes * 12);
}