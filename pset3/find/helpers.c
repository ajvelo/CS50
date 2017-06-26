/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n) {

  int min = 0;
  int max = n - 1;
  int mid = (min + max) / 2;
  
  if (n < 0) {
      return false;
  }

  while (min <= max) {
 
    if (values[mid] == value)
      return true;
    else if (value < values[mid]) {
          max = mid - 1;
          mid = (min + max) / 2;
    }
    
    else if (value > values[mid]) {
          min = mid + 1;
          mid = (min + max) / 2;
    }
    
      else 
        break;
    }
    
  return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n) {

    for (int i = 0; i < n; i++) {
    
        int min = i;
        for (int j = i + 1; j < n; j++) {
            
            if (values[j] < values[min]) {
                min = j;
            }
            
        }
        
        if (min != i) {
        
            int swap = values[min];
            values[min] = values[i];
            values[i] = swap;
        }
    }
}