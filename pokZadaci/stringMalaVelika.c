#include<stdio.h>

int main()
{
    char str[] = "MaLa sLOva ce biTI velika, a VeLiKa mala.\0";
    char *ps;

    int razmak = 'a' - 'A';

    for ( ps = str; *ps != '\0'; ps++ )
    {
        if ( *ps >= 'a' && *ps <= 'z' )
        {
            *ps -= razmak;
        }
        else if ( *ps >= 'A' && *ps <= 'Z')
        {
            *ps += razmak;
        }
    }

    printf("%s\n", str);


    return 0;
}
