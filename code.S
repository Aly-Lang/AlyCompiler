.section .data
some_number: .space 8
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
;;#; Variable Access: "some_number"
mov some_number(%rip), %rax
mov %rax, %r10
jmp .L1
;;#; If OTHERWISE
.L0:
mov $0, %r10
.L1:
;;#; Variable Access: "some_number"
mov some_number(%rip), %rax
add $32, %rsp
pop %rbp
ret
