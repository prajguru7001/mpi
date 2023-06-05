#include<stdio.h>
#include<mpi.h>

int main(int argc, char **argv)
{
	int myid, size;
	int sum;
	
	MPI_Status status;
	//Initialize MPI environment
	MPI_Init(&argc, &argv);
	
	//Get total number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//Get my unique identification among all processes
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	
	 sum = 100;
	
	MPI_Reduce(&myid, &sum, 1,MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	
	//if(myid==0)
	{
		printf("\n sum = %d\n",sum);
	}
	
	MPI_Finalize();
}

