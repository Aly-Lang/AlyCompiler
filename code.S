.section .data
.section .text
jmp aftergcd_euclid
gcd_euclid:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
push %rbx
push %rsi
push %rdi
;;#; If
;;#; Binary Operator: "="
;;#; Variable Access: "a"
mov 16(%rbp), %rax
;;#; Variable Access: "b"
mov 24(%rbp), %r10
mov $0, %r11
mov $1, %rbx
cmp %rax, %r10
cmove %rbx, %r11
;;#; If CONDITION
test %r11, %r11
jz .L0
;;#; If THEN
;;#; Variable Access: "a"
mov 16(%rbp), %rax
mov %rax, %r10
jmp .L1
;;#; If OTHERWISE
.L0:
;;#; If
;;#; Binary Operator: "<"
;;#; Variable Access: "a"
mov 16(%rbp), %rax
;;#; Variable Access: "b"
mov 24(%rbp), %r11
mov $0, %rbx
mov $1, %rdi
cmp %r11, %rax
cmovl %rdi, %rbx
;;#; If CONDITION
test %rbx, %rbx
jz .L2
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
mov 16(%rbp), %r11
sub %r11, %rax
pushq %rax
call gcd_euclid
add $16, %rsp
add $8, %rsp
mov %rax, %r11
jmp .L3
;;#; If OTHERWISE
.L2:
;;#; Function Call: "gcd_euclid"
pushq %rax
;;#; Binary Operator: "-"
;;#; Variable Access: "a"
mov 16(%rbp), %rax
;;#; Variable Access: "b"
mov 24(%rbp), %rbx
sub %rbx, %rax
pushq %rax
;;#; Variable Access: "b"
mov 24(%rbp), %rax
pushq %rax
call gcd_euclid
add $16, %rsp
add $8, %rsp
mov %rax, %r11
.L3:
mov %r11, %r10
.L1:
mov %r10, %rax
pop %rbx
pop %rsi
pop %rdi
add $32, %rsp
pop %rbp
ret
aftergcd_euclid:
.global main
main:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
;;#; Function Call: "gcd_euclid"
pushq %rax
;;#; INTEGER: 88
mov $88, %rax
pushq %rax
;;#; INTEGER: 32
mov $32, %rax
pushq %rax
call gcd_euclid
add $16, %rsp
add $8, %rsp
add $32, %rsp
pop %rbp
ret
