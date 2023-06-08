#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

#define VECTORSIZE 10

int main(int argc, char **argv)
{
	int myid, size;
	int i, j, k, sum;
	int *A, *B, *C;
	int *A_1, *C_1;		
	double exe_time;
	struct timeval stop_time, start_time;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	
	if(myid==0)
	{
	//Allocate and initialize the arrays
	A = (int *)malloc(VECTORSIZE*VECTORSIZE*sizeof(int));
	B = (int *)malloc(VECTORSIZE*VECTORSIZE*sizeof(int));
	C = (int *)malloc(VECTORSIZE*VECTORSIZE*sizeof(int));
	
	//Initialize data to some value
	for(i=0;i<VECTORSIZE;i++)
	{
		for(j=0;j<VECTORSIZE;j++)
		{
			A[i*VECTORSIZE+j] = 1;
			B[i*VECTORSIZE+j] = 2;
			C[i*VECTORSIZE+j] = 0;	
		}
	}
	
	//print the data
	printf("\nInitial data: \n");
	printf("\n A matrix:\n");
	for(i=0;i<VECTORSIZE;i++)
	{
		for(j=0;j<VECTORSIZE;j++)
		{
			printf("\t%d ", A[i*VECTORSIZE+j]);	
		}
		printf("\n");
	}
	printf("\n B matrix:\n");
	for(i=0;i<VECTORSIZE;i++)
	{
		for(j=0;j<VECTORSIZE;j++)
		{
			printf("\t%d ", B[i*VECTORSIZE+j]);	
		}
		printf("\n");
	}
	}
		
	A_1 = (int *)malloc((VECTORSIZE*VECTORSIZE)/size*sizeof(int));
	C_1 = (int *)malloc((VECTORSIZE*VECTORSIZE)/size*sizeof(int));
	gettimeofday(&start_time, NULL);
	
 	MPI_Scatter(A ,(VECTORSIZE*VECTORSIZE)/size, MPI_INT, A_1, (VECTORSIZE*VECTORSIZE)/size, MPI_INT, 0, MPI_COMM_WORLD);
	
	MPI_Bcast(B, VECTORSIZE*VECTORSIZE, MPI_INT, 0, MPI_COMM_WORLD);
	
	for(i=0;i<VECTORSIZE*VECTORSIZE;i++)
		printf("%d\m
	for(i=0;i<VECTORSIZE/size;i++)
	{
		for(j=0;j<VECTORSIZE;j++)
		{
			sum = 0;
			for(k=0;k<VECTORSIZE;k++)
			{
				
				sum = sum + A_1[i*VECTORSIZE+k]*B[k*VECTORSIZE+j];	
			}
			C_1[i*VECTORSIZE+j] =  sum;
		}
	}
	
        MPI_Gather(C_1,(VECTORSIZE*VECTORSIZE)/size, MPI_INT, C, (VECTORSIZE*VECTORSIZE)/size, MPI_INT, 0, MPI_COMM_WORLD);
        
        free(A_1);
        free(C_1);
	
	gettimeofday(&stop_time, NULL);	
	exe_time = (stop_time.tv_sec+(stop_time.tv_usec/1000000.0)) - (start_time.tv_sec+(start_time.tv_usec/1000000.0));
	MPI_Finalize();
	if(myid==0)
	{
	//print the data
	printf("\n C matrix:\n");
	for(i=0;i<VECTORSIZE;i++)
	{
		for(j=0;j<VECTORSIZE;j++)
		{
			printf("\t%d ", C[i*VECTORSIZE+j]);	
		}
		printf("\n");
	}
	}
	printf("\n Execution time is = %lf seconds\n", exe_time);
	
	printf("\nProgram exit!\n");
	
	//Free arrays
	free(A); 
	free(B);
	free(C);
}
