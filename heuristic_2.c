/*
  AI Assignment 1
  Group no. 4
  Group Members: Subhadeep Dash - 201601021
                 Sai Vamshi - 201601080
  Solving 15 slide puzzle using second heuristic
*/
#include <stdio.h>
#include <stdlib.h>
//defining macros
#define TOP 1
#define RIGHT 2
#define BOTTOM 3
#define LEFT 4
//max and min functions
#define MAX(a, b) a>b?a:b
#define MIN(a, b) a<b?a:b
//defining structure of Node for List
typedef struct LIST
{
  //puzzle
  int slide[4][4];
  //h(n), parent, i and j position where 0 is present, g(n) respectively
  int sum, change, zero_i, zero_j, step;
  struct LIST *next;
}LIST;
//Pair structure
typedef struct PAIR
{
  int first;
  int second;
}PAIR;
//defining open and close lists' head and rear
LIST *openHead = NULL;
LIST *openRear = NULL;
int openCount = 0;
int closedCount = 0;
int duplicate = 0;
LIST *closeHead = NULL;
LIST *closeRear = NULL;
//actual positions of each stored
PAIR values[16] = {{3, 3}, {0, 0}, {0, 1}, {0, 2}, {0, 3}, {1, 0}, {1, 1}, {1, 2}, {1, 3}, {2, 0}, {2, 1}, {2, 2}, {2, 3}, {3, 0}, {3, 1}, {3, 2}};
//scanning
void scan(LIST *input)
{
  int i, j;
  //h(n) = 0
  input->sum = 0;
  //parent initialization
  input->change = -1;
  input->next = NULL;
  //g(n)=0
  input->step = 0;
  for(i = 0; i <= 3; i++)
  {
    for(j = 0; j <= 3; j++)
    {
      //scanning
      scanf("%d", &(input->slide[i][j]));
      //storing zero indices
      if(input->slide[i][j] == 0)
      {
        input->zero_i = i;
        input->zero_j = j;
      }
      int a = MAX(i, values[input->slide[i][j]].first);
      int b = MIN(i, values[input->slide[i][j]].first);
      int c = MAX(j, values[input->slide[i][j]].second);
      int d = MIN(j, values[input->slide[i][j]].second);
      //finding the h(n) value
      input->sum += ((a+c)-(b+d));
    }
  }
}
//printing the given 15 slides puzzle with parameters
void print(LIST *input)
{
  if(input == NULL)
  {
    return;
  }
  int i, j;
  for(i = 0; i <= 3; i++)
  {
    for (j = 0; j <= 3 ; j++)
    {
      printf("%d ", input->slide[i][j]);
    }
    printf("\n");
  }
  printf("FINAL:\nf(n): %d h(n): %d g(n): %d\nNo. of nodes generated: %d\nNo. of nodes in memory: %d\n----------------------------------------------\n", input->sum+input->step, input->sum, input->step, openCount+duplicate, openCount);
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
    temp->slide[first->zero_i][first->zero_j] = first->slide[first->zero_i-1][first->zero_j];
    temp->slide[first->zero_i-1][first->zero_j] = 0;
    //zero position storing
    temp->zero_i = first->zero_i - 1;
    temp->zero_j = first->zero_j;
    //h(n) initally 0
    temp->sum = 0;
    int i, j;
    for(i = 0; i <= 3; i++)
    {
      for(j = 0; j <= 3; j++)
      {
        //copying all other integers
        if(!(j == first->zero_j && (i == first->zero_i || i == (first->zero_i-1))))
        {
          temp->slide[i][j] = first->slide[i][j];
        }
        int a = MAX(i, values[temp->slide[i][j]].first);
        int b = MIN(i, values[temp->slide[i][j]].first);
        int c = MAX(j, values[temp->slide[i][j]].second);
        int d = MIN(j, values[temp->slide[i][j]].second);
        //h(n) implementation
        temp->sum += ((a+c)-(b+d));
      }
    }
    //g(n) incrementation
    temp->step = first->step + 1;
    //storing parent
    temp->change = TOP;
  }
  else if(change == RIGHT)
  {
    //swapping zero and the required position
    temp->slide[first->zero_i][first->zero_j] = first->slide[first->zero_i][first->zero_j+1];
    temp->slide[first->zero_i][first->zero_j+1] = 0;
    //zero position storing
    temp->zero_j = first->zero_j + 1;
    temp->zero_i = first->zero_i;
    //h(n) initally 0
    temp->sum = 0;
    int i, j;
    for(i = 0; i <= 3; i++)
    {
      for(j = 0; j <= 3; j++)
      {
        //copying all other integers
        if(!(i == first->zero_i && (j == first->zero_j || j == (first->zero_j+1))))
        {
          temp->slide[i][j] = first->slide[i][j];
        }
        int a = MAX(i, values[temp->slide[i][j]].first);
        int b = MIN(i, values[temp->slide[i][j]].first);
        int c = MAX(j, values[temp->slide[i][j]].second);
        int d = MIN(j, values[temp->slide[i][j]].second);
        //h(n) implementation
        temp->sum += ((a+c)-(b+d));
      }
    }
    //g(n) incrementation
    temp->step = first->step + 1;
    //storing parent
    temp->change = RIGHT;
  }
  else if(change == BOTTOM)
  {
    //swapping zero and the required position
    temp->slide[first->zero_i][first->zero_j] = first->slide[first->zero_i+1][first->zero_j];
    temp->slide[first->zero_i+1][first->zero_j] = 0;
    //zero position storing
    temp->zero_i = first->zero_i + 1;
    temp->zero_j = first->zero_j;
    //h(n) initally 0
    temp->sum = 0;
    int i, j;
    for(i = 0; i <= 3; i++)
    {
      for(j = 0; j <= 3; j++)
      {
        //copying all other integers
        if(!(j == first->zero_j && (i == first->zero_i || i == (first->zero_i+1))))
        {
          temp->slide[i][j] = first->slide[i][j];
        }
        int a = MAX(i, values[temp->slide[i][j]].first);
        int b = MIN(i, values[temp->slide[i][j]].first);
        int c = MAX(j, values[temp->slide[i][j]].second);
        int d = MIN(j, values[temp->slide[i][j]].second);
        //h(n) implementation
        temp->sum += ((a+c)-(b+d));
      }
    }
    //g(n) incrementation
    temp->step = first->step + 1;
    //storing parent
    temp->change = BOTTOM;
  }
  else if(change == LEFT)
  {
    //swapping zero and the required position
    temp->slide[first->zero_i][first->zero_j] = first->slide[first->zero_i][first->zero_j-1];
    temp->slide[first->zero_i][first->zero_j-1] = 0;
    //zero position storing
    temp->zero_j = first->zero_j - 1;
    temp->zero_i = first->zero_i;
    //h(n) initally 0
    temp->sum = 0;
    int i, j;
    for(i = 0; i <= 3; i++)
    {
      for(j = 0; j <= 3; j++)
      {
        //copying all other integers
        if(!(i == first->zero_i && (j == first->zero_j || j == (first->zero_j-1))))
        {
          temp->slide[i][j] = first->slide[i][j];
        }
        int a = MAX(i, values[temp->slide[i][j]].first);
        int b = MIN(i, values[temp->slide[i][j]].first);
        int c = MAX(j, values[temp->slide[i][j]].second);
        int d = MIN(j, values[temp->slide[i][j]].second);
        //h(n) implementation
        temp->sum += ((a+c)-(b+d));
      }
    }
    //g(n) incrementation
    temp->step = first->step + 1;
    //storing parent
    temp->change = LEFT;
  }
  else
  {
    int i, j;
    //copying all data
    for(i = 0; i <= 3; i++)
    {
      for(j = 0; j <= 3; j++)
      {
        temp->slide[i][j] = first->slide[i][j];
      }
    }
    temp->sum = first->sum;
    temp->change = first->change;
    temp->step = first->step;
    temp->zero_i = first->zero_i;
    temp->zero_j = first->zero_j;
    temp->next = NULL;
  }
  return temp;
}
int presentClose(LIST *input)
{
  if(input == NULL)
  {
    return 0;
  }
  LIST *temp = closeHead;
  while(temp != NULL)
  {
    //running loop to check
    if(temp->zero_i != input->zero_i || temp->zero_j != input->zero_j || temp->sum != input->sum)
    {
      temp = temp->next;
      continue;
    }
    int i, j;
    //check whether all data is same
    for (i = 0; i <= 3; i++)
    {
      int flag = 1;
      for(j = 0; j <= 3; j++)
      {
        if(temp->slide[i][j] != input->slide[i][j])
        {
          flag = 0;
          break;
        }
      }
      if(flag == 0)
      {
        break;
      }
    }
    //if found replace with minimum
    if(i == 4 && j == 4)
    {
      temp->step = ((temp->step)>(input->step))?(input->step):(temp->step);
      duplicate++;
      return 1;
    }
    temp = temp->next;
  }
  return 0;
}
int presentOpen(LIST *input)
{
  if(input == NULL)
  {
    return 0;
  }
  LIST *temp = openHead;
  while(temp != NULL)
  {
    //running loop to check
    if(temp->zero_i != input->zero_i || temp->zero_j != input->zero_j || temp->sum != input->sum)
    {
      temp = temp->next;
      continue;
    }
    int i, j;
    //check whether all data is same
    for (i = 0; i <= 3; i++)
    {
      int flag = 1;
      for(j = 0; j <= 3; j++)
      {
        if(temp->slide[i][j] != input->slide[i][j])
        {
          flag = 0;
          break;
        }
      }
      if(flag == 0)
      {
        break;
      }
    }
    //if found replace with minimum
    if(i == 4 && j == 4)
    {
      temp->step = ((temp->step)>(input->step))?(input->step):(temp->step);
      duplicate++;
      return 1;
    }
    temp = temp->next;
  }
  return 0;
}
void insertOpen(LIST *input)
{
  if(input == NULL)
  {
    return;
  }
  //if no linkedlist present
  else if(openHead == NULL && openRear == NULL)
  {
    openHead = openRear = input;
    openRear->next = NULL;
  }
  //if it's max
  else if(openRear->step+openRear->sum < input->step+input->sum)
  {
    openRear->next = input;
    openRear = input;
    openRear->next = NULL;
  }
  //if it's min
  else if(openHead->step+openHead->sum > input->step+input->sum)
  {
    input->next = openHead;
    openHead = input;
  }
  else
  {
    LIST *temp;
    temp = openHead;
    //running till f(n) is equal
    while(temp->next != NULL && (temp->next->step + temp->next->sum) < input->step+input->sum)
    {
      temp = temp->next;
    }
    //running till h(n) is equal
    while(temp->next != NULL && temp->next->sum < input->sum && temp->next->step+temp->next->sum == input->step +input->sum)
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
void insertClose(LIST *close)
{
  LIST *input = copy(close, 0);
  if(input == NULL)
  {
    return;
  }
  //if no linkedlist present
  else if(closeHead == NULL && closeRear == NULL)
  {
    closeHead = closeRear = input;
    closeRear->next = NULL;
  }
  //if it's max
  else if(closeRear->step+closeRear->sum < input->step+input->sum)
  {
    closeRear->next = input;
    closeRear = input;
    closeRear->next = NULL;
  }
  //if it's min
  else if(closeHead->step+closeHead->sum > input->step+input->sum)
  {
    input->next = closeHead;
    closeHead = input;
  }
  else
  {
    LIST *temp;
    temp = closeHead;
    //running till f(n) is equal
    while(temp->next != NULL && temp->next->step+temp->next->sum < input->step+input->sum)
    {
      temp = temp->next;
    }
    //running till h(n) is equal
    while(temp->next != NULL && temp->next->step < input->step && temp->next->step+temp->next->sum == input->step+input->sum)
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
void solve(LIST *input)
{
  //for intermediate steps printing
  //print(input);
  if(input == NULL)
  {
    return;
  }
  //solution found if h(n) = 0
  if(input->sum == 0)
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
    if(input->zero_i >= 1 && input->change != BOTTOM)
    {
      first = copy(input, TOP);
    }
    if(input->zero_i <= 2 && input->change != TOP)
    {
      third = copy(input, BOTTOM);
    }
    if(input->zero_j >= 1 && input->change != RIGHT)
    {
      fourth = copy(input, LEFT);
    }
    if(input->zero_j <= 2 && input->change != LEFT)
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
  //initialization of a random question for which solution is present
  input->slide[0][0] = 2;
  input->slide[0][1] = 3;
  input->slide[0][2] = 7;
  input->slide[0][3] = 4;
  input->slide[1][0] = 1;
  input->slide[1][1] = 5;
  input->slide[1][2] = 0;
  input->slide[1][3] = 8;
  input->slide[2][0] = 9;
  input->slide[2][1] = 6;
  input->slide[2][2] = 10;
  input->slide[2][3] = 12;
  input->slide[3][0] = 13;
  input->slide[3][1] = 14;
  input->slide[3][2] = 11;
  input->slide[3][3] = 15;
  input->zero_i = 1;
  input->zero_j = 2;
  input->step = input->change = 0;
  input->sum = 12;
  input->next = NULL;
}
int isSolvable(LIST *input)
{
  int i, j, k=0, inversions = 0;
  int p[20];
  for(i = 0;i <= 3; i++)
  {
    for(j = 0; j <= 3; j++)
    {
      p[k++] = input->slide[i][j];
    }
  }
  for(i = 0; i <= 15; i++)
  {
    for(j = i+1; j <= 15; j++)
    {
      if(p[i] > p[j])
      {
        inversions++;
      }
    }
  }
  if(inversions%2 == 0 && (input->zero_i)%2 == 1)
  {
    return 1;
  }
  else if(inversions%2 == 1 && (input->zero_i)%2 == 0)
  {
    return 1;
  }
  return 0;
}
int main(int argc, char const *argv[])
{
  LIST *input;
  input = (LIST *)(malloc(sizeof(LIST)));
  //scan(input);
  rando(input);
  //print(input);
  (isSolvable(input) == 1)?(solve(input)):(printf("NOT SOLVABLE\n"));
  return 0;
}
