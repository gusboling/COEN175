	.file	"array.c"
	.comm	a,40,32
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$32, %esp
	movl	$10, 28(%esp)
	movl	28(%esp), %eax
	movl	%eax, (%esp)
	call	init_array
	movl	28(%esp), %eax
	movl	%eax, (%esp)
	call	print_array
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-17)"
	.section	.note.GNU-stack,"",@progbits
