#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc, char **argv)
{
	int myid, size, num, max,val,i,location;
	int values[16] = {0,6,4,7,9,2,3,111,23,85,63,42,85,0,1,22};
	int info[2],info1[2];
	int j, recv_val;
	//Initialize MPI environment
	MPI_Init(&argc, &argv);
	
	//Get total number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//Get my unique identification among all processes
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	val = values[myid];
	info[0] = val;
	info[1] = myid;
	for(i=size; i>0;i=i/2)
	{
		j = i/2;
		if(myid< i)
		{
			if(myid<(j))
			{
				MPI_Recv(info1, 2, MPI_INT, myid +j, 0 ,MPI_COMM_WORLD,MPI_STATUS_IGNORE); 	
				
				if(info[0] < info1[0])
				{
					info[0] = info1[0];
					info[1] = info1[1];

				}
			}
			else
			{
				MPI_Send(info, 2, MPI_INT, myid-j, 0, MPI_COMM_WORLD);
			}
		}
	}
	
	MPI_Finalize();
	
	if(myid==0)
	{
		printf("\nMax Value = %d\n", info[0]);
		printf("Location = %d\n", info[1]);
	}
}
