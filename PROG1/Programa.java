import java.util.Scanner;

class Programa{
	public static void main(String[] args){
	Scanner ent=new Scanner(System.in);
	Conta minhaConta;
	minhaConta = new Conta();
	System.out.println("Digite o nome do titular dessa conta:");
	minhaConta.dono=ent.nextLine();
	System.out.println("Digite o numero dessa conta:");
	minhaConta.numero=ent.nextInt();
	System.out.println("Digite o saldo dessa conta:");
	minhaConta.saldo=ent.nextDouble();
	System.out.println("Conta do(a): " +minhaConta.dono);
	System.out.println("Numero: " +minhaConta.numero);
	System.out.println("Saldo: " +minhaConta.saldo);
	minhaConta.saca(230);
	minhaConta.deposita(167);
	System.out.println("\nConta do(a): " +minhaConta.dono);
	System.out.println("Numero: " +minhaConta.numero);
	System.out.println("Saldo: " +minhaConta.saldo);

}}
