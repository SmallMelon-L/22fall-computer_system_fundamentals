.text

.globl __ctx_record
__ctx_record:

movq   %rsp,0x8(%rdi)
movq   %rbx,0x10(%rdi)
movq   %rbp,0x18(%rdi)
movq   %r12,0x20(%rdi)
movq   %r13,0x28(%rdi)
movq   %r14,0x30(%rdi)
movq   %r15,0x38(%rdi)
movq   %rsi,0x40(%rdi)
movq   $0x0,0x48(%rdi)
movq   (%rsp),%rax
movq   %rax,0x50(%rdi)
movq   $0x0,%rax
retq

.globl __ctx_recover
__ctx_recover:

movq   %rsi,%rax
movq   0x8(%rdi),%rsp
add    $0x8,%rsp
movq   0x10(%rdi),%rbx
movq   0x18(%rdi),%rbp
movq   0x20(%rdi),%r12
movq   0x28(%rdi),%r13
movq   0x30(%rdi),%r14
movq   0x38(%rdi),%r15
movq   0x50(%rdi),%rsi
movq   %rsi,-0x8(%rsp)
movq   0x40(%rdi),%rsi
movq   0x48(%rdi),%rdi
jmp    *-0x8(%rsp)

