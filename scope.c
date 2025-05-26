/* This program demonstrates the scope of variables.
 * for each of the 4 cases in showvalue(), predict the output and then
 * change the code, compile, run and see the real output. 
							Gang Qu
							Jan. 24, 2024
*/

#include <stdio.h>

int a=1;
int b = 12;
 
void showvalue(void);

int main(void)
{ int i;

  for (i = 10; i <= b; i++)
  { a++;
    printf("in main(), a = %d, \n", a);
    showvalue();
  }

  return 0;
}

void showvalue()
{ 
  static int a = 3; 	// case 0: 
			// case 1: remove static
			// case 2: remove the entire statement
  static int i = 0;	// case 3: remove static 
  a = a + b;
  printf("Times function is called: %d, a = %d\n", ++i, a);
			// what will happen if change ++i to i++?
}
