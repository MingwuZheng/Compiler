.data
    $string0: .asciiz " "
    $string1: .asciiz "\\n"
    $string2: .asciiz "ERROR!"
    $string3: .asciiz "ERROR!\\n"
.text
    sub $sp,$sp,136
    move $fp,$sp
    sub $fp,$fp,52
    j main
