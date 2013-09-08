;;; make 
;;; nasm -Dbigimm=_bigimm -fmacho64 subs.asm
;;; subs.asm:9: warning: signed dword immediate exceeds bounds
;;; cc  -o bigimm  subs.o main.o 
;;; ./bigimm
;;; got 0x65, expected 0x100000065

section .text
	global bigimm

bigimm:
	push rbp
        mov rbp, rsp
	mov rax, rdi
	add rax, 4294967396
        leave
        ret
