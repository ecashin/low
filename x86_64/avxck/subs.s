;;; -*- asm -*-

%define CPUID_ECX_OSXSAVE_BIT 1 << 27
%define CPUID_ECX_AVX_BIT 1 << 28
%define EFLAGS_ZF_BIT 1 << 6

section .data

;;; set to 0 when pxorinit finds out CPU can do AVX
%define avx_not_checked 3
%define avx_yes 0
%define avx_no 1
avxcheck:
	dq avx_not_checked

section .text
	global pxordemo
	global pxorinit

;;; args in rdi, rsi, rdx
pxordemo:
	push rbp
        mov rbp, rsp
	mov rbx, avxcheck
	mov rax, [rbx]
        leave
        ret

oldpxorinit:
	push rbp
	mov rbp, rsp
	mov rax, 0
	leave
	ret

;;; check for avx
pxorinit:
	push rbp
        mov rbp, rsp
        mov rax, 1
        cpuid
	mov rax, CPUID_ECX_OSXSAVE_BIT
	test rax, rcx
	jz .nope
	mov rcx, 0
	xgetbv
	and rax, 6		; check O.S. support bits are set in xcr0
	cmp rax, 6
	jne .nope
	mov rax, 1
	cpuid
	test rcx, CPUID_ECX_AVX_BIT
	jz .nope
	mov rax, avx_yes
	mov rbx, avxcheck
	mov [rbx], rax
	leave
	ret
.nope:
	mov rax, avx_no
	mov rbx, avxcheck
	mov [rbx], rax
        leave
        ret
