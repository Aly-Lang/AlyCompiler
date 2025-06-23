.section .data
b: .space 8
a: .space 8
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
mov $420, %rax
mov %rax, a(%rip)
mov $42, %rax
mov %rax, b(%rip)
mov $69, %rax
add $32, %rsp
pop %rbp
ret
