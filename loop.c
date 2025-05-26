/* This program reads a student ID (int), a score (float), and assigns
        a grade (char) based on the score and prints them out. It then 
	asks the same information for the next student till a given 
	number of student's data in entered.
   Features in this program:
   1. while 
   2. do-while
   3. for

                                                        Gang Qu
                                                        Sept. 1, 2015
*/

#include <stdio.h>

int main(void)
{
  int SID;
  float Score;
  char Grade;
  int No = 1; 
/* this the loop variable, which we initialize to 1 */

  while (No <= 3)
  {
/* the following statement checks the value of No when enter each iteration
    printf("Starts with No = %d \n", No);
*/
    printf("Enter the student ID and score:");
    scanf("%d %f", &SID, &Score);

    if (Score >= 60.0)
    {
      if (Score >=90.0)
       Grade = 'A';
      else
       Grade = 'P';
    }
    else
    {  Grade = 'F';
    }

    printf("SID: %d\nScore: %f\nGrade: %c\n", SID, Score, Grade);

    No = No + 1;

/* the following statement checks the value of No at the end of each iteration.
    printf("At the end of this iteration, No = : %d\n", No);
*/
  }

/* this is the do-while loop
  do
  { printf("Enter the student ID and score:");
    scanf("%d %f", &SID, &Score);

    if (Score >= 60.0)
    {
      if (Score >=90.0)
       Grade = 'A';
      else
       Grade = 'P';
    }
    else
    {  Grade = 'F';
    }

    printf("SID: %d\nScore: %f\nGrade: %c\n", SID, Score, Grade);

    No = No + 1;
  } while (No <= 3);
*/


/* this is the for loop 
  for (No = 1; No <=3; No = No + 1)
  {
    printf("Enter the student ID and score:");
    scanf("%d %f", &SID, &Score);

    if (Score >= 60.0)
    {
      if (Score >=90.0) 
       Grade = 'A';
      else 
       Grade = 'P';
    }
    else 
    {  Grade = 'F';
    }

    printf("SID: %d\nScore: %f\nGrade: %c\n", SID, Score, Grade);

  }
*/

/* the following statement checks the value of No after the loop is done. 
  printf("\nAt the end of the whole program No = %d \n", No);
*/

  return 0;
}
