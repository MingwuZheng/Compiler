.data
    $string0: .asciiz " "
    $string1: .asciiz "\\n"
    $string2: .asciiz "ERROR!"
    $string3: .asciiz "ERROR!\\n"
.text
    sub $sp,$sp,136
    move $fp,$sp
    sub $fp,$fp,52
    j main
recursive_cal:
lw $s1,136($sp)
lw $s0,132($sp)
lw $t9,8($gp)
bne $s1,$t9,$LABEL1
add $v1,$gp,12
lw $t0,0($v1)
li $v0,1
move $a0,$t0
syscall
li $s0,1
$LABEL2:
lw $t9,8($gp)
bge $s0,$t9,$LABEL3
li $v0,4
la $a0,$string0
syscall
add $v1,$gp,12
sll $t9,$s0,2
add $t9,$v1,$t9
lw $t0,0($t9)
li $v0,1
move $a0,$t0
syscall
addi $t1,$s0,1
move  $s0,$t1
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
bge $s1,$t9,$LABEL5
move  $s0,$s0
$LABEL6:
lw $t9,4($gp)
add $t0,$s1,$t9
lw $t9,8($gp)
sub $t1,$t0,$t9
addi $t2,$t1,1
bgt $s0,$t2,$LABEL7
add $v1,$gp,12
sll $t9,$s1,,2
add $v1,$v1,$t9
sw $s0,0($v1)
addi $t0,$s1,1
addi $t1,$t0,0
addi $t2,$s0,1
addi $t3,$t2,0
sw $t1,-4($fp)
sw $t3,-8($fp)
sw $8,-48($fp)
sw $9,-52($fp)
sw $10,-56($fp)
sw $11,-60($fp)
sw $16,-80($fp)
sw $17,-84($fp)
sw $ra,-140($fp)
sub $sp,$fp,140
sub $fp,$sp,80
jal recursive_cal
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $11,80($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $ra,0($sp)
add $fp,$fp,220
add $sp,$sp,220
move $t4,$v0
li $t5,-1
bne $t4,$t5,$LABEL8
li $t0,-1
move $v0,$t0
jr $ra
$LABEL8:
$LABEL9:
addi $t0,$s0,1
move  $s0,$t0
j $LABEL6
$LABEL7:
li $t9,0
move $v0,$t9
jr $ra
j $LABEL10
$LABEL5:
li $t0,-1
move $v0,$t0
jr $ra
$LABEL10:
$LABEL4:
jr $ra
initial:
lw $s2,136($sp)
lw $s1,132($sp)
li $s0,0
$LABEL11:
add $v1,$gp,12
sll $t9,$s0,,2
add $v1,$v1,$t9
sw $s2,0($v1)
addi $t0,$s0,1
move  $s0,$t0
ble $s0,$s1,$LABEL11
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
li  $t0,105
li  $t1,106
li  $t2,107
li  $t3,108
li $t4,109
li $t5,110
li $s1,111
li $s0,112
li $t6,-1
add $v1,$sp,140
sw $t6,0($v1)
add $v1,$sp,140
lw $t7,0($v1)
li $t9,-2
mul $t8,$t7,$t9
sw $t0,172($sp)
sub $t0,$0,$t8
sw $t1,168($sp)
li $t1,99
sw $t1,-4($fp)
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
sw $24,-104($fp)
sw $ra,-132($fp)
sub $sp,$fp,132
sub $fp,$sp,8
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
lw $24,28($sp)
lw $ra,0($sp)
add $fp,$fp,140
add $sp,$sp,192
sw $t2,164($sp)
move $t2,$v0
sw $t3,160($sp)
li $t9,101
move $v1,$t9
sub $t3,$v1,$t2
sw $t4,156($sp)
li $t9,1
mul $t4,$t3,$t9
sw $t5,152($sp)
li $t9,1
div $t5,$t4,$t9
sw $t6,-4($sp)
add $t6,$t0,$t5
add $v1,$sp,140
sw $t6,4($v1)
sw $t7,-8($sp)
add $v1,$sp,140
lw $t7,4($v1)
li $t9,0
beq $t7,$t9,$LABEL16
li $v0,4
la $a0,$string2
syscall
$LABEL16:
$LABEL17:
add $v1,$sp,140
lw $t0,0($v1)
addi $t1,$t0,1
li $v0,1
move $a0,$t1
syscall
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
move $a0,$s1
syscall
li $v0,1
move $a0,$s0
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
sw $ra,-208($fp)
sub $sp,$fp,208
sub $fp,$sp,60
jal test
lw $ra,0($sp)
add $fp,$fp,268
add $sp,$sp,260
move $t0,$v0
li $v0,5
syscall
move $t9,,$v0
sw $t9,4($gp)
li $v0,5
syscall
move $t9,,$v0
sw $t9,8($gp)
lw $t9,8($gp)
addi $t1,$t9,1
li $t9,1000
ble $t1,$t9,$LABEL18
li $v0,4
la $a0,$string3
syscall
li $v0,10
syscall
$LABEL18:
$LABEL19:
li $t0,0
lw $t9,8($gp)
addi $t1,$t9,1
li $t9,1
mul $t2,$t1,$t9
addi $t3,$t2,0
sw $t0,-4($fp)
sw $t3,-8($fp)
sw $8,-48($fp)
sw $9,-52($fp)
sw $10,-56($fp)
sw $11,-60($fp)
sw $ra,-140($fp)
sub $sp,$fp,140
sub $fp,$sp,8
jal initial
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $11,80($sp)
lw $ra,0($sp)
add $fp,$fp,148
add $sp,$sp,192
move $t4,$v0
li $t5,0
li $t6,1
sw $t5,-4($fp)
sw $t6,-8($fp)
sw $8,-48($fp)
sw $9,-52($fp)
sw $10,-56($fp)
sw $11,-60($fp)
sw $12,-64($fp)
sw $13,-68($fp)
sw $14,-72($fp)
sw $ra,-140($fp)
sub $sp,$fp,140
sub $fp,$sp,80
jal recursive_cal
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $11,80($sp)
lw $12,76($sp)
lw $13,72($sp)
lw $14,68($sp)
lw $ra,0($sp)
add $fp,$fp,220
add $sp,$sp,192
move $t7,$v0
li $t8,-1
bne $t7,$t8,$LABEL20
li $v0,4
la $a0,$string3
syscall
$LABEL20:
$LABEL21:
li $v0,10
syscall
