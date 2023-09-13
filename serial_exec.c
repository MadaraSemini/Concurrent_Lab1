#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "linked_list_util.h"
#include "serial_exec.h"

double serialExecution(int total_operations, int member_frac, int insert_frac, int delete_frac)
{
    Node *head = NULL;
    int member_ops_count = 0;
    int insert_ops_count = 0;
    int delete_ops_count = 0;
    int completed_count = 0;

    Populate(&head,1000);

    clock_t start, end;
    double time_taken;

    // struct timeval start;
    // struct timeval end;

    // Start time
    // gettimeofday(&start, NULL);
    start = clock();

    while (completed_count < total_operations){

        int rand_value = rand() % INT_MAX;
        int operation_no = rand() % 3;

        if (operation_no == 0 && insert_ops_count < insert_frac){
            Insert(rand_value, &head);
            insert_ops_count++;
            completed_count++;
        }
        else if(operation_no == 1 && member_ops_count < member_frac){
            Member(rand_value, head);
            member_ops_count++;
            completed_count++;
        }
        else if(delete_ops_count < delete_frac){
            Delete(rand_value, &head);
            delete_ops_count++;
            completed_count++;
        }
    }

    // End time
    // gettimeofday(&end, NULL);
    // unsigned long time_taken = time_diff(&start, &end);
    end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("The time taken to execute the program is %f seconds\n", time_taken);

    Destroy(head);
    printf("Serial run complete\n");
    return time_taken;

}