#include <stdlib.h>
#include <stdio.h>

void retrieve(int m, int n, int nBM, int nBN, int indexR, int indexC, double *A, double *a){
	int i,j;	
	int p=m/nBM;
	int q=n/nBN;
	int indexa=indexC*q+indexR*n*p;
	for(i=0;i<p;i++){
		for(j=0;j<q;j++){
			a[i*q+j]=A[indexa+j+n*i];
		}	
	}
}

void push(int size, int index, double *C, double *Cps){
	int i;
	for(i=0;i<size;i++){
		C[index+i]=Cps[i];
	}
}

void sumvec(int size, double *a, double *b){
	int i;
	for(i=0;i<size;i++){
		a[i]=a[i]+b[i];
	}
}

void zero(int size, double *Cps){
	int i;
	for(i=0;i<size;i++){
		Cps[i]=0;
	}
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

void printVector(int size, double *C){
  int i;
  for(i=0;i<size;i++){
	printf("%f ",C[i]);
  }
printf("\n");
}


void matmult_blk(int m, int n, int k, double *A, double *B, double *C, int nBM, int nBN, int nBK){
	int i,j;
	double *Apq;
	double *Bqs;
	double *Cps;
	double *Cpsaux;
	int p=m/nBM;
	int q=k/nBK;
	int s=n/nBN;
	Apq=(double *)malloc(p * q * sizeof(double));
	Bqs=(double *)malloc(q * s * sizeof(double));
	Cps=(double *)malloc(p * q * sizeof(double));
	Cpsaux=(double *)malloc(p * q * sizeof(double));
	
	int pp, qq,rr, indexRA, indexCA, indexRB, indexCB, index;
	index=-p*s;
	for(pp=0;pp<nBM;pp++){
		for(qq=0;qq<nBK;qq++){
			zero(p*s, Cps);
			for(rr=0;rr<nBN;rr++){
				indexRA=pp;
				indexCA=rr;
				indexRB=rr;
				indexCB=qq;
				retrieve(m, n, nBM, nBN, indexRA, indexCA, A, Apq);
				retrieve(m, n, nBM, nBN, indexRB, indexCB, B, Bqs);
				matmult_nat(p,s,q,Apq,Bqs,Cpsaux);
				sumvec(p*s,Cps,Cpsaux);
			}
			index=index+(p*s);
			printf("index %i \n", index);
			push(p*s,index,C,Cps);
		}
	}

	
}


int main(){
	int i,j,n,m,k,flag;
	m=4;
	n=4;
	k=4;
	flag=1;
	double A[m*k];
	for(j=0;j<k;j++){
		for(i=0;i<m;i++){
			A[i+j*m]=flag;
			flag++;
		}
	}
	flag=1;
	double B[k*n];
	for(j=0;j<n;j++){
		for(i=0;i<k;i++){
			B[i+j*k]=flag;
			flag++;
		}
	}

	
	int nBM=2;
	int nBN=2;
	int nBK=2;
	int p=m/nBM;
	int s=n/nBN;
	/*double *a;
	a=(double *)malloc(p * s * sizeof(double));
	retrieve( m,  n,  nBM, nBN, 1,  0, A, a);
	printVector(p*s,a);*/
	
	double *C;
	C=(double *)malloc(m * n * sizeof(double));
	printVector(m*k,A);
	printVector(k*n,B);
	matmult_blk(m, n, k, A, A, C, nBM, nBN, nBK);
	printf("C matrix \n");
	printVector(m*n,C);
}
