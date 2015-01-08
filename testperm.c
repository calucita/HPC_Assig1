#include <stdio.h>
#include <stdlib.h>
#include <sunperf.h>


void matmult_lib(int m, int n, int k, double **A, double **B, double **C){
	double alpha, beta;
	char transa, transb;
	
	alpha = 1.0; beta = 0.0;
	transa = 't', transb='t';
  
	dgemm(transa, transb, m, n, k, alpha, A[0], k, B[0], n, beta, C[0], m);
		
}

void matmult_nat(int m, int n, int k, double **A, double **B, double **C){
	int i,j,t;
	for ( i = 0; i < m ; i++){
		for ( j = 0; j < n; j++){
			for ( t = 0; t < k ; t++){
				C[i][j] += A[i][t]*B[t][j];
			}	
		}
	}
}

void matmult_mnk(int m, int n, int k, double **A, double **B, double **C){
	int i,j,t;
	for ( i = 0; i < m ; i++){
		for ( j = 0; j < n; j++){
			for ( t = 0; t < k ; t++){
				C[i][j] += A[i][t]*B[t][j];
			}	
		}
	}
}

void matmult_mkn(int m, int n, int k, double **A, double **B, double **C){
	int i,j,t;
	for ( i = 0; i < m ; i++){
		for ( t = 0; t < k ; t++){
			for ( j = 0; j < n; j++){
				C[i][j] += A[i][t]*B[t][j];
			}	
		}
	}
}

void matmult_nmk(int m, int n, int k, double **A, double **B, double **C){
	int i,j,t;
	for ( j = 0; j < n; j++){
		for ( i = 0; i < m ; i++){
			for ( t = 0; t < k ; t++){
				C[i][j] += A[i][t]*B[t][j];
			}	
		}
	}
}

void matmult_nkm(int m, int n, int k, double **A, double **B, double **C){
	int i,j,t;
	for ( j = 0; j < n; j++){
		for ( t = 0; t < k ; t++){
			for ( i = 0; i < m ; i++){
				C[i][j] += A[i][t]*B[t][j];
			}	
		}
	}
}

void matmult_knm(int m, int n, int k, double **A, double **B, double **C){
	int i,j,t;
	for ( t = 0; t < k ; t++){
		for ( j = 0; j < n; j++){
			for ( i = 0; i < m ; i++){
				C[i][j] += A[i][t]*B[t][j];
			}	
		}
	}
}

void matmult_kmn(int m, int n, int k, double **A, double **B, double **C){
	int i,j,t;
	for ( t = 0; t < k ; t++){
		for ( i = 0; i < m ; i++){
			for ( j = 0; j < n; j++){
				C[i][j] += A[i][t]*B[t][j];
			}	
		}
	}
}



int main() {


int m,n,k,i,j,l,sum=0; //dimensions
double **A,**B,**C, *a, *b, *c; //matrices

m=3;
n=2;
k=5;

//allocate memory
a = (double *)malloc( m*k*sizeof( double ));
b = (double *)malloc( k*n*sizeof( double ));
c = (double *)malloc( m*n*sizeof( double ));

//allocate memory
A=malloc(m * sizeof(double *));
for(i=0;i<m;i++){
  A[i]=malloc(k *sizeof(double));
}

//assign values to matrices
for(i=0;i<m;i++){
  for(j=0;j<k;j++){
    A[i][j]=10.0*(i+1)+(j+1);
  }
}

//make array
for (i=0; i<m; i++) {
  for (j=0; j<k; j++) {
    a[j+i*k] = (double) 10.0*(i+1)+(j+1);
    printf("%d ", i);
  }
}
printf("\n");

//print
for(i=0;i<(m*k);i++){
  printf("%d ", a[i]);
}

//allocate memory
B=malloc(k * sizeof(double *));
for(i=0;i<k;i++){
  B[i]=malloc(n *sizeof(double));
}

//assign values to matrices
for(i=0;i<k;i++){
  for(j=0;j<n;j++){
    B[i][j]=20.0*(i+1)+(j+1);
  }
}

//allocate memory
C=malloc(m * sizeof(double *));
for(i=0;i<m;i++){
  C[i]=malloc(n *sizeof(double));
}

/*
//multiply A and B
for(i=0; i<m; i++){
  for(j=0; j<n; j++){
    for(l=0; l<k; l++){
      sum = sum + A[i][l]*B[l][j];
    }
    C[i][j] = sum;
    sum = 0;
  }
}
*/


matmult_kmn(m, n,  k,  A, B, C);

matmult_lib( m,  n,  k, A, B,  C);
for(i=0;i<m;i++){
  for(j=0;j<n;j++){
    printf("%d ",C[i][j]);
  }
  printf("\n");
}
  
}

