#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "linked_list_util.h"
#include "serial_exec.h"

double serialExecution(int total_operations, int member_frac, int insert_frac, int delete_frac)
{
    Node *head = NULL;
    int tot_member_ops = 0;
    int tot_insert_ops = 0;
    int tot_delete_ops = 0;
    int completed_count = 0;

    Populate(&head,1000);

    clock_t start, end;
    double time_taken;

    //Start timer
    start = clock();

    while (completed_count < total_operations){

        int rand_value = rand() % INT_MAX;
        int operation_no = rand() % 3;

        if (operation_no == 0 && tot_insert_ops < insert_frac){
            Insert(rand_value, &head);
            tot_insert_ops++;
            completed_count++;
        }
        else if(operation_no == 1 && tot_member_ops < member_frac){
            Member(rand_value, head);
            tot_member_ops++;
            completed_count++;
        }
        else if(tot_delete_ops < delete_frac){
            Delete(rand_value, &head);
            tot_delete_ops++;
            completed_count++;
        }
    }

    // End time
    end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("The time taken to execute the program is %f seconds\n", time_taken);

    Destroy(head);
    printf("Serial run complete\n");
    return time_taken;

}