
section .text
	global cpuidfn
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

cpuidfn:
	push rbp
        mov rbp, rsp
        mov rax, rdi
        cpuid
	mov rax, rcx
        leave
        ret
