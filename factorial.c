/* this shows an example of recursin 
   n! = n * n-1 * n-2 * ... * 2 * 1
   n! = n * (n-1)!
   0! = 1
   1! = 1

   Question: modify the main() program such that when user gives a negative
	number, it will print out the error message and then ask the user to
	provide another input until a non-negative number is given.

                                                                Feb. 9, 2016
                                                                Gang Qu
*/

#include <stdio.h>
#include <stdlib.h>

int fact (int n)
{ int res = 1;
  if (n == 0) 
    res = 1;
  else 
    res=n*fact(n-1);
  return res;
}

int main()
{ int k;
  printf("Enter a non-negative integer: ");
  scanf("%d", &k);
  if (k < 0)
  { printf("input cannot be negative!\n");
    exit(0);
  }

  printf("%d! = %d\n", k, fact(k));
  
  return 0;
}
