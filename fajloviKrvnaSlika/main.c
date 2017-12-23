#include <stdio.h>
#include <stdlib.h>

#define MAX_KARAKTERA 20+1
#define MAX_PACIJENATA 20

typedef struct pacijent_st
{
    char ime[MAX_KARAKTERA];
    char prezime[MAX_KARAKTERA];
    float holesterol;
    unsigned int krvni_pritisak;
    float secer;
} PACIJENT;

typedef struct analiza_st
{
    char upozorenje;
    char ime[MAX_KARAKTERA];
    char prezime[MAX_KARAKTERA];
} ANALIZA;

int main( int nargs, char *args[] )
{
    PACIJENT pacijent[MAX_PACIJENATA];
    ANALIZA analiza[MAX_PACIJENATA];

    FILE *inputFile, *outputFile;
    inputFile = fopen (args[2],"r");
    outputFile = fopen (args[3], "w");

    if ( inputFile == NULL )
    {
        printf("Neuspesno otvaranje datoteke");
    }

    if ( outputFile == NULL )
    {
        printf("Neuspesno kreiranje datoteke");
    }

    if ( nargs != 4 )
    {
        printf("\nNeispravan poziv programa\nProgram se poziva u formatu ./[ime programa] [tip analize][ime ulazne datoteke] [ime izlazne datoteke]\n");
        return 1;
    }

    int i;
    int brojPacijenta = 0;
    while ( fscanf(inputFile,
                   "%s %s %f %d %f",
                   pacijent[brojPacijenta].ime,
                   pacijent[brojPacijenta].prezime,
                   &pacijent[brojPacijenta].holesterol,
                   &pacijent[brojPacijenta].krvni_pritisak,
                   &pacijent[brojPacijenta].secer) != EOF )
    {
        brojPacijenta++;
    }

    if ( strcmp( args[1], "holesterol") == 0 )
    {
        for ( i = 0; i < brojPacijenta; i++ )
        {
            if ( pacijent[i].holesterol < 5.2 )
            {
                analiza[i].upozorenje = '-';
            }
            else
            {
                analiza[i].upozorenje = '†';
            }
            strcpy( analiza[i].ime, pacijent[i].ime);
            strcpy( analiza[i].prezime, pacijent[i].prezime);
        }
    }
    else if ( strcmp( args[1], "pritisak") == 0 )
    {
        for ( i = 0; i < brojPacijenta; i++ )
        {
            if ( pacijent[i].krvni_pritisak < 120 && pacijent[i].krvni_pritisak >= 90 )
            {
                analiza[i].upozorenje = '-';
            }
            else
            {
                analiza[i].upozorenje = '†';
            }
            strcpy( analiza[i].ime, pacijent[i].ime);
            strcpy( analiza[i].prezime, pacijent[i].prezime);
        }
    }
    else if ( strcmp( args[1], "secer") == 0 )
    {
        for ( i = 0; i < brojPacijenta; i++ )
        {
            if ( pacijent[i].secer < 5.6 && pacijent[i].secer >= 3.9 )
            {
                analiza[i].upozorenje = '-';
            }
            else
            {
                analiza[i].upozorenje = '†';
            }
            strcpy( analiza[i].ime, pacijent[i].ime);
            strcpy( analiza[i].prezime, pacijent[i].prezime);
        }
    }
    else
    {
        printf("Unesite ispravan tip analize(holesterol, pritisak ili secer)\n");
        return 1;
    }
    for ( i = 0; i < brojPacijenta; i++ )
    {
        fprintf( outputFile, "%c %s %s\n",
                analiza[i].upozorenje,
                analiza[i].ime,
                analiza[i].prezime);
    }


    fclose(inputFile);
    return 0;
}
