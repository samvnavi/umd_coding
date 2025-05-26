/* This program shows how to use rand(), srand() to generate pseudo-random 
	numbers.
   1. the use of srand().
   2. how to generate numbers with different range, or pattern

   On glue, you don't need stdlib.h to use rand(), but need it if you want
	to use RAND_MAX. Similarly, you don't need time.h to use time(), but
	need it if you use time(NULL).
							Gang Qu
							Nov. 17, 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{ int i=0;
  int a[] = {2, 3, 5, 7, 11, 13, 17, 19};

//  srand(1);			// 0. this is the default seed = 1
//  srand(1234);		// 1. always the same sequence of numbers
//  srand(time(NULL));		// 2. every time it will be different

  for (; i<6; i++)
  {
// srand(time(NULL));		// 3. what will this give us? a constant!!!
				// unless this becomes a long time 60000
    printf("%3d: %6d \n", i, rand());
//    printf("%3d: %6d \n", i, rand()%10);	//4. 0 to 9
//    printf("%3d: %6d \n", i, rand()%5*2+3);	//5. odd number between 3 and 11
//    printf("%3d: %6d \n", i, a[rand()%8]);	//6. random array element
    printf("%3d: %f \n", i, 1.0*rand()/RAND_MAX);
				//7. random fraction between 0 and 1
  }

  return 0;
}

