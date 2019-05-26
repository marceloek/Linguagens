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
        .word   0,0,0,0,0,0,0,0,9
        .word   0,0,0,0,0,0,0,0,0
        .word   0,0,0,0,0,0,0,0,0
        .word   0,0,0,0,0,0,0,0,0
        .word   0,0,0,0,9,0,0,0,0
        .word   0,0,0,0,0,0,0,0,0
        .word   0,0,0,0,0,0,0,0,0
        .word   0,0,0,0,0,0,0,0,0
        .word   0,0,0,0,0,0,0,0,0

coordena:		.asciiz		"\nDigite as coordenadas do campo minado: "
dimensao:		.asciiz		"\nDigite a dificuldade do campo minado, exemplo: 5 = 5x5, 7 = 7x7 ou 9 = 9x9: "
fim_jogo:		.asciiz		"\nA BOMBA EXPLODIU! VOCE PERDEU!\n"
localiza:		.asciiz		"\nLOCALIZACAO DAS BOMBAS:\n"

	.text
main:
    addi $s6, $zero, 0  # variavel para controlar o fim do jogo

    la $a0, campo       # salva matriz campo

    addi $a1, $zero, 5  # b = num_linhas

    # variaveis para controle de posicao da matriz:
    mul $s4, $t1, $a1   # posicao_matriz = y * num_linhas
    add $s4, $s4, $t0   # posicao_matriz += x
    mul $s4, $s4, 4     # posicao_matriz *= 4 (para calculo da posicao 
    mul $s3, $a1, 4     # 4 * num_linhas (para localizacao da posicao da linha anterior ou posterior ((y+1) ou (y-1)) )
    
    continua_main1:

    # printa matriz
    j mostra_campo

    continua_main2:

	li  $v0, 5
	la  $s7, coordena   # imprime mensagem para inserir posicao

    addi $t0, $zero, 0  # x (colunas)
    addi $t1, $zero, 0  # y (linhas)


    add $s1, $s4, $a0   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo

    bne $s1, 9, calcula_bombas
    addi $s6, $zero, 1  # seto fim de jogo
	li  $v0, 5
	la  $s7, fim_jogo   # salva mensagem de fim de jogo
    syscall             # imprime string


calcula_bombas:

    addi $s0, $zero, 0  # i (contador de bombas)

    bne $t0, 0, if01    # x == 0

    addi $s1, $s4, 4    # posicao_matriz += 4 (M[x+1][y]) 
    add $s1, $s1, $a0   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo

    bne $s1, 9, if05    # M[x+1][y] == 9
    addi $s0, $s0, 1    # i++

    if05:
    bne $t1, 0, if10    # y == 0

    add $s1, $s4, $s3   # posicao_matriz += y + 1 (M[x][y+1])
    add $s1, $s1, $a0   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo
    
    bne $s1, 9, if40    # M[x][y+1] == 9
    addi $s0, $s0, 1    # i++

    if40:
    addi $s1, $s4, 4    # posicao_matriz += 4 (x+1)
    add $s1, $s1, $s3   # posicao_matriz += 4*num_linhas (y+1)
    add $s1, $a0, $s1   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo
    
    bne $s1, 9, mostra_campo   # M[x+1][y+1] == 9
    addi $s0, $s0, 1    # i++
    j mostra_campo

    if10:
    bne $a1, $t1, if11  # y == b

    sub $s1, $s4, $s3   # posicao_matriz -= 4*num_linhas (M[x][y-1])
    add $s1, $a0, $s1   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo

    bne $s1, 9, if41    # M[x][y-1] == 9
    addi $s0, $s0, 1    # i++

    if41:
    addi $s1, $s4, 4    # posicao_matriz += 4 (x+1)
    sub $s1, $s1, $s3   # posicao_matriz -= 4*num_linhas (y-1)
    add $s1, $a0, $s1   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo

    bne $s1, 9, mostra_campo   # M[x+1][y-1] == 9
    addi $s0, $s0, 1    # i++
    j mostra_campo

    if11:
    addi $s1, $s4, 4    # posicao_matriz += 4 (x+1)
    sub $s1, $s1, $s3   # posicao_matriz -= 4*num_linhas (y-1)
    add $s1, $a0, $s1   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo

    bne $s1, 9, if42    # M[x+1][y-1] == 9
    addi $s0, $s0, 1    # i++

    if42:
    addi $s1, $s4, 4    # posicao_matriz += 4 (x+1)
    add $s1, $s1, $s3   # posicao_matriz += 4*num_linhas (y+1)
    add $s1, $a0, $s1   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo
    
    bne $s1, 9, if43    # M[x+1][y+1] == 9
    addi $s0, $s0, 1    # i++

    if43:
    add $s1, $s4, $s3   # posicao_matriz += y + 1 (M[x][y+1])
    add $s1, $s1, $a0   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo
    
    bne $s1, 9, if12    # M[x][y+1] == 9
    addi $s0, $s0, 1    # i++

    if12:
    sub $s1, $s4, $s3   # posicao_matriz -= 4*num_linhas (M[x][y-1])
    add $s1, $s1, $a0   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo

    bne $s1, 9, mostra_campo   # M[x][y-1] == 9
    addi $s0, $s0, 1    # i++
    j mostra_campo

    if01:
    subi $s5, $a1, 1    # num_linhas-1
    bne $a1, $t0, if02  # x = num_linhas - 1

    subi $s1, $s4, 4    # posicao_matriz -= 4 (M[x-1][y]) 
    add $s1, $s1, $a0   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo

    bne $s1, 9, if21    # M[x-1][y] == 9
    addi $s0, $s0, 1    # i++

    if21:
    bne $t1, 0, if22    # y == 0

    add $s1, $s4, $s3   # posicao_matriz += y + 1 (M[x][y+1])
    add $s1, $s1, $a0   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo
    
    bne $s1, 9, if44    # M[x][y+1] == 9
    addi $s0, $s0, 1    # i++

    if44:
    subi $s1, $s4, 4    # posicao_matriz -= 4 (x-1)
    add $s1, $s1, $s3   # posicao_matriz += 4*num_linhas (y+1)
    add $s1, $a0, $s1   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo
    
    bne $s1, 9, mostra_campo   # M[x-1][y+1] == 9
    addi $s0, $s0, 1    # i++
    j mostra_campo

    if22:
    bne $a1, $t1, if46  # y == b

    sub $s1, $s4, $s3   # posicao_matriz -= 4*num_linhas (M[x][y-1])
    add $s1, $s1, $a0   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo

    bne $s1, 9, if45    # M[x][y-1] == 9
    addi $s0, $s0, 1    # i++

    if45:
    subi $s1, $s4, 4    # posicao_matriz -= 4 (x-1)
    sub $s1, $s1, $s3   # posicao_matriz -= 4*num_linhas (y-1)
    add $s1, $a0, $s1   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo

    bne $s1, 9, mostra_campo   # M[x-1][y-1] == 9
    addi $s0, $s0, 1    # i++
    j mostra_campo

    if46:
    subi $s1, $s4, 4    # posicao_matriz -= 4 (x-1)
    add $s1, $s1, $s3   # posicao_matriz += 4*num_linhas (y+1)
    add $s1, $a0, $s1   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo
    
    bne $s1, 9, if47    # M[x-1][y+1] == 9
    addi $s0, $s0, 1    # i++

    if47:
    subi $s1, $s4, 4    # posicao_matriz -= 4 (x-1)
    sub $s1, $s1, $s3   # posicao_matriz -= 4*num_linhas (y-1)
    add $s1, $a0, $s1   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo
    
    bne $s1, 9, if23    # M[x-1][y-1] == 9
    addi $s0, $s0, 1    # i++

    if23:
    add $s1, $s4, $s3   # posicao_matriz += y + 1 (M[x][y+1])
    add $s1, $s1, $a0   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo
    
    bne $s1, 9, if24    # M[x][y+1] == 9
    addi $s0, $s0, 1    # i++

    if24:
    sub $s1, $s4, $s3   # posicao_matriz -= 4*num_linhas (M[x][y-1])
    add $s1, $s1, $a0   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo

    bne $s1, 9, mostra_campo   # M[x][y-1] == 9
    addi $s0, $s0, 1    # i++
    j mostra_campo

    if02:
    subi $s1, $s4, 4    # posicao_matriz -= 4 (M[x-1][y]) 
    add $s1, $s1, $a0   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo

    bne $s1, 9, if31    # M[x-1][y] == 9
    addi $s0, $s0, 1    # i++
   
    if31:
    addi $s1, $s4, 4    # posicao_matriz -= 4 (M[x+1][y]) 
    add $s1, $s1, $a0   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo

    bne $s1, 9, if32    # M[x+1][y] == 9
    addi $s0, $s0, 1    # i++
    
    if32:
    bne $t1, 0, if33    # y == 0

    add $s1, $s4, $s3   # posicao_matriz += y + 1 (M[x][y+1])
    add $s1, $s1, $a0   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo
    
    bne $s1, 9, if48    # M[x][y+1] == 9
    addi $s0, $s0, 1    # i++

    if48:
    subi $s1, $s4, 4    # posicao_matriz -= 4 (x-1)
    add $s1, $s1, $s3   # posicao_matriz += 4*num_linhas (y+1)
    add $s1, $a0, $s1   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo
    
    bne $s1, 9, if49    # M[x-1][y+1] == 9
    addi $s0, $s0, 1    # i++

    if49:
    addi $s1, $s4, 4    # posicao_matriz += 4 (x+1)
    add $s1, $s1, $s3   # posicao_matriz += 4*num_linhas (y+1)
    add $s1, $a0, $s1   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo
    
    bne $s1, 9, mostra_campo    # M[x+1][y+1] == 9
    addi $s0, $s0, 1    # i++
    j mostra_campo

    if33:
    bne $a1, $t1, if34   # y == b

    subi $s1, $s4, 4    # posicao_matriz -= 4 (x-1)
    sub $s1, $s1, $s3   # posicao_matriz -= 4*num_linhas (y-1)
    add $s1, $a0, $s1   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo

    bne $s1, 9, if51    # M[x-1][y-1] == 9
    addi $s0, $s0, 1    # i++

    if51:
    addi $s1, $s4, 4    # posicao_matriz += 4 (x+1)
    sub $s1, $s1, $s3   # posicao_matriz -= 4*num_linhas (y-1)
    add $s1, $a0, $s1   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo

    bne $s1, 9, if52    # M[x+1][y-1] == 9
    addi $s0, $s0, 1    # i++

    if52:
    sub $s1, $s4, $s3   # posicao_matriz -= 4*num_linhas (M[x][y-1])
    add $s1, $s1, $a0   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo

    bne $s1, 9, mostra_campo    # M[x][y-1] == 9
    addi $s0, $s0, 1    # i++
    j mostra_campo

    if34:
    sub $s1, $s4, $s3   # posicao_matriz -= 4*num_linhas (y-1)
    add $s1, $s1, $a0   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo
    
    bne $s1, 9, if53    # M[x][y-1] == 9
    addi $s0, $s0, 1    # i++

    if53:
    add $s1, $s4, $s3   # posicao_matriz += 4*num_linhas (y+1)
    add $s1, $s1, $a0   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo
    
    bne $s1, 9, if54    # M[x][y+1] == 9
    addi $s0, $s0, 1    # i++

    if54:
    subi $s1, $s4, 4    # posicao_matriz -= 4 (x-1)
    sub $s1, $s1, $s3   # posicao_matriz -= 4*num_linhas (y-1)
    add $s1, $a0, $s1   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo
    
    bne $s1, 9, if55    # M[x-1][y-1] == 9
    addi $s0, $s0, 1    # i++

    if55:
    subi $s1, $s4, 4    # posicao_matriz -= 4 (x-1)
    add $s1, $s1, $s3   # posicao_matriz += 4*num_linhas (y+1)
    add $s1, $a0, $s1   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo
    
    bne $s1, 9, if56    # M[x-1][y+1] == 9
    addi $s0, $s0, 1    # i++

    if56:
    addi $s1, $s4, 4    # posicao_matriz += 4 (x+1)
    sub $s1, $s1, $s3   # posicao_matriz -= 4*num_linhas (y-1)
    add $s1, $a0, $s1   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo
    
    bne $s1, 9, if35    # M[x+1][y-1] == 9
    addi $s0, $s0, 1    # i++

    if35:
    addi $s1, $s4, 4    # posicao_matriz += 4 (x+1)
    add $s1, $s1, $s3   # posicao_matriz += 4*num_linhas (y+1)
    add $s1, $a0, $s1   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo

    beq $s1, 9, resume  # M[x+1][y+1] == 9
    addi $s0, $s0, 1    # i++

    resume:
    
    add $s1, $s4, $a0   # calcula posicao campo
    lw  $s1, 0($s1)     # le posicao campo
    add $s1, $s0, $zero # seto o valor de bombas ao redor da posicao


    beq $s6, 1, if99
    j continua_main1

    if99:
    j mostra_campo

mostra_campo:
    # comeca a printar a matriz

    beq $s6, 1, explodiu
    j continua_main2

    explodiu:
    
	li  $v0, 5
	la  $s7, localiza   # salva mensagem de localizacao
    syscall             # imprime string