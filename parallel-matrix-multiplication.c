#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>

// Name: Icaro Neves Melo

// Parallel Matrix Multiplication using OpenMP

struct timeval start, end;  // Time counters
 

double **alocateMatrix(int N)
{

	int i,j,k;  // i,j,k variables used as index
	double **mat=NULL;  // Pointer to matrix

  	// IF: Allocates matrix rows
  	if ( ! (mat = (double **) malloc(N*sizeof(double))) ){
    	return (NULL); 
  	}
        // Loop to allocate columns
	for ( i = 0; i <N; i++ ) {
		mat[i] = (double*) malloc (N*sizeof(double)); // Allocate more columns
		if (mat[i] == NULL) {
			printf ("** Error: Insufficient Memory**");
			return (NULL);
		}
	}
	return (mat);
}



int main (char argc,char *argv[])
{
	int n = 1500;
  	double **A, **B, **C;
	int i, j, k, threadsNum;
	double sum;
	A = alocateMatrix(n);
	B = alocateMatrix(n);
	C = alocateMatrix(n);
	threadsNum = omp_get_max_threads ( ); 
	printf ( "\n" );
	printf ( " Numbers of processors = %d\n", omp_get_num_procs ( ) );
	printf ( " Disponible threads   = %d\n", threadsNum);

	gettimeofday(&start,NULL);
	# pragma omp parallel shared (A,B,C, n, sum) private ( i, j, k ) 
	// Sharing of matrices A,B,C; matrix size n; and the summation of all elements of the resulting matrix
	// Matrix indices as private
	{
	 	# pragma omp for // Parallelization of the for for assignment of matrices
	  		for ( i = 0; i < n; i++ )
	  		{
	    		for ( j = 0; j < n; j++ )
	    		{
				A[i][j]=i+j;
				B[i][j]=i+j;
	    		}
		  	}

	  	# pragma omp for  // Pairing of the force for matrix multiplication
	  	for ( i = 0; i < n; i++ )
	  	{
	    	for ( j = 0; j < n; j++ )
	    	{
	      		for ( k = 0; k < n; k++ )
	      		{
					C[i][j] = C[i][j] + A[i][k] * B[k][j];
	      		}
	    	}
		}
	}

	sum = 0;
  	# pragma omp for  // Summation of all elements of the resulting matrix
  	for ( i = 0; i < n; i++ )
  	{
    	for ( j = 0; j < n; j++ )
    	{
			sum = sum+C[i][j];
     	}
	}
	
	gettimeofday(&end,NULL);
  	printf ( "\n \n \n" );
  	printf ( "--Result--\n");
  	printf ( " Summation: %lf\n", sum);

  	printf ( "\n \n" );
	printf ("Matrix multiplication time = %ld microsecond(s); %ld millisecond(s); %ld second(s)",((end.tv_sec*1000000+end.tv_usec)-(start.tv_sec*1000000+start.tv_usec)),((end.tv_sec*1000000+end.tv_usec)-(start.tv_sec*1000000+start.tv_usec))/1000,((end.tv_sec*1000000+end.tv_usec)-(start.tv_sec*1000000+start.tv_usec))/1000000);
  	printf ( "\n \n" );
  return 0;
}

