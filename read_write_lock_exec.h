#ifndef READ_WRITE_LOCK_H
#define READ_WRITE_LOCK_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "linked_list_util.h"

void *ReadWriteThread(void *rank);

struct read_write_lock_data
{
    pthread_rwlock_t rwlock;
    pthread_mutex_t mutex;
    Node *head;
    int m;
    int tot_member_ops;
    int tot_insert_ops;
    int tot_delete_ops;
    int total_ops;
    int member_frac;
    int insert_frac;
    int delete_frac;
};

typedef struct read_write_lock_data read_write_lock_data;

double readWriteLockExec(int thread_count, int total_operations, int member_frac, int insert_frac, int delete_frac);

#endif
