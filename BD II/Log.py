import csv

arq_list = []
redo = []
undo = []
letras = []

c = 0
i = 0
aux1 = 1
aux2 = 1

with open('teste03') as f:
	for line in csv.reader(f):
		arq_list.append(line)

arq_list.reverse()
converte_lista = [item for lista in arq_list for item in lista]

for line in converte_lista:
	line = line.replace(">","")
	line = line.replace("("," ")
	line = line.replace(")","")
	linha = list(line.split(' ', 1))
	linha2 = list(line.split(' ', 2))
	if 'End' in line:
		aux2 = 0
	if '<Start' in line:
		if aux2 == 0:
			aux1 == 0
		if linha2[2] in redo:
			pass
		elif linha2[2] in undo:
			pass
		else:
			print(linha2)
			undo.append(linha2[2])
	if aux1 == 0:
		pass
	else:
		if '<commit' in line:
			redo.append(linha[1])
		if '<start' in line:
			if linha[1] in redo:
				pass
			elif linha[1] in undo:
				pass
			else:
				undo.append(linha[1])

for line in converte_lista:
	linha2 = list(line.split(' ', 2))
	if line[:2] == '<T':
		variavel = converte_lista[i+1]
		if variavel not in letras:
			letras.append(variavel)
			c +=1
	i += 1

i=0
letras.sort()
valores = [0]*c

for line in converte_lista:
	if line[:2] == '<T':
		line = line.replace("<","")
		valor_antigo = converte_lista[i+2]
		x = letras.index(converte_lista[i+1])
		if line in undo:
			valores[x] = valor_antigo.replace(">","")
	i += 1

arq_list.reverse()
converte_lista = [item for lista in arq_list for item in lista]

i=0

for line in converte_lista:
	if line[:2] == '<T':
		line = line.replace("<","")
		valor_novo = converte_lista[i+3]
		x = letras.index(converte_lista[i+1])
		if line in redo:
			valores[x] = valor_novo.replace(">","")
	i += 1

print('Transacoes que fazem redo:')
print(redo)
print('\nTransacoes que fazem undo:')
print(undo)
print('\nValor final de cada variavel:')
print(letras)
print(valores)