/* This is the header file for the sparse matrix project
April 12: initial version that was posted.

April 15: void show_list (ROOT *M, FILE *F); is added
                this function was already implemented in sparse.c (4/12 version)
          void  read_input(FILE *F, ROOT *M, FILE *G)
                this function is left in sparse.c as an example of defining and
                implementing functions that are not in sparse.h

April 20: the following function prototypes are added. 
	  void search (ROOT *M, int k, FILE *F);
	  void find_max(ROOT *M, FILE *F);
	  ROOT * addition (ROOT *M1, ROOT *M2, FILE *F);
	  ROOT * subtraction (ROOT *M1, ROOT *M2, FILE *F);
This version contains all the functions for phase 1 of the project.

*/

#ifndef sparse 
#define sparse

#define NEW(x) (x*)malloc(sizeof(x))

typedef struct entry
{ int val;			// non-zero integer value of the entry
  int row, col;               	// entry's position in the matrix  
  struct entry *left, *right;
				// pointers to the first non-zero entry of the
				//   matrix that is to the left (smaller column
				//   number) or right (larger column number) of 
				//   this entry and in the same row of this entry 
  struct entry *up, *down;
				// pointers to the first non-zero entry of the
				//   matrix that is above (smaller row number
				//   or below (larger row number) this entry
				//   and in the same row of this entry 
  struct entry *next;		
				// a pointer to another entry in the matrix
  void * info;			// you can define additional information abot 
				//   an entry and use this pointer to access
				//   that informatio
} ENTRY;

typedef struct root 		// root to a list of all non-zero entries
{ ENTRY *head;			// first entry in a "matrix" or a list of ENTRY's. 
				//   You can traverse the list with approriate
				//   "next" pointer. That is, use "next" to access
				//   the entire matrix. 
  long num;			// the number of non-zero entries in the matrix
  void *info;			// a pointer that you can use to define anything
				//   that you find useful
} ROOT;


ENTRY * make_node (int r, int c, int v); 
				// make a new entry with value v at position
				//   (r,c) of the matrix. r,c>0, v!=0


ROOT * make_root (void);	// make a root to a list of ENTRY's
 

void show_list (ROOT *M, FILE *F);
				// print to file F the values in a linked list
				// of ENTRY's with M as the ROOT. 
		// 1. 5 entries per line in the following format
	//    3 (2,2)    16 (2,4)     7 (1,3)    18 (2,3)     6 (1,5)
		// 2. reserve 5 spaces for each value, followed by (row, col)
		// 3. first print out the following message to F
	// matrix at 0x1afc610 ...
		// where 0x1afc610 is the value of M, which is the address of
		// the ENTRY that M points to (first in the linked list)


void search (ROOT *M, int k, FILE *F);
				// search value k in a linked list of ENTRY's 
				// with M as the ROOT. Position(s) of ENTRY's
				// whose value equals k will be printed out to
				// output file F.
		// 1. first print out the following message to F
	// search k in matrix at 0x1afc610 ...
		// 2. if value k is found at position (123, 45), print out
	// 123 45
		// 3. if value k occurs multiple times in M, print out all the
		// 	positions, one per line, regardless of the order
		// 4. if value k does not occur in M, do nothing


void find_max(ROOT *M, FILE *F);
				// find the maximum value in M and print out 
				// its position in output file F
		// 1. first print out the following message to F
	// find max in matrix at 0x1afc610 ...
		// 2. then print out the position of the max to F as
	// maximum k at position (row, col)
		// 3. if the max occurs multiple times, print out to F only
		//	one of those positions is ok (any one)
			// Note: think about the output when M points to an 
			// empty list. 



ROOT * addition (ROOT *M1, ROOT *M2, FILE *F);
				// M1 and M2 point to two lists of ENTRY's
				// the function computes M1 + M2 and returns
				// a ROOT pointer points to a list of
				// ENTRY's with values in M1 + M2 
			// Note:  M1 and M2 could be the same matrix
		// 0. the following is printed to F when addition() is called
	// matrix at 0x1afc610 + matrix at 0x18878d0 ...
		// where 0x1afc610 and 0x18878d0 are the values of M1 and M2
		// This is done before the addition() call, you do not need 
		// to implement this in the addition() function
		// 1. print out the values of M1 + M2 (hint: you can call
		//	function show_list ( , );
		// 2. print ouf the following message to F
	// matrix at 0x1887040 has k non-zero entries
		// where 0x1887040 is the address where the first ENTRY of 
		// the sum M1+M2 is stored and k is the number of ENTRY's in
		// the new linked list (M1+M2) of ENTRY's


ROOT * subtraction (ROOT *M1, ROOT *M2, FILE *F);
				// identical to addition() except that this 
				// function computes M1 - M2 instead
			// Hint: there are ways that you can implement only 
			// one function to do both + and - controlled by a
			// paramter or call addition() to implement subtraction. 

#endif
