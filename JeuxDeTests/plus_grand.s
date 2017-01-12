	.cpu arm7tdmi
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"plus_grand.c"
	.text
	.align	2
	.global	is_equal
	.type	is_equal, %function
is_equal:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	str	r0, [fp, #-8]
	str	r1, [fp, #-12]
	ldr	r2, [fp, #-8]
	ldr	r3, [fp, #-12]
	cmp	r2, r3
	moveq	r3, #1
	movne	r3, #0
	and	r3, r3, #255
	mov	r0, r3
	sub	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	is_equal, .-is_equal
	.section	.rodata
	.align	2
.LC0:
	.ascii	"%i\000"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #16
	str	r0, [fp, #-16]
	str	r1, [fp, #-20]
	mov	r0, #0
	bl	time
	mov	r3, r0
	mov	r0, r3
	bl	srand
	bl	rand
	mov	r2, r0
	ldr	r3, .L8
	smull	r1, r3, r2, r3
	mov	r1, r3, asr #5
	mov	r3, r2, asr #31
	rsb	r1, r3, r1
	mov	r3, r1
	mov	r3, r3, asl #2
	add	r3, r3, r1
	mov	r1, r3, asl #2
	add	r3, r3, r1
	mov	r3, r3, asl #2
	rsb	r3, r3, r2
	str	r3, [fp, #-8]
	mvn	r3, #0
	str	r3, [fp, #-12]
	bl	s_start
	b	.L4
.L7:
	bl	s_boucle
	sub	r3, fp, #12
	ldr	r0, .L8+4
	mov	r1, r3
	bl	scanf
	ldr	r3, [fp, #-12]
	ldr	r0, [fp, #-8]
	mov	r1, r3
	bl	is_equal
	mov	r3, r0
	cmp	r3, #0
	beq	.L5
	bl	s_egal
	b	.L4
.L5:
	ldr	r3, [fp, #-12]
	ldr	r2, [fp, #-8]
	cmp	r2, r3
	bge	.L6
	bl	s_plus
	b	.L4
.L6:
	ldr	r3, [fp, #-12]
	ldr	r2, [fp, #-8]
	cmp	r2, r3
	ble	.L4
	bl	s_moins
.L4:
	ldr	r3, [fp, #-12]
	ldr	r2, [fp, #-8]
	cmp	r2, r3
	bne	.L7
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L9:
	.align	2
.L8:
	.word	1374389535
	.word	.LC0
	.size	main, .-main
	.ident	"GCC: (15:4.9.3+svn231177-1) 4.9.3 20150529 (prerelease)"
