#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define MAX_IME 20+1
#define MAX_PREZIME 20+1

//izvlacenje iz liste (return)

typedef struct student
{
    char ime[MAX_IME];
    char prezime[MAX_PREZIME];
    unsigned int ID;
    struct student *next;
} STUDENT;

void InitializeRoot ( STUDENT ** root );
void AddNode ( STUDENT ** root, char newName[MAX_IME], char newLastName[MAX_PREZIME], unsigned int x);
void AddNodeToBeginning ( STUDENT ** root, char newName[MAX_IME], char newLastName[MAX_PREZIME], unsigned int newID);
void InsertNode ( STUDENT ** root, char newName[MAX_IME], char newLastName[MAX_PREZIME], unsigned int newID, unsigned int index );
STUDENT * ReadNode ( STUDENT * root, unsigned int index );
void PrintNode ( STUDENT * node );
void PrintList ( STUDENT * root );
void FreeList ( STUDENT ** root );
void PrintTable( STUDENT * root );
void DeleteLastNode( STUDENT ** root ); /// brise poslednji noodel
void DeleteFirstNode( STUDENT ** root );
void DeleteNode( STUDENT ** root, unsigned int index );

int main()
{
    STUDENT *root;

    InitializeRoot(&root);
    AddNode(&root, "Gospodin", "tKle", 69);
    AddNode(&root, "Dragan", "Rukavina", 1);
    AddNode(&root, "Stefan", "Kitanovic", 192);
    AddNodeToBeginning(&root, "Luka", "Bobic", 97);
    AddNodeToBeginning(&root, "Nebojsa", "Bobic", 97);
    AddNodeToBeginning(&root, "Marko", "Mackic", 97);
    InsertNode(&root, "Vladimir", "Ivanovic", 5, 3);
    //DeleteNode(&root, 3);
    /*DeleteOneNode(&root);
    DeleteOneNode(&root);
    DeleteOneNode(&root);
    DeleteOneNode(&root);
    DeleteOneNode(&root);
    DeleteOneNode(&root);
    DeleteOneNode(&root);
*/
    //PrintList(root);
   // DeleteFirstNode(&root);
    PrintTable(root);
    printf("\n\n\n");
    PrintNode(ReadNode(root, 3));
    FreeList(&root);

    return 0;
}

STUDENT * ReadNode ( STUDENT * root, unsigned int index )
{
    STUDENT *temp;
    int i;

    temp = root;

    for ( i = 0; i < index; i++ )
    {
        temp = temp->next;
    }

    return temp;
}

void DeleteFirstNode( STUDENT ** root )
{
    STUDENT *temp;

    temp = *root;
    (*root) = (*root)->next;
    free(temp);
}

void DeleteLastNode( STUDENT ** root ) /// brise poslednji noodel
{
    STUDENT *temp1;
    STUDENT *temp2;
    temp1 = *root;

    if ( (*root)->next == NULL)
    {
        free(*root);
        *root = NULL;
        return;
    }

    while ( temp1->next != NULL)
    {
        temp2 = temp1;
        temp1 = temp1->next;
    }

    free(temp1);
    temp2->next = NULL;
}

void DeleteNode( STUDENT ** root, unsigned int index )
{
    STUDENT *newNode;
    STUDENT *temp1;
    STUDENT *temp2;
    int i;
    int nodes;

    for ( temp1 = *root; temp1 != NULL; temp1 = temp1->next )\
    {
        nodes++;
    }

    if ( index > nodes )
    {
        printf("Odjebi\n");
        return;
    }

    temp1 = *root;

    for ( i = 0; i < index-1 ; i++ )
    {
        temp1 = temp1->next;
    }
    temp2 = temp1->next;
    temp1->next = temp1->next->next;
    free(temp2);
}

void InitializeRoot ( STUDENT ** root )
{
    *root = ( STUDENT *)malloc(sizeof(STUDENT));
     strcpy((*root)->ime, "IME");
     strcpy((*root)->prezime, "PREZIME");
    (*root)->ID = 0;
    (*root)->next = NULL;
}

void InsertNode ( STUDENT ** root, char newName[MAX_IME], char newLastName[MAX_PREZIME], unsigned int newID, unsigned int index )
{
    STUDENT *newNode;
    STUDENT *temp;
    int i;
    int nodes;

    for ( temp = *root; temp != NULL; temp = temp->next )
        nodes++;

    if ( index > nodes )
    {
        printf("Odjebi\n");
        return;
    }

    newNode = ( STUDENT * )malloc(sizeof(STUDENT));
    strcpy(newNode->ime, newName);
    strcpy(newNode->prezime, newLastName);
    newNode->ID = newID;
    temp = *root;

    if ( index > nodes )
    {
        printf("Odjebi");
        return;
    }

    for ( i = 0; i < index-1 ; i++ )
    {
        temp = temp->next;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}

void AddNodeToBeginning ( STUDENT ** root, char newName[MAX_IME], char newLastName[MAX_PREZIME], unsigned int newID)
{

    STUDENT *newNode;

    newNode = ( STUDENT * )malloc(sizeof(STUDENT));
    strcpy(newNode->ime, newName);
    strcpy(newNode->prezime, newLastName);
    newNode->ID = newID;
    newNode->next = *root;

    *root = newNode;
}


void AddNode ( STUDENT ** root, char newName[MAX_IME], char newLastName[MAX_PREZIME], unsigned int newID)
{
    if ( *root == NULL )
    {
        printf("Root not initialized.\n");
        return;
    }

    STUDENT *newNode;

    newNode = ( STUDENT * )malloc(sizeof(STUDENT));
    strcpy(newNode -> ime, newName);
    strcpy(newNode -> prezime, newLastName);
    newNode -> ID = newID;
    newNode -> next = NULL;

    STUDENT *temp;
    temp = *root;

    while ( (temp)->next != NULL )
    {
        (temp) = (temp) -> next;
    }
    (temp)->next = newNode;
}

void PrintNode ( STUDENT *node )
{
    printf("%-20s|%-20s|%-5u"
           , node->ime, node->prezime, node->ID);
}

void PrintList ( STUDENT * root )
{
    STUDENT *temp;
    temp = root->next;

    if ( temp == NULL )
    {
        printf("List is empty!\n");
        return;
    }

    while ( temp != NULL )
    {
        PrintNode(temp);
        printf("\n");
        temp = temp->next;
    }
}

void PrintTable( STUDENT * root )
{
    if ( root == NULL)
    {
        printf("Lista prazna!");
        return;
    }

    int i;
    int brojCrtica = printf("%-20s|%-20s|%-5s\n", root->ime, root->prezime, "ID");
    for ( i = 0;    i < brojCrtica; printf("-"), i++);
    printf("\n");
    STUDENT * temp;
    temp = root->next;

    //Line();

    int brojac = 0;
    //char maxIme[MAX_IME];
    //char maxPrezime[MAX_PREZIME];

    //strcpy( maxIme, temp->ime );
    //strcpy( maxPrezime, temp->prezime );

    while(temp != NULL)
    {
        PrintNode(temp);
        printf("\n");
/*
        if ( strlen(maxIme) < strlen(temp->ime) )
        {
            strcpy( maxIme, temp->ime );
        }

        if ( strlen(maxPrezime) < strlen(temp->prezime) )
        {
            strcpy( maxPrezime, temp->prezime );
        }*/
        temp = temp->next;
      //  brojac++;
    }
    //Line();
    printf("\n");
    //printf("%-20s|%-20s|%-5s\n","Najduze ime je:","Najduze prezime je:","Broj studenata");
    //printf("%-20s|%-20s|%-5d\n", maxIme, maxPrezime, brojac);

}

void FreeList ( STUDENT ** root )
{
    STUDENT *temp;

    while ( *root != NULL )
    {
        temp = *root;
        (*root) = (*root)->next;
        free(temp);
    }
}
