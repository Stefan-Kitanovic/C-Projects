#include <stdio.h>
#include <stdlib.h>

/**
    tip_povratne_vrednosti ime_funkcije( tip_param_1 ime_param_1, tip_param_2 ime_param_2 ...)
    {

    }

    f(x) = x + 10;

    f(20) => 20 + 10;

    f(x,y,u,v) = 10*x + 100*u + v*v - y;

    f(1,2,3,4) = 10*1 + 100*3 + 4*4 - 2

    int SaberiDvaBroja(int x, int y)
    {
        int rezultat;
        rezultat = x + y;
        return rezultat;
    }

    int x = SaberiDvaBroja(10,20);
        //-> int rezultat;
        //-> rezultat = 10 + 20;
        //-> rezultat = 30;
        //-> return 30;
    int x = 30;

*/
int OduzmiDvaBroja(int x, int y)
{
    int rezultat;
    rezultat = x - y;
    return rezultat;
}

int PomnoziDvaBroja(int x, int y)
{
    int rezultat;
    rezultat = x * y;
    return rezultat;
}


int SaberiDvaBroja(int x, int y)
{
        int rezultat;
        rezultat = x + y;
        return rezultat;
}

float PodeliDvaBroja(float x, float y)
{
    if ( y == 0)
    {
        printf("Nije moguce deliti sa nulom");
        return 0;
    }
    else
    {
    float rezultat;
    rezultat = x / y;
    return rezultat;
    }
}

void Line()
{
    printf("\n---------------------------------\n");
}

int main()
{
    int a,b;
    a = 100;
    b = 200;

    Line();

    printf("Rezultat sabiranja je %d", SaberiDvaBroja(a,b));
    Line();

    printf("Rezultat oduzimanja je %d", OduzmiDvaBroja(a,b));
    Line();

    printf("Rezultat mnozenja je %d", PomnoziDvaBroja(a,b));
    Line();

    printf("Rezultat deljenja je %f", PodeliDvaBroja(a,b));

    return 0;
}
