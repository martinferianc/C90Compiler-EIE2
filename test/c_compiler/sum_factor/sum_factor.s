	.file	1 "sum_factor.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=xx
	.module	nooddspreg
	.abicalls
	.text
	.align	2
	.globl	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$fp,16,$31		# vars= 8, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-16
	sw	$fp,12($sp)
	move	$fp,$sp
	li	$2,7			# 0x7
	sw	$2,0($fp)
	lw	$3,0($fp)
	li	$2,715784192			# 0x2aaa0000
	ori	$2,$2,0xaaab
	mult	$3,$2
	mfhi	$4
	sra	$2,$3,31
	subu	$2,$4,$2
	move	$4,$2
	sll	$2,$4,1
	move	$4,$2
	sll	$2,$4,2
	subu	$2,$2,$4
	subu	$2,$3,$2
	sw	$2,4($fp)
	lw	$2,0($fp)
	move	$sp,$fp
	lw	$fp,12($sp)
	addiu	$sp,$sp,16
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.1) 5.4.0 20160609"
