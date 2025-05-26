/* Rewrite function foo() without recursion and explain what it does in 
	plain English as comment at the start of your code. 

                                                        Gang Qu
*/


#include <stdio.h>

int foo(int A[], int n)
{ int res;
  if (n == 1) res = A[0];
  else
    if (A[n-1] < foo(A, n-1))
      res = foo(A, n-1);
    else res = A[n-1];
  return res;
}

int main()
{ int A[10] = {1, -2, 3, -4, 5, -6, 7, -8, 9, 10};
  int i=1;
  
  for (; i<=10;)
    printf("largest in the first %d numbers: %d\n", i++, foo(A, i));

  return 0;
}

