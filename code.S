.section .data
.section .text
jmp afterfoo
foo:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
sub $8, %rspadd $32, %rsp
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
mov $2, %rax
mov $1, %r11
add %rax, %r11
add $32, %rsp
pop %rbp
ret
