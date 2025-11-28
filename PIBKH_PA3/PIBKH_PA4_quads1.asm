    .data
    .globl a
a:
    .long 0
    .globl b
b:
    .long 0
    .globl c
c:
    .long 0
    .globl result
result:
    .long 0
.LC_str_0:
    .string "a is max"
.LC_str_1:
    .string "Done"
_fmt_read_int:
    .string "%d"
_fmt_print_int:
    .string "%d"
_fmt_print_string:
    .string "%s"

    .text
    .extern printf
    .extern scanf

    .globl max
max:
    pushl %ebp
    movl %esp, %ebp
    subl $4, %esp
    movl $0, %eax
    movl 8(%ebp), %eax
    movl 12(%ebp), %ecx
    cmpl %ecx, %eax
    setg %al
    movzbl %al, %eax
    movl %eax, -4(%ebp)
    movl 8(%ebp), %eax
    movl 12(%ebp), %eax
.Lret_max:
    leave
    ret

    .globl main
main:
    pushl %ebp
    movl %esp, %ebp
    subl $56, %esp
    movl $0, %eax
    movl $10, %eax
    movl %eax, -4(%ebp)
    movl -4(%ebp), %eax
    movl %eax, a
    movl $20, %eax
    movl %eax, -8(%ebp)
    movl -8(%ebp), %eax
    movl %eax, b
    movl $0, %eax
    movl %eax, -12(%ebp)
    movl -12(%ebp), %eax
    movl %eax, c
    movl $5, %eax
    movl %eax, -16(%ebp)
    movl c, %eax
    movl -16(%ebp), %ecx
    cmpl %ecx, %eax
    setl %al
    movzbl %al, %eax
    movl %eax, -20(%ebp)
    movl $1, %eax
    movl %eax, -24(%ebp)
    movl c, %eax
    movl -24(%ebp), %ecx
    addl %ecx, %eax
    movl %eax, -28(%ebp)
    movl -28(%ebp), %eax
    movl %eax, c
    movl b, %eax
    pushl %eax
    movl a, %eax
    pushl %eax
    call max
    addl $8, %esp
    movl %eax, -32(%ebp)
    movl -32(%ebp), %eax
    movl %eax, a
    movl a, %eax
    movl b, %ecx
    cmpl %ecx, %eax
    setge %al
    movzbl %al, %eax
    movl %eax, -36(%ebp)
    movl $.LC_str_0, %eax
    movl %eax, -40(%ebp)
    movl -40(%ebp), %eax
    movl %eax, result
    movl b, %eax
    movl c, %ecx
    addl %ecx, %eax
    movl %eax, -44(%ebp)
    movl -44(%ebp), %eax
    movl %eax, b
    movl $2, %eax
    movl %eax, -48(%ebp)
    movl a, %eax
    movl -48(%ebp), %ecx
    imull %ecx, %eax
    movl %eax, -52(%ebp)
    movl -52(%ebp), %eax
    movl %eax, a
    movl $.LC_str_1, %eax
    movl %eax, -56(%ebp)
    movl -56(%ebp), %eax
    movl %eax, result
    jmp .Lret_main
.Lret_main:
    leave
    ret
