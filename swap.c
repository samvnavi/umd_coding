/* This program shows that 
   1) when variables of int (or char, or double, and so on) type are passed 
	to a function, it is a copy of the value of variable that is passed 
	to the function, the variable itself remains unchanges. 
   2) when the addresses of the variables are passed to the function, the
	changes you make to the variables in the function will remain outside
	the function. and
   3) when an array is passed to a function, the real array, not a copy of 
	it, will be passed to the function, and whatever change you make to 
	the array in the function will stay there.
   Memory address information is added to show this. 
							Gang Qu
							Mar. 13, 2024
*/


#include <stdio.h>

void swap1 (int, int);
// swap two numbers. WARNING: this will not swap the values of the two
// parameters passed to this function.

void swap2 (int *, int *);
// swap two numbers by passing their memory addresses. Values will be swapped.

void swap3 (int a[], int, int, int );
// swap two elements in the given positions (the last two parameters)
// in array a[] of a given size (the second parameter).

int main (void)
{ 
  int a[8] = {2,3,5,7,11,13,17,19};
  int pos1, pos2;		// the indices of elements to be swaped
  int i;

  printf("The original array:\n");
  for (i=0; i<8; i++)
    printf("\ta[%d] = %2d\n", i, a[i]);

  printf("Enter the indices of the two numbers that you want to swap: ");
  scanf("%d%d", &pos1, &pos2);

  printf("\nYour have entered:   pos1 = %2d, %p; pos2 = %2d, %p\n", pos1, &pos1, pos2, &pos2);
  swap1 (pos1, pos2);
  printf("After calling swap1: pos1 = %2d, %p; pos2 = %2d, %p\n", pos1, &pos1, pos2, &pos2);

  swap2 (&pos1, &pos2);
  printf("After calling swap2: pos1 = %2d, %p; pos2 = %2d, %p\n", pos1, &pos1, pos2, &pos2);

  swap3 (a, 8, pos1, pos2);

  printf("After calling swap3:\n");
  for (i=0; i<8; i++)
    if ( i == pos1 || i == pos2)
      printf("\ta[%d] = %2d  <---\n", i, a[i]);
    else
      printf("\ta[%d] = %2d\n", i, a[i]);

  return 0;
}

void swap3 (int a[], int size, int x, int y)
{  int tmp; 

   if ( x >= size || x < 0 || y >= size || y < 0 )
   { printf("Invalid index passed to the array. No swap performed.\n");
     return;
   }

   tmp = a[x];
   a[x] = a[y];
   a[y] = tmp; 
}

void swap1 (int x, int y)
{ int tmp;
  printf("\tEntering swap1: x = %d, %p; y = %d, %p\n", x, &x, y, &y);
  tmp = x;
  x = y;
  y = tmp;
  printf("\tExiting swap1: x = %d, %p; y = %d, %p\n", x, &x, y, &y);
}

void swap2 (int *a, int *b)
{ int tmp;
  printf("\tEntering swap2: a = (%d) %p, %p, b = (%d) %p, %p\n", *a, a, &a, *b, b, &b);
  tmp = *a;
  *a = *b;
  *b = tmp;
  printf("\tExiting swap2: a = (%d) %p, %p, b = (%d) %p, %p\n", *a, a, &a, *b, b, &b);
}

