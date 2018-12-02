.data
    $string0: .asciiz " "
    $string1: .asciiz "\n"
    $string2: .asciiz "ERROR!"
.text
    sub $sp,$sp,136
    move $fp,$sp
    sub $fp,$fp,20
    j main

recursive_cal:

lw $s0,136($sp)
lw $s1,132($sp)
lw $t9,8($gp)
bne $s0,$t9,$LABEL1
add $v1,$gp,12
lw $t0,0($v1)
li $v0,1
move $a0,$t0
syscall
li $s2,1
$LABEL2:
lw $t9,8($gp)
bge $s2,$t9,$LABEL3
li $v0,4
la $a0,$string0
syscall
add $v1,$gp,12
sll $t9,$s2,2
add $t9,$v1,$t9
lw $t0,0($t9)
li $v0,1
move $a0,$t0
syscall
addi $s2,$s2,1
j $LABEL2
$LABEL3:
li $v0,4
la $a0,$string1
syscall
jr $ra
j $LABEL4
$LABEL1:
$LABEL4:
move $s2,$s1
$LABEL5:
lw $t9,4($gp)
add $t0,$s0,$t9
lw $t9,8($gp)
sub $t1,$t0,$t9
addi $t2,$t1,1
bgt $s2,$t2,$LABEL6
add $v1,$gp,12
sll $t9,$s0,2
add $v1,$v1,$t9
sw $s2,0($v1)
addi $t0,$s0,1
addi $t1,$s2,1

sw $t0,-4($fp)
sw $t1,-8($fp)
sw $8,-48($fp)
sw $9,-52($fp)
sw $16,-80($fp)
sw $17,-84($fp)
sw $18,-88($fp)
sw $t8,-112($fp)
sw $29,-132($fp)
sw $30,-136($fp)
sw $31,-140($fp)
sub $sp,$fp,140
move $fp,$sp
sub $fp,$fp,44
jal recursive_cal
lw $8,92($sp)
lw $9,88($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $t8,28($sp)
lw $30,4($sp)
lw $31,0($sp)
lw $sp,8($sp)
move $t2,$v0

addi $s2,$s2,1
j $LABEL5
$LABEL6:
jr $ra

initial:

lw $s0,136($sp)
lw $s1,132($sp)
li $s2,0
$LABEL7:
add $v1,$gp,12
sll $t9,$s2,2
add $v1,$v1,$t9
sw $s0,0($v1)
addi $t0,$s2,1
move $s2,$t0
ble $s2,$s1,$LABEL7
jr $ra
jr $ra

main:

li $v0,5
syscall
move $t9,$v0
sw $t9,4($gp)
li $v0,5
syscall
move $t9,$v0
sw $t9,8($gp)
lw $t9,8($gp)
addi $t0,$t9,1
li $t9,1000
ble $t0,$t9,$LABEL8
li $v0,4
la $a0,$string2
syscall
li $v0,10
syscall
j $LABEL9
$LABEL8:
$LABEL9:
lw $t9,8($gp)
addi $t0,$t9,1

li $t9,0
sw $t9,-4($fp)
sw $t0,-8($fp)
sw $8,-48($fp)
sw $t8,-112($fp)
sw $29,-132($fp)
sw $30,-136($fp)
sw $31,-140($fp)
sub $sp,$fp,140
move $fp,$sp
sub $fp,$fp,8
jal initial
lw $8,92($sp)
lw $t8,28($sp)
lw $30,4($sp)
lw $31,0($sp)
lw $sp,8($sp)
move $t1,$v0


li $t9,0
sw $t9,-4($fp)
li $t9,1
sw $t9,-8($fp)
sw $8,-48($fp)
sw $9,-52($fp)
sw $t8,-112($fp)
sw $29,-132($fp)
sw $30,-136($fp)
sw $31,-140($fp)
sub $sp,$fp,140
move $fp,$sp
sub $fp,$fp,44
jal recursive_cal
lw $8,92($sp)
lw $9,88($sp)
lw $t8,28($sp)
lw $30,4($sp)
lw $31,0($sp)
lw $sp,8($sp)
move $t2,$v0

li $v0,10
syscall
