	.file	1 "func_30.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=xx
	.module	nooddspreg
	.abicalls

	.comm	i,4,4
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
	nop
	nop
	sw	$0,4($fp)
	b	$L2
	nop

$L3:
	lw	$2,4($fp)
	addiu	$2,$2,1
	sw	$2,4($fp)
$L2:
	lw	$2,4($fp)
	bltz	$2,$L3
	nop

	sw	$0,4($fp)
	b	$L4
	nop

$L5:
	lw	$2,4($fp)
	addiu	$2,$2,1
	sw	$2,4($fp)
$L4:
	lw	$2,4($fp)
	bltz	$2,$L5
	nop

	sw	$0,4($fp)
	b	$L6
	nop

$L7:
	lw	$2,4($fp)
	addiu	$2,$2,1
	sw	$2,4($fp)
$L6:
	lw	$2,4($fp)
	bltz	$2,$L7
	nop

	nop
	move	$2,$0
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
