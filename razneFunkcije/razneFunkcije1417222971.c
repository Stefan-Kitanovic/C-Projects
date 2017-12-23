#include <stdio.h>
#include <string.h>

//razne funkcije

#define MAX_CLANOVA 100

/*
	Ako je opadajuce isto sto i 1 onda se niz sortira u opadajucem redosledu  u suprotnom u rastucem.
*/
void SortirajNiz(int n, int niz[MAX_CLANOVA], short opadajuce)
{
	int i,j;
	
	for ( i = 0;	i < n-1;	i++)
	{
		for ( j = i + 1;	j < n;	j++)
		{
			if(opadajuce)
			{
				if ( niz[i] < niz[j])
				{
					int temp = niz[i];
					niz[i] = niz[j];
					niz[j] = temp;
				}			
			}
			else
			{
				if ( niz[i] > niz[j])
				{
					int temp = niz[i];
					niz[i] = niz[j];
					niz[j] = temp;
				}
			}
		}
	}
}

void Linija()
{
	printf("\n===================================\n");
}

void IspisiNiz(int niz[MAX_CLANOVA], int n)
{
	int i;
	for ( i =0;	i < n;	i++)
	{
		printf("%d ", niz[i]);
	}
	printf("\n");
}

int GetMinFromArray(int arr[MAX_CLANOVA], int n)
{
	int min = arr[0];
	int i;
	
	for ( i = 1;	i < n;	i++)
	{
		if (arr[i] < min)
		{
			min = arr[i];
		}
	} 
	
	return min;
}

int GetMaxFromArray(int arr[MAX_CLANOVA], int n)
{
	int max = arr[0];
	int i;
	
	for ( i = 1;	i < n;	i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	} 
	
	return max;
}

int GetMinOrMax(int arr[MAX_CLANOVA], int n, int min)
{
	if ( min )
	{
		return GetMinFromArray(arr,n);
	}
	else
	{
		return GetMaxFromArray(arr,n);
	}
}

int SumirajPrvihNClanova(int arr[MAX_CLANOVA],int n)
{
	int i;
	int sum = 0;
	for ( i = 0;	i < n;	i++)
	{
		sum += arr[i];
	}
	
	return sum;
}

float ArrayAvg(int arr[MAX_CLANOVA], int n)
{
	//return ((float)sumirajPrvihNClanova(arr,n)) / ((float)n);
	
	float mean = SumirajPrvihNClanova(arr,n);
	mean = mean / ((float)n);
	return mean;
}

void FlipArray(int arr[MAX_CLANOVA], int n)
{
	int i;
	int j;
	
	for ( i = 0, j = n - 1 ; i < j;	i++, j--)
	{
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
	
	
}

typedef struct mala
{
	int data;
} MALA;

void CreateMatrixFromArray(int arr[MAX_CLANOVA], int matrix[MAX_CLANOVA][MAX_CLANOVA], int matrixDims)
{
	int row, col;
	
	for ( row = 0;	row < matrixDims;	row++)
	{
		for ( col = 0;	col < matrixDims;	col++)
		{
			matrix[row][col] = arr[row * matrixDims + col];
		}
	}
	
}

void PrintMatrix(int matrica[MAX_CLANOVA][MAX_CLANOVA], int dim)
{
	int row,col;
	for ( row = 0;	row < dim;	row++)
	{
		for ( col = 0;	col < dim;	col++)
		{
			printf("%d ", matrica[row][col]);
		}
		printf("\n");
	}
}

int main()
{
	char str0[MAX_CLANOVA] = "U nesto SE_Uda4r4t1 m0RA!\0";
	char str1[MAX_CLANOVA];
	char strCatRes[MAX_CLANOVA];
	
	
	
	/*IspisiNiz(nizBrojeva, 10);
	int nizBrojeva[] = {3,4,5,7,8,-100,3,2,-20,15,17,7,7,7,23,10050,1,100,2,4,-100};
	int matrica[MAX_CLANOVA][MAX_CLANOVA];
	int sum;
	Linija();
	SortirajNiz(nizBrojeva, 10, 1);
	IspisiNiz(nizBrojeva, 10);

	int minOrMax = GetMinOrMax(nizBrojeva, 15, 1 );
	printf("Minimalni clan od prvih 15 clanova je : %d\n", minOrMax);
	minOrMax = GetMinOrMax(nizBrojeva, 10, 0);
	printf("Maximalni clan od prvih 15 clanova je : %d\n", minOrMax);
	
	sum = SumirajPrvihNClanova(nizBrojeva, 3);
	IspisiNiz(nizBrojeva,3);
	printf("%d <-- Suma prvih %d clanova\n", sum, 3);
	
	IspisiNiz(nizBrojeva,12);
	IspisiNiz(nizBrojeva, 15);
	FlipArray(nizBrojeva,15);
	IspisiNiz(nizBrojeva, 15);
	
	IspisiNiz(nizBrojeva, 16);
	CreateMatrixFromArray(nizBrojeva, matrica, 4);
	PrintMatrix(matrica, 4);		
	
	strcpy( char destination[], char source[]);
	kopira sadrzaj iz source u destination
	strcpy(str1, str0);
	
	printf("%s\n%s\n", str0, str1);
	printf("%d <-- duzina stringa str0\n", strlen(str0));
	
	printf("%s\n", str0);
	
	strcmp(str0, str1) -> vraca 0 ako su isti, vraca poz broj ako je str0 duzi, vraca neg broj ako je str1 duzi
	
	
	
	printf("%d <-- ?? %s || %s\n", strcmp(str0,str1), str0, str1);
	*/
	MALA *milica;
	MALA milicaNePok;
		
	milicaNePok.data = 100;
	milica = &milicaNePok;
	
	milica->data = 12340;
	
	printf("%d <-- \n", milicaNePok.data);
	
	return 0;	
}


