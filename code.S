.section .data
a: .space 8
.section .text
.global main
main:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
movq $69, a(%rip)
movq $0, a(%rip)
mov $1, %rax
mov $1, %r10
add %rax, %r10
test %r10, %r10
jz .L0
movq $5, a(%rip)
mov $69, %rax
mov a(%rip), %rax
mov $1337, %r10
push %rbx
mov $0, %r11
mov $1, %rbx
test %rax, %r10
cmove %rbx, %r11
pop %rbx
test %r11, %r11
jz .L1
mov a(%rip), %rax
.L1:
.L0:
add $32, %rsp
pop %rbp
ret
