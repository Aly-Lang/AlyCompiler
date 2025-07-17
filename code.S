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
;;#; Addressof
lea -40(%rbp), %rax
mov %rax, -48(%rbp)
;;#; Variable Reassignment
;;#; INTEGER: 4
mov $4, %rax
;;#; Dereference
;;#; Variable Access: "ptr"
mov -48(%rbp), %r10
mov %rax, (%r10)
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
;;#; Function Call: "foo"
pushq %rax
call foo
add $8, %rsp
add $32, %rsp
pop %rbp
ret
