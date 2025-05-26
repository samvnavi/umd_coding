/* This program shows the bascis of dynamic memory allocation.
	It reads in input from keyboard, one character at a time,
	allocates memory to the input and store it until user enters
	letter 'q'. Then the program prints out the input backwards.

							Gang Qu
							Sept. 1, 2015
*/

#include<stdio.h>
#include<stdlib.h>

int main(void)
{ char *p, data;
  int i = 0, mem=0;

  if (( p =(char *) malloc(sizeof(char))) == NULL )
  { printf("no memory ...\n");
    exit (0);
  }

  while ((scanf("%c", &data) == 1) && (data != 'q'))
  { p[i] = data;
    printf("input: %c\n\t", p[i]);
    mem+= sizeof(*p);
    printf("memory assigned to p: %3d\n", mem);
    i++;
    p = (char *) realloc(p, (i+1)*sizeof(char));
  }

  printf("\n%d characters entered.\n", i);
  
  for (i--; i>=0; i--)
    printf("%c", p[i]);

  putchar('\n');

  free(p);

  return 0;
}
