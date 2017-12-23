#include<stdio.h>

int main()
{
    int arr[6] = { 3, 0, -2, 123, -5, 1};

    int *pa, *pa2, temp;

    for ( pa = arr; pa < arr+5; pa++)
    {
        for ( pa2 = pa+1; pa2 < arr+5; pa2++ )
        {
            if ( *pa > *pa2 )
            {
            temp = *pa;
            *pa = *pa2;
            *pa2 = temp;
            }
        }
    }

    int i;
    for ( pa = arr; pa < arr+5; *pa++ )
    {
        printf("%d ", *pa);
    }

    return 0;
}
