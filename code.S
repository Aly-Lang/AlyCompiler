.section .data
a: .space 8
.section .text
.global main
main:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
movq $0, a(%rip)
add $32, %rsp
pop %rbp
ret
