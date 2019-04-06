            .data
vector_A:	.word	  31, 5, -2, 5, -10, 11, 30, 7, 0, -6

	.text
main:
	la $a0, vector_A   		# a0 armazena vetor[10]
    addi $a1, $zero, 10
    addi	$s0, $zero, -99			# a = 99
    addi	$s1, $zero, 99			# b = -99
    add	$s2, $zero, $zero			# z = 0
#int a = 99;
#int b = -99;
#int x;
#int vetor[10];
#for(x=0;x<10;x++){
    #if(a > vetor[x])
   #     a = vetor[x];
  #  if(b < vetor[x])
 #       b = vetor[x];
#}

teste: slti $t0, $s2, 10		# testa condiçao de final de laço
	beq  $t0, $zero, fim
	sll  $t1, $s2, 2		# multilica x por 4
	add  $t3, $a0, $t1		# calcula posiçao A[x]
	lw   $t2, 0($t3)		# le A[x]

	slt $t0, $s0, $t2
	beq $t0, $zero, maior
	add $s0, $t2, $zero
maior:
	slt $t0, $t2, $s1
	beq $t0, $zero, menor
	add $s1, $t2, $zero
menor:
	addi $s2, $s2, 1		# x = x + 1
	
	j    teste			# desvia para o teste
	
fim: 
    
