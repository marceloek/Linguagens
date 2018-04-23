import java.util.*;

public class Mamifero extends Animal{
	private alimento;
	public Mamifero(String nome, String cor, String alimento,int comprimento, double velocidade, int patas){
		super.setNome(nome);
		super.setCor(cor);
		super.setAmbiente(ambiente);
		super.setComprimento(comprimento);
		super.setVelocidade(velocidade);
		super.setPatas(patas);
	}

	void setAlimento(String alimento){
		this.alimento = alimento;
	}

	String getAlimento(){
		return alimento;
	} // retorna o alimento de um determindado uso

	void dados(){
		system.out.println("Animal: "+this.animal);
		system.out.println("Comprimento: "+this.comprimento);
		system.out.println("Patas: "+this.patas);
		system.out.println("Cor: "+this.cor);
		system.out.println("Ambiente: "+this.ambiente);
		system.out.println("Velocidade:"+this.velocidade);
		system.out.println("Alimento: ", +Alimento);
	} // imprimir na tela todos os dados
}