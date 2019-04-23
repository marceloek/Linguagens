            .data
    
    .text
main:
    addi $a0, $zero, 10		# x tem valor 10
    addi $a1, $zero, 101	# comparador com valor 101
    addi $s0, $zero, 10	# a
    addi $s1, $zero, 100	# b
    addi $s2, $zero, 10	# c

while1:
    slti $t0, $a0, 20	    # x < 20
    beq $t0, $zero, fim1

    mul $s1, $s0, $s2

    slt $t0, $s1, $a1	    # b > 101
    beq $t0, $zero, fim1

    add $s1, $zero, $zero

    j while1

fim1: