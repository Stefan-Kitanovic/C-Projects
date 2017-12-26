#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IME 20

typedef struct meso_st
{
    char grad[3];
    char meso[MAX_IME];
    float cena;
    struct meso_st *next;

} MESO;

void addNode ( MESO ** root, char grad[2], char meso[MAX_IME], float cena );
FILE * safeOpen ( char name[MAX_IME], char type[MAX_IME] );
void loadList ( MESO ** root, FILE *inputFile );
MESO * najpovoljnije ( MESO * root, FILE *outputFile, char vrsta[MAX_IME]);
void ispis ( MESO * root, FILE *outputFile, char vrsta[MAX_IME] );
void switchNodes ( MESO ** root, int i);
void sort ( MESO ** root );
void freeList ( MESO ** root );
MESO * getNode ( MESO ** root, unsigned int index );

int main( int nargs, char *args[] )
{
    if ( nargs != 4 )
    {
        printf("Pogresno ste pozvali program!\n");
        return 1;
    }

    FILE *inputFile, *outputFile;

    MESO *root;
    root = NULL;

    inputFile = safeOpen( args[2], "r" );
    loadList(&root, inputFile);
    fclose(inputFile);

    outputFile = safeOpen( args[3], "w");
    ispis(root, outputFile, args[1]);

    sort(&root);
    //switchNodes(&root, 0);
    ispis(root, outputFile, args[1]);
    fclose(outputFile);

    freeList(&root);

    return 0;
}


FILE * safeOpen ( char name[MAX_IME], char type[MAX_IME] )
{
    FILE *fileName;

    fileName = fopen (name, type);

    if ( fileName == NULL && strcmp(type, "r") == 0 )
    {
        printf("Neuspesno otvaranje ulazne datoteke!\n");
        exit(1);
    }
    else if ( fileName == NULL && strcmp(type, "w") == 0 )
    {
        printf("Neuspesno kreiranje izlazne datoteke!\n");
        exit(2);
    }

    return fileName;
}

void addNode ( MESO ** root, char grad[3], char meso[MAX_IME], float cena )
{
    MESO *newNode;

    if ( *root == NULL )
    {
        *root = (MESO *)malloc(sizeof(MESO));
        strcpy((*root)->grad, grad);
        strcpy((*root)->meso, meso);
        (*root)->cena = cena;
        (*root)->next = NULL;
        return;
    }

    newNode = (MESO *)malloc(sizeof(MESO));
    strcpy(newNode->grad, grad);
    strcpy(newNode->meso, meso);
    newNode->cena = cena;
    newNode->next = NULL;

    MESO *temp;
    temp = *root;

    while ( temp->next != NULL )
    {
        temp = temp->next;
    }

    temp->next = newNode;
}

void loadList ( MESO ** root, FILE *inputFile )
{
    MESO meso;
    while ( (fscanf(inputFile,"%s %s %f", meso.grad, meso.meso, &meso.cena)) != EOF  )
    {
        addNode(root, meso.grad, meso.meso, meso.cena);
    }
}


MESO * najpovoljnije ( MESO * root, FILE *outputFile, char vrsta[MAX_IME])
{
    MESO *temp;
    MESO *minCena;
    temp = root;
    minCena = NULL;

    while ( temp != NULL )
    {
        if ( strcmp(vrsta, temp->meso) == 0 )
        {
            if ( minCena == NULL )
            {
                minCena = temp;
            }
            else if ( minCena->cena > temp->cena )
            {
                minCena = temp;
            }
        }
        temp = temp->next;
    }
    return minCena;
}

MESO * getNode ( MESO ** root, unsigned int index )
{
    MESO *temp;
    temp = *root;
    int i;

    for ( i = 0; i < index; i++ )
    {
        temp = temp->next;
    }
    return temp;
}

void switchNodes ( MESO ** root, int i)
{
    MESO *temp1;
    MESO *temp2;
    MESO *temp3;
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

    for ( k = 0; k < i-1 ; k++ )
    {
        temp1 = temp1->next;
    }

    temp2 = temp1->next;
    temp3 = temp2->next;

    temp1->next = temp3;
    temp2->next = temp3->next;
    temp3->next = temp2;
}
void sort ( MESO ** root )
{
    MESO *temp;
    temp = *root;
    int nodes = 0;
    while ( temp != NULL )
    {
        nodes++;
        temp = temp->next;
    }

    int i,j;
    for ( i = 0; i < nodes - 1; i++)
    {
        for ( j = 0; j < nodes - i - 1; j++)
        {
            if ( getNode(root, j)->cena > getNode(root, j+1)->cena)
            {
                //printf("\nSwitched:  [%.2f]  and  [%.2f]\n", GetNode(root, i)->cena, GetNode(root, j)->cena);
                switchNodes(root, j );
            }
        }
    }
}

void ispis ( MESO * root, FILE *outputFile, char vrsta[MAX_IME] )
{
    MESO *temp;
    temp = root;
    MESO *minCena;

    minCena = najpovoljnije(root, outputFile, vrsta);

    while ( temp != NULL )
    {
        fprintf(outputFile,"%.2f %s %s\n", temp->cena, temp->grad, temp->meso);
        temp = temp->next;
    }
    if ( minCena == NULL )
    {
        fprintf(outputFile,"Odjebi");
    }
    else
    {
        fprintf(outputFile,"\nNajpovoljnija: \n%.2f %s %s\n\n", minCena->cena, minCena->grad, minCena->meso);
    }
}

void freeList ( MESO ** root )
{
    MESO *temp;

    while ( *root != NULL )
    {
        temp = *root;
        (*root) = (*root)->next;
        free(temp);
    }
}
