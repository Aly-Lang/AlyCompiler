.section .data
numptr: .space 8
number: .space 8
bar: .space 8
foo: .space 8
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
;;#; Variable Declaration: "a"
sub $8, %rsp
;;#; Variable Reassignment
;;#; INTEGER: 0
mov $0, %rax
mov %rax, -40(%rbp)
;;#; Variable Declaration: "b"
sub $8, %rsp
;;#; Variable Reassignment
;;#; INTEGER: 42
mov $42, %rax
mov %rax, -48(%rbp)
;;#; Variable Declaration: "ptr"
sub $8, %rsp
;;#; Variable Reassignment
;;#; Addressof
lea -40(%rbp), %rax
mov %rax, -56(%rbp)
;;#; Variable Reassignment
;;#; INTEGER: 69
mov $69, %rax
;;#; Dereference
;;#; Variable Access: "ptr"
mov -56(%rbp), %r10
mov %rax, (%r10)
;;#; Variable Declaration: "test_ptr"
sub $8, %rsp
;;#; Variable Reassignment
;;#; Addressof
lea -48(%rbp), %rax
mov %rax, -64(%rbp)
;;#; Variable Declaration: "ptrptr"
sub $8, %rsp
;;#; Variable Reassignment
;;#; Addressof
lea -56(%rbp), %rax
mov %rax, -72(%rbp)
;;#; Variable Reassignment
;;#; Variable Access: "test_ptr"
mov -64(%rbp), %rax
;;#; Dereference
;;#; Variable Access: "ptrptr"
mov -72(%rbp), %r10
mov %rax, (%r10)
;;#; Variable Reassignment
;;#; INTEGER: 42
mov $42, %rax
;;#; Dereference
;;#; Variable Access: "ptr"
mov -56(%rbp), %r10
mov %rax, (%r10)
;;#; Variable Access: "a"
mov -40(%rbp), %rax
pop %rbx
pop %rsi
pop %rdi
add $72, %rsp
pop %rbp
ret
after.L0:
lea .L0(%rip), %rax
mov %rax, foo(%rip)
;;#; Function Call: "foo"
pushq %rax
;;#; Variable Access: "foo"
mov foo(%rip), %rax
call *%rax
add $8, %rsp
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
;;#; Variable Reassignment
;;#; INTEGER: 69
mov $69, %rax
;;#; Dereference
;;#; Variable Access: "ptr"
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
after.L1:
lea .L1(%rip), %rax
mov %rax, bar(%rip)
;;#; Variable Reassignment
;;#; INTEGER: 0
mov $0, %rax
mov %rax, number(%rip)
;;#; Variable Reassignment
;;#; Addressof
lea number(%rip), %rax
mov %rax, numptr(%rip)
;;#; Function Call: "bar"
pushq %rax
;;#; Variable Access: "numptr"
mov numptr(%rip), %rax
pushq %rax
;;#; Variable Access: "bar"
mov bar(%rip), %rax
call *%rax
add $8, %rsp
add $8, %rsp
;;#; Variable Access: "number"
mov number(%rip), %rax
add $32, %rsp
pop %rbp
ret
