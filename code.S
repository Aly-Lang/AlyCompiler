.section .data
.section .text
.global main
main:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
;;#; If
;;#; INTEGER: 1
mov $1, %rax
;;#; If CONDITION
test %rax, %rax
jz .L0
;;#; If THEN
;;#; INTEGER: 42
mov $42, %rax
mov %rax, %r10
jmp .L1
;;#; If OTHERWISE
.L0:
mov $0, %r10
;;#; INTEGER: 69
mov $69, %rax
mov %rax, %r10
.L1:
mov %r10, %rax
add $32, %rsp
pop %rbp
ret
