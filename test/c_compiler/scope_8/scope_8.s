	.file	1 "scope_8.c"
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
	lui	$28,%hi(__gnu_local_gp)
	addiu	$28,$28,%lo(__gnu_local_gp)
	li	$2,10			# 0xa
	sw	$2,0($fp)
	lw	$2,%got(i)($28)
	li	$3,5			# 0x5
	sw	$3,0($2)
	lw	$2,%got(i)($28)
	lw	$3,0($2)
	li	$2,5			# 0x5
	bne	$3,$2,$L2
	nop

	li	$2,20			# 0x14
	sw	$2,4($fp)
$L2:
	lw	$2,%got(i)($28)
	lw	$3,0($2)
	lw	$2,0($fp)
	addu	$2,$3,$2
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
