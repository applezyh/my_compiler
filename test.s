	.arch armv7-a
	.eabi_attribute 28, 1
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"test.c"
	.text
	.align	1
	.global	main
	.arch armv7-a
	.syntax unified
	.thumb
	.thumb_func
	.fpu vfpv3-d16
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	sub	sp, sp, #8
	add	r7, sp, #0
	movs	r3, #1
	str	r3, [r7, #4]
	ldr	r3, [r7, #4]
	cmp	r3, #1
	bne	.L2
	ldr	r3, [r7, #4]
	cmp	r3, #1
	beq	.L3
.L2:
	ldr	r3, [r7, #4]
	cmp	r3, #3
	bne	.L4
.L3:
	movs	r3, #3
	str	r3, [r7, #4]
.L4:
	ldr	r0, [r7, #4]
	bl	print(PLT)
	bl	newline(PLT)
	nop
	adds	r7, r7, #8
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	main, .-main
	.ident	"GCC: (Ubuntu 10.3.0-1ubuntu1) 10.3.0"
	.section	.note.GNU-stack,"",%progbits
