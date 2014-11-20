#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char ** argv){


	FILE *file;
	int x = 0, y = 0, i = 0, j = 0;
	int  **matriz1, **matriz2;
	file = fopen("matriz.txt","r");
	fscanf(file, "%d %d\n", &x, &y);
	matriz1 = (int**)malloc(sizeof(int*)*y);
	matriz2 = (int**)malloc(sizeof(int*)*y);

	for(i = 0; i < x; i++)
	{
		matriz1[i] = (int*)malloc(sizeof(int)*x);
		matriz2[i] = (int*)malloc(sizeof(int)*x);
	}

	i = 0;

	while(feof(file) == 0)
	{
		int aux;
		fscanf(file, "%d", &aux);
		matriz1[j][i] = aux;
		i++;
		if (i%x==0)
		{
			i=0;
			j++;
		}
		if (j==y)
		{
			break;
		}	
	}
	i = 0; j = 0;
	while(feof(file) == 0)
	{
		int aux;
		fscanf(file, "%d", &aux);
		matriz2[j][i] = aux;
		i++;
		if (i%x==0)
		{
			i=0;
			j++;
		}
		if (j==y)
		{
			break;
		}	
	}
	for (i = 0; i < y; i++)
	{
		for (j = 0; j < x; j++)
		{
			printf("%d ", matriz1[i][j]);
		}
		printf("\n");
	}
	puts("");
	for (i = 0; i < y; i++)
	{
		for (j = 0; j < x; j++)
		{
			printf("%d ", matriz2[i][j]);
		}
		printf("\n");
	}

	fclose(file);

	int ierr = MPI_Init(&argc,&argv);
	return 0;
}