/* This progam shows the basic features of scanf()

							Gang Qu
							Sept. 1, 2015
*/

#include <stdio.h>

int main (void)

{ int a;
  float b;
  char c;
  char name[10], name2[10];

//  scanf("%d %f %c %s", &a, &b, &c, name);

  scanf("%d %f %c %[a-zA-Z]s", &a, &b, &c, name);

  printf("a= %d, b = %f, c = %c, name = %s\n",
	a, b, c, name);

  scanf("%s", name2);
  printf("%s\n", name2);


/*
  printf("Enter in the following format: \n \t student_ID ... score ... \n");
  scanf("%*s %d %*s %c", &a, &c);

  printf("a = %d, c = %c\n", a, c);
  scanf("%d", &a);

  scanf("%*c %c", &c);
  printf("%c \n", c);

*/
  return 0;

}
