#ifndef QUEUE_H
#define QUEUE_H

#define MAX_QUEUE_SIZE 1024

struct Queue {
  int arr[MAX_QUEUE_SIZE];
  int cur;
};

struct Queue* create_queue();
int length(struct Queue *queue);   
int is_empty(struct Queue *queue);   
int is_full(struct Queue *queue);
int peek(struct Queue *queue);
int add(struct Queue *queue, int data);
int pop(struct Queue *queue);

#endif