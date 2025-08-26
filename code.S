.section .data
first_int: .space 8
first_int_pointer: .space 8
int_array: .space 32
.section .text
.global main
main:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
;;#; Variable Reassignment
;;#; Index 0
lea int_array(%rip), %rax
mov %rax, first_int_pointer(%rip)
;;#; Variable Reassignment
;;#; Dereference
;;#; Index 0
lea int_array(%rip), %rax
mov %rax, first_int(%rip)
;;#; Variable Reassignment
;;#; INTEGER: 69
mov $69, %rax
;;#; Dereference
;;#; Index 0
lea int_array(%rip), %rcx
mov %rax, (%rcx)
;;#; Variable Reassignment
;;#; INTEGER: 420
mov $420, %rax
;;#; Dereference
;;#; Index 1
lea int_array(%rip), %rcx
add $8, %rcx
mov %rax, (%rcx)
;;#; Variable Reassignment
;;#; INTEGER: 69
mov $69, %rax
;;#; Dereference
;;#; Index 2
lea int_array(%rip), %rcx
add $16, %rcx
mov %rax, (%rcx)
;;#; Variable Reassignment
;;#; INTEGER: 420
mov $420, %rax
;;#; Dereference
;;#; Index 3
lea int_array(%rip), %rcx
add $24, %rcx
mov %rax, (%rcx)
add $32, %rsp
pop %rbp
ret
