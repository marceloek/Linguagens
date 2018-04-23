import java.util.*;

public class testeAnimal{
	public static void main(String[] args){
		Mamifero Camelo = new Mamifero("Camelo", "Amarelo", "Terra", 150, 2, 4);
		Peixe Tubarao = new Peixe("Tubarão", "Cinzento", "Mar", 300, 1.5, 0, "Barbatanas e cauda");
		Mamifero UrsoCan = new Mamifero("Camelo", "Amarelo", "Terra", 150, 2, 4, "Mel");
		Camelo.dados();
		Tubarão.dados();
		UrsoCan.dados();
	}
}