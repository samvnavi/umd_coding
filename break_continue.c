/* This program shows how break and continue work.

							Gang Qu
							Sept. 1, 2015
*/

#include <stdio.h>

int main(void)
{ int x, y;

  for (x=1; x<10; x++)
  { if (x == 5) 
      break;
    printf("%2d", x);
  }

  printf("\nx=%2d\n",x);

  for (y=1;y<10; y++)
  { if (y == 5)
      continue;
    printf("%2d", y);
  }

  printf("\ny=%2d\n",y);

  return 0;
}

