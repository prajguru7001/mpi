#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

#define ARRSIZE 1000

int main(int argc, char **argv)
{
	int myid, size;
	int i;
	int a[ARRSIZE];
	int b[ARRSIZE];
	int c[ARRSIZE];
	MPI_Status status;
	//Initialize MPI environment
	MPI_Init(&argc, &argv);
	
	//Get total number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//Get my unique identification among all processes
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	
	int receive_data_a[ARRSIZE/size];
	int receive_data_b[ARRSIZE/size];
	int receive_data_c[ARRSIZE/size];
	
	//If root
	if(myid == 0)
	{
	int a[ARRSIZE];
	int b[ARRSIZE];
	int c[ARRSIZE];
	//Initialize data to save value
		for (i=0; i<ARRSIZE;i++)
		{
			a[i]=i;
			b[i]=i;
			c[i]=0;
		}
		//Print the data
		printf("\n Initial data:\n");
		for(i=0; i<ARRSIZE;i++)
		{
			printf("%d\t%d\n", a[i], b[i]);
		}
	
	}
	
	MPI_Scatter(&a,ARRSIZE/size, MPI_INT, &receive_data_a, ARRSIZE/size, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(&b,ARRSIZE/size, MPI_INT, &receive_data_b, ARRSIZE/size, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(&c,ARRSIZE/size, MPI_INT, &receive_data_c, ARRSIZE/size, MPI_INT, 0, MPI_COMM_WORLD);
	
	for(i=0; i<ARRSIZE/size; i++)
	{
		receive_data_c[i] = receive_data_a[i]+receive_data_b[i];
	}
	
	MPI_Gather(&receive_data_c,ARRSIZE/size, MPI_INT, &c, ARRSIZE/size, MPI_INT, 0, MPI_COMM_WORLD);
	
	//If root
	if (myid==0)
	{
		// print the data
		printf("\n Final data:");
		for(i=0; i<ARRSIZE; i++)
		{
			printf("\t%d", c[i]);
		}
		printf("\n\n Program exit!\n");
	
	}
	
	
	//End MPI environment
	MPI_Finalize();
}
