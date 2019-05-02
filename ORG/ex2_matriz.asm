    .data
matriz_A:	.word   1,5,2,9 
            .word   2,4,4,6
            .word   9,0,9,9
            .word   2,9,5,8
            .word   2,9,9,2
            .word   1,1,1,1

	.text
    la $s1, matriz_A
    addi $a0, $zero, 0  # x
    addi $a1, $zero, 0  # y
    addi $a2, $zero, 4  # dimx
    addi $a3, $zero, 6  # dimy
    addi $s0, $zero, 0  # i
    mul $s4, $a1, $a2   # indice_vetor = y * dimx 
    add $s4, $s4, $a0   # indice_vetor += x (M[x][y])
    mul $s4, $s4, 4     # indice_vetor = indice_vetor * 4

main:
    bne $a0, 0, if1     # x == 0

    addi $s2, $s4, 4    # indice_vetor += 4 (M[x+1][y]) 
    add $s2, $s2, $s1   # calcula posicao matriz_A[x][y]
    lw  $s1, 0($s2)     # le posicao matriz_A[x][y]

    bne $s1, 9, if99    # M[x+1][y] == 9
    addi $s0, $s0, 1    # i++

if99:
    bne $a1, 0, if2     # y == 0

    addi $s3, $a3, 4    # y + 1 = 4 * dimx
    add $s2, $s4, $s3   # indice_vetor += y + 1 (M[x][y+1])
    add $s2, $s2, $s1   # calcula posicao matriz_A[x][y]
    lw  $s1, 0($s2)     # le posicao matriz_A[x][y]
    
    bne $s1, 9, if9     # M[x][y+1] == 9
    addi $s0, $s0, 1    # i++


    addi $s3, $a3, 4    # y + 1 = 4 * dimx
    add $s2, $s4, $s3   # indice_vetor += y + 1 (M[x][y+1])
    add $s2, $s2, $s1   # calcula posicao matriz_A[x][y]
    lw  $s1, 0($s2)     # le posicao matriz_A[x][y]

    bne $a1, 0, if2     # y == b-1
    bne $s1, 9, if9     # M[x][y-1] == 9
    addi $s0, $s0, 1    # i++
    j if2

 if1:

    addi $s3, $a3, 4    # y + 1 = 4 * dimx
    add $s2, $s4, $s3   # indice_vetor += y + 1 (M[x][y+1])
    add $s2, $s2, $s1   # calcula posicao matriz_A[x][y]
    lw  $s1, 0($s2)     # le posicao matriz_A[x][y]

    bne $s1, 9, if9     # M[x][y-1] == 9
    addi $s0, $s0, 1    # i++ 
    j fim


    addi $s3, $a3, 4    # y + 1 = 4 * dimx
    add $s2, $s4, $s3   # indice_vetor += y + 1 (M[x][y+1])
    add $s2, $s2, $s1   # calcula posicao matriz_A[x][y]
    lw  $s1, 0($s2)     # le posicao matriz_A[x][y]

    bne $s1, 9, if9     # M[x][y+1] == 9
    addi $s0, $s0, 1    # i++ 
    j fim



if2:
    addi $s3, $a3, 4    # y + 1 = 4 * dimx
    add $s2, $s4, $s3   # indice_vetor += y + 1 (M[x][y+1])
    add $s2, $s2, $s1   # calcula posicao matriz_A[x][y]
    lw  $s1, 0($s2)     # le posicao matriz_A[x][y]


if3:
    sd