.data
    $string0: .asciiz " "
    $string1: .asciiz "\\n"
    $string2: .asciiz "ERROR!"
.text
    sub $sp,$sp,136
    move $fp,$sp
    sub $fp,$fp,36
    j main
recursive_cal:
lw $t9,8($gp)
bne $a1,$t9,$LABEL1
lw $t0,12($gp)
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
jr $ra
$LABEL1:
$LABEL4:
move  $s0,$a2
$LABEL5:
lw $t9,4($gp)
add $t0,$a1,$t9
lw $t9,8($gp)
sub $t1,$t0,$t9
addi $t2,$t1,1
bgt $s0,$t2,$LABEL6
add $v1,$gp,12
sll $t9,$a1,2
add $v1,$v1,$t9
sw $s0,0($v1)
addi $t0,$a1,1
addi $t1,$t0,0
addi $t2,$s0,1
addi $t3,$t2,0
sw $5,-36($fp)
sw $6,-40($fp)
sw $8,-48($fp)
sw $9,-52($fp)
sw $10,-56($fp)
sw $11,-60($fp)
sw $16,-80($fp)
sw $ra,-140($fp)
move $a1,$t1
move $a2,$t3
sub $sp,$fp,140
sub $fp,$sp,60
jal recursive_cal
lw $5,104($sp)
lw $6,100($sp)
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $11,80($sp)
lw $16,60($sp)
lw $ra,0($sp)
add $fp,$fp,200
add $sp,$sp,200
move $t4,$v0
addi $t5,$s0,1
move  $s0,$t5
j $LABEL5
$LABEL6:
jr $ra
initial:
li $s0,0
$LABEL7:
add $v1,$gp,12
sll $t9,$s0,2
add $v1,$v1,$t9
sw $a1,0($v1)
addi $t0,$s0,1
move  $s0,$t0
ble $s0,$a2,$LABEL7
jr $ra
jr $ra
main:
li $v0,5
syscall
move $t9,,$v0
sw $t9,4($gp)
li $v0,5
syscall
move $t9,,$v0
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
$LABEL8:
$LABEL9:
li $t0,0
lw $t9,8($gp)
addi $t1,$t9,1
addi $t2,$t1,0
sw $8,-48($fp)
sw $9,-52($fp)
sw $10,-56($fp)
sw $ra,-140($fp)
move $a1,$t0
move $a2,$t2
sub $sp,$fp,140
sub $fp,$sp,8
jal initial
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $ra,0($sp)
add $fp,$fp,148
add $sp,$sp,176
move $t3,$v0
li $t4,0
li $t5,1
sw $8,-48($fp)
sw $9,-52($fp)
sw $10,-56($fp)
sw $11,-60($fp)
sw $12,-64($fp)
sw $13,-68($fp)
sw $ra,-140($fp)
move $a1,$t4
move $a2,$t5
sub $sp,$fp,140
sub $fp,$sp,60
jal recursive_cal
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $11,80($sp)
lw $12,76($sp)
lw $13,72($sp)
lw $ra,0($sp)
add $fp,$fp,200
add $sp,$sp,176
move $t6,$v0
li $v0,10
syscall
