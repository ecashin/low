;;; The Intel Software Developer's Manual makes it sound like
;;; you can't use the old high-byte registers like ah, bh, ...
;;; when in 64-bit mode.  It sounds like they silently become
;;; al, bl, ..., which would be awful.  Really, it just seems
;;; to mean that you can't use r0h, for example.
;;;
;;; This experiment is named in honor of Hilo, Hawaii, as well
;;; as the high and low bytes of the general purpose regs.  ;)

section .text
	global hilo

hilo:				; return old high rdi OR old low rsi
	push rbp
        mov rbp, rsp
	mov qword [rbp-8], 0
	mov qword [rbp-16], 0
	mov rbx, rdi
        mov [rbp-8], bh	; see 3.4.1 in "Basic Execution Environment"
	mov [rbp-16], bl
	mov rax, [rbp-8]
	or rax, [rbp-16]
        leave
        ret
