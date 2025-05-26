#include <stdio.h>
#include <stdlib.h>

#define NEW(x) (x*)malloc(sizeof(x))

typedef struct node
{ void * data;
  struct node * next;
} NODE;

void display1(NODE n)
{ printf("By display1: %d\n", *(int *)(n.data));
// there will be a warning if you don't cast explicitly
// printf("By display1: %d\n", *(n.data));
}

void display2(void * d)
{ printf("By display2: %d\n", *(int *)d);
}

NODE * make_node (void *data)
{ NODE * temp;
  temp = NEW(NODE);
  if (temp != NULL)
  { temp->data = data;
    temp->next = NULL;
  }
  return temp;
}

int main(void)
{ 
  int data1, data2;
  void * dp1, *dp2;
  NODE *first, *second;

  printf("Enter two integers: ");
  scanf("%d%d", &data1, &data2);
  dp1 = &data1;
  dp2 = &data2;

// can I replace the above three lines by
// scanf("%d%d", (int *) dp1, (int *) dp2);

  first = make_node(dp1);
  second = make_node(dp2);

  display1(*first);
  display2(second->data);

  first->next = second;
  display1(*(first->next));
  return 0;
}

     
