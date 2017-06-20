	.file	1 "func_29.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=xx
	.module	nooddspreg
	.abicalls
	.text
	.align	2
	.globl	f
	.set	nomips16
	.set	nomicromips
	.ent	f
	.type	f, @function
f:
	.frame	$fp,40,$31		# vars= 0, regs= 3/0, args= 16, gp= 8
	.mask	0xc0010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-40
	sw	$31,36($sp)
	sw	$fp,32($sp)
	sw	$16,28($sp)
	move	$fp,$sp
	sw	$4,40($fp)
	sw	$5,44($fp)
	lw	$2,40($fp)
	beq	$2,$0,$L2
	nop

	lw	$2,44($fp)
	bne	$2,$0,$L3
	nop

$L2:
	li	$2,1			# 0x1
	b	$L4
	nop

$L3:
	lw	$2,40($fp)
	addiu	$3,$2,-1
	lw	$2,40($fp)
	addu	$3,$3,$2
	lw	$2,44($fp)
	addiu	$2,$2,-1
	move	$5,$2
	move	$4,$3
	.option	pic0
	jal	f
	nop

	.option	pic2
	addiu	$16,$2,1
	lw	$4,40($fp)
	.option	pic0
	jal	g
	nop

	.option	pic2
	addu	$2,$16,$2
$L4:
	move	$sp,$fp
	lw	$31,36($sp)
	lw	$fp,32($sp)
	lw	$16,28($sp)
	addiu	$sp,$sp,40
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	f
	.size	f, .-f
	.align	2
	.globl	g
	.set	nomips16
	.set	nomicromips
	.ent	g
	.type	g, @function
g:
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
	.option	pic0
	jal	l
	nop

	.option	pic2
	move	$3,$2
	lw	$2,32($fp)
	addu	$2,$3,$2
	move	$sp,$fp
	lw	$31,28($sp)
	lw	$fp,24($sp)
	addiu	$sp,$sp,32
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	g
	.size	g, .-g
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
	li	$2,7			# 0x7
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
	.globl	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$fp,48,$31		# vars= 8, regs= 3/0, args= 16, gp= 8
	.mask	0xc0010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-48
	sw	$31,44($sp)
	sw	$fp,40($sp)
	sw	$16,36($sp)
	move	$fp,$sp
	li	$5,3			# 0x3
	li	$4,2			# 0x2
	.option	pic0
	jal	f
	nop

	.option	pic2
	move	$16,$2
	li	$5,2			# 0x2
	li	$4,1			# 0x1
	.option	pic0
	jal	f
	nop

	.option	pic2
	addu	$2,$16,$2
	sw	$2,28($fp)
	lw	$2,28($fp)
	move	$sp,$fp
	lw	$31,44($sp)
	lw	$fp,40($sp)
	lw	$16,36($sp)
	addiu	$sp,$sp,48
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.1) 5.4.0 20160609"
