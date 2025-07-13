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
mov $69, %rax
mov $1, %r10
mov $1, %r11
sub %r10, %r11
test %r11, %r11
jz .L1
mov $42, %r10
.L1:
.L0:
add $32, %rsp
pop %rbp
ret
