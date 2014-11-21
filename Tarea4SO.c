#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#define data_tag 123

int main(int argc, char ** argv){

	// Declaración de variables y fork
	MPI_Status status;
	int id_process, root_process = 0, ierr;
	clock_t t;
	ierr = MPI_Init(&argc,&argv);
	ierr = MPI_Comm_rank(MPI_COMM_WORLD, &id_process);
	int  **matriz1, **matriz2;

	// Proceso de la maquina en que se ejecuta el programa
	if(id_process == root_process)
	{	
		// comienza la medición de tiempo para el programa
		t = clock();
		// Inicialización de variables
		FILE *input,*output;
		int x = 0, y = 0, i = 0, j = 0, aux;
		input = fopen("/media/sf_Tarea4SO/matriz2.txt","r");  /*Columna, Fila*/
		fscanf(input, "%d %d\n\n", &y, &x);
		matriz1 = (int**)malloc(sizeof(int*)*y);
		matriz2 = (int**)malloc(sizeof(int*)*y);
		ierr = MPI_Send(&y, 1 , MPI_INT, 1, data_tag, MPI_COMM_WORLD); // Envia número de 
		ierr = MPI_Send(&x, 1 , MPI_INT, 1, data_tag, MPI_COMM_WORLD); // Filas y Columnas

		// Pide memoria para las matrices
		for(i = 0; i < y ; i++)
		{
			matriz1[i] = (int*)malloc(sizeof(int)*x);
			matriz2[i] = (int*)malloc(sizeof(int)*x);
		}
		i = 0;

		// Lee la primera matriz
		while(feof(input) == 0)
		{
			fscanf(input, "%d", &aux);
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

		// Lee linea en blanco
		fscanf(input, "\n");

		// Lee la segunda matriz
		while(feof(input) == 0)
		{
			fscanf(input, "%d", &aux);
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
		// Ciera el archivo
		fclose(input);

		// Envia las Filas superiores de la primera Matriz
		for(i = 0; i< y/2; i++)
		{
			for(j = 0; j < x; j++)
			{
				ierr = MPI_Send(&matriz1[i][j],1,MPI_INT,1, 2014, MPI_COMM_WORLD);

			}
		}

		// Envia las Filas superiores de la segunda Matriz
		for(i = 0; i< y/2; i++)
		{
			for(j = 0; j < x; j++)
			{
				ierr = MPI_Send(&matriz2[i][j],1,MPI_INT,1, 2014, MPI_COMM_WORLD);
			}

		}

		// Suma las Filas inferiores de ambas Matrices
		for(i = y/2; i< y; i++)
		{
			for(j = 0; j < x; j++)
			{
				matriz1[i][j] = matriz1[i][j] + matriz2[i][j];
			}
		}

		//  Recive y agrega el resultado de la suma de filas superiores
		for(i = y/2; i< y; i++)
		{
			for(j = 0; j < x; j++)
			{
				ierr = MPI_Recv( &matriz1[i][j], 1, MPI_INT, 1, data_tag, MPI_COMM_WORLD, &status);
			}
		}

		// Abre archivo para escritura
		output = fopen("/media/sf_Tarea4SO/output.txt","w");
		// Escribe dimensión de la matriz
		fprintf(output, "%d %d\n",x,y);
		// Escribe la matriz resultante
		for (i = 0; i < y; i++)
		{
			for (j = 0; j < x; j++)
			{
				printf("%d ", matriz1[i][j]);
				fprintf(output,"%d ", matriz1[i][j]);

			}
			printf("\n");
			fprintf(output,"\n");
		}
		// Cierra el archivo
		fclose(output);
		// Termina el tiempo de ejecución
		t = clock()-t;
		// Imprime el tiempo
		printf("\nTiempo de ejecucion: %f (s) \n",(double)t/CLOCKS_PER_SEC);

	}
	else
	{	
		// Inicialización de variables
		int x,y,i,j, aux;
		ierr = MPI_Recv( &x, 1, MPI_INT, 0, data_tag, MPI_COMM_WORLD, &status);
		ierr = MPI_Recv( &y, 1, MPI_INT, 0, data_tag, MPI_COMM_WORLD, &status);
		
		// Pide memoria para la matriz
		matriz1 = (int**)malloc(sizeof(int*)*y/2);
		for(i = 0; i < y/2 ; i++)
		{
			matriz1[i] = (int*)malloc(sizeof(int)*x);
		}

		i = 0;

		// Recive las filas de la primera matriz
		for(i = 0; i< y/2 ; i++)
		{
			for(j = 0; j < x; j++)
			{
				ierr = MPI_Recv( &matriz1[i][j], 1, MPI_INT, 0, data_tag, MPI_COMM_WORLD, &status);
			}

		}

		// Recive las filas de la segunda matriz y las suma
		for(i = 0 ; i< y/2 ; i++)
		{
			for(j = 0; j < x; j++)
			{
				ierr = MPI_Recv( &aux, 1, MPI_INT, 0, data_tag, MPI_COMM_WORLD, &status);
				matriz1[i][j] = matriz1[i][j] + aux;
			}

		}

		// Envía el resultado de las filas sumadas
		for(i = 0; i< y/2; i++)
		{
			for(j = 0; j < x; j++)
			{
				ierr = MPI_Send(&matriz1[i][j],1,MPI_INT,0, 2014, MPI_COMM_WORLD);
			}
		}

	}

	ierr = MPI_Finalize();
	return 0;
}