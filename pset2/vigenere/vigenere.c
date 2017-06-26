#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int key(int count, string k)
{
    return tolower(k[count % strlen(k)]) - 97;
}

int main(int argc, string argv[])
{	
    if (argc != 2)
    {
        printf("./vigenere k\n");
        return 1;
    }
 
    string k = argv[1];
    
    for (int i = 0, n = strlen(k); i < n; i++) 
    {
        if (!isalpha(k[i])) 
        {
            printf("./vigenere k\n");
            return 1;
        }
    }
    
    printf("plaintext: ");
    
    string s = GetString();
    
    printf("ciphertext: ");
    
    int count = 0;
 
    for (int j = 0, o = strlen(s); j < o; j++)
    {
        char c = s[j];
 
        if (isupper(c))
        {   
            char cipher = (((c - 65) + key(count, k)) % 26) + 65;
            count++;
            printf("%c", cipher);
        }
        else if(islower(c))
        {
            char cipher = (((c - 97) + key(count, k)) % 26) + 97;
            count++;
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