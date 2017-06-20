	.file	1 "array_4.c"
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
	.frame	$fp,72,$31		# vars= 40, regs= 2/0, args= 16, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-72
	sw	$31,68($sp)
	sw	$fp,64($sp)
	move	$fp,$sp
	lui	$28,%hi(__gnu_local_gp)
	addiu	$28,$28,%lo(__gnu_local_gp)
	.cprestore	16
	lw	$2,%got(__stack_chk_guard)($28)
	lw	$2,0($2)
	sw	$2,60($fp)
	li	$2,2			# 0x2
	sw	$2,40($fp)
	li	$2,-2			# 0xfffffffffffffffe
	sw	$2,44($fp)
	li	$2,7			# 0x7
	sw	$2,52($fp)
	li	$2,8			# 0x8
	sw	$2,56($fp)
	li	$2,9			# 0x9
	sw	$2,48($fp)
	sw	$0,28($fp)
	b	$L2
	nop

$L6:
	sw	$0,32($fp)
	b	$L3
	nop

$L5:
	lw	$2,32($fp)
	sll	$2,$2,2
	addiu	$3,$fp,64
	addu	$2,$3,$2
	lw	$3,-24($2)
	lw	$2,32($fp)
	addiu	$2,$2,1
	sll	$2,$2,2
	addiu	$4,$fp,64
	addu	$2,$4,$2
	lw	$2,-24($2)
	slt	$2,$2,$3
	beq	$2,$0,$L4
	nop

	lw	$2,32($fp)
	addiu	$2,$2,1
	sll	$2,$2,2
	addiu	$3,$fp,64
	addu	$2,$3,$2
	lw	$2,-24($2)
	sw	$2,36($fp)
	lw	$2,32($fp)
	addiu	$4,$2,1
	lw	$2,32($fp)
	sll	$2,$2,2
	addiu	$3,$fp,64
	addu	$2,$3,$2
	lw	$3,-24($2)
	sll	$2,$4,2
	addiu	$4,$fp,64
	addu	$2,$4,$2
	sw	$3,-24($2)
	lw	$2,32($fp)
	sll	$2,$2,2
	addiu	$3,$fp,64
	addu	$2,$3,$2
	lw	$3,36($fp)
	sw	$3,-24($2)
$L4:
	lw	$2,32($fp)
	addiu	$2,$2,1
	sw	$2,32($fp)
$L3:
	li	$3,4			# 0x4
	lw	$2,28($fp)
	subu	$3,$3,$2
	lw	$2,32($fp)
	slt	$2,$2,$3
	bne	$2,$0,$L5
	nop

	lw	$2,28($fp)
	addiu	$2,$2,1
	sw	$2,28($fp)
$L2:
	lw	$2,28($fp)
	slt	$2,$2,4
	bne	$2,$0,$L6
	nop

	lw	$2,44($fp)
	lw	$3,%got(__stack_chk_guard)($28)
	lw	$4,60($fp)
	lw	$3,0($3)
	beq	$4,$3,$L8
	nop

	lw	$2,%call16(__stack_chk_fail)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,__stack_chk_fail
1:	jalr	$25
	nop

$L8:
	move	$sp,$fp
	lw	$31,68($sp)
	lw	$fp,64($sp)
	addiu	$sp,$sp,72
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.1) 5.4.0 20160609"
