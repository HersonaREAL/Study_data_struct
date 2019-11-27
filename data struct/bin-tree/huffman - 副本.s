	.file	"huffman.cpp"
	.text
	.section	.text$_ZN6ch_numC1Ev,"x"
	.linkonce discard
	.align 2
	.globl	_ZN6ch_numC1Ev
	.def	_ZN6ch_numC1Ev;	.scl	2;	.type	32;	.endef
	.seh_proc	_ZN6ch_numC1Ev
_ZN6ch_numC1Ev:
.LFB58:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	16(%rbp), %rax
	movl	$0, 4(%rax)
	nop
	popq	%rbp
	ret
	.seh_endproc
	.globl	CH
	.bss
	.align 32
CH:
	.space 1024
	.globl	HTNode
	.align 16
HTNode:
	.space 20
	.globl	HuffmanTree
	.align 8
HuffmanTree:
	.space 8
	.globl	HC
	.align 8
HC:
	.space 8
	.globl	str
	.align 32
str:
	.space 600
	.globl	len
	.align 4
len:
	.space 4
	.globl	huffsum
	.align 8
huffsum:
	.space 8
	.def	__main;	.scl	2;	.type	32;	.endef
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
.LFB59:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	call	__main
	leaq	str(%rip), %rcx
	call	gets
	leaq	str(%rip), %rdx
	leaq	CH(%rip), %rcx
	call	_Z8sum_charP6ch_numPc
	movl	%eax, len(%rip)
	movl	len(%rip), %edx
	movq	huffsum(%rip), %rax
	movq	%rax, %rcx
	call	_Z15creat_sum_arrayP6ch_numi
	movq	%rax, huffsum(%rip)
	movl	len(%rip), %edx
	movq	huffsum(%rip), %rax
	movl	%edx, %r8d
	movq	%rax, %rdx
	leaq	HuffmanTree(%rip), %rcx
	call	_Z13CreatHuffTreeRP8TreeNodeP6ch_numi
	movl	len(%rip), %eax
	movl	%eax, %ecx
	call	_Z16PrintHuffmanTreei
	movl	len(%rip), %edx
	movq	HuffmanTree(%rip), %rax
	movl	%edx, %r8d
	leaq	HC(%rip), %rdx
	movq	%rax, %rcx
	call	_Z16CreatHuffmanCodeP8TreeNodeRPPci
	movl	len(%rip), %eax
	movl	%eax, %ecx
	call	_Z16PrintHuffmanCodei
	call	getchar
	movl	$0, %eax
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	_Z8sum_charP6ch_numPc
	.def	_Z8sum_charP6ch_numPc;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z8sum_charP6ch_numPc
_Z8sum_charP6ch_numPc:
.LFB60:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
.L6:
	cmpl	$127, -8(%rbp)
	jg	.L5
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	16(%rbp), %rax
	addq	%rdx, %rax
	movl	-8(%rbp), %edx
	movb	%dl, (%rax)
	addl	$1, -8(%rbp)
	jmp	.L6
.L5:
	movl	$0, -12(%rbp)
.L8:
	movl	-12(%rbp), %eax
	cltq
	movq	24(%rbp), %rdx
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	je	.L7
	movl	-12(%rbp), %eax
	cltq
	movq	24(%rbp), %rdx
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbq	%al, %rax
	leaq	0(,%rax,8), %rdx
	movq	16(%rbp), %rax
	addq	%rdx, %rax
	movl	4(%rax), %edx
	addl	$1, %edx
	movl	%edx, 4(%rax)
	addl	$1, -12(%rbp)
	jmp	.L8
.L7:
	movl	$0, -16(%rbp)
.L11:
	cmpl	$127, -16(%rbp)
	jg	.L9
	movl	-16(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	16(%rbp), %rax
	addq	%rdx, %rax
	movl	4(%rax), %eax
	testl	%eax, %eax
	je	.L10
	addl	$1, -4(%rbp)
.L10:
	addl	$1, -16(%rbp)
	jmp	.L11
.L9:
	movl	-4(%rbp), %eax
	addq	$16, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC0:
	.ascii "%c:%d\12\0"
	.text
	.globl	_Z15creat_sum_arrayP6ch_numi
	.def	_Z15creat_sum_arrayP6ch_numi;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z15creat_sum_arrayP6ch_numi
_Z15creat_sum_arrayP6ch_numi:
.LFB61:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	$0, -4(%rbp)
	movl	24(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rcx
	call	malloc
	movq	%rax, -16(%rbp)
	movl	$0, -8(%rbp)
.L16:
	cmpl	$127, -8(%rbp)
	jg	.L14
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	4+CH(%rip), %rax
	movl	(%rdx,%rax), %eax
	testl	%eax, %eax
	je	.L15
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-16(%rbp), %rax
	addq	%rax, %rdx
	movl	-8(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rcx
	leaq	CH(%rip), %rax
	movzbl	(%rcx,%rax), %eax
	movb	%al, (%rdx)
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movl	-8(%rbp), %edx
	movslq	%edx, %rdx
	leaq	0(,%rdx,8), %rcx
	leaq	4+CH(%rip), %rdx
	movl	(%rcx,%rdx), %edx
	movl	%edx, 4(%rax)
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movl	4(%rax), %edx
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rcx
	movq	-16(%rbp), %rax
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%edx, %r8d
	movl	%eax, %edx
	leaq	.LC0(%rip), %rcx
	call	printf
	addl	$1, -4(%rbp)
.L15:
	addl	$1, -8(%rbp)
	jmp	.L16
.L14:
	movq	-16(%rbp), %rax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC1:
	.ascii "\12-------------------------\263\365\314\254------------------------------\12\275\332\265\343     weight     parent     lchiled     rchild\0"
.LC2:
	.ascii "%-11d%-11d%-11d%-11d%-11d\12\0"
	.text
	.globl	_Z13CreatHuffTreeRP8TreeNodeP6ch_numi
	.def	_Z13CreatHuffTreeRP8TreeNodeP6ch_numi;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z13CreatHuffTreeRP8TreeNodeP6ch_numi
_Z13CreatHuffTreeRP8TreeNodeP6ch_numi:
.LFB62:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$96, %rsp
	.seh_stackalloc	96
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	movl	%r8d, 32(%rbp)
	cmpl	$1, 32(%rbp)
	jle	.L35
	movl	32(%rbp), %eax
	addl	%eax, %eax
	subl	$1, %eax
	movl	%eax, -40(%rbp)
	movl	-40(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rcx
	call	malloc
	movq	%rax, %rdx
	movq	16(%rbp), %rax
	movq	%rdx, (%rax)
	movl	$1, -4(%rbp)
.L22:
	movl	-4(%rbp), %eax
	cmpl	-40(%rbp), %eax
	jg	.L21
	movq	16(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rax, %rcx
	movl	$0, 16(%rcx)
	movq	16(%rbp), %rax
	movq	(%rax), %r8
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	leaq	(%r8,%rax), %rdx
	movl	16(%rcx), %eax
	movl	%eax, 12(%rdx)
	movq	16(%rbp), %rax
	movq	(%rax), %r8
	movl	-4(%rbp), %eax
	movslq	%eax, %rcx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$2, %rax
	addq	%r8, %rax
	movl	12(%rdx), %edx
	movl	%edx, 8(%rax)
	addl	$1, -4(%rbp)
	jmp	.L22
.L21:
	leaq	.LC1(%rip), %rcx
	call	puts
	movl	$1, -8(%rbp)
.L24:
	movl	-8(%rbp), %eax
	cmpl	32(%rbp), %eax
	jg	.L23
	movl	-8(%rbp), %eax
	cltq
	salq	$3, %rax
	leaq	-8(%rax), %rdx
	movq	24(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movq	16(%rbp), %rax
	movq	(%rax), %r8
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	leaq	(%r8,%rax), %rdx
	movzbl	(%rcx), %eax
	movb	%al, (%rdx)
	movl	-8(%rbp), %eax
	cltq
	salq	$3, %rax
	leaq	-8(%rax), %rdx
	movq	24(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movq	16(%rbp), %rax
	movq	(%rax), %r8
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%r8, %rax
	movl	4(%rcx), %edx
	movl	%edx, 4(%rax)
	movq	HuffmanTree(%rip), %rcx
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	movl	16(%rax), %r8d
	movq	HuffmanTree(%rip), %rcx
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	movl	12(%rax), %ecx
	movq	HuffmanTree(%rip), %r9
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%r9, %rax
	movl	8(%rax), %r9d
	movq	HuffmanTree(%rip), %r10
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%r10, %rax
	movl	4(%rax), %edx
	movl	-8(%rbp), %eax
	movl	%r8d, 40(%rsp)
	movl	%ecx, 32(%rsp)
	movl	%edx, %r8d
	movl	%eax, %edx
	leaq	.LC2(%rip), %rcx
	call	printf
	addl	$1, -8(%rbp)
	jmp	.L24
.L23:
	movl	32(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -24(%rbp)
.L34:
	movl	-24(%rbp), %eax
	cmpl	-40(%rbp), %eax
	jg	.L18
	movq	16(%rbp), %rax
	movq	(%rax), %rcx
	movl	-24(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	subq	$20, %rax
	addq	%rcx, %rax
	movl	4(%rax), %eax
	movl	%eax, -12(%rbp)
	movl	-24(%rbp), %eax
	subl	$1, %eax
	movl	%eax, -16(%rbp)
	movl	$1, -28(%rbp)
.L27:
	movl	-24(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jle	.L25
	movq	16(%rbp), %rax
	movq	(%rax), %rcx
	movl	-28(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	movl	8(%rax), %eax
	testl	%eax, %eax
	jne	.L26
	movq	16(%rbp), %rax
	movq	(%rax), %rcx
	movl	-28(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	movl	4(%rax), %eax
	cmpl	%eax, -12(%rbp)
	jl	.L26
	movq	16(%rbp), %rax
	movq	(%rax), %rcx
	movl	-28(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	movl	4(%rax), %eax
	movl	%eax, -12(%rbp)
	movl	-28(%rbp), %eax
	movl	%eax, -16(%rbp)
.L26:
	addl	$1, -28(%rbp)
	jmp	.L27
.L25:
	movl	$1, -32(%rbp)
.L30:
	movl	-24(%rbp), %eax
	cmpl	-32(%rbp), %eax
	jle	.L28
	movq	16(%rbp), %rax
	movq	(%rax), %rcx
	movl	-32(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	movl	8(%rax), %eax
	testl	%eax, %eax
	jne	.L29
	movl	-32(%rbp), %eax
	cmpl	-16(%rbp), %eax
	je	.L29
	movq	16(%rbp), %rax
	movq	(%rax), %rcx
	movl	-32(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	movl	4(%rax), %eax
	movl	%eax, -12(%rbp)
	jmp	.L28
.L29:
	addl	$1, -32(%rbp)
	jmp	.L30
.L28:
	movl	$1, -36(%rbp)
.L33:
	movl	-24(%rbp), %eax
	cmpl	-36(%rbp), %eax
	jle	.L31
	movq	16(%rbp), %rax
	movq	(%rax), %rcx
	movl	-36(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	movl	8(%rax), %eax
	testl	%eax, %eax
	jne	.L32
	movl	-36(%rbp), %eax
	cmpl	-16(%rbp), %eax
	je	.L32
	movq	16(%rbp), %rax
	movq	(%rax), %rcx
	movl	-36(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	movl	4(%rax), %eax
	cmpl	%eax, -12(%rbp)
	jl	.L32
	movq	16(%rbp), %rax
	movq	(%rax), %rcx
	movl	-36(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	movl	4(%rax), %eax
	movl	%eax, -12(%rbp)
	movl	-36(%rbp), %eax
	movl	%eax, -20(%rbp)
.L32:
	addl	$1, -36(%rbp)
	jmp	.L33
.L31:
	movq	16(%rbp), %rax
	movq	(%rax), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	leaq	(%rcx,%rax), %rdx
	movl	-24(%rbp), %eax
	movl	%eax, 8(%rdx)
	movq	16(%rbp), %rax
	movq	(%rax), %r8
	movl	-16(%rbp), %eax
	movslq	%eax, %rcx
	movq	%rcx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	salq	$2, %rax
	addq	%r8, %rax
	movl	8(%rdx), %edx
	movl	%edx, 8(%rax)
	movq	16(%rbp), %rax
	movq	(%rax), %rcx
	movl	-24(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	movl	-16(%rbp), %edx
	movl	%edx, 12(%rax)
	movq	16(%rbp), %rax
	movq	(%rax), %rcx
	movl	-24(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	movl	-20(%rbp), %edx
	movl	%edx, 16(%rax)
	movq	16(%rbp), %rax
	movq	(%rax), %rcx
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	movl	4(%rax), %r8d
	movq	16(%rbp), %rax
	movq	(%rax), %rcx
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	movl	4(%rax), %ecx
	movq	16(%rbp), %rax
	movq	(%rax), %r9
	movl	-24(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%r9, %rax
	leal	(%r8,%rcx), %edx
	movl	%edx, 4(%rax)
	addl	$1, -24(%rbp)
	jmp	.L34
.L35:
	nop
.L18:
	addq	$96, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	_Z16CreatHuffmanCodeP8TreeNodeRPPci
	.def	_Z16CreatHuffmanCodeP8TreeNodeRPPci;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z16CreatHuffmanCodeP8TreeNodeRPPci
_Z16CreatHuffmanCodeP8TreeNodeRPPci:
.LFB63:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%r15
	.seh_pushreg	%r15
	pushq	%r14
	.seh_pushreg	%r14
	pushq	%r13
	.seh_pushreg	%r13
	pushq	%r12
	.seh_pushreg	%r12
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$64, %rsp
	.seh_stackalloc	64
	.seh_endprologue
	movq	%rcx, 64(%rbp)
	movq	%rdx, 72(%rbp)
	movl	%r8d, 80(%rbp)
	movq	%rsp, %rax
	movq	%rax, %rsi
	movl	80(%rbp), %eax
	addl	$1, %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rcx
	call	malloc
	movq	%rax, %rdx
	movq	72(%rbp), %rax
	movq	%rdx, (%rax)
	movl	80(%rbp), %eax
	cltq
	subq	$1, %rax
	movq	%rax, -24(%rbp)
	movq	%rax, %rdx
	addq	$1, %rdx
	movq	%rdx, %r14
	movl	$0, %r15d
	movq	%rax, %rdx
	addq	$1, %rdx
	movq	%rdx, %r12
	movl	$0, %r13d
	addq	$1, %rax
	addq	$15, %rax
	shrq	$4, %rax
	salq	$4, %rax
	call	___chkstk_ms
	subq	%rax, %rsp
	leaq	32(%rsp), %rax
	addq	$0, %rax
	movq	%rax, -32(%rbp)
	movl	80(%rbp), %eax
	subl	$1, %eax
	movq	-32(%rbp), %rdx
	cltq
	movb	$0, (%rdx,%rax)
	movl	$1, -4(%rbp)
.L42:
	movl	-4(%rbp), %eax
	cmpl	80(%rbp), %eax
	jg	.L37
	movl	80(%rbp), %eax
	subl	$1, %eax
	movl	%eax, -16(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, -12(%rbp)
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	64(%rbp), %rax
	addq	%rdx, %rax
	movl	8(%rax), %eax
	movl	%eax, -8(%rbp)
.L41:
	cmpl	$0, -8(%rbp)
	je	.L38
	subl	$1, -16(%rbp)
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	64(%rbp), %rax
	addq	%rdx, %rax
	movl	12(%rax), %eax
	cmpl	%eax, -12(%rbp)
	jne	.L39
	movq	-32(%rbp), %rdx
	movl	-16(%rbp), %eax
	cltq
	movb	$48, (%rdx,%rax)
	jmp	.L40
.L39:
	movq	-32(%rbp), %rdx
	movl	-16(%rbp), %eax
	cltq
	movb	$49, (%rdx,%rax)
.L40:
	movl	-8(%rbp), %eax
	movl	%eax, -12(%rbp)
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	64(%rbp), %rax
	addq	%rdx, %rax
	movl	8(%rax), %eax
	movl	%eax, -8(%rbp)
	jmp	.L41
.L38:
	movl	80(%rbp), %eax
	subl	-16(%rbp), %eax
	cltq
	movq	72(%rbp), %rdx
	movq	(%rdx), %rcx
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	leaq	(%rcx,%rdx), %rbx
	movq	%rax, %rcx
	call	malloc
	movq	%rax, (%rbx)
	movl	-16(%rbp), %eax
	cltq
	movq	-32(%rbp), %rdx
	addq	%rax, %rdx
	movq	72(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	%rcx, %rax
	movq	(%rax), %rax
	movq	%rax, %rcx
	call	strcpy
	addl	$1, -4(%rbp)
	jmp	.L42
.L37:
	movq	%rsi, %rsp
	nop
	movq	%rbp, %rsp
	popq	%rbx
	popq	%rsi
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC3:
	.ascii "\12\271\376\267\362\302\374\261\340\302\353\243\272\0"
.LC4:
	.ascii "%c : \0"
.LC5:
	.ascii "\12\0"
	.text
	.globl	_Z16PrintHuffmanCodei
	.def	_Z16PrintHuffmanCodei;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z16PrintHuffmanCodei
_Z16PrintHuffmanCodei:
.LFB64:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	leaq	.LC3(%rip), %rcx
	call	puts
	movl	$1, -4(%rbp)
.L47:
	movl	-4(%rbp), %eax
	cmpl	16(%rbp), %eax
	jg	.L48
	movq	HuffmanTree(%rip), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%eax, %edx
	leaq	.LC4(%rip), %rcx
	call	printf
	movl	$0, -8(%rbp)
.L46:
	movq	HC(%rip), %rdx
	movl	-4(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movl	-8(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	je	.L45
	movq	HC(%rip), %rdx
	movl	-4(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movl	-8(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%eax, %ecx
	call	putchar
	addl	$1, -8(%rbp)
	jmp	.L46
.L45:
	leaq	.LC5(%rip), %rcx
	call	puts
	addl	$1, -4(%rbp)
	jmp	.L47
.L48:
	nop
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC6:
	.ascii "\12-------------------------\326\325\314\254------------------------------\12\275\332\265\343     weight     parent     lchiled     rchild\0"
	.text
	.globl	_Z16PrintHuffmanTreei
	.def	_Z16PrintHuffmanTreei;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z16PrintHuffmanTreei
_Z16PrintHuffmanTreei:
.LFB65:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$64, %rsp
	.seh_stackalloc	64
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	leaq	.LC6(%rip), %rcx
	call	puts
	movl	$1, -4(%rbp)
.L51:
	movl	16(%rbp), %eax
	addl	%eax, %eax
	cmpl	%eax, -4(%rbp)
	jge	.L52
	movq	HuffmanTree(%rip), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	movl	16(%rax), %r8d
	movq	HuffmanTree(%rip), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rcx, %rax
	movl	12(%rax), %ecx
	movq	HuffmanTree(%rip), %r9
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%r9, %rax
	movl	8(%rax), %r9d
	movq	HuffmanTree(%rip), %r10
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%r10, %rax
	movl	4(%rax), %edx
	movl	-4(%rbp), %eax
	movl	%r8d, 40(%rsp)
	movl	%ecx, 32(%rsp)
	movl	%edx, %r8d
	movl	%eax, %edx
	leaq	.LC2(%rip), %rcx
	call	printf
	addl	$1, -4(%rbp)
	jmp	.L51
.L52:
	nop
	addq	$64, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.def	_Z41__static_initialization_and_destruction_0ii;	.scl	3;	.type	32;	.endef
	.seh_proc	_Z41__static_initialization_and_destruction_0ii
_Z41__static_initialization_and_destruction_0ii:
.LFB66:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movl	%ecx, 32(%rbp)
	movl	%edx, 40(%rbp)
	cmpl	$1, 32(%rbp)
	jne	.L57
	cmpl	$65535, 40(%rbp)
	jne	.L57
	leaq	CH(%rip), %rax
	movl	$127, %ebx
	movq	%rax, %rsi
.L56:
	testq	%rbx, %rbx
	js	.L57
	movq	%rsi, %rcx
	call	_ZN6ch_numC1Ev
	addq	$8, %rsi
	subq	$1, %rbx
	jmp	.L56
.L57:
	nop
	addq	$32, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rbp
	ret
	.seh_endproc
	.def	_GLOBAL__sub_I_CH;	.scl	3;	.type	32;	.endef
	.seh_proc	_GLOBAL__sub_I_CH
_GLOBAL__sub_I_CH:
.LFB67:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movl	$65535, %edx
	movl	$1, %ecx
	call	_Z41__static_initialization_and_destruction_0ii
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section	.ctors,"w"
	.align 8
	.quad	_GLOBAL__sub_I_CH
	.ident	"GCC: (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0"
	.def	gets;	.scl	2;	.type	32;	.endef
	.def	getchar;	.scl	2;	.type	32;	.endef
	.def	malloc;	.scl	2;	.type	32;	.endef
	.def	printf;	.scl	2;	.type	32;	.endef
	.def	puts;	.scl	2;	.type	32;	.endef
	.def	strcpy;	.scl	2;	.type	32;	.endef
	.def	putchar;	.scl	2;	.type	32;	.endef
