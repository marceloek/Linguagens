            .data
    
    .text
main:
    addi $a0, $zero, 4		# a0 é o valor do fatorial
    add $a1, $a0, $zero	    # a1 é o valor do fatorial
    addi $a2, $zero, 1      # a2 para comparar o fim da recursao

fatorial:
    subi $a1, $a1, 1        # a1--
    beq $a1, $a2, if1       # a1 == 1
    mul $a0, $a0, $a1       # a0 = a0 * a1
    j fatorial              # faz recursao

if1: