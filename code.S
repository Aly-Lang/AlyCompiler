.section .data
.section .text
jmp afterfoo
foo:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
push %rbx
push %rsi
push %rdi
;;#; Variable Declaration: "a"
sub $8, %rsp
;;#; Variable Reassignment
;;#; INTEGER: 0
mov $0, %rax
mov %rax, -40(%rbp)
;;#; Variable Declaration: "ptr"
sub $8, %rsp
;;#; Variable Reassignment
mov %rax, (null)
;;#; Variable Reassignment
;;#; INTEGER: 4
mov $4, %rax
mov %rax, (null)
;;#; Variable Access: "a"
mov -40(%rbp), %rax
pop %rbx
pop %rsi
pop %rdi
add $48, %rsp
pop %rbp
ret
afterfoo:
.global main
main:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
;;#; Function
add $32, %rsp
pop %rbp
ret
