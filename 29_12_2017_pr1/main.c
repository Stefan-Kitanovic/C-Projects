#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define MAX_SIZE 20+1

typedef struct student_st
{
    char name[MAX_SIZE];
    unsigned int points;
    struct student_st *next;
} STUDENT;

void initializeRoot ( STUDENT ** root );
void addNode ( STUDENT ** root, char name[MAX_SIZE], unsigned int points );
void printNode ( STUDENT *node );
void printList ( STUDENT * root );
void freeList ( STUDENT ** root );

int main()
{
    STUDENT *root;

    initializeRoot(&root);
    addNode(&root, "Dragan", 100);
    printList(root);

    return 0;
}


void initializeRoot ( STUDENT ** root )
{
    *root =(STUDENT *)malloc(sizeof(STUDENT));
     strcpy((*root)->name, "NAME");
     (*root)->points = 0;
     (*root)->next = NULL;
}

void addNode ( STUDENT ** root, char name[MAX_SIZE], unsigned int points )
{
    if ( *root == NULL )
    {
        printf("Lista je prazna\n");
        return;
    }

    STUDENT *newNode;

    newNode = (STUDENT *)malloc(sizeof(STUDENT));
    strcpy(newNode->name, name);
    newNode->points = points;
    newNode->next = NULL;

    STUDENT *temp;
    temp = *root;

    while ( temp->next != NULL )
    {
        temp = temp->next;
    }

    temp->next = newNode;
}

void printNode ( STUDENT *node )
{
    printf("%s %u\n", node->name, node->points);
}

void printList ( STUDENT * root )
{
    STUDENT *temp;
    temp = root;

    while ( temp != NULL )
    {
        printNode(temp);
        temp = temp->next;
    }
}

void freeList ( STUDENT ** root )
{
    STUDENT *temp;

    while ( *root != NULL )
    {
        temp = *root;
        *root = (*root)->next;
        free(temp);
    }
}


