#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "serial_exec.h"
#include "read_write_lock_exec.h"
#include "mutex.h"

int main()
{
    double serial, readWriteArr[4], mutex[4];
    double cases[3][3] = {{0.99, 0.005, 0.005}, {0.9, 0.05, 0.05}, {0.5, 0.25, 0.25}};
    char fileNames[3][5] = {"1.csv", "2.csv", "3.csv"};
    int sample_count = 350;
    int m = 10000;

    int memberOpCount;
    int insertOpCount;
    int deleteOpCount;

    FILE *file;

    char filePath[50] = "./output/Case";
    printf(filePath);
    char filePathAddition[] = "1.csv";
    file = fopen(strcat(filePath, filePathAddition), "w+");

    for (int i = 0; i < 3; i++)
    {
        // file = fopen(strcat(filePath, fileNames[i]), "w+");
        fprintf(file, "Serial, Mutex_t1, Mutex_t2, Mutex_t4, Mutex_t8, ReadWrite_t1, ReadWrite_t2, ReadWrite_t4, ReadWrite_t8\n");
        memberOpCount = lround(m * cases[i][0]);
        insertOpCount = lround(m * cases[i][1]);
        deleteOpCount = lround(m * cases[i][2]);
    }

    for (int execCount = 0; execCount < sample_count; execCount++)
    {
        readWriteArr[0] = readWriteLockExec(1, m, memberOpCount, insertOpCount, deleteOpCount);
        readWriteArr[1] = readWriteLockExec(2, m, memberOpCount, insertOpCount, deleteOpCount);
        readWriteArr[2] = readWriteLockExec(4, m, memberOpCount, insertOpCount, deleteOpCount);
        readWriteArr[3] = readWriteLockExec(8, m, memberOpCount, insertOpCount, deleteOpCount);

        fprintf(file, "%lf, %lf, %lf, %lf\n", readWriteArr[0], readWriteArr[1], readWriteArr[2], readWriteArr[3]);
    }

    // fprintf(file, "1,2,4,8\n");
    // int member_frac = lround(m * 0.99);
    // int insert_frac = lround(m * 0.005);
    // int delete_frac = lround(m * 0.005);
    // readWriteArr[0] = readWriteLockExec(1, m, member_frac, insert_frac, delete_frac);
    // readWriteArr[1] = readWriteLockExec(2, m, member_frac, insert_frac, delete_frac);
    // readWriteArr[2] = readWriteLockExec(4, m, member_frac, insert_frac, delete_frac);
    // readWriteArr[3] = readWriteLockExec(8, m, member_frac, insert_frac, delete_frac);

    // printf("t1: %lf\n", readWriteArr[0]);
    // printf("t2: %lf\n", readWriteArr[1]);
    // printf("t4: %lf\n", readWriteArr[2]);
    // printf("t8: %lf\n", readWriteArr[3]);

    // fprintf(file, "%lf, %lf, %lf, %lf\n", readWriteArr[0], readWriteArr[1], readWriteArr[2], readWriteArr[3]);
    return 0;
}