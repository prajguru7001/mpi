#include<stdio.h>
#include<stdbool.h>
#include<mpi.h>

int main(int argc, char **argv)
{
	int myid, size;
	int val[1];
	
	
	//Initialize MPI environment
	MPI_Init(&argc, &argv);
	
	//Get total number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//Get my unique identification among all processes
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);


		
	MPI_Recv(val, 1, MPI_INT, (myid-1)%size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	//printf("Value recieved at %d... %d\n",(myid-1)%size, val[0]);
		
	val[0] = val[0]+myid;
	//printf("Process: %d \t Value: %d\n",myid,val[0]);	
		
		
	MPI_Send(val, 1, MPI_INT, (myid+1)%size, 0, MPI_COMM_WORLD);
	//printf("Data Sent...\n");


	if(myid==0){
		sum = myid;
		MPI_Send(&sum, MPI_INIT, myid+1, 0, MPI_COMM_WORLD);
		MPI_Recv(&sum, MPI_INIT, size-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	else if(myid==size-1){
		MPI_Recv(&sum, 1, MPI_INIT, myid-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		sum=sum+myid;
		MPI_Send(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

	}
	else
	{
		MPI_Recv(&sum, 1, MPI_INT, myid-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		sum=sum+myid;
		MPI_Send(&sum, 1, MPI_INT, myid+1, 0, MPI_COMM_WORLD);
	}
	//End MPI environment
	MPI_Finalize();
	if(myid==size-1){
		printf("Sum = %d\n",val[0]);
	}

}
