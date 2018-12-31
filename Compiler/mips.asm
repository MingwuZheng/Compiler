.data
    $string0: .asciiz " x = "
    $string1: .asciiz " y = "
    $string2: .asciiz " SWAP x = "
    $string3: .asciiz " SWAP y = "
    $string4: .asciiz " OVERFLOW!          "
    $string5: .asciiz " complete number: "
    $string6: .asciiz "  "
    $string7: .asciiz "          "
    $string8: .asciiz " ---------------------------------------------------------------          "
    $string9: .asciiz " b = "
    $string10: .asciiz " "
    $string11: .asciiz "          The total is "
    $string12: .asciiz " 10! = "
.text
    addiu $sp,$sp,-132
    addiu $fp,$sp,-12
    j main
factorial:
li $t9,1
bgt $a1,$t9,$LABEL1
li $v0,1
jr $ra
j $LABEL2
$LABEL1:
addiu $t0,$a1,-1
sw $a1,-28($fp)
sw $ra,-132($fp)
move $a1,$t0
addiu $sp,$fp,-132
addiu $fp,$sp,-16
jal factorial
lw $a1,104($sp)
lw $ra,0($sp)
addiu $fp,$fp,148
addiu $sp,$sp,148
mul $v0,$a1,$v0
jr $ra
$LABEL2:
jr $ra
mod:
div $a1,$a2
mflo $t0
mul $t1,$t0,$a2
subu $v0,$a1,$t1
jr $ra
swap:
li $v0,4
la $a0,$string0
syscall
li $v0,1
move $a0,$a1
syscall
li $v0,4
la $a0,$string1
syscall
li $v0,1
move $a0,$a2
syscall
move $t0,$a1
move $a1,$a2
move $a2,$t0
li $v0,4
la $a0,$string2
syscall
li $v0,1
move $a0,$a1
syscall
li $v0,4
la $a0,$string3
syscall
li $v0,1
move $a0,$a2
syscall
jr $ra
complete_num:
move $s3,$a1
$LABEL3:
li $s2,-1
move $s0,$s3
li $s4,1
$LABEL4:
sw $ra,-136($fp)
move $a1,$s3
move $a2,$s4
addiu $sp,$fp,-136
addiu $fp,$sp,-12
jal mod
lw $ra,0($sp)
addiu $fp,$fp,148
addiu $sp,$sp,292
bne $v0,$0,$LABEL5
addiu $s2,$s2,1
subu $s0,$s0,$s4
li $t9,128
blt $s2,$t9,$LABEL6
li $v0,4
la $a0,$string4
syscall
j $LABEL7
$LABEL6:
addiu $v1,$sp,688
sll $t9,$s2,2
addu $v1,$v1,$t9
sw $s4,0($v1)
$LABEL7:
$LABEL5:
$LABEL8:
addiu $s4,$s4,1
blt $s4,$s3,$LABEL4
bne $s0,$0,$LABEL9
li $v0,4
la $a0,$string5
syscall
li $v0,1
move $a0,$s3
syscall
li $s4,0
$LABEL10:
li $v0,4
la $a0,$string6
syscall
addiu $v1,$sp,688
sll $t9,$s4,2
addu $t9,$v1,$t9
lw $t0,0($t9)
li $v0,1
move $a0,$t0
syscall
addiu $s4,$s4,1
ble $s4,$s2,$LABEL10
li $v0,4
la $a0,$string7
syscall
$LABEL9:
$LABEL11:
addiu $s3,$s3,1
li $t9,1024
blt $s3,$t9,$LABEL3
li $v0,4
la $a0,$string8
syscall
li $s1,0
li $s4,0
$LABEL12:
mul $s0,$s1,$s4
mul $t1,$s3,$s2
mul $s1,$s1,$s4
addu $t4,$s1,$s0
addu $s1,$t4,$t1
addiu $s4,$s4,1
li $t9,1024
blt $s4,$t9,$LABEL12
move $s0,$s1
li $s4,0
$LABEL13:
addu $s0,$s0,$s4
addiu $s4,$s4,1
li $t9,1024
blt $s4,$t9,$LABEL13
li $v0,4
la $a0,$string9
syscall
li $v0,1
move $a0,$s0
syscall
li $v0,4
la $a0,$string8
syscall
li $s1,0
li $s0,1
li $s3,2
$LABEL14:
div $s2,$s3,2
li $s4,2
$LABEL15:
sw $ra,-136($fp)
move $a1,$s3
move $a2,$s4
addiu $sp,$fp,-136
addiu $fp,$sp,-12
jal mod
lw $ra,0($sp)
addiu $fp,$fp,148
addiu $sp,$sp,292
bne $v0,$0,$LABEL16
li $s0,0
$LABEL16:
$LABEL17:
addiu $s4,$s4,1
ble $s4,$s2,$LABEL15
li $t9,1
bne $s0,$t9,$LABEL18
li $v0,4
la $a0,$string10
syscall
li $v0,1
move $a0,$s3
syscall
addiu $s1,$s1,1
div $t1,$s1,10
mul $t2,$t1,10
bne $t2,$s1,$LABEL19
li $v0,4
la $a0,$string7
syscall
$LABEL19:
$LABEL20:
$LABEL18:
$LABEL21:
li $s0,1
addiu $s3,$s3,1
li $t9,1024
ble $s3,$t9,$LABEL14
li $v0,4
la $a0,$string11
syscall
li $v0,1
move $a0,$s1
syscall
jr $ra
main:
sw $ra,-132($fp)
li $a1,10
addiu $sp,$fp,-132
addiu $fp,$sp,-16
jal factorial
lw $ra,0($sp)
addiu $fp,$fp,148
addiu $sp,$sp,144
move $t1,$v0
li $v0,4
la $a0,$string12
syscall
li $v0,1
move $a0,$t1
syscall
sw $ra,-140($fp)
li $a1,5
li $a2,10
addiu $sp,$fp,-140
addiu $fp,$sp,0
jal swap
lw $ra,0($sp)
addiu $fp,$fp,140
addiu $sp,$sp,152
sw $ra,-696($fp)
li $a1,2
addiu $sp,$fp,-696
addiu $fp,$sp,-156
jal complete_num
lw $ra,0($sp)
addiu $fp,$fp,852
addiu $sp,$sp,708
li $v0,10
syscall
