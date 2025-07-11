.section .data
x: .space 8
z: .space 8
b: .space 8
a: .space 8
.section .text
jmp afterfoo
foo:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
sub $8, %rsp
mov -32(%rbp), %rax
mov $3, %rax
mov %rax, 16(%rbp)
mov 16(%rbp), %rax
add $40, %rsp
pop %rbp
ret
afterfoo:
.global main
main:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
movq $7, x(%rip)
movq $420, a(%rip)
movq $42, b(%rip)
movq $120, z(%rip)
mov $2, %rax
mov $3, %r10
imul %rax, %r10
mov $2, %rax
mov $1, %r11
add %rax, %r11
mov a(%rip), %rax
mov z(%rip), %rax
add $32, %rsp
pop %rbp
ret
