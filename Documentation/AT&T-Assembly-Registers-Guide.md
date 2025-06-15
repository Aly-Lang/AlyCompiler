# AT&T x86_64 Assembly Registers

| Register     | Size   | Purpose                                | Notes                               |
|:-------------|:-------|:---------------------------------------|:------------------------------------|
| `%rax`       | 64-bit | Return value, accumulator              | Function return values             |
| `%eax`       | 32-bit | Lower 32 bits of `%rax`                 |                                    |
| `%ax`        | 16-bit | Lower 16 bits of `%eax`                 |                                    |
| `%al`        | 8-bit  | Lower 8 bits of `%ax`                   |                                    |
| `%ah`        | 8-bit  | High 8 bits of `%ax` (bits 8–15)        |                                    |
| `%rbx`       | 64-bit | Callee-saved, base register             | Must be preserved across function calls |
| `%rcx`       | 64-bit | Counter for loops, 4th function argument | Used in string/loop operations (`rep movsb`) |
| `%rdx`       | 64-bit | I/O pointer, 3rd function argument     |                                    |
| `%rsi`       | 64-bit | Source index for string ops, 2nd argument |                                   |
| `%rdi`       | 64-bit | Destination index, 1st argument        |                                   |
| `%rsp`       | 64-bit | Stack pointer                          | Always points to the top of stack  |
| `%rbp`       | 64-bit | Base pointer (frame pointer)           | Often used to create a stable frame |
| `%r8`–`%r15` | 64-bit | Extra general-purpose registers        | Used for additional function arguments (5th–8th) |
| `%rip`       | 64-bit | Instruction pointer                    | Points to next instruction; used for RIP-relative addressing |
| `%rflags`    | 64-bit | Flags register                         | Status flags (CF, ZF, SF, OF, etc.) |

---

## Extra Notes

- **Register prefixes:**
  - In AT&T syntax, **registers are always prefixed with `%`**.
  - Immediate values (constants) are **prefixed with `$`**, e.g., `mov $5, %rax`.
  - Memory addresses are usually enclosed in parentheses, e.g., `mov (%rax), %rbx`.

- **Instruction operand order:**
  - **Source → Destination**, e.g., `mov %rax, %rbx` moves the contents of `%rax` into `%rbx`.
  - This is the **opposite** of Intel syntax, where it's destination first.

- **Calling convention (System V AMD64 ABI):**
  - Function arguments are passed in order using `%rdi`, `%rsi`, `%rdx`, `%rcx`, `%r8`, `%r9`.
  - Return values are passed back in `%rax` (or `%rax` + `%rdx` for larger returns).
  - Registers that **must be preserved** (callee-saved) across function calls: `%rbx`, `%rsp`, `%rbp`, `%r12`–`%r15`.
  - Caller-saved (volatile) registers: `%rdi`, `%rsi`, `%rdx`, `%rcx`, `%r8`, `%r9`, `%r10`, `%r11`.

- **Stack behavior:**
  - Stack grows **downward** (toward lower memory addresses).
  - `%rsp` always points to the current top of the stack.
  - Function prologues often push `%rbp`, then move `%rsp` into `%rbp` to set up a stable frame.

- **Instruction pointer:**
  - `%rip` is special — it **cannot be directly read or written**; it's used indirectly for things like position-independent code (PIC).

- **Flags (`%rflags` register):**
  - Important status bits:
    - **CF**: Carry Flag (for unsigned overflow)
    - **ZF**: Zero Flag (result was zero)
    - **SF**: Sign Flag (result was negative)
    - **OF**: Overflow Flag (for signed overflow)

---

## Quick Example

```asm
mov $10, %rax        # Move immediate value 10 into %rax
add %rbx, %rax       # Add %rbx to %rax, store result in %rax
mov %rax, (%rcx)     # Move %rax into memory address pointed by %rcx
```