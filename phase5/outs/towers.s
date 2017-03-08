.globl	towers
towers:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16,%esp
	pushl	-12(%ebp)
pushl	-16(%ebp)
pushl	-8(%ebp)
pushl	-4(%ebp)
	call	call_towers
	pushl	-12(%ebp)
pushl	-8(%ebp)
	call	print_move
	pushl	-8(%ebp)
pushl	-12(%ebp)
pushl	-16(%ebp)
pushl	-4(%ebp)
	call	call_towers
	movl	%ebp,%esp
	popl	%ebp
	ret

.globl	main
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4,%esp
	movl	$3,%eax
	movl	%eax,-4(%ebp)
	pushl	-4(%ebp)
	call	print
	pushl	$3
pushl	$2
pushl	$1
pushl	-4(%ebp)
	call	towers
	movl	%ebp,%esp
	popl	%ebp
	ret

