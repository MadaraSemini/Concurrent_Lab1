#ifndef SERIAL_EXEC_H
#define SERIAL_EXEC_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>
#include "linked_list_util.h"

unsigned long serialExecution(int total_operations, int member_frac, int insert_frac, int delete_frac);

#endif