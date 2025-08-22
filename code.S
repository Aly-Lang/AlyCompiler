.section .data
.section .text
.global main
main:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
;;#; Function Call: "putchar"
pushq %rax
;;#; INTEGER: 69
mov $69, %rax
mov %rax, %rcx
call putchar
mov %rax, %rcx
pop %rax
;;#; Function Call: "putchar"
pushq %rax
;;#; INTEGER: 121
mov $121, %rcx
mov %rcx, %rcx
call putchar
mov %rax, %rdx
pop %rax
;;#; Function Call: "putchar"
pushq %rax
;;#; INTEGER: 121
mov $121, %rdx
mov %rdx, %rcx
call putchar
mov %rax, %r8
pop %rax
mov %r8, %rax
add $32, %rsp
pop %rbp
ret
