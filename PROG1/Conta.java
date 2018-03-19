

class Conta{
	int numero;
	String dono;
	double saldo;

void saca(double valor){
	this.saldo -= valor;
}

void deposita(double valor){
	this.saldo += valor;
}
}
