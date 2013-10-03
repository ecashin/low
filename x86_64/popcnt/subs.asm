;;; Try out the popcnt instruction
;;; and provide cpuid so they can see whether the CPU supports it.
;;; 
;;; The caller is responsible for aligning data and providing a
;;; byte count that's evenly divisible by 8.

%define CPUID_POPCNT_BIT 1 << 23
%define CPUID_SSE4_2_BIT 1 << 20

section .text
	global canpopcnt
	global countbits

countbits:
	push rbp
	mov rbp, rsp
	mov rcx, rsi	; rcx is the count ...
	shr rcx, 3	; ... of quadwords remaining to examine.
	mov rdx, 0	; rdx is bit count
	jrcxz .end	; don't start the loop if count is zero
.loop:
	popcnt rbx, [rdi]	; rdi is still the source address
	add rdx, rbx
	add rdi, 8
	loop .loop		; decrement rcx, goto .loop if non-zero
.end:
	mov rax, rdx
	leave
	ret

canpopcnt:
	push rbp
        mov rbp, rsp
        mov rax, 1
        cpuid
	mov rax, CPUID_SSE4_2_BIT
	or rax, CPUID_POPCNT_BIT
	and rcx, rax		; clear bits in rcx other than those of interest
	cmp rax, rcx
	je .fine
	mov rax, 0
.fine:
        leave
        ret
