#include<stdio.h>

void Kruskal(int K[4][11], int V[2][8]){
	int dist = 0;
	int f = 0;
	for(int i = 0; i<11; i++){
		int p = V[1][K[1][i]];
		if(K[1][i] != K[2][i]){
			if(V[0][K[1][i]] == K[1][i] && p == K[2][i]){
				K[3][i] = -1;
			}else if(p > -1 && p == V[1][K[2][i]]){
				K[3][i] = -1;
			}else{
				printf("(%d, %d) -> ", K[1][i], K[2][i]);
				dist = dist + K[0][i];
				K[3][i] = 1;
				if(V[1][K[1][i]] == -1){
					for(int h = 0, d = K[2][i]; h != 1; ){
						if(V[1][d] < 0){
							V[1][K[1][i]] = d;
							V[1][d] = V[1][d] - 1;
							h = 1;
						}else{
							d = V[1][d];
						}
					}
				}else{
					if(V[1][K[2][i]] == -1){
						V[1][K[2][i]] = V[1][K[1][i]];
					}else{
						if(V[1][V[1][K[1][i]]] <= V[1][V[1][K[2][i]]]){
							V[1][V[1][K[1][i]]] = V[1][V[1][K[1][i]]] + V[1][V[1][K[2][i]]];
							V[1][V[1][K[2][i]]] = V[1][K[1][i]];

						}else{
							V[1][V[1][K[2][i]]] = V[1][V[1][K[2][i]]] + V[1][V[1][K[1][i]]];
							V[1][V[1][K[1][i]]] = V[1][K[2][i]];
						}
					}
				}
			}
		}
		f = 0;
		for(int j=0; j < 8; j++){
			if(V[1][j] < 0)
				f++;
		}
		if(f == 1)
			break;
	}
	printf("\n\nCusto total da arvore: %d\n\n", dist);
}

int main(){
	int K[4][11] = {{2, 3, 3, 4, 4, 7, 7, 7, 8, 8, 8},
	{ 6, 0, 0, 0, 5, 4, 4, 5, 2, 2, 3},
	{ 7, 1, 3, 2, 6, 6, 7, 7, 4, 5, 5},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
	int V[2][8] = {{ 0, 1, 2, 3, 4, 5, 6, 7},
	{-1,-1,-1,-1,-1,-1,-1,-1}};
	printf("\nArvore geradora minima: ");
	Kruskal(K, V);
}