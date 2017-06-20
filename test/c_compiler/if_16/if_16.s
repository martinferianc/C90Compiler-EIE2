	.file	1 "if_16.c"
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
	.frame	$fp,24,$31		# vars= 16, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$fp,20($sp)
	move	$fp,$sp
	li	$2,6			# 0x6
	sw	$2,4($fp)
	li	$2,7			# 0x7
	sw	$2,8($fp)
	li	$2,20			# 0x14
	sw	$2,12($fp)
	lw	$2,4($fp)
	beq	$2,$0,$L2
	nop

	lw	$2,8($fp)
	bne	$2,$0,$L3
	nop

$L2:
	lw	$2,12($fp)
	beq	$2,$0,$L4
	nop

$L3:
	lw	$2,4($fp)
	beq	$2,$0,$L5
	nop

	lw	$2,12($fp)
	beq	$2,$0,$L5
	nop

	li	$2,1			# 0x1
	b	$L7
	nop

$L5:
	move	$2,$0
	b	$L7
	nop

$L4:
	move	$2,$0
$L7:
	move	$sp,$fp
	lw	$fp,20($sp)
	addiu	$sp,$sp,24
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.1) 5.4.0 20160609"
