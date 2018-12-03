.data
    $string0: .asciiz "Sorting finished~"
    $string1: .asciiz "This is item : "
    $string2: .asciiz "This is the one we chose, right? ;)"
    $string3: .asciiz "And here comes the best number!"
.text
    sub $sp,$sp,144
    move $fp,$sp
    sub $fp,$fp,52
    j main

comparison:

lw $s0,132($sp)
lw $s1,128($sp)
blt $s0,$s1,$LABEL1
li $t9,1
move $v0,$t9
jr $ra
j $LABEL2
$LABEL1:
li $t9,0
move $v0,$t9
jr $ra
$LABEL2:
jr $ra

quickSort:

lw $s0,164($sp)
lw $s1,160($sp)
move $s3,$s0
move $s4,$s1
add $v1,$gp,16
sll $t9,$s0,2
add $t9,$v1,$t9
lw $t0,0($t9)
move $s5,$t0
add $v1,$gp,56
sll $t9,$s0,2
add $t9,$v1,$t9
lw $t1,0($t9)
move $s6,$t1

sw $s3,-4($fp)
sw $s4,-8($fp)
sw $8,-44($fp)
sw $9,-48($fp)
sw $16,-76($fp)
sw $17,-80($fp)
sw $18,-84($fp)
sw $19,-88($fp)
sw $20,-92($fp)
sw $21,-96($fp)
sw $22,-100($fp)
sw $23,-104($fp)
sw $t8,-108($fp)
sw $29,-128($fp)
sw $30,-132($fp)
sw $31,-136($fp)
sub $sp,$fp,136
move $fp,$sp
sub $fp,$fp,4
jal comparison
lw $8,92($sp)
lw $9,88($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $19,48($sp)
lw $20,44($sp)
lw $21,40($sp)
lw $22,36($sp)
lw $23,32($sp)
lw $t8,28($sp)
lw $30,4($sp)
lw $31,0($sp)
lw $sp,8($sp)
move $t2,$v0

li $t9,1
move $v1,$t9
bne $v1,$t2,$LABEL3
jr $ra
j $LABEL4
$LABEL3:
$LABEL4:
$LABEL5:
li $s7,0
li $t0,3
addi $t1,$t0,3
addi $t2,$t1,97
move $t3,$t2
$LABEL6:
add $v1,$gp,16
sll $t9,$s4,2
add $t9,$v1,$t9
lw $t0,0($t9)
blt $t0,$s5,$LABEL7
bne $s4,$s3,$LABEL8
li $s7,1
add $v1,$gp,16
sll $t9,$s4,2
add $t9,$v1,$t9
lw $t0,0($t9)
move $s2,$t0
add $v1,$gp,16
sll $t9,$s4,2
add $v1,$v1,$t9
sw $s5,0($v1)
j $LABEL9
$LABEL8:
$LABEL9:
li $t9,1
sub $s4,$s4,$t9
j $LABEL6
$LABEL7:
li $t9,0
beq $s7,$t9,$LABEL10
addi $t0,$s4,1
move $s4,$t0
add $v1,$gp,16
sll $t9,$s4,2
add $v1,$v1,$t9
sw $s2,0($v1)
j $LABEL11
$LABEL10:
$LABEL11:
ble $s4,$s3,$LABEL12
add $v1,$gp,16
sll $t9,$s4,2
add $t9,$v1,$t9
lw $t0,0($t9)
add $v1,$gp,16
sll $t9,$s3,2
add $v1,$v1,$t9
sw $t0,0($v1)
add $v1,$gp,56
sll $t9,$s4,2
add $t9,$v1,$t9
lw $t1,0($t9)
add $v1,$gp,56
sll $t9,$s3,2
add $v1,$v1,$t9
sw $t1,0($v1)
addi $t2,$s3,1
move $s3,$t2
j $LABEL13
$LABEL12:
$LABEL13:
li $s7,0
li $t0,-1
li $t1,6
sub $t2,$t0,$t1
li $t9,-1
sub $t3,$t2,$t9
addi $t4,$t3,-1
li $t5,194
add $t6,$t4,$t5
move $t7,$t6
$LABEL14:
add $v1,$gp,16
sll $t9,$s3,2
add $t9,$v1,$t9
lw $t0,0($t9)
bgt $t0,$s5,$LABEL15
bne $s3,$s4,$LABEL16
li $s7,1
add $v1,$gp,16
sll $t9,$s3,2
add $t9,$v1,$t9
lw $t0,0($t9)
move $s2,$t0
add $v1,$gp,16
sll $t9,$s3,2
add $v1,$v1,$t9
sw $s5,0($v1)
j $LABEL17
$LABEL16:
$LABEL17:
addi $s3,$s3,1
j $LABEL14
$LABEL15:
li $t9,0
beq $s7,$t9,$LABEL18
li $t9,1
sub $t0,$s3,$t9
move $s3,$t0
add $v1,$gp,16
sll $t9,$s3,2
add $v1,$v1,$t9
sw $s2,0($v1)
j $LABEL19
$LABEL18:
$LABEL19:
bge $s3,$s4,$LABEL20
add $v1,$gp,16
sll $t9,$s3,2
add $t9,$v1,$t9
lw $t0,0($t9)
add $v1,$gp,16
sll $t9,$s4,2
add $v1,$v1,$t9
sw $t0,0($v1)
add $v1,$gp,56
sll $t9,$s3,2
add $t9,$v1,$t9
lw $t1,0($t9)
add $v1,$gp,56
sll $t9,$s4,2
add $v1,$v1,$t9
sw $t1,0($v1)
li $t9,1
sub $t2,$s4,$t9
move $s4,$t2
j $LABEL21
$LABEL20:
$LABEL21:
blt $s3,$s4,$LABEL5
add $v1,$gp,16
sll $t9,$s3,2
add $v1,$v1,$t9
sw $s5,0($v1)
add $v1,$gp,56
sll $t9,$s4,2
add $v1,$v1,$t9
sw $s6,0($v1)
li $t9,1
sub $t0,$s3,$t9

sw $s0,-4($fp)
sw $t0,-8($fp)
sw $8,-76($fp)
sw $16,-108($fp)
sw $17,-112($fp)
sw $18,-116($fp)
sw $19,-120($fp)
sw $20,-124($fp)
sw $21,-128($fp)
sw $22,-132($fp)
sw $23,-136($fp)
sw $t8,-140($fp)
sw $29,-160($fp)
sw $30,-164($fp)
sw $31,-168($fp)
sub $sp,$fp,168
move $fp,$sp
sub $fp,$fp,156
jal quickSort
lw $8,92($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $19,48($sp)
lw $20,44($sp)
lw $21,40($sp)
lw $22,36($sp)
lw $23,32($sp)
lw $t8,28($sp)
lw $30,4($sp)
lw $31,0($sp)
lw $sp,8($sp)
move $t1,$v0

addi $t2,$s3,1

sw $t2,-4($fp)
sw $s1,-8($fp)
sw $8,-76($fp)
sw $9,-80($fp)
sw $10,-84($fp)
sw $16,-108($fp)
sw $17,-112($fp)
sw $18,-116($fp)
sw $19,-120($fp)
sw $20,-124($fp)
sw $21,-128($fp)
sw $22,-132($fp)
sw $23,-136($fp)
sw $t8,-140($fp)
sw $29,-160($fp)
sw $30,-164($fp)
sw $31,-168($fp)
sub $sp,$fp,168
move $fp,$sp
sub $fp,$fp,156
jal quickSort
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $19,48($sp)
lw $20,44($sp)
lw $21,40($sp)
lw $22,36($sp)
lw $23,32($sp)
lw $t8,28($sp)
lw $30,4($sp)
lw $31,0($sp)
lw $sp,8($sp)
move $t3,$v0

jr $ra

initialize:

li $t0,9
move $s0,$t0
$LABEL22:
li $t0,-1
ble $s0,$t0,$LABEL23
li $t0,2
li $t9,2
sub $t1,$t0,$t9
add $v1,$gp,16
sll $t9,$s0,2
add $v1,$v1,$t9
sw $t1,0($v1)
li $t9,1
sub $s0,$s0,$t9
j $LABEL22
$LABEL23:
li $t9,99
move $v0,$t9
jr $ra
jr $ra

main:


sw $16,-72($fp)
sw $t8,-104($fp)
sw $29,-124($fp)
sw $30,-128($fp)
sw $31,-132($fp)
sub $sp,$fp,132
move $fp,$sp
sub $fp,$fp,20
jal initialize
lw $16,60($sp)
lw $t8,28($sp)
lw $30,4($sp)
lw $31,0($sp)
lw $sp,8($sp)
move $t0,$v0

li $t9,99
bne $t0,$t9,$LABEL24
li $s0,0
$LABEL25:
li $t9,10
bge $s0,$t9,$LABEL26
li $v0,5
syscall
move $t0,$v0
li $v0,12
syscall
move $t1,$v0
add $v1,$gp,16
sll $t9,$s0,2
add $v1,$v1,$t9
sw $t0,0($v1)
add $v1,$gp,56
sll $t9,$s0,2
add $v1,$v1,$t9
sw $t1,0($v1)
addi $s0,$s0,1
j $LABEL25
$LABEL26:
li $t0,9

li $t9,0
sw $t9,-4($fp)
sw $t0,-8($fp)
sw $8,-76($fp)
sw $16,-108($fp)
sw $t8,-140($fp)
sw $29,-160($fp)
sw $30,-164($fp)
sw $31,-168($fp)
sub $sp,$fp,168
move $fp,$sp
sub $fp,$fp,156
jal quickSort
lw $8,92($sp)
lw $16,60($sp)
lw $t8,28($sp)
lw $30,4($sp)
lw $31,0($sp)
lw $sp,8($sp)
move $t1,$v0

li $v0,4
la $a0,$string0
syscall
li $s0,0
$LABEL27:
li $t0,9
bgt $s0,$t0,$LABEL28
li $v0,4
la $a0,$string1
syscall
addi $t0,$s0,1
li $v0,1
move $a0,$t0
syscall
add $v1,$gp,16
sll $t9,$s0,2
add $t9,$v1,$t9
lw $t1,0($t9)
li $v0,1
move $a0,$t1
syscall
add $v1,$gp,56
sll $t9,$s0,2
add $t9,$v1,$t9
lw $t2,0($t9)
li $t9,119
bne $t2,$t9,$LABEL29
li $v0,4
la $a0,$string2
syscall
j $LABEL30
$LABEL29:
$LABEL30:
add $v1,$gp,16
sll $t9,$s0,2
add $t9,$v1,$t9
lw $t0,0($t9)
li $t9,42
bne $t0,$t9,$LABEL31
li $v0,4
la $a0,$string3
syscall
j $LABEL32
$LABEL31:
$LABEL32:
addi $s0,$s0,1
j $LABEL27
$LABEL28:
j $LABEL33
$LABEL24:
$LABEL33:
li $v0,10
syscall
