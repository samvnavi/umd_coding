/* This program shows the implicit and explict cast in C. 
	
							Gang Qu
							Sept. 1, 2015
*/


#include <stdio.h>

int main (void)

{ int a;
  float b;

  int result;
  float real_result;

  printf("Enter an integer and a real number: ");
  scanf("%d %f", &a, &b);

  printf("a= %d, b = %f \n", a, b);

  result = a * (int) b;
  printf("%d * (int) %f = %d \n", a, b, result);

  result = a * b;
  printf("%d * %f = %d \n", a, b, result);
  printf("%d * %f = (double) %f \n", a, b, (double) result);

  real_result = a * b;
  printf("%d * %f = %f \t %f \n", a, b, a * b, real_result);

  if (b == (int) b) 
	printf("b == (int) b \n");
  else  printf("b != (int) b \n");


  return 0;

}
