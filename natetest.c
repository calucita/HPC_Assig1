#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sunperf.h>


void matmult_lib(int m, int n, int k, double *A, double *B, double *C){
	double alpha, beta;
	char transa, transb;
	
	alpha = 1.0; beta = 0.0;
	transa = 't', transb='t';
  
	dgemm(transa, transb, m, n, k, alpha, A, k, B, n, beta, C, m);
		
}

void matmult_nat(int m, int n, int k, double *A, double *B, double *C){
	int i,j,t;
	// C++ printing commented out.-
	for (i = 0; i < m ; i++){
		for (j = 0; j < n; j++){
			C[i*n+j]=0;
			for (t = 0; t < k ; t++){
				C[i*n+j] += A[i*k+t]*B[t*n+j];
			}
			//std::cout << C[i*n+j] << "\t";
		}
		//std::cout << std::endl;
	}
}

int min(int num_a, int num_b){
	if (num_a < num_b){
		return num_a;
	}
	else return num_b;
}

void matrixing(int m, int n, double *a, double **A){
	int i, j;
	for (i=0; i<m; i++){
		for (j=0; j<n; j++){
			A[i][j] = a[j+i*n]; 
		}
	}
}

void arraying(int m, int n, double *a, double **A){
	int i, j;
	for (i=0; i<m; i++){
		for (j=0; j<n; j++){
			a[j+i*n] = A[i][j]; 
		}
	}
}

void matmult_blk_N(int m, int n, int l, double **A, double **B, double **C, int bb){
	////// JUST FOR SQUARED MATRICES!
	int i, j, k, ii, jj, kk;
	double r;	
	bb = sqrt(bb);
	//blocked multiplication
	for (kk = 0; kk < l; kk += bb){
		for (jj = 0; jj < n; jj += bb){
			for (i = 0; i < m; i++){
				for (k = kk; k < min(kk+bb,l); k++){   
					r = A[i][k];
					for (j = jj; j < min(jj+bb,n); j++){
						C[i][j] +=  r*B[k][j];
					}
				}
			}
		}
	}

} 

int main(){
	int m, n, k, i, j, bs;
	
	m = 4, k = 4, n = 4;
	bs = 4;
  	
	double **A;
	A = malloc(m * sizeof(double *));
	for(i = 0; i < m; i++)
		{
		A[i] = malloc(k * sizeof(double));
		}

	double **B;
		B = malloc(k * sizeof(double *));
		for(i = 0; i < k; i++)
			{
			B[i] = malloc(n * sizeof(double));
			}		

	double **C;
		C = malloc(m * sizeof(double *));
		for(i = 0; i < m; i++)
			{
			C[i] = malloc(n * sizeof(double));
			}
  
 	printf (" Intializing matrix data \n\n");
	for (j = 0; j < m; j++) {
		for (i = 0; i < k; i++){
			A[j][i] = (double)(10*(i+1) + (j+1));
		}
	}
	
	for (j = 0; j < k; j++) {
		for (i = 0; i < n; i++){
			B[j][i] = (double)(20*(i+1) + (j+1));
		}
	}
	 

	for (j = 0; j < m; j++) {
		for (i = 0; i < n; i++){
			C[j][i] = (double)(0);
		}
	}


//display matrices
	printf("\n");
	printf (" Top left corner of matrix A: \n");
	for (j=0; j<m; j++) {
		for (i=0; i<k; i++) {  
			printf ("%12.0f", A[j][i]);
		}
		printf ("\n");
	}

	printf ("\n Top left corner of matrix B: \n");

	for (j=0; j<k; j++) {
		for (i=0; i<n; i++) {
			printf ("%12.0f", B[j][i]);
		}
		printf ("\n");
	}

///// FUNCTION CALL!!!

	matmult_blk_N(m, n, k, A, B, C, bs);
	
//  print for blocked matrix 

 printf ("\n Top left corner of matrix C with matmult_blk: \n");
    for (i=0; i<m; i++) {
      for (j=0; j<n; j++) {
        printf ("%12.5G", C[j][i]);
      }
      printf ("\n");
    }

    printf ("\n Deallocating memory \n\n");
    free(A);
    free(B);
	free(C);

  
  return 0;
  
}

