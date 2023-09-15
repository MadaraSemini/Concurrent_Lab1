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
    char fileNames[3][18] = {"./output/Case1.csv", "./output/Case2.csv", "./output/Case3.csv"};
    int sample_count = 100;
    int m = 10000;

    int memberOpCount;
    int insertOpCount;
    int deleteOpCount;

    FILE *file;

    // char filePath[50] = "./output/Case";
    // printf(filePath);
    // char filePathAddition[] = "1.csv";
    // file = fopen(strcat(filePath, filePathAddition), "w+");

    for (int i = 0; i < 3; i++)
    {
        if (i == 0)
        {
            file = fopen("./output/Case1.csv", "w+");
        }
        else if (i == 1)
        {
            file = fopen("./output/Case2.csv", "w+");
        }
        else
        {
            file = fopen("./output/Case3.csv", "w+");
        }

        fprintf(file, "Serial, 1_Thread_ReadWriteLock, 2_Thread_ReadWriteLock, 4_Thread_ReadWriteLock, 8_Thread_ReadWriteLock, 1_Thread_Mutex, 2_Thread_Mutex, 4_Thread_Mutex, 8_Thread_Mutex\n");
        memberOpCount = lround(m * cases[i][0]);
        insertOpCount = lround(m * cases[i][1]);
        deleteOpCount = lround(m * cases[i][2]);

        for (int execCount = 0; execCount < sample_count; execCount++)
        {
            // serial execution
            serial = serialExecution(m, memberOpCount, insertOpCount, deleteOpCount);
            // read-write-lock execution
            readWriteArr[0] = readWriteLockExec(1, m, memberOpCount, insertOpCount, deleteOpCount);
            readWriteArr[1] = readWriteLockExec(2, m, memberOpCount, insertOpCount, deleteOpCount);
            readWriteArr[2] = readWriteLockExec(4, m, memberOpCount, insertOpCount, deleteOpCount);
            readWriteArr[3] = readWriteLockExec(8, m, memberOpCount, insertOpCount, deleteOpCount);
            // mutex execution
            mutex[0] = mutexExecution(1, m, memberOpCount, insertOpCount, deleteOpCount);
            mutex[1] = mutexExecution(2, m, memberOpCount, insertOpCount, deleteOpCount);
            mutex[2] = mutexExecution(4, m, memberOpCount, insertOpCount, deleteOpCount);
            mutex[3] = mutexExecution(8, m, memberOpCount, insertOpCount, deleteOpCount);

            fprintf(file, "%lf, %lf, %lf, %lf,%lf, %lf, %lf, %lf, %lf\n", serial, readWriteArr[0], readWriteArr[1], readWriteArr[2], readWriteArr[3], mutex[0], mutex[1], mutex[2], mutex[3]);
        }
    }
    return 0;
}