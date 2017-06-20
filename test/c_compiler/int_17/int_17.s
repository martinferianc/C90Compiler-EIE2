	.file	1 "int_17.c"
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
	lw	$2,0($fp)
	addiu	$2,$2,20
	lw	$3,4($fp)
	and	$2,$3,$2
	sw	$2,4($fp)
	lw	$2,4($fp)
	addiu	$3,$2,20
	lw	$2,4($fp)
	addu	$2,$3,$2
	lw	$3,4($fp)
	or	$2,$3,$2
	sw	$2,4($fp)
	lw	$2,4($fp)
	addiu	$2,$2,1
	sw	$2,4($fp)
	lw	$2,4($fp)
	addiu	$2,$2,1
	sw	$2,4($fp)
	lw	$2,4($fp)
	addiu	$2,$2,-1
	sw	$2,4($fp)
	lw	$2,4($fp)
	addiu	$2,$2,-1
	sw	$2,4($fp)
	lw	$2,4($fp)
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
