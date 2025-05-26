/*  This is a simple example on pointer and function, how to pass pointer to
	a function. Need to add some more examples on how to return a pointer.
			
							Gang Qu
							Mar. 9, 2016
*/

#include <stdio.h>

void f1 (char * x)
{ *x = '$';
  printf("in f1, before x ++: \nrvalue of pointer x = %p, lvalue = %p \n", x, &x);
  x ++;
  printf("in f1, after x++: \nrvalue of pointer x = %p, lvalue = %p \n\n", x, &x);
}

int f2(char *a)
{ int i;
  for (i=0; *(a+i) != '\0'; i++)
    printf("%c", *(a+i));
  return i;
}

int main(void)
{ char c, *p = &c;
  
  char b[9]={'E','N','E','E',' ', '1','5','0','\0'};

  printf("\n\nin main: \nrvalue of variable c = %d, lvalue = %p \n", c, &c);
  printf("rvalue of pointer p = %p, lvalue = %p \n\n", p, &p);

  f1(p);
//  f1(&c);
  printf("in main, after calling f1(): \nrvalue of pointer p = %p, lvalue = %p \n", p, &p);
  printf("in main, after calling f1(): \nrvalue of c = %c, lvalue = %p \n", c, &c);
// this last printf() is to test *x = '$'

  printf("\nb has %d characters. \n", f2(b));

  return 0;
}
