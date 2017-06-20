	.file	1 "for_3.c"
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
	sw	$0,0($fp)
	b	$L2
	nop

$L5:
	lw	$3,0($fp)
	li	$2,7			# 0x7
	beq	$3,$2,$L3
	nop

	lw	$2,0($fp)
	b	$L4
	nop

$L3:
	li	$2,1234			# 0x4d2
	sw	$2,4($fp)
	lw	$2,0($fp)
	addiu	$2,$2,1
	sw	$2,0($fp)
$L2:
	lw	$2,0($fp)
	slt	$2,$2,120
	bne	$2,$0,$L5
	nop

	lw	$2,4($fp)
$L4:
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
