#include<stdio.h>
#include<stdbool.h>
#include<mpi.h>

int main(int argc, char **argv)
{
	int myid, size;
	int data_arr [2];
	float data_arr_1 [2];
	char data_arr_2 [2];
	
	
	//Initialize MPI environment
	MPI_Init(&argc, &argv);
	
	//Get total number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//Get my unique identification among all processes
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	if(myid==0)
	{
		//Initialize data to be sent
		data_arr[0] = 205;
		data_arr[1] = 408;
		
		//Print the data to be sent
		printf("\nData Sent from process %d.\n",myid);
		printf("\nmyid:%d\t data_arr[0] = %d",myid, data_arr[0]);
		printf("\nmyid:%d\t data_arr[1] = %d",myid, data_arr[1]);
		
		//send the data

	//	MPI_Send(data_arr, 2, MPI_INT, 1,0, MPI_COMM_WORLD);
		MPI_Send(data_arr, 2, MPI_INT, 2,0, MPI_COMM_WORLD);	
	//	MPI_Recv(data_arr_1, 2, MPI_FLOAT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		
		//Print received data
//		printf("\nData received at process %d.\n",myid);
//		printf("\nmyid: %d \t data_arr[0] = %f", myid, data_arr_1[0]);
//		printf("\nmyid: %d \t data_arr[1] = %f", myid, data_arr_1[1]);
		
		//printf("\nData sent...\n");
	}
	if(myid==1) //Process with id exxactly equal to 1
	{
		//Initialize receive array to some other data
		data_arr_1[0] = 1.525645;
		data_arr_1[1] = 2.16541;
		
		//Print the data to be sent
		printf("\nData Sent from process %d.\n",myid);
		printf("\nmyid:%d\t data_arr[0] = %f",myid, data_arr_1[0]);
		printf("\nmyid:%d\t data_arr[1] = %f",myid, data_arr_1[1]);
		
		//printf("\nRank %d ready to post MPI_Recv CAll...\n", myid);

		MPI_Send(data_arr_1, 2, MPI_FLOAT, 2, 0, MPI_COMM_WORLD);
	//	MPI_Recv(data_arr, 2, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		//printf("\nData Received...");
		
		//Print received data
//		printf("\nData received at process %d.\n",myid);
//		printf("\nmyid: %d \t data_arr[0] = %d", myid, data_arr[0]);
//		printf("\nmyid: %d \t data_arr[1] = %d", myid, data_arr[1]);
		

	}
	if(myid==2) //Process with id exxactly equal to 2
	{
		//Initialize receive array to some other data
		data_arr_2[0] = 'v';
		data_arr_2[1] = 'p';
		
		//Print the data to be sent
//		printf("\nData Sent from process %d.\n",myid);
//		printf("\nmyid:%d\t data_arr[0] = %f",myid, data_arr_2[0]);
//		printf("\nmyid:%d\t data_arr[1] = %f",myid, data_arr_2[1]);
		
		//printf("\nRank %d ready to post MPI_Recv CAll...\n", myid);

		//MPI_Send(data_arr_1, 2, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
		
		printf("\n++++++++++\n");
		MPI_Recv(data_arr, 2, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		//Print received data
		printf("\nData received from process 0.\n");
		printf("\nmyid: %d \t data_arr[0] = %d", myid, data_arr[0]);
		printf("\nmyid: %d \t data_arr[1] = %d", myid, data_arr[1]);
		
		MPI_Recv(data_arr_1, 2, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);		
		//printf("\nData Received...");
		
		//Print received data
		printf("\nData received from process 1.\n");
		printf("\nmyid: %d \t data_arr[0] = %f", myid, data_arr_1[0]);
		printf("\nmyid: %d \t data_arr[1] = %f", myid, data_arr_1[1]);
		

	}
	//printf("\nRank %d reached here - Before MPI_FInalize.\n", myid);
	//End MPI environment
	MPI_Finalize();
			printf("\n\nProgram exit!\n");
//	printf("\nRank %d reached here - after MPI_FInalize.\n", myid);
}
