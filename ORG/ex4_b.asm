            .data
    
    .text
main:
    addi $a3, $zero, 101	# comparador com valor 101
    addi $s0, $zero, 100    # a
    addi $s1, $zero, 10 	# b
    addi $s2, $zero, 100    # c
    addi $s3, $zero, 10	    # d

    div $a0, $s0, $s2       # x0 = a / c
    mul $a1, $s1, $s3       # x1 = b * d
    add $a2, $a0, $a1       # x = x0 + x1
    subi $a2, $a2, 50       # x = x - 50

    slt $t0, $s2, $a3	    # c >= 101
    beq $t0, $zero, if1
    mul $s2, $s2, 5         # c *= 5
    j fim
if1:
    add $s2, $zero, $zero     # c = 0
    j fim

fim: