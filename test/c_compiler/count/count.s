	.file	1 "count.c"
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
	sw	$0,4($fp)
	li	$2,1204			# 0x4b4
	sw	$2,0($fp)
	b	$L2
	nop

$L3:
	lw	$2,0($fp)
	li	$3,1717960704			# 0x66660000
	ori	$3,$3,0x6667
	mult	$2,$3
	mfhi	$3
	sra	$3,$3,2
	sra	$2,$2,31
	subu	$2,$3,$2
	sw	$2,0($fp)
	lw	$2,4($fp)
	addiu	$2,$2,1
	sw	$2,4($fp)
$L2:
	lw	$2,0($fp)
	bne	$2,$0,$L3
	nop

	lw	$2,4($fp)
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
