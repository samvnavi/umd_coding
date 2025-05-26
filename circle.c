/* This program asks user to enter the radius of a circle and then print 
	out the area and circumference of the circle.
   It has the following features:
   1. variable declaration.
   2. constant variable declaration.
   3. read in input from screen (scanf() function).
   4. print out the value of variables by printf() function.
   5. define all the variables in a function before any other statement.
   6. a couple of good programming habits
	* tell the user what you are expecting
	* check whether you are reading in the right thing or not after 
		each scanf() by simply printing out the values

							Gang Qu
							Sept. 5, 2008 
*/


#include <stdio.h>

#define PI 3.14159

int main(void)
{ float r, A, C;
/*  this is another way to declare constant variable.
	notice the (many) difference between this one and the #define
  const float PI = 3.14159;
*/

  printf("Enter the radius of the circle (positive number):");

  scanf("%f", &r);
  printf("Radius = %f \n", r);

/* we should check whether r is positive or not, 
	which we will learn pretty soon.
*/

  if(r>0){
    A = PI * r * r;
    C = 2 * r * PI;
  }
  else {
    A=0;
    C=0;
  }

  printf("Area = %f, Circumference = %f\n", A, C);
 
  return 0;
}

