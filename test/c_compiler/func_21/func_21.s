	.file	1 "func_21.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=xx
	.module	nooddspreg
	.abicalls
	.text
	.align	2
	.globl	l
	.set	nomips16
	.set	nomicromips
	.ent	l
	.type	l, @function
l:
	.frame	$fp,8,$31		# vars= 0, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-8
	sw	$fp,4($sp)
	move	$fp,$sp
	li	$2,12			# 0xc
	move	$sp,$fp
	lw	$fp,4($sp)
	addiu	$sp,$sp,8
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	l
	.size	l, .-l
	.align	2
	.globl	f
	.set	nomips16
	.set	nomicromips
	.ent	f
	.type	f, @function
f:
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
	lw	$2,32($fp)
	slt	$2,$2,15
	beq	$2,$0,$L4
	nop

	li	$2,1			# 0x1
	b	$L5
	nop

$L4:
	.option	pic0
	jal	l
	nop

	.option	pic2
	addiu	$2,$2,10
$L5:
	move	$sp,$fp
	lw	$31,28($sp)
	lw	$fp,24($sp)
	addiu	$sp,$sp,32
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	f
	.size	f, .-f
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
	sw	$0,28($fp)
	b	$L7
	nop

$L10:
	lw	$4,28($fp)
	.option	pic0
	jal	f
	nop

	.option	pic2
	move	$3,$2
	lw	$2,28($fp)
	addu	$2,$2,$3
	sw	$2,28($fp)
	b	$L8
	nop

$L9:
	lw	$2,28($fp)
	addiu	$2,$2,1
	sw	$2,28($fp)
$L8:
	lw	$2,28($fp)
	slt	$2,$2,20
	bne	$2,$0,$L9
	nop

	lw	$2,28($fp)
	addiu	$2,$2,1
	sw	$2,28($fp)
$L7:
	lw	$2,28($fp)
	slt	$2,$2,123
	bne	$2,$0,$L10
	nop

	lw	$2,28($fp)
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
