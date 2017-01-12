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
	.file	"plus_grand_affichage.c"
	.section	.rodata
	.align	2
.LC0:
	.ascii	"Votre chiffre est plus grand.\000"
	.text
	.align	2
	.global	s_plus
	.type	s_plus, %function
s_plus:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	ldr	r0, .L2
	bl	puts
	ldmfd	sp!, {fp, pc}
.L3:
	.align	2
.L2:
	.word	.LC0
	.size	s_plus, .-s_plus
	.section	.rodata
	.align	2
.LC1:
	.ascii	"Votre chiffre est plus petit.\000"
	.text
	.align	2
	.global	s_moins
	.type	s_moins, %function
s_moins:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	ldr	r0, .L5
	bl	puts
	ldmfd	sp!, {fp, pc}
.L6:
	.align	2
.L5:
	.word	.LC1
	.size	s_moins, .-s_moins
	.section	.rodata
	.align	2
.LC2:
	.ascii	"Bravo, vous avez trouv\303\251 !\000"
	.text
	.align	2
	.global	s_egal
	.type	s_egal, %function
s_egal:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	ldr	r0, .L8
	bl	puts
	ldmfd	sp!, {fp, pc}
.L9:
	.align	2
.L8:
	.word	.LC2
	.size	s_egal, .-s_egal
	.section	.rodata
	.align	2
.LC3:
	.ascii	"Un chiffre \303\240 \303\251t\303\251 choisis entre"
	.ascii	" 0 et 99.\000"
	.text
	.align	2
	.global	s_start
	.type	s_start, %function
s_start:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	ldr	r0, .L11
	bl	puts
	ldmfd	sp!, {fp, pc}
.L12:
	.align	2
.L11:
	.word	.LC3
	.size	s_start, .-s_start
	.section	.rodata
	.align	2
.LC4:
	.ascii	"Tapez un chiffre puis appuyez sur Entr\303\251e :\000"
	.text
	.align	2
	.global	s_boucle
	.type	s_boucle, %function
s_boucle:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	ldr	r0, .L14
	bl	puts
	ldmfd	sp!, {fp, pc}
.L15:
	.align	2
.L14:
	.word	.LC4
	.size	s_boucle, .-s_boucle
	.ident	"GCC: (15:4.9.3+svn231177-1) 4.9.3 20150529 (prerelease)"
