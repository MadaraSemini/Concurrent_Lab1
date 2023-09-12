#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct Node* head_p = NULL;
pthread_mutex_t mutex;

// Define a structure for a node
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

//Check a value is a member of the linked list
int member(int value, struct Node* head_p) {
    struct Node* current_p = head_p;

    while (current_p != NULL && current_p->data < value)
    {
        current_p = current_p->next;
    }

    if(current_p == NULL || current_p->data >value) {
        return 0;
    } else {
        return 1;
    }
    
}

//Insert value to the link list
int insert(int value, struct Node** head_p) {
    struct Node* current_p = *head_p;
    struct Node* pred_p = NULL;
    struct Node* temp_p;

    while (current_p !=NULL && current_p->data <value) {
        pred_p = current_p;
        current_p = current_p->next;
    }

    if(current_p == NULL || current_p->data>value) {
        temp_p =malloc(sizeof(struct Node));
        temp_p->data =value;
        temp_p->next = current_p;
        if(pred_p == NULL)
            *head_p =temp_p;
        else
            pred_p->next = temp_p;
        return 1;
    } else {
        return 0;
    }   
}

//Delete node
int delete(int value, struct Node** head_p) {
   struct Node* current_p = *head_p;
   struct Node* pred_p = NULL;

   while (current_p != NULL && current_p->data < value)
   {
    pred_p = current_p;
    current_p =current_p->next;
   }
   if(current_p != NULL && current_p->data ==value) {
    if(pred_p ==NULL){
        *head_p =current_p->next;
        free(current_p);
    } else {
        pred_p->next =current_p->next;
        free(current_p);
    }
    return 1;
   } else {
    return 0;
   }
}

// Function to display the linked list
void displayList(struct Node* head_p) {
    struct Node* current_p = head_p;
    while (current_p != NULL) {
        printf("%d -> ", current_p->data);
        current_p = current_p->next;
    }
    printf("NULL\n");
}

int main(int argc, char* argv[]) {
    clock_t start, end;
    double time_taken;

    start = clock();

    long thread_count;
    pthread_t* thread_handle;

    thread_count= strtol(argv[1],NULL,10);
    thread_handle = malloc(thread_count*sizeof(pthread_t));

    head_p =createNode(6);
    insert(2,&head_p);
    printf("Linked List: ");
    displayList(head_p);



    end = clock();

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("The time taken to execute the program is %f seconds\n", time_taken);
    return 0;
}
