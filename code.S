.section .data
fact: .space 8
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
jz .L1
;;#; If THEN
;;#; INTEGER: 1
mov $1, %rax
mov %rax, %r10
jmp .L2
;;#; If OTHERWISE
.L1:
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
;;#; Variable Access: "fact"
mov fact(%rip), %r11
call *%r11
add $8, %rsp
mov %rax, %r11
pop %rax
imul %rax, %r11
mov %r11, %r10
.L2:
mov %r10, %rax
pop %rbx
pop %rsi
pop %rdi
add $32, %rsp
pop %rbp
ret
after.L0:
lea .L0(%rip), %rax
mov %rax, fact(%rip)
;;#; Function Call: "fact"
pushq %rax
;;#; INTEGER: 5
mov $5, %rax
pushq %rax
;;#; Variable Access: "fact"
mov fact(%rip), %rax
call *%rax
add $8, %rsp
add $8, %rsp
add $32, %rsp
pop %rbp
ret
