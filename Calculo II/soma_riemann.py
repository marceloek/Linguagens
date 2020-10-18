from scipy.integrate import quad

# valor 'a' da integral
inicio_intervalo = -5

# valor 'b' da integral
fim_intervalo = 12

# numero de pontos que serao utilizados para calcular a integral
num_pontos_plot = 15

# funcao da integral
def function(x):
	return 2*x**4 - 6*x**2 - 9

# calcula distancia do intervalo entre os pontos
delta_x = ((fim_intervalo - inicio_intervalo) / num_pontos_plot)

# variavel e valor inicial para o somatorio
soma_riemann = 0

# valor inicial para o loop do somatorio
ponto = 0

# valor inicial do 'x' somado com o 'ponto medio do delta_x'
x = inicio_intervalo + (delta_x / 2)

# loop para calcular cada area do intervalo e acrescentar ao somatorio
while ponto < num_pontos_plot:
	# calcula valor do y para 'x' ponto
	f = function(x)

	# calcula a area do intervalo do ponto 'x' e acrescenta ao somatorio
	soma_riemann = soma_riemann + f*delta_x
	
	# x passa a ser o proximo valor do intervalo
	x = x + delta_x

	# ponto acrescentado em 1 para continuar o loop
	ponto = ponto + 1

# calculo da integral definida
integral_definida, err = quad(function, -5, 12)

# calculo da diferenca entre a integral definida e a soma de riemann
dif = integral_definida - soma_riemann

# taxa de erro entre a integral definida e a soma de riemann
taxa_erro = (dif / integral_definida) * 100

print('Resultado da área da integral por Somas de Riemann: %.5f' % soma_riemann)
print('Resultado da área da integral por Integral Definida: %.5f' % integral_definida)
print('Diferença (porcentagem de erro): %.5f' % abs(dif) + ' (' '%.3f' % taxa_erro +'%)')

