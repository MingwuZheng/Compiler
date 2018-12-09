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
    sub $fp,$fp,548
    j main

ff1:

li $t9,98
sw $t9,12($gp)
lw $t0,132($sp)
move $v0,$t0
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

lw $s0,148($sp)
lw $s1,144($sp)
lw $s2,140($sp)
lw $s3,136($sp)
lw $s4,132($sp)
lw $s5,128($sp)
add $t0,$s0,$s1
add $t1,$t0,$s2
add $t2,$t1,$s3
add $t3,$t2,$s4
add $t4,$t3,$s5
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

sw $t0,-4($fp)
sw $8,-44($fp)
sw $16,-76($fp)
sw $ra,-136($fp)
sub $sp,$fp,136
sub $fp,$sp,16
jal factorial
lw $8,92($sp)
lw $16,60($sp)
lw $ra,0($sp)
add $fp,$fp,152
add $sp,$sp,152
move $t1,$v0

mul $t2,$t1,$s0
move $t3,$t2
move $v0,$t3
jr $ra
$LABEL2:
jr $ra

ff5:

li $t9,4
sw $t9,128($sp)
lw $t9,128($gp)
addi $t0,$t9,122
lw $t9,12($gp)
add $t1,$t0,$t9
li $v0,1
move $a0,$t1
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
move $s2,$t8
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
move $s4,$t5
beq $s2,$s4,$LABEL4
li $v0,4
la $a0,$string4
syscall
$LABEL4:
$LABEL5:
bne $s2,$s3,$LABEL6
li $v0,4
la $a0,$string5
syscall
$LABEL6:
$LABEL7:
bgt $s2,$s3,$LABEL8
li $v0,4
la $a0,$string6
syscall
$LABEL8:
$LABEL9:
bge $s2,$s4,$LABEL10
li $v0,4
la $a0,$string7
syscall
$LABEL10:
$LABEL11:
blt $s3,$s4,$LABEL12
li $v0,4
la $a0,$string8
syscall
$LABEL12:
$LABEL13:
ble $s4,$s2,$LABEL14
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
sw $23,-96($fp)
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
lw $23,32($sp)
lw $24,28($sp)
lw $ra,0($sp)
add $fp,$fp,136
add $sp,$sp,676
sw $t4,1748($sp)
move $t4,$v0

sw $t3,1752($sp)
move $t3,$t4

li $t9,121
sw $t9,-4($fp)
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
lw $23,32($sp)
lw $24,28($sp)
lw $ra,0($sp)
add $fp,$fp,136
add $sp,$sp,684
sw $t6,1744($sp)
move $t6,$v0

sw $t5,-72($sp)
move $t5,$t6
sw $t7,-76($sp)
sw $t0,1800($sp)
lw $t0,1808($sp)
sw $t8,1804($sp)
lw $t8,1752($sp)
add $t7,$t0,$t8
sw $t1,1796($sp)
sw $t2,-80($sp)
lw $t2,1748($sp)
add $t1,$t7,$t2
sw $t3,1792($sp)
sw $t4,-84($sp)
lw $t4,1744($sp)
add $t3,$t1,$t4
sw $t5,1740($sp)
sw $t6,-88($sp)
lw $t6,1804($sp)
add $t5,$t3,$t6
sw $t0,1808($sp)
sw $t8,1752($sp)
lw $t8,1800($sp)
add $t0,$t5,$t8
sw $t7,-92($sp)
sw $t2,1748($sp)
lw $t2,1796($sp)
add $t7,$t0,$t2
sw $t1,-96($sp)
sw $t4,1744($sp)
lw $t4,1792($sp)
add $t1,$t7,$t4
sw $t3,-100($sp)
sw $t6,1804($sp)
lw $t6,1740($sp)
add $t3,$t1,$t6
move $t4,$t3
sw $t5,-104($sp)
sw $t8,1800($sp)
lw $t8,1804($sp)
li $t9,-7
mul $t5,$t8,$t9
sw $t0,-108($sp)
mul $t0,$t5,$t2
sw $t7,-112($sp)
div $t7,$t0,$t6
sw $t1,-116($sp)
sw $t4,1792($sp)
lw $t4,1808($sp)
div $t1,$t7,$t4
sw $t3,-120($sp)
sw $t8,1804($sp)
lw $t8,1800($sp)
mul $t3,$t1,$t8
li $v0,1
move $a0,$t3
syscall
li $v0,4
la $a0,$string13
syscall
sw $t5,-124($sp)
sw $t2,1796($sp)
lw $t2,1792($sp)
addi $t5,$t2,4
li $v0,1
move $a0,$t5
syscall
li $v0,4
la $a0,$string13
syscall
sw $t0,-128($sp)
li $t0,-1
sw $t6,1740($sp)
sub $t6,$0,$t0
li $v0,1
move $a0,$t6
syscall
sw $t7,-132($sp)
li $t7,0
li $t9,0
beq $t7,$t9,$LABEL24
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
li $s5,1
li $s6,0
li $t9,4
bgt $s5,$t9,$LABEL36
$LABEL37:
li $s7,1
bge $s7,$s5,$LABEL38
$LABEL39:
add $t0,$s6,$s7
move $s6,$t0
addi $t1,$s7,1
move $s7,$t1
blt $s7,$s5,$LABEL39
$LABEL38:
$LABEL40:
addi $t0,$s5,1
move $s5,$t0
li $t9,4
ble $s5,$t9,$LABEL37
$LABEL36:
$LABEL41:
li $t9,0
sw $t9,1772($sp)
li $t9,2
sw $t9,1768($sp)
$LABEL42:
lw $t9,1768($sp)
move $v1,$t9
li $t9,5
bgt $v1,$t9,$LABEL43
li $t9,1
sw $t9,1760($sp)
li $t9,2
sw $t9,1764($sp)
$LABEL44:
lw $t9,1764($sp)
move $v1,$t9
lw $t9,1768($sp)
bge $v1,$t9,$LABEL45
lw $t9,1760($sp)
move $v1,$t9
lw $t9,1764($sp)
mul $t0,$v1,$t9
move $t9,$t0
sw $t9,1760($sp)
lw $t9,1764($sp)
addi $t1,$t9,2
move $t9,$t1
sw $t9,1764($sp)
j $LABEL44
$LABEL45:
lw $t9,1772($sp)
move $v1,$t9
lw $t9,1760($sp)
add $t0,$v1,$t9
move $t9,$t0
sw $t9,1772($sp)
lw $t9,1768($sp)
addi $t1,$t9,1
move $t9,$t1
sw $t9,1768($sp)
j $LABEL42
$LABEL43:
li $t9,100
sw $t9,1768($sp)
$LABEL46:
lw $t9,1768($sp)
move $v1,$t9
li $t9,97
blt $v1,$t9,$LABEL47
li $t9,1
sw $t9,1760($sp)
li $t9,100
sw $t9,1764($sp)
$LABEL48:
lw $t9,1764($sp)
move $v1,$t9
lw $t9,1768($sp)
ble $v1,$t9,$LABEL49
lw $t9,1760($sp)
move $v1,$t9
lw $t9,1764($sp)
mul $t0,$v1,$t9
move $t9,$t0
sw $t9,1760($sp)
lw $t9,1764($sp)
move $v1,$t9
li $t9,2
sub $t1,$v1,$t9
move $t9,$t1
sw $t9,1764($sp)
j $LABEL48
$LABEL49:
lw $t9,1772($sp)
move $v1,$t9
lw $t9,1760($sp)
add $t0,$v1,$t9
move $t9,$t0
sw $t9,1772($sp)
lw $t9,1768($sp)
move $v1,$t9
li $t9,1
sub $t1,$v1,$t9
move $t9,$t1
sw $t9,1768($sp)
j $LABEL46
$LABEL47:
li $v0,4
la $a0,$string13
syscall
li $v0,1
lw $t9,1772($sp)
move $a0,$t9
syscall
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
li $t9,0
sw $t9,1756($sp)
$LABEL53:
lw $t9,1756($sp)
move $v1,$t9
li $t9,100
bge $v1,$t9,$LABEL54
lw $t9,1756($sp)
addi $t0,$t9,2
move $t9,$t0
sw $t9,1756($sp)
lw $t9,1756($sp)
move $v1,$t9
li $t9,60
ble $v1,$t9,$LABEL55
li $v0,4
la $a0,$string13
syscall
lw $t9,1772($sp)
add $t0,$s6,$t9
lw $t9,1756($sp)
add $t1,$t0,$t9
li $v0,1
move $a0,$t1
syscall
li $v0,10
syscall
$LABEL55:
$LABEL56:
lw $t9,1756($sp)
addi $t0,$t9,1
move $t9,$t0
sw $t9,1756($sp)
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

li $t9,1
sw $t9,-4($fp)
sw $16,-76($fp)
sw $17,-80($fp)
sw $18,-84($fp)
sw $19,-88($fp)
sw $20,-92($fp)
sw $21,-96($fp)
sw $22,-100($fp)
sw $23,-104($fp)
sw $ra,-136($fp)
sub $sp,$fp,136
sub $fp,$sp,16
jal factorial
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $19,48($sp)
lw $20,44($sp)
lw $21,40($sp)
lw $22,36($sp)
lw $23,32($sp)
lw $ra,0($sp)
add $fp,$fp,152
add $sp,$sp,684
move $t0,$v0


li $t9,2
sw $t9,-4($fp)
sw $8,-44($fp)
sw $16,-76($fp)
sw $17,-80($fp)
sw $18,-84($fp)
sw $19,-88($fp)
sw $20,-92($fp)
sw $21,-96($fp)
sw $22,-100($fp)
sw $23,-104($fp)
sw $ra,-136($fp)
sub $sp,$fp,136
sub $fp,$sp,16
jal factorial
lw $8,92($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $19,48($sp)
lw $20,44($sp)
lw $21,40($sp)
lw $22,36($sp)
lw $23,32($sp)
lw $ra,0($sp)
add $fp,$fp,152
add $sp,$sp,684
move $t1,$v0

add $t2,$t0,$t1

li $t9,5
sw $t9,-4($fp)
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
sw $23,-104($fp)
sw $ra,-136($fp)
sub $sp,$fp,136
sub $fp,$sp,16
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
lw $23,32($sp)
lw $ra,0($sp)
add $fp,$fp,152
add $sp,$sp,684
move $t3,$v0

add $t4,$t2,$t3
li $v0,1
move $a0,$t4
syscall
li $t9,97
sw $t9,12($gp)

li $t9,43
sw $t9,-4($fp)
sw $8,-44($fp)
sw $9,-48($fp)
sw $10,-52($fp)
sw $11,-56($fp)
sw $12,-60($fp)
sw $16,-76($fp)
sw $17,-80($fp)
sw $18,-84($fp)
sw $19,-88($fp)
sw $20,-92($fp)
sw $21,-96($fp)
sw $22,-100($fp)
sw $23,-104($fp)
sw $ra,-136($fp)
sub $sp,$fp,136
sub $fp,$sp,0
jal ff1
lw $8,92($sp)
lw $9,88($sp)
lw $10,84($sp)
lw $11,80($sp)
lw $12,76($sp)
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $19,48($sp)
lw $20,44($sp)
lw $21,40($sp)
lw $22,36($sp)
lw $23,32($sp)
lw $ra,0($sp)
add $fp,$fp,136
add $sp,$sp,684
move $t5,$v0

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
sw $16,-68($fp)
sw $17,-72($fp)
sw $18,-76($fp)
sw $19,-80($fp)
sw $20,-84($fp)
sw $21,-88($fp)
sw $22,-92($fp)
sw $23,-96($fp)
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
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $19,48($sp)
lw $20,44($sp)
lw $21,40($sp)
lw $22,36($sp)
lw $23,32($sp)
lw $ra,0($sp)
add $fp,$fp,136
add $sp,$sp,676
move $t6,$v0

li $v0,11
lw $t9,16($gp)
move $a0,$t9
syscall

li $t9,1
sw $t9,-4($fp)
li $t9,2
sw $t9,-8($fp)
li $t9,97
sw $t9,-12($fp)
li $t9,3
sw $t9,-16($fp)
li $t9,98
sw $t9,-20($fp)
li $t9,99
sw $t9,-24($fp)
sw $8,-60($fp)
sw $9,-64($fp)
sw $10,-68($fp)
sw $11,-72($fp)
sw $12,-76($fp)
sw $13,-80($fp)
sw $14,-84($fp)
sw $16,-92($fp)
sw $17,-96($fp)
sw $18,-100($fp)
sw $19,-104($fp)
sw $20,-108($fp)
sw $21,-112($fp)
sw $22,-116($fp)
sw $23,-120($fp)
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
lw $16,60($sp)
lw $17,56($sp)
lw $18,52($sp)
lw $19,48($sp)
lw $20,44($sp)
lw $21,40($sp)
lw $22,36($sp)
lw $23,32($sp)
lw $ra,0($sp)
add $fp,$fp,172
add $sp,$sp,700
move $t7,$v0


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
sw $23,-96($fp)
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
lw $23,32($sp)
lw $ra,0($sp)
add $fp,$fp,128
add $sp,$sp,676
move $t8,$v0

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
sw $23,-104($fp)
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
lw $23,32($sp)
lw $24,28($sp)
lw $ra,0($sp)
add $fp,$fp,144
add $sp,$sp,684
sw $t0,-224($sp)
move $t0,$v0

li $t9,6666
sw $t9,936($sp)
li $t9,56
sw $t9,928($sp)
sw $t1,-228($sp)
lw $t9,936($gp)
move $v1,$t9
lw $t9,928($gp)
add $t1,$v1,$t9
li $v0,1
move $a0,$t1
syscall
add $v1,$sp,524
li $t9,104
sw $t9,200($v1)
sw $t2,-232($sp)
add $v1,$sp,524
lw $t2,200($v1)
li $v0,11
move $a0,$t2
syscall

li $t9,103
sw $t9,-4($fp)
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
lw $23,32($sp)
lw $24,28($sp)
lw $ra,0($sp)
add $fp,$fp,136
add $sp,$sp,684
sw $t3,-236($sp)
move $t3,$v0

li $v0,11
move $a0,$t3
syscall
li $v0,1
li $t9,114
move $a0,$t9
syscall
li $t9,0
sw $t9,932($sp)
$LABEL59:
lw $t9,932($sp)
move $v1,$t9
li $t9,100
bge $v1,$t9,$LABEL60
add $v1,$sp,924
lw $t9,932($sp)
sll $t9,$t9,2
add $v1,$v1,$t9
lw $t9,932($sp)
sw $t9,0($v1)
lw $t9,932($sp)
addi $t0,$t9,1
move $t9,$t0
sw $t9,932($sp)
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
lw $t9,932($sp)
mul $t6,$v1,$t9
li $t9,23
div $t7,$t6,$t9
add $v1,$sp,924
lw $t8,4($v1)
sw $t0,-280($sp)
li $t9,1000
mul $t0,$t8,$t9
sw $t1,-284($sp)
mul $t1,$t7,$t0
sw $t2,-288($sp)
li $t9,1000
div $t2,$t1,$t9
sw $t3,-292($sp)
li $t3,3
sw $t5,-300($sp)
add $t5,$t2,$t3
sw $t4,-296($sp)
add $v1,$sp,924
sll $t9,$t5,2
add $t9,$v1,$t9
lw $t4,0($t9)
sw $t6,-304($sp)
li $t9,30
div $t6,$t4,$t9
sw $t8,-312($sp)
sw $t7,-308($sp)
lw $t7,-300($sp)
add $t8,$t7,$t6
sw $t0,-316($sp)
add $v1,$sp,924
sll $t9,$t8,2
add $t9,$v1,$t9
lw $t0,0($t9)
move $t9,$t0
sw $t9,932($sp)
sw $t1,-320($sp)
li $t1,8
sw $t2,-324($sp)
li $t9,6
mul $t2,$t1,$t9
sw $t3,-328($sp)
li $t3,12
sw $t5,-332($sp)
add $t5,$t2,$t3
sw $t4,-336($sp)
add $v1,$sp,924
sll $t9,$t5,2
add $t9,$v1,$t9
lw $t4,0($t9)
sw $t7,-300($sp)
li $t9,23
div $t7,$t4,$t9
sw $t6,-340($sp)
li $t9,22
move $v1,$t9
lw $t9,932($sp)
mul $t6,$v1,$t9
sw $t8,-344($sp)
li $t9,23
div $t8,$t6,$t9
sw $t0,-348($sp)
add $v1,$sp,924
lw $t0,4($v1)
sw $t1,-352($sp)
li $t9,1000
mul $t1,$t0,$t9
sw $t2,-356($sp)
mul $t2,$t8,$t1
sw $t3,-360($sp)
li $t9,1000
div $t3,$t2,$t9
sw $t5,-364($sp)
li $t5,3
sw $t7,-372($sp)
add $t7,$t3,$t5
sw $t4,-368($sp)
add $v1,$sp,924
sll $t9,$t7,2
add $t9,$v1,$t9
lw $t4,0($t9)
sw $t6,-376($sp)
li $t9,30
div $t6,$t4,$t9
sw $t0,-384($sp)
sw $t8,-380($sp)
lw $t8,-372($sp)
add $t0,$t8,$t6
sw $t1,-388($sp)
add $v1,$sp,924
sll $t9,$t0,2
add $t9,$v1,$t9
lw $t1,0($t9)

sw $t1,-4($fp)
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
sw $ra,-136($fp)
sub $sp,$fp,136
sub $fp,$sp,16
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
lw $23,32($sp)
lw $24,28($sp)
lw $ra,0($sp)
add $fp,$fp,152
add $sp,$sp,684
sw $t2,-392($sp)
move $t2,$v0

li $v0,1
move $a0,$t2
syscall
$LABEL58:
$LABEL61:
li $v0,10
syscall
li $v0,10
syscall
