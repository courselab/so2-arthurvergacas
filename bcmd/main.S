	.file	"main.c"
	.code16gcc
	.text
	.globl	buffer
	.bss
	.align 4
	.type	buffer, @object
	.size	buffer, 10
buffer:
	.zero	10
	.section	.rodata
.LC0:
	.string	"I can't :("
	.text
	.globl	add_1
	.type	add_1, @function
add_1:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	cmpl	$0, 8(%ebp)
	jle	.L2
	cmpl	$9, 8(%ebp)
	jle	.L3
.L2:
	movl	$.LC0, %ecx
	call	println
	jmp	.L1
.L3:
	movl	8(%ebp), %eax
	addl	$49, %eax
	movb	%al, -10(%ebp)
	movb	$0, -9(%ebp)
	leal	-10(%ebp), %eax
	movl	%eax, %ecx
	call	println
.L1:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	add_1, .-add_1
	.section	.rodata
.LC1:
	.string	"Boot Command 1.0"
.LC2:
	.string	"$ "
.LC3:
	.string	"add1 "
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x7c,0x6
	subl	$20, %esp
	call	clear
	movl	$.LC1, %ecx
	call	println
.L7:
	movl	$.LC2, %ecx
	call	print
	movl	$buffer, %ecx
	call	readln
	movzbl	buffer, %eax
	testb	%al, %al
	je	.L7
	subl	$12, %esp
	pushl	$4
	movl	$.LC3, %edx
	movl	$buffer, %ecx
	call	strcmp
	addl	$12, %esp
	testl	%eax, %eax
	jne	.L7
	movl	$buffer+5, %ecx
	call	str_to_int
	movl	%eax, -12(%ebp)
	subl	$12, %esp
	pushl	-12(%ebp)
	call	add_1
	addl	$16, %esp
	jmp	.L7
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
