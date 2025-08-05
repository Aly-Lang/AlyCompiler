.section .data
foo: .space 8
sixty_nine: .space 8
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
;;#; INTEGER: 69
mov $69, %rax
pop %rbx
pop %rsi
pop %rdi
add $32, %rsp
pop %rbp
ret
after.L0:
lea .L0(%rip), %rax
mov %rax, sixty_nine(%rip)
;;#; Variable Reassignment
;;#; Function
jmp after.L1
.L1:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
push %rbx
push %rsi
push %rdi
;;#; Function Call: "int"
pushq %rax
;;#; Variable Access: "int"
mov 16(%rbp), %rax
call *%rax
add $8, %rsp
pop %rbx
pop %rsi
pop %rdi
add $32, %rsp
pop %rbp
ret
after.L1:
lea .L1(%rip), %rax
mov %rax, foo(%rip)
;;#; Function Call: "foo"
pushq %rax
;;#; Variable Access: "sixty_nine"
mov sixty_nine(%rip), %rax
pushq %rax
;;#; Variable Access: "foo"
mov foo(%rip), %rax
call *%rax
add $8, %rsp
add $8, %rsp
add $32, %rsp
pop %rbp
ret
