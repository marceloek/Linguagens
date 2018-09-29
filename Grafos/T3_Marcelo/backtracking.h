void backtracking(int beck, int mp[4][beck+1]){
	int soma = 0, i=1;
	printf("\nArvore geradora minima: ");
	while(i!=8){
		printf("(%d,%d) -> ", mp[0][i], mp[2][i]);
		soma += mp[1][i];
		i++;
	}
	printf("\nComprimento: %d\n", soma);
	puts("");
}