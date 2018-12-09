.data
    $string0: .asciiz " A(-+11)= "
    $string1: .asciiz " calc A ="
    $string2: .asciiz "input1>input2 "
    $string3: .asciiz "input1<input2 "
    $string4: .asciiz "input1==input2 "
    $string5: .asciiz " four param cal="
    $string6: .asciiz "scanf two int "
    $string7: .asciiz "get_gcd a and A= "
    $string8: .asciiz " fourparam return= "
    $string9: .asciiz "\\n\\n\\n const A_const_char= "
    $string10: .asciiz "\\\\n\\\\n\\\\n a_var_char_arr[4]= "
.text
    sub $sp,$sp,152
    move $fp,$sp
    sub $fp,$fp,40
    j main

fibo:

lw $s0,128($sp)
li $t9,1
bne $s0,$t9,$LABEL1
li $t9,1
move $v0,$t9
jr $ra
j $LABEL2
$LABEL1:
li $t9,2
bne $s0,$t9,$LABEL3
li $t9,1
move $v0,$t9
jr $ra
j $LABEL4
$LABEL3:
li $t9,1
sub $t0,$s0,$t9

sw $t0,-4($fp)
sw $8,-40($fp)
sw $16,-72($fp)
sw $ra,-132($fp)
sub $sp,$fp,132
sub $fp,$sp,28
jal fibo
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
jal fibo
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
$LABEL4:
$LABEL2:
jr $ra

test_base:

lw $s0,140($sp)
lw $s1,136($sp)
li $t0,-11
move $s2,$t0
li $v0,4
la $a0,$string0
syscall
li $v0,1
move $a0,$s2
syscall
$LABEL7:
$LABEL8:
$LABEL6:
$LABEL9:
$LABEL5:
$LABEL10:
li $t0,11
li $t9,11
sub $t1,$t0,$t9
addi $t2,$t1,-11

li $t9,5
sw $t9,-4($fp)
sw $8,-40($fp)
sw $9,-44($fp)
sw $10,-48($fp)
sw $16,-72($fp)
sw $17,-76($fp)
sw $18,-80($fp)
sw $ra,-132($fp)
sub $sp,$fp,132
sub $fp,$sp,28
jal fibo
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $ra,0($sp)
add $fp,$fp,160
add $sp,$sp,196
move $t3,$v0

add $t4,$t2,$t3
li $t5,-2
add $t6,$t4,$t5
li $t7,3
sub $t8,$t6,$t7
move $s2,$t8
li $v0,4
la $a0,$string1
syscall
li $v0,1
move $a0,$s2
syscall
ble $s0,$s1,$LABEL11
li $v0,4
la $a0,$string2
syscall
jr $ra
j $LABEL12
$LABEL11:
bge $s0,$s1,$LABEL13
li $v0,4
la $a0,$string3
syscall
jr $ra
j $LABEL14
$LABEL13:
bne $s0,$s1,$LABEL15
li $v0,4
la $a0,$string4
syscall
jr $ra
$LABEL15:
$LABEL16:
$LABEL14:
$LABEL12:
jr $ra

get_gcd:

lw $s0,144($sp)
lw $s1,140($sp)
ble $s0,$s1,$LABEL17
move $t0,$s0
move $s0,$s1
move $s1,$t0
$LABEL17:
$LABEL18:
div $t0,$s1,$s0
move $t1,$t0
mul $t2,$t1,$s0
move $t1,$t2
sub $t3,$s1,$t1
li $t9,0
bne $t3,$t9,$LABEL19
move $v0,$s0
jr $ra
$LABEL19:
$LABEL20:
li $t9,2
div $t0,$s0,$t9
move $s2,$t0
$LABEL21:
li $t9,1
ble $s2,$t9,$LABEL22
div $t0,$s0,$s2
move $t1,$t0
mul $t2,$t1,$s2
move $t1,$t2
sub $t3,$s0,$t1
li $t9,0
bne $t3,$t9,$LABEL23
div $t0,$s1,$s2
move $t1,$t0
mul $t2,$t1,$s2
move $t1,$t2
sub $t3,$s1,$t1
li $t9,0
bne $t3,$t9,$LABEL24
move $v0,$s2
jr $ra
$LABEL24:
$LABEL25:
$LABEL23:
$LABEL26:
li $t9,1
sub $s2,$s2,$t9
j $LABEL21
$LABEL22:
li $t9,1
move $v0,$t9
jr $ra
jr $ra

fourparam:

lw $s0,144($sp)
lw $s1,140($sp)
lw $s2,136($sp)
lw $s3,132($sp)
li $t0,-22
add $t1,$s0,$s1
move $s0,$t1
add $t2,$s0,$s1
move $s1,$t2
mul $t3,$s0,$s1
add $t4,$t3,$s0
move $s0,$t4
add $t5,$s2,$s0
move $s0,$t5
add $t6,$s3,$s0
move $s0,$t6
add $t7,$t0,$s0
move $s0,$t7
li $v0,4
la $a0,$string5
syscall
li $v0,1
move $a0,$s0
syscall
move $v0,$s3
jr $ra
jr $ra

main:

li $s1,0
li $s0,5
li $s1,0
$LABEL27:
bge $s1,$s0,$LABEL28
add $v1,$gp,12
sll $t9,$s1,2
add $v1,$v1,$t9
sw $s1,0($v1)
addi $s1,$s1,1
j $LABEL27
$LABEL28:
li $s1,0
$LABEL29:
add $v1,$gp,32
sll $t9,$s1,2
add $v1,$v1,$t9
li $t9,97
sw $t9,0($v1)
addi $t0,$s1,1
move $s1,$t0
blt $s1,$s0,$LABEL29
li $v0,4
la $a0,$string6
syscall
li $v0,5
syscall
move $t0,$v0
li $v0,5
syscall
move $t1,$v0

sw $t0,-4($fp)
sw $t1,-8($fp)
sw $8,-52($fp)
sw $9,-56($fp)
sw $16,-84($fp)
sw $17,-88($fp)
sw $ra,-144($fp)
sub $sp,$fp,144
sub $fp,$sp,64
jal test_base
lw $8,92($sp)
lw $9,88($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $ra,0($sp)
add $fp,$fp,208
add $sp,$sp,184
move $t2,$v0


sw $t0,-4($fp)
sw $t1,-8($fp)
sw $8,-56($fp)
sw $9,-60($fp)
sw $10,-64($fp)
sw $16,-88($fp)
sw $17,-92($fp)
sw $ra,-148($fp)
sub $sp,$fp,148
sub $fp,$sp,60
jal get_gcd
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $ra,0($sp)
add $fp,$fp,208
add $sp,$sp,188
move $t3,$v0

move $t9,$t3
sw $t9,8($gp)
li $v0,4
la $a0,$string7
syscall
li $v0,1
lw $t9,8($gp)
move $a0,$t9
syscall
li $v0,12
syscall
move $t4,$v0
li $v0,12
syscall
move $t5,$v0

sw $t0,-4($fp)
sw $t1,-8($fp)
sw $t4,-12($fp)
sw $t5,-16($fp)
sw $8,-56($fp)
sw $9,-60($fp)
sw $10,-64($fp)
sw $11,-68($fp)
sw $12,-72($fp)
sw $13,-76($fp)
sw $16,-88($fp)
sw $17,-92($fp)
sw $ra,-148($fp)
sub $sp,$fp,148
sub $fp,$sp,28
jal fourparam
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $11,80($sp)
lw $12,76($sp)
lw $13,72($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $ra,0($sp)
add $fp,$fp,176
add $sp,$sp,188
move $t6,$v0

move $t5,$t6
li $v0,4
la $a0,$string8
syscall
li $v0,11
move $a0,$t5
syscall
li $v0,4
la $a0,$string9
syscall
li $v0,11
li $t9,65
move $a0,$t9
syscall
li $v0,4
la $a0,$string10
syscall
li $t7,2
addi $t8,$t7,1
sw $t2,-8($sp)
addi $t2,$t8,1
sw $t3,-12($sp)
add $v1,$gp,32
sll $t9,$t2,2
add $t9,$v1,$t9
lw $t3,0($t9)
li $v0,11
move $a0,$t3
syscall
li $v0,10
syscall
li $v0,10
syscall
