/* This programs shows all (probably more than that) you need to know about
	printf().
   data types have to be introduced before this program.

							Gang Qu
							Feb. 11, 2011
*/

#include <stdio.h>

int main(void)
{
	int a1 = 23, a2 = -19;
	short int b1 = 53, b2 = 12;
	int i1 = 32000, i2 = -320;

	float f1 = 1.0, f2 = -0.0001, f3 = 2.3e+8, f4 = -1.23E-02;

// integer example 
	printf("%%d: a1 = %d, a2 = %d, b1 = %d, b2 = %d, i1 = %d, i2 = %d\n", 
		a1, a2, b1, b2, i1, i2);
	printf("%%i: a1 = %i, a2 = %i\n", a1, a2);
	printf("%%x: a1 = %x, a2 = %x\n", a1, a2);
	printf("%%X: a1 = %X, a2 = %X\n", a1, a2);
	printf("%%o: b1 = %o, b2 = %o\n", b1, b2);
	printf("%%O: b1 = %O, b2 = %O\n", b1, b2);
	printf("%%u: i1 = %u, i2 = %u\n", i1, i2);
	printf("%%U: i1 = %U, i2 = %U\n", i1, i2);

	a1 = 023;
	b1 = 0x53;

	printf("\nAfter reassign values:\n a1: 023=%d, b1: 0x53=%d\n", a1, b1);

// floating point example 
	printf("\n\n");
	printf("1.0 = %f, -0.0001 = %f\n", f1, f2);
	printf("2.3e+8 = %f, -1.23E-02 = %f\n\n", f3, f4);

	printf("1.0 = %e, -0.0001 = %e\n", f1, f2);
        printf("2.3e+8 = %e, -1.23E-02 = %e\n\n", f3, f4);

        printf("1.0 = %E, -0.0001 = %E\n", f1, f2);
        printf("2.3e+8 = %E, -1.23E-02 = %E\n\n", f3, f4);

        printf("1.0 = %g, -0.0001 = %g\n", f1, f2);
        printf("2.3e+8 = %g, -1.23E-02 = %g\n\n", f3, f4);

        printf("1.0 = %G, -0.0001 = %G\n", f1, f2);
        printf("2.3e+8 = %G, -1.23E-02 = %G\n\n", f3, f4);

// char and string example 
	printf("%c, %c, %c, \n", '&', 0x4B, 87);

	printf("%s%s\n", "Hello \n World\0 Welcome!", "!");
        printf("%s%s\n", "Hello World Welcome!", "!");
// note that it compiles if you have %S, but the whole printf() is ignored. 


// field width example 
	printf("%12d \n%12f \n%14e \n%6E \n%012d\n",23,3.1416,-2.0,3.1,-23);

	printf("%012d \n%*d \n%0*d \n%*d \n", -23, 12,23, 12,23, 012,23);

// precision example 
	printf("%5.2f \n%.2f \n%9.2e \n", 3.14159, 3.14159, 13.14159);

	printf("%*.*f \n", 5, 3, 3.14159);
// this shows that the number will be rounded to the closest one, not always
//	round up or round down

	printf("%5.2d \n%10.5s\n", 1, "Hello, World!");

// format example 
	printf("%-15ftest \n%+ftest \n% ftest\n", 3.1416, 3.1416, 3.1416);

	return 0;
}
