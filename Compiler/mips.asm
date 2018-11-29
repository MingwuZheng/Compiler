.data
    $string0: .asciiz "Sorting finished~"
    $string1: .asciiz "And here comes the best number!"
.text
    sub $sp,$sp,144
    move $fp,$sp
    j main

comparison:

add $t9,$sp,132
lw $t0,0($t9)
add $t9,$sp,128
lw $t1,0($t9)
ble $t0,$t1,$LABEL1
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

add $t9,$sp,152
lw $t1,0($t9)
move $t0,$t1
add $t9,$sp,148
lw $t3,0($t9)
move $t2,$t3
add $v0,$gp,16
mul $t9,$t1,4
add $t9,$v0,$t9
lw $t4,0($t9)
move $t5,$t4
add $v0,$gp,56
mul $t9,$t1,4
add $t9,$v0,$t9
lw $t6,0($t9)
move $t7,$t6

sw $t0,-4($fp)
sw $t2,-8($fp)
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
sw $19,-88($fp)
sw $20,-92($fp)
sw $21,-96($fp)
sw $22,-100($fp)
sw $23,-104($fp)
sw $24,-108($fp)
sw $25,-112($fp)
sw $26,-116($fp)
sw $27,-120($fp)
sw $28,-124($fp)
sw $29,-128($fp)
sw $30,-132($fp)
sw $31,-136($fp)
sub $sp,$fp,136
move $fp,$sp
jal comparison
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
lw $26,20($sp)
lw $27,16($sp)
lw $28,12($sp)
lw $30,4($sp)
lw $31,0($sp)
lw $sp,8($sp)
move $t8,$v0

li $t9,1
bne $t9,$t8,$LABEL3
jr $ra
j $LABEL4
$LABEL3:
$LABEL4:
$LABEL5:
ble $t2,$t0,$LABEL6
add $t9,$sp,148
sw $t3,0($t9)
add $v0,$gp,16
mul $t9,$t2,4
add $t9,$v0,$t9
lw $t3,0($t9)
add $v0,$gp,16
mul $t9,$t0,4
add $v0,$v0,$t9
sw $t3,0($v0)
add $t9,$sp,132
sw $t5,0($t9)
add $v0,$gp,56
mul $t9,$t2,4
add $t9,$v0,$t9
lw $t5,0($t9)
add $v0,$gp,56
mul $t9,$t0,4
add $v0,$v0,$t9
sw $t5,0($v0)
j $LABEL7
$LABEL6:
$LABEL7:
bge $t0,$t2,$LABEL8
sub $fp,$fp,4
add $t9,$sp,-4
sw $t4,0($t9)
add $v0,$gp,16
mul $t9,$t0,4
add $t9,$v0,$t9
lw $t4,0($t9)
add $v0,$gp,16
mul $t9,$t2,4
add $v0,$v0,$t9
sw $t4,0($v0)
add $t9,$sp,152
sw $t1,0($t9)
add $v0,$gp,56
mul $t9,$t0,4
add $t9,$v0,$t9
lw $t1,0($t9)
add $v0,$gp,56
mul $t9,$t2,4
add $v0,$v0,$t9
sw $t1,0($v0)
j $LABEL9
$LABEL8:
$LABEL9:
bne $t0,$t2,$LABEL5
add $v0,$gp,16
mul $t9,$t0,4
add $v0,$v0,$t9
add $t9,$sp,128
sw $t7,0($t9)
add $t9,$sp,132
lw $t7,0($t9)
sw $t7,0($v0)
add $v0,$gp,56
mul $t9,$t2,4
add $v0,$v0,$t9
sub $fp,$fp,4
add $t9,$sp,-8
sw $t6,0($t9)
add $t9,$sp,128
lw $t6,0($t9)
sw $t6,0($v0)
sub $fp,$fp,4
add $t9,$sp,-12
sw $t8,0($t9)
li $t9,1
sub $t8,$t0,$t9

sub $fp,$fp,4
add $t9,$sp,-16
sw $t3,0($t9)
add $t9,$sp,152
lw $t3,0($t9)
sw $t3,-4($fp)
sw $t8,-8($fp)
sw $8,-64($fp)
sw $9,-68($fp)
sw $10,-72($fp)
sw $11,-76($fp)
sw $12,-80($fp)
sw $13,-84($fp)
sw $14,-88($fp)
sw $15,-92($fp)
sw $16,-96($fp)
sw $17,-100($fp)
sw $18,-104($fp)
sw $19,-108($fp)
sw $20,-112($fp)
sw $21,-116($fp)
sw $22,-120($fp)
sw $23,-124($fp)
sw $24,-128($fp)
sw $25,-132($fp)
sw $26,-136($fp)
sw $27,-140($fp)
sw $28,-144($fp)
sw $29,-148($fp)
sw $30,-152($fp)
sw $31,-156($fp)
sub $sp,$fp,156
move $fp,$sp
jal quickSort
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
lw $26,20($sp)
lw $27,16($sp)
lw $28,12($sp)
lw $30,4($sp)
lw $31,0($sp)
lw $sp,8($sp)
sub $fp,$fp,4
add $t9,$sp,-20
sw $t5,0($t9)
move $t5,$v0

sub $fp,$fp,4
add $t9,$sp,-24
sw $t4,0($t9)
addi $t4,$t0,1

sw $t4,-4($fp)
sub $fp,$fp,4
add $t9,$sp,-28
sw $t1,0($t9)
add $t9,$sp,148
lw $t1,0($t9)
sw $t1,-8($fp)
sw $8,-64($fp)
sw $9,-68($fp)
sw $10,-72($fp)
sw $11,-76($fp)
sw $12,-80($fp)
sw $13,-84($fp)
sw $14,-88($fp)
sw $15,-92($fp)
sw $16,-96($fp)
sw $17,-100($fp)
sw $18,-104($fp)
sw $19,-108($fp)
sw $20,-112($fp)
sw $21,-116($fp)
sw $22,-120($fp)
sw $23,-124($fp)
sw $24,-128($fp)
sw $25,-132($fp)
sw $26,-136($fp)
sw $27,-140($fp)
sw $28,-144($fp)
sw $29,-148($fp)
sw $30,-152($fp)
sw $31,-156($fp)
sub $sp,$fp,156
move $fp,$sp
jal quickSort
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
lw $26,20($sp)
lw $27,16($sp)
lw $28,12($sp)
lw $30,4($sp)
lw $31,0($sp)
lw $sp,8($sp)
add $t9,$sp,132
sw $t7,0($t9)
move $t7,$v0

jr $ra

initialize:

li $t0,9
move $t1,$t0
$LABEL10:
li $t9,0
ble $t1,$t9,$LABEL11
li $t2,2
li $t9,2
sub $t3,$t2,$t9
add $v0,$gp,16
mul $t9,$t1,4
add $v0,$v0,$t9
sw $t3,0($v0)
li $t9,1
sub $t1,$t1,$t9
j $LABEL10
$LABEL11:
li $t9,99
move $v0,$t9
jr $ra
jr $ra

main:


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
sw $19,-84($fp)
sw $20,-88($fp)
sw $21,-92($fp)
sw $22,-96($fp)
sw $23,-100($fp)
sw $24,-104($fp)
sw $25,-108($fp)
sw $26,-112($fp)
sw $27,-116($fp)
sw $28,-120($fp)
sw $29,-124($fp)
sw $30,-128($fp)
sw $31,-132($fp)
sub $sp,$fp,132
move $fp,$sp
jal initialize
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
lw $26,20($sp)
lw $27,16($sp)
lw $28,12($sp)
lw $30,4($sp)
lw $31,0($sp)
lw $sp,8($sp)
move $t0,$v0

li $t9,99
bne $t0,$t9,$LABEL12
li $t1,0
$LABEL13:
li $t9,10
bge $t1,$t9,$LABEL14
li $v0,5
syscall
move $t2,$v0
add $v0,$gp,16
mul $t9,$t1,4
add $v0,$v0,$t9
sw $t2,0($v0)
addi $t1,$t1,1
j $LABEL13
$LABEL14:
li $t3,9

li $t9,0
sw $t9,-4($fp)
sw $t3,-8($fp)
sw $8,-64($fp)
sw $9,-68($fp)
sw $10,-72($fp)
sw $11,-76($fp)
sw $12,-80($fp)
sw $13,-84($fp)
sw $14,-88($fp)
sw $15,-92($fp)
sw $16,-96($fp)
sw $17,-100($fp)
sw $18,-104($fp)
sw $19,-108($fp)
sw $20,-112($fp)
sw $21,-116($fp)
sw $22,-120($fp)
sw $23,-124($fp)
sw $24,-128($fp)
sw $25,-132($fp)
sw $26,-136($fp)
sw $27,-140($fp)
sw $28,-144($fp)
sw $29,-148($fp)
sw $30,-152($fp)
sw $31,-156($fp)
sub $sp,$fp,156
move $fp,$sp
jal quickSort
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
lw $26,20($sp)
lw $27,16($sp)
lw $28,12($sp)
lw $30,4($sp)
lw $31,0($sp)
lw $sp,8($sp)
move $t4,$v0

li $v0,4
la $a0,$string0
syscall
li $t1,0
$LABEL15:
li $t9,10
bge $t1,$t9,$LABEL16
add $v0,$gp,16
mul $t9,$t1,4
add $t9,$v0,$t9
lw $t5,0($t9)
li $v0,1
move $a0,$t5
syscall
add $v0,$gp,16
mul $t9,$t1,4
add $t9,$v0,$t9
lw $t6,0($t9)
li $t9,42
bne $t6,$t9,$LABEL17
li $v0,4
la $a0,$string1
syscall
j $LABEL18
$LABEL17:
$LABEL18:
addi $t1,$t1,1
j $LABEL15
$LABEL16:
j $LABEL19
$LABEL12:
$LABEL19:
li $v0,10
syscall
