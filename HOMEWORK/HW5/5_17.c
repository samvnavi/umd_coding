/* Sample solutions for the first three problems in the homework.
   When you answer other problems, keep the portion above the line 
// DO NOT MAKE CHANGES ABOVE THIS LINE.
   After you implement the function defined in each problem, complete
	the main() function to create a linked list to test your function.

   If you find the function(s) defined for problem 1 and/or problem 2
	useful, feel free to use them.

							Gang Qu
This is problem 17:
(**) Implement a function that takes two ROOT pointers P1 and
P2 to two linked list both sorted in the increasing order, and
returns a ROOT pointer to a merged linked list that is also
sorted in the increasing order. For example, if P1 is 3->5->7->9
and P2 is 4->9, the new list should become 3->4->5->7->9->9.
*/


#include <stdio.h>
#include <stdlib.h>

#define NEW(x) (x*)malloc(sizeof(x))

typedef struct node
{ int * data;
  struct node * next;
} NODE;

typedef struct
{ NODE *head;
} ROOT;

NODE * make_node (int *data)
{ NODE * temp;
  temp = NEW(NODE);
  if (temp != NULL)
  { temp->data = data;
    temp->next = NULL;
  }
  return temp;
}

ROOT * make_root (void)
{ ROOT * temp;
  temp = NEW(ROOT);
  if (temp != NULL)
    temp->head = NULL;
  return temp;
}

// DO NOT MAKE CHANGES ABOVE THIS LINE.

int insert_at_tail(ROOT *r, int *d)	// problem 1. 
{ NODE *temp, *curr ;
  temp = make_node(d);

  if (temp == NULL) return -1;  // fail, cannot create new NODE

  if (r == NULL)
  { r = make_root();
    if (r == NULL) return -1;   // fail, cannot create ROOT
  }

  curr = r->head;		// when the linked list is empty
  if (curr == NULL)
  { r->head = temp;
    return 0;
  }

  for (; curr->next != NULL; curr = curr->next);
				// find the tail, empty loop body
  curr->next = temp; 		// link node temp to the linked list 
				// at the tail.

  return 0;
}

void display_list(ROOT *r)	// problem 2.
{ NODE *temp;
  if (r == NULL) return;		// undefinted linked list
  if (r->head == NULL) return;		// empty linked list
  
  for (temp = r->head; temp != NULL; temp = temp->next)
    printf("%d->", *temp->data);
  printf("/\n");
}


void display_largest(ROOT *r)	// problem 3.
{ NODE *temp;
  int largest = 10;			// safe, because values are 
					// between 10 and 20
  if (r == NULL) return;                
  if (r->head == NULL) return;          

  for (temp = r->head; temp != NULL; temp = temp->next)
    if (*(temp->data) > largest)	// find a larger data
      largest = *(temp->data);
  
  printf("  Largest: %d\n", largest);

}


ROOT * merge(ROOT *r1, ROOT *r2)	// problem 17
{ ROOT *r3;
  NODE *temp1, *temp2, *temp3;
  NODE *curr;

  if (r1 == NULL) return r2;		// if one is empty, return the other one
  if (r2 == NULL) return r1;

  temp1 = r1->head;
  temp2 = r2->head;

  r3 = make_root();
  if (r3 == NULL) return r3;		// return NULL
   
  while(temp1 != NULL && temp2 != NULL)
  { if (*(temp1->data) < *(temp2->data))
    { insert_at_tail(r3, temp1->data); 
      temp1 = temp1->next;
    }
    else 
    { insert_at_tail(r3, temp2->data);
      temp2 = temp2->next;
    }
  }

  if (temp1 == NULL)                    // reach r1's tail
  { while (temp2 != NULL)
    { insert_at_tail(r3, temp2->data);
      temp2 = temp2->next;
    }
  }
  else
  { while (temp1 != NULL)
    { insert_at_tail(r3, temp1->data);
      temp1 = temp1->next;
    }
  }


/*
// compare with the following implementation without calling
// insert_at_tail(r3, .)
  while(temp1 != NULL && temp2 != NULL)
  { if (*(temp1->data) < *(temp2->data))
    { curr = make_node(temp1->data);
      temp1 = temp1->next;
    }
    else
    { curr = make_node(temp2->data);
      temp2 = temp2->next;
    }
    if (r3->head == NULL)
    { r3->head = curr;
      temp3 = curr;
      continue;
    }
    temp3->next = curr;
    temp3 = curr;
  }

  if (temp1 == NULL)			// reach r1's tail
  { while (temp2 != NULL)
    { curr = make_node(temp2->data);
      temp2 = temp2->next;
      temp3->next = curr;
      temp3 = curr;
    }
  }
  else 
  { while (temp1 != NULL)
    { curr = make_node(temp1->data);
      temp1 = temp1->next;
      temp3->next = temp1;
      temp3 = curr;
    }
  }
*/

  return r3;
}


int main(void)
{ int value, i;
  int *p;
  NODE *temp;
  ROOT *r;
  ROOT *r1, *r2, *r3;

  r = make_root();
  if (r == NULL)
    return -1;

  for (i=0; i<10; i++)
  { value = rand()%11 + 10;
    p = NEW(int);
    if (p == NULL) 
      return -1;

    *p = value;

    insert_at_tail(r, p);		// insert at tail
//    display_list(r);			// question 2
//    display_largest(r);			// question 3
  }

  r1 = make_root();
  r2 = make_root();
  r3 = make_root();

  for (i=0; i<10; i++)
  { 
   p = NEW(int);
   if (p == NULL)
     return -1;

   *p = i*2+3;

   insert_at_tail(r1, p);               // insert at tail

   p = NEW(int);
   if (p == NULL)
     return -1;

   *p = i*4+1;
   insert_at_tail(r2, p);
  }

printf("list r1:");
  display_list(r1);
printf("list r2:");
  display_list(r2);

printf("\nMerging r1 and r2 ...\n");
  r3 = merge(r1, r2);
printf("list r3:");
  display_list(r3);

  return 0;
}
