	.file	1 "gcd.c"
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
	li	$2,40			# 0x28
	sw	$2,8($fp)
	li	$2,50			# 0x32
	sw	$2,12($fp)
	li	$2,1			# 0x1
	sw	$2,0($fp)
	b	$L2
	nop

$L5:
	lw	$3,8($fp)
	lw	$2,0($fp)
	teq	$2,$0,7
	div	$0,$3,$2
	mfhi	$2
	bne	$2,$0,$L3
	nop

	lw	$3,12($fp)
	lw	$2,0($fp)
	teq	$2,$0,7
	div	$0,$3,$2
	mfhi	$2
	bne	$2,$0,$L3
	nop

	lw	$2,0($fp)
	sw	$2,4($fp)
$L3:
	lw	$2,0($fp)
	addiu	$2,$2,1
	sw	$2,0($fp)
$L2:
	lw	$3,0($fp)
	lw	$2,8($fp)
	slt	$2,$2,$3
	bne	$2,$0,$L4
	nop

	lw	$3,0($fp)
	lw	$2,12($fp)
	slt	$2,$2,$3
	beq	$2,$0,$L5
	nop

$L4:
	lw	$2,4($fp)
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
