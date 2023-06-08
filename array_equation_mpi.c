#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<sys/time.h>


#define N 10

int main(int argc, char **argv)
{
	int myid, size;
	int i, j;
	double *c, *x, *y;
	double *C, *X, *Y;
	double a;
	double exe_time;

	struct timeval stop_time, start_time;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);	


	
	if(myid == 0)
	{
		a = 0.01;
		x = (double *) malloc(N*sizeof(double));
		y = (double *) malloc(N*sizeof(double));
		c = (double *) malloc(N*sizeof(double));
		
		for(i=0;i<N;i++)
		{
		    x[i] = i;
		    y[i] = i;
		    c[i] = 0;
		}
		printf("\n Initial Array :\n");
		for(i=0;i<N;i++)
		{
		    printf("%lf, %lf\t", x[i], y[i]);
		}
	}
	
	gettimeofday(&start_time, NULL);
	
	C = (double *) malloc(N/size*sizeof(double));
	X = (double *) malloc(N/size*sizeof(double));
	Y = (double *) malloc(N/size*sizeof(double));
	
	MPI_Bcast(&a, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
//	MPI_Scatter(c ,N/size, MPI_DOUBLE, C, N/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Scatter(x ,N/size, MPI_DOUBLE, X, N/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Scatter(y ,N/size, MPI_DOUBLE, Y, N/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	
	
	for(i=0;i<N/size;i++)
	{
		C[i] = a*X[i] + Y[i];
	}

        MPI_Gather(C,N/size, MPI_DOUBLE, c, N/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Gather(X,N/size, MPI_DOUBLE, x, N/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Gather(Y,N/size, MPI_DOUBLE, y, N/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        
       	free(C);
	free(X);
	free(Y);

	gettimeofday(&stop_time, NULL);	
	exe_time = (stop_time.tv_sec+(stop_time.tv_usec/1000000.0)) - (start_time.tv_sec+(start_time.tv_usec/1000000.0));
	
	MPI_Finalize();
	if(myid==0)
	{
		printf("\n Final Array :\n");
		for(i=0;i<N;i++)
		{
		    printf(" %lf", c[i]);
		}
	}
	printf("\n");
	free(c);
	free(x);
	free(y);
}

