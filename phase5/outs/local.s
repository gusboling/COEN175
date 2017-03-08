.comm	a,4,4
.comm	b,4,4
.comm	c,4,4
.comm	x,4,4
.comm	y,4,4
.comm	z,4,4
.globl	main
main:
pushl	%ebp
movl	%esp, %ebp
subl	$0,%ebp
movl	$1,%eax
movl	%eax,-4(%ebp)
movl	$2,%eax
movl	%eax,-8(%ebp)
movl	$3,%eax
movl	%eax,-12(%ebp)
call	print
movl	%ebp,%esp
popl	%ebp
ret

