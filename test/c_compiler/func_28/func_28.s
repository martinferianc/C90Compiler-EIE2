	.file	1 "func_28.c"
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
	beq	$2,$0,$L2
	nop

	lw	$2,36($fp)
	bne	$2,$0,$L3
	nop

$L2:
	li	$2,1			# 0x1
	b	$L4
	nop

$L3:
	lw	$2,32($fp)
	addiu	$3,$2,-1
	lw	$2,32($fp)
	addu	$3,$3,$2
	lw	$2,36($fp)
	addiu	$2,$2,-1
	move	$5,$2
	move	$4,$3
	.option	pic0
	jal	f
	nop

	.option	pic2
	addiu	$2,$2,1
$L4:
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
	li	$5,10			# 0xa
	li	$4,20			# 0x14
	.option	pic0
	jal	f
	nop

	.option	pic2
	move	$16,$2
	li	$5,1			# 0x1
	li	$4,1			# 0x1
	.option	pic0
	jal	f
	nop

	.option	pic2
	move	$5,$2
	move	$4,$16
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
