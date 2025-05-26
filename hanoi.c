/* This program shows the classic recursive solution for the Hanoi problem.
   We also count the total number of moves and it has a nice feature about
	global variable and static auto variable.
							Gang Qu
							Nov. 4, 2004
*/


#include <stdio.h>

int counter;

void hanoi(char from, char to, char middle, int n)
{ 
//  static int counter;
/* need to comment the last printf in main() and global variable 
	counter if you try to use this static variable.		
*/
   
  if ( n == 1) 
    printf("%3d: Move disk from %c to %c\n", ++counter, from, to);

  else
  { hanoi (from, middle, to, n-1);
    hanoi (from, to, middle, 1);
    hanoi (middle, to, from, n-1);
  }
}

int main (void)
{ int disks;

  printf("Enter the number of disks: ");
  scanf("%d", &disks);
  printf("\n\n");

  hanoi('A', 'C', 'B', disks);
  
  printf("\n\nTotal number of moves: %d\n", counter);

  return 0;
}
