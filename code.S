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
movq $420, a(%rip)
movq $42, b(%rip)
mov $0, %rax
add $32, %rsp
pop %rbp
ret
