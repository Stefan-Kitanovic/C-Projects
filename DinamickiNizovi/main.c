#include <stdio.h>
#include <stdlib.h>

typedef struct cvor
{
    int podatak;
    struct cvor *sledeci;
}CVOR;

void PrintCvor(CVOR * c);
void InitializeRoot(CVOR ** root);
void AddNode(CVOR ** root, int x);
void PrintEntireList(CVOR * root);
void FreeEntireList(CVOR ** root);
int CountAllNodes(CVOR * root);


int main()
{
    CVOR * koren;

    InitializeRoot(&koren);

    koren->sledeci = (CVOR *)malloc(sizeof(CVOR));
    koren->sledeci->sledeci = NULL;
    koren->sledeci->podatak = 100;

    koren->sledeci->sledeci = (CVOR *)malloc(sizeof(CVOR));
    koren->sledeci->sledeci->sledeci = NULL;
    koren->sledeci->sledeci->podatak = 200;

    PrintEntireList(koren);
    printf("Evo koliko clanova lista ima: %d\n", CountAllNodes(koren));
    printf("\n-----------------------\n");
    AddNode(&koren, 666);

    PrintEntireList(koren);
    printf("Evo koliko clanova lista ima: %d\n", CountAllNodes(koren));
    printf("\n-----------------------\n");
    AddNode(&koren, 1666);

    AddNode(&koren, 6666);

    AddNode(&koren, 100000);
    PrintEntireList(koren);

    printf("Evo koliko clanova lista ima: %d\n", CountAllNodes(koren));

    FreeEntireList(&koren);
    PrintEntireList(koren);

    printf("Evo koliko clanova lista ima: %d\n", CountAllNodes(koren));

    return 0;
}

void PrintCvor(CVOR * c)
{
    printf("Podatak u cvoru: [%d]", c->podatak);
}

void PrintEntireList(CVOR * root)
{
    CVOR *temp;
    temp = root;

    if ( temp == NULL)
    {
        printf("List is empty!\n");
        return;
    }

    while( temp != NULL)
    {
        PrintCvor(temp);
        printf("\n");

        ///temp (trenutni cvor) preuzima adresu sledeceg cvora od sebe
        ///temp (trenutni cvor) postaje sledeci cvor
        ///u jednom trenutku ce sledeci od trenutnog biti NULL
        ///sto znaci da ce trenutni uzeti vrednost NULL
        ///i po uslovu while petlje STATI ( temp != NULL )
        temp = temp->sledeci;
    }
}

void InitializeRoot(CVOR ** root)
{
    *root = (CVOR *)malloc(sizeof(CVOR));
    (*root)->podatak = 0;
    (*root)->sledeci = NULL;
}

void AddNode(CVOR ** root, int x)
{
    if ( root == NULL)
    {
        printf("Root not initialized, please use InitializeRoot(rootNode) to init!\n");
        return;
    }

    CVOR *newCvor;
    newCvor = (CVOR *)malloc(sizeof(CVOR));
    newCvor->podatak = x;
    newCvor->sledeci = NULL;

    CVOR **temp;
    *temp = *root;

    while ( (*temp)->sledeci != NULL )
    {
        (*temp) = (*temp)->sledeci;
    }

    (*temp)->sledeci = newCvor;
}

void FreeEntireList(CVOR ** root)
{
    CVOR *temp;

    while ( *root != NULL)
    {
        temp = *root;
        (*root) = (*root)->sledeci;
        free(temp);
    }

    *root = NULL;
}

int CountAllNodes(CVOR * root) ///cvoren
{
    CVOR *temp;
    int brojac = 0;
    ///     inicijalizacija;     provera tacnosti uslova za nastavak rada petlje;        iteracija
    for ( temp = root;  temp != NULL;   temp = temp->sledeci, brojac++);

    return brojac;
}

/**
    CVOR * koren;

    koren = (CVOR *)malloc(sizeof(CVOR));

    koren->podatak = 100;

    PrintCvor(koren);

    free(koren);
*/

/**
MN

void PromeniVrednostPokazivaca(int **p)
/// p = x
/// p = 1234
/// p = 100000
{

    ///p -> adresa nekog pokazivaca
    ///*p -> vrednost koja se nalazi na adresi tog nekog pokazivaca ( adresa neke promenljive );
    *p = 10000;
}

void PromeniVrednostPokNaPok(int ***ppp)
{
    *ppp = 1412341234;
}

    int x;
    int *xp;
    int **xpp;

    x = 100;        ///x == 100, &x == 1234;
    xp = &x;        ///xp == 666, &xp == 4321, *xp == 100
    xpp = &xp;      ///xpp == 4321, &xpp == 200, *xpp == 1234, **xpp == 100
    **xpp = 5000;   ///x == 5000;
    *xpp = 666;


void PromeniVrednostPromenljive(int *x)
{
    *x = 200;
}

main...
int *x;

    x = 1234;
    printf("Adresa (vrednost) na koju pokazuje x je: %d\n", x);
    PromeniVrednostPokazivaca(&x);
    printf("Adresa (vrednost) na koju pokazuje x je: %d\n", x);

*/
