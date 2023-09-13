#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int thread_count;
int m = 3; // Number of rows in the matrix
int n = 4; // Number of columns in the matrix
int y[3];  // Result vector
int a[3][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}};
int x[4] = {1, 2, 3, 4}; // Vector to be multiplied with the matrix

void *Pth_mat_vect(void *rank);

int main(int argc, char *argv[])
{
    long thread;
    pthread_t *thread_handles;

    thread_count = m;
    thread_handles = malloc(thread_count * sizeof(pthread_t));

    for (thread = 0; thread < thread_count; thread++)
        pthread_create(&thread_handles[thread], NULL, Pth_mat_vect, (void *)thread);

    printf("Hello from main thread\n");

    for (thread = 0; thread < thread_count; thread++)
        pthread_join(thread_handles[thread], NULL);

    // Print the result vector y
    printf("Result vector y: ");
    for (int i = 0; i < m; i++)
        printf("%d ", y[i]);
    printf("\n");

    free(thread_handles);
    return 0;
}

void *Pth_mat_vect(void *rank)
{
    long my_rank = (long)rank;
    int i, j;
    int local_m = m / thread_count;
    int my_first_row = my_rank * local_m;
    int my_last_row = (my_rank + 1) * local_m - 1;

    for (i = my_first_row; i <= my_last_row; i++)
    {
        y[i] = 0;
        for (j = 0; j < n; j++)
        {
            y[i] += a[i][j] * x[j];
        }
    }
    return NULL;
}
