import java.util.*;

public class Peixe extends Animal(){
	private caracteristica;
	public Peixe(String nome, String caracteristica, int comprimento, double velocidade){
		super.setNome(nome);
		super.setComprimento(comprimento);
		super.setVelocidade(velocidade);
	}

	void setCaracteristica(String caracteristica){
		this.caracteristica = caracteristica;
	}

	String getCaracteristica(){
		return caracteristica;
	} // retorna as características de um determinado peixe;

	void dados(){
		system.out.println("Animal: "+this.animal);
		system.out.println("Comprimento: "+this.comprimento);
		system.out.println("Patas: "+this.patas);
		system.out.println("Cor: "+this.cor);
		system.out.println("Ambiente: "+this.ambiente);
		system.out.println("Velocidade:"+this.velocidade);
		system.out.println("Caracteristica: ", +this.caracteristica);
	}
}