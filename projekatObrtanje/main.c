#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 20

typedef struct string_st
{
    char karakter;
    struct string_st *next;
} STRING;

void push ( STRING ** root, char karakter );
char pop ( STRING ** root );
void obrni ( STRING ** root, char string[MAX_SIZE] );

int main()
{
    STRING *root;
    root = NULL;
    char string[MAX_SIZE];
    strcpy(string, "Gospodin tKle");
    obrni(&root, string);

    return 0;
}

void push ( STRING ** root, char karakter )
{
    STRING *newNode;

    if ( (*root) == NULL )
    {
        *root = (STRING *)malloc(sizeof(STRING));
        (*root)->karakter = karakter;
        (*root)->next = NULL;
        return;
    }

    newNode = (STRING *)malloc(sizeof(STRING));
    newNode->karakter = karakter;
    newNode->next = *root;
    *root = newNode;
}

char pop ( STRING ** root )
{
    STRING *temp;
    temp = *root;

    (*root) = (*root)->next;
    char karakter = temp->karakter;
    free(temp);

    return karakter;
}

void obrni ( STRING ** root, char string[MAX_SIZE] )
{
    int i;
    for ( i = 0; string[i] != '\0'; i++ )
    {
        push(root, string[i]);
    }
    for ( i = 0; string[i] != '\0'; i++ )
    {
        printf("%c", pop(root));
    }
}
