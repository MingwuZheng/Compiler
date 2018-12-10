.data
    $string0: .asciiz "#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ !"
    $string1: .asciiz "test of comp symbol"
    $string2: .asciiz "a==b"
    $string3: .asciiz "a<b"
    $string4: .asciiz "c>a"
    $string5: .asciiz "d"
    $string6: .asciiz "error"
    $string7: .asciiz "a<=c"
    $string8: .asciiz "error!"
    $string9: .asciiz "test global variable and constance"
    $string10: .asciiz "before change para="
    $string11: .asciiz "after change para="
    $string12: .asciiz "test for expression"
    $string13: .asciiz "--12--12--12-+12+-12--12--12--12--12="
    $string14: .asciiz "10*-5="
    $string15: .asciiz "10/+4="
    $string16: .asciiz "fib(12)-fib(14)="
    $string17: .asciiz "c + 12 = "
    $string18: .asciiz "c*12/1="
    $string19: .asciiz "1-(((12+1)))="
    $string20: .asciiz "arr[1]*'b'+fib(3)="
    $string21: .asciiz "addone(g_v_char_h)+add(1, fib(5))/G_v_int_a1 - tag[6]="
    $string22: .asciiz "please input an integer"
    $string23: .asciiz "please input 2 integers press enter for each integer"
    $string24: .asciiz " "
    $string25: .asciiz "input the number of fib you want(1~10)"
    $string26: .asciiz "this is a permutation of ABCDE"
.text
    sub $sp,$sp,188
    move $fp,$sp
    sub $fp,$fp,120
    j main

foo1:

lw $s0,132($sp)
lw $s1,128($sp)
add $t0,$s0,$s1
move $v0,$t0
jr $ra
jr $ra

add:

lw $s0,132($sp)
lw $s1,128($sp)
add $t0,$s0,$s1
move $v0,$t0
jr $ra
jr $ra

addchar:

lw $s0,132($sp)
lw $s1,128($sp)
add $t0,$s0,$s1
move $v0,$t0
jr $ra
jr $ra

addone:

lw $s0,128($sp)
addi $t0,$s0,1
move $v0,$t0
jr $ra
jr $ra

addint:

lw $s0,128($sp)
addi $t0,$s0,1
move $v0,$t0
jr $ra
jr $ra

foo2:

lw $s0,128($sp)
li $t9,99
ble $s0,$t9,$LABEL1
li $t9,47
move $v0,$t9
jr $ra
j $LABEL2
$LABEL1:
li $t9,42
move $v0,$t9
jr $ra
$LABEL2:
jr $ra

test_string_int:

li $t0,1
li $v0,1
move $a0,$t0
syscall
li $t0,0
li $v0,1
move $a0,$t0
syscall
li $t0,0
li $v0,1
move $a0,$t0
syscall
li $t1,0
move $t0,$t1
li $v0,1
move $a0,$t0
syscall
li $t0,12
li $v0,1
move $a0,$t0
syscall
li $t2,-12
move $t0,$t2
li $v0,1
move $a0,$t0
syscall
li $v0,4
la $a0,$string0
syscall
jr $ra
jr $ra

fib:

lw $s0,128($sp)
li $t9,1
bne $s0,$t9,$LABEL3
li $t9,1
move $v0,$t9
jr $ra
j $LABEL4
$LABEL3:
li $t9,2
bne $s0,$t9,$LABEL5
li $t9,1
move $v0,$t9
jr $ra
$LABEL5:
$LABEL6:
$LABEL4:
li $t9,1
sub $t0,$s0,$t9

sw $t0,-4($fp)
sw $8,-40($fp)
sw $16,-72($fp)
sw $ra,-132($fp)
sub $sp,$fp,132
sub $fp,$sp,28
jal fib
lw $8,92($sp)
lw $16,60($sp)
lw $ra,0($sp)
add $fp,$fp,160
add $sp,$sp,160
move $t1,$v0

li $t9,2
sub $t2,$s0,$t9

sw $t2,-4($fp)
sw $8,-40($fp)
sw $9,-44($fp)
sw $10,-48($fp)
sw $16,-72($fp)
sw $ra,-132($fp)
sub $sp,$fp,132
sub $fp,$sp,28
jal fib
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $16,60($sp)
lw $ra,0($sp)
add $fp,$fp,160
add $sp,$sp,160
move $t3,$v0

add $t4,$t1,$t3
move $v0,$t4
jr $ra
jr $ra

test_lots_paras:

lw $s0,144($sp)
lw $s1,140($sp)
lw $s2,136($sp)
lw $s3,132($sp)
lw $s4,128($sp)
add $t0,$s0,$s1
add $t1,$t0,$s2
sub $t2,$t1,$s3
add $t3,$t2,$s4
move $v0,$t3
jr $ra
jr $ra

test_all_cond:

li $s0,1
li $s1,2
li $s2,2
li $s3,65
li $v0,4
la $a0,$string1
syscall
bne $s1,$s2,$LABEL7
li $v0,4
la $a0,$string2
syscall
$LABEL7:
$LABEL8:
bge $s0,$s1,$LABEL9
li $v0,4
la $a0,$string3
syscall
$LABEL9:
$LABEL10:
ble $s2,$s0,$LABEL11
li $v0,4
la $a0,$string4
syscall
$LABEL11:
$LABEL12:
li $t9,0
beq $s3,$t9,$LABEL13
li $v0,4
la $a0,$string5
syscall
$LABEL13:
$LABEL14:
li $t9,1
bne $s0,$t9,$LABEL15
li $v0,4
la $a0,$string6
syscall
$LABEL15:
$LABEL16:
li $t9,1
beq $s0,$t9,$LABEL17
li $v0,4
la $a0,$string6
syscall
$LABEL17:
$LABEL18:
bgt $s0,$s2,$LABEL19
li $v0,4
la $a0,$string7
syscall
$LABEL19:
$LABEL20:
blt $s0,$s2,$LABEL21
li $v0,4
la $a0,$string8
syscall
$LABEL21:
$LABEL22:
li $t9,66
ble $s3,$t9,$LABEL23
li $v0,4
la $a0,$string8
syscall
$LABEL23:
$LABEL24:
jr $ra
jr $ra

test_diff_domain:

lw $s0,136($sp)
li $v0,11
li $t9,98
move $a0,$t9
syscall
li $t0,222
sw $t0,128($sp)
li $v0,1
move $a0,$t0
syscall
li $v0,4
la $a0,$string9
syscall
li $v0,1
li $t9,1
move $a0,$t9
syscall
li $v0,11
li $t9,102
move $a0,$t9
syscall
li $v0,11
li $t9,98
move $a0,$t9
syscall
li $v0,11
li $t9,98
move $a0,$t9
syscall
li $v0,1
li $t9,2
move $a0,$t9
syscall
li $v0,1
li $t9,3
move $a0,$t9
syscall
add $v1,$gp,76
li $t9,72
sw $t9,8($v1)
add $v1,$gp,76
lw $t1,8($v1)
li $v0,11
move $a0,$t1
syscall
add $v1,$gp,28
li $t9,155
sw $t9,24($v1)
add $v1,$gp,28
lw $t2,24($v1)
li $v0,1
move $a0,$t2
syscall
li $v0,4
la $a0,$string10
syscall
li $v0,1
move $a0,$s0
syscall
li $t9,2
mul $t3,$s0,$t9
move $s0,$t3
li $v0,4
la $a0,$string11
syscall
li $v0,1
move $a0,$s0
syscall
li $t9,89
sw $t9,72($gp)
li $v0,11
lw $t9,72($gp)
move $a0,$t9
syscall
jr $ra

test_expr:

li $v0,4
la $a0,$string12
syscall
li $t0,12
li $t9,-12
sub $t1,$t0,$t9
li $t9,-12
sub $t2,$t1,$t9
li $t9,12
sub $t3,$t2,$t9
addi $t4,$t3,-12
li $t9,-12
sub $t5,$t4,$t9
li $t9,-12
sub $t6,$t5,$t9
li $t9,-12
sub $t7,$t6,$t9
li $t9,-12
sub $t8,$t7,$t9
sw $t0,-4($sp)
move $t0,$t8
li $v0,4
la $a0,$string13
syscall
li $v0,1
move $a0,$t0
syscall
sw $t1,-8($sp)
li $t1,-50
move $t0,$t1
li $v0,4
la $a0,$string14
syscall
li $v0,1
move $a0,$t0
syscall
sw $t2,-12($sp)
li $t2,2
move $t0,$t2
li $v0,4
la $a0,$string15
syscall
li $v0,1
move $a0,$t0
syscall

li $t9,12
sw $t9,-4($fp)
sw $8,-40($fp)
sw $9,-44($fp)
sw $10,-48($fp)
sw $11,-52($fp)
sw $12,-56($fp)
sw $13,-60($fp)
sw $14,-64($fp)
sw $15,-68($fp)
sw $24,-104($fp)
sw $ra,-132($fp)
sub $sp,$fp,132
sub $fp,$sp,28
jal fib
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $11,80($sp)
lw $12,76($sp)
lw $13,72($sp)
lw $14,68($sp)
lw $15,64($sp)
lw $24,28($sp)
lw $ra,0($sp)
add $fp,$fp,160
add $sp,$sp,252
sw $t3,-16($sp)
move $t3,$v0


li $t9,14
sw $t9,-4($fp)
sw $8,-40($fp)
sw $9,-44($fp)
sw $10,-48($fp)
sw $11,-52($fp)
sw $12,-56($fp)
sw $13,-60($fp)
sw $14,-64($fp)
sw $15,-68($fp)
sw $24,-104($fp)
sw $ra,-132($fp)
sub $sp,$fp,132
sub $fp,$sp,28
jal fib
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $11,80($sp)
lw $12,76($sp)
lw $13,72($sp)
lw $14,68($sp)
lw $15,64($sp)
lw $24,28($sp)
lw $ra,0($sp)
add $fp,$fp,160
add $sp,$sp,252
sw $t4,-20($sp)
move $t4,$v0

sw $t5,-24($sp)
sub $t5,$t3,$t4
move $t0,$t5
li $v0,4
la $a0,$string16
syscall
li $v0,1
move $a0,$t0
syscall
sw $t6,-28($sp)
li $t6,111
move $t0,$t6
li $v0,4
la $a0,$string17
syscall
li $v0,1
move $a0,$t0
syscall
sw $t7,-32($sp)
li $t7,1188
sw $t8,-36($sp)
li $t9,1
div $t8,$t7,$t9
move $t0,$t8
li $v0,4
la $a0,$string18
syscall
li $v0,1
move $a0,$t0
syscall
sw $t1,-40($sp)
li $t1,13
sw $t2,-44($sp)
li $t9,1
move $v1,$t9
sub $t2,$v1,$t1
move $t0,$t2
li $v0,4
la $a0,$string19
syscall
li $v0,1
move $a0,$t0
syscall
add $v1,$sp,204
li $t9,15
sw $t9,4($v1)
sw $t3,-48($sp)
add $v1,$sp,204
lw $t3,4($v1)
sw $t4,-52($sp)
li $t9,98
mul $t4,$t3,$t9

li $t9,3
sw $t9,-4($fp)
sw $8,-40($fp)
sw $9,-44($fp)
sw $10,-48($fp)
sw $11,-52($fp)
sw $12,-56($fp)
sw $13,-60($fp)
sw $14,-64($fp)
sw $15,-68($fp)
sw $24,-104($fp)
sw $ra,-132($fp)
sub $sp,$fp,132
sub $fp,$sp,28
jal fib
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $11,80($sp)
lw $12,76($sp)
lw $13,72($sp)
lw $14,68($sp)
lw $15,64($sp)
lw $24,28($sp)
lw $ra,0($sp)
add $fp,$fp,160
add $sp,$sp,252
sw $t5,-56($sp)
move $t5,$v0

sw $t6,-60($sp)
add $t6,$t4,$t5
move $t0,$t6
li $v0,4
la $a0,$string20
syscall
li $v0,1
move $a0,$t0
syscall
li $t9,5
sw $t9,24($gp)
add $v1,$sp,156
li $t9,12
sw $t9,24($v1)
sw $t7,-64($sp)
li $t7,104

sw $t7,-4($fp)
sw $8,-40($fp)
sw $9,-44($fp)
sw $10,-48($fp)
sw $11,-52($fp)
sw $12,-56($fp)
sw $13,-60($fp)
sw $14,-64($fp)
sw $15,-68($fp)
sw $24,-104($fp)
sw $ra,-132($fp)
sub $sp,$fp,132
sub $fp,$sp,4
jal addone
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $11,80($sp)
lw $12,76($sp)
lw $13,72($sp)
lw $14,68($sp)
lw $15,64($sp)
lw $24,28($sp)
lw $ra,0($sp)
add $fp,$fp,136
add $sp,$sp,252
sw $t8,-68($sp)
move $t8,$v0


li $t9,5
sw $t9,-4($fp)
sw $8,-40($fp)
sw $9,-44($fp)
sw $10,-48($fp)
sw $11,-52($fp)
sw $12,-56($fp)
sw $13,-60($fp)
sw $14,-64($fp)
sw $15,-68($fp)
sw $24,-104($fp)
sw $ra,-132($fp)
sub $sp,$fp,132
sub $fp,$sp,28
jal fib
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $11,80($sp)
lw $12,76($sp)
lw $13,72($sp)
lw $14,68($sp)
lw $15,64($sp)
lw $24,28($sp)
lw $ra,0($sp)
add $fp,$fp,160
add $sp,$sp,252
sw $t1,-72($sp)
move $t1,$v0


li $t9,1
sw $t9,-4($fp)
sw $t1,-8($fp)
sw $8,-44($fp)
sw $9,-48($fp)
sw $10,-52($fp)
sw $11,-56($fp)
sw $12,-60($fp)
sw $13,-64($fp)
sw $14,-68($fp)
sw $15,-72($fp)
sw $24,-108($fp)
sw $ra,-136($fp)
sub $sp,$fp,136
sub $fp,$sp,4
jal add
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $11,80($sp)
lw $12,76($sp)
lw $13,72($sp)
lw $14,68($sp)
lw $15,64($sp)
lw $24,28($sp)
lw $ra,0($sp)
add $fp,$fp,140
add $sp,$sp,256
sw $t2,-76($sp)
move $t2,$v0

sw $t3,-80($sp)
lw $t9,24($gp)
div $t3,$t2,$t9
sw $t4,-84($sp)
add $t4,$t8,$t3
sw $t5,-88($sp)
add $v1,$sp,156
lw $t5,24($v1)
sw $t6,-92($sp)
sub $t6,$t4,$t5
move $t0,$t6
li $v0,4
la $a0,$string21
syscall
li $v0,1
move $a0,$t0
syscall
jr $ra
jr $ra

test_scanf:

li $v0,4
la $a0,$string22
syscall
li $v0,5
syscall
move $t0,$v0
li $v0,1
move $a0,$t0
syscall
li $v0,4
la $a0,$string23
syscall
li $v0,5
syscall
move $t0,$v0
li $v0,5
syscall
move $t1,$v0
li $v0,1
move $a0,$t0
syscall
li $v0,1
move $a0,$t1
syscall
jr $ra
jr $ra

echo_char:

li $v0,11
lw $t0,128($sp)
move $a0,$t0
syscall
move $v0,$t0
jr $ra
jr $ra

really_void:

jr $ra

really_void2:

jr $ra

really_void3:

jr $ra

permutation:

lw $s0,144($sp)
lw $s1,140($sp)
li $t9,1
sub $t0,$s1,$t9
bge $s0,$t0,$LABEL25
addi $t0,$s0,1

sw $t0,-4($fp)
sw $s1,-8($fp)
sw $8,-56($fp)
sw $16,-88($fp)
sw $17,-92($fp)
sw $18,-96($fp)
sw $ra,-148($fp)
sub $sp,$fp,148
sub $fp,$sp,76
jal permutation
lw $8,92($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $ra,0($sp)
add $fp,$fp,224
add $sp,$sp,224
move $t1,$v0

addi $t2,$s0,1
move $s2,$t2
$LABEL26:
bge $s2,$s1,$LABEL27
add $v1,$gp,276
sll $t9,$s0,2
add $t9,$v1,$t9
lw $t0,0($t9)
move $t1,$t0
add $v1,$gp,276
sll $t9,$s2,2
add $t9,$v1,$t9
lw $t2,0($t9)
add $v1,$gp,276
sll $t9,$s0,2
add $v1,$v1,$t9
sw $t2,0($v1)
add $v1,$gp,276
sll $t9,$s2,2
add $v1,$v1,$t9
sw $t1,0($v1)
addi $t3,$s0,1

sw $t3,-4($fp)
sw $s1,-8($fp)
sw $8,-56($fp)
sw $9,-60($fp)
sw $10,-64($fp)
sw $11,-68($fp)
sw $16,-88($fp)
sw $17,-92($fp)
sw $18,-96($fp)
sw $ra,-148($fp)
sub $sp,$fp,148
sub $fp,$sp,76
jal permutation
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $11,80($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $ra,0($sp)
add $fp,$fp,224
add $sp,$sp,224
move $t4,$v0

add $v1,$gp,276
sll $t9,$s0,2
add $t9,$v1,$t9
lw $t5,0($t9)
move $t1,$t5
add $v1,$gp,276
sll $t9,$s2,2
add $t9,$v1,$t9
lw $t6,0($t9)
add $v1,$gp,276
sll $t9,$s0,2
add $v1,$v1,$t9
sw $t6,0($v1)
add $v1,$gp,276
sll $t9,$s2,2
add $v1,$v1,$t9
sw $t1,0($v1)
addi $t7,$s2,1
move $s2,$t7
j $LABEL26
$LABEL27:
j $LABEL28
$LABEL25:
li $s2,0
$LABEL29:
add $v1,$gp,276
sll $t9,$s2,2
add $t9,$v1,$t9
lw $t0,0($t9)

sw $t0,-4($fp)
sw $8,-40($fp)
sw $16,-72($fp)
sw $17,-76($fp)
sw $18,-80($fp)
sw $ra,-132($fp)
sub $sp,$fp,132
sub $fp,$sp,0
jal echo_char
lw $8,92($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $ra,0($sp)
add $fp,$fp,132
add $sp,$sp,208
move $t1,$v0

move $t2,$t1
add $v1,$gp,276
sll $t9,$s2,2
add $t9,$v1,$t9
lw $t3,0($t9)
beq $t2,$t3,$LABEL30
li $v0,4
la $a0,$string6
syscall
$LABEL30:
$LABEL31:
addi $t0,$s2,1
move $s2,$t0
li $t9,5
blt $s2,$t9,$LABEL29
li $v0,4
la $a0,$string24
syscall
$LABEL28:
jr $ra

main:

li $s0,0
$LABEL32:
li $t9,10
bge $s0,$t9,$LABEL33
addi $t0,$s0,1

sw $t0,-4($fp)
sw $8,-40($fp)
sw $16,-72($fp)
sw $17,-76($fp)
sw $18,-80($fp)
sw $ra,-132($fp)
sub $sp,$fp,132
sub $fp,$sp,28
jal fib
lw $8,92($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $ra,0($sp)
add $fp,$fp,160
add $sp,$sp,252
move $t1,$v0

add $v1,$sp,180
sll $t9,$s0,2
add $v1,$v1,$t9
sw $t1,0($v1)
addi $t2,$s0,1
move $s0,$t2
j $LABEL32
$LABEL33:
li $v0,4
la $a0,$string25
syscall
li $v0,5
syscall
move $s1,$v0
li $v0,5
syscall
move $s2,$v0
li $t9,1
sub $t0,$s1,$t9
move $s0,$t0
$LABEL34:
li $v0,4
la $a0,$string24
syscall
add $v1,$sp,180
sll $t9,$s0,2
add $t9,$v1,$t9
lw $t0,0($t9)
li $v0,1
move $a0,$t0
syscall
addi $t1,$s0,1
move $s0,$t1
blt $s0,$s2,$LABEL34
li $t9,1
sub $t0,$s2,$t9
move $s0,$t0
$LABEL35:
li $t9,1
sub $t0,$s1,$t9
blt $s0,$t0,$LABEL36
li $v0,4
la $a0,$string24
syscall
add $v1,$sp,180
sll $t9,$s0,2
add $t9,$v1,$t9
lw $t0,0($t9)
li $v0,1
move $a0,$t0
syscall
li $t9,1
sub $t1,$s0,$t9
move $s0,$t1
j $LABEL35
$LABEL36:

li $t9,1
sw $t9,-4($fp)
li $t9,98
sw $t9,-8($fp)
sw $16,-76($fp)
sw $17,-80($fp)
sw $18,-84($fp)
sw $ra,-136($fp)
sub $sp,$fp,136
sub $fp,$sp,4
jal foo1
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $ra,0($sp)
add $fp,$fp,140
add $sp,$sp,256
move $t0,$v0

li $v0,1
move $a0,$t0
syscall

li $t9,1
sw $t9,-4($fp)
li $t9,2
sw $t9,-8($fp)
sw $8,-44($fp)
sw $16,-76($fp)
sw $17,-80($fp)
sw $18,-84($fp)
sw $ra,-136($fp)
sub $sp,$fp,136
sub $fp,$sp,4
jal add
lw $8,92($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $ra,0($sp)
add $fp,$fp,140
add $sp,$sp,256
move $t1,$v0

li $v0,1
move $a0,$t1
syscall

li $t9,97
sw $t9,-4($fp)
li $t9,98
sw $t9,-8($fp)
sw $8,-44($fp)
sw $9,-48($fp)
sw $16,-76($fp)
sw $17,-80($fp)
sw $18,-84($fp)
sw $ra,-136($fp)
sub $sp,$fp,136
sub $fp,$sp,4
jal addchar
lw $8,92($sp)
lw $9,88($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $ra,0($sp)
add $fp,$fp,140
add $sp,$sp,256
move $t2,$v0

li $v0,1
move $a0,$t2
syscall

li $t9,70
sw $t9,-4($fp)
sw $8,-40($fp)
sw $9,-44($fp)
sw $10,-48($fp)
sw $16,-72($fp)
sw $17,-76($fp)
sw $18,-80($fp)
sw $ra,-132($fp)
sub $sp,$fp,132
sub $fp,$sp,4
jal addone
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $ra,0($sp)
add $fp,$fp,136
add $sp,$sp,252
move $t3,$v0

li $v0,1
move $a0,$t3
syscall

li $t9,16
sw $t9,-4($fp)
sw $8,-40($fp)
sw $9,-44($fp)
sw $10,-48($fp)
sw $11,-52($fp)
sw $16,-72($fp)
sw $17,-76($fp)
sw $18,-80($fp)
sw $ra,-132($fp)
sub $sp,$fp,132
sub $fp,$sp,4
jal addint
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $11,80($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $ra,0($sp)
add $fp,$fp,136
add $sp,$sp,252
move $t4,$v0

li $v0,1
move $a0,$t4
syscall

li $t9,99
sw $t9,-4($fp)
sw $8,-40($fp)
sw $9,-44($fp)
sw $10,-48($fp)
sw $11,-52($fp)
sw $12,-56($fp)
sw $16,-72($fp)
sw $17,-76($fp)
sw $18,-80($fp)
sw $ra,-132($fp)
sub $sp,$fp,132
sub $fp,$sp,4
jal foo2
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $11,80($sp)
lw $12,76($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $ra,0($sp)
add $fp,$fp,136
add $sp,$sp,252
move $t5,$v0

li $v0,11
move $a0,$t5
syscall

sw $8,-40($fp)
sw $9,-44($fp)
sw $10,-48($fp)
sw $11,-52($fp)
sw $12,-56($fp)
sw $13,-60($fp)
sw $16,-72($fp)
sw $17,-76($fp)
sw $18,-80($fp)
sw $ra,-132($fp)
sub $sp,$fp,132
sub $fp,$sp,8
jal test_string_int
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $11,80($sp)
lw $12,76($sp)
lw $13,72($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $ra,0($sp)
add $fp,$fp,140
add $sp,$sp,252
move $t6,$v0


li $t9,233
sw $t9,-4($fp)
sw $8,-48($fp)
sw $9,-52($fp)
sw $10,-56($fp)
sw $11,-60($fp)
sw $12,-64($fp)
sw $13,-68($fp)
sw $14,-72($fp)
sw $16,-80($fp)
sw $17,-84($fp)
sw $18,-88($fp)
sw $ra,-140($fp)
sub $sp,$fp,140
sub $fp,$sp,12
jal test_diff_domain
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $11,80($sp)
lw $12,76($sp)
lw $13,72($sp)
lw $14,68($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $ra,0($sp)
add $fp,$fp,152
add $sp,$sp,260
move $t7,$v0


sw $8,-120($fp)
sw $9,-124($fp)
sw $10,-128($fp)
sw $11,-132($fp)
sw $12,-136($fp)
sw $13,-140($fp)
sw $14,-144($fp)
sw $15,-148($fp)
sw $16,-152($fp)
sw $17,-156($fp)
sw $18,-160($fp)
sw $ra,-212($fp)
sub $sp,$fp,212
sub $fp,$sp,120
jal test_expr
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $11,80($sp)
lw $12,76($sp)
lw $13,72($sp)
lw $14,68($sp)
lw $15,64($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $ra,0($sp)
add $fp,$fp,332
add $sp,$sp,332
move $t8,$v0


sw $8,-52($fp)
sw $9,-56($fp)
sw $10,-60($fp)
sw $11,-64($fp)
sw $12,-68($fp)
sw $13,-72($fp)
sw $14,-76($fp)
sw $15,-80($fp)
sw $16,-84($fp)
sw $17,-88($fp)
sw $18,-92($fp)
sw $24,-116($fp)
sw $ra,-144($fp)
sub $sp,$fp,144
sub $fp,$sp,36
jal test_all_cond
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $11,80($sp)
lw $12,76($sp)
lw $13,72($sp)
lw $14,68($sp)
lw $15,64($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $24,28($sp)
lw $ra,0($sp)
add $fp,$fp,180
add $sp,$sp,264
sw $t0,-44($sp)
move $t0,$v0


sw $8,-44($fp)
sw $9,-48($fp)
sw $10,-52($fp)
sw $11,-56($fp)
sw $12,-60($fp)
sw $13,-64($fp)
sw $14,-68($fp)
sw $15,-72($fp)
sw $16,-76($fp)
sw $17,-80($fp)
sw $18,-84($fp)
sw $24,-108($fp)
sw $ra,-136($fp)
sub $sp,$fp,136
sub $fp,$sp,0
jal test_scanf
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $11,80($sp)
lw $12,76($sp)
lw $13,72($sp)
lw $14,68($sp)
lw $15,64($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $24,28($sp)
lw $ra,0($sp)
add $fp,$fp,136
add $sp,$sp,256
sw $t1,-48($sp)
move $t1,$v0


li $t9,97
sw $t9,-4($fp)
sw $8,-40($fp)
sw $9,-44($fp)
sw $10,-48($fp)
sw $11,-52($fp)
sw $12,-56($fp)
sw $13,-60($fp)
sw $14,-64($fp)
sw $15,-68($fp)
sw $16,-72($fp)
sw $17,-76($fp)
sw $18,-80($fp)
sw $24,-104($fp)
sw $ra,-132($fp)
sub $sp,$fp,132
sub $fp,$sp,0
jal echo_char
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $11,80($sp)
lw $12,76($sp)
lw $13,72($sp)
lw $14,68($sp)
lw $15,64($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $24,28($sp)
lw $ra,0($sp)
add $fp,$fp,132
add $sp,$sp,252
sw $t2,-52($sp)
move $t2,$v0


li $t9,1
sw $t9,-4($fp)
li $t9,2
sw $t9,-8($fp)
li $t9,99
sw $t9,-12($fp)
li $t9,100
sw $t9,-16($fp)
li $t9,5
sw $t9,-20($fp)
sw $8,-56($fp)
sw $9,-60($fp)
sw $10,-64($fp)
sw $11,-68($fp)
sw $12,-72($fp)
sw $13,-76($fp)
sw $14,-80($fp)
sw $15,-84($fp)
sw $16,-88($fp)
sw $17,-92($fp)
sw $18,-96($fp)
sw $24,-120($fp)
sw $ra,-148($fp)
sub $sp,$fp,148
sub $fp,$sp,16
jal test_lots_paras
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $11,80($sp)
lw $12,76($sp)
lw $13,72($sp)
lw $14,68($sp)
lw $15,64($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $24,28($sp)
lw $ra,0($sp)
add $fp,$fp,164
add $sp,$sp,268
sw $t3,-56($sp)
move $t3,$v0

li $v0,1
move $a0,$t3
syscall

sw $8,-36($fp)
sw $9,-40($fp)
sw $10,-44($fp)
sw $11,-48($fp)
sw $12,-52($fp)
sw $13,-56($fp)
sw $14,-60($fp)
sw $15,-64($fp)
sw $16,-68($fp)
sw $17,-72($fp)
sw $18,-76($fp)
sw $24,-100($fp)
sw $ra,-128($fp)
sub $sp,$fp,128
sub $fp,$sp,0
jal really_void
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $11,80($sp)
lw $12,76($sp)
lw $13,72($sp)
lw $14,68($sp)
lw $15,64($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $24,28($sp)
lw $ra,0($sp)
add $fp,$fp,128
add $sp,$sp,248
sw $t4,-60($sp)
move $t4,$v0


sw $8,-36($fp)
sw $9,-40($fp)
sw $10,-44($fp)
sw $11,-48($fp)
sw $12,-52($fp)
sw $13,-56($fp)
sw $14,-60($fp)
sw $15,-64($fp)
sw $16,-68($fp)
sw $17,-72($fp)
sw $18,-76($fp)
sw $24,-100($fp)
sw $ra,-128($fp)
sub $sp,$fp,128
sub $fp,$sp,0
jal really_void2
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $11,80($sp)
lw $12,76($sp)
lw $13,72($sp)
lw $14,68($sp)
lw $15,64($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $24,28($sp)
lw $ra,0($sp)
add $fp,$fp,128
add $sp,$sp,248
sw $t5,-64($sp)
move $t5,$v0


sw $8,-36($fp)
sw $9,-40($fp)
sw $10,-44($fp)
sw $11,-48($fp)
sw $12,-52($fp)
sw $13,-56($fp)
sw $14,-60($fp)
sw $15,-64($fp)
sw $16,-68($fp)
sw $17,-72($fp)
sw $18,-76($fp)
sw $24,-100($fp)
sw $ra,-128($fp)
sub $sp,$fp,128
sub $fp,$sp,0
jal really_void3
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $11,80($sp)
lw $12,76($sp)
lw $13,72($sp)
lw $14,68($sp)
lw $15,64($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $24,28($sp)
lw $ra,0($sp)
add $fp,$fp,128
add $sp,$sp,248
sw $t6,-68($sp)
move $t6,$v0

add $v1,$gp,276
li $t9,65
sw $t9,0($v1)
add $v1,$gp,276
li $t9,66
sw $t9,4($v1)
add $v1,$gp,276
li $t9,67
sw $t9,8($v1)
add $v1,$gp,276
li $t9,68
sw $t9,12($v1)
add $v1,$gp,276
li $t9,69
sw $t9,16($v1)
li $v0,4
la $a0,$string26
syscall

li $t9,0
sw $t9,-4($fp)
li $t9,5
sw $t9,-8($fp)
sw $8,-56($fp)
sw $9,-60($fp)
sw $10,-64($fp)
sw $11,-68($fp)
sw $12,-72($fp)
sw $13,-76($fp)
sw $14,-80($fp)
sw $15,-84($fp)
sw $16,-88($fp)
sw $17,-92($fp)
sw $18,-96($fp)
sw $24,-120($fp)
sw $ra,-148($fp)
sub $sp,$fp,148
sub $fp,$sp,76
jal permutation
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $11,80($sp)
lw $12,76($sp)
lw $13,72($sp)
lw $14,68($sp)
lw $15,64($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $24,28($sp)
lw $ra,0($sp)
add $fp,$fp,224
add $sp,$sp,268
sw $t7,-72($sp)
move $t7,$v0

li $v0,10
syscall
li $v0,10
syscall
