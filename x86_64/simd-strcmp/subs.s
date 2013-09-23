;;; -*- asm -*-

section .text
	global diffidx
	global cpuidfn

;;; args in rdi, rsi, rdx
diffidx:
	push rbp
        mov rbp, rsp
	add rsp, -8
	mov [rbp-8], r12	; It's nice to debuggers to store regs on stack.
	mov r12, 0		; r12 will keep a byte count of how far in we go
.loop:
	movdqu xmm0, [rdi]	; load in 128-bits from arg0
	movdqu xmm1, [rsi]	; load in 128-bits from arg1
	mov rax, rdx		; len for first operand is rax, len for 2nd is rdx
	pcmpestri xmm0, xmm1, 24 ; see 325383.pdf p. 661 for this crazy 3rd operand
	cmp rcx, 16		 ; if they're equal ...
	jne .end		 ; we're done.
	add r12, 16
	add rdx, -16
	cmp rdx, 0
	jle .end		; out of data
	add rdi, 16
	add rsi, 16
	jmp .loop
.end:
	add rcx, r12
	mov rax, rcx
	pop r12
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
