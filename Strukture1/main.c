#include <stdio.h>
#include <stdlib.h>

typedef struct kompleksni_broj
{
    float r;
    float i;
} K_BROJ;

void IspisiKompleksiBroj(K_BROJ kbroj)
{
    printf("%.2f ", kbroj.r);

    if( kbroj.i < 0)
    {
        printf("%.2fi", kbroj.i);
    }
    else if ( kbroj.i > 0)
    {
        printf("+ %.2fi",kbroj.i);
    }
    printf("\n");
}

K_BROJ Konjuguj(K_BROJ x)
{
    x.i *= -1;

    return x;
}

K_BROJ SaberiDvaKompleksasa(K_BROJ x, K_BROJ y)
{
    K_BROJ kbroj;
    kbroj.i = x.i + y.i;
    kbroj.r = x.r + y.r;

    return kbroj;
}

float Mnozenje(K_BROJ x)
{
    K_BROJ konjugovani = Konjuguj(x);

    float rezultat;
    rezultat = konjugovani.i *konjugovani.i + konjugovani.r * konjugovani.r;

    return rezultat;
}



int main()
{
    K_BROJ kompleksniBrojevi[10];
    K_BROJ temp;

    int i,j;
    for( i = 0; i < 10; i++)
    {
        kompleksniBrojevi[i].i = i + 10 * 2 - 16;
        kompleksniBrojevi[i].r = i - 23 + 4*i*i;
    }

    for ( i = 0; i < 10; i++)
    {
        IspisiKompleksiBroj(kompleksniBrojevi[i]);
    }

    for ( i = 0; i < 10; i++ )
    {
        for ( j = 1; j < 10; j++)
        {
            if ( kompleksniBrojevi[i].r < kompleksniBrojevi[j].r )
            {
                temp = kompleksniBrojevi[i];
                kompleksniBrojevi[i] = kompleksniBrojevi[j];
                kompleksniBrojevi[j] = temp;
            }
        }
    }

    printf("Sortiran\n");

    for ( i = 0; i < 10; i++)
    {
        IspisiKompleksiBroj(kompleksniBrojevi[i]);
    }


    return 0;
}
