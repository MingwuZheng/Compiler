.data
    $string0: .asciiz " "
    $string1: .asciiz "\n"
    $string2: .asciiz "ERROR!"
.text
    sub $sp,$sp,136
    move $fp,$sp
    j main

recursive_cal:

add $t9,$sp,136
lw $s0,0($t9)
add $t9,$sp,132
lw $s1,0($t9)
add $t9,$gp,8
lw $t9,0($t9)
bne $s0,$t9,$LABEL1
sub $fp,$fp,4
add $v1,$gp,12
lw $t0,0($v1)
li $v0,1
move $a0,$t0
syscall
li $s2,1
$LABEL2:
add $t9,$gp,8
lw $t9,0($t9)
bge $s2,$t9,$LABEL3
li $v0,4
la $a0,$string0
syscall
sub $fp,$fp,4
add $v1,$gp,12
mul $t9,$s2,4
add $t9,$v1,$t9
lw $t1,0($t9)
li $v0,1
move $a0,$t1
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
sub $fp,$fp,4
add $t9,$gp,4
lw $t9,0($t9)
add $t2,$s0,$t9
sub $fp,$fp,4
add $t9,$gp,8
lw $t9,0($t9)
sub $t3,$t2,$t9
sub $fp,$fp,4
addi $t4,$t3,1
bgt $s2,$t4,$LABEL6
add $v1,$gp,12
mul $t9,$s0,4
add $v1,$v1,$t9
sw $s2,0($v1)
sub $fp,$fp,4
addi $t5,$s0,1
sub $fp,$fp,4
addi $t6,$s2,1

sw $t5,-4($fp)
sw $t6,-8($fp)
sw $8,-48($fp)
sw $9,-52($fp)
sw $10,-56($fp)
sw $11,-60($fp)
sw $12,-64($fp)
sw $13,-68($fp)
sw $14,-72($fp)
sw $15,-76($fp)
sw $16,-80($fp)
sw $17,-84($fp)
sw $18,-88($fp)
sw $19,-92($fp)
sw $20,-96($fp)
sw $21,-100($fp)
sw $22,-104($fp)
sw $23,-108($fp)
sw $24,-112($fp)
sw $25,-116($fp)
sw $29,-132($fp)
sw $30,-136($fp)
sw $31,-140($fp)
sub $sp,$fp,140
move $fp,$sp
jal recursive_cal
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
lw $19,48($sp)
lw $20,44($sp)
lw $21,40($sp)
lw $22,36($sp)
lw $23,32($sp)
lw $24,28($sp)
lw $25,24($sp)
lw $30,4($sp)
lw $31,0($sp)
lw $sp,8($sp)
sub $fp,$fp,4
move $t7,$v0

addi $s2,$s2,1
j $LABEL5
$LABEL6:
jr $ra

initial:

add $t9,$sp,136
lw $s0,0($t9)
add $t9,$sp,132
lw $s1,0($t9)
li $s2,0
$LABEL7:
add $v1,$gp,12
mul $t9,$s2,4
add $v1,$v1,$t9
sw $s0,0($v1)
sub $fp,$fp,4
addi $t0,$s2,1
move $s2,$t0
ble $s2,$s1,$LABEL7
jr $ra
jr $ra

main:

li $v0,5
syscall
move $t9,$v0
add $v1,$gp,4
sw $t9,0($v1)
li $v0,5
syscall
move $t9,$v0
add $v1,$gp,8
sw $t9,0($v1)
sub $fp,$fp,4
add $t9,$gp,8
lw $t9,0($t9)
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
sub $fp,$fp,4
add $t9,$gp,8
lw $t9,0($t9)
addi $t1,$t9,1

li $t9,0
sw $t9,-4($fp)
sw $t1,-8($fp)
sw $8,-48($fp)
sw $9,-52($fp)
sw $10,-56($fp)
sw $11,-60($fp)
sw $12,-64($fp)
sw $13,-68($fp)
sw $14,-72($fp)
sw $15,-76($fp)
sw $16,-80($fp)
sw $17,-84($fp)
sw $18,-88($fp)
sw $19,-92($fp)
sw $20,-96($fp)
sw $21,-100($fp)
sw $22,-104($fp)
sw $23,-108($fp)
sw $24,-112($fp)
sw $25,-116($fp)
sw $29,-132($fp)
sw $30,-136($fp)
sw $31,-140($fp)
sub $sp,$fp,140
move $fp,$sp
jal initial
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
lw $19,48($sp)
lw $20,44($sp)
lw $21,40($sp)
lw $22,36($sp)
lw $23,32($sp)
lw $24,28($sp)
lw $25,24($sp)
lw $30,4($sp)
lw $31,0($sp)
lw $sp,8($sp)
sub $fp,$fp,4
move $t2,$v0


li $t9,0
sw $t9,-4($fp)
li $t9,1
sw $t9,-8($fp)
sw $8,-48($fp)
sw $9,-52($fp)
sw $10,-56($fp)
sw $11,-60($fp)
sw $12,-64($fp)
sw $13,-68($fp)
sw $14,-72($fp)
sw $15,-76($fp)
sw $16,-80($fp)
sw $17,-84($fp)
sw $18,-88($fp)
sw $19,-92($fp)
sw $20,-96($fp)
sw $21,-100($fp)
sw $22,-104($fp)
sw $23,-108($fp)
sw $24,-112($fp)
sw $25,-116($fp)
sw $29,-132($fp)
sw $30,-136($fp)
sw $31,-140($fp)
sub $sp,$fp,140
move $fp,$sp
jal recursive_cal
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
lw $19,48($sp)
lw $20,44($sp)
lw $21,40($sp)
lw $22,36($sp)
lw $23,32($sp)
lw $24,28($sp)
lw $25,24($sp)
lw $30,4($sp)
lw $31,0($sp)
lw $sp,8($sp)
sub $fp,$fp,4
move $t3,$v0

li $v0,10
syscall
