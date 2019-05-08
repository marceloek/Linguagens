-- Acadêmico: Marcelo Elias Knob

CREATE OR REPLACE FUNCTION salario() RETURNS TRIGGER AS $$
DECLARE
	maxi decimal(10,2);
	mini decimal(10,2);
BEGIN
	select max(salario) into maxi from empregado;
	select min(salario) into mini from empregado;
	if NEW.salario > maxi then
		RAISE EXCEPTION '% esta acima do limite máximo permitido', NEW.salario;
		RETURN NULL;
	end if;
	if NEW.salario < mini then
		RAISE EXCEPTION '% esta abaixo do limite minimo permitido', NEW.salario;
		RETURN NULL;
	end if;
	RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER insere_empregado before INSERT ON empregado FOR EACH ROW EXECUTE PROCEDURE salario();