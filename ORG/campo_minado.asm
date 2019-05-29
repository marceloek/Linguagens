    ##############################################################################
    #####################    Academico: Marcelo Elias Knob   #####################
    ##############################################################################
    
    # TODAS AS VARIAVEIS UTILIZADAS E OS REGISTRADORES:
    # $a0 = matriz campo                    $s3 = posicao da matriz
    # $a1 = num_linhas                      $t0 = coordenada x  
    # $a2 = matriz user                     $t1 = coordenada y
    # $a3 = variavel fim de jogo            $t2 = contador de linha 
    # $s0 = contador de bombas              $t3 = contador de coluna
    # $s1 = posicao de referencia da matriz $t4 = verificador slt
    # $s2 = num_linhas - 1                  $t5 = posicao da matriz              

        .data
user:                       # matriz visualizada pelo usuario
        .word   -1,-1,-1,-1,-1,-1,-1,-1,-1
        .word   -1,-1,-1,-1,-1,-1,-1,-1,-1
        .word   -1,-1,-1,-1,-1,-1,-1,-1,-1
        .word   -1,-1,-1,-1,-1,-1,-1,-1,-1
        .word   -1,-1,-1,-1,-1,-1,-1,-1,-1
        .word   -1,-1,-1,-1,-1,-1,-1,-1,-1
        .word   -1,-1,-1,-1,-1,-1,-1,-1,-1
        .word   -1,-1,-1,-1,-1,-1,-1,-1,-1
        .word   -1,-1,-1,-1,-1,-1,-1,-1,-1
campo:                      # matriz campo inicializada com zeros
        .word   0,9,0,0,0,9,9,0,9
        .word   9,0,0,9,0,9,0,9,0
        .word   0,0,9,0,0,0,0,0,0
        .word   0,0,0,9,0,9,9,0,0
        .word   9,0,0,0,9,0,0,9,0
        .word   0,0,0,0,0,0,0,0,0
        .word   9,0,0,0,0,9,9,0,0
        .word   0,0,9,0,9,0,0,9,0
        .word   0,0,0,0,0,0,0,0,0

coordena:		.asciiz		"\nDigite as coordenadas do campo minado (coluna/linha):\n"
dimensao:		.asciiz		"\nDigite a dificuldade do campo minado entre 5 (5x5), 7 (7x7) ou 9 (9x9): "
fim_jogo:		.asciiz		"\nA BOMBA EXPLODIU! VOCE PERDEU!\n"
campomin:		.asciiz		"\nVEJA A SITUACAO DO CAMPO MINADO:\n"
coordinv:		.asciiz		"\nA COORDENADA ESCOLHIDA EH INVALIDA. TENTE NOVAMENTE!"
novalinh:		.asciiz		"\n"
novbarra:		.asciiz		"|"
novespac:		.asciiz		" "
imprnove:		.asciiz		" 9"
difinval:		.asciiz		"\nA DIFICULDADE ESCOLHIDA EH INVALIDA. TENTE NOVAMENTE!"

	    .text
main:
        addi $a3, $zero, 0      # variavel para controlar o fim do jogo

        continua_main00:
        li  $v0, 4              # seta valor da operacao
        la  $a0, dimensao       # imprime mensagem para escolher dificuldade
        syscall                 # imprime string

        li	$v0, 5			
        syscall                 # le num_linhas
        add $a1, $zero, $v0     # b = num_linhas
        beq $a1, 5, else        # verifica escolha de dificuldade
        beq $a1, 7, else        # verifica escolha de dificuldade
        beq $a1, 9, else        # verifica escolha de dificuldade
        li  $v0, 4              # seta valor da operacao
        la  $a0, difinval       # imprime mensagem de dificuldade invalida
        syscall                 # imprime string
        j continua_main00
        else:

        subi $s2, $a1, 1        # num_linhas - 1

        j insere_bombas         # chama funcao para inserir as bombas na matriz campo

        continua_main01:

        j calcula_bombas        # chama funcao para calcular todas as bombas ao redor de todas as posicoes

        continua_main10:

        j mostra_campo          # printa campo minado

        continua_main11:
        li  $v0, 4              # seta valor da operacao
        la  $a0, coordena       # imprime mensagem para inserir posicao
        syscall                 # imprime string

        li	$v0, 5              # seta valor da operacao
        syscall                 # le x
        add $t0, $zero, $v0     # x (colunas)
        subi $t0, $t0, 1        # x-- (colunas)

        li	$v0, 5              # seta valor da operacao
        syscall                 # le y
        add $t1, $zero, $v0     # y (linhas)
        subi $t1, $t1, 1        # y-- (linhas)

        slt $t4, $t0, $a1        # verifica escolha de coordenada
        beq $t4, 1, else1
        li  $v0, 4              # seta valor da operacao
        la  $a0, coordinv       # imprime mensagem de coordernadas invalidas
        syscall                 # imprime string
        j continua_main11

        else1:
        slt $t4, $t1, $a1        # verifica escolha de coordenada
        beq $t4, 1, else2
        li  $v0, 4              # seta valor da operacao
        la  $a0, coordinv       # imprime mensagem de coordernadas invalidas
        syscall                 # imprime string
        j continua_main11

        else2:
        slti $t4, $t0, 0        # verifica escolha de coordenada
        beq $t4, 0, else3
        li  $v0, 4              # seta valor da operacao
        la  $a0, coordinv       # imprime mensagem de coordernadas invalidas
        syscall                 # imprime string
        j continua_main11

        else3:
        slti $t4, $t1, 0        # verifica escolha de coordenada
        beq $t4, 0, else4
        li  $v0, 4              # seta valor da operacao
        la  $a0, coordinv       # imprime mensagem de coordernadas invalidas
        syscall                 # imprime string
        j continua_main11
        
        else4:

        # variaveis para controle de posicao da matriz:
        mul $s1, $t1, 9         # posicao_matriz = y * dimensao da matriz (9)
        add $s1, $s1, $t0       # posicao_matriz += x
        mul $s1, $s1, 4         # posicao_matriz *= 4 (para calculo da posicao)

        # verifico se ha bomba na posicao digitada pelo usuario para finalizar o jogo
        lw  $t5, campo($s1)     # le posicao campo
        sw  $t5, user($s1)      # salvo valor de campo[x][y] em user[x][y]
        bne $t5, 9, mostra_campo
        addi $a3, $zero, 1      # seto fim de jogo
        li  $v0, 4              # seta valor da operacao
        la  $a0, fim_jogo       # salva mensagem de fim de jogo
        syscall                 # imprime string

mostra_campo:
        la $a0, campo           # parametro da matriz campo
        addi $a1, $a1, 0        # parametro da dimensao da matriz campo
        la $a2, user            # parametro da matriz user
        addi $a3, $a3, 0        # parametro da variavel de fim de jogo

        # comeca a printar a matriz user
        li  $v0, 4              # seta valor da operacao
        la  $a0, campomin       # imprime mensagem para mostrar campo minado
        syscall                 # imprime string

        addi $t2, $zero, 0      # resetando variavel do for linha

        for:
        addi $t3, $zero, -1     # resetando variavel do for coluna
        beq $t2, $a1, exit      # verifica fim do for

        for2:
        addi $t3, $t3, 1        # aumento contador de coluna
        beq $t3, $a1, exit1     # verifica fim do for2

        mul $s1, $t2, 9         # posicao_matriz = y * dimensao da matriz (9)
        add $s1, $s1, $t3       # posicao_matriz += x
        mul $s1, $s1, 4         # posicao_matriz *= 4 (para calculo da posicao)
        lw  $s3, user($s1)      # salva posicao da matriz user
        lw  $t5, campo($s1)     # salva posicao da matriz campo
        
        # imprime uma barra
        li $v0, 4
        la $a0, novbarra
        syscall

        bne $a3, 1, if20        # verifica variavel de fim de jogo para saber o que imprimir
        bne $t5, 9, if20        # verifica posicao da matriz campo se é igual a 9
        # imprime valor 9
        li $v0, 4
        la $a0, imprnove
        syscall
        j for2                  # volta pro for2 porque o valor é bomba

        if20:                   # verifica necessidade de imprimir espaco
        beq $s3, -1, if21
        # imprime um espaco
        li $v0, 4
        la $a0, novespac
        syscall

        if21:
        # imprime as posicoes
        li $v0, 1
        add $a0, $s3, $zero
        syscall

        j for2                  # volta pro for2
        exit1:
        # imprime uma barra
        li $v0, 4
        la $a0, novbarra
        syscall
        # imprime nova linha
        li $v0, 4
        la $a0, novalinh
        syscall
        addi $t2, $t2, 1        # aumenta contador de linha
        j for                   # volta pro for
        exit:
        
        beq $a3, 1, final       # termina o jogo, senao continua o jogo
        j continua_main11       # continua o jogo e volta para main11

calcula_bombas:
        la $a0, campo           # parametro da matriz campo
        addi $a1, $a1, 0        # parametro da dimensao da matriz campo

        addi $t2, $zero, 0      # resetando variavel do for linha

        for10:
        addi $t3, $zero, -1     # resetando variavel do for coluna
        beq $t2, $a1, fim1      # verifica fim do for

        for11:
        addi $s0, $zero, 0      # resetando contador de bombas
        addi $t3, $t3, 1        # aumento contador de coluna
        beq $t3, $a1, fim2      # verifica fim do for11

        mul $s1, $t2, 9         # posicao_matriz = y * dimensao da matriz (9)
        add $s1, $s1, $t3       # posicao_matriz += x
        mul $s1, $s1, 4         # posicao_matriz *= 4 (para calculo da posicao)

        lw  $s3, campo($s1)     # salva posicao da matriz

        bne $s3, 9, if01        # verifica posicao da matriz se é igual a 9
        j for11                 # volta pro for11

        if01:

        subi $s3, $s1, 4        # posicao_matriz -= 4 (M[x-1][y])
        subi $s3, $s3, 36       # posicao_matriz -= 36 (M[x-1][y-1])
        lw  $s3, campo($s3)     # le posicao campo

        beq $t2, 0, if02        # verifica y != 0
        beq $t3, 0, if02        # verifica x != 0
        bne $s1, 9, if02        # verifica campo[x - 1][y - 1] == 9
        addi $s0, $s0, 1        # i++

        if02:
        subi $s3, $s1, 4        # posicao_matriz -= 4 (M[x-1][y]) 
        lw  $s3, campo($s3)     # le posicao campo
        
        beq $t3, 0, if03        # verifica y != 0
        bne $s3, 9, if03        # verifica campo[x - 1][y] == 9
        addi $s0, $s0, 1        # i++

        if03:
        subi $s3, $s1, 4        # posicao_matriz -= 4 (M[x-1][y])
        addi $s3, $s3, 36       # posicao_matriz += 36 (M[x-1][y+1])
        lw  $s3, campo($s3)     # le posicao campo

        beq $t3, 0, if04        # verifica y != 0
        beq $t2, $s2, if04      # verifica x != num_linhas
        bne $s3, 9, if04        # verifica campo[x - 1][y + 1] == 9
        addi $s0, $s0, 1        # i++

        if04:
        subi $s3, $s1, 36       # posicao_matriz -= 36 (M[x][y-1])
        lw  $s3, campo($s3)     # le posicao campo

        beq $t2, 0, if05        # verifica x != 0
        bne $s3, 9, if05        # verifica campo[x][y - 1] == 9
        addi $s0, $s0, 1        # i++

        if05:
        addi $s3, $s1, 36       # posicao_matriz += 36 (M[x][y+1])
        lw  $s3, campo($s3)     # le posicao campo
        
        beq $t2, $s2, if06      # verifica x != num_linhas
        bne $s3, 9, if06        # verifica campo[x][y + 1] == 9
        addi $s0, $s0, 1        # i++

        if06:
        addi $s3, $s1, 4        # posicao_matriz += 4 (M[x+1][y])
        subi $s3, $s3, 36       # posicao_matriz -= 36 (M[x+1][y-1])
        lw  $s3, campo($s3)     # le posicao campo
        
        beq $t3, $s2, if07      # verifica y != num_linhas
        beq $t2, 0, if07        # verifica x != 0
        bne $s3, 9, if07        # verifica campo[x + 1][y - 1] == 9
        addi $s0, $s0, 1        # i++

        if07:
        addi $s3, $s1, 4        # posicao_matriz += 4 (M[x+1][y]) 
        lw  $s3, campo($s3)     # le posicao campo
        
        beq $t3, $s2, if08      # verifica y != num_linhas
        bne $s3, 9, if08        # verifica campo[x + 1][y] == 9
        addi $s0, $s0, 1        # i++

        if08:
        addi $s3, $s1, 4        # posicao_matriz += 4 (M[x+1][y])
        addi $s3, $s3, 36       # posicao_matriz += 36 (M[x+1][y+1])
        lw  $s3, campo($s3)     # le posicao campo

        beq $t3, $s2, resume    # verifica y != num_linhas
        beq $t2, $s2, resume    # verifica x != 0
        bne $s3, 9, resume      # verifica campo[x + 1][y + 1] == 9
        addi $s0, $s0, 1        # i++

        resume:

        sw  $s0, campo($s1)      # seto o valor de bombas ao redor da posicao
 
        j for11                 # volta pro for11 porque o valor é bomba

        fim2:

        addi $t2, $t2, 1        # aumenta contador de linha
        j for10                 # volta pro for10

        fim1:
        j continua_main10

insere_bombas:
        # codigo da funcao insere bombas aqui
        la $a0, campo           # parametro da matriz campo
        addi $a1, $a1, 0        # parametro da dimensao da matriz campo

        j continua_main01       # volta para main01

final:
