//
// Main.c
// Practica4
//
// Created by Beatriz Paulina Garcia Salgado
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ParallelMatrix.h"

int main(int argc, char** argv)
{
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////No cambiar este segmento////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Variables for matrix operations
	long double* A = NULL;
	long double* B = NULL;
	long double* C = NULL;
	long double count;
	int sizeMat = 100;
	int row,col;
	
	//Variables for thread management and time
	int numThreads;
	struct timespec t0, t1;
	double tiempoMedido;
	
	//Allocate matrices
	A = (long double*)malloc(sizeMat * sizeMat * sizeof(long double));
	B = (long double*)malloc(sizeMat * sizeMat * sizeof(long double));
	C = (long double*)malloc(sizeMat * sizeMat * sizeof(long double));
	if(!A || !B || !C)
	{
		printf("Cannot allocate the matrices\n");
		exit(EXIT_FAILURE);
	}
	
	//Set the maximum number of cores as available threads
	numThreads = getNumberOfCPUs();
	printf("Available cores: %d\n",numThreads);
	omp_set_num_threads(numThreads);
	
	//Initialise the matrices
	for(row = 0; row < sizeMat; row++)
	{
		count = 1;
		for(col = 0; col < sizeMat; col++)
		{
			*(A + row * sizeMat + col) = count;
			*(B + row * sizeMat + col) = 2;
			count++;
		}
	}
	
	checkSumAll(&count, A, sizeMat);
	printf("The addition of all components of A is %Lf\n",count);
	
	checkSumAll(&count, B, sizeMat);
	printf("The addition of all components of B is %Lf\n",count);
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//La multiplicacion a realizar es A*B.
	//El maximo debe obtenerse de la matriz A.

	float timeBank[4];

	//Parallel product matrix calc
	if (clock_gettime(CLOCK_REALTIME, &t0) != 0)
	{
		printf("Error calling clock_gettime for t0\n");
		exit(EXIT_FAILURE);
	}
	
	ompParallelMatrixMult(&C, A, B, sizeMat);

	if (clock_gettime(CLOCK_REALTIME, &t1) != 0)
	{
		printf("Error calling clock_gettime for t1\n");
		exit(EXIT_FAILURE);
	}
	
	tiempoMedido = (double)(t1.tv_sec - t0.tv_sec) + ((double)(t1.tv_nsec - t0.tv_nsec) / 1000000000L);
	timeBank[0] = tiempoMedido;

	checkSumAll(&count, C, sizeMat);

	printf("\nTime elapsed in parallel mult: %lf seconds\n", tiempoMedido);
	printf("The addition of all components of the product A x B is %Lf\n",count);


	//Praduct matrix calc
	if (clock_gettime(CLOCK_REALTIME, &t0) != 0)
	{
		printf("Error calling clock_gettime for t0\n");
		exit(EXIT_FAILURE);
	}
	
	matrixMult(&C, A, B, sizeMat);

	if (clock_gettime(CLOCK_REALTIME, &t1) != 0)
	{
		printf("Error calling clock_gettime for t1\n");
		exit(EXIT_FAILURE);
	}
	
	tiempoMedido = (double)(t1.tv_sec - t0.tv_sec) + ((double)(t1.tv_nsec - t0.tv_nsec) / 1000000000L);
	timeBank[1] = tiempoMedido;

	checkSumAll(&count, C, sizeMat);

	printf("\nTime elapsed in mult: %lf seconds\n", tiempoMedido);
	printf("The addition of all components of the product A x B is %Lf\n",count);
	
	//Parallel max value in matrix

	if (clock_gettime(CLOCK_REALTIME, &t0) != 0)
	{
		printf("Error calling clock_gettime for t0\n");
		exit(EXIT_FAILURE);
	}
	
	ompParallelMatrixMax(&count, A, sizeMat);

	if (clock_gettime(CLOCK_REALTIME, &t1) != 0)
	{
		printf("Error calling clock_gettime for t1\n");
		exit(EXIT_FAILURE);
	}
	
	tiempoMedido = (double)(t1.tv_sec - t0.tv_sec) + ((double)(t1.tv_nsec - t0.tv_nsec) / 1000000000L);
	timeBank[2] = tiempoMedido;

	printf("\nTime elapsed in parallel max: %lf seconds\n", tiempoMedido);
	printf("The max value in  A  is %Lf\n",count);


	//Max value in matrix

	if (clock_gettime(CLOCK_REALTIME, &t0) != 0)
	{
		printf("Error calling clock_gettime for t0\n");
		exit(EXIT_FAILURE);
	}
	
	matrixMax(&count, A, sizeMat);

	if (clock_gettime(CLOCK_REALTIME, &t1) != 0)
	{
		printf("Error calling clock_gettime for t1\n");
		exit(EXIT_FAILURE);
	}
	
	tiempoMedido = (double)(t1.tv_sec - t0.tv_sec) + ((double)(t1.tv_nsec - t0.tv_nsec) / 1000000000L);
	timeBank[3] = tiempoMedido;

	printf("\nTime elapsed in max: %lf seconds\n", tiempoMedido);
	printf("The max value in  A  is %Lf\n",count);



	printf("-------------------------------------------------------\n");
	printf("|   Funcion     |    T Paralelo    |     T Normal     |\n");
	printf("-------------------------------------------------------\n");
	printf("| Multipicacion |     %f     |     %f     |\n",timeBank[0], timeBank[1]);
	printf("| Valor maximo  |     %f     |     %f     |\n",timeBank[2], timeBank[3]);
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	return EXIT_SUCCESS;
}
