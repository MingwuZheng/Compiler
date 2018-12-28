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
    subu $sp,$sp,132
    subu $fp,$sp,28
    j main
func_factorial:
li $t9,1
bgt $a1,$t9,$LABEL1
li $v0,1
jr $ra
j $LABEL2
$LABEL1:
li $t9,1
subu $t0,$a1,$t9
sw $a1,-28($fp)
sw $t0,-40($fp)
sw $t0,-44($fp)
sw $ra,-132($fp)
move $a1,$t0
subu $sp,$fp,132
subu $fp,$sp,20
jal func_factorial
lw $a1,104($sp)
lw $t0,92($sp)
lw $t1,88($sp)
lw $ra,0($sp)
addiu $fp,$fp,152
addiu $sp,$sp,152
mul $v0,$a1,$v0
jr $ra
$LABEL2:
jr $ra
func_mod:
div $t0,$a1,$a2
mul $t1,$t0,$a2
subu $v0,$a1,$t1
jr $ra
func_swap:
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
func_complete_num:
sw $a1,172($sp)
$LABEL3:
li $s2,-1
lw $s1,172($sp)
li $t9,1
sw $t9,176($sp)
$LABEL4:
lw $v1,172($sp)
lw $t9,176($sp)
div $t0,$v1,$t9
lw $t9,176($sp)
mul $t2,$t0,$t9
lw $t9,172($sp)
addiu $t3,$t9,0
lw $t9,176($sp)
sw $a1,-32($fp)
sw $t0,-44($fp)
sw $t1,-48($fp)
sw $t2,-52($fp)
sw $t3,-56($fp)
sw $t9,-60($fp)
sw $s0,-76($fp)
sw $s1,-80($fp)
sw $s2,-84($fp)
sw $s3,-88($fp)
sw $s4,-92($fp)
sw $s5,-96($fp)
sw $ra,-136($fp)
move $a1,$t3
move $a2,$t9
subu $sp,$fp,136
subu $fp,$sp,12
jal func_mod
lw $a1,104($sp)
lw $t0,92($sp)
lw $t1,88($sp)
lw $t2,84($sp)
lw $t3,80($sp)
lw $t4,76($sp)
lw $s0,60($sp)
lw $s1,56($sp)
lw $s2,52($sp)
lw $s3,48($sp)
lw $s4,44($sp)
lw $s5,40($sp)
lw $ra,0($sp)
addiu $fp,$fp,148
addiu $sp,$sp,308
li $t9,0
bne $v0,$t9,$LABEL5
addiu $s2,$s2,1
lw $t9,176($sp)
subu $s1,$s1,$t9
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
lw $t9,176($sp)
sw $t9,0($v1)
$LABEL7:
$LABEL5:
$LABEL8:
lw $t9,176($sp)
addiu $t9,$t9,1
sw $t9,176($sp)
lw $v1,176($sp)
lw $t9,172($sp)
blt $v1,$t9,$LABEL4
li $t9,0
bne $s1,$t9,$LABEL9
li $v0,4
la $a0,$string5
syscall
li $v0,1
lw $a0,172($sp)
syscall
li $t9,0
sw $t9,176($sp)
$LABEL10:
li $v0,4
la $a0,$string6
syscall
addiu $v1,$sp,688
lw $t9,176($sp)
sll $t9,$t9,2
addu $t9,$v1,$t9
lw $t0,0($t9)
li $v0,1
move $a0,$t0
syscall
lw $t9,176($sp)
addiu $t9,$t9,1
sw $t9,176($sp)
lw $v1,176($sp)
ble $v1,$s2,$LABEL10
li $v0,4
la $a0,$string7
syscall
$LABEL9:
$LABEL11:
lw $t9,172($sp)
addiu $t9,$t9,1
sw $t9,172($sp)
lw $v1,172($sp)
li $t9,1024
blt $v1,$t9,$LABEL3
li $v0,4
la $a0,$string8
syscall
li $s0,0
li $t9,0
sw $t9,176($sp)
$LABEL12:
lw $t9,176($sp)
mul $s3,$s0,$t9
lw $v1,172($sp)
mul $t2,$v1,$s2
lw $t9,176($sp)
mul $s0,$s0,$t9
addu $t4,$s0,$s3
addu $s0,$t4,$t2
lw $t9,176($sp)
addiu $t9,$t9,1
sw $t9,176($sp)
lw $v1,176($sp)
li $t9,1024
blt $v1,$t9,$LABEL12
move $s3,$s0
li $t9,0
sw $t9,176($sp)
$LABEL13:
lw $t9,176($sp)
addu $s3,$s3,$t9
lw $t9,176($sp)
addiu $t9,$t9,1
sw $t9,176($sp)
lw $v1,176($sp)
li $t9,1024
blt $v1,$t9,$LABEL13
li $v0,4
la $a0,$string9
syscall
li $v0,1
move $a0,$s3
syscall
li $v0,4
la $a0,$string8
syscall
li $s5,0
li $s4,1
li $s0,2
$LABEL14:
li $t9,2
div $s3,$s0,$t9
li $t9,2
sw $t9,176($sp)
$LABEL15:
lw $t9,176($sp)
div $t0,$s0,$t9
lw $t9,176($sp)
mul $t2,$t0,$t9
lw $t9,176($sp)
sw $a1,-32($fp)
sw $t0,-44($fp)
sw $t1,-48($fp)
sw $t2,-52($fp)
sw $s0,-56($fp)
sw $t9,-60($fp)
sw $s0,-76($fp)
sw $s1,-80($fp)
sw $s2,-84($fp)
sw $s3,-88($fp)
sw $s4,-92($fp)
sw $s5,-96($fp)
sw $ra,-136($fp)
move $a1,$s0
move $a2,$t9
subu $sp,$fp,136
subu $fp,$sp,12
jal func_mod
lw $a1,104($sp)
lw $t0,92($sp)
lw $t1,88($sp)
lw $t2,84($sp)
lw $t3,80($sp)
lw $t4,76($sp)
lw $s0,60($sp)
lw $s1,56($sp)
lw $s2,52($sp)
lw $s3,48($sp)
lw $s4,44($sp)
lw $s5,40($sp)
lw $ra,0($sp)
addiu $fp,$fp,148
addiu $sp,$sp,308
li $t9,0
bne $v0,$t9,$LABEL16
li $s4,0
$LABEL16:
$LABEL17:
lw $t9,176($sp)
addiu $t9,$t9,1
sw $t9,176($sp)
lw $v1,176($sp)
ble $v1,$s3,$LABEL15
li $t9,1
bne $s4,$t9,$LABEL18
li $v0,4
la $a0,$string10
syscall
li $v0,1
move $a0,$s0
syscall
addiu $s5,$s5,1
li $t9,10
div $t1,$s5,$t9
li $t9,10
mul $t3,$t1,$t9
bne $t3,$s5,$LABEL19
li $v0,4
la $a0,$string7
syscall
$LABEL19:
$LABEL20:
$LABEL18:
$LABEL21:
li $s4,1
addiu $s0,$s0,1
li $t9,1024
ble $s0,$t9,$LABEL14
li $v0,4
la $a0,$string11
syscall
li $v0,1
move $a0,$s5
syscall
jr $ra
main:
li $t0,10
sw $t0,-40($fp)
sw $ra,-132($fp)
move $a1,$t0
subu $sp,$fp,132
subu $fp,$sp,20
jal func_factorial
lw $t0,92($sp)
lw $ra,0($sp)
addiu $fp,$fp,152
addiu $sp,$sp,160
move $t2,$v0
li $v0,4
la $a0,$string12
syscall
li $v0,1
move $a0,$t2
syscall
li $t3,5
li $t4,10
sw $t0,-48($fp)
sw $t1,-52($fp)
sw $t2,-56($fp)
sw $t3,-60($fp)
sw $t4,-64($fp)
sw $ra,-140($fp)
move $a1,$t3
move $a2,$t4
subu $sp,$fp,140
subu $fp,$sp,0
jal func_swap
lw $t0,92($sp)
lw $t1,88($sp)
lw $t2,84($sp)
lw $t3,80($sp)
lw $t4,76($sp)
lw $ra,0($sp)
addiu $fp,$fp,140
addiu $sp,$sp,168
li $t6,2
sw $t0,-604($fp)
sw $t1,-608($fp)
sw $t2,-612($fp)
sw $t3,-616($fp)
sw $t4,-620($fp)
sw $v0,-624($fp)
sw $t6,-628($fp)
sw $ra,-696($fp)
move $a1,$t6
subu $sp,$fp,696
subu $fp,$sp,172
jal func_complete_num
lw $t0,92($sp)
lw $t1,88($sp)
lw $t2,84($sp)
lw $t3,80($sp)
lw $t4,76($sp)
lw $t5,72($sp)
lw $t6,68($sp)
lw $ra,0($sp)
addiu $fp,$fp,868
addiu $sp,$sp,724
li $v0,10
syscall
