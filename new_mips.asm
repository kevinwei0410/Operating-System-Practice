#a0 = base_address of array
#a1 = lo
#a2 = hi

Qsort:
addi $sp, $sp , -20
sw $ra, 16($sp)		#return address
sw $s0, 12($sp)		#i
sw $s1, 8($sp)		#j
sw $a1, 4($sp)		#lo
sw $a2, 0($sp)		#hi

move $s0, $a1  #$s0 = i,	i = lo
move $s1, $a2  #$s1 = j,	j = hi

add $t0, $s0, $s1 #$t0 =  lo + hi
sll $t0, $t0, 1 #$t0 = (lo + hi)/2 * 4  ,  the result is offset 
add $t0, $a0, $t0 #base_address + offset save to $t0
lw $s2, 0($t0)	#$s2 = x

do_while_loop:
i_loop:
sll $t1, $s0, 2 #get offset of i
add $t1, $a0, $t1 #address = base_address + offset
lw $t2, 0($t1) 	#$t2 = a[i]

slt $t7, $t2, $s2    #a[i] < x
beq $t7, $zero, end_i_loop    #if not match, jump to end_i_loop
addi $s0, $s0, 1    #i++
j i_loop
 end_i_loop:
 
j_loop:
sll $t1, $s1, 2	#get offset of j
add $t1,  $a0, $t1  #address = base_address + offset
lw $t3, 0($t1)	#$t3 = a[j]

slt $t7, $s2, $t3 #a[j] > x
beq $t7, $zero, end_j_loop 	#if not match, jump to end_j_loop
addi $s1, $s1, -1 #j--
j j_loop
end_j_loop:

slt $t7, $s1, $s0 #if j < i , then not going to if scope
bne $t7, $zero, out_if

sll $t1, $s0, 2		#get offset of i
add $t2, $a0, $t1	#$t2 = address of a[i]
lw $s3, 0($t2)		#$s3 = h		 			h = a[i]		--1

sll $t1, $s1, 2		#get offset of j
add $t4, $a0, $t1	#$t4 = address of a[j]
lw $t5, 0($t4)		#$t5 = a[j]								--2

sw $t5, 0($t2)		#load a[j] to the address of a[i],		a[i] = a[j]		--3
sw $s3, 0($t4)		#load h to the address of a[j],		a[j] = h		--4

addi $s0, $s0, 1		#i++
addi $s1, $s1, -1	#j--

out_if:
slt $t1, $s1, $s0 	#i f j < i, then $t1 = 1
beq $t1, $zero,  do_while_loop	#if t1 = 0,then match "if(i <= j )", so we need to do the loop again

#---------------
slt $t1, $a1, $s1	# if lo < j
beq $t1, $zero, out_if_1

lw $a1, 4($sp)	#reload $a1												**
move $a2, $s1	#change the argument $a2  to j,		qsort(a, lo, j)
jal Qsort
out_if_1:

slt $t1, $s0, $a2	# if i < hi
beq $t1, $zero, out_if_2

lw $a2, 0($sp)	#reload $a2												**
move $a1, $s0	#change the argument $a1 to i,		qsort(a, i, hi)
jal Qsort
out_if_2:


lw $a2, 0($sp)		#hi
lw $a1, 4($sp)		#lo
lw $s1, 8($sp)		#j
lw $s0, 12($sp)		#i
lw $ra, 16($sp)		#return address
addi $sp, $sp , 20

jr $ra





#slt != sll															**
