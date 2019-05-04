    .data
matriz_A:	
        .word   9,3,9,9 
        .word   9,9,9,1
        .word   9,9,9,9
        .word   9,1,5,9
        .word   9,9,1,9
        .word   9,3,9,9

	.text
    la $s1, matriz_A
    addi $a0, $zero, 0  # x (colunas)
    addi $a1, $zero, 3  # y (linhas)
    addi $a2, $zero, 4  # dimx (colunas da matriz)
    addi $a3, $zero, 6  # dimy (linhas da matriz)
    addi $s0, $zero, 0  # i (contador de 9)
    mul $s4, $a1, $a2   # indice_vetor = y * dimx 
    add $s4, $s4, $a0   # indice_vetor += x (M[x][y])
    mul $s4, $s4, 4     # indice_vetor = indice_vetor * 4
    mul $s3, $a2, 4     # 4 * dimx

main:
    bne $a0, 0, if01    # x == 0

    addi $s2, $s4, 4    # indice_vetor += 4 (M[x+1][y]) 
    add $s2, $s2, $s1   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]

    bne $s2, 9, if05    # M[x+1][y] == 9
    addi $s0, $s0, 1    # i++

if05:
    bne $a1, 0, if10    # y == 0

    add $s2, $s4, $s3   # indice_vetor += y + 1 (M[x][y+1])
    add $s2, $s2, $s1   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]
    
    bne $s2, 9, if40    # M[x][y+1] == 9
    addi $s0, $s0, 1    # i++

if40:
    addi $s2, $s4, 4    # indice_vetor += 4 (x+1)
    add $s2, $s2, $s3   # indice_vetor += 4*dimx (y+1)
    add $s2, $s1, $s2   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]
    
    bne $s2, 9, final   # M[x+1][y+1] == 9
    addi $s0, $s0, 1    # i++
    j final

if10:
    subi $s5, $a3, 1    # y = b-1
    bne $s5, $a1, if11  # y == b-1

    sub $s2, $s4, $s3   # indice_vetor -= 4*dimx (M[x][y-1])
    add $s2, $s1, $s2   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]

    bne $s2, 9, if41    # M[x][y-1] == 9
    addi $s0, $s0, 1    # i++

if41:
    addi $s2, $s4, 4    # indice_vetor += 4 (x+1)
    sub $s2, $s2, $s3   # indice_vetor -= 4*dimx (y-1)
    add $s2, $s1, $s2   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]

    bne $s2, 9, final   # M[x+1][y-1] == 9
    addi $s0, $s0, 1    # i++
    j final

 if11:
    addi $s2, $s4, 4    # indice_vetor += 4 (x+1)
    sub $s2, $s2, $s3   # indice_vetor -= 4*dimx (y-1)
    add $s2, $s1, $s2   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]

    bne $s2, 9, if42    # M[x+1][y-1] == 9
    addi $s0, $s0, 1    # i++

if42:
    addi $s2, $s4, 4    # indice_vetor += 4 (x+1)
    add $s2, $s2, $s3   # indice_vetor += 4*dimx (y+1)
    add $s2, $s1, $s2   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]
    
    bne $s2, 9, if43    # M[x+1][y+1] == 9
    addi $s0, $s0, 1    # i++

if43:
    add $s2, $s4, $s3   # indice_vetor += y + 1 (M[x][y+1])
    add $s2, $s2, $s1   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]
    
    bne $s2, 9, if12    # M[x][y+1] == 9
    addi $s0, $s0, 1    # i++

if12:
    sub $s2, $s4, $s3   # indice_vetor -= 4*dimx (M[x][y-1])
    add $s2, $s2, $s1   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]

    bne $s2, 9, final   # M[x][y-1] == 9
    addi $s0, $s0, 1    # i++
    j final

if01:
    subi $s5, $a2, 1    # dimx-1
    bne $s5, $a0, if02  # x = dimx - 1

    subi $s2, $s4, 4    # indice_vetor -= 4 (M[x-1][y]) 
    add $s2, $s2, $s1   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]

    bne $s2, 9, if21    # M[x-1][y] == 9
    addi $s0, $s0, 1    # i++

if21:
    bne $a1, 0, if22    # y == 0

    add $s2, $s4, $s3   # indice_vetor += y + 1 (M[x][y+1])
    add $s2, $s2, $s1   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]
    
    bne $s2, 9, if44    # M[x][y+1] == 9
    addi $s0, $s0, 1    # i++

if44:
    subi $s2, $s4, 4    # indice_vetor -= 4 (x-1)
    add $s2, $s2, $s3   # indice_vetor += 4*dimx (y+1)
    add $s2, $s1, $s2   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]
    
    bne $s2, 9, final   # M[x-1][y+1] == 9
    addi $s0, $s0, 1    # i++
    j final

if22:
    subi $s5, $a3, 1    # y = b-1
    bne $s5, $a1, if46  # y == b-1

    sub $s2, $s4, $s3   # indice_vetor -= 4*dimx (M[x][y-1])
    add $s2, $s2, $s1   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]

    bne $s2, 9, if45    # M[x][y-1] == 9
    addi $s0, $s0, 1    # i++

if45:
    subi $s2, $s4, 4    # indice_vetor -= 4 (x-1)
    sub $s2, $s2, $s3   # indice_vetor -= 4*dimx (y-1)
    add $s2, $s1, $s2   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]

    bne $s2, 9, final   # M[x-1][y-1] == 9
    addi $s0, $s0, 1    # i++
    j final

if46:
    subi $s2, $s4, 4    # indice_vetor -= 4 (x-1)
    add $s2, $s2, $s3   # indice_vetor += 4*dimx (y+1)
    add $s2, $s1, $s2   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]
    
    bne $s2, 9, if47    # M[x-1][y+1] == 9
    addi $s0, $s0, 1    # i++

if47:
    subi $s2, $s4, 4    # indice_vetor -= 4 (x-1)
    sub $s2, $s2, $s3   # indice_vetor -= 4*dimx (y-1)
    add $s2, $s1, $s2   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]
    
    bne $s2, 9, if23    # M[x-1][y-1] == 9
    addi $s0, $s0, 1    # i++

if23:
    add $s2, $s4, $s3   # indice_vetor += y + 1 (M[x][y+1])
    add $s2, $s2, $s1   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]
    
    bne $s2, 9, if24    # M[x][y+1] == 9
    addi $s0, $s0, 1    # i++

if24:
    sub $s2, $s4, $s3   # indice_vetor -= 4*dimx (M[x][y-1])
    add $s2, $s2, $s1   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]

    bne $s2, 9, final   # M[x][y-1] == 9
    addi $s0, $s0, 1    # i++
    j final

if02:
    subi $s2, $s4, 4    # indice_vetor -= 4 (M[x-1][y]) 
    add $s2, $s2, $s1   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]

    bne $s2, 9, if31    # M[x-1][y] == 9
    addi $s0, $s0, 1    # i++
   
if31:
    addi $s2, $s4, 8    # indice_vetor -= 4 (M[x+1][y]) 
    add $s2, $s2, $s1   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]

    bne $s2, 9, if32    # M[x+1][y] == 9
    addi $s0, $s0, 1    # i++
    
if32:
    bne $a1, 0, if33    # y == 0

    add $s2, $s4, $s3   # indice_vetor += y + 1 (M[x][y+1])
    add $s2, $s2, $s1   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]
    
    bne $s2, 9, if48    # M[x][y+1] == 9
    addi $s0, $s0, 1    # i++

if48:
    subi $s2, $s4, 4    # indice_vetor -= 4 (x-1)
    add $s2, $s2, $s3   # indice_vetor += 4*dimx (y+1)
    add $s2, $s1, $s2   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]
    
    bne $s2, 9, if49    # M[x-1][y+1] == 9
    addi $s0, $s0, 1    # i++

if49:
    addi $s2, $s4, 4    # indice_vetor += 4 (x+1)
    add $s2, $s2, $s3   # indice_vetor += 4*dimx (y+1)
    add $s2, $s1, $s2   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]
    
    bne $s2, 9, final    # M[x+1][y+1] == 9
    addi $s0, $s0, 1    # i++
    j final

if33:
    subi $s5, $a3, 1    # y = b-1
    bne $s5, $a1, if34    # y == b-1

    subi $s2, $s4, 4    # indice_vetor -= 4 (x-1)
    sub $s2, $s2, $s3   # indice_vetor -= 4*dimx (y-1)
    add $s2, $s1, $s2   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]

    bne $s2, 9, if51    # M[x-1][y-1] == 9
    addi $s0, $s0, 1    # i++

if51:
    addi $s2, $s4, 4    # indice_vetor += 4 (x+1)
    sub $s2, $s2, $s3   # indice_vetor -= 4*dimx (y-1)
    add $s2, $s1, $s2   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]

    bne $s2, 9, if52    # M[x+1][y-1] == 9
    addi $s0, $s0, 1    # i++

if52:
    sub $s2, $s4, $s3   # indice_vetor -= 4*dimx (M[x][y-1])
    add $s2, $s2, $s1   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]

    bne $s2, 9, final    # M[x][y-1] == 9
    addi $s0, $s0, 1    # i++
    j final

if34:
    sub $s2, $s4, $s3   # indice_vetor -= 4*dimx (y-1)
    add $s2, $s2, $s1   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]
    
    bne $s2, 9, if53    # M[x][y-1] == 9
    addi $s0, $s0, 1    # i++

if53:
    add $s2, $s4, $s3   # indice_vetor += 4*dimx (y+1)
    add $s2, $s2, $s1   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]
    
    bne $s2, 9, if54    # M[x][y+1] == 9
    addi $s0, $s0, 1    # i++

if54:
    subi $s2, $s4, 4    # indice_vetor -= 4 (x-1)
    sub $s2, $s2, $s3   # indice_vetor -= 4*dimx (y-1)
    add $s2, $s1, $s2   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]
    
    bne $s2, 9, if55    # M[x-1][y-1] == 9
    addi $s0, $s0, 1    # i++

if55:
    subi $s2, $s4, 4    # indice_vetor -= 4 (x-1)
    add $s2, $s2, $s3   # indice_vetor += 4*dimx (y+1)
    add $s2, $s1, $s2   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]
    
    bne $s2, 9, if56    # M[x-1][y+1] == 9
    addi $s0, $s0, 1    # i++

if56:
    addi $s2, $s4, 4    # indice_vetor += 4 (x+1)
    sub $s2, $s2, $s3   # indice_vetor -= 4*dimx (y-1)
    add $s2, $s1, $s2   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]
    
    bne $s2, 9, if35    # M[x+1][y-1] == 9
    addi $s0, $s0, 1    # i++

if35:
    addi $s2, $s4, 4    # indice_vetor += 4 (x+1)
    add $s2, $s2, $s3   # indice_vetor += 4*dimx (y+1)
    add $s2, $s1, $s2   # calcula posicao matriz_A[x][y]
    lw  $s2, 0($s2)     # le posicao matriz_A[x][y]

    bne $s2, 9, final   # M[x+1][y+1] == 9
    addi $s0, $s0, 1    # i++

final: