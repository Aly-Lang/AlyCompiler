jmp afterfoo
foo:
push %rbp
mov %rsp, %rbp
sub $32, %rsp
add $32, %rsp
pop %rbp
ret
afterfoo:
mov , a(%rip)
mov , b(%rip)
