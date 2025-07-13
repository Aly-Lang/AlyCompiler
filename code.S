.section .data
c: .space 8
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
movq $69, a(%rip)
movq $420, a(%rip)
movq $42, b(%rip)
movq $59, a(%rip)
mov a(%rip), %rax
pushq %rax
call foo
add $8, %rsp
mov %rax, a(%rip)
mov a(%rip), %rax
movq $69, c(%rip)
mov c(%rip), %rax
add $32, %rsp
pop %rbp
ret
