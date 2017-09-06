#include<stdio.h>
#include<stdlib.h>

int* uniao(int *v1, int n1, int *v2, int n2){ 
	int *v3=(int *)calloc(n1+n2, sizeof(int)), i;
	for(i=0;i<n1;i++){
		*(v3+i)=*(v1+i);
	}
	for(i=n1;i<n1+n2;i++){
		*(v3+i)=*(v2+i-n1);
	}
	return v3;
}

int main(){
	int v1[4]={11,13,45,7}, v2[6]={24,4,16,81,10,12}, n1=4, n2=6, n;
	int *v3=(int *)calloc(n1+n2, sizeof(int));
	v3=uniao(v1,n1,v2,n2);
	for(n=0;n<n1+n2;n++){
		printf("v3[%d]: %d\n", n, v3[n]);
	}
	
	free(v3);	
	return 0;
}
