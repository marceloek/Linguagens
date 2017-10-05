#include <stdio.h>
#include <stdlib.h>

int conf(int xA, int xB, int xC, int yA, int yB, int yC, int areaABC, int i, int j){
	int areaAC, areaBC, areaAB;
	areaAC=(xA*j + yA*xC + i*yC - (j*xC + xA*yC + yA*i));
	if(areaAC<0)
		areaAC=areaAC*(-1);
	areaBC=(i*yB + j*xC + xB*yC - (yB*xC + i*yC + j*xB));
	if(areaBC<0)
		areaBC=areaBC*(-1);	
	areaAB=(xA*yB + yA*i + xB*j - (yB*i + xA*j + yA*xB));	
	if(areaAB<0)
		areaAB=areaAB*(-1);
	if((areaAC+areaBC+areaAB)<=areaABC)
		return 1;
	else
		return 0;
}

int main(){
	int xA, xB, xC, yA, yB, yC, areaABC, i, j;
	printf("Digite as coordendas da posicao A: ");
	scanf("%d %d", &xA, &yA);
	printf("Digite as coordendas da posicao B: ");
	scanf("%d %d", &xB, &yB);
	printf("Digite as coordendas da posicao C: ");
	scanf("%d %d", &xC, &yC);
	areaABC=(xA*yB + yA*xC + xB*yC - (yB*xC + xA*yC + yA*xB));
	if(areaABC<0)
		areaABC=areaABC*(-1);
	system("clear");
	for(i=0;i<40;i++){
		for(j=0;j<40;j++){
			if(conf(xA, xB, xC, yA, yB, yC, areaABC, i, j)==1)
				printf("7");
			else
				printf(".");
		}
		puts("");
	}	
	return 0;
}
