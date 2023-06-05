#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

#define ARRSIZE 20

int main(int argc, char **argv)
{
	int myid, size;
	int i;
	int data[ARRSIZE];
	int receive_data[ARRSIZE/4];
	
	
	MPI_Status status;
	//Initialize MPI environment
	MPI_Init(&argc, &argv);
	
	//Get total number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//Get my unique identification among all processes
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	
	
	if (size!=4)
	{
		printf("\n Please use EXACTLY 4 Processes!\n:");
		MPI_Finalize();
		exit(0);
	}
	
	//If root
	if(myid == 0)
	{
	//Initialize data to save value
		for (i=0; i<ARRSIZE;i++)
		{
			data[i]=i;
		}
		//Print the data
		printf("\n Initial data:");
		for(i=0; i<ARRSIZE;i++)
		{
			printf("\t%d", data[i]);
		}
	
	}

	MPI_Scatter(&data,ARRSIZE/4, MPI_INT, &receive_data, ARRSIZE/4, MPI_INT, 0, MPI_COMM_WORLD);

	//Every process works on ARRSIZE/4 of data
	for(i=0; i<ARRSIZE/4; i++)
	{
		receive_data[i] = receive_data[i]*2;
	}	
	
	MPI_Gather(&receive_data,ARRSIZE/4, MPI_INT, &data, ARRSIZE/4, MPI_INT, 0, MPI_COMM_WORLD);

	//If root
	if (myid==0)
	{
		// print the data
		printf("\n Final data:");
		for(i=0; i<ARRSIZE; i++)
		{
			printf("\t%d", data[i]);
		}
		printf("\n\n Program exit!\n");
	
	}
	//End MPI environment
	MPI_Finalize();
}

