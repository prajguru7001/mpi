#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>


int main(int argc, char **argv){
        int size, myid;
        int N = 10;
        int A[N][N];
        int B[N];
        int C_1[N];
        int i, j, k, temp;
	double start_t, end_t, exec_t;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	int C[N/size];
	int A_1[(N*N)/size];
	
	if(myid==0)
	{
		for(i=0; i<N; i++){
			B[i] = 2;
		        for(j=0; j<N; j++){
		                A[i][j] = 2;
		        }
		}
        }
 
 	if(myid==0)
 	{
		start_t = MPI_Wtime();
	}
 
 	MPI_Scatter(A ,(N*N)/size, MPI_INT, A_1, (N*N)/size, MPI_INT, 0, MPI_COMM_WORLD);
 	
 //	for(i=0; i<(N*N)/size; i++)
//		printf("%d  process id: %d\n",A_1[i], myid);


 	
	MPI_Bcast(B, N, MPI_INT, 0, MPI_COMM_WORLD);
 	
// 	for(i=0; i<N; i++)
//		printf("%d  process id: %d\n",B[i], myid);

	
	for(i=0;i<N/size;i++){
		temp = 0;
		for(j=0; j<N;j++){
			temp+=A_1[i*N+j]*B[j];
		}
		C[i] = temp;
	//	printf("%d\n",C[i]);
	}
          
        MPI_Gather(C,N/size, MPI_INT, C_1, N/size, MPI_INT, 0, MPI_COMM_WORLD);

        if(myid==0){
	       	end_t = MPI_Wtime();
		exec_t = end_t - start_t;
		printf("\nExecution Time = %f\n", exec_t);
		for(i=0;i<N;i++)
			printf("%d\n",C_1[i]);
		
	}
      	MPI_Finalize();
}

