#include <stdio.h>

int main()
{ char a, *p2;
  const char b='#', *p1;
p1 = &b;			
p1 = &a;		
p2 = &a;		
*p2 = '$';
p1 = p2;	

 *p1 = '$';
p2 = &b;
p2 = p1;

  return 0;
}
