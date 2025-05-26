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
 

#endif
