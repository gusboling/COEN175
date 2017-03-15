main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$main.size, %esp
	movl	$48, %eax	# Assignment::generate
	movl	%eax, -12(%ebp)
	movl	$2, %eax
	addl	$3, %eax
	movl	%eax,-16(%ebp)
	movl	-16(%ebp), %eax	# Assignment::generate
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	addl	-12(%ebp), %eax
	movl	%eax,-20(%ebp)
	pushl	-20(%ebp)
	call	putchar
	addl	$4, %esp
	movl	$10, %eax
	movl	$5, %ecx
	cltd	
	idivl	%ecx
	movl	%eax, -24(%ebp)
	movl	-24(%ebp), %eax	# Assignment::generate
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	addl	-12(%ebp), %eax
	movl	%eax,-28(%ebp)
	pushl	-28(%ebp)
	call	putchar
	addl	$4, %esp
	movl	-8(%ebp), %eax
	cmpl	-4(%ebp), %eax
	setl	%al
	movzbl	%al, %eax
	movl	%eax, -32(%ebp)
	pushl	-32(%ebp)
	call	putchar
	addl	$4, %esp
0:
	movl	%ebp, %esp
	popl	%ebp
	ret

	.globl	main
	.set	main.size, 32

