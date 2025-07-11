.section .data
b: .space 8
a: .space 8
.section .text
jmp afterfoo
foo:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
mov 16(%rbp), %rax
mov $10, %r10
add %rax, %r10
mov %r10, %rax
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
mov $10, %rax
pushq %rax
call foo
add $8, %rsp
add $32, %rsp
pop %rbp
ret
