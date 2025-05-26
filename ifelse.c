/* This program shows warious way to use if, if-else, switch, and ?: for 
	program selection. 
							Gang Qu
							October 5, 2004 */


#include <stdio.h>

#define ROSTER 59
#define LowA 90.0
#define LowB 80.0
#define LowC 70.0
#define LowD 60.0

int main(void)
{ int i;
  float s;		//lazy, avoid to type score[i]
  char g;		//lazy again but not bad 

  int sid[ROSTER];
  float score[ROSTER];
  char grade[ROSTER];

// initialized the array
  for (i=0; i<ROSTER; i++)
  { sid[i] = 0;
    score[i] = 0.0;
    grade[i] = ' ';
  }

  i = 0;

  while (i < ROSTER)
  {
    do 
    { printf("Enter the ID and score of student %2d:  ", i+1);
      scanf("%d %f", &sid[i], &score[i]);
      if ((sid[i] < 0) || (sid[i] > 999999999)) 
	printf("Student ID must be positive and with maximal 9 digits. \n");
      if ((score[i] < 0) || (score[i] > 100))
	printf("Student's score must be between 0.0 and 100.0 \n");
    } while (!(sid[i] >= 0 && sid[i] <= 999999999 && 0 <= score[i] && score[i] <= 100)); 
    
    s = score[i];
   
/*
// implementation 1:
    if ( s >= LowA )
      g = 'A';
    else
      if (s >= LowB )
        g = 'B';
      else 
	if (s >= LowC)
	  g = 'C';
	else 
	  if (s >= LowD)
	    g = 'D';
	  else
	    g = 'F';

// implemenation 2:
    if (s < LowA)
      if (s < LowB)
        if (s < LowC)
          if (s < LowD)
 	   g = 'F';
	  else g = 'D';
        else g = 'C';
      else g = 'B';
    else g = 'A';

// implementation 3:
    if (s >= LowA) 
      g ='A';
    if (s >= LowB && s < LowA)
      g = 'B';
    if (s >= LowC && s < LowB)
      g = 'C';
    if (s >= LowD && s < LowC)
      g = 'D';
    if (s < LowD)
      g = 'F';

// implemenation 4:
    if (s >= LowB)
      if (s >= LowA) 
        g = 'A';
      else 
	g = 'B';
    else if (s >= LowC)
	   g = 'C';
	 else if (s >= LowD)
		g = 'D';
	      else 
		g = 'F';

// implementation 5:
    g = (s<LowA)?(s<LowB)?(s<LowC)?(s<LowD)?'F':'D':'C':'B':'A';

*/
// implementation 6:
    switch ((int)s/10)
    { case 10: 
      case  9: g = 'A'; break;
      case  8: g = 'B'; break;
      case  7: g = 'C'; break;
      case  6: g = 'D'; break;
      default: g = 'F';
    }

    grade[i] = g;
    printf("SID: %09d   Score: %5.1f   Grade: %c. \n", sid[i], score[i], grade[i]);

    i++;    
  } 
  
  return 0;
}

