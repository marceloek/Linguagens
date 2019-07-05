def get_():
    list = []
    while True:
        a = input()
        if a == '':
            break
        list.append(a)
    return list

def add_token(A, token):
    p = 0
    for i in token:
        prod = A[p]
        if prod != '':
            prod += ' '
        prod += i + '<' + str(len(A)) + '>' 
        A[p] = prod
        p = len(A)
        A.append('<'+ str(p) + '> ::=')
    A[len(A)-1] += ' eps'
    return A

def add_er(A, er):
    for i in er:
        p = ''
        for j in i:
            p+= j
            if j == 'S':
                p+= '\''
        if i[1] == 'S':
            prod = A[0]
            prod += p[8:]
            A[0] = prod
        A.append(p)
    return A

def get_prod(p, prod):
    for i in range(len(prod)):
        if prod[i][0] == p:
            return prod[i]
    return []

def get_sf(A):
    sf = []
    for i in A:
        for j in i[2:]:
            if j == 'eps' or j == '|':
                continue
            if j[0] not in sf: 
                sf.append(j[0])
    return sf

def create_p(len_sf):
    p = []
    for i in range(len_sf):
        p.append('')
    return p

def fixup_p(prod):
    for i in range(len(prod)):
        if prod[i] == '':
            prod[i] = '-'
        if ' ' in prod[i]:
            p = '-'
            for j in sorted(prod[i]):
                if j == ' ':
                    continue
                p += j
            prod[i] = p
    return prod

def clear_p(prod):
    p = ''
    for i in prod:
        if i == ' ':
            continue
        p += i
    return p

def check_prod(prod, p, test):
    i = '<'
    if test:
        i += '-'
    p = i + p + '>'
    return p in prod

def error_p(n):
    error = ['<->']
    error_p = []
    for i in range(n):
        error_p.append('-')
    error.append(error_p)
    return error

def find_p(producoes_p, producao, A, sf):
    ignore = ['eps', '|', '::=']
    producao = get_prod(producao, A)
    for i in producao[1:]:
        if i in ignore:
            continue
        indice_p = sf.index(i[0])
        if len(i) > 2 and i[2:-1] in producoes_p[indice_p]:
            continue
        if producoes_p[indice_p] != '':
            producoes_p[indice_p] += ' '
        if len(i) == 1:
            producoes_p[indice_p] += '*'
        else:
            producoes_p[indice_p] += i[2:-1]
    return producoes_p

def find_new_p(producoes_p, fila, prod):
    for i in producoes_p:
        if i == '' or i == '*':
            continue
        if ' ' in i:
            j = True
        else:
            j = False
        if not check_prod(prod, i, j):
            fila.insert(0, i)
    return fila


def determinizacao(A):
    sf = sorted(get_sf(A))
    fila = []
    afd = []
    producoes_AFD = []
    for i in A:
        producoes_AFD.append(i[0])
    for i in A:
        producao = [i[0]]
        if 'eps' in i:
            producao.insert(0, '*')
        producoes_p = create_p(len(sf))
        producoes_p = find_p(producoes_p, i[0], A, sf)
        fila = find_new_p(producoes_p, fila, producoes_AFD)
        producao.append(fixup_p(producoes_p))
        afd.append(producao)
    while fila != []:
        p = fila.pop()
        p_split = p.split()
        p = clear_p(sorted(p))
        if check_prod(producoes_AFD, p, True):
            continue
        p = '<-' + p + '>'
        producoes_AFD.append(p)
        producao = [p]
        producoes_p = create_p(len(sf))
        for i in p_split:
            prod_i = get_prod('<' + i + '>', A)
            if 'eps' in prod_i and '*' not in producao:
                producao.insert(0, '*')
            producoes_p = find_p(producoes_p, '<' + i + '>', A, sf)
        fila = find_new_p(producoes_p, fila, producoes_AFD)
        producao.append(fixup_p(producoes_p))
        afd.append(producao)
    
    afd.append(error_p(len(sf)))
    return afd


def print_afd(AFD, A):
    sf = sorted(get_sf(A))
    for i in AFD:
        p = ''
        if '*' in i:
            p+= i[1]
            producoes = i[2]
            eps = True
        else:
            p+= i[0]
            eps = False
            producoes = i[1]
        p += ' ::= '
        for i in range(len(producoes)):
            flag = True
            p += sf[i] + '<' + producoes[i] + '>'
            if i < len(producoes) - 1 or eps:
                p+= ' | '
        if eps:
            p+= 'eps'
        print(p)


tokens = get_()
er = get_()
A = []
A.append('<S> ::=')
for i in tokens:
    A = add_token(A, i)
A = add_er(A, er)
for i in range(len(A)):
    A[i] = A[i].split()  
AFD = determinizacao(A)
print_afd(AFD, A)