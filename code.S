.section .data
barbar: .space 8
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
;;#; INTEGER: 42
mov $42, %rax
pop %rbx
pop %rsi
pop %rdi
add $32, %rsp
pop %rbp
ret
after.L0:
lea .L0(%rip), %rax
mov %rax, foo(%rip)
;;#; Function
jmp after.L1
.L1:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
push %rbx
push %rsi
push %rdi
;;#; INTEGER: 5
mov $5, %rax
pop %rbx
pop %rsi
pop %rdi
add $32, %rsp
pop %rbp
ret
after.L1:
lea .L1(%rip), %rax
;;#; Function
jmp after.L2
.L2:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
push %rbx
push %rsi
push %rdi
;;#; Variable Declaration: "a"
sub $8, %rsp
;;#; Variable Reassignment
;;#; INTEGER: 69
mov $69, %rax
mov %rax, -40(%rbp)
;;#; Function
jmp after.L3
.L3:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
push %rbx
push %rsi
push %rdi
;;#; INTEGER: 42
mov $42, %rax
pop %rbx
pop %rsi
pop %rdi
add $32, %rsp
pop %rbp
ret
after.L3:
lea .L3(%rip), %rax
;;#; Variable Access: "a"
mov -40(%rbp), %rax
pop %rbx
pop %rsi
pop %rdi
add $40, %rsp
pop %rbp
ret
after.L2:
lea .L2(%rip), %rax
;;#; Function
jmp after.L4
.L4:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
push %rbx
push %rsi
push %rdi
;;#; INTEGER: 5
mov $5, %rax
pop %rbx
pop %rsi
pop %rdi
add $32, %rsp
pop %rbp
ret
after.L4:
lea .L4(%rip), %rax
;;#; Variable Reassignment
;;#; Variable Access: "bar"
mov bar(%rip), %rax
mov %rax, barbar(%rip)
;;#; Function Call: "foo"
pushq %rax
;;#; Variable Access: "foo"
mov foo(%rip), %rax
call *%rax
add $8, %rsp
add $32, %rsp
pop %rbp
ret
