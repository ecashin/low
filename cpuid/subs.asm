
section .text
	global _cpuid

_cpuid:
	push rbp
        mov rbp, rsp
        mov rax, rdi
        cpuid
	mov rcx, rax
        leave
        ret
