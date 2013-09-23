	.text
	.align	2
	.global	clz
	.type	clz, %function
clz:
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	str	r0, [fp, #-8]
	ldr	r3, [fp, #-8]
	clz	r0, r3
	add	sp, fp, #0
	ldmfd	sp!, {fp}
	bx	lr
	.size	clz, .-clz
