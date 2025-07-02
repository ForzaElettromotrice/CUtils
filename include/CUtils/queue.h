//
// Created by f3m on 07/05/25.
//

#pragma once

#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Node
{
    void *val;
    size_t size;
    struct Node *next;
} Node_t;

typedef struct Queue
{
    Node_t *head;
    Node_t *tail;
} Queue_t;


int initQueue(Queue_t **queue);
void cleanQueue(Queue_t *queue);

int pushFirstQueue(const void *value, size_t size, Queue_t *queue);
int pushQueue(const void *value, size_t size, Queue_t *queue);
int popQueue(Queue_t *queue, void **val, size_t *size);

bool isEmpty(Queue_t *queue);

#ifdef __cplusplus
}
#endif
