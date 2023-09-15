#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "read_write_lock_exec.h"

int main()
{
    double rw_t1_runtime, rw_t2_runtime, rw_t4_runtime, rw_t8_runtime;
    // Number of operations
    int m = 10000;

    // Fractions for each case
    int member_frac = lround(m * 0.99);
    int insert_frac = lround(m * 0.005);
    int delete_frac = lround(m * 0.005);
    rw_t1_runtime = readWriteLockExec(m, member_frac, insert_frac, delete_frac, 1);
    rw_t2_runtime = readWriteLockExec(m, member_frac, insert_frac, delete_frac, 2);
    rw_t4_runtime = readWriteLockExec(m, member_frac, insert_frac, delete_frac, 4);
    rw_t8_runtime = readWriteLockExec(m, member_frac, insert_frac, delete_frac, 8);

    printf("t1: %lf\n", rw_t1_runtime);
    printf("t2: %lf\n", rw_t2_runtime);
    printf("t4: %lf\n", rw_t4_runtime);
    printf("t8: %lf\n", rw_t8_runtime);
}