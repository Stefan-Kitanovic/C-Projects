#include <stdio.h>
#include <stdlib.h>

#define MAX_IME 20+1
#define MAX_PREZIME 20+1

typedef struct student_t_distribution
{
    int broj_indeksa;
    double prosek;
    struct StudenT *next;

} STUDENT;

void PrintStudent (STUDENT s)
{
    printf("Student: prosek = %.2lf, broj indeksa = %d", s.prosek, s.broj_indeksa);
}

int main()
{
    /*
    STUDENT *neki_student;
    STUDENT kitanovic;

    kitanovic.broj_indeksa = 192;
    kitanovic.prosek = 9.0;

    PrintStudent(kitanovic); printf("\n");

    neki_student = &kitanovic;

    printf("%d <-- broj indeksa \n", neki_student->broj_indeksa);
    */

    STUDENT *neki_student;
    STUDENT *neki_student_2;

    neki_student = (STUDENT *) malloc(sizeof(STUDENT));
    neki_student_2 = (STUDENT *) malloc(sizeof(STUDENT));
    neki_student_2->broj_indeksa = 120;
    neki_student_2->prosek = 6.75;

    neki_student->broj_indeksa = 100;
    neki_student -> prosek = 10.0;
    //neki student->next = (STUDENT *) malloc(sizeof(STUDENT));
    neki_student->next = neki_student_2;

    PrintStudent(*(neki_student));
    printf("\n");
    PrintStudent(*(neki_student->next));

    free (neki_student);
    free (neki_student->next);
    return 0;
}
