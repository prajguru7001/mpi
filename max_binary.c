#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc, char **argv)
{
	int myid, size, num, max,val,i,location;
	int values[16] = {0,6,4,7,9,2,3,111,23,85,63,42,85,0,1,22};
	int info[2],info1[2];
	int j, recv_val;
	
	MPI_Status status;
	//Initialize MPI environment
	MPI_Init(&argc, &argv);
	
	//Get total number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//Get my unique identification among all processes
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	val = values[myid];

	for(i=size; i>0;i=i/2)
	{
		j = i/2;
		if(myid< i)
		{
			if(myid<(j))
			{
				MPI_Recv(&recv_val, 1, MPI_INT, myid +j, 0 ,MPI_COMM_WORLD,MPI_STATUS_IGNORE); 	
				
				if(val < recv_val)
				{
					val = recv_val;


				}
			}
			else
			{
				MPI_Send(&val, 1, MPI_INT, myid-j, 0, MPI_COMM_WORLD);
			}
		}
	}
	

	
	if(myid==0)
	{
		printf("\nMax Value = %d\n", val);

	}
	
	if(myid==0)
	{
		for(i=1;i<size;i++)
		{
			MPI_Send(&val, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
		}
		MPI_Recv(&recv_val, 1, MPI_INT, MPI_ANY_SOURCE,10 ,MPI_COMM_WORLD, &status);
		printf("Value recieved %d from location %d\n",val, status.MPI_SOURCE);
	}	
	else
	{
		
		MPI_Recv(&recv_val, 1, MPI_INT, 0,0 ,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		if(recv_val == values[myid])
		{
			MPI_Send(&myid, 1, MPI_INT, 0, 10, MPI_COMM_WORLD);
		}
	}
	
		MPI_Finalize();
	
	
	
	
	
	
}
