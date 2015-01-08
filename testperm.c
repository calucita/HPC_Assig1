#include <stdio.h>
#include <stdlib.h>

#include <libmatmult.h>
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



for(i=0;i<m;i++){
  for(j=0;j<n;j++){
    printf("%d ",C[i][j]);
  }
  printf("\n");
}
  
}

