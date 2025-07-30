.section .data
.section .text
.global main
main:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
;;#; Function
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
;;#; Variable Declaration: "debug_marker"
sub $8, %rsp
;;#; Variable Access: "a"
mov 16(%rbp), %rax
mov %rax, %rax
jmp .L1
;;#; If OTHERWISE
.L0:
;;#; If
;;#; Binary Operator: "<"
;;#; Variable Access: "a"
mov 16(%rbp), %rax
;;#; Variable Access: "b"
mov 24(%rbp), %r10
mov $0, %r11
mov $1, %rbx
cmp %r10, %rax
cmovl %rbx, %r11
;;#; If CONDITION
test %r11, %r11
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
mov 16(%rbp), %r10
sub %r10, %rax
pushq %rax
call gcd_euclid
add $16, %rsp
add $8, %rsp
mov %rax, %r10
jmp .L3
;;#; If OTHERWISE
.L2:
;;#; Function Call: "gcd_euclid"
pushq %rax
;;#; Binary Operator: "-"
;;#; Variable Access: "a"
mov 16(%rbp), %rax
;;#; Variable Access: "b"
mov 24(%rbp), %r11
sub %r11, %rax
pushq %rax
;;#; Variable Access: "b"
mov 24(%rbp), %rax
pushq %rax
call gcd_euclid
add $16, %rsp
add $8, %rsp
mov %rax, %r10
.L3:
mov %r10, %rax
.L1:
pop %rbx
pop %rsi
pop %rdi
add $40, %rsp
pop %rbp
ret
aftergcd_euclid:
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
