#include<stdio.h>
#include<mpi.h>

int main(int argc, char **argv)
{
	int myid, size;
	int sum;
	
	
	if(myid == 0)
	{
		sum = 100;
	}
	else
	{
		sum = 101;
	}
	
	MPI_Status status;
	//Initialize MPI environment
	MPI_Init(&argc, &argv);
	
	//Get total number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//Get my unique identification among all processes
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	
	
	MPI_Bcast( &sum, 1,MPI_INT, 0, MPI_COMM_WORLD);
	
	if (myid==0)
	{
		printf("\n sum = %d\n",sum);
	}
	
	MPI_Finalize();
}

