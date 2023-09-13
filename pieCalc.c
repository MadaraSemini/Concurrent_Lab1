#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int thread_count;
int n = 999999999; // Number of terms in the sequence
double sum;
pthread_mutex_t mutex; // Declare a mutex variable

void *Thread_sum(void *rank);

int main(int argc, char *argv[])
{
    time_t start_time, end_time;
    double time_difference;

    long thread;
    pthread_t *thread_handles;

    thread_count = strtol(argv[1], NULL, 10);
    thread_handles = malloc(thread_count * sizeof(pthread_t));

    time(&start_time);

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    for (thread = 0; thread < thread_count; thread++)
        pthread_create(&thread_handles[thread], NULL, Thread_sum, (void *)thread);

    printf("Hello from main thread\n");

    for (thread = 0; thread < thread_count; thread++)
        pthread_join(thread_handles[thread], NULL);

    time(&end_time);

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    // Print the result
    printf("Result: %lf\n", 4.0 * sum);

    time_difference = difftime(end_time, start_time);
    printf("Time difference: %.2lf seconds\n", time_difference);

    free(thread_handles);
    return 0;
}

void *Thread_sum(void *rank)
{
    long my_rank = (long)rank;
    double factor;
    long long i;
    long long my_n = n / thread_count;
    long long my_first_i = my_n * my_rank;
    long long my_last_i = my_first_i + my_n;
    double my_sum = 0.0;

    printf("\n****\nRank :%ld\n", my_rank);
    printf("First i :%ld\n", my_first_i);
    printf("Last i :%ld\n", my_last_i);
    printf("Local n:%ld\n****\n", my_n);

    if (my_first_i % 2 == 0) // even
        factor = 1.0;
    else
        factor = -1.0;

    for (i = my_first_i; i < my_last_i; i++, factor = -factor)
    {
        my_sum += factor / (2 * i + 1);
    }

    // Lock the mutex before updating the shared variable
    pthread_mutex_lock(&mutex);
    sum += my_sum;
    // Unlock the mutex after updating the shared variable
    pthread_mutex_unlock(&mutex);

    return NULL;
}
