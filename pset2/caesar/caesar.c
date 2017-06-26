#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
 
int main(int argc, string argv[])
{	
    if (argc != 2)
    {
        printf("./caesar k\n");
        return 1;
    }
 
    int k = atoi(argv[1]);
    
    printf("plaintext: ");
    
    string s = GetString();
    
    printf("ciphertext: ");
 
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        char c = s[i];
 
        if (isupper(c))
        {   
            char cipher = (((c - 65) + k) % 26) + 65;
            printf("%c", cipher);
        }
        else if(islower(c))
        {
            char cipher = (((c - 97) + k) % 26) + 97;
            printf("%c", cipher);
        }
        else
        {
            printf("%c", c);
        }
    }
    printf("\n");
    
    return 0;
}