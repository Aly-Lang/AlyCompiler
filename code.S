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
;;#; Variable Reassignment
;;#; INTEGER: 69
mov $69, %rax
;;#; Dereference
;;#; Variable Access: "x"
mov 16(%rbp), %r10
mov %rax, (%r10)
;;#; INTEGER: 0
mov $0, %rax
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
;;#; Variable Reassignment
;;#; INTEGER: 42
mov $42, %rax
mov %rax, bar(%rip)
;;#; Function Call: "foo"
pushq %rax
;;#; Addressof
lea bar(%rip), %rax
pushq %rax
call foo
add $8, %rsp
add $8, %rsp
;;#; Variable Access: "bar"
mov bar(%rip), %rax
add $32, %rsp
pop %rbp
ret
