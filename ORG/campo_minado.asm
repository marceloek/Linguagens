    ##############################################################################
    #####################    Acadêmico: Marcelo Elias Knob   #####################
    ##############################################################################
    
    # TODAS AS VARIÁVEIS UTILIZADAS E OS REGISTRADORES:
    # $a0 = matriz campo                    $s4 = endereço da matriz campo
    # $a1 = num_linhas                      $t0 = coordenada x  
    # $a2 = matriz user                     $t1 = coordenada y
    # $a3 = variável fim de jogo            $t2 = contador de linha (y1)
    # $s0 = contador de bombas              $t3 = contador de coluna (x1)
    # $s1 = posição de referência da matriz $t4 = verificador utilizado no slt
    # $s2 = num_linhas - 1                  $t5 = posição da matriz    
    # $s3 = posição da matriz

        .data
user:                       # matriz visualizada pelo usuário
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
        .word   0,0,0,0,0,0,0,0,0
        .word   0,0,0,0,0,0,0,0,0
        .word   0,0,0,0,0,0,0,0,0
        .word   0,0,0,0,0,0,0,0,0
        .word   0,0,0,0,0,0,0,0,0
        .word   0,0,0,0,0,0,0,0,0
        .word   0,0,0,0,0,0,0,0,0
        .word   0,0,0,0,0,0,0,0,0
        .word   0,0,0,0,0,0,0,0,0

coordena:		.asciiz		"\nDigite as coordenadas do campo minado (coluna/linha):\n"
tam_camp:		.asciiz		"\nDigite o tamanho do campo minado entre 5 (5x5), 7 (7x7) ou 9 (9x9): "
fim_jogo:		.asciiz		"\nA BOMBA EXPLODIU! VOCE PERDEU!\n"
campomin:		.asciiz		"\nVEJA A SITUACAO DO CAMPO MINADO:\n"
coordinv:		.asciiz		"\nA JOGADA ESCOLHIDA EH INVALIDA. TENTE NOVAMENTE!\n"
novalinh:		.asciiz		"\n"
novbarra:		.asciiz		"|"
novespac:		.asciiz		" "
imprnove:		.asciiz		" 9"
taminval:		.asciiz		"\nA ESCOLHA DE TAMANHO DO CAMPO EH INVALIDA. TENTE NOVAMENTE!"

	    .text
main:
        li  $v0, 4              # seta valor de operação para string
        la  $a0, tam_camp       # imprime mensagem para escolher tamanho do campo
        syscall                 # imprime string

        li  $v0, 5		# seta valor de operação para pegar valor digitado pelo usuário	
        syscall                 # pede para digitar tamanho do campo (num_linhas)

        add $a1, $zero, $v0     # salva valor digitado em num_linhas
        beq $a1, 5, else        # verifica se a escolha de tamanho do campo é válida
        beq $a1, 7, else        # verifica se a escolha de tamanho do campo é válida
        beq $a1, 9, else        # verifica se a escolha de tamanho do campo é válida
        li  $v0, 4              # seta valor de operação para string
        la  $a0, taminval       # imprime mensagem de tamanho do campo invalido
        syscall                 # imprime string
        j main                  # volta para main para escolher novamente o tamanho do campo

        else:
        subi $s2, $a1, 1        # num_linhas - 1
        add $a3, $zero, $zero   # seta valor para a variável de controle o fim do jogo

        la $a0, campo           # parâmetro da matriz campo (int * campo[])
        add $a1, $a1, $zero     # parâmetro do tamanho da matriz campo (int num_linhas)
        jal insere_bombas       # chama função para inserir as bombas na matriz campo

        la $a0, campo           # parâmetro da matriz campo (int * campo[])
        add $a1, $a1, $zero     # parâmetro do tamanho da matriz campo (int num_linhas)
        jal calcula_bombas      # chama função para calcular todas as bombas ao redor de todas as posições

        continua_main0:
        la $a0, campo           # parâmetro da matriz campo
        add $a1, $a1, $zero     # parâmetro do tamanho da matriz campo
        la $a2, user            # parâmetro da matriz user
        add $a3, $a3, $zero     # parâmetro da variável de fim de jogo
        jal mostra_campo        # printa campo minado

        continua_main1:
        li  $v0, 4              # seta valor de operação para string
        la  $a0, coordena       # imprime mensagem para inserir posição
        syscall                 # imprime string

        li  $v0, 5              # seta valor de operação para pegar valor digitado pelo usuário
        syscall                 # pede para digitar coordenada coluna (x)
        add $t0, $zero, $v0     # x (colunas)
        subi $t0, $t0, 1        # x-- (colunas)

        li  $v0, 5              # seta valor de operação para pegar valor digitado pelo usuário
        syscall                 # pede para digitar coordenada linha (y)
        add $t1, $zero, $v0     # y (linhas)
        subi $t1, $t1, 1        # y-- (linhas)

        slt $t4, $t0, $a1       # verifica se escolha de coordenada x é maior que o num_linhas
        beq $t4, 1, else1
        li  $v0, 4              # seta valor de operação para string
        la  $a0, coordinv       # imprime mensagem de coordernadas invalidas
        syscall                 # imprime string
        j continua_main1        # volta para continua_main1 para escolher novamente a coordenada da matriz

        else1:
        slt $t4, $t1, $a1       # verifica se escolha de coordenada y é maior que o num_linhas
        beq $t4, 1, else2
        li  $v0, 4              # seta valor de operação para string
        la  $a0, coordinv       # imprime mensagem de coordernadas invalidas
        syscall                 # imprime string
        j continua_main1        # volta para continua_main1 para escolher novamente a coordenada da matriz

        else2:
        slt $t4, $t0, $zero     # verifica se escolha de coordenada x é menor ou igual a 0
        beq $t4, 0, else3
        li  $v0, 4              # seta valor de operação para string
        la  $a0, coordinv       # imprime mensagem de coordernadas invalidas
        syscall                 # imprime string
        j continua_main1        # volta para continua_main1 para escolher novamente a coordenada da matriz

        else3:
        slt $t4, $t1, $zero     # verifica se escolha de coordenada y é menor ou igual a 0
        beq $t4, 0, else4
        li  $v0, 4              # seta valor de operação para string
        la  $a0, coordinv       # imprime mensagem de coordernadas invalidas
        syscall                 # imprime string
        j continua_main1        # volta para continua_main1 para escolher novamente a coordenada da matriz 
        
        else4:
        # variável para controle de posição da matriz:
        mul $s1, $t1, 9         # posição_matriz = y * ordem da matriz (9)
        add $s1, $s1, $t0       # posição_matriz += x
        mul $s1, $s1, 4         # posição_matriz *= 4 (para cálculo da posição)

        lw  $s3, campo($s1)     # salva endereço da posição campo
        sw  $s3, user($s1)      # salva valor de campo[x1][y1] em user[x1][y1]
        # verifica se há bomba na posição digitada pelo usuário para finalizar o jogo
        bne $s3, 9, continua
        addi $a3, $zero, 1      # seta variável de fim de jogo para 1
        li  $v0, 4              # seta valor de operação para string
        la  $a0, fim_jogo       # salva mensagem de fim de jogo
        syscall                 # imprime string
        
        la $a0, campo           # parâmetro da matriz campo (int * campo[])
        add $a1, $a1, $zero     # parâmetro do tamanho da matriz campo (int num_linhas)
        la $a2, user            # parâmetro da matriz user (int * user[])
        add $a3, $a3, $zero     # parâmetro da variável de fim de jogo (int fim_jogo)
        jal mostra_campo        # imprime o campo minado pela ultima vez com as bombas
        j final                 # finaliza o jogo
        
        continua:
        j continua_main0        # continua o jogo printando o campo minado e pedindo outra coordenada

mostra_campo:                   # void mostra_campo(int * campo[], int num_linhas, int * user[], int fim_jogo)
        # essa função imprimirá a matriz user, mas necessita da matriz campo e da variável fim_jogo para saber
        # se será impresso uma bomba ou não
        
        add $s4, $a0, $zero     # salva endereço da matriz campo

        li  $v0, 4              # seta valor de operação para string
        la  $a0, campomin       # imprime mensagem para mostrar campo minado
        syscall                 # imprime string

        add $t2, $zero, $zero   # reseta variável do laço que percorre as linhas

        for:
        addi $t3, $zero, -1     # reseta variável do laço que percorre as colunas; é setado com valor -1 
        # pelo fato de haver um "continue" na função, necessitando de um ++ no início do laço para
        # ignorar a posição da matriz que o chamou e para começar da posição 0 e não da posição 1
        beq $t2, $a1, exit      # verifica fim do for

        for2:
        addi $t3, $t3, 1        # aumenta contador de colunas
        beq $t3, $a1, exit1     # verifica fim do for2

        mul $s1, $t2, 9         # posição_matriz = y1 (linhas) * ordem da matriz (9)
        add $s1, $s1, $t3       # posição_matriz += x1 (colunas)
        mul $s1, $s1, 4         # posição_matriz *= 4 (para cálculo da posição)
        add $s3, $s1, $a2       # calcula endereço da posição da matriz user
        lw  $s3, 0($s3)         # salva posição da matriz user
        add $t5, $s1, $s4       # calcula endereço da matriz campo
        lw  $t5, 0($t5)         # salva posição da matriz campo
        
        # imprime uma barra
        li $v0, 4               # seta valor de operação para string
        la $a0, novbarra        # carrega string
        syscall                 # imprime string
        
        # verifica variável de fim de jogo para saber o que imprimir; se a posição é bomba entao 
        # imprime a bomba e não a posição da matriz user, depois retorna, como um "continue",
        # para o laço continuar a imprimir as demais posições
        bne $a3, 1, if20        
        bne $t5, 9, if20        # verifica se a posição da matriz campo[x1][y1] == 9
        # imprime valor 9
        li $v0, 4               # seta valor de operação para string
        la $a0, imprnove        # carrega string
        syscall                 # imprime string
        j for2                  # volta para for2 porque o valor é bomba

        if20:                   
        # verifica necessidade de imprimir um espaço, servindo como forma de justificacao de impressão 
        # do campo minado, pois "-1" ocupa o espaço de dois char
        beq $s3, -1, if21
        # imprime um espaço
        li $v0, 4               # seta valor de operação para string
        la $a0, novespac        # carrega string
        syscall                 # imprime string

        if21:
        # imprime as posições
        li $v0, 1               # seta valor de operação para integer
        add $a0, $s3, $zero     # salva valor de $s3 em $a0 para ser impresso
        syscall                 # imprime string

        j for2                  # volta para for2
        exit1:
        # imprime uma barra
        li $v0, 4               # seta valor de operação para string
        la $a0, novbarra        # carrega string
        syscall                 # imprime string
        # imprime nova linha
        li $v0, 4               # seta valor de operação para string
        la $a0, novalinh        # carrega string
        syscall                 # imprime string
        addi $t2, $t2, 1        # aumenta contador de linha
        j for                   # volta para for
        exit:
        
        jr $ra

calcula_bombas:                 # void calcula_bombas(int * campo[], int num_linhas);
        add $t2, $zero, $zero   # reseta variável do laço que percorre as linhas

        for10:
        addi $t3, $zero, -1     # reseta variável do laço que percorre as colunas; é setado com valor -1 
        # pelo fato de haver um "continue" na função, necessitando de um ++ no início do laço para
        # ignorar a posição da matriz que o chamou e para começar da posição 0 e não da posição 1
        beq $t2, $a1, fim1      # verifica fim do for10

        for11:
        add $s0, $zero, $zero   # reseta contador de bombas
        addi $t3, $t3, 1        # aumenta contador de colunas
        beq $t3, $a1, fim2      # verifica fim do for11

        mul $s1, $t2, 9         # posição_matriz = y1 (linhas) * ordem da matriz (9)
        add $s1, $s1, $t3       # posição_matriz += x1 (colunas)
        mul $s1, $s1, 4         # posição_matriz *= 4 (para cálculo da posição)

        add $s3, $s1, $a0       # calcula endereço da matriz campo[x1][y1]
        lw  $s3, 0($s3)         # salva posição da matriz

        # verifica se a posição é bomba; se ela for, retorna, como um "continue", para o laço
        # para ignorar essa posição, já que não preciso saber o número de bombas ao redor
        # de uma posição que já é bomba
        bne $s3, 9, if01        # verifica se posição da matriz campo[x1][y1] == 9
        j for11                 # volta para for11 porque o valor é bomba

        if01:

        subi $s3, $s1, 4        # posição_matriz -= 4 (M[x1-1][y1])
        subi $s3, $s3, 36       # posição_matriz -= 36 (M[x1-1][y1-1])
        add $s3, $a0, $s3       # calcula endereço da matriz a ser verificado se o dado é uma bomba
        lw  $s3, 0($s3)         # salva posição da matriz

        beq $t2, 0, if02        # verifica y1 != 0
        beq $t3, 0, if02        # verifica x1 != 0
        bne $s3, 9, if02        # verifica campo[x1 - 1][y1 - 1] == 9
        addi $s0, $s0, 1        # i++

        if02:
        subi $s3, $s1, 36       # posição_matriz -= 36 (M[x1][y1-1])
        add $s3, $s3, $a0       # calcula endereço da matriz a ser verificado se o dado é uma bomba
        lw  $s3, 0($s3)         # salva posição da matriz

        beq $t2, 0, if03        # verifica y1 != 0
        bne $s3, 9, if03        # verifica campo[x1][y1 - 1] == 9
        addi $s0, $s0, 1        # i++

        if03:
        addi $s3, $s1, 4        # posição_matriz += 4 (M[x1+1][y1])
        subi $s3, $s3, 36       # posição_matriz -= 36 (M[x1+1][y1-1])
        add $s3, $s3, $a0       # calcula endereço da matriz a ser verificado se o dado é uma bomba
        lw  $s3, 0($s3)         # salva posição da matriz
        
        beq $t3, $s2, if04      # verifica x1 != num_linhas
        beq $t2, 0, if04        # verifica y1 != 0
        bne $s3, 9, if04        # verifica campo[x1 + 1][y1 - 1] == 9
        addi $s0, $s0, 1        # i++

        if04:
        subi $s3, $s1, 4        # posição_matriz -= 4 (M[x1-1][y1]) 
        add $s3, $s3, $a0       # calcula endereço da matriz a ser verificado se o dado é uma bomba
        lw  $s3, 0($s3)         # salva posição da matriz
        
        beq $t3, 0, if05        # verifica x1 != 0
        bne $s3, 9, if05        # verifica campo[x1 - 1][y1] == 9
        addi $s0, $s0, 1        # i++

        if05:
        addi $s3, $s1, 4        # posição_matriz += 4 (M[x1+1][y1]) 
        add $s3, $s3, $a0       # calcula endereço da matriz a ser verificado se o dado é uma bomba
        lw  $s3, 0($s3)         # salva posição da matriz
        
        beq $t3, $s2, if06      # verifica x1 != num_linhas
        bne $s3, 9, if06        # verifica campo[x1 + 1][y1] == 9
        addi $s0, $s0, 1        # i++

        if06:
        subi $s3, $s1, 4        # posição_matriz -= 4 (M[x1-1][y1])
        addi $s3, $s3, 36       # posição_matriz += 36 (M[x1-1][y1+1])
        add $s3, $s3, $a0       # calcula endereço da matriz a ser verificado se o dado é uma bomba
        lw  $s3, 0($s3)         # salva posição da matriz

        beq $t3, 0, if07        # verifica x1 != 0
        beq $t2, $s2, if07      # verifica y1 != num_linhas
        bne $s3, 9, if07        # verifica campo[x1 - 1][y1 + 1] == 9
        addi $s0, $s0, 1        # i++

        if07:
        addi $s3, $s1, 36       # posição_matriz += 36 (M[x1][y1+1])
        add $s3, $s3, $a0       # calcula endereço da matriz a ser verificado se o dado é uma bomba
        lw  $s3, 0($s3)         # salva posição da matriz
        
        beq $t2, $s2, if08      # verifica y1 != num_linhas
        bne $s3, 9, if08        # verifica campo[x1][y1 + 1] == 9
        addi $s0, $s0, 1        # i++

        if08:
        addi $s3, $s1, 4        # posição_matriz += 4 (M[x1+1][y1])
        addi $s3, $s3, 36       # posição_matriz += 36 (M[x1+1][y1+1])
        add $s3, $s3, $a0       # calcula endereço da matriz a ser verificado se o dado é uma bomba
        lw  $s3, 0($s3)         # salva posição da matriz

        beq $t3, $s2, resume    # verifica se x1 != num_linhas
        beq $t2, $s2, resume    # verifica se y1 != num_linhas
        bne $s3, 9, resume      # verifica se campo[x1 + 1][y1 + 1] == 9
        addi $s0, $s0, 1        # i++

        resume:
        add $s3, $s1, $a0       # calcula endereço da matriz na qual o dado vai ser substituido 
                                # pelo numero de bombas que ha ao seu redor 
        sw  $s0, 0($s3)         # seta o valor de bombas ao redor da posição
        j for11                 # volta para for11

        fim2:
        addi $t2, $t2, 1        # aumenta contador de linhas da matriz
        j for10                 # volta para for10

        fim1:
        jr $ra

insere_bombas:                  # void insere_bombas(int * campo[], int num_linhas);
        # codigo da função insere bombas aqui

        jr $ra

final: