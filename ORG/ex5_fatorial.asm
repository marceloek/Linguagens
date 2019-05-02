    .data
    
    .text
main:
    addi $a0, $zero, 4		# a0 = n = 4
    subi $a1, $a0, 1	    # a1 = n - 1

fatorial:
    beq $a1, 1, if1         # a1 == 1
    mul $a0, $a0, $a1       # a0 = a0 * a1
    subi $a1, $a1, 1        # n-1
    j fatorial              # faz recursao

if1: