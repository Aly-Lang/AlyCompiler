.section .data
.section .text
.global main
main:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
mov $2, %rax
mov $3, %r10
imul %rax, %r10
mov $2, %r10
mov $1, %r11
add %rax, %r11
add $32, %rsp
pop %rbp
ret
