import csv

arq_list = []
redo = []
undo = []
letras = {}
c = 0

with open('teste03') as f:
	for line in csv.reader(f):
		arq_list.append(line)

arq_list.reverse()
convert_list = [item for lista in arq_list for item in lista]

for bb in convert_list:
	kk = bb
	kk = kk.replace(">","")
	if '<commit' in kk:
		lista1 = list(kk.split(' ', 2))
		redo.append(lista1[1])
	if '<start' in kk:
		lista2 = list(kk.split(' ', 2))
		if lista2[1] in redo:
			pass
		else:
			undo.append(lista2[1])
	if '<CKPT' in kk:
		c = 1
  
arq_list.reverse()
convert_list = [item for lista in arq_list for item in lista]

i=0

for bb in convert_list:
	kk = bb
	kk = kk.replace("<","")
	if 'commit' in kk:
		pass
	else:
		if kk[:1] == 'T':
			if kk in undo:
				letras[convert_list[i+1]] = convert_list[i+2].replace(">","")
	i = i+1

i=0

for bb in convert_list:
	kk = bb
	kk = kk.replace("<","")
	if 'commit' in kk:
		pass
	else:
		if kk[:1] == 'T':
			if kk in redo:
				letras[convert_list[i+1]] = convert_list[i+3].replace(">","")
	i = i+1

print(redo)
print(undo)
print(letras)