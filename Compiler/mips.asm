.data
    $string0: .asciiz " "
    $string1: .asciiz "\n"
    $string2: .asciiz "ERROR!"
    $string3: .asciiz "ERROR!\n"
.text
    sub $sp,$sp,136
    move $fp,$sp
    j main

recursive_cal:

lw $s0,136($sp)
lw $s1,132($sp)
lw $t9,8($gp)
bne $s0,$t9,$LABEL1
sub $fp,$fp,4
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
sub $fp,$fp,4
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
li $t9,0
move $v0,$t9
jr $ra
j $LABEL4
$LABEL1:
lw $t9,8($gp)
bge $s0,$t9,$LABEL5
move $s2,$s1
$LABEL6:
sub $fp,$fp,4
lw $t9,4($gp)
add $t0,$s0,$t9
sub $fp,$fp,4
lw $t9,8($gp)
sub $t1,$t0,$t9
sub $fp,$fp,4
addi $t2,$t1,1
bgt $s2,$t2,$LABEL7
add $v1,$gp,12
sll $t9,$s0,2
add $v1,$v1,$t9
sw $s2,0($v1)
sub $fp,$fp,4
addi $t0,$s0,1
sub $fp,$fp,4
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
sub $fp,$fp,4
move $t2,$v0

sub $fp,$fp,4
li $t3,-1
bne $t2,$t3,$LABEL8
sub $fp,$fp,4
li $t0,-1
move $v0,$t0
jr $ra
j $LABEL9
$LABEL8:
$LABEL9:
addi $s2,$s2,1
j $LABEL6
$LABEL7:
li $t9,0
move $v0,$t9
jr $ra
j $LABEL10
$LABEL5:
sub $fp,$fp,4
li $t0,-1
move $v0,$t0
jr $ra
$LABEL10:
$LABEL4:
jr $ra

initial:

lw $s0,136($sp)
lw $s1,132($sp)
li $s2,0
$LABEL11:
add $v1,$gp,12
sll $t9,$s2,2
add $v1,$v1,$t9
sw $s0,0($v1)
sub $fp,$fp,4
addi $t0,$s2,1
move $s2,$t0
ble $s2,$s1,$LABEL11
jr $ra
jr $ra

echo_lower:

lw $s0,128($sp)
li $t9,97
blt $s0,$t9,$LABEL12
li $t9,122
bgt $s0,$t9,$LABEL13
move $v0,$s0
jr $ra
j $LABEL14
$LABEL13:
li $v0,4
la $a0,$string2
syscall
li $t9,48
move $v0,$t9
jr $ra
$LABEL14:
j $LABEL15
$LABEL12:
li $v0,4
la $a0,$string2
syscall
li $t9,48
move $v0,$t9
jr $ra
$LABEL15:
jr $ra

test:

li $t0,105
li $t1,106
li $t2,107
li $t3,108
li $t4,109
li $t5,110
li $s0,111
li $s1,112
sub $fp,$fp,4
li $t6,-1
add $v1,$sp,140
sw $t6,0($v1)
sub $fp,$fp,4
add $v1,$sp,140
lw $t7,0($v1)
sub $fp,$fp,4
li $t9,-2
mul $t8,$t7,$t9
sub $fp,$fp,4
sw $t0,172($sp)
sub $t0,$0,$t8

li $t9,99
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
sw $29,-124($fp)
sw $30,-128($fp)
sw $31,-132($fp)
sub $sp,$fp,132
move $fp,$sp
jal echo_lower
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
lw $30,4($sp)
lw $31,0($sp)
lw $sp,8($sp)
sub $fp,$fp,4
sw $t1,168($sp)
move $t1,$v0

sub $fp,$fp,4
sw $t2,164($sp)
li $t9,101
move $v1,$t9
sub $t2,$v1,$t1
sub $fp,$fp,4
sw $t3,160($sp)
li $t9,1
mul $t3,$t2,$t9
sub $fp,$fp,4
sw $t4,156($sp)
li $t9,1
div $t4,$t3,$t9
sub $fp,$fp,4
sw $t5,152($sp)
add $t5,$t0,$t4
add $v1,$sp,140
sw $t5,4($v1)
sub $fp,$fp,4
sw $t6,-4($sp)
add $v1,$sp,140
lw $t6,4($v1)
li $t9,0
beq $t6,$t9,$LABEL16
li $v0,4
la $a0,$string2
syscall
j $LABEL17
$LABEL16:
$LABEL17:
sub $fp,$fp,4
add $v1,$sp,140
lw $t0,0($v1)
sub $fp,$fp,4
addi $t1,$t0,1
li $v0,1
move $a0,$t1
syscall
sub $fp,$fp,4
add $v1,$sp,140
lw $t2,4($v1)
li $v0,1
move $a0,$t2
syscall
li $v0,11
li $t9,116
move $a0,$t9
syscall
li $v0,1
move $a0,$s0
syscall
li $v0,1
move $a0,$s1
syscall
li $v0,11
li $t9,116
move $a0,$t9
syscall
li $v0,4
la $a0,$string1
syscall
jr $ra

main:


sw $t8,-180($fp)
sw $29,-200($fp)
sw $30,-204($fp)
sw $31,-208($fp)
sub $sp,$fp,208
move $fp,$sp
jal test
lw $t8,28($sp)
lw $30,4($sp)
lw $31,0($sp)
lw $sp,8($sp)
sub $fp,$fp,4
move $t0,$v0

li $v0,5
syscall
move $t9,$v0
sw $t9,4($gp)
li $v0,5
syscall
move $t9,$v0
sw $t9,8($gp)
sub $fp,$fp,4
lw $t9,8($gp)
addi $t1,$t9,1
li $t9,1000
ble $t1,$t9,$LABEL18
li $v0,4
la $a0,$string3
syscall
li $t9,0
move $v0,$t9
li $v0,10
syscall
j $LABEL19
$LABEL18:
$LABEL19:
sub $fp,$fp,4
lw $t9,8($gp)
addi $t0,$t9,1
sub $fp,$fp,4
li $t9,1
mul $t1,$t0,$t9

li $t9,0
sw $t9,-4($fp)
sw $t1,-8($fp)
sw $8,-48($fp)
sw $9,-52($fp)
sw $t8,-112($fp)
sw $29,-132($fp)
sw $30,-136($fp)
sw $31,-140($fp)
sub $sp,$fp,140
move $fp,$sp
jal initial
lw $8,92($sp)
lw $9,88($sp)
lw $t8,28($sp)
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
sw $t8,-112($fp)
sw $29,-132($fp)
sw $30,-136($fp)
sw $31,-140($fp)
sub $sp,$fp,140
move $fp,$sp
jal recursive_cal
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $t8,28($sp)
lw $30,4($sp)
lw $31,0($sp)
lw $sp,8($sp)
sub $fp,$fp,4
move $t3,$v0

sub $fp,$fp,4
li $t4,-1
bne $t3,$t4,$LABEL20
li $v0,4
la $a0,$string3
syscall
j $LABEL21
$LABEL20:
$LABEL21:
li $v0,10
syscall
