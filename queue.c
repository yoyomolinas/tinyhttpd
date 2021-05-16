#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


struct Queue* create_queue()
{
  struct Queue *queue = malloc(sizeof(struct Queue));
  queue->cur = -1;
  return queue;
}

int length(struct Queue *queue)
{
  return queue->cur+1;
}

int is_empty(struct Queue *queue) {
   if(queue->cur == -1)
      return 1;
   else
      return 0;
}
   
int is_full(struct Queue *queue) {
   if(queue->cur == MAX_QUEUE_SIZE -1)
      return 1;
   else
      return 0;
}

int peek(struct Queue *queue) {
  if (!is_empty(queue)) return queue->arr[0];
  return -1;
}

int add(struct Queue *queue, int data) {
  if(!is_full(queue)) {
    queue->arr[++queue->cur] = data;
    return 1;
  } 
  
  printf("Could not add data, Queue is full.\n");
  return -1;
}

int pop(struct Queue *queue) {
   int data;
	
  if(!is_empty(queue)) {
    data = queue->arr[0];
    for (int i = 1; i <= queue->cur; i++)
    {
      queue->arr[i-1] = queue->arr[i];
    }

    queue->cur--;
    return data;
  } 

  printf("Could not retrieve data, Queue is empty.\n");
  return -1;
}

// Test function
// int main() {
//   struct Queue *queue = create_queue();
//   add(queue, 12);
//   add(queue, 13);
//   add(queue, 14);
//   add(queue, 15);
//   add(queue, 16);
//   while(!is_empty(queue))
//   {
//     printf("peek: %i\n", peek(queue));
//     pop(queue);
//   }
  
//   return 0;
// }