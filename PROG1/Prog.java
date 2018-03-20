import java.util.Scanner;

public class Prog{
	public static void main(String[] args){
		Scanner tec=new Scanner(System.in);
		Med Morfina = new Med;
		int num, p;
		do{
			System.out.println("ESCOLHA O QUE DESEJA FAZER:");
			System.out.println("1-PARA COMPRAR:");
			System.out.println("2-PARA VENDER:");
			System.out.println("3-PARA MOSTRAR DATA DE VALIDADE:");
			System.out.println("4-PARA SAIR:");
			switch(p){
				case 1:
				mostrar();
				break;
				case 2:
				vender();
				break;
				case 3:
				vadidade();
				break;
				case 4:
				System.out.println("Voce saiu do programa!");
				break;
				default
				System.out.println("Opcao invalida!");
			}
		}while(num!=4);
	}

}