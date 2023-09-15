#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "serial_exec.h"
#include "mutex.h"

int main(int argc, char* argv[]) {
    double serial_runtime, mut_t1_runtime, mut_t2_runtime, mut_t4_runtime, mut_t8_runtime, rw_t1_runtime,  rw_t2_runtime, rw_t4_runtime, rw_t8_runtime;

    // Number of samples
    const int N = 385;

    // Number of operations
    int m = 10000;

    // Fractions for each case
    int member_frac;
    int insert_frac;
    int delete_frac;

    // Use current time as seed for random generator
    srand(time(0));

    // FILE *file;

    // Iterate for the 3 cases
    for (int i = 0; i < 3; i++) {
        switch (i) {
            case 0:
            printf("case 0");
                // file = fopen("C:\\Concurrent Programming\\Assignments\\Lab1\\output\\Case_1.csv","w+");
                // fprintf(file,"Serial, Mutex_t1, Mutex_t2, Mutex_t4, Mutex_t8, ReadWrite_t1, ReadWrite_t2, ReadWrite_t4, ReadWrite_t8\n");
                member_frac = lround(m * 0.99);
                insert_frac = lround(m * 0.005);
                delete_frac = lround(m * 0.005);
                break;

            case 1:
                // file = fopen("C:\\Concurrent Programming\\Assignments\\Lab1\\output\\Case_2.csv","w+");
                // fprintf(file,"Serial, Mutex_t1, Mutex_t2, Mutex_t4, Mutex_t8, ReadWrite_t1, ReadWrite_t2, ReadWrite_t4, ReadWrite_t8\n");
                member_frac = lround(m * 0.9);
                insert_frac = lround(m * 0.05);
                delete_frac = lround(m * 0.05);
                break;

            case 2:
                // file = fopen("C:\\Concurrent Programming\\Assignments\\Lab1\\output\\Case_3.csv","w+");
                // fprintf(file,"Serial, Mutex_t1, Mutex_t2, Mutex_t4, Mutex_t8, ReadWrite_t1, ReadWrite_t2, ReadWrite_t4, ReadWrite_t8\n");
                member_frac = lround(m * 0.5);
                insert_frac = lround(m * 0.25);
                delete_frac = lround(m * 0.25);
                break;

            default:
                break;
        }

        for (int j = 0; j < N; j++)
        {
            serial_runtime = serialExecution(m, member_frac, insert_frac, delete_frac);
            mut_t1_runtime = mutexExecution(1,m, member_frac, insert_frac, delete_frac);
            mut_t2_runtime = mutexExecution(2,m, member_frac, insert_frac, delete_frac);
            mut_t4_runtime = mutexExecution(4,m, member_frac, insert_frac, delete_frac);
            mut_t8_runtime = mutexExecution(8,m, member_frac, insert_frac, delete_frac);
            // rw_t1_runtime = readWriteExecution(m, member_frac, insert_frac, delete_frac, 1);
            // rw_t2_runtime = readWriteExecution(m, member_frac, insert_frac, delete_frac, 2);
            // rw_t4_runtime = readWriteExecution(m, member_frac, insert_frac, delete_frac, 4);
            // rw_t8_runtime = readWriteExecution(m, member_frac, insert_frac, delete_frac, 8);

            printf("Case %d : %f \n %f \n %f\n %f\n %f\n", i,serial_runtime,mut_t1_runtime,mut_t2_runtime,mut_t4_runtime,mut_t8_runtime);
            // fprintf(file,"%lu, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %lu\n",serial_runtime, mut_t1_runtime, mut_t2_runtime, mut_t4_runtime, mut_t8_runtime, rw_t1_runtime,  rw_t2_runtime, rw_t4_runtime, rw_t8_runtime);
        }
        printf("----------------------------- Case %d completed -----------------------------\n", i);
        // fclose(file);
    }
    return 0;
}
