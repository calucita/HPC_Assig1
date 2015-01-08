#include <stdio.h>
#include <stdlib.h>
#include <sunperf.h>
#include <math.h>

#define min(a,b)(((a)<(b))?(a):(b))


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

void matmult_blk(int m, int n, int l, double **A, double **B, double **C, int bb){
	int i,j,k,ii,jj,kk;
	double r;
	//size of block from number of elements
	bb=sqrt(bb);
	//blocked multiplication
	for(kk=0;kk<l;kk+=bb){
		for(jj=0;jj<n;jj+=bb){
			for(i=0;i<m;i++){
				for(k=kk;k<min(kk+bb,l);k++){
					r=A[i][k];
					for(j=jj;j<min(jj+bb,n);j++){
						C[i][j]+=r*B[k][j];
					}
				}
			}
		}
	}
}



int main() {


int m,n,k,i,j,l,i1,j1,l1,p,q,r,s,bz; //dimensions
double **A,**B,**C; //matrices

m=3;
n=2;
k=5;

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

matmult_blk(m, n, k, A, B, C, 9);

/*
s=2;
//multiply A and B
for(p=0;p<s;p++){
  for(q=0;q<s;q++){
    C[p][q]=0;
    for(r=0;r<m;r++){
      C[p][q]=C[p][q]+A[p][r]*B[r][q];
    }
  }
}
*/

/*
bz=2;
for(i1=0;i1<(n/bz);i1++){
	for(j1=0;j1<(n/bz);j1++){
		for(l1=0;l1<(n/bz);l1++){
			for(i=i1;p<min(i1+bz-1,n);p++){
				for(j=j1;j<min(j1+bz-1,n);j1++){
					for(l=l1;l<min(l1+bz-1,n);l++){
						C[i][j]=C[i][j]+A[i][l]*B[l][j];
					}
				}
			}		
		}
	}
}
*/

printf ("\n matrix A: \n");
for(i=0;i<m;i++){
  for(j=0;j<k;j++){
    printf("%lf ",A[i][j]);
  }
  printf("\n");
}

printf ("\n matrix B: \n");
for(i=0;i<k;i++){
  for(j=0;j<n;j++){
    printf("%lf ",B[i][j]);
  }
  printf("\n");
}

printf ("\n matrix C: \n");
for(i=0;i<m;i++){
  for(j=0;j<n;j++){
    printf("%lf ",C[i][j]);
  }
  printf("\n");
}

    free(A);
    free(B);
    free(C);
  
}

