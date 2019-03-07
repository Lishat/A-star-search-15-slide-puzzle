/*
  AI Assignment 1
  Group no. 4
  Group Members: Subhadeep Dash - 201601021
                 Sai Vamshi - 201601080
  Solving 15 slide puzzle using first heuristic
*/
#include <stdio.h>
#include <stdlib.h>

//defining macros
#define TOP 1
#define RIGHT 2
#define BOTTOM 3
#define LEFT 4

//defining structure of Node for List
typedef struct LIST
{
  int slide[20];
  struct LIST *next;
}LIST;
//defining open and close lists' head and rear
LIST *openHead = NULL;
LIST *openRear = NULL;
int openCount = 0;
int closedCount = 0;
int duplicate = 0;
LIST *closeHead = NULL;
LIST *closeRear = NULL;

//scanning input 15-slide puzzle
void scan(LIST *input)
{
  int i;
  //h[n] = 0 initially i.e. h[n] is stored in slide[17]
  input->slide[17] = 0;
  //g[n] = 0 initially i.e. g[n] is stored in slide[18]
  input->slide[18] = 0;
  //parent is initally -1
  input->slide[19] = -1;
  for(i = 1; i <= 16; i++)
  {
    //scanning
    scanf("%d", &(input->slide[i]));
    //storing zero index in slide[0]
    if(input->slide[i] == 0)
    {
      input->slide[0] = i;
    }
    //calculating no. of misplaced characters
    if(input->slide[i] != i)
    {
      input->slide[17] = input->slide[17] + 1;
    }
  }
  input->next = NULL;
}
LIST *copy(LIST *first, int change)
{
  LIST *temp;
  temp = (LIST *)(malloc(sizeof(LIST)));
  temp->next = NULL;
  //copying as per the given parameter
  if(change == TOP)
  {
    //swapping zero and the required position
    temp->slide[first->slide[0]] = first->slide[first->slide[0]-4];
    temp->slide[first->slide[0]-4] = 0;
    //zero position storing
    temp->slide[0] = first->slide[0]-4;
    //no. of misplaced characters initally 0
    temp->slide[17] = 0;
    int i;
    for(i = 1; i <= 16; i++)
    {
      //copying all others except the specified 2 characters
      if(i != first->slide[0] && i != first->slide[0]-4)
      {
        temp->slide[i] = first->slide[i];
      }
      //no. of misplaced characters
      if(temp->slide[i] != i)
      {
        temp->slide[17] = temp->slide[17] + 1;
      }
    }
    //increment no. of steps = g[n] by 1
    temp->slide[18] = first->slide[18] + 1;
    //initialize parent to TOP
    temp->slide[19] = TOP;
  }
  else if(change == RIGHT)
  {
    //swapping zero and the required position
    temp->slide[first->slide[0]] = first->slide[first->slide[0]+1];
    temp->slide[first->slide[0]+1] = 0;
    //zero position storing
    temp->slide[0] = first->slide[0]+1;
    //no. of misplaced characters initally 0
    temp->slide[17] = 0;
    int i;
    for(i = 1; i <= 16; i++)
    {
      //copying all others except the specified 2 characters
      if(i != first->slide[0] && i != first->slide[0]+1)
      {
        temp->slide[i] = first->slide[i];
      }
      //no. of misplaced characters
      if(temp->slide[i] != i)
      {
        temp->slide[17] = temp->slide[17] + 1;
      }
    }
    //increment no. of steps = g[n] by 1
    temp->slide[18] = first->slide[18] + 1;
    //initialize parent to RIGHT
    temp->slide[19] = RIGHT;
  }
  else if(change == BOTTOM)
  {
    //swapping zero and the required position
    temp->slide[first->slide[0]] = first->slide[first->slide[0]+4];
    temp->slide[first->slide[0]+4] = 0;
    //zero position storing
    temp->slide[0] = first->slide[0]+4;
    //no. of misplaced characters initally 0
    temp->slide[17] = 0;
    int i;
    for(i = 1; i <= 16; i++)
    {
      //copying all others except the specified 2 characters
      if(i != first->slide[0] && i != first->slide[0]+4)
      {
        temp->slide[i] = first->slide[i];
      }
      //no. of misplaced characters
      if(temp->slide[i] != i)
      {
        temp->slide[17] = temp->slide[17] + 1;
      }
    }
    //increment no. of steps = g[n] by 1
    temp->slide[18] = first->slide[18] + 1;
    //initialize parent to BOTTOM
    temp->slide[19] = BOTTOM;
  }
  else if(change == LEFT)
  {
    //swapping zero and the required position
    temp->slide[first->slide[0]] = first->slide[first->slide[0]-1];
    temp->slide[first->slide[0]-1] = 0;
    //zero position storing
    temp->slide[0] = first->slide[0]-1;
    //no. of misplaced characters initally 0
    temp->slide[17] = 0;
    int i;
    for(i = 1; i <= 16; i++)
    {
      //copying all others except the specified 2 characters
      if(i != first->slide[0] && i != first->slide[0]-1)
      {
        temp->slide[i] = first->slide[i];
      }
      //no. of misplaced characters
      if(temp->slide[i] != i)
      {
        temp->slide[17] = temp->slide[17] + 1;
      }
    }
    //increment no. of steps = g[n] by 1
    temp->slide[18] = first->slide[18] + 1;
    //initialize parent to LEFT
    temp->slide[19] = LEFT;
  }
  else
  {
    //copy everything condition
    int i;
    for(i = 0; i <= 19; i++)
    {
      temp->slide[i] = first->slide[i];
    }
  }
  return temp;
}
//printing elements
void print(LIST *input)
{
  if(input == NULL)
  {
    return;
  }
  int i;
  for(i = 1; i <= 16; i++)
  {
    printf("%d ", input->slide[i]);
    if(i%4 == 0)
    {
      printf("\n");
    }
  }
  printf("FINAL:\nf(n): %d h(n): %d g(n): %d\nNo. of nodes generated: %d\nNo. of nodes in memory: %d\n----------------------------------------------\n", input->slide[17]+input->slide[18], input->slide[17], input->slide[18], openCount+duplicate, openCount);
}
//inserting in Open list
void insertOpen(LIST *input)
{
  if(input == NULL)
  {
    return;
  }
  //inserting if the openHead or openRear is NULL
  else if(openHead == NULL && openRear == NULL)
  {
    openHead = openRear = input;
    openRear->next = NULL;
  }
  //inserting at last if max
  else if(openRear->slide[17]+openRear->slide[18] < input->slide[17]+input->slide[18])
  {
    openRear->next = input;
    openRear = input;
    openRear->next = NULL;
  }
  //inserting at first if min
  else if(openHead->slide[17]+openHead->slide[18] > input->slide[17]+input->slide[18])
  {
    input->next = openHead;
    openHead = input;
  }
  else
  {
    LIST *temp;
    temp = openHead;
    //running till f(n) is equal
    while(temp->next != NULL && temp->next->slide[17]+temp->next->slide[18] < input->slide[17]+input->slide[18])
    {
      temp = temp->next;
    }
    //running till h(n) is equal
    while(temp->next != NULL && temp->next->slide[17] < input->slide[17] && temp->next->slide[17]+temp->next->slide[17] == input->slide[17]+input->slide[18])
    {
      temp = temp->next;
    }
    //inserting
    LIST *hold;
    hold = temp->next;
    temp->next = input;
    input->next = hold;
    //if it is last node point rear node to the current
    if(temp == openRear)
    {
      openRear = openRear->next;
    }
  }
  openCount++;
}
//inserting in close list
void insertClose(LIST *close)
{
  LIST *input = copy(close, 0);
  if(input == NULL)
  {
    return;
  }
  //inserting if the closeHead or closeRear is NULL
  else if(closeHead == NULL && closeRear == NULL)
  {
    closeHead = closeRear = input;
    closeRear->next = NULL;
  }
  //inserting at last if max
  else if(closeRear->slide[17]+closeRear->slide[18] < input->slide[17]+input->slide[18])
  {
    closeRear->next = input;
    closeRear = input;
    closeRear->next = NULL;
  }
  //inserting at first if min
  else if(closeHead->slide[17]+closeHead->slide[18] > input->slide[17]+input->slide[18])
  {
    input->next = closeHead;
    closeHead = input;
  }
  else
  {
    LIST *temp;
    temp = closeHead;
    //running till f(n) is equal
    while(temp->next != NULL && temp->next->slide[17]+temp->next->slide[17] < input->slide[17]+input->slide[18])
    {
      temp = temp->next;
    }
    //running till h(n) is equal
    while(temp->next != NULL && temp->next->slide[17] < input->slide[17] && temp->next->slide[17]+temp->next->slide[17] == input->slide[17]+input->slide[18])
    {
      temp = temp->next;
    }
    //inserting
    LIST *hold;
    hold = temp->next;
    temp->next = input;
    input->next = hold;
    //if it is last node point rear node to the current
    if(temp == closeRear)
    {
      closeRear = closeRear->next;
    }
  }
  closedCount++;
}
int presentOpen(LIST *input)
{
  if(input == NULL)
  {
    return 0;
  }
  //checking if it there in open list
  LIST *temp = openHead;
  while(temp != NULL)
  {
    if(temp->slide[0] != input->slide[0] || temp->slide[17] != input->slide[17])
    {
      temp = temp->next;
      continue;
    }
    int i;
    for(i = 1;i <= 16; i++)
    {
      if(temp->slide[i] != input->slide[i])
      {
        break;
      }
    }
    //if present update it with min valued one
    if(i == 17)
    {
      temp->slide[18] = ((temp->slide[18])>(input->slide[18]))?(input->slide[18]):(temp->slide[18]);
      duplicate++;
      return 1;
    }
    temp = temp->next;
  }
  return 0;
}
int presentClose(LIST *input)
{
  if(input == NULL)
  {
    return 0;
  }
  //checking if it there in close list
  LIST *temp = closeHead;
  while(temp != NULL)
  {
    if(temp->slide[0] != input->slide[0] || temp->slide[17] != input->slide[17])
    {
      temp = temp->next;
      continue;
    }
    int i;
    for(i = 1;i <= 16; i++)
    {
      if(temp->slide[i] != input->slide[i])
      {
        break;
      }
    }
    //if present replace it with min valued one
    if(i == 17)
    {
      temp->slide[18] = ((temp->slide[18])>(input->slide[18]))?(input->slide[18]):(temp->slide[18]);
      duplicate++;
      return 1;
    }
    temp = temp->next;
  }
  return 0;
}
void solve(LIST *input)
{
  //for intermediate steps printing
  //print(input);
  if(input == NULL)
  {
    return;
  }
  //solution found if misplaced only equal to blank i.e. h(n) = 1
  if(input->slide[17] == 1)
  {
    print(input);
    return;
  }
  else
  {
    //four possible cases
    LIST *first, *second, *third, *fourth;
    first = second = third = fourth = NULL;
    //checking out of four how many are possible
    if(input->slide[0] >= 5 && input->slide[0] <= 16 && input->slide[19] != BOTTOM)
    {
      first = copy(input, TOP);
    }
    if(input->slide[0] >= 1 && input->slide[0] <= 12 && input->slide[19] != TOP)
    {
      third = copy(input, BOTTOM);
    }
    if((input->slide[0])%4 != 1 && input->slide[19] != RIGHT)
    {
      fourth = copy(input, LEFT);
    }
    if((input->slide[0])%4 != 0 && input->slide[19] != LEFT)
    {
      second = copy(input, RIGHT);
    }
    //checking of each in closed and inserting in open list
    presentClose(first);
    if(presentOpen(first) != 1)
    {
      insertOpen(first);
    }
    presentClose(second);
    if(presentOpen(second) != 1)
    {
      insertOpen(second);
    }
    presentClose(third);
    if(presentOpen(third) != 1)
    {
      insertOpen(third);
    }
    presentClose(fourth);
    if(presentOpen(fourth) != 1)
    {
      insertOpen(fourth);
    }
    LIST *temp = openHead;
    openHead = openHead->next;
    insertClose(temp);
    //recursive function
    solve(temp);
  }
}
void rando(LIST *input)
{
  //randomized one for which solution is available
  input->slide[0] = 7;
  input->slide[1] = 2;
  input->slide[2] = 3;
  input->slide[3] = 7;
  input->slide[4] = 4;
  input->slide[5] = 1;
  input->slide[6] = 5;
  input->slide[7] = 0;
  input->slide[8] = 8;
  input->slide[9] = 9;
  input->slide[10] = 6;
  input->slide[11] = 10;
  input->slide[12] = 12;
  input->slide[13] = 13;
  input->slide[14] = 14;
  input->slide[15] = 11;
  input->slide[16] = 15;
  input->slide[17] = 10;
  input->slide[18] = 0;
  input->slide[19] = 0;
  input->next = NULL;
}
int isSolvable(LIST *input)
{
  int inversions = 0, i, j;
  for(i = 1; i <= 16; i++)
  {
    for(j = i+1; j <= 16; j++)
    {
      if(input->slide[i] > input->slide[j])
      {
        inversions++;
      }
    }
  }
  if(inversions%2 == 0 && (input->slide[0]/4)%2 == 1)
  {
    return 1;
  }
  else if(inversions%2 == 1 && (input->slide[0]/4)%2 == 0)
  {
    return 1;
  }
  return 0;
}
//main function
int main(int argc, char const *argv[])
{
  LIST *input;
  input = (LIST *)(malloc(sizeof(LIST)));
  //scan(input);
  rando(input);
  (isSolvable(input) == 1)?(solve(input)):(printf("NOT SOLVABLE\n"));
  return 0;
}
