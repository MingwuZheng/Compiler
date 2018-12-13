.data
    $string0: .asciiz "_ff4_"
    $string1: .asciiz "___ !#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~___\\n\\t\\\\\\'___"
    $string2: .asciiz ""
    $string3: .asciiz "@@@@@"
    $string4: .asciiz "error1"
    $string5: .asciiz "error2"
    $string6: .asciiz "error3"
    $string7: .asciiz "error4"
    $string8: .asciiz "error5"
    $string9: .asciiz "error6"
    $string10: .asciiz "error7"
    $string11: .asciiz "error8"
    $string12: .asciiz "error9"
    $string13: .asciiz " "
    $string14: .asciiz "error10"
    $string15: .asciiz "error11"
    $string16: .asciiz "error12"
    $string17: .asciiz " ojbk"
    $string18: .asciiz "error13"
    $string19: .asciiz "error14"
.text
    sub $sp,$sp,1916
    move $fp,$sp
    sub $fp,$fp,600
    j main

ff1:

lw $s0,132($sp)
li $t9,98
sw $t9,12($gp)
move $v0,$s0
jr $ra
jr $ra

ff2:

li $t9,45
sw $t9,16($gp)
li $t0,3
addi $t1,$t0,3
move $v0,$t1
jr $ra
jr $ra

ff3:

lw $s5,148($sp)
lw $s4,144($sp)
lw $s3,140($sp)
lw $s2,136($sp)
lw $s1,132($sp)
lw $s0,128($sp)
add $t0,$s5,$s4
add $t1,$t0,$s3
add $t2,$t1,$s2
add $t3,$t2,$s1
add $t4,$t3,$s0
li $v0,1
move $a0,$t4
syscall
jr $ra
jr $ra

ff4:

li $v0,4
la $a0,$string0
syscall
jr $ra

factorial:

lw $s0,132($sp)
li $t9,1
bne $s0,$t9,$LABEL1
li $t9,1
move $v0,$t9
jr $ra
j $LABEL2
$LABEL1:
li $t9,1
sub $t0,$s0,$t9
addi $t1,$t0,0

sw $t1,-4($fp)
sw $8,-44($fp)
sw $9,-48($fp)
sw $16,-76($fp)
sw $ra,-136($fp)
sub $sp,$fp,136
sub $fp,$sp,20
jal factorial
lw $8,92($sp)
lw $9,88($sp)
lw $16,60($sp)
lw $ra,0($sp)
add $fp,$fp,156
add $sp,$sp,156
move $t2,$v0

mul $t3,$t2,$s0
move $t4,$t3
move $v0,$t4
jr $ra
$LABEL2:
jr $ra

ff5:

li $t0,4
sw $t0,128($sp)
addi $t1,$t0,122
lw $t9,12($gp)
add $t2,$t1,$t9
li $v0,1
move $a0,$t2
syscall
jr $ra

main:

li $v0,5
syscall
move $s1,$v0
li $t9,1
bne $s1,$t9,$LABEL3
li $v0,5
syscall
move $t0,$v0
li $v0,12
syscall
move $t1,$v0
li $v0,12
syscall
move $t2,$v0
li $v0,5
syscall
move $t3,$v0
mul $t4,$t0,$t1
add $t5,$t1,$t4
div $t6,$t0,$t2
sub $t7,$t5,$t6
li $v0,1
move $a0,$t7
syscall
li $v0,4
la $a0,$string1
syscall
li $v0,4
la $a0,$string2
syscall
li $v0,4
la $a0,$string3
syscall
li $v0,11
move $a0,$t1
syscall
add $v1,$sp,1884
li $t9,43
sw $t9,0($v1)
add $v1,$sp,1884
li $t9,45
sw $t9,4($v1)
add $v1,$sp,1884
li $t9,42
sw $t9,8($v1)
add $v1,$sp,1884
li $t9,47
sw $t9,12($v1)
add $v1,$sp,1884
li $t9,48
sw $t9,16($v1)
add $v1,$sp,1884
li $t9,57
sw $t9,20($v1)
add $v1,$sp,1884
li $t9,97
sw $t9,24($v1)
add $v1,$sp,1884
li $t9,122
sw $t9,28($v1)
add $v1,$sp,1884
li $t9,65
sw $t9,32($v1)
add $v1,$sp,1884
li $t9,90
sw $t9,36($v1)
li $t9,43
sw $t9,12($gp)
li $t9,97
sw $t9,20($gp)
lw $t9,12($gp)
addi $t8,$t9,2
move $s4,$t8
sw $t3,1896($sp)
lw $t9,20($gp)
sub $t3,$0,$t9
sw $t4,-4($sp)
addi $t4,$t3,77
move $s3,$t4
sw $t0,1900($sp)
li $t0,-1
sw $t2,1892($sp)
addi $t2,$t0,45
sw $t5,-8($sp)
addi $t5,$t2,1
move $s2,$t5
beq $s4,$s2,$LABEL4
li $v0,4
la $a0,$string4
syscall
$LABEL4:
$LABEL5:
bne $s4,$s3,$LABEL6
li $v0,4
la $a0,$string5
syscall
$LABEL6:
$LABEL7:
bgt $s4,$s3,$LABEL8
li $v0,4
la $a0,$string6
syscall
$LABEL8:
$LABEL9:
bge $s4,$s2,$LABEL10
li $v0,4
la $a0,$string7
syscall
$LABEL10:
$LABEL11:
blt $s3,$s2,$LABEL12
li $v0,4
la $a0,$string8
syscall
$LABEL12:
$LABEL13:
ble $s2,$s4,$LABEL14
li $v0,4
la $a0,$string9
syscall
$LABEL14:
$LABEL15:
li $t0,12
li $t1,23
li $t2,-23
move $t3,$t2
add $t4,$t3,$t0
add $t5,$t4,$t1
li $t9,12
beq $t5,$t9,$LABEL16
li $v0,4
la $a0,$string10
syscall
$LABEL16:
$LABEL17:
j $LABEL18
li $v0,4
la $a0,$string11
syscall
$LABEL18:
$LABEL19:
li $t0,9
li $t1,51
li $t2,52
sub $t3,$t2,$t1
add $t4,$t3,$t0
li $t9,10
beq $t4,$t9,$LABEL20
li $v0,4
la $a0,$string12
syscall
$LABEL20:
$LABEL21:
$LABEL3:
$LABEL22:
li $t9,2
bne $s1,$t9,$LABEL23
add $v1,$sp,1736
li $t9,2333
sw $t9,0($v1)
add $v1,$sp,1336
li $t9,47
sw $t9,0($v1)
li $t0,-7
addi $t1,$t0,9
move $t2,$t1
li $t3,43
move $t4,$t3
add $v1,$sp,1336
lw $t5,0($v1)
move $t6,$t5
li $t7,-7
move $t8,$t7
sw $t0,-64($sp)
move $t0,$t8
sw $t2,1808($sp)
add $v1,$sp,1736
lw $t2,0($v1)
sw $t1,-68($sp)
move $t1,$t2

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
sw $19,-80($fp)
sw $20,-84($fp)
sw $21,-88($fp)
sw $22,-92($fp)
sw $24,-100($fp)
sw $ra,-128($fp)
sub $sp,$fp,128
sub $fp,$sp,8
jal ff2
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
lw $24,28($sp)
lw $ra,0($sp)
add $fp,$fp,136
add $sp,$sp,728
sw $t4,1748($sp)
move $t4,$v0

sw $t3,1752($sp)
move $t3,$t4
sw $t6,1744($sp)
li $t9,121
addi $t6,$t9,0

sw $t6,-4($fp)
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
sw $24,-108($fp)
sw $ra,-136($fp)
sub $sp,$fp,136
sub $fp,$sp,0
jal ff1
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
lw $24,28($sp)
lw $ra,0($sp)
add $fp,$fp,136
add $sp,$sp,736
sw $t5,-72($sp)
move $t5,$v0

sw $t7,-76($sp)
move $t7,$t5
sw $t0,1800($sp)
sw $t8,1804($sp)
lw $t8,1808($sp)
sw $t1,1796($sp)
lw $t1,1752($sp)
add $t0,$t8,$t1
sw $t2,-80($sp)
sw $t3,1792($sp)
lw $t3,1748($sp)
add $t2,$t0,$t3
sw $t4,-84($sp)
sw $t6,-88($sp)
lw $t6,1744($sp)
add $t4,$t2,$t6
sw $t7,1740($sp)
sw $t5,-92($sp)
lw $t5,1804($sp)
add $t7,$t4,$t5
sw $t8,1808($sp)
sw $t1,1752($sp)
lw $t1,1800($sp)
add $t8,$t7,$t1
sw $t0,-96($sp)
sw $t3,1748($sp)
lw $t3,1796($sp)
add $t0,$t8,$t3
sw $t2,-100($sp)
sw $t6,1744($sp)
lw $t6,1792($sp)
add $t2,$t0,$t6
sw $t4,-104($sp)
sw $t5,1804($sp)
lw $t5,1740($sp)
add $t4,$t2,$t5
move $t6,$t4
sw $t7,-108($sp)
sw $t1,1800($sp)
lw $t1,1804($sp)
li $t9,-7
mul $t7,$t1,$t9
sw $t8,-112($sp)
mul $t8,$t7,$t3
sw $t0,-116($sp)
div $t0,$t8,$t5
sw $t2,-120($sp)
sw $t6,1792($sp)
lw $t6,1808($sp)
div $t2,$t0,$t6
sw $t4,-124($sp)
sw $t1,1804($sp)
lw $t1,1800($sp)
mul $t4,$t2,$t1
li $v0,1
move $a0,$t4
syscall
li $v0,4
la $a0,$string13
syscall
sw $t7,-128($sp)
sw $t3,1796($sp)
lw $t3,1792($sp)
addi $t7,$t3,4
li $v0,1
move $a0,$t7
syscall
li $v0,4
la $a0,$string13
syscall
sw $t8,-132($sp)
li $t8,-1
sw $t5,1740($sp)
sub $t5,$0,$t8
li $v0,1
move $a0,$t5
syscall
sw $t0,-136($sp)
li $t0,0
li $t9,0
beq $t0,$t9,$LABEL24
li $v0,4
la $a0,$string14
syscall
j $LABEL25
$LABEL24:
li $s0,1
$LABEL25:
j $LABEL27
li $v0,4
la $a0,$string15
syscall
j $LABEL28
$LABEL27:
li $t9,0
ble $s0,$t9,$LABEL30
li $t9,0
bge $s0,$t9,$LABEL31
li $v0,4
la $a0,$string16
syscall
j $LABEL32
$LABEL31:
li $v0,4
la $a0,$string17
syscall
$LABEL32:
$LABEL30:
$LABEL33:
$LABEL29:
$LABEL34:
$LABEL28:
j $LABEL35
$LABEL26:
li $v0,4
la $a0,$string18
syscall
$LABEL35:
li $s3,1
li $s6,0
li $t9,4
bgt $s3,$t9,$LABEL36
$LABEL37:
li $s2,1
bge $s2,$s3,$LABEL38
$LABEL39:
add $t0,$s6,$s2
move $s6,$t0
addi $t1,$s2,1
move $s2,$t1
blt $s2,$s3,$LABEL39
$LABEL38:
$LABEL40:
addi $t0,$s3,1
move $s3,$t0
li $t9,4
ble $s3,$t9,$LABEL37
$LABEL36:
$LABEL41:
li $s5,0
li $s4,2
$LABEL42:
li $t9,5
bgt $s4,$t9,$LABEL43
li $s2,1
li $s3,2
$LABEL44:
bge $s3,$s4,$LABEL45
mul $t0,$s2,$s3
move $s2,$t0
addi $t1,$s3,2
move $s3,$t1
j $LABEL44
$LABEL45:
add $t0,$s5,$s2
move $s5,$t0
addi $t1,$s4,1
move $s4,$t1
j $LABEL42
$LABEL43:
li $s4,100
$LABEL46:
li $t9,97
blt $s4,$t9,$LABEL47
li $s2,1
li $s3,100
$LABEL48:
ble $s3,$s4,$LABEL49
mul $t0,$s2,$s3
move $s2,$t0
li $t9,2
sub $t1,$s3,$t9
move $s3,$t1
j $LABEL48
$LABEL49:
add $t0,$s5,$s2
move $s5,$t0
li $t9,1
sub $t1,$s4,$t9
move $s4,$t1
j $LABEL46
$LABEL47:
li $t0,0
li $t9,1
move $v1,$t9
ble $v1,$t0,$LABEL50
li $v0,4
la $a0,$string17
syscall
$LABEL50:
$LABEL51:
$LABEL52:
li $s2,0
$LABEL53:
li $t9,100
bge $s2,$t9,$LABEL54
addi $t0,$s2,2
move $s2,$t0
li $t9,60
ble $s2,$t9,$LABEL55
li $v0,4
la $a0,$string13
syscall
add $t0,$s6,$s5
add $t1,$t0,$s2
li $v0,1
move $a0,$t1
syscall
li $v0,10
syscall
$LABEL55:
$LABEL56:
addi $t0,$s2,1
move $s2,$t0
j $LABEL53
$LABEL54:
j $LABEL52
li $v0,4
la $a0,$string19
syscall
$LABEL23:
$LABEL57:
li $t9,3
bne $s1,$t9,$LABEL58
li $t0,1

sw $t0,-4($fp)
sw $8,-44($fp)
sw $16,-76($fp)
sw $17,-80($fp)
sw $18,-84($fp)
sw $19,-88($fp)
sw $20,-92($fp)
sw $21,-96($fp)
sw $22,-100($fp)
sw $ra,-136($fp)
sub $sp,$fp,136
sub $fp,$sp,20
jal factorial
lw $8,92($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $19,48($sp)
lw $20,44($sp)
lw $21,40($sp)
lw $22,36($sp)
lw $ra,0($sp)
add $fp,$fp,156
add $sp,$sp,736
move $t1,$v0

li $t2,2

sw $t2,-4($fp)
sw $8,-44($fp)
sw $9,-48($fp)
sw $10,-52($fp)
sw $16,-76($fp)
sw $17,-80($fp)
sw $18,-84($fp)
sw $19,-88($fp)
sw $20,-92($fp)
sw $21,-96($fp)
sw $22,-100($fp)
sw $ra,-136($fp)
sub $sp,$fp,136
sub $fp,$sp,20
jal factorial
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
lw $ra,0($sp)
add $fp,$fp,156
add $sp,$sp,736
move $t3,$v0

add $t4,$t1,$t3
li $t5,5

sw $t5,-4($fp)
sw $8,-44($fp)
sw $9,-48($fp)
sw $10,-52($fp)
sw $11,-56($fp)
sw $12,-60($fp)
sw $13,-64($fp)
sw $16,-76($fp)
sw $17,-80($fp)
sw $18,-84($fp)
sw $19,-88($fp)
sw $20,-92($fp)
sw $21,-96($fp)
sw $22,-100($fp)
sw $ra,-136($fp)
sub $sp,$fp,136
sub $fp,$sp,20
jal factorial
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $11,80($sp)
lw $12,76($sp)
lw $13,72($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $19,48($sp)
lw $20,44($sp)
lw $21,40($sp)
lw $22,36($sp)
lw $ra,0($sp)
add $fp,$fp,156
add $sp,$sp,736
move $t6,$v0

add $t7,$t4,$t6
li $v0,1
move $a0,$t7
syscall
li $t9,97
sw $t9,12($gp)
li $t9,43
addi $t8,$t9,0

sw $t8,-4($fp)
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
sw $24,-108($fp)
sw $ra,-136($fp)
sub $sp,$fp,136
sub $fp,$sp,0
jal ff1
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
lw $24,28($sp)
lw $ra,0($sp)
add $fp,$fp,136
add $sp,$sp,736
sw $t0,-228($sp)
move $t0,$v0

li $v0,11
lw $t9,12($gp)
move $a0,$t9
syscall
li $t9,98
sw $t9,16($gp)

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
sw $19,-80($fp)
sw $20,-84($fp)
sw $21,-88($fp)
sw $22,-92($fp)
sw $24,-100($fp)
sw $ra,-128($fp)
sub $sp,$fp,128
sub $fp,$sp,8
jal ff2
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
lw $24,28($sp)
lw $ra,0($sp)
add $fp,$fp,136
add $sp,$sp,728
sw $t2,-236($sp)
move $t2,$v0

li $v0,11
lw $t9,16($gp)
move $a0,$t9
syscall
sw $t1,-232($sp)
li $t1,1
sw $t3,-240($sp)
li $t3,2
sw $t5,-248($sp)
li $t9,97
addi $t5,$t9,0
sw $t4,-244($sp)
li $t4,3
sw $t6,-252($sp)
li $t9,98
addi $t6,$t9,0
sw $t7,-256($sp)
li $t9,99
addi $t7,$t9,0

sw $t1,-4($fp)
sw $t3,-8($fp)
sw $t5,-12($fp)
sw $t4,-16($fp)
sw $t6,-20($fp)
sw $t7,-24($fp)
sw $8,-60($fp)
sw $9,-64($fp)
sw $10,-68($fp)
sw $11,-72($fp)
sw $12,-76($fp)
sw $13,-80($fp)
sw $14,-84($fp)
sw $15,-88($fp)
sw $16,-92($fp)
sw $17,-96($fp)
sw $18,-100($fp)
sw $19,-104($fp)
sw $20,-108($fp)
sw $21,-112($fp)
sw $22,-116($fp)
sw $24,-124($fp)
sw $ra,-152($fp)
sub $sp,$fp,152
sub $fp,$sp,20
jal ff3
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
lw $24,28($sp)
lw $ra,0($sp)
add $fp,$fp,172
add $sp,$sp,752
sw $t8,-260($sp)
move $t8,$v0


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
sw $19,-80($fp)
sw $20,-84($fp)
sw $21,-88($fp)
sw $22,-92($fp)
sw $24,-100($fp)
sw $ra,-128($fp)
sub $sp,$fp,128
sub $fp,$sp,0
jal ff4
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
lw $24,28($sp)
lw $ra,0($sp)
add $fp,$fp,128
add $sp,$sp,728
sw $t0,-264($sp)
move $t0,$v0

li $t9,42
sw $t9,12($gp)

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
sw $24,-108($fp)
sw $ra,-136($fp)
sub $sp,$fp,136
sub $fp,$sp,8
jal ff5
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
lw $24,28($sp)
lw $ra,0($sp)
add $fp,$fp,144
add $sp,$sp,736
sw $t2,-268($sp)
move $t2,$v0

sw $t1,-272($sp)
li $t1,6666
sw $t1,936($sp)
sw $t3,-276($sp)
li $t3,56
sw $t3,928($sp)
sw $t5,-280($sp)
add $t5,$t1,$t3
li $v0,1
move $a0,$t5
syscall
add $v1,$sp,524
li $t9,104
sw $t9,200($v1)
sw $t4,-284($sp)
add $v1,$sp,524
lw $t4,200($v1)
li $v0,11
move $a0,$t4
syscall
sw $t6,-288($sp)
li $t9,103
addi $t6,$t9,0

sw $t6,-4($fp)
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
sw $24,-108($fp)
sw $ra,-136($fp)
sub $sp,$fp,136
sub $fp,$sp,0
jal ff1
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
lw $24,28($sp)
lw $ra,0($sp)
add $fp,$fp,136
add $sp,$sp,736
sw $t7,-292($sp)
move $t7,$v0

li $v0,11
move $a0,$t7
syscall
li $v0,1
li $t9,114
move $a0,$t9
syscall
li $s2,0
$LABEL59:
li $t9,100
bge $s2,$t9,$LABEL60
add $v1,$sp,924
sll $t9,$s2,2
add $v1,$v1,$t9
sw $s2,0($v1)
addi $t0,$s2,1
move $s2,$t0
j $LABEL59
$LABEL60:
li $t0,8
li $t9,6
mul $t1,$t0,$t9
li $t2,12
add $t3,$t1,$t2
add $v1,$sp,924
sll $t9,$t3,2
add $t9,$v1,$t9
lw $t4,0($t9)
li $t9,23
div $t5,$t4,$t9
li $t9,22
move $v1,$t9
mul $t6,$v1,$s2
li $t9,23
div $t7,$t6,$t9
add $v1,$sp,924
lw $t8,4($v1)
sw $t0,-328($sp)
li $t9,1000
mul $t0,$t8,$t9
sw $t1,-332($sp)
mul $t1,$t7,$t0
sw $t2,-336($sp)
li $t9,1000
div $t2,$t1,$t9
sw $t3,-340($sp)
li $t3,3
sw $t5,-348($sp)
add $t5,$t2,$t3
sw $t4,-344($sp)
add $v1,$sp,924
sll $t9,$t5,2
add $t9,$v1,$t9
lw $t4,0($t9)
sw $t6,-352($sp)
li $t9,30
div $t6,$t4,$t9
sw $t8,-360($sp)
sw $t7,-356($sp)
lw $t7,-348($sp)
add $t8,$t7,$t6
sw $t0,-364($sp)
add $v1,$sp,924
sll $t9,$t8,2
add $t9,$v1,$t9
lw $t0,0($t9)
move $s2,$t0
sw $t1,-368($sp)
li $t1,8
sw $t2,-372($sp)
li $t9,6
mul $t2,$t1,$t9
sw $t3,-376($sp)
li $t3,12
sw $t5,-380($sp)
add $t5,$t2,$t3
sw $t4,-384($sp)
add $v1,$sp,924
sll $t9,$t5,2
add $t9,$v1,$t9
lw $t4,0($t9)
sw $t7,-348($sp)
li $t9,23
div $t7,$t4,$t9
sw $t6,-388($sp)
li $t9,22
move $v1,$t9
mul $t6,$v1,$s2
sw $t8,-392($sp)
li $t9,23
div $t8,$t6,$t9
sw $t0,-396($sp)
add $v1,$sp,924
lw $t0,4($v1)
sw $t1,-400($sp)
li $t9,1000
mul $t1,$t0,$t9
sw $t2,-404($sp)
mul $t2,$t8,$t1
sw $t3,-408($sp)
li $t9,1000
div $t3,$t2,$t9
sw $t5,-412($sp)
li $t5,3
sw $t7,-420($sp)
add $t7,$t3,$t5
sw $t4,-416($sp)
add $v1,$sp,924
sll $t9,$t7,2
add $t9,$v1,$t9
lw $t4,0($t9)
sw $t6,-424($sp)
li $t9,30
div $t6,$t4,$t9
sw $t0,-432($sp)
sw $t8,-428($sp)
lw $t8,-420($sp)
add $t0,$t8,$t6
sw $t1,-436($sp)
add $v1,$sp,924
sll $t9,$t0,2
add $t9,$v1,$t9
lw $t1,0($t9)
sw $t2,-440($sp)
addi $t2,$t1,0

sw $t2,-4($fp)
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
sw $24,-108($fp)
sw $ra,-136($fp)
sub $sp,$fp,136
sub $fp,$sp,20
jal factorial
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
lw $24,28($sp)
lw $ra,0($sp)
add $fp,$fp,156
add $sp,$sp,736
sw $t3,-444($sp)
move $t3,$v0

li $v0,1
move $a0,$t3
syscall
$LABEL58:
$LABEL61:
li $v0,10
syscall
li $v0,10
syscall
