.section .data
int_array: .space 16
.section .text
.global main
main:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
;;#; Variable Reassignment
;;#; INTEGER: 506631917033178453
mov $506631917033178453, %rax
;;#; Dereference
;;#; Index 0
lea int_array(%rip), %rcx
mov %rax, (%rcx)
;;#; Variable Reassignment
;;#; INTEGER: 506776893918711584
mov $506776893918711584, %rax
;;#; Dereference
;;#; Index 1
lea int_array(%rip), %rcx
add $8, %rcx
mov %rax, (%rcx)
;;#; Variable Access: "int_array"
mov int_array(%rip), %rax
;;#; Index 0
lea int_array(%rip), %rax
;;#; Dereference
;;#; Index 0
lea int_array(%rip), %rax
add $32, %rsp
pop %rbp
ret
