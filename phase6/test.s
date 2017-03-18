main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$main.size, %esp
	movl	$1, %eax	# Assignment::generate
	movl	%eax, -4(%ebp)
	movl	$0, %eax	# Assignment::generate
	movl	%eax, -8(%ebp)
	movl	-8(%ebp),%eax
	cmpl	$0,%eax
	jne	.L0
	movl	-4(%ebp),%eax
	cmpl	$0,%eax
.L0:
	setne	%al
	movzbl	%al,%eax
	movl	%eax,-12(%ebp)
	pushl	-12(%ebp)
	call	putchar
	addl	$4, %esp
0:
	movl	%ebp, %esp
	popl	%ebp
	ret

	.globl	main
	.set	main.size, 12

