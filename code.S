.section .data
.section .text
jmp afterfoo
foo:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
add $32, %rsp
pop %rbp
ret
afterfoo:
.global main
main:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
mov $2, %rax
mov $3, %r10
imul %rax, %r10
mov $1, %r10
add %rax, %r10
add %r10, %rax
add $32, %rsp
pop %rbp
ret
