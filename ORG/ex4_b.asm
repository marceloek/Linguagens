    .data
    
    .text
main:
    addi $s0, $zero, 100    # a
    addi $s1, $zero, 10     # b
    addi $s2, $zero, 10     # c
    addi $s3, $zero, 10     # d

    div $a0, $s0, $s2       # x0 = a / c
    mul $a1, $s1, $s3       # x1 = b * d
    add $a1, $a0, $a1       # x1 = x0 + x1
    subi $a1, $a1, 50       # x1 = x1 - 50
    mul $s2, $a0, 10        # c = x * 10

    slti $t0, $s2, 101	    # c > 100
    bne $t0, $zero, if1
    add $s2, $zero, $zero   # c = 0
    j fim

if1:
    mul $s2, $s2, 5         # c *= 5

fim: