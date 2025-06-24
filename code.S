.section .data
.section .text
.global main
main:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
mov $2, %rax
mov $2, %r10
add %rax, %r10
mov $8, %rax
sub %r10, %rax
mov $6, %rax
add %r10, %rax
add $32, %rsp
pop %rbp
ret
