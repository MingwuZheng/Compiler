.data
    $string0: .asciiz "#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ !"
    $string1: .asciiz "test of comp symbol"
    $string2: .asciiz "a==b"
    $string3: .asciiz "a<b"
    $string4: .asciiz "c>a"
    $string5: .asciiz "d"
    $string6: .asciiz "error"
    $string7: .asciiz "a<=c"
    $string8: .asciiz "error!"
    $string9: .asciiz "test global variable and constance"
    $string10: .asciiz "before change para="
    $string11: .asciiz "after change para="
    $string12: .asciiz "test for expression"
    $string13: .asciiz "--12--12--12-+12+-12--12--12--12--12="
    $string14: .asciiz "10*-5="
    $string15: .asciiz "10/+4="
    $string16: .asciiz "fib(12)-fib(14)="
    $string17: .asciiz "c + 12 = "
    $string18: .asciiz "c*12/1="
    $string19: .asciiz "1-(((12+1)))="
    $string20: .asciiz "arr[1]*'b'+fib(3)="
    $string21: .asciiz "addone(g_v_char_h)+add(1, fib(5))/G_v_int_a1 - tag[6]="
    $string22: .asciiz "please input an integer"
    $string23: .asciiz "please input 2 integers press enter for each integer"
    $string24: .asciiz " "
    $string25: .asciiz "input the number of fib you want(1~10)"
    $string26: .asciiz "this is a permutation of ABCDE"
.text
    addiu $sp,$sp,-188
    addiu $fp,$sp,-120
    j main
foo1:
addu $t0,$a1,$a2
move $v0,$t0
jr $ra
jr $ra
add:
addu $t0,$a1,$a2
move $v0,$t0
jr $ra
jr $ra
addchar:
addu $t0,$a1,$a2
move $v0,$t0
jr $ra
jr $ra
addone:
addiu $t0,$a1,1
move $v0,$t0
jr $ra
jr $ra
addint:
addiu $t0,$a1,1
move $v0,$t0
jr $ra
jr $ra
foo2:
li $t9,99
ble $a1,$t9,$LABEL1
li $t9,47
move $v0,$t9
jr $ra
j $LABEL2
$LABEL1:
li $t9,42
move $v0,$t9
jr $ra
$LABEL2:
jr $ra
test_string_int:
li $v0,1
li $t9,1
move $a0,$t9
syscall
li $v0,1
move $a0,$0
syscall
li $v0,1
move $a0,$0
syscall
li $v0,1
move $a0,$0
syscall
li $v0,1
li $t9,12
move $a0,$t9
syscall
li $v0,1
li $t9,-12
move $a0,$t9
syscall
li $v0,4
la $a0,$string0
syscall
jr $ra
jr $ra
fib:
li $t9,1
bne $a1,$t9,$LABEL3
li $t9,1
move $v0,$t9
jr $ra
j $LABEL4
$LABEL3:
li $t9,2
bne $a1,$t9,$LABEL5
li $t9,1
move $v0,$t9
jr $ra
$LABEL5:
$LABEL6:
$LABEL4:
addiu $t0,$a1,-1
sw $a1,-28($fp)
sw $t0,-40($fp)
sw $ra,-132($fp)
move $a1,$t0
addiu $sp,$fp,-132
addiu $fp,$sp,-28
jal fib
lw $a1,104($sp)
lw $t0,92($sp)
lw $ra,0($sp)
addiu $fp,$fp,160
addiu $sp,$sp,160
move $t1,$v0
addiu $t2,$a1,-2
sw $a1,-28($fp)
sw $t0,-40($fp)
sw $t1,-44($fp)
sw $t2,-48($fp)
sw $ra,-132($fp)
move $a1,$t2
addiu $sp,$fp,-132
addiu $fp,$sp,-28
jal fib
lw $a1,104($sp)
lw $t0,92($sp)
lw $t1,88($sp)
lw $t2,84($sp)
lw $ra,0($sp)
addiu $fp,$fp,160
addiu $sp,$sp,160
move $t3,$v0
addu $t4,$t1,$t3
move $v0,$t4
jr $ra
jr $ra
test_lots_paras:
addu $t0,$a1,$a2
addu $t1,$t0,$a3
subu $t2,$t1,$s1
addu $t3,$t2,$s0
move $v0,$t3
jr $ra
jr $ra
test_all_cond:
li $s3,1
li $s2,2
li $s1,2
li $s0,65
li $v0,4
la $a0,$string1
syscall
li $v0,4
la $a0,$string2
syscall
$LABEL7:
$LABEL8:
bge $s3,$s2,$LABEL9
li $v0,4
la $a0,$string3
syscall
$LABEL9:
$LABEL10:
ble $s1,$s3,$LABEL11
li $v0,4
la $a0,$string4
syscall
$LABEL11:
$LABEL12:
beq $s0,$0,$LABEL13
li $v0,4
la $a0,$string5
syscall
$LABEL13:
$LABEL14:
li $t9,1
bne $s3,$t9,$LABEL15
li $v0,4
la $a0,$string6
syscall
$LABEL15:
$LABEL16:
li $t9,1
beq $s3,$t9,$LABEL17
li $v0,4
la $a0,$string6
syscall
$LABEL17:
$LABEL18:
bgt $s3,$s1,$LABEL19
li $v0,4
la $a0,$string7
syscall
$LABEL19:
$LABEL20:
blt $s3,$s1,$LABEL21
li $v0,4
la $a0,$string8
syscall
$LABEL21:
$LABEL22:
li $t9,66
ble $s0,$t9,$LABEL23
li $v0,4
la $a0,$string8
syscall
$LABEL23:
$LABEL24:
jr $ra
jr $ra
test_diff_domain:
li $v0,11
li $t9,98
move $a0,$t9
syscall
li $v0,1
li $t9,222
move $a0,$t9
syscall
li $v0,4
la $a0,$string9
syscall
li $v0,1
li $t9,1
move $a0,$t9
syscall
li $v0,11
li $t9,102
move $a0,$t9
syscall
li $v0,11
li $t9,98
move $a0,$t9
syscall
li $v0,11
li $t9,98
move $a0,$t9
syscall
li $v0,1
li $t9,2
move $a0,$t9
syscall
li $v0,1
li $t9,3
move $a0,$t9
syscall
li $t9,72
sw $t9,84($gp)
lw $t0,84($gp)
li $v0,11
move $a0,$t0
syscall
li $t9,155
sw $t9,52($gp)
lw $t1,52($gp)
li $v0,1
move $a0,$t1
syscall
li $v0,4
la $a0,$string10
syscall
li $v0,1
move $a0,$a1
syscall
mul $t2,$a1,2
move $a1,$t2
li $v0,4
la $a0,$string11
syscall
li $v0,1
move $a0,$a1
syscall
li $t9,89
sw $t9,72($gp)
li $v0,11
li $t9,89
move $a0,$t9
syscall
jr $ra
test_expr:
li $v0,4
la $a0,$string12
syscall
li $t0,60
li $v0,4
la $a0,$string13
syscall
li $v0,1
li $t9,60
move $a0,$t9
syscall
li $t0,-50
li $v0,4
la $a0,$string14
syscall
li $v0,1
li $t9,-50
move $a0,$t9
syscall
li $t0,2
li $v0,4
la $a0,$string15
syscall
li $v0,1
li $t9,2
move $a0,$t9
syscall
sw $t0,-40($fp)
sw $ra,-132($fp)
li $t9,12
move $a1,$t9
addiu $sp,$fp,-132
addiu $fp,$sp,-28
jal fib
lw $t0,92($sp)
lw $ra,0($sp)
addiu $fp,$fp,160
addiu $sp,$sp,192
move $t1,$v0
sw $t0,-40($fp)
sw $t1,-44($fp)
sw $ra,-132($fp)
li $t9,14
move $a1,$t9
addiu $sp,$fp,-132
addiu $fp,$sp,-28
jal fib
lw $t0,92($sp)
lw $t1,88($sp)
lw $ra,0($sp)
addiu $fp,$fp,160
addiu $sp,$sp,192
move $t2,$v0
subu $t3,$t1,$t2
move $t0,$t3
li $v0,4
la $a0,$string16
syscall
li $v0,1
move $a0,$t0
syscall
li $t0,111
li $v0,4
la $a0,$string17
syscall
li $v0,1
li $t9,111
move $a0,$t9
syscall
li $t0,1188
li $v0,4
la $a0,$string18
syscall
li $v0,1
li $t9,1188
move $a0,$t9
syscall
li $t0,-12
li $v0,4
la $a0,$string19
syscall
li $v0,1
li $t9,-12
move $a0,$t9
syscall
li $t9,15
sw $t9,208($sp)
lw $t4,208($sp)
mul $t5,$t4,98
sw $t0,-40($fp)
sw $t1,-44($fp)
sw $t2,-48($fp)
sw $t3,-52($fp)
sw $t4,-56($fp)
sw $t5,-60($fp)
sw $ra,-132($fp)
li $t9,3
move $a1,$t9
addiu $sp,$fp,-132
addiu $fp,$sp,-28
jal fib
lw $t0,92($sp)
lw $t1,88($sp)
lw $t2,84($sp)
lw $t3,80($sp)
lw $t4,76($sp)
lw $t5,72($sp)
lw $ra,0($sp)
addiu $fp,$fp,160
addiu $sp,$sp,192
move $t6,$v0
addu $t7,$t5,$t6
move $t0,$t7
li $v0,4
la $a0,$string20
syscall
li $v0,1
move $a0,$t0
syscall
li $t9,5
sw $t9,24($gp)
li $t9,12
sw $t9,180($sp)
sw $t0,-40($fp)
sw $t1,-44($fp)
sw $t2,-48($fp)
sw $t3,-52($fp)
sw $t4,-56($fp)
sw $t5,-60($fp)
sw $t6,-64($fp)
sw $t7,-68($fp)
sw $ra,-132($fp)
li $t9,104
move $a1,$t9
addiu $sp,$fp,-132
addiu $fp,$sp,-4
jal addone
lw $t0,92($sp)
lw $t1,88($sp)
lw $t2,84($sp)
lw $t3,80($sp)
lw $t4,76($sp)
lw $t5,72($sp)
lw $t6,68($sp)
lw $t7,64($sp)
lw $ra,0($sp)
addiu $fp,$fp,136
addiu $sp,$sp,192
move $t8,$v0
sw $t0,-40($fp)
sw $t1,-44($fp)
sw $t2,-48($fp)
sw $t3,-52($fp)
sw $t4,-56($fp)
sw $t5,-60($fp)
sw $t6,-64($fp)
sw $t7,-68($fp)
sw $t8,-104($fp)
sw $ra,-132($fp)
li $t9,5
move $a1,$t9
addiu $sp,$fp,-132
addiu $fp,$sp,-28
jal fib
lw $t0,92($sp)
lw $t1,88($sp)
lw $t2,84($sp)
lw $t3,80($sp)
lw $t4,76($sp)
lw $t5,72($sp)
lw $t6,68($sp)
lw $t7,64($sp)
lw $t8,28($sp)
lw $ra,0($sp)
addiu $fp,$fp,160
addiu $sp,$sp,192
sw $t1,-4($sp)
move $t1,$v0
sw $t0,-44($fp)
sw $t1,-48($fp)
sw $t2,-52($fp)
sw $t3,-56($fp)
sw $t4,-60($fp)
sw $t5,-64($fp)
sw $t6,-68($fp)
sw $t7,-72($fp)
sw $t8,-108($fp)
sw $ra,-136($fp)
li $t9,1
move $a1,$t9
move $a2,$t1
addiu $sp,$fp,-136
addiu $fp,$sp,-4
jal add
lw $t0,92($sp)
lw $t1,88($sp)
lw $t2,84($sp)
lw $t3,80($sp)
lw $t4,76($sp)
lw $t5,72($sp)
lw $t6,68($sp)
lw $t7,64($sp)
lw $t8,28($sp)
lw $ra,0($sp)
addiu $fp,$fp,140
addiu $sp,$sp,196
sw $t2,-8($sp)
move $t2,$v0
sw $t3,-12($sp)
div $t3,$t2,5
sw $t4,-16($sp)
addu $t4,$t8,$t3
sw $t5,-20($sp)
lw $t5,180($sp)
sw $t6,-24($sp)
subu $t6,$t4,$t5
move $t0,$t6
li $v0,4
la $a0,$string21
syscall
li $v0,1
move $a0,$t0
syscall
jr $ra
jr $ra
test_scanf:
li $v0,4
la $a0,$string22
syscall
li $v0,5
syscall
move $t0,$v0
li $v0,1
move $a0,$t0
syscall
li $v0,4
la $a0,$string23
syscall
li $v0,5
syscall
move $t0,$v0
li $v0,5
syscall
move $t1,$v0
li $v0,1
move $a0,$t0
syscall
li $v0,1
move $a0,$t1
syscall
jr $ra
jr $ra
echo_char:
li $v0,11
move $a0,$a1
syscall
move $v0,$a1
jr $ra
jr $ra
really_void:
jr $ra
really_void2:
jr $ra
really_void3:
jr $ra
permutation:
addiu $t0,$a2,-1
bge $a1,$t0,$LABEL25
addiu $t0,$a1,1
sw $a1,-44($fp)
sw $a2,-48($fp)
sw $t0,-56($fp)
sw $s0,-88($fp)
sw $ra,-148($fp)
move $a1,$t0
move $a2,$a2
addiu $sp,$fp,-148
addiu $fp,$sp,-76
jal permutation
lw $a1,104($sp)
lw $a2,100($sp)
lw $t0,92($sp)
lw $s0,60($sp)
lw $ra,0($sp)
addiu $fp,$fp,224
addiu $sp,$sp,224
move $t1,$v0
addiu $t2,$a1,1
move $s0,$t2
$LABEL26:
bge $s0,$a2,$LABEL27
addiu $v1,$gp,276
sll $t9,$a1,2
addu $t9,$v1,$t9
lw $t0,0($t9)
move $t1,$t0
addiu $v1,$gp,276
sll $t9,$s0,2
addu $t9,$v1,$t9
lw $t2,0($t9)
addiu $v1,$gp,276
sll $t9,$a1,2
addu $v1,$v1,$t9
sw $t2,0($v1)
addiu $v1,$gp,276
sll $t9,$s0,2
addu $v1,$v1,$t9
sw $t1,0($v1)
addiu $t3,$a1,1
sw $a1,-44($fp)
sw $a2,-48($fp)
sw $t0,-56($fp)
sw $t1,-60($fp)
sw $t2,-64($fp)
sw $t3,-68($fp)
sw $s0,-88($fp)
sw $ra,-148($fp)
move $a1,$t3
move $a2,$a2
addiu $sp,$fp,-148
addiu $fp,$sp,-76
jal permutation
lw $a1,104($sp)
lw $a2,100($sp)
lw $t0,92($sp)
lw $t1,88($sp)
lw $t2,84($sp)
lw $t3,80($sp)
lw $s0,60($sp)
lw $ra,0($sp)
addiu $fp,$fp,224
addiu $sp,$sp,224
move $t4,$v0
addiu $v1,$gp,276
sll $t9,$a1,2
addu $t9,$v1,$t9
lw $t5,0($t9)
move $t1,$t5
addiu $v1,$gp,276
sll $t9,$s0,2
addu $t9,$v1,$t9
lw $t6,0($t9)
addiu $v1,$gp,276
sll $t9,$a1,2
addu $v1,$v1,$t9
sw $t6,0($v1)
addiu $v1,$gp,276
sll $t9,$s0,2
addu $v1,$v1,$t9
sw $t1,0($v1)
addiu $t7,$s0,1
move $s0,$t7
j $LABEL26
$LABEL27:
j $LABEL28
$LABEL25:
li $s0,0
$LABEL29:
addiu $v1,$gp,276
sll $t9,$s0,2
addu $t9,$v1,$t9
lw $t0,0($t9)
sw $a1,-28($fp)
sw $a2,-32($fp)
sw $t0,-40($fp)
sw $s0,-72($fp)
sw $ra,-132($fp)
move $a1,$t0
addiu $sp,$fp,-132
addiu $fp,$sp,0
jal echo_char
lw $a1,104($sp)
lw $a2,100($sp)
lw $t0,92($sp)
lw $s0,60($sp)
lw $ra,0($sp)
addiu $fp,$fp,132
addiu $sp,$sp,208
move $t1,$v0
move $t2,$t1
addiu $v1,$gp,276
sll $t9,$s0,2
addu $t9,$v1,$t9
lw $t3,0($t9)
beq $t2,$t3,$LABEL30
li $v0,4
la $a0,$string6
syscall
$LABEL30:
$LABEL31:
addiu $t0,$s0,1
move $s0,$t0
li $t9,5
blt $s0,$t9,$LABEL29
li $v0,4
la $a0,$string24
syscall
$LABEL28:
jr $ra
main:
li $s2,0
$LABEL32:
li $t9,10
bge $s2,$t9,$LABEL33
addiu $t0,$s2,1
sw $t0,-40($fp)
sw $s0,-72($fp)
sw $s1,-76($fp)
sw $s2,-80($fp)
sw $ra,-132($fp)
move $a1,$t0
addiu $sp,$fp,-132
addiu $fp,$sp,-28
jal fib
lw $t0,92($sp)
lw $s0,60($sp)
lw $s1,56($sp)
lw $s2,52($sp)
lw $ra,0($sp)
addiu $fp,$fp,160
addiu $sp,$sp,252
move $t1,$v0
addiu $v1,$sp,180
sll $t9,$s2,2
addu $v1,$v1,$t9
sw $t1,0($v1)
addiu $t2,$s2,1
move $s2,$t2
j $LABEL32
$LABEL33:
li $v0,4
la $a0,$string25
syscall
li $v0,5
syscall
move $s1,$v0
li $v0,5
syscall
move $s0,$v0
addiu $t0,$s1,-1
move $s2,$t0
$LABEL34:
li $v0,4
la $a0,$string24
syscall
addiu $v1,$sp,180
sll $t9,$s2,2
addu $t9,$v1,$t9
lw $t0,0($t9)
li $v0,1
move $a0,$t0
syscall
addiu $t1,$s2,1
move $s2,$t1
blt $s2,$s0,$LABEL34
addiu $t0,$s0,-1
move $s2,$t0
$LABEL35:
addiu $t0,$s1,-1
blt $s2,$t0,$LABEL36
li $v0,4
la $a0,$string24
syscall
addiu $v1,$sp,180
sll $t9,$s2,2
addu $t9,$v1,$t9
lw $t0,0($t9)
li $v0,1
move $a0,$t0
syscall
addiu $t1,$s2,-1
move $s2,$t1
j $LABEL35
$LABEL36:
sw $s0,-76($fp)
sw $s1,-80($fp)
sw $s2,-84($fp)
sw $ra,-136($fp)
li $t9,1
move $a1,$t9
li $t9,98
move $a2,$t9
addiu $sp,$fp,-136
addiu $fp,$sp,-4
jal foo1
lw $s0,60($sp)
lw $s1,56($sp)
lw $s2,52($sp)
lw $ra,0($sp)
addiu $fp,$fp,140
addiu $sp,$sp,256
move $t0,$v0
li $v0,1
move $a0,$t0
syscall
sw $t0,-44($fp)
sw $s0,-76($fp)
sw $s1,-80($fp)
sw $s2,-84($fp)
sw $ra,-136($fp)
li $t9,1
move $a1,$t9
li $t9,2
move $a2,$t9
addiu $sp,$fp,-136
addiu $fp,$sp,-4
jal add
lw $t0,92($sp)
lw $s0,60($sp)
lw $s1,56($sp)
lw $s2,52($sp)
lw $ra,0($sp)
addiu $fp,$fp,140
addiu $sp,$sp,256
move $t1,$v0
li $v0,1
move $a0,$t1
syscall
sw $t0,-44($fp)
sw $t1,-48($fp)
sw $s0,-76($fp)
sw $s1,-80($fp)
sw $s2,-84($fp)
sw $ra,-136($fp)
li $t9,97
move $a1,$t9
li $t9,98
move $a2,$t9
addiu $sp,$fp,-136
addiu $fp,$sp,-4
jal addchar
lw $t0,92($sp)
lw $t1,88($sp)
lw $s0,60($sp)
lw $s1,56($sp)
lw $s2,52($sp)
lw $ra,0($sp)
addiu $fp,$fp,140
addiu $sp,$sp,256
move $t2,$v0
li $v0,1
move $a0,$t2
syscall
sw $t0,-40($fp)
sw $t1,-44($fp)
sw $t2,-48($fp)
sw $s0,-72($fp)
sw $s1,-76($fp)
sw $s2,-80($fp)
sw $ra,-132($fp)
li $t9,70
move $a1,$t9
addiu $sp,$fp,-132
addiu $fp,$sp,-4
jal addone
lw $t0,92($sp)
lw $t1,88($sp)
lw $t2,84($sp)
lw $s0,60($sp)
lw $s1,56($sp)
lw $s2,52($sp)
lw $ra,0($sp)
addiu $fp,$fp,136
addiu $sp,$sp,252
move $t3,$v0
li $v0,1
move $a0,$t3
syscall
sw $t0,-40($fp)
sw $t1,-44($fp)
sw $t2,-48($fp)
sw $t3,-52($fp)
sw $s0,-72($fp)
sw $s1,-76($fp)
sw $s2,-80($fp)
sw $ra,-132($fp)
li $t9,16
move $a1,$t9
addiu $sp,$fp,-132
addiu $fp,$sp,-4
jal addint
lw $t0,92($sp)
lw $t1,88($sp)
lw $t2,84($sp)
lw $t3,80($sp)
lw $s0,60($sp)
lw $s1,56($sp)
lw $s2,52($sp)
lw $ra,0($sp)
addiu $fp,$fp,136
addiu $sp,$sp,252
move $t4,$v0
li $v0,1
move $a0,$t4
syscall
sw $t0,-40($fp)
sw $t1,-44($fp)
sw $t2,-48($fp)
sw $t3,-52($fp)
sw $t4,-56($fp)
sw $s0,-72($fp)
sw $s1,-76($fp)
sw $s2,-80($fp)
sw $ra,-132($fp)
li $t9,99
move $a1,$t9
addiu $sp,$fp,-132
addiu $fp,$sp,-4
jal foo2
lw $t0,92($sp)
lw $t1,88($sp)
lw $t2,84($sp)
lw $t3,80($sp)
lw $t4,76($sp)
lw $s0,60($sp)
lw $s1,56($sp)
lw $s2,52($sp)
lw $ra,0($sp)
addiu $fp,$fp,136
addiu $sp,$sp,252
move $t5,$v0
li $v0,11
move $a0,$t5
syscall
sw $t0,-40($fp)
sw $t1,-44($fp)
sw $t2,-48($fp)
sw $t3,-52($fp)
sw $t4,-56($fp)
sw $t5,-60($fp)
sw $s0,-72($fp)
sw $s1,-76($fp)
sw $s2,-80($fp)
sw $ra,-132($fp)
addiu $sp,$fp,-132
addiu $fp,$sp,0
jal test_string_int
lw $t0,92($sp)
lw $t1,88($sp)
lw $t2,84($sp)
lw $t3,80($sp)
lw $t4,76($sp)
lw $t5,72($sp)
lw $s0,60($sp)
lw $s1,56($sp)
lw $s2,52($sp)
lw $ra,0($sp)
addiu $fp,$fp,132
addiu $sp,$sp,252
move $t6,$v0
sw $t0,-48($fp)
sw $t1,-52($fp)
sw $t2,-56($fp)
sw $t3,-60($fp)
sw $t4,-64($fp)
sw $t5,-68($fp)
sw $t6,-72($fp)
sw $s0,-80($fp)
sw $s1,-84($fp)
sw $s2,-88($fp)
sw $ra,-140($fp)
li $t9,233
move $a1,$t9
addiu $sp,$fp,-140
addiu $fp,$sp,-16
jal test_diff_domain
lw $t0,92($sp)
lw $t1,88($sp)
lw $t2,84($sp)
lw $t3,80($sp)
lw $t4,76($sp)
lw $t5,72($sp)
lw $t6,68($sp)
lw $s0,60($sp)
lw $s1,56($sp)
lw $s2,52($sp)
lw $ra,0($sp)
addiu $fp,$fp,156
addiu $sp,$sp,260
move $t7,$v0
sw $t0,-120($fp)
sw $t1,-124($fp)
sw $t2,-128($fp)
sw $t3,-132($fp)
sw $t4,-136($fp)
sw $t5,-140($fp)
sw $t6,-144($fp)
sw $t7,-148($fp)
sw $s0,-152($fp)
sw $s1,-156($fp)
sw $s2,-160($fp)
sw $ra,-212($fp)
addiu $sp,$fp,-212
addiu $fp,$sp,-60
jal test_expr
lw $t0,92($sp)
lw $t1,88($sp)
lw $t2,84($sp)
lw $t3,80($sp)
lw $t4,76($sp)
lw $t5,72($sp)
lw $t6,68($sp)
lw $t7,64($sp)
lw $s0,60($sp)
lw $s1,56($sp)
lw $s2,52($sp)
lw $ra,0($sp)
addiu $fp,$fp,272
addiu $sp,$sp,332
move $t8,$v0
sw $t0,-52($fp)
sw $t1,-56($fp)
sw $t2,-60($fp)
sw $t3,-64($fp)
sw $t4,-68($fp)
sw $t5,-72($fp)
sw $t6,-76($fp)
sw $t7,-80($fp)
sw $s0,-84($fp)
sw $s1,-88($fp)
sw $s2,-92($fp)
sw $t8,-116($fp)
sw $ra,-144($fp)
addiu $sp,$fp,-144
addiu $fp,$sp,-36
jal test_all_cond
lw $t0,92($sp)
lw $t1,88($sp)
lw $t2,84($sp)
lw $t3,80($sp)
lw $t4,76($sp)
lw $t5,72($sp)
lw $t6,68($sp)
lw $t7,64($sp)
lw $s0,60($sp)
lw $s1,56($sp)
lw $s2,52($sp)
lw $t8,28($sp)
lw $ra,0($sp)
addiu $fp,$fp,180
addiu $sp,$sp,264
sw $t0,-44($sp)
move $t0,$v0
sw $t0,-44($fp)
sw $t1,-48($fp)
sw $t2,-52($fp)
sw $t3,-56($fp)
sw $t4,-60($fp)
sw $t5,-64($fp)
sw $t6,-68($fp)
sw $t7,-72($fp)
sw $s0,-76($fp)
sw $s1,-80($fp)
sw $s2,-84($fp)
sw $t8,-108($fp)
sw $ra,-136($fp)
addiu $sp,$fp,-136
addiu $fp,$sp,0
jal test_scanf
lw $t0,92($sp)
lw $t1,88($sp)
lw $t2,84($sp)
lw $t3,80($sp)
lw $t4,76($sp)
lw $t5,72($sp)
lw $t6,68($sp)
lw $t7,64($sp)
lw $s0,60($sp)
lw $s1,56($sp)
lw $s2,52($sp)
lw $t8,28($sp)
lw $ra,0($sp)
addiu $fp,$fp,136
addiu $sp,$sp,256
sw $t1,-48($sp)
move $t1,$v0
sw $t0,-40($fp)
sw $t1,-44($fp)
sw $t2,-48($fp)
sw $t3,-52($fp)
sw $t4,-56($fp)
sw $t5,-60($fp)
sw $t6,-64($fp)
sw $t7,-68($fp)
sw $s0,-72($fp)
sw $s1,-76($fp)
sw $s2,-80($fp)
sw $t8,-104($fp)
sw $ra,-132($fp)
li $t9,97
move $a1,$t9
addiu $sp,$fp,-132
addiu $fp,$sp,0
jal echo_char
lw $t0,92($sp)
lw $t1,88($sp)
lw $t2,84($sp)
lw $t3,80($sp)
lw $t4,76($sp)
lw $t5,72($sp)
lw $t6,68($sp)
lw $t7,64($sp)
lw $s0,60($sp)
lw $s1,56($sp)
lw $s2,52($sp)
lw $t8,28($sp)
lw $ra,0($sp)
addiu $fp,$fp,132
addiu $sp,$sp,252
sw $t2,-52($sp)
move $t2,$v0
sw $t0,-56($fp)
sw $t1,-60($fp)
sw $t2,-64($fp)
sw $t3,-68($fp)
sw $t4,-72($fp)
sw $t5,-76($fp)
sw $t6,-80($fp)
sw $t7,-84($fp)
sw $s0,-88($fp)
sw $s1,-92($fp)
sw $s2,-96($fp)
sw $t8,-120($fp)
sw $ra,-148($fp)
li $t9,1
move $a1,$t9
li $t9,2
move $a2,$t9
li $t9,99
move $a3,$t9
li $t9,100
move $s1,$t9
li $t9,5
move $s0,$t9
addiu $sp,$fp,-148
addiu $fp,$sp,-16
jal test_lots_paras
lw $t0,92($sp)
lw $t1,88($sp)
lw $t2,84($sp)
lw $t3,80($sp)
lw $t4,76($sp)
lw $t5,72($sp)
lw $t6,68($sp)
lw $t7,64($sp)
lw $s0,60($sp)
lw $s1,56($sp)
lw $s2,52($sp)
lw $t8,28($sp)
lw $ra,0($sp)
addiu $fp,$fp,164
addiu $sp,$sp,268
sw $t3,-56($sp)
move $t3,$v0
li $v0,1
move $a0,$t3
syscall
sw $t0,-36($fp)
sw $t1,-40($fp)
sw $t2,-44($fp)
sw $t3,-48($fp)
sw $t4,-52($fp)
sw $t5,-56($fp)
sw $t6,-60($fp)
sw $t7,-64($fp)
sw $s0,-68($fp)
sw $s1,-72($fp)
sw $s2,-76($fp)
sw $t8,-100($fp)
sw $ra,-128($fp)
addiu $sp,$fp,-128
addiu $fp,$sp,0
jal really_void
lw $t0,92($sp)
lw $t1,88($sp)
lw $t2,84($sp)
lw $t3,80($sp)
lw $t4,76($sp)
lw $t5,72($sp)
lw $t6,68($sp)
lw $t7,64($sp)
lw $s0,60($sp)
lw $s1,56($sp)
lw $s2,52($sp)
lw $t8,28($sp)
lw $ra,0($sp)
addiu $fp,$fp,128
addiu $sp,$sp,248
sw $t4,-60($sp)
move $t4,$v0
sw $t0,-36($fp)
sw $t1,-40($fp)
sw $t2,-44($fp)
sw $t3,-48($fp)
sw $t4,-52($fp)
sw $t5,-56($fp)
sw $t6,-60($fp)
sw $t7,-64($fp)
sw $s0,-68($fp)
sw $s1,-72($fp)
sw $s2,-76($fp)
sw $t8,-100($fp)
sw $ra,-128($fp)
addiu $sp,$fp,-128
addiu $fp,$sp,0
jal really_void2
lw $t0,92($sp)
lw $t1,88($sp)
lw $t2,84($sp)
lw $t3,80($sp)
lw $t4,76($sp)
lw $t5,72($sp)
lw $t6,68($sp)
lw $t7,64($sp)
lw $s0,60($sp)
lw $s1,56($sp)
lw $s2,52($sp)
lw $t8,28($sp)
lw $ra,0($sp)
addiu $fp,$fp,128
addiu $sp,$sp,248
sw $t5,-64($sp)
move $t5,$v0
sw $t0,-36($fp)
sw $t1,-40($fp)
sw $t2,-44($fp)
sw $t3,-48($fp)
sw $t4,-52($fp)
sw $t5,-56($fp)
sw $t6,-60($fp)
sw $t7,-64($fp)
sw $s0,-68($fp)
sw $s1,-72($fp)
sw $s2,-76($fp)
sw $t8,-100($fp)
sw $ra,-128($fp)
addiu $sp,$fp,-128
addiu $fp,$sp,0
jal really_void3
lw $t0,92($sp)
lw $t1,88($sp)
lw $t2,84($sp)
lw $t3,80($sp)
lw $t4,76($sp)
lw $t5,72($sp)
lw $t6,68($sp)
lw $t7,64($sp)
lw $s0,60($sp)
lw $s1,56($sp)
lw $s2,52($sp)
lw $t8,28($sp)
lw $ra,0($sp)
addiu $fp,$fp,128
addiu $sp,$sp,248
sw $t6,-68($sp)
move $t6,$v0
li $t9,65
sw $t9,276($gp)
li $t9,66
sw $t9,280($gp)
li $t9,67
sw $t9,284($gp)
li $t9,68
sw $t9,288($gp)
li $t9,69
sw $t9,292($gp)
li $v0,4
la $a0,$string26
syscall
sw $t0,-56($fp)
sw $t1,-60($fp)
sw $t2,-64($fp)
sw $t3,-68($fp)
sw $t4,-72($fp)
sw $t5,-76($fp)
sw $t6,-80($fp)
sw $t7,-84($fp)
sw $s0,-88($fp)
sw $s1,-92($fp)
sw $s2,-96($fp)
sw $t8,-120($fp)
sw $ra,-148($fp)
move $a1,$0
li $t9,5
move $a2,$t9
addiu $sp,$fp,-148
addiu $fp,$sp,-76
jal permutation
lw $t0,92($sp)
lw $t1,88($sp)
lw $t2,84($sp)
lw $t3,80($sp)
lw $t4,76($sp)
lw $t5,72($sp)
lw $t6,68($sp)
lw $t7,64($sp)
lw $s0,60($sp)
lw $s1,56($sp)
lw $s2,52($sp)
lw $t8,28($sp)
lw $ra,0($sp)
addiu $fp,$fp,224
addiu $sp,$sp,268
sw $t7,-72($sp)
move $t7,$v0
li $v0,10
syscall
li $v0,10
syscall
