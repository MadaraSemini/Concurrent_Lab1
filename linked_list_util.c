#include <stdlib.h>
#include "linked_list_util.h"

// Check a value is a member of the linked list
int Member(int value, struct Node *head_p)
{
    struct Node *current_p = head_p;

    while (current_p != NULL && current_p->data < value)
        current_p = current_p->next;
    if (current_p == NULL || current_p->data > value)
        return 0;
    else
        return 1;
}

// Insert value to the link list
int Insert(int value, struct Node **head_p)
{
    struct Node *current_p = *head_p;
    struct Node *pred_p = NULL;
    struct Node *temp_p;

    while (current_p != NULL && current_p->data < value)
    {
        pred_p = current_p;
        current_p = current_p->next;
    }

    if (current_p == NULL || current_p->data > value)
    {
        temp_p = malloc(sizeof(struct Node));
        temp_p->data = value;
        temp_p->next = current_p;
        if (pred_p == NULL)
            *head_p = temp_p;
        else
            pred_p->next = temp_p;
        return 1;
    }
    else
        return 0;
}

// Delete node
int Delete(int value, struct Node **head_p)
{
    struct Node *current_p = *head_p;
    struct Node *pred_p = NULL;

    while (current_p != NULL && current_p->data < value)
    {
        pred_p = current_p;
        current_p = current_p->next;
    }
    if (current_p != NULL && current_p->data == value)
    {
        if (pred_p == NULL)
        {
            *head_p = current_p->next;
            free(current_p);
        }
        else
        {
            pred_p->next = current_p->next;
            free(current_p);
        }
        return 1;
    }
    else
        return 0;
}

// Function to generate and insert random integers into the linked list
void Populate(struct Node **head, int count)
{
    for (int i = 0; i < count; i++)
    {
        int randomValue = rand() % 65536;
        Insert(randomValue, head);
    }
}