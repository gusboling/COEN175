.comm	a,4,4
.comm	n,4,4
.comm	n,4,4
.comm	n,4,4
.globl	main
main:
pushl	%ebp
movl	%esp, %ebp
subl	$0,%ebp
movl	$10,%eax
movl	%eax,-4(%ebp)
call	init_array
call	print_array
movl	%ebp,%esp
popl	%ebp
ret

