.section .data
a: .space 8
.section .text
.global main
main:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
movq $42, a(%rip)
mov a(%rip), %rax
mov $42, %r10
mov $0, %r11
mov $1, %rbx
cmp %rax, %r10
cmove %rbx, %r11
test %r11, %r11
jz .L0
mov $5, %rax
mov %rax, %r10
jmp .L1
.L0:
mov $0, %r10
.L1:
mov %r10, %rax
add $32, %rsp
pop %rbp
ret
