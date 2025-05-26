/*  This files implements the UNIX cp command. It does not have the file
	protection. For example, if file "to" exist, then the program will
	crash.

							Gang Qu
							Sept. 1, 2015

*/

#include <stdio.h>
#include <stdlib.h>	// need this for exit(0)

int main(int argc, char *argv[])
{ FILE *from, *to;
  char ch;

  if (argc != 3)
  { printf("Usage: executable input_file output_file\n"); 
    exit(0);
  }

  from = fopen(argv[1], "r");
  to = fopen(argv[2], "w");

  while (fscanf(from, "%c", &ch) != EOF)
  { fprintf(to, "%c", ch);
    printf("%c", ch);
  }

  fclose(from);
  fclose(to);

  return 0;
}
