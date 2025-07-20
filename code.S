.section .data
bar: .space 8
.section .text
jmp afterfoo
foo:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
push %rbx
push %rsi
push %rdi
;;#; Binary Operator: "+"
;;#; Variable Access: "x"
mov 16(%rbp), %rax
;;#; INTEGER: 35
mov $35, %r10
add %rax, %r10
mov %r10, %rax
pop %rbx
pop %rsi
pop %rdi
add $32, %rsp
pop %rbp
ret
afterfoo:
.global main
main:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
;;#; Function
;;#; Function Call: "foo"
pushq %rax
;;#; Variable Access: "bar"
mov bar(%rip), %rax
pushq %rax
call foo
add $8, %rsp
add $8, %rsp
add $32, %rsp
pop %rbp
ret
