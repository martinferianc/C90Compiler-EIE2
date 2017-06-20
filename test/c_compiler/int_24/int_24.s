	.file	1 "int_24.c"
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
	.frame	$fp,32,$31		# vars= 24, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-32
	sw	$fp,28($sp)
	move	$fp,$sp
	li	$2,120			# 0x78
	sw	$2,4($fp)
	li	$2,213			# 0xd5
	sw	$2,8($fp)
	lw	$3,4($fp)
	lw	$2,8($fp)
	bne	$3,$2,$L2
	nop

	lw	$3,4($fp)
	lw	$2,8($fp)
	beq	$3,$2,$L3
	nop

$L2:
	li	$2,1			# 0x1
	b	$L4
	nop

$L3:
	move	$2,$0
$L4:
	sw	$2,12($fp)
	sw	$0,16($fp)
	lw	$2,16($fp)
	bne	$2,$0,$L5
	nop

	lw	$2,12($fp)
	bne	$2,$0,$L5
	nop

	lw	$2,4($fp)
	beq	$2,$0,$L6
	nop

$L5:
	li	$2,1			# 0x1
	b	$L7
	nop

$L6:
	move	$2,$0
$L7:
	sw	$2,20($fp)
	lw	$2,20($fp)
	move	$sp,$fp
	lw	$fp,28($sp)
	addiu	$sp,$sp,32
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.1) 5.4.0 20160609"
