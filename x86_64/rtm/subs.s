;;; -*- asm -*-

%define CPUID_EBX_RTM_BIT 1 << 11
%define EFLAGS_ZF_BIT 1 << 6

section .text
	global rtm
	global rtminit

;;; args in rdi, rsi, rdx
rtm:
	push rbp
        mov rbp, rsp
        leave
        ret

;;; return 0 if we're OK for RTM; non-zero otherwise
rtminit:
	push rbp
        mov rbp, rsp
        mov rax, 1
        cpuid
	mov rax, CPUID_EBX_RTM_BIT
	test rax, rbx
	;; now i am going to be obnoxious and avoid a jz
	pushfq			; thanks, x86_64 red zone!
	mov rax, [rbp-8]
 	and rax, EFLAGS_ZF_BIT
        leave
        ret
