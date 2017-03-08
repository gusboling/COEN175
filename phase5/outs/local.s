.globl	main
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$12,%esp
	movl	$1,%eax
	movl	%eax,-4(%ebp)
	movl	$2,%eax
	movl	%eax,-8(%ebp)
	movl	$3,%eax
	movl	%eax,-12(%ebp)
	pushl	-4(%ebp)
	pushl	-8(%ebp)
	pushl	-12(%ebp)
	call	print
	movl	%ebp,%esp
	popl	%ebp
	ret

