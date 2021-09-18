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
	.file	"print.c"
	.text
	.section	.rodata
	.align	2
.LC0:
	.ascii	"%d\000"
	.text
	.align	1
	.global	print_f
	.syntax unified
	.thumb
	.thumb_func
	.fpu vfpv3-d16
	.type	print_f, %function
print_f:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	sub	sp, sp, #8
	add	r7, sp, #0
	str	r0, [r7, #4]
	ldr	r1, [r7, #4]
	ldr	r3, .L2
.LPIC0:
	add	r3, pc
	mov	r0, r3
	bl	printf(PLT)
	nop
	adds	r7, r7, #8
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
.L3:
	.align	2
.L2:
	.word	.LC0-(.LPIC0+4)
	.size	print_f, .-print_f
	.align	1
	.global	print
	.syntax unified
	.thumb
	.thumb_func
	.fpu vfpv3-d16
	.type	print, %function
print:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	ldr r0, [sp, #0]
	push	{lr}
	bl	print_f(PLT)
	nop
	pop {pc}
	@ sp needed
	.size	print, .-print
	.align	1
	.global	newline
	.syntax unified
	.thumb
	.thumb_func
	.fpu vfpv3-d16
	.type	newline, %function
newline:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{lr}
	movs	r0, #10
	bl	putchar(PLT)
	nop
	@ sp needed
	pop	{pc}
	.size	newline, .-newline
	.ident	"GCC: (Ubuntu/Linaro 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",%progbits
