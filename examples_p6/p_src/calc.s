lexan:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$lexan.size, %esp
	movl	c, %eax
	cmpl	$0, %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	cmpl	$0, %eax
	je	.L1
	call	getchar
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax	# Assignment::generate
	movl	%eax, c
.L1:
.L2:
.L3:
	pushl	c
	call	isspace
	addl	$4, %esp
	movl	%eax, -20(%ebp)
movl	-20(%ebp),%eax
cmpl	$0,%eax
jne	.L4
	movl	c, %eax
	cmpl	LF, %eax
	setne	%al
	movzbl	%al, %eax
	movl	%eax, -24(%ebp)
movl	-24(%ebp),%eax
cmpl	$0,%eax
.L4:
	setne	%al
	movzbl	%al,%eax
	movl	%eax,-28(%ebp)
	movl	-28(%ebp), %eax
	cmpl	$0, %eax
	je	.L5
	call	getchar
	movl	%eax, -32(%ebp)
	movl	-32(%ebp), %eax	# Assignment::generate
	movl	%eax, c
	jmp	.L3
.L5:
	pushl	c
	call	isdigit
	addl	$4, %esp
	movl	%eax, -36(%ebp)
	movl	-36(%ebp), %eax
	cmpl	$0, %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, -40(%ebp)
	movl	-40(%ebp), %eax
	cmpl	$0, %eax
	je	.L6
	movl	c, %eax	# Assignment::generate
	movl	%eax, -8(%ebp)
	movl	$0, %eax	# Assignment::generate
	movl	%eax, c
	movl	-8(%ebp), %eax
	jmp	.L0
.L6:
.L7:
	movl	$0, %eax	# Assignment::generate
	movl	%eax, -4(%ebp)
.L8:
	pushl	c
	call	isdigit
	addl	$4, %esp
	movl	%eax, -44(%ebp)
	movl	-44(%ebp), %eax
	cmpl	$0, %eax
	je	.L9
	movl	-4(%ebp), %eax
	imull	$10, %eax
	movl	%eax, -48(%ebp)
	movl	-48(%ebp), %eax
	addl	c, %eax
	movl	%eax,-52(%ebp)
	movl	-52(%ebp), %eax
	subl	$48, %eax
	movl	%eax, -56(%ebp)
	movl	-56(%ebp), %eax	# Assignment::generate
	movl	%eax, -4(%ebp)
	pushl	c
	call	getchar
	addl	$4, %esp
	movl	%eax, -60(%ebp)
	movl	-60(%ebp), %eax	# Assignment::generate
	movl	%eax, c
	jmp	.L8
.L9:
	movl	-4(%ebp), %eax	# Assignment::generate
	movl	%eax, lexval
	movl	NUM, %eax
	jmp	.L0
.L0:
	movl	%ebp, %esp
	popl	%ebp
	ret

	.globl	lexan
	.set	lexan.size, 60

match:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$match.size, %esp
	movl	lookahead, %eax
	cmpl	8(%ebp), %eax
	setne	%al
	movzbl	%al, %eax
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	cmpl	$0, %eax
	je	.L11
	pushl	lookahead
	pushl	
	call	printf
	addl	$8, %esp
	movl	%eax, -8(%ebp)
	pushl	$1
	call	exit
	addl	$4, %esp
	movl	%eax, -12(%ebp)
.L11:
.L12:
	call	lexan
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax	# Assignment::generate
	movl	%eax, lookahead
.L10:
	movl	%ebp, %esp
	popl	%ebp
	ret

	.globl	match
	.set	match.size, 16

factor:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$factor.size, %esp
	movl	lookahead, %eax
	cmpl	LPAREN, %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	cmpl	$0, %eax
	je	.L14
	pushl	LPAREN
	call	match
	addl	$4, %esp
	movl	%eax, -12(%ebp)
	call	expr
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax	# Assignment::generate
	movl	%eax, -4(%ebp)
	pushl	RPAREN
	call	match
	addl	$4, %esp
	movl	%eax, -20(%ebp)
	movl	-4(%ebp), %eax
	jmp	.L13
.L14:
.L15:
	movl	lexval, %eax	# Assignment::generate
	movl	%eax, -4(%ebp)
	pushl	NUM
	call	match
	addl	$4, %esp
	movl	%eax, -24(%ebp)
	movl	-4(%ebp), %eax
	jmp	.L13
.L13:
	movl	%ebp, %esp
	popl	%ebp
	ret

	.globl	factor
	.set	factor.size, 24

term:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$term.size, %esp
	call	factor
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax	# Assignment::generate
	movl	%eax, -4(%ebp)
.L17:
	movl	lookahead, %eax
	cmpl	MUL, %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp),%eax
	cmpl	$0,%eax
	jne	.L18
	movl	lookahead, %eax
	cmpl	DIV, %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp),%eax
	cmpl	$0,%eax
.L18:
	setne	%al
	movzbl	%al,%eax
	movl	%eax,-20(%ebp)
	movl	-20(%ebp), %eax
	cmpl	$0, %eax
	je	.L19
	movl	lookahead, %eax
	cmpl	MUL, %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, -24(%ebp)
	movl	-24(%ebp), %eax
	cmpl	$0, %eax
	je	.L20
	pushl	MUL
	call	match
	addl	$4, %esp
	movl	%eax, -28(%ebp)
	call	factor
	movl	%eax, -32(%ebp)
	movl	-4(%ebp), %eax
	imull	-32(%ebp), %eax
	movl	%eax, -36(%ebp)
	movl	-36(%ebp), %eax	# Assignment::generate
	movl	%eax, -4(%ebp)
	jmp	.L21
.L20:
	pushl	DIV
	call	match
	addl	$4, %esp
	movl	%eax, -40(%ebp)
	call	factor
	movl	%eax, -44(%ebp)
	movl	-4(%ebp), %eax
	movl	-44(%ebp), %ecx
	cltd	
	idivl	%ecx
	movl	%eax, -48(%ebp)
	movl	-48(%ebp), %eax	# Assignment::generate
	movl	%eax, -4(%ebp)
.L21:
	jmp	.L17
.L19:
	movl	-4(%ebp), %eax
	jmp	.L16
.L16:
	movl	%ebp, %esp
	popl	%ebp
	ret

	.globl	term
	.set	term.size, 48

expr:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$expr.size, %esp
	call	term
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax	# Assignment::generate
	movl	%eax, -4(%ebp)
.L23:
	movl	lookahead, %eax
	cmpl	ADD, %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp),%eax
	cmpl	$0,%eax
	jne	.L24
	movl	lookahead, %eax
	cmpl	SUB, %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp),%eax
	cmpl	$0,%eax
.L24:
	setne	%al
	movzbl	%al,%eax
	movl	%eax,-20(%ebp)
	movl	-20(%ebp), %eax
	cmpl	$0, %eax
	je	.L25
	movl	lookahead, %eax
	cmpl	ADD, %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, -24(%ebp)
	movl	-24(%ebp), %eax
	cmpl	$0, %eax
	je	.L26
	pushl	ADD
	call	match
	addl	$4, %esp
	movl	%eax, -28(%ebp)
	call	term
	movl	%eax, -32(%ebp)
	movl	-4(%ebp), %eax
	addl	-32(%ebp), %eax
	movl	%eax,-36(%ebp)
	movl	-36(%ebp), %eax	# Assignment::generate
	movl	%eax, -4(%ebp)
	jmp	.L27
.L26:
	pushl	SUB
	call	match
	addl	$4, %esp
	movl	%eax, -40(%ebp)
	call	term
	movl	%eax, -44(%ebp)
	movl	-4(%ebp), %eax
	subl	-44(%ebp), %eax
	movl	%eax, -48(%ebp)
	movl	-48(%ebp), %eax	# Assignment::generate
	movl	%eax, -4(%ebp)
.L27:
	jmp	.L23
.L25:
	movl	-4(%ebp), %eax
	jmp	.L22
.L22:
	movl	%ebp, %esp
	popl	%ebp
	ret

	.globl	expr
	.set	expr.size, 48

main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$main.size, %esp
	movl	$10, %eax	# Assignment::generate
	movl	%eax, LF
	movl	$40, %eax	# Assignment::generate
	movl	%eax, LPAREN
	movl	$41, %eax	# Assignment::generate
	movl	%eax, RPAREN
	movl	$42, %eax	# Assignment::generate
	movl	%eax, MUL
	movl	$43, %eax	# Assignment::generate
	movl	%eax, ADD
	movl	$45, %eax	# Assignment::generate
	movl	%eax, SUB
	movl	$47, %eax	# Assignment::generate
	movl	%eax, DIV
	movl	$256, %eax	# Assignment::generate
	movl	%eax, NUM
	call	lexan
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax	# Assignment::generate
	movl	%eax, lookahead
.L29:
	movl	$1, %eax
	negl	%eax
	movl	%eax, -12(%ebp)
	movl	lookahead, %eax
	cmpl	-12(%ebp), %eax
	setne	%al
	movzbl	%al, %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	cmpl	$0, %eax
	je	.L30
	call	expr
	movl	%eax, -20(%ebp)
	movl	-20(%ebp), %eax	# Assignment::generate
	movl	%eax, -4(%ebp)
	pushl	-4(%ebp)
	pushl	
	call	printf
	addl	$8, %esp
	movl	%eax, -24(%ebp)
.L31:
	movl	lookahead, %eax
	cmpl	LF, %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, -28(%ebp)
	movl	-28(%ebp), %eax
	cmpl	$0, %eax
	je	.L32
	pushl	LF
	call	match
	addl	$4, %esp
	movl	%eax, -32(%ebp)
	jmp	.L31
.L32:
	jmp	.L29
.L30:
.L28:
	movl	%ebp, %esp
	popl	%ebp
	ret

	.globl	main
	.set	main.size, 32

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
