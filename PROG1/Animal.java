public class Animal{
	private String nome;
	private int comprimento;
	private String cor;
	private String ambiente;
	private double velocidade;
	private int patas;

	public Animal(String nome, String cor, String ambiente, int comprimento, double velocidade, int patas){
		setNome(nome);
		setCor(cor);
		setAmbiente(ambiente);
		setComprimento(comprimento);
		setVelocidade(velocidade);
		setPatas(patas);
	}

	void setNome(String nome){
		this.nome = nome;
	}

	void setComprimento(int comprimento){
		this.comprimento = comprimento;
	}

	void setPatas(int patas){
		this.patas = patas;
	}

	void setCor(String cor){
		this.cor = cor;
	}

	void setAmbiente(String ambiente){
		this.ambiente = ambiente;
	}

	void setVelocidade(float velocidade){
		this.velocidade = velocidade;
	}

	void dados(){
		system.out.println("Animal: "+this.animal);
		system.out.println("Comprimento: "+this.comprimento);
		system.out.println("Patas: "+this.patas);
		system.out.println("Cor: "+this.cor);
		system.out.println("Ambiente: "+this.ambiente);
		system.out.println("Velocidade:"+this.velocidade);
	}
}