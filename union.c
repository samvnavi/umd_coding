/* This code is copied from 
	http://www.tutorialspoint.com/cprogramming/c_unions.htm
							Gang Qu
							Sept. 1, 2015
*/

#include <stdio.h>
#include <string.h>
 
union Data
{
   int i;
   float f;
   char  str[20];
};
 
int main( )
{
   union Data data;        

   printf( "Memory size occupied by data : %d\n", sizeof(data));

   data.i = 10;
   printf( "data.i : %d\n", data.i);
   
   data.f = 220.5;
   printf( "data.f : %f\n", data.f);
   
   strcpy( data.str, "C Programming");
   printf( "data.str : %s\n", data.str);
// the next two printf() will print out junk value because data.str
// has taken the memory (values of data.i and data.f are overwritten).
   printf( "data.i : %d\n", data.i);
   printf( "data.f : %f\n", data.f);

   return 0;
}
