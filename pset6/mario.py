#!/usr/bin/env python3

import cs50

def main():
    print('Please enter the height of your pyramid! ', end = '')
    height = cs50.get_int()
    
    while height > 23 or height < 0:
        print('Please enter a height between 0 and 23: ', end = '')
        height = cs50.get_int()
        
    for i in range(1, height + 1):
        print(' ' * (height - i) + "#" * i + ' ' + "#" * i)
        
if __name__ == "__main__":
    main()