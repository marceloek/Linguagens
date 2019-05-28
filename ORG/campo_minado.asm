  .data
user:	                # matriz visualizada pelo usuario
        .word   0,0,0,0,0,0,0,0,0
        .word   0,0,0,0,0,0,0,0,0
        .word   0,0,0,0,0,0,0,0,0
        .word   0,0,0,0,0,0,0,0,0
        .word   0,0,0,0,0,0,0,0,0
        .word   0,0,0,0,0,0,0,0,0
        .word   0,0,0,0,0,0,0,0,0
        .word   0,0,0,0,0,0,0,0,0
        .word   0,0,0,0,0,0,0,0,0
campo:                  # matriz campo inicializada com zeros
        .word   0,9,0,0,0,9,9,0,9
        .word   9,0,0,9,0,9,0,9,0
        .word   0,0,9,0,0,0,0,0,0
        .word   0,0,0,9,0,9,9,0,0
        .word   9,0,0,0,9,0,0,9,0
        .word   0,0,0,0,0,0,0,0,0
        .word   9,0,0,0,0,0,9,0,0
        .word   0,0,9,0,9,0,0,9,0
        .word   9,0,0,0,0,0,0,0,9

coordena:		.asciiz		"\nDigite as coordenadas do campo minado (coluna/linha):\n"
dimensao:		.asciiz		"\nDigite a dificuldade do campo minado entre 5 (5x5), 7 (7x7) ou 9 (9x9): "
fim_jogo:		.asciiz		"\nA BOMBA EXPLODIU! VOCE PERDEU!\n"
localiza:		.asciiz		"\nLOCALIZACAO DAS BOMBAS:\n"
campomin:		.asciiz		"\nVEJA A SITUACAO DO CAMPO MINADO:\n"
novalinh:		.asciiz		"\n"
noespaco:		.asciiz		"|"
difinval:		.asciiz		"\nA DIFICULDADE ESCOLHIDA EH INVALIDA. TENTE NOVAMENTE!"

	.text
main:
    addi $s2, $zero, 0  # variavel para controlar o fim do jogo

    continua_main:
    li  $v0, 4          # seta valor da operacao
    la  $a0, dimensao   # imprime mensagem para escolher dificuldade
    syscall             # imprime string

    li	$v0, 5			
    syscall             # le num_linhas
    add $a1, $zero, $v0 # b = num_linhas
    beq $a1, 5, else    # verifica escolha de dificuldade
    beq $a1, 7, else    # verifica escolha de dificuldade
    beq $a1, 9, else    # verifica escolha de dificuldade
    li  $v0, 4          # seta valor da operacao
    la  $a0, difinval   # imprime mensagem de dificuldade invalida
    syscall             # imprime string
    j continua_main
    else:

    subi $s3, $a1, 1    # num_linhas - 1

    j insere_bombas     # chama funcao para inserir as bombas na matriz campo

    continua_main1:
    # printa matriz
    j mostra_campo

    continua_main2:
    li  $v0, 4          # seta valor da operacao
    la  $a0, coordena   # imprime mensagem para inserir posicao
    syscall             # imprime string

    li	$v0, 5          # seta valor da operacao
    syscall             # le x
    add $t0, $zero, $v0 # x (colunas)
    subi $t0, $t0, 1    # x-- (colunas)

    li	$v0, 5          # seta valor da operacao
    syscall             # le y
    add $t1, $zero, $v0 # y (linhas)
    subi $t1, $t1, 1    # y-- (linhas)

    # variaveis para controle de posicao da matriz:
    mul $s4, $t1, 9     # posicao_matriz = y * dimensao da matriz (9)
    add $s4, $s4, $t0   # posicao_matriz += x
    mul $s4, $s4, 4     # posicao_matriz *= 4 (para calculo da posicao)

    lw  $s1, campo($s4) # le posicao campo
    bne $s1, 9, calcula_bombas
    addi $s2, $zero, 1  # seto fim de jogo
    li  $v0, 4          # seta valor da operacao
    la  $a0, fim_jogo   # salva mensagem de fim de jogo
    syscall             # imprime string

calcula_bombas:
    la $a0, campo       # parametro da matriz campo
    addi $a1, $a1, 0    # parametro da dimensao da matriz campo
    
    addi $s0, $zero, 0  # i (contador de bombas)

    bne $t0, 0, if01    # x == 0

    addi $s1, $s4, 4    # posicao_matriz += 4 (M[x+1][y]) 
    lw  $s1, campo($s1) # le posicao campo
    bne $s1, 9, if05    # M[x+1][y] == 9
    addi $s0, $s0, 1    # i++

    if05:
    bne $t1, 0, if10    # y == 0

    addi $s1, $s4, 36   # posicao_matriz += 36 (M[x][y+1])
    lw  $s1, campo($s1) # le posicao campo
    bne $s1, 9, if40    # M[x][y+1] == 9
    addi $s0, $s0, 1    # i++

    if40:
    addi $s1, $s4, 4    # posicao_matriz += 4 (x+1)
    addi $s1, $s1, 36   # posicao_matriz += 36 (y+1)
    lw  $s1, campo($s1) # le posicao campo 
    bne $s1, 9, resume  # M[x+1][y+1] == 9
    addi $s0, $s0, 1    # i++
    j resume

    if10:
    bne $s3, $t1, if11  # y == b

    subi $s1, $s4, 36   # posicao_matriz -= 36 (M[x][y-1])
    lw  $s1, campo($s1) # le posicao campo
    bne $s1, 9, if41    # M[x][y-1] == 9
    addi $s0, $s0, 1    # i++

    if41:
    addi $s1, $s4, 4    # posicao_matriz += 4 (x+1)
    subi $s1, $s1, 36   # posicao_matriz -= 36 (y-1)
    lw  $s1, campo($s1) # le posicao campo
    bne $s1, 9, resume  # M[x+1][y-1] == 9
    addi $s0, $s0, 1    # i++
    j resume

    if11:
    addi $s1, $s4, 4    # posicao_matriz += 4 (x+1)
    subi $s1, $s1, 36   # posicao_matriz -= 36 (y-1)
    lw  $s1, campo($s1) # le posicao campo
    bne $s1, 9, if42    # M[x+1][y-1] == 9
    addi $s0, $s0, 1    # i++

    if42:
    addi $s1, $s4, 4    # posicao_matriz += 4 (x+1)
    addi $s1, $s1, 36   # posicao_matriz += 36 (y+1)
    lw  $s1, campo($s1) # le posicao campo
    bne $s1, 9, if43    # M[x+1][y+1] == 9
    addi $s0, $s0, 1    # i++

    if43:
    addi $s1, $s4, 36   # posicao_matriz += 36 (M[x][y+1])
    lw  $s1, campo($s1) # le posicao campo
    bne $s1, 9, if12    # M[x][y+1] == 9
    addi $s0, $s0, 1    # i++

    if12:
    subi $s1, $s4, 36   # posicao_matriz -= 36 (M[x][y-1])
    lw  $s1, campo($s1) # le posicao campo
    bne $s1, 9, resume  # M[x][y-1] == 9
    addi $s0, $s0, 1    # i++
    j resume

    if01:
    bne $s3, $t0, if02  # x = b

    subi $s1, $s4, 4    # posicao_matriz -= 4 (M[x-1][y]) 
    lw  $s1, campo($s1) # le posicao campo
    bne $s1, 9, if21    # M[x-1][y] == 9
    addi $s0, $s0, 1    # i++

    if21:
    bne $t1, 0, if22    # y == 0

    addi $s1, $s4, 36   # posicao_matriz += 36 (M[x][y+1])
    lw  $s1, campo($s1) # le posicao campo
    bne $s1, 9, if44    # M[x][y+1] == 9
    addi $s0, $s0, 1    # i++

    if44:
    subi $s1, $s4, 4    # posicao_matriz -= 4 (x-1)
    addi $s1, $s1, 36   # posicao_matriz += 36 (y+1)
    lw  $s1, campo($s1) # le posicao campo
    bne $s1, 9, resume  # M[x-1][y+1] == 9
    addi $s0, $s0, 1    # i++
    j resume

    if22:
    bne $s3, $t1, if46  # y == b

    subi $s1, $s4, 36   # posicao_matriz -= 36 (M[x][y-1])
    lw  $s1, campo($s1) # le posicao campo
    bne $s1, 9, if45    # M[x][y-1] == 9
    addi $s0, $s0, 1    # i++

    if45:
    subi $s1, $s4, 4    # posicao_matriz -= 4 (x-1)
    subi $s1, $s1, 36   # posicao_matriz -= 36 (y-1)
    lw  $s1, campo($s1) # le posicao campo
    bne $s1, 9, resume  # M[x-1][y-1] == 9
    addi $s0, $s0, 1    # i++
    j resume

    if46:
    subi $s1, $s4, 4    # posicao_matriz -= 4 (x-1)
    addi $s1, $s1, 36   # posicao_matriz += 36 (y+1)
    lw  $s1, campo($s1) # le posicao campo
    bne $s1, 9, if47    # M[x-1][y+1] == 9
    addi $s0, $s0, 1    # i++

    if47:
    subi $s1, $s4, 4    # posicao_matriz -= 4 (x-1)
    subi $s1, $s1, 36   # posicao_matriz -= 36 (y-1)
    lw  $s1, campo($s1) # le posicao campo
    bne $s1, 9, if23    # M[x-1][y-1] == 9
    addi $s0, $s0, 1    # i++

    if23:
    addi $s1, $s4, 36   # posicao_matriz += 36 (M[x][y+1])
    lw  $s1, campo($s1) # le posicao campo
    bne $s1, 9, if24    # M[x][y+1] == 9
    addi $s0, $s0, 1    # i++

    if24:
    subi $s1, $s4, 36   # posicao_matriz -= 36 (M[x][y-1])
    lw  $s1, campo($s1) # le posicao campo
    bne $s1, 9, resume  # M[x][y-1] == 9
    addi $s0, $s0, 1    # i++
    j resume

    if02:
    subi $s1, $s4, 4    # posicao_matriz -= 4 (M[x-1][y]) 
    lw  $s1, campo($s1) # le posicao campo
    bne $s1, 9, if31    # M[x-1][y] == 9
    addi $s0, $s0, 1    # i++
   
    if31:
    addi $s1, $s4, 4    # posicao_matriz -= 4 (M[x+1][y]) 
    lw  $s1, campo($s1) # le posicao campo
    bne $s1, 9, if32    # M[x+1][y] == 9
    addi $s0, $s0, 1    # i++
    
    if32:
    bne $t1, 0, if33    # y == 0

    addi $s1, $s4, 36   # posicao_matriz += 36 (M[x][y+1])
    lw  $s1, campo($s1) # le posicao campo
    bne $s1, 9, if48    # M[x][y+1] == 9
    addi $s0, $s0, 1    # i++

    if48:
    subi $s1, $s4, 4    # posicao_matriz -= 4 (x-1)
    addi $s1, $s1, 36   # posicao_matriz += 36 (y+1)
    lw  $s1, campo($s1) # le posicao campo
    bne $s1, 9, if49    # M[x-1][y+1] == 9
    addi $s0, $s0, 1    # i++

    if49:
    addi $s1, $s4, 4    # posicao_matriz += 4 (x+1)
    addi $s1, $s1, 36   # posicao_matriz += 36 (y+1)
    lw  $s1, campo($s1) # le posicao campo
    bne $s1, 9, resume  # M[x+1][y+1] == 9
    addi $s0, $s0, 1    # i++
    j resume

    if33:
    bne $s3, $t1, if34  # y == b

    subi $s1, $s4, 4    # posicao_matriz -= 4 (x-1)
    subi $s1, $s1, 36   # posicao_matriz -= 36 (y-1)
    lw  $s1, campo($s1) # le posicao campo
    bne $s1, 9, if51    # M[x-1][y-1] == 9
    addi $s0, $s0, 1    # i++

    if51:
    addi $s1, $s4, 4    # posicao_matriz += 4 (x+1)
    subi $s1, $s1, 36   # posicao_matriz -= 36 (y-1)
    lw  $s1, campo($s1) # le posicao campo
    bne $s1, 9, if52    # M[x+1][y-1] == 9
    addi $s0, $s0, 1    # i++

    if52:
    subi $s1, $s4, 36   # posicao_matriz -= 36 (M[x][y-1])
    lw  $s1, campo($s1) # le posicao campo
    bne $s1, 9, resume  # M[x][y-1] == 9
    addi $s0, $s0, 1    # i++
    j resume

    if34:
    subi $s1, $s4, 36   # posicao_matriz -= 36 (y-1)
    lw  $s1, campo($s1) # le posicao campo
    bne $s1, 9, if53    # M[x][y-1] == 9
    addi $s0, $s0, 1    # i++

    if53:
    addi $s1, $s4, 36   # posicao_matriz += 36 (y+1)
    lw  $s1, campo($s1) # le posicao campo
    bne $s1, 9, if54    # M[x][y+1] == 9
    addi $s0, $s0, 1    # i++

    if54:
    subi $s1, $s4, 4    # posicao_matriz -= 4 (x-1)
    subi $s1, $s1, 36   # posicao_matriz -= 36 (y-1)
    lw  $s1, campo($s1) # le posicao campo
    bne $s1, 9, if55    # M[x-1][y-1] == 9
    addi $s0, $s0, 1    # i++

    if55:
    subi $s1, $s4, 4    # posicao_matriz -= 4 (x-1)
    addi $s1, $s1, 36   # posicao_matriz += 36 (y+1)
    lw  $s1, campo($s1) # le posicao campo
    bne $s1, 9, if56    # M[x-1][y+1] == 9
    addi $s0, $s0, 1    # i++

    if56:
    addi $s1, $s4, 4    # posicao_matriz += 4 (x+1)
    subi $s1, $s1, 36   # posicao_matriz -= 36 (y-1)
    lw  $s1, campo($s1) # le posicao campo
    bne $s1, 9, if35    # M[x+1][y-1] == 9
    addi $s0, $s0, 1    # i++

    if35:
    addi $s1, $s4, 4    # posicao_matriz += 4 (x+1)
    addi $s1, $s1, 36   # posicao_matriz += 36 (y+1)
    lw  $s1, campo($s1) # le posicao campo
    bne $s1, 9, resume  # M[x+1][y+1] == 9
    addi $s0, $s0, 1    # i++

    resume:
    sw  $s0, user($s4)  # seto o valor de bombas ao redor da posicao

    beq $s2, 1, if99
    j continua_main1
    if99:

mostra_campo:
    la $a0, user        # parametro da matriz user
    la $a0, campo       # parametro da matriz campo
    addi $a1, $a1, 0    # parametro da dimensao da matriz campo

    # comeca a printar a matriz user
    li  $v0, 4          # seta valor da operacao
    la  $a0, campomin   # imprime mensagem para mostrar campo minado
    syscall             # imprime string

    addi $t2, $zero, 0  # zerando variavel do for linha
    addi $t4, $zero, 0  # zerando variavel de adicao de linha

    for:
    beq $t2, $a1, exit  # verifica fim do for
    addi $t3, $zero, 0  # zerando variavel do for coluna

    for2:
    beq $t3, $a1, exit2 # verifica fim do for2

    mul $t5, $t3, 4     # calcula posicao de adicao de coluna
    add $s1, $t5, $t4   # adiciona linha com coluna
    lw  $s1, user($s1)  # salva posicao da matriz

    # printo uma barra
    li $v0, 4
    la $a0, noespaco
    syscall
    # printo as posicoes
    li $v0, 1
    add $a0, $s1, $zero
    syscall

    addi $t3, $t3, 1    # aumento contador de coluna
    j for2              # volta pro for2
    exit2:
    # printo uma barra
    li $v0, 4
    la $a0, noespaco
    syscall
    # printo nova linha
    li $v0, 4
    la $a0, novalinh
    syscall

    addi $t2, $t2, 1    # aumento contador de linha
    mul $t4, $t2, 36    # calcula posicao de adicao da linha
    j for               # volta pro for
    exit:
    
    beq $s2, 1, f_jogo  # termino o jogo e printo a matriz campo
    j continua_main2    # continuo a main

    f_jogo:
    # comeca a printar a matriz campo
    li  $v0, 4          # seta valor da operacao
    la  $a0, localiza   # salva mensagem de localizacao
    syscall             # imprime string

    addi $t2, $zero, 0  # zerando variavel do for linha
    addi $t4, $zero, 0  # zerando variavel de adicao de linha

    for3:
    beq $t2, $a1, exit3 # verifica fim do for3
    addi $t3, $zero, 0  # zerando variavel do for coluna

    for4:
    beq $t3, $a1, exit4 # verifica fim do for4

    mul $t5, $t3, 4     # calcula posicao de adicao de coluna
    add $s1, $t5, $t4   # adiciona linha com coluna
    lw  $s1, campo($s1) # salva posicao da matriz

    # printo uma barra
    li $v0, 4
    la $a0, noespaco
    syscall
    # printo as posicoes
    li $v0, 1
    add $a0, $s1, $zero
    syscall

    addi $t3, $t3, 1    # aumento contador de coluna
    j for4              # volta pro for4
    exit4:
    # printo uma barra
    li $v0, 4
    la $a0, noespaco
    syscall
    # printo nova linha
    li $v0, 4
    la $a0, novalinh
    syscall

    addi $t2, $t2, 1    # aumento contador de linha
    mul $t4, $t2, 36    # calcula posicao de adicao da linha
    j for3              # volta pro for3
    exit3:

    j final             # termino o programa

insere_bombas:
    # codigo da funcao insere bombas aqui
    la $a0, campo       # parametro da matriz campo
    addi $a1, $a1, 0    # parametro da dimensao da matriz campo

    j continua_main1

final: