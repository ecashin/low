;;; -*- asm -*-

section .text
	global diffidx
	global cpuidfn

;;; args in rdi, rsi, rdx
diffidx:
	push rbp
        mov rbp, rsp
	movdqu xmm0, [rdi]
	movdqu xmm1, [rsi]
	mov rax, rdx		; len for first operand is rax, len for 2nd is rdx
	pcmpestri xmm0, xmm1, 24 ; see 325383.pdf p. 661 for this crazy 3rd operand
	mov rax, rcx
        leave
        ret

cpuidfn:
	push rbp
        mov rbp, rsp
        mov rax, rdi
        cpuid
	mov rax, rcx
        leave
        ret
