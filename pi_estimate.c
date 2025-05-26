/* Use the following procedure to estimate the value of Pi (which is
 * approximately 3.1415926...)
 * 1. generate N random points (x,y) in the x-y plane, where -1 <= x, y <= 1.
 * 2. count how many points are inside the unit circle x^2 + y^2 <= 1, let us
 * assume that there are m such points
 * 3. the value of 4*m/N is an estimate of Pi.
 * Write a program to implement this procedure. Your program should take the
 * value of N from the command line and print out the estimate of Pi on the
 * screen. 
 * For example, 
 * a.out 100
 * Pi = 3.1600
 * */

#include<stdio.h>
#include<stdlib.h>


int main(int argc, char *argv[])
{ float pi = 0.0;
  int round;		// number of simulations
  float x, y;		// (x,y) coordinates of the random point
  int cnt = 0;		// number of points in the circle
  int i;

  round = atoi(argv[1]);

  for (i=0; i<round; i++)
  { x = 1.0 * rand()/RAND_MAX;
    if (rand()%2 == 0) 
     x = -x;		// x could be between -1 and 0
    y = 1.0 * rand()/RAND_MAX; 
    if (rand()%2 == 0)
     y = -y;

    if (x*x + y*y <= 1) 
     cnt++;
  }
  
  printf("Pi = %.4f\n", 4.0*cnt/round);

  return 0;
}
