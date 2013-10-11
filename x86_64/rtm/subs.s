;;; -*- asm -*-

%define CPUID_EBX_RTM_BIT 1 << 11
%define EFLAGS_ZF_BIT 1 << 6

section .data

;;; set to 0 when rtminit finds out CPU can RTM
badinit:
	dq 1

abortcnt:
	dq 0

section .text
	global rtmxbegin
	global rtmxend
	global rtminit
	global rtmabortcnt

rtmxabort:
	mov rax, abortcnt
	lock inc qword [rax]
	mov rax, [rax]
	leave
	ret

rtmabortcnt:
	push rbp
	mov rbp, rsp
	mov rax, abortcnt
	mov rax, [rax]
	leave
	ret

;;; args in rdi, rsi, rdx
rtmxbegin:
	push rbp
        mov rbp, rsp
	xbegin rtmxabort
        leave
        ret

rtmxend:
	push rbp
	mov rbp, rsp
	xend
	leave
	ret

;;; return 0 if we're OK for RTM; non-zero otherwise
rtminit:
	push rbp
        mov rbp, rsp
	mov rax, 7
        cpuid
	mov rax, CPUID_EBX_RTM_BIT
	and rax, rbx
	mov rcx, 1
	cmp rax, 0
	cmove rax, rcx
	mov rcx, 0
	cmovne rax, rcx
	;; store result for later
	mov rbx, badinit
	mov [rbx], rax
        leave
        ret
