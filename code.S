.section .data
.section .text
jmp afterfact
fact:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
push %rbx
push %rsi
push %rdi
;;#; If
;;#; Binary Operator: "<"
;;#; Variable Access: "n"
mov 16(%rbp), %rax
;;#; INTEGER: 2
mov $2, %r10
mov $0, %r11
mov $1, %rbx
cmp %r10, %rax
cmovl %rbx, %r11
;;#; If CONDITION
test %r11, %r11
jz .L0
;;#; If THEN
;;#; INTEGER: 1
mov $1, %rax
mov %rax, %r10
jmp .L1
;;#; If OTHERWISE
.L0:
;;#; Binary Operator: "*"
;;#; Variable Access: "n"
mov 16(%rbp), %rax
;;#; Function Call: "fact"
pushq %rax
;;#; Binary Operator: "-"
;;#; Variable Access: "n"
mov 16(%rbp), %r11
;;#; INTEGER: 1
mov $1, %rbx
sub %rbx, %r11
pushq %r11
call fact
add $8, %rsp
mov %rax, %r11
pop %rax
imul %rax, %r11
mov %r11, %r10
.L1:
mov %r10, %rax
pop %rbx
pop %rsi
pop %rdi
add $32, %rsp
pop %rbp
ret
afterfact:
.global main
main:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
;;#; Function Call: "fact"
pushq %rax
;;#; INTEGER: 5
mov $5, %rax
pushq %rax
call fact
add $8, %rsp
add $8, %rsp
add $32, %rsp
pop %rbp
ret
