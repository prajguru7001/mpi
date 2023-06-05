#include<stdio.h>
#include<stdbool.h>
#include<mpi.h>

int main(int argc, char **argv)
{
	int x, myid, size, total_work_per_rank,start, end, j;
	int n = 10;
	int a[n], b[n], c[n];
	
	//Initialize MPI environment
	MPI_Init(&argc, &argv);
	
	//Get total number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//Get my unique identification among all processes
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	for(int i=0; i<n; i++){
		c[i] = 0;
		a[i] = i;
		b[i] = i;
	}

	total_work_per_rank=2;
	start= myid*total_work_per_rank;
	end = start+total_work_per_rank;
	printf("rank %d start %d end %d\n",myid, start, end);
	for(int i=start, x=0;x<3, i<end; i++){

	//	c[i] = a[i] + b[i];
		c[x*(size*total_work_per_rank)+i] = a[x*(size*total_work_per_rank)+i] + b[x*(size*total_work_per_rank)+i];
	//	c[a*(size*total_work_per_rank)+i] = a[2*(size*total_work_per_rank)+i] + b[2*(size*total_work_per_rank)+i];
//		x+=1;
		}
	
	
	for(int i =0; i<n; i++){
		printf(" %d  %d  %d \n",a[i],b[i],c[i]);
	}
	
	//End MPI environment
	MPI_Finalize();
}
