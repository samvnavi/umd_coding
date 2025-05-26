/* Sample solutions for the first three problems in the homework.
   When you answer other problems, keep the portion above the line 
// DO NOT MAKE CHANGES ABOVE THIS LINE.
   After you implement the function defined in each problem, complete
	the main() function to create a linked list to test your function.

   If you find the function(s) defined for problem 1 and/or problem 2
	useful, feel free to use them.

							Gang Qu
This is problem 18:
(**) Implement a function that takes a ROOT pointer as input
and checks whether there is a pair of NODEs where the value of
one NODE is a multiple of the other. Return the “index” of the
NODE with the smaller value and 0 if no such pair. For example,
on 3->8->4->7->9->2, you can return either 3 (for 4) or 6 (for 2).
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


int find_multiple(ROOT *r)		// problem 18
{ int pos1=0, pos2=0;			// indices of the two numbers
					// return the one with smaller value
  NODE *temp1, *temp2;

  if (r == NULL) return 0;		// not found

  for (temp1 = r->head; temp1 != NULL; temp1 = temp1->next)
  { pos1++;
    pos2 = pos1;
    for (temp2 = temp1->next; temp2 != NULL; temp2 = temp2->next)
    { pos2++; 
      if (*(temp1->data)<=*(temp2->data) && *(temp2->data) % *(temp1->data) == 0)
        return pos1;
      if (*(temp1->data) > *(temp2->data) && *(temp1->data) % *(temp2->data) == 0)
        return pos2;
    }
  }

  return 0;
}
    


int main(void)
{ int value, i;
  int *p;
  NODE *temp;
  ROOT *r;

  r = make_root();
  if (r == NULL)
    return -1;

  for (i=0; i<10; i++)
  { value = rand()%31 + 10;		// increse the range from 11 to 31
    p = NEW(int);
    if (p == NULL) 
      return -1;

    *p = value;

    insert_at_tail(r, p);		// insert at tail
//    display_list(r);			// question 2
//    display_largest(r);			// question 3
  }

  display_list(r);
  printf("index of smaller value: %d\n", find_multiple(r));

  return 0;
}
