.comm	a,40,4
.globl	main
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4,%esp
	movl	$10,%eax
	movl	%eax,-4(%ebp)
	pushl	-4(%ebp)
	call	init_array
	pushl	-4(%ebp)
	call	print_array
	movl	%ebp,%esp
	popl	%ebp
	ret

