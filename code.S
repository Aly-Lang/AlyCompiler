.section .data
.section .text
.global main
main:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
;;#; Binary Operator: "/"
;;#; INTEGER: 24
mov $24, %rax
;;#; INTEGER: 4
mov $4, %r10
push %rax
push %rdx
xor %rdx, %rdx
mov %rax, %rax
div %r10
mov %rax, %r11
pop %rdx
pop %rax
;;#; Binary Operator: "["
;;#; INTEGER: 2
mov $2, %r11
;;#; INTEGER: 2
mov $2, %rbx
push %rcx
mov %rbx, %rcx
shl %cl, %r11
pop %rcx
;;#; Binary Operator: "]"
;;#; INTEGER: 8
mov $8, %r11
;;#; INTEGER: 2
mov $2, %rbx
push %rcx
mov %rbx, %rcx
shr %cl, %r11
pop %rcx
mov %r11, %rax
add $32, %rsp
pop %rbp
ret
