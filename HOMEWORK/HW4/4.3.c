/* Complete the program so it can product exactly what 4.3.out does. 
	see 4.3.detail.out for the random numbers created.
   Most missing parts require only 1 or 2 statements. 
   No need to declare any new variables.
   You have to re-produce exactly 4.3.out does to receive full credits.
							Gang Qu
							Mar. 6, 2024
*/

#include <stdio.h>
#include <stdlib.h>

int getSeed();		// get the seed value from user input

int main()
{ int **A;		// A[][] is the "ragged" matrix
  int	row, 		// the number of rows in A[][]
	col;		// the number of columns in the longest row in A[][]
  int *real_col;	// array of the number of columns/elements in each row
  int i, j;

  srand(getSeed());

//  generate a number between 2 and 6 for row
 
//  generate a number between 2 and 6 for col 

// allocate memory for A (int ** type) and real_col (int * type)
 
  for (i=0; i<row; i++)
  { 
// for each row i, generate a random number between 1 and col for 
// 	real_col[i]. This is the number of elements in row i. 
//	Then allocate memory for the row A[i] for that many elements.


// create random numbers A[i][0], A[i][1], ..., all between 0 and 9  

  }    

// print out A[][] backwards
  for (i=row-1; i>=0; i--)
  { for (j=real_col[i]-1; j>=0; j--)
      printf("%2d", A[i][j]);
    printf("\n");
  }

  return 0;
}


