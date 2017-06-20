	.file	1 "int_5.c"
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
	li	$2,10			# 0xa
	sw	$2,0($fp)
	li	$2,2			# 0x2
	sw	$2,4($fp)
	lw	$3,4($fp)
	lw	$2,0($fp)
	addu	$2,$3,$2
	sll	$2,$2,9
	sll	$2,$2,2
	sll	$3,$2,2
	addu	$2,$2,$3
	sw	$2,4($fp)
	lw	$3,4($fp)
	lw	$2,0($fp)
	addu	$2,$3,$2
	sra	$2,$2,3
	li	$3,-1840709632			# 0xffffffff92490000
	ori	$3,$3,0x2493
	mult	$2,$3
	mfhi	$3
	addu	$3,$3,$2
	sra	$3,$3,2
	sra	$2,$2,31
	subu	$2,$3,$2
	sw	$2,4($fp)
	lw	$2,4($fp)
	andi	$2,$2,0x4
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
