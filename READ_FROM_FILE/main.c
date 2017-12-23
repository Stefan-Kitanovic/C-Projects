#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IME 20+1
#define MAX_PREZIME 20+1
#define MAX_STUDENATA 200
#define MAX_BR_INDEKSA 20+1
#define MAX_FILENAME 256

/// ./zadatak studemti.txt output.txt 35
/// preko_35_poena.txt

struct student
{
    unsigned int broj_indeksa;
    char ime[MAX_IME];
    char prezime[MAX_PREZIME];
    unsigned int broj_poena;
};

void PrintStudent(struct student Student)
{
    printf("Ime: %s\nPrezime: %s\nBroj Bodova: %u\nBroj indeksa: %u\n",
        Student.ime,
        Student.prezime,
        Student.broj_poena,
        Student.broj_indeksa
    );
}

int main(int nargs, char * args[])
{
    if ( nargs != 4)
    {
        printf("Potreban broj argumenata je 4!!!\n");
        return 1;
    }

    FILE *inputFile, *outputFile, *outputFilePoints,*outputFileDuzStud;
    char outputFilePointsName[MAX_FILENAME] = "preko_";
    struct student niz_studenata[MAX_STUDENATA];
    int broj_studenata = 0;

    int i,j;

    inputFile = fopen(args[1], "r"); ///

    if ( inputFile == NULL)
    {
        printf("Cannot open file: %s\n", args[1]);
        return 1;
    }
    printf("Successfully opened file: %s\n", args[1]);

    char br_indeksa[MAX_BR_INDEKSA];

    while ( fscanf( inputFile ,"%s %s %s %d", br_indeksa,
        niz_studenata[broj_studenata].ime ,
        niz_studenata[broj_studenata].prezime,
        &niz_studenata[broj_studenata].broj_poena) != EOF )
    {
        char iseceniBrojIndeksa[MAX_BR_INDEKSA];
        int k,j;
        for ( k = 2, j = 0; br_indeksa[k] != '/'; k++, j++)
        {
            iseceniBrojIndeksa[j] = br_indeksa[k];
        }
        iseceniBrojIndeksa[j] = '\0';

        niz_studenata[broj_studenata].broj_indeksa = atoi(iseceniBrojIndeksa);

        broj_studenata++;
    }

    fclose(inputFile);

    for ( i = 0;    i < broj_studenata - 1; i++)
    {
        for ( j = i + 1;    j < broj_studenata; j++)
        {
            if ( niz_studenata[i].broj_indeksa < niz_studenata[j].broj_indeksa)
            {
                struct student temp = niz_studenata[i];
                niz_studenata[i] = niz_studenata[j];
                niz_studenata[j] = temp;
            }
        }
    }

    outputFile = fopen(args[2], "w");
    if ( outputFile == NULL )
    {
        printf("Unable to create file %s\n", args[2]);
        return 1;
    }

    for ( i = 0;    i < broj_studenata; i++)
    {
        fprintf(outputFile,
            "%u %s %s %u\n",
            niz_studenata[i].broj_indeksa,
            niz_studenata[i].ime,
            niz_studenata[i].prezime,
            niz_studenata[i].broj_poena);
    }
    fclose(outputFile);

    struct student brCharNajduze;
    struct student brCharNajkrace;

    brCharNajduze = niz_studenata[0];
    brCharNajkrace = niz_studenata[0];

    for ( i = 1;    i < broj_studenata; i++)
    {
        if ( strlen(niz_studenata[i].prezime) > strlen(brCharNajduze.prezime))
        {
            brCharNajduze = niz_studenata[i];
        }

        if ( strlen(niz_studenata[i].prezime) < strlen(brCharNajkrace.prezime))
        {
            brCharNajkrace = niz_studenata[i];
        }
    }

    printf("Najkrace prezime: ");
    PrintStudent(brCharNajkrace);
    printf("\n====================================\n");

    printf("Najdruze prezime: ");
    PrintStudent(brCharNajduze);
    printf("\n====================================\n");
    sprintf(outputFilePointsName, "preko_%s_poena.txt", args[3]);
    int prekoBodova = atoi(args[3]);

    outputFilePoints = fopen(outputFilePointsName, "w");
    if(outputFilePoints == NULL)
    {
        printf("Cannot create file %s\n", outputFilePointsName);
        return 1;
    }
    for ( i = 0;    i < broj_studenata; i++)
    {
        if ( niz_studenata[i].broj_poena > prekoBodova )
        {
            fprintf(outputFilePoints, "%d %s %s %d\n",
                niz_studenata[i].broj_poena,
                niz_studenata[i].ime,
                niz_studenata[i].prezime,
                niz_studenata[i].broj_indeksa);
        }
    }
    fclose(outputFilePoints);

    outputFileDuzStud = fopen("izlaz.txt" ,"w");
    if(outputFileDuzStud == NULL)
    {
        printf("Cannot open this file");
        return 1;
    }

    float prosek = 0;
    for(i=0;i<broj_studenata;i++)
    {
        prosek+=strlen(niz_studenata[i].ime);
    }

    fprintf(outputFileDuzStud,"%2.f",prosek/broj_studenata);

    fclose(outputFileDuzStud);


    /**
    struct student
    {
        unsigned int broj_indeksa;
        char ime[MAX_IME];
        char prezime[MAX_PREZIME];
        unsigned int broj_poena;
    };
    */

    return 0;
}
