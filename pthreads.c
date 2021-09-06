#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>


/*
Program using pthreads, which creates 8 threads and uses these threads to do vector sum
R[0..N]=A[0..N]+B[0..N]. Where all vectors have 2^27 elements and vectors A and B must
be started with A[i]=B[i]=i
*/

long N;
int NTHREADS = 8;
long* R;
long* A;
long* B;

void *sumtoria(void *region_ptr){
	long region = (long) region_ptr;
	long sum;
	for(long i=0;i<10;i++){
		sum = A[i]+B[i];
	}
	R[region] = sum;
	return NULL;

}

int main(){
	N = pow(2,27);
	A = (long*)malloc(N*sizeof(long));
	B = (long*)malloc(N*sizeof(long));
	R = (long*)malloc(N*sizeof(long));
	long sum; // result of sum variable
	pthread_t thread[8];

	for(long i = 0;i < NTHREADS;i++){ // createion of threads
		pthread_create (&thread[i], NULL, sumtoria, (void *)i);
	}

	for(long i = 0; i < 10; i++){ // attribution ofA values
		A[i] = i;
	}

	for(long j = 0; j < 10; j++){ // Attribution of B
		B[j] = j;
	}

	sum = 0;
	for(long i = 0;i < NTHREADS; i++){ // creation of threads
		pthread_join(thread[i], NULL);
		sum += R[i];
	}

	for(long i = 0;i < 10; i++){
		printf("%ld ", R[i]);
	}

}

