.globl	main
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$0,%esp
	pushl	$83
	call	putchar
	pushl	$101
	call	putchar
	pushl	$103
	call	putchar
	pushl	$109
	call	putchar
	pushl	$101
	call	putchar
	pushl	$110
	call	putchar
	pushl	$116
	call	putchar
	pushl	$97
	call	putchar
	pushl	$116
	call	putchar
	pushl	$105
	call	putchar
	pushl	$111
	call	putchar
	pushl	$110
	call	putchar
	pushl	$32
	call	putchar
	pushl	$102
	call	putchar
	pushl	$97
	call	putchar
	pushl	$117
	call	putchar
	pushl	$108
	call	putchar
	pushl	$116
	call	putchar
	pushl	$10
	call	putchar
	movl	%ebp,%esp
	popl	%ebp
	ret

