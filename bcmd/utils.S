	.file	"utils.c"
	.code16gcc
	.text
	.globl	strcmp
	.type	strcmp, @function
strcmp:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%esi
	.cfi_offset 6, -12
	movl	%ecx, %esi
	pushl	%ebx
	.cfi_offset 3, -16
	xorl	%ebx, %ebx
.L2:
	movsbl	(%esi,%ebx), %eax
	movsbl	(%edx,%ebx), %ecx
	testb	%al, %al
	je	.L3
	cmpb	%cl, %al
	jne	.L3
	testb	%cl, %cl
	je	.L3
	cmpl	$-1, 8(%ebp)
	jne	.L16
.L4:
	incl	%ebx
	jmp	.L2
.L16:
	cmpl	8(%ebp), %ebx
	jl	.L4
.L3:
	popl	%ebx
	.cfi_restore 3
	subl	%ecx, %eax
	popl	%esi
	.cfi_restore 6
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret	$4
	.cfi_endproc
.LFE0:
	.size	strcmp, .-strcmp
	.globl	str_to_int
	.type	str_to_int, @function
str_to_int:
.LFB1:
	.cfi_startproc
	xorl	%eax, %eax
.L18:
	movsbl	(%ecx), %edx
	testb	%dl, %dl
	je	.L20
	imull	$10, %eax, %eax
	incl	%ecx
	leal	-48(%eax,%edx), %eax
	jmp	.L18
.L20:
	ret
	.cfi_endproc
.LFE1:
	.size	str_to_int, .-str_to_int
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
