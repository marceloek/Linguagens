class Med{
	String nome;
	double precoVenda;
	Data Validade = new Data;
	Lab Labo = new Lab;
	int qtdEstoque;

	boolean receitaObrigatoria{


	}

	reajustar (double perc){
		System.out.println("Digite a porcentagem que voce deseja alterar: ");
		this.precoVenda = precoVenda*perc;
	}

	vender (int quant){

	}

	comprar (int quant){

	}

	void mostra(){
		System.out.println("Nome do medicamento: ", this.nome);
		System.out.println("Preco de venda: ", this.precoVenda);
		Vadidade();
		Labo();	
		System.out.println("Quatidade em estoque: ", this.qtdEstoque);
	}
}