.section .data
gcd_euclid: .space 8
.section .text
.global main
main:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
;;#; Variable Reassignment
;;#; Function
jmp after.L0
.L0:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
;;#; If
;;#; Binary Operator: "="
;;#; Variable Access: "a"
mov 16(%rbp), %rax
;;#; Variable Access: "b"
mov 24(%rbp), %rcx
mov $0, %rdx
mov $1, %r8
cmp %rax, %rcx
cmove %r8, %rdx
;;#; If CONDITION
test %rdx, %rdx
jz .L1
;;#; If THEN
;;#; Variable Access: "a"
mov 16(%rbp), %rax
mov %rax, %rcx
jmp .L2
;;#; If OTHERWISE
.L1:
;;#; If
;;#; Binary Operator: "<"
;;#; Variable Access: "a"
mov 16(%rbp), %rax
;;#; Variable Access: "b"
mov 24(%rbp), %rdx
mov $0, %r8
mov $1, %r9
cmp %rdx, %rax
cmovl %r9, %r8
;;#; If CONDITION
test %r8, %r8
jz .L3
;;#; If THEN
;;#; Function Call: "gcd_euclid"
pushq %rax
;;#; Variable Access: "a"
mov 16(%rbp), %rax
pushq %rax
;;#; Binary Operator: "-"
;;#; Variable Access: "b"
mov 24(%rbp), %rax
;;#; Variable Access: "a"
mov 16(%rbp), %rdx
sub %rdx, %rax
pushq %rax
;;#; Variable Access: "gcd_euclid"
mov gcd_euclid(%rip), %rax
call *%rax
add $16, %rsp
add $8, %rsp
mov %rax, %rdx
jmp .L4
;;#; If OTHERWISE
.L3:
;;#; Function Call: "gcd_euclid"
pushq %rax
;;#; Binary Operator: "-"
;;#; Variable Access: "a"
mov 16(%rbp), %rax
;;#; Variable Access: "b"
mov 24(%rbp), %r8
sub %r8, %rax
pushq %rax
;;#; Variable Access: "b"
mov 24(%rbp), %rax
pushq %rax
;;#; Variable Access: "gcd_euclid"
mov gcd_euclid(%rip), %rax
call *%rax
add $16, %rsp
add $8, %rsp
mov %rax, %rdx
.L4:
mov %rdx, %rcx
.L2:
mov %rcx, %rax
add $32, %rsp
pop %rbp
ret
after.L0:
lea .L0(%rip), %rax
mov %rax, gcd_euclid(%rip)
;;#; Function Call: "gcd_euclid"
pushq %rax
;;#; INTEGER: 88
mov $88, %rax
pushq %rax
;;#; INTEGER: 32
mov $32, %rax
pushq %rax
;;#; Variable Access: "gcd_euclid"
mov gcd_euclid(%rip), %rax
call *%rax
add $16, %rsp
add $8, %rsp
add $32, %rsp
pop %rbp
ret
