#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


struct Stack* create_stack()
{
  struct Stack *stack = malloc(sizeof(struct Stack));
  stack->cur = -1;
  return stack;
}

int is_empty(struct Stack *stack) {
   if(stack->cur == -1)
      return 1;
   else
      return 0;
}
   
int is_full(struct Stack *stack) {
   if(stack->cur == MAX_STACK_SIZE -1)
      return 1;
   else
      return 0;
}

int peek(struct Stack *stack) {
  if (!is_empty(stack)) return stack->arr[stack->cur];
  return -1;
}

int add(struct Stack *stack, int data) {
  if(!is_full(stack)) {
    stack->arr[++stack->cur] = data;
    return 1;
  } 
  
  printf("Could not add data, Stack is full.\n");
  return -1;
}

int pop(struct Stack *stack) {
   int data;
	
  if(!is_empty(stack)) {
    data = stack->arr[stack->cur--];
    return data;
  } 

  printf("Could not retrieve data, Stack is empty.\n");
  return -1;
}

int main() {
  struct Stack *stack = create_stack();
  add(stack, 12);
  printf("peek: %i\n", peek(stack));
  printf("isempty?: %i\n", is_empty(stack) == 1);
  pop(stack);
  printf("isempty?: %i\n", is_empty(stack) == 1);
  return 0;
}