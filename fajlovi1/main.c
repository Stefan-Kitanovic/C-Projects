#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KARAKTERA 20+1
#define MAX_PAKETA 30
/**
    Naziv provajdera (jedna reè, do 20 karaktera)
    Naziv paketa (jedna reè, do 20 karaktera)
    Meseèna pretplata (prirodan broj)
    Broj besplatnih poruka ukljuèenih u pretplatu (prirodan broj)
    Cena po poruci nakon potrošenih besplatnih poruka (realan broj)
*/

typedef struct paket_st{
    char naziv_provajdera[MAX_KARAKTERA];
    char naziv_paketa[MAX_KARAKTERA];
    unsigned int mesecna_pretplata;
    unsigned int broj_besplatnih_poruka;
    float cena_po_poruci;
} PAKET;

typedef struct cena_st{
    char naziv_provajdera[MAX_KARAKTERA];
    char naziv_paketa[MAX_KARAKTERA];
    float ukupna_cena_paketa;
} CENA_ST;

void Line()
{
    printf("--------------------------------\n");
}

FILE * OpenAFile (const char *fileName, int shouldOpen);
void PrintPacket(PAKET p);

int main()
{
    PAKET Paketi[MAX_PAKETA];
    CENA_ST Cene[MAX_PAKETA];
    int brojPaketa = 0;
    char inputFileName[] = "paketi.txt";
    char outputFileName[] = "rezultati.txt";
    FILE *inputFile, *outputFile;

    int brojPoruka = 237;

    inputFile = fopen("paketi.txt", "r");

    if ( inputFile == NULL)
    {
        printf("...");
        return 1;
    }

    while ( fscanf(inputFile,
                   "%s %s %d %d %f",
                   Paketi[brojPaketa].naziv_provajdera,
                   Paketi[brojPaketa].naziv_paketa,
                   &Paketi[brojPaketa].mesecna_pretplata,
                   &Paketi[brojPaketa].broj_besplatnih_poruka,
                   &Paketi[brojPaketa].cena_po_poruci) != EOF)
    {
        ///PrintPacket(Paketi[brojPaketa]);
        ///printf("\n------------------\n");
        brojPaketa++;
    }

    int i;

    for ( i = 0;     i < brojPaketa;    i++)
    {
        float cenaPaketa = ((int)(brojPoruka - Paketi[i].broj_besplatnih_poruka)) *
                            Paketi[i].cena_po_poruci +
                            Paketi[i].mesecna_pretplata;
        Cene[i].ukupna_cena_paketa = cenaPaketa;

        strcpy( Cene[i].naziv_paketa, Paketi[i].naziv_paketa);
        strcpy( Cene[i].naziv_provajdera, Paketi[i].naziv_provajdera);
    }

    fclose(inputFile);

    outputFile = fopen(outputFileName, "w");
    if( outputFile == NULL)
    {
        printf("Neuspesno kreiranje [%s] datoteke!\n", outputFileName);
        return 1;
    }

    for ( i =0; i < brojPaketa; i++)
    {
        fprintf(outputFile, "%7.2f %s %s\n",
                Cene[i].ukupna_cena_paketa,
                Cene[i].naziv_provajdera,
                Cene[i].naziv_paketa);
    }

    fclose(outputFile);
    return 0;
}

int main1()
{
    char inputFileName[] = "paketi.txt";
    char outputFileName[] = "rezultat.txt";
    FILE *inputFile, *outputFile;

    inputFile = OpenAFile (inputFileName, 1);
    /// r - read    - ovo je za citanje datoteke
    /// w - write   - je za uspisivanje podataka
    /// a - append  - nalepljuje sadrzaj u datoteku
    /// r+
    /// w+
    /// a+

    if ( inputFile == NULL )
    {
        printf("Nije uspesno otvaranje datoteke %s\n", inputFileName);
        return 1;
    }

    printf("[%s] je uspesno otvorena za citanje\n", inputFileName);

    char rec1[MAX_KARAKTERA];
    char rec2[MAX_KARAKTERA];
    int br1;
    int br2;
    float rbr1;

    while ( fscanf(inputFile, "%s %s %d %d %f", rec1, rec2, &br1, &br2, &rbr1) != EOF )
    {
        printf(">>%s\n>>%s\n>>%d\n>>%d\n>>%.2f\n", rec1, rec2, br1, br2, rbr1);
        Line();
    }

    fclose(inputFile);
    return 0;
}

FILE * OpenAFile(const char *fileName, int shouldRead)              // ne mora const
{
    FILE *f;
    if ( shouldRead )
    {
        f = fopen(fileName, "r");
    }
    else
    {
        f = fopen(fileName, "w");
    }

    return f;
}

void PrintPacket(PAKET p)
{
    printf("P: %d %.2f %d %s %s",
           p.broj_besplatnih_poruka,
           p.cena_po_poruci,
           p.mesecna_pretplata,
           p.naziv_paketa,
           p.naziv_provajdera);
}

