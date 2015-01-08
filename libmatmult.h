#include <stdio.h>
#include <stdlib.h>
#include <sunperf.h>

#ifndef MATMULT_LIB_H
#define MATMULT_LIB_H

void matmult_lib(int m, int n, int k, double **A, double **B, double **C){
	double alpha, beta;
	char transa, transb;
	
	alpha = 1.0; beta = 0.0;
	transa = 't', transb='t';
  
	dgemm(transa, transb, m, n, k, alpha, A[0], k, B[0], n, beta, C[0], m);
		
}

void matmult_nat(int m, int n, int k, double **A, double **B, double **C){
	int i,j,t;
	for (int i = 0; i < m ; i++){
		for (int j = 0; j < n; j++){
			for (int t = 0; t < k ; t++){
				C[i][j] += A[i][t]*B[t][j];
			}	
		}
	}
}

void matmult_mnk(int m, int n, int k, double **A, double **B, double **C){
	int i,j,t;
	for (int i = 0; i < m ; i++){
		for (int j = 0; j < n; j++){
			for (int t = 0; t < k ; t++){
				C[i][j] += A[i][t]*B[t][j];
			}	
		}
	}
}

void matmult_mkn(int m, int n, int k, double **A, double **B, double **C){
	int i,j,t;
	for (int i = 0; i < m ; i++){
		for (int t = 0; t < k ; t++){
			for (int j = 0; j < n; j++){
				C[i][j] += A[i][t]*B[t][j];
			}	
		}
	}
}

void matmult_nmk(int m, int n, int k, double **A, double **B, double **C){
	int i,j,t;
	for (int j = 0; j < n; j++){
		for (int i = 0; i < m ; i++){
			for (int t = 0; t < k ; t++){
				C[i][j] += A[i][t]*B[t][j];
			}	
		}
	}
}

void matmult_nkm(int m, int n, int k, double **A, double **B, double **C){
	int i,j,t;
	for (int j = 0; j < n; j++){
		for (int t = 0; t < k ; t++){
			for (int i = 0; i < m ; i++){
				C[i][j] += A[i][t]*B[t][j];
			}	
		}
	}
}

void matmult_knm(int m, int n, int k, double **A, double **B, double **C){
	int i,j,t;
	for (int t = 0; t < k ; t++){
		for (int j = 0; j < n; j++){
			for (int i = 0; i < m ; i++){
				C[i][j] += A[i][t]*B[t][j];
			}	
		}
	}
}

void matmult_kmn(int m, int n, int k, double **A, double **B, double **C){
	int i,j,t;
	for (int t = 0; t < k ; t++){
		for (int i = 0; i < m ; i++){
			for (int j = 0; j < n; j++){
				C[i][j] += A[i][t]*B[t][j];
			}	
		}
	}
}


#endif
