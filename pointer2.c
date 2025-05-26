/* This program shows how to use pointers to manipulate arrays. Detailed 
	comments are embedded in the program as comments.
							Gang Qu
							Mar. 9, 2016
*/ 


#include <stdio.h>

int main(void)
{ int i;
  int a[5] = {10,20,30,40,50};
  int *p;

// two ways to point a pointer to an array
  p = &a[0];
//  p = a;

  for (i=0; i<5; i++)
//  3 ways to access a[]: a[i] = *(p+i) = p[i] 
//  printf("a[%d] = %d, *(p+i) = %d, p[i] = %d \n", i, a[i], *(p+i), p[i]);

// notice that *p++ changes the pointer, unlike *(p+i) 
//  printf("a[%d] = %d, *(p+i) = %d, *p++ = %d \n", i, a[i], *(p+i), *p++);

// note the difference between *p++ and *(++p)
//  printf("a[%d] = %d, *(p+i) = %d, *(++p) = %d \n", i, a[i], *(p+i), *(++p));

  putchar('\n');

// the following codes show that *p++ = *(p++), not (*p)++
  p = &a[0];
  for (i=0; i<5; i++)
    printf("*p++ = %d \n", *p++);
  putchar('\n');

  p = &a[0];
  printf("*(p++) = : ");
  for (i=0; i<5; i++)
  { printf("%d ", *(p++));
    printf("(%d,%d) ", a[0], a[i]);
  }
  putchar('\n');

  a[0] = 10;
  p = &a[0];
  printf("(*p)++ = : ");
  for (i=0; i<5; i++)
  { printf("%d ", (*p)++ );
    printf("(%d,%d) ", a[0], a[i]);
  }
  putchar('\n');

  a[0] = 10;
  p = &a[0];
  printf("\n *p++  = : ");
  for (i=0; i<5; i++)
  { printf("%d ", *p++);
    printf("(%d,%d) ", a[0], a[i]);
  }
  putchar('\n');

  a[0] = 10;
  p = &a[0];
  printf("\n *(++p) = : ");
  for (i=0; i<5; i++)
  { printf("%d ", *(++p));
    printf("(%d,%d) ", a[0], a[i]);
  }
  putchar('\n');

  return 0;
}

