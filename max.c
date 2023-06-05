#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc, char **argv)
{
	int myid, size, num, max,val,i;
	int values[10] = {0,6,4,7,9,2,3,0,1,22};
	
	//Initialize MPI environment
	MPI_Init(&argc, &argv);
	
	//Get total number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//Get my unique identification among all processes
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	
	
	if(myid==0){
		max = values[myid];
		for(i=1; i<size; i++){
			MPI_Recv(&val, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			if(val>max)
			{
				max =val;			
			}
	}
	printf("\nMax value= %d\n", max);
	}

	else{
	
		val = values[myid];
		MPI_Send(&val, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		}
		
	
	MPI_Finalize();
}
