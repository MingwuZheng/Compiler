.data
.text
    sub $sp,$sp,128
    move $fp,$sp
    sub $fp,$fp,12
    j main
func_add:
lw $t9,0($gp)
move  $t0,$t9
addi $t1,$t0,1
move  $t9,$t1
sw $t9,0($gp)
lw $t9,0($gp)
move  $t2,$t9
move $v0,$t2
jr $ra
jr $ra
main:
lw $t9,0($gp)
move  $t0,$t9
sw $8,-36($fp)
sw $ra,-128($fp)
sub $sp,$fp,128
sub $fp,$sp,12
jal func_add
lw $8,92($sp)
lw $ra,0($sp)
addi $fp,$fp,140
addi $sp,$sp,140
move $t1,$v0
add $t2,$t0,$t1
li $v0,1
move $a0,$t2
syscall
li $v0,10
syscall
