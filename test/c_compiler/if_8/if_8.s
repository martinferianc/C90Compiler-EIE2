	.file	1 "if_8.c"
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
	lw	$3,0($fp)
	li	$2,20			# 0x14
	bne	$3,$2,$L2
	nop

	li	$2,7			# 0x7
	b	$L3
	nop

$L2:
	lw	$2,0($fp)
	slt	$2,$2,11
	beq	$2,$0,$L4
	nop

	lw	$2,0($fp)
	slt	$2,$2,8
	bne	$2,$0,$L5
	nop

	li	$2,5			# 0x5
	b	$L3
	nop

$L5:
	li	$2,9			# 0x9
	b	$L3
	nop

$L4:
	move	$2,$0
$L3:
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
