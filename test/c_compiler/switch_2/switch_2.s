	.file	1 "switch_2.c"
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
	li	$2,66			# 0x42
	sb	$2,3($fp)
	lb	$2,3($fp)
	li	$3,66			# 0x42
	beq	$2,$3,$L3
	nop

	li	$3,67			# 0x43
	beq	$2,$3,$L4
	nop

	li	$3,65			# 0x41
	bne	$2,$3,$L8
	nop

	li	$2,1			# 0x1
	sw	$2,4($fp)
	b	$L6
	nop

$L3:
	li	$2,99			# 0x63
	sb	$2,3($fp)
	b	$L6
	nop

$L4:
	li	$2,5			# 0x5
	sw	$2,4($fp)
	b	$L6
	nop

$L8:
	li	$2,6			# 0x6
	sw	$2,4($fp)
	nop
$L6:
	lb	$2,3($fp)
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
