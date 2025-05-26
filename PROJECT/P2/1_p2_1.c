/* the main program for project 2
p2_1_v1.c: 	command line safety check
		define data structure (ROOT **M) to store input
		read_input();
		show_list();
								Gang Qu
								April 13, 2025

*/

#include <stdlib.h>
#include <stdio.h>
#include "sparse.h"			// include the header file


int main(int argc, char *argv[])
{ FILE *in, *out;
  ROOT **M; 
  int i, j, k;


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
  fclose(out);

  return 0;
}

