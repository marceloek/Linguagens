#include <stdio.h>
#include <stdlib.h>

int verifica(int xA, int xB, int xC, int yA, int yB, int yC, int areatotal, int i, int j){
	int area1, area2, area3;
	area1=(xA*j + yA*xC + i*yC - (j*xC + xA*yC + yA*i));
	if(area1<0)
		area1=area1*(-1);
	area2=(i*yB + j*xC + xB*yC - (yB*xC + i*yC + j*xB));
	if(area2<0)
		area2=area2*(-1);	
	area3=(xA*yB + yA*i + xB*j - (yB*i + xA*j + yA*xB));	
	if(area3<0)
		area3=area3*(-1);
	if((area1+area2+area3)<=areatotal)
		return 1;
	else
		return 0;
}

int main(){
	int xA, xB, xC, yA, yB, yC, areatotal, i, j;
	printf("Digite o valor da coordenada de A: ");
	scanf("%d %d", &xA, &yA);
	printf("Digite o valor da coordenada de B: ");
	scanf("%d %d", &xB, &yB);
	printf("Digite o valor da coordenada de C: ");
	scanf("%d %d", &xC, &yC);
	areatotal=(xA*yB + yA*xC + xB*yC - (yB*xC + xA*yC + yA*xB));
	if(areatotal<0)
		areatotal=areatotal*(-1);
	system("clear");
	for(i=0;i<40;i++){
		for(j=0;j<40;j++){
			if(verifica(xA, xB, xC, yA, yB, yC, areatotal, i, j)==1)
				printf("7");
			else
				printf("0");
		}
		puts("");
	}	
	return 0;
}
