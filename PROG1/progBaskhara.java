import java.util.Scanner;
import java.lang.Math;

class progBaskhara{
	public static void main(String[] args){
	
	Scanner tec=new Scanner(System.in);
	int a=tec.nextInt();
	int b=tec.nextInt();
	int c=tec.nextInt();
	Baskhara Bask=new Baskhara(a,b,c);
	Bask.imprime();
}
}
