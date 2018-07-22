#include<stdio.h>
#include<stdlib.h>

#include "queue.h"

static int isempty(struct queue *pq)
{
    return pq->size == 0;
}
static int isfull(struct queue *pq)
{
    return pq->size >= pq->capacity;
}
static void makeempty(struct queue *pq)
{
    pq->size = 0;
    pq->front = 0;
    pq->rear = 0;
}
struct queue *createqueue(int cap)
{
    if(cap < 1) {
        return NULL;
    }
    struct queue *pq = malloc(sizeof(struct queue));
    if(pq) {
        pq->parray = malloc(cap * sizeof(int));
        if(!pq->parray) {
            free(pq);
            return NULL;
        }
        pq->capacity = cap;
        makeempty(pq);
    }
    else {
        return NULL;
    }

    return pq;
}
void destroyqueue(struct queue *pq)
{
    free(pq->parray);
    free(pq);
}

int enqueue(struct queue *pq, int element)
{
    if(isfull(pq)) {
        return -1;
    }
    pq->parray[pq->rear] = element;
    pq->rear++;
    if(pq->rear >= pq->capacity){
        pq->rear = 0;
    }
    pq->size++;

    return 0;
}
int dequeue(struct queue *pq)
{
    int temp;

    if(isempty(pq)) {
        return -1;
    }
    temp = pq->parray[pq->front];
    pq->front++;
    if(pq->front >= pq->capacity) {
        pq->front = 0;
    }
    pq->size--;

    return temp;
}
void printqueue(struct queue *pq)
{
    int front = pq->front;
    int rear = pq->rear;

    if(isempty(pq)) {
        printf("queue is empty\n");
        return;
    }
    printf("\n");
    do {
        printf("%d ", pq->parray[front]);
        front++;
        if(front >= pq->capacity) {
            front = 0;
        }
    }while(front != rear);
    printf("\n");
}
