#include <stdio.h>
#include <stdlib.h>

#define __ printf("==============")

int main()
{

    int sh;
    int *shp;
    int **shp;

    sh = 100;
    shp = &sh;
    shpp = &shp;

    __
    printf("Adresa promenljive sh: [%d], vrednost promenljive je [%d] je [%d]\n", &sh, sh);
    __
    printf("Adresa promenljive shp: [%d], vrednost promenljive shp je [%d] -> [%d]\n", &shp, shp, &sh);
    printf("Vrednost na adresi [%d] je [%d]\n", shp,*shp);
    __
    printf("Adresa promenljive shpp: [%d], vrednost promenljive shpp je [%d] -> [%d]\n", &shpp, shpp, &shp);
    printf("Vrednost na adresi [%d] je [%d]\n", shpp, *shpp);
    printf("Vrednost na adresi [%d] je [%d]\n", *shpp, **shpp);

    __
    int arr[5] = {50,60,70,100,120};

    int i;
    for ( i = 0; i < 5; i++)
    {
        printf("%d -> %d\n", arr+1, *(arr+1));
        *(arr+i) = 666;
    }

    __
    for ( i = 0; i < 5; i++ )
    {
        printf("%d -> %d\n", arr+1, *(arr+1));
    }

    return 0;
}
