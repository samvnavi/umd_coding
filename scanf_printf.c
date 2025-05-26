/* This program reads a student ID (int), a score (float), a grade
	(char), and prints them out.
   There are two implementations, one tries to prompt the user for data
	piece by piece, the other tries to get all at one time. Think 
	about their advantages and disadvantages. Also note how to read
	in a character in the first implementation.

 							Gang Qu
							Sept. 1, 2015
*/

#include <stdio.h>

int main(void)
{
  int SID;
  float Score;
  char Grade;

/*
  printf("Enter the student ID: ");
  scanf("%d", &SID);

  printf("Enter the score: ");
  scanf("%f", &Score);

  printf("Enter the grade: ");
  scanf("%c%c", &Grade, &Grade);
// note that the last statement reads in two charaters 

/* the following two statements achieve the same thing as the above six
	statements.
   note that in this case we only need to read in variable Grade once
   	and the white space will be skipped (more about this will be 
	discussed later on.
*/
  printf("Enter the student ID, score, and grade: ");
  scanf("%d %f %c", &SID, &Score, &Grade);

  printf("SID: %d \nScore: %f \nGrade: %c\n", SID,Score,Grade);
 
  return 0;
}
