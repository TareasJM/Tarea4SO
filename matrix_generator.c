#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int random_number(int min_num, int max_num)
{
	int result=0,low_num=0,hi_num=0;
	if(min_num<max_num)
	{
		low_num=min_num;
		hi_num=max_num+1; // this is done to include max_num in output.
	}
	else
	{
		low_num=max_num+1;// this is done to include max_num in output.
		hi_num=min_num;
	}
	result = (rand()%(hi_num-low_num))+low_num;
	return result;
}

int main()
{
	srand(time(0));
	FILE *file;
	char filename[64];
	int matrix_id, rows, i, j, n;

	printf("Ingrese ID de matriz\n");
	scanf("%d", &matrix_id);

	printf("Ingrese tamano:\n");
	scanf("%d", &rows);

	snprintf(filename, sizeof(filename), "matriz%d.txt", matrix_id);
	file = fopen(filename, "w");
	fprintf(file, "%d %d\n\n", rows, rows);
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < rows; j++)
		{
			n = random_number(1, 100);
			if(j == rows-1)
				fprintf(file, "%d\n", n);
			else
				fprintf(file, "%d ", n);
		}
	}
	fprintf(file, "\n");
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < rows; j++)
		{
			n = random_number(1, 100);
			if(j == rows-1)
				fprintf(file, "%d\n", n);
			else
				fprintf(file, "%d ", n);
		}
	}
	fclose(file);
	return 0;
}