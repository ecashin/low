;;; -*- asm -*-

%define CPUID_EBX_RTM_BIT 1 << 11
%define EFLAGS_ZF_BIT 1 << 6

section .data

;;; set to 0 when rtminit finds out CPU can RTM
badinit:
	dq 1

section .text
	global rtm
	global rtminit

;;; args in rdi, rsi, rdx
rtm:
	push rbp
        mov rbp, rsp
	mov rbx, badinit
	mov rax, [rbx]
        leave
        ret

;;; return 0 if we're OK for RTM; non-zero otherwise
rtminit:
	push rbp
        mov rbp, rsp
        mov rax, 1
        cpuid
	mov rax, CPUID_EBX_RTM_BIT
	mov rcx, 1
	and rax, rbx
	test rax, rax
	cmovz rax, rcx
	mov rcx, 0
	cmovnz rax, rcx
	;; store result for later
	mov rbx, badinit
	mov [rbx], rax
        leave
        ret
