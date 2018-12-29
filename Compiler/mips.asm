.data
    $string0: .asciiz " | "
    $string1: .asciiz " | v: "
    $string2: .asciiz " | b: "
.text
    addiu $sp,$sp,-140
    addiu $fp,$sp,-104
    j main
limit2char:
div $t0,$a1,256
mul $t1,$t0,256
subu $v0,$a1,$t1
jr $ra
M:
ble $0,$a1,$LABEL1
$LABEL2:
addu $a1,$a1,$a2
blt $a1,$0,$LABEL2
$LABEL1:
$LABEL3:
bge $a1,$a2,$LABEL4
move $v0,$a1
jr $ra
j $LABEL5
$LABEL4:
div $a1,$a2
mflo $t0
mul $t1,$t0,$a2
subu $a1,$a1,$t1
$LABEL5:
move $v0,$a1
jr $ra
randomSet:
lw $t0,72($gp)
lw $t9,40($gp)
sw $ra,-136($fp)
move $a1,$t0
move $a2,$t9
addiu $sp,$fp,-136
addiu $fp,$sp,-28
jal M
lw $ra,0($sp)
addiu $fp,$fp,164
addiu $sp,$sp,152
addiu $v1,$gp,96
sll $t9,$v0,2
addu $t9,$v1,$t9
lw $t3,0($t9)
sw $t3,92($gp)
jr $ra
normal:
sw $ra,-132($fp)
addiu $sp,$fp,-132
addiu $fp,$sp,-12
jal limit2char
lw $ra,0($sp)
addiu $fp,$fp,144
addiu $sp,$sp,188
move $a1,$v0
beq $a1,$0,$LABEL6
j $LABEL7
$LABEL6:
bne $a1,$0,$LABEL8
sw $ra,-132($fp)
li $a1,36
addiu $sp,$fp,-132
addiu $fp,$sp,-56
jal normal
lw $ra,0($sp)
addiu $fp,$fp,188
addiu $sp,$sp,188
sw $ra,-132($fp)
move $a1,$v0
addiu $sp,$fp,-132
addiu $fp,$sp,-12
jal limit2char
lw $ra,0($sp)
addiu $fp,$fp,144
addiu $sp,$sp,188
jr $ra
$LABEL8:
$LABEL9:
$LABEL7:
li $t9,43
beq $a1,$t9,$LABEL10
sw $a1,-24($fp)
sw $ra,-128($fp)
addiu $sp,$fp,-128
addiu $fp,$sp,-16
jal randomSet
lw $a1,104($sp)
lw $ra,0($sp)
addiu $fp,$fp,144
addiu $sp,$sp,184
$LABEL10:
$LABEL11:
li $v1,47
bge $v1,$a1,$LABEL12
li $t9,57
bgt $a1,$t9,$LABEL13
sw $ra,-132($fp)
addiu $sp,$fp,-132
addiu $fp,$sp,-12
jal limit2char
lw $ra,0($sp)
addiu $fp,$fp,144
addiu $sp,$sp,188
jr $ra
$LABEL13:
$LABEL14:
$LABEL12:
$LABEL15:
addiu $t0,$a1,-32
sw $ra,-136($fp)
move $a1,$t0
li $a2,95
addiu $sp,$fp,-136
addiu $fp,$sp,-28
jal M
lw $ra,0($sp)
addiu $fp,$fp,164
addiu $sp,$sp,192
addiu $t2,$v0,32
sw $ra,-132($fp)
move $a1,$t2
addiu $sp,$fp,-132
addiu $fp,$sp,-12
jal limit2char
lw $ra,0($sp)
addiu $fp,$fp,144
addiu $sp,$sp,188
jr $ra
acc:
sw $a1,-32($fp)
sw $ra,-136($fp)
li $a2,4
addiu $sp,$fp,-136
addiu $fp,$sp,-28
jal M
lw $a1,104($sp)
lw $ra,0($sp)
addiu $fp,$fp,164
addiu $sp,$sp,152
sw $a1,-32($fp)
sw $ra,-136($fp)
li $a2,4
addiu $sp,$fp,-136
addiu $fp,$sp,-28
jal M
lw $a1,104($sp)
lw $ra,0($sp)
addiu $fp,$fp,164
addiu $sp,$sp,152
addiu $v1,$gp,76
sll $t9,$v0,2
addu $t9,$v1,$t9
lw $t2,0($t9)
addu $t3,$t2,$a1
addiu $v1,$gp,76
sll $t9,$v0,2
addu $v1,$v1,$t9
sw $t3,0($v1)
jr $ra
f:
sw $a1,-28($fp)
sw $ra,-132($fp)
move $a1,$a2
addiu $sp,$fp,-132
addiu $fp,$sp,-56
jal normal
lw $a1,104($sp)
lw $ra,0($sp)
addiu $fp,$fp,188
addiu $sp,$sp,156
sw $v0,128($sp)
sw $a1,-28($fp)
sw $ra,-132($fp)
move $a1,$v0
addiu $sp,$fp,-132
addiu $fp,$sp,-16
jal acc
lw $a1,104($sp)
lw $ra,0($sp)
addiu $fp,$fp,148
addiu $sp,$sp,156
mul $t4,$a1,13
addu $t5,$t4,$v0
sw $ra,-136($fp)
move $a1,$t5
li $a2,100007
addiu $sp,$fp,-136
addiu $fp,$sp,-28
jal M
lw $t0,92($sp)
lw $ra,0($sp)
addiu $fp,$fp,164
addiu $sp,$sp,160
jr $ra
hash:
lw $t9,40($gp)
bgt $t9,$0,$LABEL16
jr $ra
$LABEL16:
$LABEL17:
sw $a1,72($gp)
li $s0,0
$LABEL18:
lw $t9,40($gp)
bge $s0,$t9,$LABEL19
lw $t0,72($gp)
addiu $v1,$gp,96
sll $t9,$s0,2
addu $t9,$v1,$t9
lw $t1,0($t9)
sw $ra,-148($fp)
move $a1,$t0
move $a2,$t1
addiu $sp,$fp,-148
addiu $fp,$sp,-24
jal f
lw $ra,0($sp)
addiu $fp,$fp,172
addiu $sp,$sp,180
sw $v0,72($gp)
addiu $s0,$s0,1
j $LABEL18
$LABEL19:
jr $ra
main:
li $t9,0
sw $t9,40($gp)
sw $s0,-76($fp)
sw $ra,-136($fp)
li $a1,391
addiu $sp,$fp,-136
addiu $fp,$sp,-32
jal hash
lw $s0,60($sp)
lw $ra,0($sp)
addiu $fp,$fp,168
addiu $sp,$sp,240
li $v0,5
syscall
sw $v0,40($gp)
li $s0,0
$LABEL20:
lw $t9,40($gp)
bge $s0,$t9,$LABEL21
li $v0,12
syscall
addiu $v1,$gp,96
sll $t9,$s0,2
addu $v1,$v1,$t9
sw $v0,0($v1)
addiu $s0,$s0,1
j $LABEL20
$LABEL21:
sw $ra,-136($fp)
li $a1,-20
li $a2,2
addiu $sp,$fp,-136
addiu $fp,$sp,-28
jal M
lw $ra,0($sp)
addiu $fp,$fp,164
addiu $sp,$sp,240
move $t0,$v0
move $s0,$v0
sw $t0,-44($fp)
sw $ra,-136($fp)
li $a1,1
li $a2,2
addiu $sp,$fp,-136
addiu $fp,$sp,-28
jal M
lw $t0,92($sp)
lw $ra,0($sp)
addiu $fp,$fp,164
addiu $sp,$sp,240
move $t1,$v0
move $s0,$v0
sw $t0,-44($fp)
sw $t1,-48($fp)
sw $ra,-136($fp)
li $a1,3
li $a2,2
addiu $sp,$fp,-136
addiu $fp,$sp,-28
jal M
lw $t0,92($sp)
lw $t1,88($sp)
lw $ra,0($sp)
addiu $fp,$fp,164
addiu $sp,$sp,240
move $s0,$v0
sw $t0,-40($fp)
sw $ra,-132($fp)
move $a1,$0
addiu $sp,$fp,-132
addiu $fp,$sp,-56
jal normal
lw $t0,92($sp)
lw $ra,0($sp)
addiu $fp,$fp,188
addiu $sp,$sp,236
sw $t0,-40($fp)
sw $ra,-132($fp)
li $a1,43
addiu $sp,$fp,-132
addiu $fp,$sp,-56
jal normal
lw $t0,92($sp)
lw $ra,0($sp)
addiu $fp,$fp,188
addiu $sp,$sp,236
sw $t0,-40($fp)
sw $ra,-132($fp)
li $a1,47
addiu $sp,$fp,-132
addiu $fp,$sp,-56
jal normal
lw $t0,92($sp)
lw $ra,0($sp)
addiu $fp,$fp,188
addiu $sp,$sp,236
sw $t0,-40($fp)
sw $ra,-132($fp)
li $a1,49
addiu $sp,$fp,-132
addiu $fp,$sp,-56
jal normal
lw $t0,92($sp)
lw $ra,0($sp)
addiu $fp,$fp,188
addiu $sp,$sp,236
lw $t9,40($gp)
li $v0,1
move $a0,$t9
syscall
li $v0,4
la $a0,$string0
syscall
sw $t0,-16($sp)
lw $t9,40($gp)
sw $t1,-20($sp)
addiu $s0,$t9,-1
$LABEL22:
blt $s0,$0,$LABEL23
addiu $v1,$gp,96
addiu $v1,$gp,96
sll $t9,$s0,2
addu $t9,$v1,$t9
lw $t2,0($t9)
li $v0,11
move $a0,$t2
syscall
addiu $s0,$s0,-1
j $LABEL22
$LABEL23:
sw $s0,-76($fp)
sw $ra,-136($fp)
li $a1,391
addiu $sp,$fp,-136
addiu $fp,$sp,-32
jal hash
lw $s0,60($sp)
lw $ra,0($sp)
addiu $fp,$fp,168
addiu $sp,$sp,240
li $v0,4
la $a0,$string1
syscall
lw $t9,72($gp)
li $v0,1
move $a0,$t9
syscall
lw $t9,92($gp)
sw $ra,-132($fp)
move $a1,$t9
addiu $sp,$fp,-132
addiu $fp,$sp,-56
jal normal
lw $ra,0($sp)
addiu $fp,$fp,188
addiu $sp,$sp,236
move $t5,$v0
li $v0,4
la $a0,$string2
syscall
li $v0,1
move $a0,$t5
syscall
li $s0,0
$LABEL24:
li $t9,4
bge $s0,$t9,$LABEL25
li $v0,4
la $a0,$string0
syscall
addiu $v1,$gp,76
sll $t9,$s0,2
addu $t9,$v1,$t9
lw $t0,0($t9)
li $v0,1
move $a0,$t0
syscall
addiu $s0,$s0,1
j $LABEL24
$LABEL25:
li $v0,10
syscall
