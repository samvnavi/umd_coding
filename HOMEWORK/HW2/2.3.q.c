/* in this implemenation, we assume the followings:
   1. the user is going to enter numbers one by one, separted by a signle
	space. When the first array is done, an ENTER ('\n') will be used
	as input and the second array will start.
   2. each array input will not have more than 10 integers
								Gang Qu
*/

#include <stdio.h>

void sort(int [], int, int, int [], int, int);
// this is the recursive function that you are supposed to implement

int main()
{ int A[10], B[10], cnt_a, cnt_b; 
  int i, j;
  char ch;

  printf("Enter the first array:");
  i = 0;
  do
  { scanf("%d%c", &A[i], &ch);
// read in an integer that next character ch
// use the value of ch to check whether there is more numbers ( )
// or the first array has reached the end (\n)
    i++;
  } while (ch==' ' && i<10);
  cnt_a = i;

  printf("Enter the second array:");
  i = 0;
  do
  { scanf("%d%c", &B[i], &ch);
    i++;
  } while (ch==' ' && i<10);
  cnt_b = i;

  sort(A, 0, cnt_a-1, B, 0, cnt_b-1);
  printf("\n");

  return 0;
}

void sort (int A[], int a, int b, int B[], int c, int d)
{ 
// write your recursion here to replace the while loop!
// the following code tests input has been read in correctly
// please comment or remove them when you submit your work
   int i, j;
   printf("1st array:");
   for (i=0; i<=b; i++)
    printf(" %d", A[i]);
   printf("\n2nd array:");
   for (i=0; i<=d; i++)
    printf(" %d", B[i]);

   printf("\n\n");
   i=a;
   j = d;
   while (i<=b || j>=c)
   { if (i<=b && j>=c)
    { if (A[i] < B[j])
      { printf("%d ", A[i]);
        i++;
      }
      else
      { printf("%d ", B[j]);
        j--;
      }
    }
    else
    { if (i==b+1 && j>=c)
      { printf("%d ", B[j]);
        j--;
      }
      else // if (j<c && i<b)
      { printf("%d ", A[i]);
        i++;
      }
    }
   }

   printf("\n");
}
