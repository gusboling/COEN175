main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$main.size, %esp
	movl	-4(%ebp), %eax
	addl	-8(%ebp), %eax
	movl	%eax,-28(%ebp)
	movl	-28(%ebp), %eax	# Assignment::generate
	movl	%eax, -12(%ebp)
	movl	$5, %eax	# Assignment::generate
	movl	%eax, -20(%ebp)
	movl	-20(%ebp), %eax
	negl	%eax
	movl	%eax, -32(%ebp)
	movl	-32(%ebp), %eax	# Assignment::generate
	movl	%eax, -16(%ebp)
0:
	movl	%ebp, %esp
	popl	%ebp
	ret

	.globl	main
	.set	main.size, 32

