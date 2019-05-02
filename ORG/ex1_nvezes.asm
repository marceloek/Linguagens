    .data
vector_A:	.word   31, 5, -2, 5, -15, 11, 30, 7, 0, -6
vector_B:   .space	40

	.text
main:
	la $a0, vector_A   		# a0 armazena vetor1[10]
	addi $a1, $zero, 10		# a1 armazena tamanho do vetor
	la $a2, vector_B   		# a2 armazena vetor2
	add	$s0, $zero, $zero	# x = 0
	add	$s1, $zero, $zero	# z = 0

forx:  
	slt $t0, $s0, $a1		# testa condiçao de final de forx
	beq  $t0, $zero, fimx	# termina forx
	
	add $s2, $zero, $zero	# count = 0

	sll  $t1, $s0, 2		# multilica x por 4
	add  $t2, $a0, $t1		# calcula posiçao vetor1[x]
	lw   $t3, 0($t2)		# le vetor1[x]

forz: 
	slt $t0, $s1, $a1		# testa condiçao de final de forz
	beq  $t0, $zero, fimz	# termina forz

	sll  $t4, $s1, 2		# multilica z por 4
	add  $t6, $a0, $t4		# calcula posiçao vetor1[z]
	lw   $t5, 0($t6)		# le vetor1[z]

	bne $t3, $t5, if1		# if(vetor1[x] == vetor1[z])
	addi $s2, $s2, 1		# count++
	
if1:
	addi $s1, $s1, 1		# z++
	j forz

fimz:
	add	$s1, $zero, $zero	# z = 0

	add  $s4, $a2, $t1		# calcula posiçao vetor2[x]
	lw   $s5, 0($s4)		# le vetor2[x]
	add $s5, $zero, $s2		# vetor2[x] = count;
	sw	$s5, 0($s4)			# salva valor no vetor2

	addi $s0, $s0, 1		# x++
	j forx					
fimx: