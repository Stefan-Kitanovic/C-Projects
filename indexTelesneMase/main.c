#include <stdio.h>
#include <stdlib.h>
#define MAX_KARAKTERA 20+1
#define MAX_PACIJENATA 20


typedef struct pacijent_st
{
    char ime[MAX_KARAKTERA];
    char prezime[MAX_KARAKTERA];
    unsigned int masa;
    float visina;
} PACIJENT;

typedef struct analiza_st
{
    char ime[MAX_KARAKTERA];
    char prezime[MAX_KARAKTERA];
    float BMI;
    char dijagnoza[MAX_KARAKTERA];
} ANALIZA;

int main(int nargs, char *args[])
{
    PACIJENT pacijent[MAX_PACIJENATA];
    ANALIZA analiza[MAX_PACIJENATA];
    FILE *inputFile, *outputFile;
    int brojPacijenta = 0;

    if ( nargs != 3 )
    {
        printf("Neuspesno pokretanje programa\nProgram se pokrece u formatu ./[ime programa] [ulazna datoteka] [izlazna datoteka]");
        return 1;
    }

    inputFile = fopen (args[1], "r");
    if ( inputFile == NULL )
    {
        printf("Neuspesno otvaranje ulazne datoteke.\n");
        return 1;
    }

        while ( fscanf(inputFile,"%s %s %d %f",
                       pacijent[brojPacijenta].ime,
                       pacijent[brojPacijenta].prezime,
                       &pacijent[brojPacijenta].masa,
                       &pacijent[brojPacijenta].visina) != EOF )
        {
            brojPacijenta++;
        }
    fclose(inputFile);

    outputFile = fopen (args[2], "w");
    if ( outputFile == NULL )
    {
        printf("Neuspesno kreiranje izlazne datoteke.\n");
        return 1;
    }

    int i;
    for( i = 0; i < brojPacijenta; i++ )
    {

        strcpy( analiza[i].ime, pacijent[i].ime );
        strcpy( analiza[i].prezime, pacijent[i].prezime);
        analiza[i].BMI = (float)((float)pacijent[i].masa / (pacijent[i].visina * pacijent[i].visina));

        if ( analiza[i].BMI < 18.5 )
        {
            strcpy(analiza[i].dijagnoza,"Pothranjenost");
        }
        else if ( analiza[i].BMI >= 18.5 && analiza[i].BMI <25 )
        {
            strcpy(analiza[i].dijagnoza, "Idealna tezina");
        }
        else if ( analiza[i].BMI >= 25 && analiza[i].BMI < 30 )
        {
            strcpy(analiza[i].dijagnoza, "Prekomerna tezina");
        }
        else
        {
            strcpy(analiza[i].dijagnoza, "Gojaznost - RIP †");
        }
    }

    for ( i = 0; i < brojPacijenta; i++ )
    {
        fprintf(outputFile,"%s %s %.2f %s\n",
                analiza[i].ime,
                analiza[i].prezime,
                analiza[i].BMI,
                analiza[i].dijagnoza);
    }

    fclose(outputFile);

    return 0;
}
