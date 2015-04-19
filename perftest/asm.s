	.file	"main.cpp"
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.rodata
.LC0:
	.string	"Processing:"
.LC1:
	.string	" nSec"
	.text
	.globl	_Z16writeFrameToFilev
	.type	_Z16writeFrameToFilev, @function
_Z16writeFrameToFilev:
.LFB971:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$614472, %rsp
	.cfi_offset 3, -24
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-614464(%rbp), %rax
	movq	%rax, %rsi
	movl	$0, %edi
	call	clock_gettime
	movl	$0, -614468(%rbp)
	jmp	.L2
.L3:
	movw	$0, -614470(%rbp)
	movl	-614468(%rbp), %eax
	cltq
	movzbl	-614432(%rbp,%rax), %eax
	movsbl	%al, %eax
	sarl	$3, %eax
	sall	$11, %eax
	movl	%eax, %edx
	movzwl	-614470(%rbp), %eax
	orl	%edx, %eax
	movw	%ax, -614470(%rbp)
	movl	-614468(%rbp), %eax
	addl	$1, %eax
	cltq
	movzbl	-614432(%rbp,%rax), %eax
	movsbl	%al, %eax
	sarl	$2, %eax
	sall	$5, %eax
	movl	%eax, %edx
	movzwl	-614470(%rbp), %eax
	orl	%edx, %eax
	movw	%ax, -614470(%rbp)
	movl	-614468(%rbp), %eax
	addl	$2, %eax
	cltq
	movzbl	-614432(%rbp,%rax), %eax
	movsbl	%al, %eax
	sarl	$3, %eax
	movl	%eax, %edx
	movzwl	-614470(%rbp), %eax
	orl	%edx, %eax
	movw	%ax, -614470(%rbp)
	addl	$4, -614468(%rbp)
.L2:
	cmpl	$614399, -614468(%rbp)
	jle	.L3
	leaq	-614448(%rbp), %rax
	movq	%rax, %rsi
	movl	$0, %edi
	call	clock_gettime
	movq	-614440(%rbp), %rdx
	movq	-614456(%rbp), %rax
	movq	%rdx, %rbx
	subq	%rax, %rbx
	movl	$.LC0, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZNSolsEl
	movl	$.LC1, %esi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L4
	call	__stack_chk_fail
.L4:
	addq	$614472, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE971:
	.size	_Z16writeFrameToFilev, .-_Z16writeFrameToFilev
	.globl	main
	.type	main, @function
main:
.LFB972:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$0, -4(%rbp)
	jmp	.L6
.L7:
	call	_Z16writeFrameToFilev
	addl	$1, -4(%rbp)
.L6:
	cmpl	$100, -4(%rbp)
	jle	.L7
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE972:
	.size	main, .-main
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB982:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	cmpl	$1, -4(%rbp)
	jne	.L9
	cmpl	$65535, -8(%rbp)
	jne	.L9
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	call	__cxa_atexit
.L9:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE982:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I__Z16writeFrameToFilev, @function
_GLOBAL__sub_I__Z16writeFrameToFilev:
.LFB983:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$65535, %esi
	movl	$1, %edi
	call	_Z41__static_initialization_and_destruction_0ii
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE983:
	.size	_GLOBAL__sub_I__Z16writeFrameToFilev, .-_GLOBAL__sub_I__Z16writeFrameToFilev
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__Z16writeFrameToFilev
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
