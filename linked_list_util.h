#ifndef LINKED_LIST_UTIL_H
#define LINKED_LIST_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Node */
struct Node
{
    int data;
    struct Node *next;
};

typedef struct Node Node;

int Member(int value, Node *head_p);
int Insert(int value, Node **head_p);
int Delete(int value, Node **head_p);
void Populate(struct Node **head, int count);

#endif