	.file	1 "leap_year.c"
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
	li	$2,120			# 0x78
	sw	$2,4($fp)
	lw	$2,4($fp)
	andi	$2,$2,0x3
	bne	$2,$0,$L2
	nop

	lw	$3,4($fp)
	li	$2,1374355456			# 0x51eb0000
	ori	$2,$2,0x851f
	mult	$3,$2
	mfhi	$2
	sra	$4,$2,5
	sra	$2,$3,31
	subu	$2,$4,$2
	sll	$2,$2,2
	sll	$4,$2,2
	addu	$2,$2,$4
	sll	$4,$2,2
	addu	$2,$2,$4
	subu	$2,$3,$2
	bne	$2,$0,$L3
	nop

	lw	$3,4($fp)
	li	$2,1374355456			# 0x51eb0000
	ori	$2,$2,0x851f
	mult	$3,$2
	mfhi	$2
	sra	$4,$2,7
	sra	$2,$3,31
	subu	$2,$4,$2
	sll	$2,$2,4
	sll	$4,$2,2
	addu	$2,$2,$4
	sll	$4,$2,2
	addu	$2,$2,$4
	subu	$2,$3,$2
	bne	$2,$0,$L4
	nop

	li	$2,1			# 0x1
	b	$L5
	nop

$L4:
	move	$2,$0
	b	$L5
	nop

$L3:
	li	$2,1			# 0x1
	b	$L5
	nop

$L2:
	move	$2,$0
$L5:
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
