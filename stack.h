#ifndef STACK_H
#define STACK_H

#define MAX_STACK_SIZE 1024

struct Stack {
  int arr[MAX_STACK_SIZE];
  int cur;
};

struct Stack* create_stack();
int is_empty(struct Stack *stack);   
int is_full(struct Stack *stack);
int peek(struct Stack *stack);
int add(struct Stack *stack, int data);
int pop(struct Stack *stack);

#endif