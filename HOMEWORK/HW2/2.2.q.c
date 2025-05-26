/* this is a ssample main program to test your recursion version of foo().

							Gang Qu
*/

#include <stdio.h>

int foo (int A[], int n)
{ int res = 0, i = n-1;
  for (; i>=0; i--)
    res += A[i];
  return res;
}

int main()
{ int A[10] = {1, 2, 3, -4, -5, -6, 7, 8, 9, 10};
  int i=1;
  
  for (; i<=10;)
    printf("sum of the first %d numbers: %d\n", i++, foo(A, i));

  return 0;
}

