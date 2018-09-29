void backtracking(int beck, int mp[4][beck]){
	printf("\nComprimento: %d\n", mp[1][beck-1]);
	printf("\nCaminho mais curto: ");
	while(beck!=0){
		beck--;
		printf("%d -> ", mp[0][beck]);
		beck=mp[2][beck];
	}
	puts("");
}