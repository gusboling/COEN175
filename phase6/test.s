main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$main.size, %esp
	movl	$2, %eax
	addl	$3, %eax
	movl	%eax,-12(%ebp)
	movl	-12(%ebp), %eax	# Assignment::generate
	movl	%eax, -4(%ebp)
	movl	$48, %eax	# Assignment::generate
	movl	%eax, -8(%ebp)
	movl	-4(%ebp), %eax
	addl	-8(%ebp), %eax
	movl	%eax,-16(%ebp)
	pushl	-16(%ebp)
	call	putchar
	addl	$4, %esp
0:
	movl	%ebp, %esp
	popl	%ebp
	ret

	.globl	main
	.set	main.size, 16

