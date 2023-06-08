#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<sys/time.h>

#define N 10

int main(int argc, char **argv)
{	
        int size, myid;	
	int i, j;
	int *A;
	int *A_1;
	double exe_time;
	struct timeval stop_time, start_time;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	
	if(myid==0){
		A = (int *) malloc(N*sizeof(int));
		
		for(i=0;i<N;i++)
		{
		    A[i] = i;
		}
		printf("\n Initial Array :\n");
		for(i=0;i<N;i++)
		{
		    printf(" %d", A[i]);
		}
	}
	
	gettimeofday(&start_time, NULL);
	A_1 = (int *) malloc(N/size*sizeof(int));
	MPI_Scatter(A ,N/size, MPI_INT, A_1, N/size, MPI_INT, 0, MPI_COMM_WORLD);
	
	for(i=0;i<N/size;i++)
	{
		A_1[i] = A_1[i]*A_1[i];
	}
	
        MPI_Gather(A_1,N/size, MPI_INT, A, N/size, MPI_INT, 0, MPI_COMM_WORLD);
	free(A_1);
	gettimeofday(&stop_time, NULL);	
	exe_time = (stop_time.tv_sec+(stop_time.tv_usec/1000000.0)) - (start_time.tv_sec+(start_time.tv_usec/1000000.0));
	
      	MPI_Finalize();
	
	if(myid == 0){
		printf("\n Final Array :\n");
		for(i=0;i<N;i++)
		{
		    printf(" %d", A[i]);
		}
		printf("\n");
	}
	free(A);
}

