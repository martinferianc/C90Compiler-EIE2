	.file	1 "switch_3.c"
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
	li	$2,66			# 0x42
	sb	$2,7($fp)
	li	$2,20			# 0x14
	sw	$2,8($fp)
	lw	$2,8($fp)
	li	$3,2			# 0x2
	beq	$2,$3,$L3
	nop

	li	$3,20			# 0x14
	beq	$2,$3,$L4
	nop

	li	$3,1			# 0x1
	bne	$2,$3,$L8
	nop

	li	$2,1			# 0x1
	sw	$2,8($fp)
$L3:
	li	$2,67			# 0x43
	sb	$2,7($fp)
	li	$2,68			# 0x44
	sb	$2,7($fp)
$L4:
	li	$2,5			# 0x5
	sw	$2,8($fp)
	li	$2,112			# 0x70
	sb	$2,7($fp)
	b	$L6
	nop

$L8:
	li	$2,7			# 0x7
	sw	$2,12($fp)
	nop
$L6:
	lb	$3,7($fp)
	lw	$2,8($fp)
	addu	$2,$3,$2
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
