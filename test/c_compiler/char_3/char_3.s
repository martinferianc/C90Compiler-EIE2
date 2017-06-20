	.file	1 "char_3.c"
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
	li	$2,100			# 0x64
	sb	$2,6($fp)
	lb	$2,6($fp)
	sll	$2,$2,3
	sb	$2,6($fp)
	li	$2,115			# 0x73
	sb	$2,7($fp)
	lbu	$3,7($fp)
	lbu	$2,6($fp)
	addu	$2,$3,$2
	andi	$2,$2,0x00ff
	sb	$2,6($fp)
	lb	$2,6($fp)
	addiu	$2,$2,1
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
