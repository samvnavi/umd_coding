/* This program shows an example of indirectly resursive call.
 	pay attention to the use of "static int cnt = 0;" in main()
   Think about the output before you compile and run it.
   Compare your expected output with the real output and figure out why if
	they are different.
							Gang Qu
							Nov. 9, 2004
*/


#include <stdio.h>

void f(void);
void g(void);

int main(void)
{  
  static int cnt = 0;
  printf("In main():\n");
  cnt++;
printf("counter = %3d \n", cnt);

  if (cnt <= 2)
  { 
    f();
//printf("I am here calling g() \n");
// see what happens if you uncomment the following function call
//    g();
  }

  return 0;
}

void f(void)
{
  printf("In f():\n");
  g();
}

void g(void)
{
  printf("In g():\n");
  main();
}
   

