.data
    $string0: .asciiz "Sorting finished~"
    $string1: .asciiz "This is item "
    $string2: .asciiz "This is the one we chose, right? ;)"
    $string3: .asciiz "And here comes the best number!"
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
add $t4,$gp,16
mul $t9,$t1,4
add $t9,$t4,$t9
lw $t5,0($t9)
move $t6,$t5
add $t7,$gp,56
mul $t9,$t1,4
add $t9,$t7,$t9
lw $t8,0($t9)
add $t9,$sp,144
sw $t0,0($t9)
move $t0,$t8

add $t9,$sp,140
sw $t2,0($t9)
add $t9,$sp,144
lw $t2,0($t9)
sw $t2,-4($fp)
add $t9,$sp,148
sw $t3,0($t9)
add $t9,$sp,140
lw $t3,0($t9)
sw $t3,-8($fp)
sw $0,-12($fp)
sw $1,-16($fp)
sw $2,-20($fp)
sw $3,-24($fp)
sw $4,-28($fp)
sw $5,-32($fp)
sw $6,-36($fp)
sw $7,-40($fp)
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
lw $3,112($sp)
lw $4,108($sp)
lw $5,104($sp)
lw $6,100($sp)
lw $7,96($sp)
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
lw $sp,8($sp)
add $t9,$gp,16
sw $t4,0($t9)
move $t4,$v0

li $t9,1
bne $t9,$t4,$LABEL3
jr $ra
j $LABEL4
$LABEL3:
$LABEL4:
$LABEL5:
add $t9,$sp,132
sw $t6,0($t9)
li $t6,3
sub $fp,$fp,4
add $t9,$sp,-4
sw $t5,0($t9)
addi $t5,$t6,3
add $t9,$gp,56
sw $t7,0($t9)
addi $t7,$t5,97
add $t9,$sp,152
sw $t1,0($t9)
move $t1,$t7
$LABEL6:
add $t9,$sp,128
sw $t0,0($t9)
sub $fp,$fp,4
add $t9,$sp,-8
sw $t8,0($t9)
add $t0,$gp,16
mul $t9,$t3,4
add $t9,$t0,$t9
lw $t8,0($t9)
add $t9,$sp,144
sw $t2,0($t9)
add $t9,$sp,132
lw $t2,0($t9)
ble $t8,$t2,$LABEL7
li $t9,1
sub $t3,$t3,$t9
j $LABEL6
$LABEL7:
sub $fp,$fp,4
add $t9,$sp,-12
sw $t4,0($t9)
add $t9,$sp,144
lw $t4,0($t9)
ble $t3,$t4,$LABEL8
sub $fp,$fp,4
add $t9,$sp,-16
sw $t6,0($t9)
add $t0,$gp,16
mul $t9,$t3,4
add $t9,$t0,$t9
lw $t6,0($t9)
add $t0,$gp,16
mul $t9,$t4,4
add $t9,$t0,$t9
sw $t6,0($t9)
sub $fp,$fp,4
add $t9,$sp,-20
sw $t5,0($t9)
add $t9,$sp,136
sw $t1,0($t9)
add $t5,$gp,56
mul $t9,$t3,4
add $t9,$t5,$t9
lw $t1,0($t9)
add $t5,$gp,56
mul $t9,$t4,4
add $t9,$t5,$t9
sw $t1,0($t9)
j $LABEL9
$LABEL8:
$LABEL9:
sub $fp,$fp,4
add $t9,$sp,-24
sw $t7,0($t9)
li $t7,-1
sub $fp,$fp,4
add $t9,$sp,-28
sw $t8,0($t9)
li $t8,0
add $t9,$sp,132
sw $t2,0($t9)
sub $t2,$t7,$t8
add $t9,$gp,16
sw $t0,0($t9)
move $t0,$t2
$LABEL10:
sub $fp,$fp,4
add $t9,$sp,-32
sw $t6,0($t9)
add $t9,$sp,140
sw $t3,0($t9)
add $t6,$gp,16
mul $t9,$t4,4
add $t9,$t6,$t9
lw $t3,0($t9)
add $t9,$gp,56
sw $t5,0($t9)
add $t9,$sp,132
lw $t5,0($t9)
bgt $t3,$t5,$LABEL11
addi $t4,$t4,1
j $LABEL10
$LABEL11:
sub $fp,$fp,4
add $t9,$sp,-36
sw $t1,0($t9)
add $t9,$sp,140
lw $t1,0($t9)
bge $t4,$t1,$LABEL12
sub $fp,$fp,4
add $t9,$sp,-40
sw $t7,0($t9)
add $t6,$gp,16
mul $t9,$t4,4
add $t9,$t6,$t9
lw $t7,0($t9)
add $t6,$gp,16
mul $t9,$t1,4
add $t9,$t6,$t9
sw $t7,0($t9)
sub $fp,$fp,4
add $t9,$sp,-44
sw $t8,0($t9)
add $t9,$sp,136
sw $t0,0($t9)
add $t8,$gp,56
mul $t9,$t4,4
add $t9,$t8,$t9
lw $t0,0($t9)
add $t8,$gp,56
mul $t9,$t1,4
add $t9,$t8,$t9
sw $t0,0($t9)
j $LABEL13
$LABEL12:
$LABEL13:
bne $t4,$t1,$LABEL5
add $t6,$gp,16
mul $t9,$t4,4
add $t9,$t6,$t9
sw $t5,0($t9)
add $t8,$gp,56
sub $fp,$fp,4
add $t9,$sp,-48
sw $t2,0($t9)
add $t9,$sp,128
lw $t2,0($t9)
mul $t9,$t1,4
add $t9,$t8,$t9
sw $t2,0($t9)
sub $fp,$fp,4
add $t9,$sp,-52
sw $t3,0($t9)
li $t9,1
sub $t3,$t4,$t9

sub $fp,$fp,4
add $t9,$sp,-56
sw $t7,0($t9)
add $t9,$sp,152
lw $t7,0($t9)
sw $t7,-4($fp)
sw $t3,-8($fp)
sw $0,-32($fp)
sw $1,-36($fp)
sw $2,-40($fp)
sw $3,-44($fp)
sw $4,-48($fp)
sw $5,-52($fp)
sw $6,-56($fp)
sw $7,-60($fp)
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
lw $3,112($sp)
lw $4,108($sp)
lw $5,104($sp)
lw $6,100($sp)
lw $7,96($sp)
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
lw $sp,8($sp)
sub $fp,$fp,4
add $t9,$sp,-60
sw $t0,0($t9)
move $t0,$v0

add $t9,$gp,16
sw $t6,0($t9)
addi $t6,$t4,1

sw $t6,-4($fp)
add $t9,$sp,132
sw $t5,0($t9)
add $t9,$sp,148
lw $t5,0($t9)
sw $t5,-8($fp)
sw $0,-32($fp)
sw $1,-36($fp)
sw $2,-40($fp)
sw $3,-44($fp)
sw $4,-48($fp)
sw $5,-52($fp)
sw $6,-56($fp)
sw $7,-60($fp)
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
lw $3,112($sp)
lw $4,108($sp)
lw $5,104($sp)
lw $6,100($sp)
lw $7,96($sp)
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
lw $sp,8($sp)
add $t9,$gp,56
sw $t8,0($t9)
move $t8,$v0

jr $ra

initialize:
li $t0,9
move $t1,$t0
$LABEL14:
li $t9,0
ble $t1,$t9,$LABEL15
li $t2,2
li $t9,2
sub $t3,$t2,$t9
add $t4,$gp,16
mul $t9,$t1,4
add $t9,$t4,$t9
sw $t3,0($t9)
li $t9,1
sub $t1,$t1,$t9
j $LABEL14
$LABEL15:
li $t9,99
move $v0,$t9
jr $ra
jr $ra

main:

sw $0,-8($fp)
sw $1,-12($fp)
sw $2,-16($fp)
sw $3,-20($fp)
sw $4,-24($fp)
sw $5,-28($fp)
sw $6,-32($fp)
sw $7,-36($fp)
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
lw $3,112($sp)
lw $4,108($sp)
lw $5,104($sp)
lw $6,100($sp)
lw $7,96($sp)
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
lw $sp,8($sp)
move $t0,$v0

li $t9,99
bne $t0,$t9,$LABEL16
li $t1,0
$LABEL17:
li $t9,10
bge $t1,$t9,$LABEL18
li $v0,5
syscall
move $t2,$v0
li $v0,12
syscall
move $t3,$v0
add $t4,$gp,16
mul $t9,$t1,4
add $t9,$t4,$t9
sw $t2,0($t9)
add $t5,$gp,56
mul $t9,$t1,4
add $t9,$t5,$t9
sw $t3,0($t9)
addi $t1,$t1,1
j $LABEL17
$LABEL18:
li $t6,9

li $t9,0
sw $t9,-4($fp)
sw $t6,-8($fp)
sw $0,-32($fp)
sw $1,-36($fp)
sw $2,-40($fp)
sw $3,-44($fp)
sw $4,-48($fp)
sw $5,-52($fp)
sw $6,-56($fp)
sw $7,-60($fp)
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
lw $3,112($sp)
lw $4,108($sp)
lw $5,104($sp)
lw $6,100($sp)
lw $7,96($sp)
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
lw $sp,8($sp)
move $t7,$v0

li $v0,4
la $a0,$string0
syscall
li $t1,0
$LABEL19:
li $t9,10
bge $t1,$t9,$LABEL20
li $v0,4
la $a0,$string1
syscall
addi $t8,$t1,1
li $v0,1
move $a0,$t8
syscall
sub $fp,$fp,4
add $t9,$sp,-4
sw $t0,0($t9)
add $t4,$gp,16
mul $t9,$t1,4
add $t9,$t4,$t9
lw $t0,0($t9)
li $v0,1
move $a0,$t0
syscall
add $t9,$sp,132
sw $t2,0($t9)
add $t5,$gp,56
mul $t9,$t1,4
add $t9,$t5,$t9
lw $t2,0($t9)
li $t9,119
bne $t2,$t9,$LABEL21
li $v0,4
la $a0,$string2
syscall
j $LABEL22
$LABEL21:
$LABEL22:
add $t9,$sp,128
sw $t3,0($t9)
add $t4,$gp,16
mul $t9,$t1,4
add $t9,$t4,$t9
lw $t3,0($t9)
li $t9,42
bne $t3,$t9,$LABEL23
li $v0,4
la $a0,$string3
syscall
j $LABEL24
$LABEL23:
$LABEL24:
addi $t1,$t1,1
j $LABEL19
$LABEL20:
j $LABEL25
$LABEL16:
$LABEL25:
li $v0,10
syscall
