/* test of constant 

*/

#include <stdio.h>


int main()
{ const int a=5; 
  int b=3;

  int x[] = {1,2,3,4,5};
  int *const p=&x[0];
  int *q;

  const int y[] = {2,3,5,7};
  const int *q2 = &y[0];

  printf("b = a + 2: %d\n", a+2);
//  printf("a++: %d\n", a++);
//  printf("a = b - 1: %d\n", a=b-1);

  printf("b = *p: %d\n", *p);
  printf("b = *(p+2): %d\n", *(p+2));
  printf("b = p[2]: %d\n", p[2]);
//  p++;
//  p = &x[3];
//  p = q; 

  q2++; printf("q2++: %d\n", *q2);
  q2 = p; printf("q2 = p: %d\n", *q2);
  q2 = &y[3]; printf("q2 = &y[3]: %d\n", *q2);
//  *q2 = 0;
//  p = q2;
//  q2[2] = 10;

  return 0;
}
