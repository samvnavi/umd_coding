/* This program shows the basics about pointer
	1. declaration and initialization
	2. size of pointers
	3. lvalue and rvalue
	4. use pointer to access variable values
	pr++ and pr=pr+32 are added to show what happen when pointer moves
   Note that you have the 3 different usage of * in this example.

							Gang Qu
							Mar. 9, 2016
*/

#include <stdio.h>

int main(void)
{ int a, b, d = 3, *pr = &d;
  char c, *p = &c;

// concept of pointer, lvalue and rvalue 
  printf("sizeof(pr) = %d, sizeof(p) = %d \n\n", sizeof(pr), sizeof(p));
  printf("c is stored at memory location \t %p \n", &c);
  printf("p points to memory location  \t %p \n", p);

  printf("variables and their memory addresses: \n");
  printf("a\t%p\n", &a);
  printf("b\t%p\n", &b);
  printf("d\t%p\n", &d);
  printf("pr\t%p\n", &pr);
  printf("c\t%p\n", &c);
  printf("p\t%p\n", &p);


  c = 'A';
  printf("\n rvalue of c = %d \n lvalue of c = %p\n", c, &c);
  printf("\n rvalue of p = %p \n lvalue of p = %p\n", p, &p);

// how to use pointer by the * operator 
  a = * pr;
  b = *&d;
  printf("\nrvalue of a = %d \n lvalue of a = %p\n", a, &a);
  printf("rvalue of b = %d \n lvalue of b = %p\n", b, &b);
  printf("rvalue of d = %d \n lvalue of d = %p\n", d, &d);

  *pr = 2 + a;
  printf("\nafter *pr = 2 + a;");
  printf("\n rvalue of d = %d \n lvalue of d = %p = %p \n", d, &d, pr);

  *pr = *pr + *pr;
  printf("\nafter *pr = *pr + *pr;");
  printf("\n rvalue of d = %d \n lvalue of d = %p = %p \n", d, &d, pr);

  *pr = *pr**pr;
  printf("\nafter *pr = *pr**pr;");
  printf("\n rvalue of d = %d \n lvalue of d = %p = %p \n", d, &d, pr);
  printf("\n rvalue of a = %d \n lvalue of a = %p != %p \n", a, &a, pr);
  printf("\n rvalue of b = %d \n lvalue of b = %p != %p \n", b, &b, pr);

  pr++;
//  pr = pr + 32;
  printf("\n rvalue of d = %d \n lvalue of d = %p \n", d, &d);
  printf("\n rvalue of pr = %p \n value pr points to = %d \n ", pr, *pr);

// see what happens if an int pointer points to a char
  p  = pr;
  printf("\n rvalue of p = %p \n p points to %c\n", p, *p);

  return 0;
}
