#!/usr/bin/env python3

import cs50
import sys

def main():
    
    if len(sys.argv) != 2:
        print('caesar.py k')
        exit(1)
        
    k = int(sys.argv[1])
    
    print('plaintext: ', end = '')
    
    s = cs50.get_string()
    
    print('ciphertext: ', end = '')
    
    for i in range(len(s)):
        
        c = s[i]
        
        if str.isupper(c):
            cipher = (((ord(c) - 65) + k) % 26) + 65
            print(chr(cipher), end = '')
        elif str.islower(c):
            cipher = (((ord(c)- 97) + k) % 26) + 97
            print(chr(cipher), end = '')
        else:
            print(c, end = '')
            
    
    print('')
    
    exit(0)
            
    
if __name__ == "__main__":
    main()