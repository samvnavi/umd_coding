/* the main program for project 2 phase II

It opens each of the input matrix by calling 
	read_input(in, M[i-1], out);		// implemented in sparse.c
then print out the matrix by calling 
	show_list(M[i-1], out);			// implemented in sparse.c
Both functions are implemented for you in the sample sparse.c and used in Phase I.

After that, it multiplies every two adjacent matrices by calling
	PROD = multiplication(M[i-1], M[i], out);
and prints out the output PROD by calling
	show_list(PROD, out);
next, it finds a path in matrix M[i] from the first ENTRY to the third ENTRY
        find_path(M[i], j, k, l, m, out);

At the end, it prompts the user to enter two positions in matrix M[0] and find a
path between them. 

Remember that it is your task to implement find_path() and multiplication().

								Gang Qu
								April 29, 2025
*/

#include <stdlib.h>
#include <stdio.h>
#include "sparse.h"			// include the header file


int main(int argc, char *argv[])
{ FILE *in, *out;
  ROOT **M; 
  int i, j=0, k=0, l=0, m=0;
  ROOT *PROD;
 
  PROD = make_root();

  if (argc < 2)
  { printf("Usage: a.out input1 input2 ... output\n");
    exit(0);
  }

  M = (ROOT **) malloc((argc-1)*sizeof(ROOT *));
  if (M == NULL) 
    exit(0);

  out = fopen(argv[argc-1], "w");
  if (out == NULL)
  { printf("output file %s cannot open ...\n", argv[argc-1]);
    exit(0);
  }

  for (i=1; i<argc-1; i++)
  { in =  fopen(argv[i],  "r");
    if (in == NULL)
    { printf("Input %s not found ...\n", argv[i]);
      exit(0);
    }

    M[i-1] = make_root();
    read_input(in, M[i-1], out);
// printf("input %s:\n", argv[i]);		// no indent. Test only
    show_list(M[i-1], out);    

    fclose(in);
  }

  for (i=1; i<argc-2; i++)
  { fprintf(out, "\nMultiplying %p with %p ...\n", M[i-1], M[i]);
    PROD = multiplication(M[i-1], M[i], out);
  
    if (M[i] != NULL && M[i]->head != NULL)
    { j = M[i]->head->row;
      k = M[i]->head->col;
    }
    if (M[i] != NULL && M[i]->head != NULL && M[i]->head->next != NULL &&\
        M[i]->head->next->next != NULL)
    { l = M[i]->head->next->next->row;
      m = M[i]->head->next->next->col;
    }
    fprintf(out, "\nFinding path from (%d, %d) to (%d, %d) ...\n", j, k, l, m);
    find_path(M[i], j, k, l, m, out);
  }

  printf("Enter P1 and P2: ");
  scanf("%d %d %d %d", &i, &j, &k, &l);
  fprintf(out, "\n\nFinding path from (%d, %d) to (%d, %d) ...\n", i, j, k, l);
  find_path(M[0], i, j, k, l, out);

  fclose(out);

  return 0;
}
