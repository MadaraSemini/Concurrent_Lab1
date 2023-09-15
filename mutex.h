#ifndef LAB1_MUTEX_H
#define LAB1_MUTEX_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>
#include "linked_list_util.h"

void *threadFuncMutex(void* rank);

struct mutex_data {
    pthread_mutex_t mutex;
    Node *head;

    int m;

    int member_frac;
    int insert_frac;
    int delete_frac;

    int tot_member_ops;
    int tot_insert_ops;
    int tot_delete_ops;
    int completed_count;
};
typedef struct mutex_data mutex_data;

double mutexExecution(int thread_count, int total_operations, int member_frac, int insert_frac, int delete_frac);

#endif //LAB1_MUTEX_H
