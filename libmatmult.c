#include <stdio.h>
#include <stdlib.h>
#include <sunperf.h>

#ifndef MATMULT_LIB_H
#define MATMULT_LIB_H

void matmult_lib(int m, int n, int k, double *A, double *B, double *C){
	double alpha, beta;
	char transa, transb;
	
	alpha = 1.0; beta = 0.0;
	transa = 't', transb='t';
  
	dgemm(transa, transb, m, n, k, alpha, A, k, B, n, beta, C, m);
		
}

void matmult_nat(int m, int n, int k, double *A, double *B, double *C){
	int i,j,t;
	for (i = 0; i < m ; i++){
		for (j = 0; j < n; j++){
			C[i*n+j]=0;
			for (t = 0; t < k ; t++){
				C[i*n+j] += A[i*k+t]*B[t*n+j];
			}
		}
	}
}

#endif
