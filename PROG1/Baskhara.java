class Baskhara{
int a;
int b;
int c;

Baskhara(int a, int b, int c){
	this.a=a;
	this.b=b;
	this.c=c;
}

void imprime(){
	double x1 = (-b + (Math.sqrt((b*b)-(4*a*c))))/(2*a);
	double x2=(-b - (Math.sqrt((b*b)-(4*a*c))))/(2*a);
	System.out.println("X1: " +x1);
	System.out.println("X2: " +x2);
}
}

