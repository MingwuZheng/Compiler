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
addu $v0,$a1,$a2
jr $ra
add:
addu $v0,$a1,$a2
jr $ra
addchar:
addu $v0,$a1,$a2
jr $ra
addone:
addiu $v0,$a1,1
jr $ra
addint:
addiu $v0,$a1,1
jr $ra
foo2:
li $t9,99
ble $a1,$t9,$LABEL1
li $v0,47
jr $ra
j $LABEL2
$LABEL1:
li $v0,42
jr $ra
$LABEL2:
jr $ra
test_string_int:
li $v0,1
li $a0,1
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
li $a0,12
syscall
li $v0,1
li $a0,-12
syscall
li $v0,4
la $a0,$string0
syscall
jr $ra
fib:
li $t9,1
bne $a1,$t9,$LABEL3
li $v0,1
jr $ra
j $LABEL4
$LABEL3:
li $t9,2
bne $a1,$t9,$LABEL5
li $v0,1
jr $ra
$LABEL5:
$LABEL6:
$LABEL4:
addiu $t0,$a1,-1
sw $a1,-28($fp)
sw $ra,-132($fp)
move $a1,$t0
addiu $sp,$fp,-132
addiu $fp,$sp,-28
jal fib
lw $a1,104($sp)
lw $ra,0($sp)
addiu $fp,$fp,160
addiu $sp,$sp,160
move $t1,$v0
addiu $t2,$a1,-2
sw $a1,-28($fp)
sw $t1,-44($fp)
sw $ra,-132($fp)
move $a1,$t2
addiu $sp,$fp,-132
addiu $fp,$sp,-28
jal fib
lw $a1,104($sp)
lw $t1,88($sp)
lw $ra,0($sp)
addiu $fp,$fp,160
addiu $sp,$sp,160
move $t3,$v0
addu $v0,$t1,$t3
jr $ra
test_lots_paras:
addu $t0,$a1,$a2
addu $t1,$t0,$a3
subu $t2,$t1,$s1
addu $v0,$t2,$s0
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
test_diff_domain:
li $v0,11
li $a0,98
syscall
li $v0,1
li $a0,222
syscall
li $v0,4
la $a0,$string9
syscall
li $v0,1
li $a0,1
syscall
li $v0,11
li $a0,102
syscall
li $v0,11
li $a0,98
syscall
li $v0,11
li $a0,98
syscall
li $v0,1
li $a0,2
syscall
li $v0,1
li $a0,3
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
mul $a1,$a1,2
li $v0,4
la $a0,$string11
syscall
li $v0,1
move $a0,$a1
syscall
li $t9,89
sw $t9,72($gp)
li $v0,11
li $a0,89
syscall
jr $ra
test_expr:
li $v0,4
la $a0,$string12
syscall
li $v0,4
la $a0,$string13
syscall
li $v0,1
li $a0,60
syscall
li $v0,4
la $a0,$string14
syscall
li $v0,1
li $a0,-50
syscall
li $v0,4
la $a0,$string15
syscall
li $v0,1
li $a0,2
syscall
sw $ra,-132($fp)
li $a1,12
addiu $sp,$fp,-132
addiu $fp,$sp,-28
jal fib
lw $ra,0($sp)
addiu $fp,$fp,160
addiu $sp,$sp,192
move $t1,$v0
sw $t1,-44($fp)
sw $ra,-132($fp)
li $a1,14
addiu $sp,$fp,-132
addiu $fp,$sp,-28
jal fib
lw $t1,88($sp)
lw $ra,0($sp)
addiu $fp,$fp,160
addiu $sp,$sp,192
move $t2,$v0
subu $t0,$t1,$t2
li $v0,4
la $a0,$string16
syscall
li $v0,1
move $a0,$t0
syscall
li $v0,4
la $a0,$string17
syscall
li $v0,1
li $a0,111
syscall
li $v0,4
la $a0,$string18
syscall
li $v0,1
li $a0,1188
syscall
li $v0,4
la $a0,$string19
syscall
li $v0,1
li $a0,-12
syscall
li $t9,15
sw $t9,208($sp)
lw $t4,208($sp)
mul $t5,$t4,98
sw $t1,-44($fp)
sw $t2,-48($fp)
sw $t3,-52($fp)
sw $ra,-132($fp)
li $a1,3
addiu $sp,$fp,-132
addiu $fp,$sp,-28
jal fib
lw $t1,88($sp)
lw $t2,84($sp)
lw $t3,80($sp)
lw $ra,0($sp)
addiu $fp,$fp,160
addiu $sp,$sp,192
move $t6,$v0
addu $t0,$t5,$t6
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
sw $ra,-132($fp)
li $a1,104
addiu $sp,$fp,-132
addiu $fp,$sp,-4
jal addone
lw $ra,0($sp)
addiu $fp,$fp,136
addiu $sp,$sp,192
move $t8,$v0
sw $t1,-44($fp)
sw $t2,-48($fp)
sw $t3,-52($fp)
sw $ra,-132($fp)
li $a1,5
addiu $sp,$fp,-132
addiu $fp,$sp,-28
jal fib
lw $t1,88($sp)
lw $t2,84($sp)
lw $t3,80($sp)
lw $ra,0($sp)
addiu $fp,$fp,160
addiu $sp,$sp,192
sw $t1,-4($sp)
move $t1,$v0
sw $ra,-136($fp)
li $a1,1
move $a2,$t1
addiu $sp,$fp,-136
addiu $fp,$sp,-4
jal add
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
subu $t0,$t4,$t5
li $v0,4
la $a0,$string21
syscall
li $v0,1
move $a0,$t0
syscall
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
echo_char:
li $v0,11
move $a0,$a1
syscall
move $v0,$a1
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
sw $s0,-88($fp)
sw $ra,-148($fp)
move $a1,$t0
addiu $sp,$fp,-148
addiu $fp,$sp,-76
jal permutation
lw $a1,104($sp)
lw $a2,100($sp)
lw $s0,60($sp)
lw $ra,0($sp)
addiu $fp,$fp,224
addiu $sp,$sp,224
addiu $s0,$a1,1
$LABEL26:
bge $s0,$a2,$LABEL27
addiu $v1,$gp,276
sll $t9,$a1,2
addu $t9,$v1,$t9
lw $t1,0($t9)
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
sw $s0,-88($fp)
sw $ra,-148($fp)
move $a1,$t3
addiu $sp,$fp,-148
addiu $fp,$sp,-76
jal permutation
lw $a1,104($sp)
lw $a2,100($sp)
lw $s0,60($sp)
lw $ra,0($sp)
addiu $fp,$fp,224
addiu $sp,$sp,224
addiu $v1,$gp,276
sll $t9,$a1,2
addu $t9,$v1,$t9
lw $t1,0($t9)
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
addiu $s0,$s0,1
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
sw $s0,-72($fp)
sw $ra,-132($fp)
move $a1,$t0
addiu $sp,$fp,-132
addiu $fp,$sp,0
jal echo_char
lw $a1,104($sp)
lw $a2,100($sp)
lw $s0,60($sp)
lw $ra,0($sp)
addiu $fp,$fp,132
addiu $sp,$sp,208
move $t2,$v0
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
addiu $s0,$s0,1
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
sw $s2,-80($fp)
sw $ra,-132($fp)
move $a1,$t0
addiu $sp,$fp,-132
addiu $fp,$sp,-28
jal fib
lw $s2,52($sp)
lw $ra,0($sp)
addiu $fp,$fp,160
addiu $sp,$sp,252
move $t1,$v0
addiu $v1,$sp,180
sll $t9,$s2,2
addu $v1,$v1,$t9
sw $t1,0($v1)
addiu $s2,$s2,1
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
addiu $s2,$s1,-1
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
addiu $s2,$s2,1
blt $s2,$s0,$LABEL34
addiu $s2,$s0,-1
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
addiu $s2,$s2,-1
j $LABEL35
$LABEL36:
sw $ra,-136($fp)
li $a1,1
li $a2,98
addiu $sp,$fp,-136
addiu $fp,$sp,-4
jal foo1
lw $ra,0($sp)
addiu $fp,$fp,140
addiu $sp,$sp,256
move $t0,$v0
li $v0,1
move $a0,$t0
syscall
sw $ra,-136($fp)
li $a1,1
li $a2,2
addiu $sp,$fp,-136
addiu $fp,$sp,-4
jal add
lw $ra,0($sp)
addiu $fp,$fp,140
addiu $sp,$sp,256
move $t1,$v0
li $v0,1
move $a0,$t1
syscall
sw $ra,-136($fp)
li $a1,97
li $a2,98
addiu $sp,$fp,-136
addiu $fp,$sp,-4
jal addchar
lw $ra,0($sp)
addiu $fp,$fp,140
addiu $sp,$sp,256
move $t2,$v0
li $v0,1
move $a0,$t2
syscall
sw $ra,-132($fp)
li $a1,70
addiu $sp,$fp,-132
addiu $fp,$sp,-4
jal addone
lw $ra,0($sp)
addiu $fp,$fp,136
addiu $sp,$sp,252
move $t3,$v0
li $v0,1
move $a0,$t3
syscall
sw $ra,-132($fp)
li $a1,16
addiu $sp,$fp,-132
addiu $fp,$sp,-4
jal addint
lw $ra,0($sp)
addiu $fp,$fp,136
addiu $sp,$sp,252
move $t4,$v0
li $v0,1
move $a0,$t4
syscall
sw $ra,-132($fp)
li $a1,99
addiu $sp,$fp,-132
addiu $fp,$sp,-4
jal foo2
lw $ra,0($sp)
addiu $fp,$fp,136
addiu $sp,$sp,252
move $t5,$v0
li $v0,11
move $a0,$t5
syscall
sw $ra,-132($fp)
addiu $sp,$fp,-132
addiu $fp,$sp,0
jal test_string_int
lw $ra,0($sp)
addiu $fp,$fp,132
addiu $sp,$sp,252
move $t6,$v0
sw $t0,-48($fp)
sw $t1,-52($fp)
sw $ra,-140($fp)
li $a1,233
addiu $sp,$fp,-140
addiu $fp,$sp,-16
jal test_diff_domain
lw $t0,92($sp)
lw $t1,88($sp)
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
lw $ra,0($sp)
addiu $fp,$fp,272
addiu $sp,$sp,332
sw $ra,-144($fp)
addiu $sp,$fp,-144
addiu $fp,$sp,-36
jal test_all_cond
lw $ra,0($sp)
addiu $fp,$fp,180
addiu $sp,$sp,264
sw $t0,-44($sp)
sw $t1,-48($fp)
sw $ra,-136($fp)
addiu $sp,$fp,-136
addiu $fp,$sp,0
jal test_scanf
lw $t1,88($sp)
lw $ra,0($sp)
addiu $fp,$fp,136
addiu $sp,$sp,256
sw $t1,-48($sp)
sw $ra,-132($fp)
li $a1,97
addiu $sp,$fp,-132
addiu $fp,$sp,0
jal echo_char
lw $ra,0($sp)
addiu $fp,$fp,132
addiu $sp,$sp,252
sw $t2,-52($sp)
sw $ra,-148($fp)
li $a1,1
li $a2,2
li $a3,99
li $s1,100
li $s0,5
addiu $sp,$fp,-148
addiu $fp,$sp,-16
jal test_lots_paras
lw $ra,0($sp)
addiu $fp,$fp,164
addiu $sp,$sp,268
sw $t3,-56($sp)
move $t3,$v0
li $v0,1
move $a0,$t3
syscall
sw $ra,-128($fp)
addiu $sp,$fp,-128
addiu $fp,$sp,0
jal really_void
lw $ra,0($sp)
addiu $fp,$fp,128
addiu $sp,$sp,248
sw $t4,-60($sp)
sw $ra,-128($fp)
addiu $sp,$fp,-128
addiu $fp,$sp,0
jal really_void2
lw $ra,0($sp)
addiu $fp,$fp,128
addiu $sp,$sp,248
sw $t5,-64($sp)
sw $ra,-128($fp)
addiu $sp,$fp,-128
addiu $fp,$sp,0
jal really_void3
lw $ra,0($sp)
addiu $fp,$fp,128
addiu $sp,$sp,248
sw $t6,-68($sp)
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
sw $ra,-148($fp)
move $a1,$0
li $a2,5
addiu $sp,$fp,-148
addiu $fp,$sp,-76
jal permutation
lw $ra,0($sp)
addiu $fp,$fp,224
addiu $sp,$sp,268
sw $t7,-72($sp)
li $v0,10
syscall
li $v0,10
syscall
