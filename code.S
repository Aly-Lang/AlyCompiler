.section .data
a: .space 8
.section .text
.global main
main:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
;#; Variable Declaration
;#; Variable Reassignment
movq $30, a(%rip)
;#; If
;#; Binary Operator: "+"
;#; INTEGER: 1
mov $1, %rax
;#; INTEGER: 1
mov $1, %r10
add %rax, %r10
;#; If CONDITION
test %r10, %r10
jz .L0
;#; If THEN
;#; INTEGER: 69
mov $69, %rax
;#; If
;#; Binary Operator: "="
;#; Variable Access: "a"
mov a(%rip), %r10
;#; INTEGER: 42
mov $42, %r11
mov $0, %rbx
mov $1, %rdi
cmp %r10, %r11
cmove %rdi, %rbx
;#; If CONDITION
test %rbx, %rbx
jz .L2
;#; If THEN
;#; INTEGER: 5
mov $5, %r10
mov %r10, %r11
jmp .L3
;#; If OTHERWISE
.L2:
mov $0, %r11
.L3:
mov %r11, %rax
jmp .L1
;#; If OTHERWISE
.L0:
mov $0, %rax
.L1:
add $32, %rsp
pop %rbp
ret
