#include <stdio.h>
#include <stdlib.h>
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

void matrixing(int m, int n, double *a, double A[m][n]){
	int i, j;
	for (i=0; i<m; i++){
		for (j=0; j<n; j++){
			A[i][j] = a[j+i*n]; 
		}
	}
}

void arraying(int m, int n, double *a, double A[m][n]){
	int i, j;
	for (i=0; i<m; i++){
		for (j=0; j<n; j++){
			a[j+i*n] = A[i][j]; 
		}
	}
}

/*void matmult_blk_N(int N, int bb, double *a, double *b, double *c){
	////// JUST FOR SQUARED MATRICES!
	int i, j, k, ii, jj, kk;
	double r;
	//allocating matrices
	double **A;
	A = malloc(N * sizeof(double *));
	for(i = 0; i < N; i++)
		{
		A[i] = malloc(N * sizeof(double));
		}

	double **B;
		B = malloc(N * sizeof(double *));
		for(i = 0; i < N; i++)
			{
			B[i] = malloc(N * sizeof(double));
			}		

	double **C;
		C = malloc(N * sizeof(double *));
		for(i = 0; i < N; i++)
			{
			C[i] = malloc(N * sizeof(double));
			}		

	//assigning matrices the array values

	matrixing(N, N, a, A);
	matrixing(N, N, b, B);
	matrixing(N, N, c, C);

	//blocked multiplication
	for (kk=0; kk<N; kk+=bb){
		for (jj=0; jj<N; jj+=bb){
			for (i=0; i<N; i++){
				for (k=kk; k < min(kk+bb,N); k++){
					r = A[i][k];
					for (j=jj; j < min(jj+bb,N); j++){
						C[i][j] +=  r*B[k][j];
					}
				}
			}
		}
	}

	arraying(N, N, c, C);
	
	free(A);
	free(B);
	free(C);

} */

void matmult_blk(int m, int n, int l, int M, int N, int K, double *a, double *b, double *c){
	int i, j, k, ii, jj, kk;
	double r;

	

	//assigning matrices the array values
	printf("ciao");
	
	for (i=0;)
	
	//allocating matrices
	double A[m][k];
	double B[k][n];	
	double C[m][n];	

	matrixing(m, k, a, A);
	matrixing(k, n, b, B);
	matrixing(m, n, c, C);
	
	printf("ciao");
	for (i=0; i<m; i++){
		for (j=0; j<n; j++){
			printf("%5.0f",A[i][j]); 
		}
		printf("\n");
	}

	int blM = m/M;
	int blN = n/N;
	int blK = l/K;

	//blocked multiplication
/*	for (kk = 0; kk < l; kk += blK){
		for (jj = 0; jj < n; jj += blN){
			for (i = 0; i < m; i++){
				for (k = kk; k < min(kk+blK,l); k++){   
					r = A[i][k];
					for (j = jj; j < min(jj+blN,n); j++){
						C[i][j] +=  r*B[k][j];
					}
				}
			}
		}
	}*/
	N+=2;
	int bb = blM;

	for (kk=0; kk<N; kk+=bb){
		for (jj=0; jj<N; jj+=bb){
			for (i=0; i<N; i++){
				for (k=kk; k < min(kk+bb,N); k++){
					r = A[i][k];
					for (j=jj; j < min(jj+bb,N); j++){
						C[i][j] +=  r*B[k][j];
					}
				}
			}
		}
	}

	arraying(m, n, c, C);
	
}

int main(){
  
  double *A, *B, *Clib, *Cnat, *Cblk;
  int m, n, k,i,j;
  double alpha, beta;
  char transa, transb;
  
  m = 4, k = 4, n = 4;
  
  A = (double *)malloc( m*k*sizeof( double ));
  B = (double *)malloc( k*n*sizeof( double ));
  Clib = (double *)malloc( m*n*sizeof( double ));
  Cnat = (double *)malloc( m*n*sizeof( double ));	
  Cblk = (double *)malloc( m*n*sizeof( double ));
  
 	printf (" Intializing matrix data \n\n");
	for (j = 0; j < k; j++) {
		for (i = 0; i < m; i++){
			A[i*k + j] = (double)(10*(i+1) + (j+1));
		}
	}
	
  
  for (j = 0; j < n; j++) {
    for (i = 0; i < k; i++){
      B[j + i*n] = (double)(20*(i+1) + (j+1));
    }
  }

  for (i = 0; i < (m*n); i++) {
    Clib[i] = 0.0;
    Cnat[i] = 0.0;
  }
  

//display matrices
	printf("\n");
  printf (" Top left corner of matrix A: \n");
  for (j=0; j<m; j++) {
    for (i=0; i<k; i++) {  
        printf ("%12.0f", A[i+j*k]);
     }
      printf ("\n");
    }

    printf ("\n Top left corner of matrix B: \n");
    
    for (j=0; j<k; j++) {
      for (i=0; i<n; i++) {
	printf ("%12.0f", B[i+j*n]);
      }
      printf ("\n");
    }
     
///// FUNCTION CALL!!!

	//matmult_lib(m, n, k, A,B, Clib);
	//matmult_nat(m, n, k, A,B, Cnat);
	matmult_blk(m, n, k, 2, 2, 2, A, B, Cblk);
	

/// final print ( TRANSPOSED - DGEMM STYLE)
    printf ("\n Top left corner of matrix C with matmult_lid: \n");
    for (i=0; i<m; i++) {
      for (j=0; j<n; j++) {
        printf ("%12.5G", Clib[i+j*m]);
      }
      printf ("\n");
    }
 /// final print ( For nat style)
    printf ("\n Top left corner of matrix C with matmult_nat: \n");
    for (i=0; i<m; i++) {
      for (j=0; j<n; j++) {
        printf ("%12.5G", Cnat[j+i*n]);
      }
      printf ("\n");
    }  

//  print for blocked matrix 

 printf ("\n Top left corner of matrix C with matmult_blk: \n");
    for (i=0; i<m; i++) {
      for (j=0; j<n; j++) {
        printf ("%12.5G", Cblk[j+i*n]);
      }
      printf ("\n");
    }

    printf ("\n Deallocating memory \n\n");
    free(A);
    free(B);
    free(Clib);
    free(Cnat);
	free(Cblk);

  
  return 0;
  
}

