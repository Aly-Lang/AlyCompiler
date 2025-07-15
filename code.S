.section .data
ptr: .space 8
a: .space 8
.section .text
.global main
main:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
;;#; Variable Reassignment
movq $0, a(%rip)
;;#; Variable Reassignment
mov %rax, ptr(%rip)
;;#; Variable Access: "a"
mov a(%rip), %rax
add $32, %rsp
pop %rbp
ret
