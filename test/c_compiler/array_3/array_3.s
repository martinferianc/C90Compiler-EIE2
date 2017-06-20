	.file	1 "array_3.c"
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
	.frame	$fp,64,$31		# vars= 32, regs= 2/0, args= 16, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-64
	sw	$31,60($sp)
	sw	$fp,56($sp)
	move	$fp,$sp
	lui	$28,%hi(__gnu_local_gp)
	addiu	$28,$28,%lo(__gnu_local_gp)
	.cprestore	16
	lw	$2,%got(__stack_chk_guard)($28)
	lw	$2,0($2)
	sw	$2,52($fp)
	li	$2,2			# 0x2
	sw	$2,32($fp)
	li	$2,-2			# 0xfffffffffffffffe
	sw	$2,36($fp)
	li	$2,7			# 0x7
	sw	$2,44($fp)
	li	$2,8			# 0x8
	sw	$2,48($fp)
	li	$2,9			# 0x9
	sw	$2,40($fp)
	li	$2,1			# 0x1
	sw	$2,28($fp)
	b	$L2
	nop

$L4:
	lw	$3,32($fp)
	lw	$2,28($fp)
	sll	$2,$2,2
	addiu	$4,$fp,56
	addu	$2,$4,$2
	lw	$2,-24($2)
	slt	$2,$3,$2
	beq	$2,$0,$L3
	nop

	lw	$2,28($fp)
	sll	$2,$2,2
	addiu	$3,$fp,56
	addu	$2,$3,$2
	lw	$2,-24($2)
	sw	$2,32($fp)
$L3:
	lw	$2,28($fp)
	addiu	$2,$2,1
	sw	$2,28($fp)
$L2:
	lw	$2,28($fp)
	slt	$2,$2,5
	bne	$2,$0,$L4
	nop

	lw	$2,32($fp)
	lw	$3,%got(__stack_chk_guard)($28)
	lw	$4,52($fp)
	lw	$3,0($3)
	beq	$4,$3,$L6
	nop

	lw	$2,%call16(__stack_chk_fail)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,__stack_chk_fail
1:	jalr	$25
	nop

$L6:
	move	$sp,$fp
	lw	$31,60($sp)
	lw	$fp,56($sp)
	addiu	$sp,$sp,64
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.1) 5.4.0 20160609"
