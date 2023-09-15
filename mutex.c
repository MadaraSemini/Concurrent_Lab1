#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include "linked_list_util.h"
#include "mutex.h"

double mutexExecution(int thread_count, int total_operations, int member_frac, int insert_frac, int delete_frac)
{

    mutex_data data;
    data.head = NULL;
    // data.m = total_operations;
    data.m = insert_frac + member_frac + delete_frac;

    data.tot_insert_ops = 0;
    data.tot_member_ops = 0;
    data.tot_delete_ops = 0;
    data.completed_count = 0;

    data.member_frac = member_frac;
    data.insert_frac = insert_frac;
    data.delete_frac = delete_frac;

    Populate(&data.head, 1000);

    // Initialize the mutex
    pthread_mutex_init(&data.mutex, NULL);

    // Allocate memory
    pthread_t *thread_handles = malloc(thread_count * sizeof(pthread_t));

    clock_t start, end;
    double time_taken;

    // Start timer
    start = clock();

    // Generate threads
    for (int thread = 0; thread < thread_count; thread++)
    {
        pthread_create(&thread_handles[thread], NULL, threadFuncMutex, (void *)&data);
    }

    for (int thread = 0; thread < thread_count; thread++)
    {
        pthread_join(thread_handles[thread], NULL);
    }

    free(thread_handles);

    // End timer
    end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    // printf("The time taken to execute the program is %f seconds\n", time_taken);

    Destroy(data.head);
    printf("Mutex run complete\n");
    return time_taken;
}

void *threadFuncMutex(void *args)
{

    mutex_data *data = args;

    while (data->completed_count < data->m)
    {

        // Generate random number
        int rand_value = rand() % 65536;

        // Generate random operation number
        int op = rand() % 3;

        if (op == 0 && data->tot_insert_ops < data->insert_frac)
        {
            if (data->completed_count < data->m)
            {
                /* Critical section */
                pthread_mutex_lock(&data->mutex);
                Insert(rand_value, &data->head);
                data->tot_insert_ops++;
                data->completed_count++;
                pthread_mutex_unlock(&data->mutex);
            }
        }
        else if (op == 1 && data->tot_delete_ops < data->delete_frac)
        {
            if (data->completed_count < data->m)
            {
                /* Critical section */
                pthread_mutex_lock(&data->mutex);
                Delete(rand_value, &data->head);
                data->tot_delete_ops++;
                data->completed_count++;
                pthread_mutex_unlock(&data->mutex);
            }
        }
        else if (data->tot_member_ops < data->member_frac)
        {
            if (data->completed_count < data->m)
            {
                /* Critical section */
                pthread_mutex_lock(&data->mutex);
                Member(rand_value, data->head);
                data->tot_member_ops;
                data->completed_count++;
                pthread_mutex_unlock(&data->mutex);
            }
        }
    }
    return NULL;
}