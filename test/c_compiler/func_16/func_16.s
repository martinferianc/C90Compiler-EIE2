	.file	1 "func_16.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=xx
	.module	nooddspreg
	.abicalls
	.text
	.align	2
	.globl	d
	.set	nomips16
	.set	nomicromips
	.ent	d
	.type	d, @function
d:
	.frame	$fp,32,$31		# vars= 0, regs= 2/0, args= 16, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$fp,24($sp)
	move	$fp,$sp
	sw	$4,32($fp)
	sw	$5,36($fp)
	lw	$2,32($fp)
	slt	$2,$2,2
	beq	$2,$0,$L2
	nop

	li	$2,1			# 0x1
	b	$L3
	nop

$L2:
	lw	$2,32($fp)
	addiu	$2,$2,-1
	lw	$5,36($fp)
	move	$4,$2
	.option	pic0
	jal	d
	nop

	.option	pic2
$L3:
	move	$sp,$fp
	lw	$31,28($sp)
	lw	$fp,24($sp)
	addiu	$sp,$sp,32
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	d
	.size	d, .-d
	.align	2
	.globl	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$fp,40,$31		# vars= 8, regs= 2/0, args= 16, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-40
	sw	$31,36($sp)
	sw	$fp,32($sp)
	move	$fp,$sp
	li	$2,200			# 0xc8
	sw	$2,28($fp)
	li	$5,5			# 0x5
	li	$4,144			# 0x90
	.option	pic0
	jal	d
	nop

	.option	pic2
	move	$sp,$fp
	lw	$31,36($sp)
	lw	$fp,32($sp)
	addiu	$sp,$sp,40
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.1) 5.4.0 20160609"
