
section .text
	global cpuidfn
	global countbits

countbits:
	push rbp
	mov rbp, rsp
	mov rcx, rdi	; rcx will hold address
	mov rdx, 0	; rdx is bit count
.loop:
	cmp rsi, 0
	je .end
	popcnt rbx, [rcx]
	add rdx, rbx
	add rcx, 8
	add esi, -8
	jmp .loop
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
