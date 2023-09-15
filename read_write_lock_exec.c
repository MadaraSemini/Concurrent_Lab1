#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "linked_list_util.h"
#include "read_write_lock_exec.h"

double readWriteLockExec(int thread_count, int total_operations, int member_frac, int insert_frac, int delete_frac)
{
    read_write_lock_data data;
    data.head = NULL;

    data.m = total_operations;
    data.tot_member_ops = 0;
    data.tot_insert_ops = 0;
    data.tot_delete_ops = 0;
    data.total_ops = 0;

    int completed_count = 0;

    Populate(&data.head, 1000);

    // Initializing the read write lock, mutex and allocating memory for threads
    pthread_rwlock_init(&data.rwlock, NULL);
    pthread_mutex_init(&data.mutex, NULL);
    pthread_t *thread_handles = malloc(thread_count * sizeof(pthread_t));

    clock_t start, end;
    double time_taken;

    start = clock();

    // Creating and joining threads

    for (int thread = 0; thread < thread_count; thread++)
    {
        pthread_create(&thread_handles[thread], NULL, ReadWriteThread, (void *)&data);
    }

    for (int thread = 0; thread < thread_count; thread++)
    {
        pthread_join(thread_handles[thread], NULL);
    }

    free(thread_handles);

    end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("The time taken to execute the program is %f seconds\n", time_taken);

    pthread_rwlock_destroy(&data.rwlock);
    pthread_mutex_destroy(&data.mutex);
    // Destroy(&data.head);
    printf("Read Write Lock Execution completed\n");
    return time_taken;
}

void *ReadWriteThread(void *args)
{

    read_write_lock_data *data = args;
    pthread_t tid = pthread_self(); // Get the thread ID
    printf("Thread ID: %lu\n", tid);

    while (data->total_ops < data->m)
    {
        int operation_type = rand() % 3;
        int value_for_op = rand() % 65536;

        if (operation_type == 0 && data->tot_member_ops < data->member_frac)
        {
            if (data->total_ops < data->m)
            {
                /* Critical section */
                pthread_rwlock_rdlock(&data->rwlock);
                Member(value_for_op, data->head);
                pthread_rwlock_unlock(&data->rwlock);

                /* Critical section*/
                pthread_mutex_lock(&data->mutex);
                data->tot_member_ops++;
                data->total_ops++;
                pthread_mutex_unlock(&data->mutex);
            }
        }
        else if (operation_type == 1 && data->tot_insert_ops < data->insert_frac)
        {
            if (data->total_ops < data->m)
            {
                /* Critical section */
                pthread_rwlock_wrlock(&data->rwlock);
                Insert(value_for_op, &data->head);
                data->tot_insert_ops++;
                data->total_ops++;
                pthread_rwlock_unlock(&data->rwlock);
            }
        }
        else if (operation_type == 2 && data->tot_delete_ops < data->delete_frac)
        {
            if (data->total_ops < data->m)
            {
                /* Critical section */
                pthread_rwlock_wrlock(&data->rwlock);
                Delete(value_for_op, &data->head);
                data->tot_delete_ops++;
                data->total_ops++;
                pthread_rwlock_unlock(&data->rwlock);
            }
        }
    }
    return NULL;
}