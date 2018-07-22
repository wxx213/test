#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

/**
1. enqueue by moving queue::rear element
2. dequeue by moving queue::front element
3. actually element in queue is queue::parry[queue::front]
    ~ queue::parry[queue::rear - 1]
**/
struct queue {
    int capacity;
    int front;
    int rear;
    int size;
    int *parray;
};

struct queue *createqueue(int cap);
void destroyqueue(struct queue *pq);
int enqueue(struct queue *pq, int element);
int dequeue(struct queue *pq);
void printqueue(struct queue *pq);

#endif // QUEUE_H_INCLUDED
