.comm	n,4,4
.comm	from,4,4
.comm	to,4,4
.comm	spare,4,4
.comm	from,4,4
.comm	to,4,4
.comm	n,4,4
.comm	n,4,4
.comm	from,4,4
.comm	to,4,4
.comm	spare,4,4
.globl	towers
towers:
pushl	%ebp
movl	%esp, %ebp
subl	$0,%ebp
call	call_towers
call	print_move
call	call_towers
movl	%ebp,%esp
popl	%ebp
ret

.comm	n,4,4
.globl	main
main:
pushl	%ebp
movl	%esp, %ebp
subl	$0,%ebp
movl	$3,%eax
movl	%eax,-4(%ebp)
call	print
call	towers
movl	%ebp,%esp
popl	%ebp
ret

