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
mov $42, %rax
mov a(%rip), %r10
mov $0, %r11
mov $0, %rbx
mov $1, %rdi
test %r10, %r11
cmove %rdi, %rbx
test %rbx, %rbx
jz .L1
mov a(%rip), %r10
mov $69, %r11
add %r10, %r11
.L1:
.L0:
mov %r11, %rax
add $32, %rsp
pop %rbp
ret
