#include<stdio.h>
#include<string.h>

struct student
{ char name[40];
  int SID;
  char status[2];
  float exams[3];
  float project[5];
  float hw[5];
};

void display (struct student s);

int main(void)
{
// structure variable decalaration and initialization
  struct student s1 = {"Joe Smith", 12345678, "JR", 
	{69.5, 80}, {100, 90, 98}, {18, 19, 20}};
  struct student s2, *p1;

// access structure elements
  printf("%s\n%d\n%s\n%5.2f %5.2f %5.2f\n %5.2f %5.2f %5.2f\n",
	s1.name, s1.SID, s1.status, s1.exams[0], s1.exams[1],
	s1.exams[2], s1.project[0], s1.project[1], s1.project[2]);

// size of the structure is not simply the sum of all its elements
  putchar('\n');
  printf("size of the structure student is %d\n", sizeof(s1));
  printf("%d, %d, %d, %d, %d, %d \n", sizeof(s1.name), sizeof(s1.SID), 
	sizeof(s1.status), sizeof(s1.exams), sizeof(s1.project),sizeof(s1.hw));

// copy and assignment of structure
  s2 = s1;
  printf("name of s2: %s\t exam 1 score = %5.2f\n", s2.name, s2.exams[0]);

// update structure elements
  strcpy(s2.name, "Jane Doe");
  s2.exams[0] += 3.0;
  printf("name of s2: %s\t exam 1 score = %5.2f\n", s2.name, s2.exams[0]);
  printf("name of s1: %s\t exam 1 score = %5.2f\n", s1.name, s1.exams[0]);

// structure and function
  display (s1);

// pointers to structure
  p1 = &s1;
  p1->exams[0] += 3.0;
  display (*p1);
  display (s1);

  return 0;
}

void display (struct student s)
{ printf("name: %s\n", s.name);
  printf("SID: %09d\n", s.SID);
  printf("Status: %s\n", s.status);
  printf("Exam scores: %5.2f, %5.2f, %5.2f\n", 
	s.exams[0], s.exams[1], s.exams[2]);
  printf("Project scores: %5.2f, %5.2f, %5.2f,%5.2f,%5.2f \n",
	s.project[0], s.project[1], s.project[2], s.project[3], s.project[4]);
  printf("Homework scores: %5.2f, %5.2f, %5.2f,%5.2f,%5.2f \n",
        s.hw[0], s.hw[1], s.hw[2], s.hw[3], s.hw[4]);
}
