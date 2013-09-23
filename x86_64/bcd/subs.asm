
section .text
	global bcddemo

bcddemo:
	push rbp
        mov rbp, rsp
	fbld [rdi]
	fbld [rsi]
	faddp
	fbstp [rdi]
        leave
        ret
