#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INDEX 10+1
#define MAX_IME 20+1
#define MAX_PREZIME 20+1

typedef struct student_st
{
    char index[MAX_INDEX];
    char ime[MAX_IME];
    char prezime[MAX_PREZIME];
    unsigned int poeni;
    struct student_st *next;

    unsigned int parsedNumber;
    unsigned int parsedYear;
} STUDENT;


FILE *safeOpen ( char name[MAX_IME], char type[3] );
void addNode ( STUDENT ** root, char index[MAX_INDEX], char ime[MAX_IME], char prezime[MAX_PREZIME], unsigned int poeni );
void loadList ( STUDENT ** root, FILE *inputFile );
STUDENT * getNode ( STUDENT ** root, unsigned int index );
void switchNodes ( STUDENT ** root, int i );
void parseIndexes ( STUDENT ** root );
void sortList ( STUDENT ** root );
void printSorted ( STUDENT * root, FILE *outputFile );
void printList ( STUDENT * root );

int main( int nargs, char *args[] )
{
    if ( nargs != 3 )
    {
        printf("Pogresno ste pozvali program!\n");
        return 1;
    }

    STUDENT * root;
    root = NULL;

    FILE *inputFile, *outputFile;

    inputFile = safeOpen (args[1], "r");
    loadList(&root, inputFile);
    fclose(inputFile);

    outputFile = safeOpen ("sortirani_studenti.txt", "w");
    parseIndexes(&root);
    sortList(&root);
    printList(root);
    //printSorted(root, outputFile);
    fclose(outputFile);


    return 0;
}

FILE *safeOpen ( char name[MAX_IME], char type[3] )
{
    FILE *filePointer;

    filePointer = fopen (name, type );

    if ( filePointer == NULL && strcmp(type, "r") == 0 )
    {
        printf("Neuspesno otvaranje ulazne datoteke!\n");
        exit(1);
    }
    else if ( filePointer == NULL && strcmp(type, "w") == 0 )
    {
        printf("Neuspesno kreiranje izlazne datoteke!\n");
        exit(2);
    }

    return filePointer;
}

void addNode ( STUDENT ** root, char index[MAX_INDEX], char ime[MAX_IME], char prezime[MAX_PREZIME], unsigned int poeni )
{
    STUDENT *newNode;

    if ( *root == NULL )
    {
        *root = (STUDENT *)malloc(sizeof(STUDENT));
        strcpy((*root)->index, index);
        strcpy((*root)->ime, ime);
        strcpy((*root)->prezime, prezime);
        (*root)->poeni = poeni;
        (*root)->next = NULL;
        return;
    }

    newNode = (STUDENT *)malloc(sizeof(STUDENT));
    strcpy(newNode->index, index);
    strcpy(newNode->ime, ime);
    strcpy(newNode->prezime, prezime);
    newNode->poeni = poeni;
    newNode->next = NULL;

    STUDENT *temp;
    temp = *root;

    while ( temp->next != NULL )
    {
        temp = temp->next;
    }
    temp->next = newNode;
}

void loadList ( STUDENT ** root, FILE *inputFile )
{
    STUDENT student;

    while ( (fscanf(inputFile,"%s %s %s %d", student.index, student.ime, student.prezime, &student.poeni)) != EOF)
    {
        addNode(root, student.index, student.ime, student.prezime, student.poeni);
    }
}

STUDENT * getNode ( STUDENT ** root, unsigned int index )
{
    STUDENT *temp;
    temp = *root;
    int i;

    for ( i = 0; i < index; i++ )
    {
        temp = temp->next;
    }
    return temp;
}

void switchNodes ( STUDENT ** root, int i )
{
    STUDENT *temp1;
    STUDENT *temp2;
    STUDENT *temp3;
    temp1 = *root;

    if ( i == 0 )
    {
        temp1 = temp1->next;
        (*root)->next = temp1->next;
        temp1->next = *root;
        *root = temp1;
        return;
    }

    int k;

    for ( k = 0; k < i-1; k++ )
    {
        temp1 = temp1->next;
    }

    temp2 = temp1->next;
    temp3 = temp2->next;

    temp1->next = temp3;
    temp2->next = temp3->next;
    temp3->next = temp2;
}

void parseIndexes ( STUDENT ** root )
{
    STUDENT *temp;
    temp = *root;

    int i,j;

    while ( temp != NULL )
    {
        char parsedNumber[MAX_INDEX];
        char parsedYear[MAX_INDEX];
        for ( i = 2, j = 0; temp->index[i] != '/'; i++, j++ )
        {
            parsedNumber[j] = temp->index[i];
        }
        parsedNumber[j] = '\0';

        for ( i += 1, j = 0; temp->index[i] != '\0'; i++, j++ )
        {
            parsedYear[j] = temp->index[i];
        }
        parsedYear[j] = '\0';

        temp->parsedNumber = atoi(parsedNumber);
        temp->parsedYear = atoi (parsedYear);

        temp = temp->next;
    }
}

void sortList ( STUDENT ** root )
{
    STUDENT *temp;
    temp = *root;
    int nodes = 0;

    while ( temp != NULL )
    {
        nodes++;
        temp = temp->next;
    }

    int i,j;
    for ( i = 0; i < nodes - 1; i++ )
    {
        for ( j = 0; j < nodes - i - 1; j++)
        {
            if ( getNode(root, j)->parsedNumber < getNode(root, j+1)->parsedNumber );
            {
                switchNodes(root, j);
            }
        }
    }
}

void printSorted ( STUDENT * root, FILE *outputFile )
{
    STUDENT *temp;
    temp = root;

    while ( temp != NULL )
    {
        fprintf(outputFile,"%s %s %s %d\n", temp->index, temp->ime, temp->prezime, temp->poeni );
        temp = temp->next;
    }
}

void printList ( STUDENT * root )
{
    STUDENT *temp;
    temp = root;

    while ( temp != NULL )
    {
        printf("RA %u - %u %s %s\n", temp->parsedNumber, temp->parsedYear, temp->ime, temp->prezime);
        temp = temp->next;
    }
}
