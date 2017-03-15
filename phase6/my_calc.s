lexan:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$lexan.size, %esp
	movl	$0, %eax
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	%eax, lexval
	movl	%ebp, %esp
	popl	%ebp
	ret

	.globl	lexan
	.set	lexan.size, 8

match:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$match.size, %esp
	call	lexan
	movl	, %eax
	movl	%eax, lookahead
	movl	%ebp, %esp
	popl	%ebp
	ret

	.globl	match
	.set	match.size, 0

factor:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$factor.size, %esp
	movl	lexval, %eax
	movl	%eax, -4(%ebp)
	pushl	NUM
	call	match
	addl	$4, %esp
	movl	%ebp, %esp
	popl	%ebp
	ret

	.globl	factor
	.set	factor.size, 4

term:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$term.size, %esp
	call	factor
	movl	, %eax
	movl	%eax, -4(%ebp)
	movl	%ebp, %esp
	popl	%ebp
	ret

	.globl	term
	.set	term.size, 4

expr:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$expr.size, %esp
	call	term
	movl	, %eax
	movl	%eax, -4(%ebp)
	movl	%ebp, %esp
	popl	%ebp
	ret

	.globl	expr
	.set	expr.size, 4

main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$main.size, %esp
	movl	$10, %eax
	movl	%eax, LF
	movl	$40, %eax
	movl	%eax, LPAREN
	movl	$41, %eax
	movl	%eax, RPAREN
	movl	$42, %eax
	movl	%eax, MUL
	movl	$43, %eax
	movl	%eax, ADD
	movl	$45, %eax
	movl	%eax, SUB
	movl	$47, %eax
	movl	%eax, DIV
	movl	$256, %eax
	movl	%eax, NUM
	call	lexan
	movl	, %eax
	movl	%eax, lookahead
	movl	%ebp, %esp
	popl	%ebp
	ret

	.globl	main
	.set	main.size, 4

	.data
	.comm	ADD, 4, 4
	.comm	SUB, 4, 4
	.comm	MUL, 4, 4
	.comm	DIV, 4, 4
	.comm	NUM, 4, 4
	.comm	LF, 4, 4
	.comm	LPAREN, 4, 4
	.comm	RPAREN, 4, 4
	.comm	lookahead, 4, 4
	.comm	c, 4, 4
	.comm	lexval, 4, 4
