#include "linkedList.h"

Block* init_node(int size)
{
    Block* newNode = (Block*)sbrk(sizeof(Block*));
    if (!newNode) {
        printf("Error has been occured during memory allocation for Node");
        return NULL;
    }
    newNode->size = size;
    newNode->next = NULL;
    return newNode;
}

void append(Block** head, int size)
{
    Block *newNode = init_node(size);
    if (!newNode) return;

    if (*head == NULL) { // there are any elements in linked list
        *head = newNode;
        return;
    }

    Block* temp = *head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void print_node(Block* head)
{
    Block* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->size);
        temp = temp->next;
    }
    printf("NULL\n");
}