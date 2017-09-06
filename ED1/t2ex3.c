#include<stdio.h>
#include<stdlib.h>
int main(){
	int n=5, i, cont=2, c;
	int *p = (int *)calloc(n, sizeof(int));
	
	for(i=0;i<=n;i++){
		if(i==n){
			int *pNew = realloc(p, (cont*5)*sizeof(int));
			if(pNew){
				p = pNew;
			}
			n=n+5;
			cont++;
					
		}
		scanf("%d", p+i);
		if(*(p+i)==0)
			break;
	}
	
	for(c=0;c<i;c++){
		printf("Posições: %p 	Conteúdo: %d\n", p, *p);
		p++;
	}
	
	free(p);
	return 0;	
}
