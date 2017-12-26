#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IME 10+1
#define MAX_ZANR 8+1
#define MAX_PLATFORMA 8+1

typedef struct igra_st
{
    char ime[MAX_IME];
    char zanr[MAX_ZANR];
    char platforma[MAX_PLATFORMA];
    float cena;
    struct igra_st *next;
} IGRA;

FILE * safeOpen ( char name[MAX_IME], char type[2] );
void addNode ( IGRA ** root, char ime[MAX_IME], char zanr[MAX_ZANR], char platforma[MAX_PLATFORMA], float cena );
void loadList ( IGRA ** root, FILE * inputFile );
IGRA * najpovoljnija ( IGRA * root, char zanr[MAX_ZANR], char platforma[MAX_PLATFORMA] );
void ispis ( IGRA * root, FILE *outputFile, char zanr[MAX_ZANR], char platforma[MAX_PLATFORMA] );
void freeList ( IGRA ** root );

int main( int nargs, char *args[] )
{
    if ( nargs != 5 )
    {
        printf("Pogresno ste pozvali program!\n");
        return 1;
    }

    IGRA *root;
    root = NULL;

    FILE *inputFile, *outputFile;

    inputFile = safeOpen (args[3], "r");
    loadList(&root, inputFile);
    fclose(inputFile);

    outputFile = safeOpen (args[4], "w");
    ispis(root, outputFile, args[2], args[1] );
    fclose(outputFile);

    freeList(&root);

    return 0;
}

FILE * safeOpen ( char name[MAX_IME], char type[2] )
{
    FILE * filePointer;

    filePointer = fopen (name, type);

    if ( filePointer == NULL && strcmp(type, "r") == 0 )
    {
        printf("Neuspesno otvaranje ulazne datoteke!\n");
        exit(1);
    }
    if ( filePointer == NULL && strcmp(type,"w") == 0 )
    {
        printf("Neuspesno kreiranje izlazne datoteke!\n");
        exit(2);
    }

    return filePointer;
}

void addNode ( IGRA ** root, char ime[MAX_IME], char zanr[MAX_ZANR], char platforma[MAX_PLATFORMA], float cena )
{
    IGRA *newNode;

    if ( *root == NULL )
    {
        *root = (IGRA *)malloc(sizeof(IGRA));
        strcpy((*root)->ime, ime);
        strcpy((*root)->zanr, zanr);
        strcpy((*root)->platforma, platforma);
        (*root)->cena = cena;
        (*root)->next = NULL;
        return;
    }

    newNode = (IGRA *)malloc(sizeof(IGRA));
    strcpy(newNode->ime, ime);
    strcpy(newNode->zanr, zanr);
    strcpy(newNode->platforma, platforma);
    newNode->cena = cena;
    newNode->next = NULL;

    IGRA *temp;
    temp = *root;

    while ( temp->next != NULL )
    {
        temp = temp->next;
    }
    temp->next = newNode;
}

void loadList ( IGRA ** root, FILE * inputFile )
{
    IGRA igra;
    while( (fscanf(inputFile,"%s %s %s %f", igra.ime, igra.zanr, igra.platforma, &igra.cena )) != EOF )
    {
        if ( igra.cena < 0 )
        {
            printf("Igra ne moze da ima negativnu cenu! (%s %s %s)\n", igra.ime, igra.zanr, igra.platforma);
            continue;
        }
        addNode(root, igra.ime, igra.zanr, igra.platforma, igra.cena );
    }
}

IGRA * najpovoljnija ( IGRA * root, char zanr[MAX_ZANR], char platforma[MAX_PLATFORMA] )
{
    IGRA *temp;
    IGRA *minCena;
    temp = root;
    minCena = NULL;

    while ( temp != NULL )
    {
        if ( strcmp(zanr, temp->zanr) == 0 && strcmp(platforma, temp->platforma) == 0 )
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

void ispis ( IGRA * root, FILE *outputFile, char zanr[MAX_ZANR], char platforma[MAX_PLATFORMA] )
{
    IGRA *temp;
    temp = root;
    IGRA *minCena = najpovoljnija(root, zanr, platforma);

    while ( temp != NULL )
    {
        fprintf(outputFile, "%-10s %-8s %-8s %5.2f\n", temp->ime, temp->zanr, temp->platforma, temp->cena );
        temp = temp->next;
    }
    if ( minCena == NULL )
    {
        fprintf(outputFile,"\nZa %s platformu ne postoje %s igre!\n", platforma, zanr );
    }
    else
    {
        fprintf(outputFile,"\nNajpovoljnija %s igra za %s platformu je :\n%s %5.2f\n", minCena->zanr, minCena->platforma, minCena->ime, minCena->cena );
    }
}

void freeList ( IGRA ** root )
{
    IGRA *temp;

    while ( *root != NULL )
    {
        temp = *root;
        (*root) = (*root)->next;
        free(temp);
    }
}
