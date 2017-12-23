#include <stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){

    char nasString[] = "Danas jelep dan.\0";

    char *cp;

    printf("%s", nasString);

    for ( cp = nasString; (*cp) != '\0'; cp++)
    {
        if ( (*cp) == ' ')
        {
            (*cp = '-');
        }
    }
    printf("%s\n", nasString);

    char *vladaKraj;
    char *vladaPocetak;

    for ( vladaKraj = nasString; (*vladaKraj) != '\0'; vladaKraj++ );
        vladaKraj--;

    for ( vladaPocetak = nasString; vladaPocetak < vladaKraj; vladaPocetak++, vladaKraj++)
    {
        char zamena = *vladaPocetak;
        (*vladaPocetak) = (*vladaKraj);
        (*vladaKraj) = zamena;
    }

    printf("%s\n", nasString);

    return 0;
}

