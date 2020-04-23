	.file	"main.c"
	.intel_syntax noprefix
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.globl	reverse
	.type	reverse, @function
reverse:
.LFB30:
	.cfi_startproc
	xor	eax, eax
	or	rcx, -1
	mov	rdx, rdi
	repnz scasb
	xor	eax, eax
	not	rcx
	dec	rcx
	movsx	rsi, ecx
	add	rsi, rdx
.L2:
	mov	edi, ecx
	mov	r8d, eax
	sub	edi, eax
	inc	rax
	cmp	r8d, edi
	jge	.L5
	mov	rdi, rax
	mov	r8b, BYTE PTR [rdx-1+rax]
	neg	rdi
	mov	r9b, BYTE PTR [rsi+rdi]
	mov	BYTE PTR [rdx-1+rax], r9b
	mov	BYTE PTR [rsi+rdi], r8b
	jmp	.L2
.L5:
	ret
	.cfi_endproc
.LFE30:
	.size	reverse, .-reverse
	.section	.text.unlikely
.LCOLDE0:
	.text
.LHOTE0:
	.section	.text.unlikely
.LCOLDB1:
	.text
.LHOTB1:
	.globl	to_hex_char
	.type	to_hex_char, @function
to_hex_char:
.LFB31:
	.cfi_startproc
	cmp	edi, 9
	ja	.L7
	lea	eax, [rdi+48]
	ret
.L7:
	lea	eax, [rdi-10]
	add	edi, 55
	cmp	eax, 5
	mov	al, 0
	cmovbe	eax, edi
	ret
	.cfi_endproc
.LFE31:
	.size	to_hex_char, .-to_hex_char
	.section	.text.unlikely
.LCOLDE1:
	.text
.LHOTE1:
	.section	.text.unlikely
.LCOLDB4:
	.text
.LHOTB4:
	.globl	is_integral
	.type	is_integral, @function
is_integral:
.LFB32:
	.cfi_startproc
	cvttss2si	eax, xmm0
	cvtsi2ss	xmm1, eax
	subss	xmm0, xmm1
	movss	xmm1, DWORD PTR .LC2[rip]
	andps	xmm0, xmm1
	movss	xmm1, DWORD PTR .LC3[rip]
	ucomiss	xmm1, xmm0
	seta	al
	ret
	.cfi_endproc
.LFE32:
	.size	is_integral, .-is_integral
	.section	.text.unlikely
.LCOLDE4:
	.text
.LHOTE4:
	.section	.text.unlikely
.LCOLDB9:
	.text
.LHOTB9:
	.globl	bin_to_dec
	.type	bin_to_dec, @function
bin_to_dec:
.LFB33:
	.cfi_startproc
	push	r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	push	r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	xor	eax, eax
	push	r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	push	r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	or	rcx, -1
	push	rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	push	rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	mov	rbx, rdi
	xorps	xmm0, xmm0
	sub	rsp, 24
	.cfi_def_cfa_offset 80
	repnz scasb
	not	rcx
	dec	rcx
	test	ecx, ecx
	je	.L12
	mov	al, BYTE PTR [rbx]
	mov	r12d, ecx
	mov	BYTE PTR [rsp+11], al
	xor	eax, eax
.L13:
	cmp	eax, r12d
	mov	edx, eax
	jge	.L27
	inc	rax
	cmp	BYTE PTR [rbx-1+rax], 46
	jne	.L13
	mov	r13b, 1
	jmp	.L14
.L27:
	xor	edx, edx
	xor	r13d, r13d
.L14:
	xorps	xmm2, xmm2
	mov	r15d, ecx
	lea	r14d, [rdx-1]
	mov	rbp, rbx
	sub	r15d, edx
.L16:
	mov	edx, ebp
	sub	edx, ebx
	cmp	r12d, edx
	jle	.L28
	cmp	BYTE PTR [rbp+0], 49
	jne	.L17
	test	r13b, r13b
	movss	DWORD PTR [rsp+12], xmm2
	je	.L18
	cvtsi2ss	xmm1, r14d
	jmp	.L26
.L18:
	lea	edx, [r15+r14]
	cvtsi2ss	xmm1, edx
.L26:
	movss	xmm0, DWORD PTR .LC8[rip]
	call	powf
	movss	xmm2, DWORD PTR [rsp+12]
	addss	xmm2, xmm0
.L17:
	dec	r14d
	inc	rbp
	jmp	.L16
.L28:
	cmp	BYTE PTR [rsp+11], 45
	movss	xmm0, DWORD PTR .LC6[rip]
	je	.L20
	movss	xmm0, DWORD PTR .LC7[rip]
.L20:
	mulss	xmm0, xmm2
.L12:
	add	rsp, 24
	.cfi_def_cfa_offset 56
	pop	rbx
	.cfi_def_cfa_offset 48
	pop	rbp
	.cfi_def_cfa_offset 40
	pop	r12
	.cfi_def_cfa_offset 32
	pop	r13
	.cfi_def_cfa_offset 24
	pop	r14
	.cfi_def_cfa_offset 16
	pop	r15
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE33:
	.size	bin_to_dec, .-bin_to_dec
	.section	.text.unlikely
.LCOLDE9:
	.text
.LHOTE9:
	.section	.text.unlikely
.LCOLDB11:
	.text
.LHOTB11:
	.globl	dec_to_base
	.type	dec_to_base, @function
dec_to_base:
.LFB34:
	.cfi_startproc
	xorps	xmm1, xmm1
	push	r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	mov	r12, rsi
	push	rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	mov	ebp, edi
	push	rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	mov	rbx, rsi
	ucomiss	xmm1, xmm0
	jbe	.L30
	movss	xmm1, DWORD PTR .LC10[rip]
	lea	rbx, [rsi+1]
	mov	BYTE PTR [rsi], 45
	xorps	xmm0, xmm1
.L30:
	cvttss2si	rdx, xmm0
	mov	r8, rbx
	xor	r10d, r10d
	mov	eax, edx
	mov	edx, edx
	cvtsi2ss	xmm1, rdx
	subss	xmm0, xmm1
	movaps	xmm2, xmm0
.L34:
	xor	edx, edx
	lea	ecx, [r10+1]
	div	ebp
	mov	esi, eax
	mov	edi, edx
	call	to_hex_char
	mov	BYTE PTR [r8], al
	inc	r8
	test	esi, esi
	mov	eax, esi
	je	.L45
	mov	r10d, ecx
	jmp	.L34
.L45:
	movsx	rcx, ecx
	mov	rdi, rbx
	lea	r11, [rbx+rcx]
	mov	BYTE PTR [r11], 0
	call	reverse
	movaps	xmm0, xmm2
	call	is_integral
	test	al, al
	jne	.L35
	mov	eax, ebp
	lea	ecx, [r10+2]
	mov	BYTE PTR [r11], 46
	cvtsi2ss	xmm3, rax
	movsx	rcx, ecx
	mulss	xmm2, xmm3
.L39:
	cvttss2si	rax, xmm2
	xor	edx, edx
	div	ebp
	mov	edi, edx
	call	to_hex_char
	movaps	xmm0, xmm2
	mov	BYTE PTR [rbx+rcx], al
	call	is_integral
	test	al, al
	lea	rdx, [rcx+1]
	jne	.L38
	cvttss2si	eax, xmm2
	mov	rcx, rdx
	cvtsi2ss	xmm0, eax
	subss	xmm2, xmm0
	mulss	xmm2, xmm3
	jmp	.L39
.L38:
	mov	BYTE PTR [rbx+1+rcx], 0
.L35:
	mov	rax, r12
	pop	rbx
	.cfi_def_cfa_offset 24
	pop	rbp
	.cfi_def_cfa_offset 16
	pop	r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE34:
	.size	dec_to_base, .-dec_to_base
	.section	.text.unlikely
.LCOLDE11:
	.text
.LHOTE11:
	.section	.text.unlikely
.LCOLDB12:
	.text
.LHOTB12:
	.globl	bits_in_memory
	.type	bits_in_memory, @function
bits_in_memory:
.LFB35:
	.cfi_startproc
	movd	eax, xmm0
	push	rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	mov	rbx, rdi
	mov	edi, 2
	mov	eax, eax
	sub	rsp, 48
	.cfi_def_cfa_offset 64
	cvtsi2ss	xmm0, rax
	lea	rsi, [rsp+8]
	mov	rdx, QWORD PTR fs:40
	mov	QWORD PTR [rsp+40], rdx
	xor	edx, edx
	call	dec_to_base
	mov	rsi, rbx
	xor	ecx, ecx
	xor	edi, edi
	xor	r8d, r8d
	mov	r9d, 5
	mov	r10b, 48
.L52:
	inc	edi
	mov	eax, edi
	cdq
	idiv	r9d
	test	edx, edx
	jne	.L49
	mov	BYTE PTR [rsi], 32
	jmp	.L50
.L49:
	movsx	rax, ecx
	mov	al, BYTE PTR [rsp+8+rax]
	test	al, al
	je	.L54
	test	r8b, r8b
	cmovne	eax, r10d
	jmp	.L51
.L54:
	mov	r8b, 1
	mov	al, 48
.L51:
	mov	BYTE PTR [rsi], al
	inc	ecx
.L50:
	inc	rsi
	cmp	ecx, 31
	jle	.L52
	mov	rdx, QWORD PTR [rsp+40]
	xor	rdx, QWORD PTR fs:40
	mov	BYTE PTR [rbx+41], 0
	mov	rax, rbx
	je	.L53
	call	__stack_chk_fail
.L53:
	add	rsp, 48
	.cfi_def_cfa_offset 16
	pop	rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE35:
	.size	bits_in_memory, .-bits_in_memory
	.section	.text.unlikely
.LCOLDE12:
	.text
.LHOTE12:
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC13:
	.string	"Hex: %s\n"
.LC14:
	.string	"Dec: %s\n"
.LC15:
	.string	"Oct: %s\n"
.LC16:
	.string	"Bin: %s\n"
.LC17:
	.string	"Bin (in memory): %s\n"
.LC21:
	.string	"Mistake at binary transfer: %.6f, (%.2f%%)\n"
	.section	.text.unlikely
.LCOLDB22:
	.text
.LHOTB22:
	.globl	print
	.type	print, @function
print:
.LFB36:
	.cfi_startproc
	push	rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	mov	ebx, edi
	mov	edi, 16
	add	rsp, -128
	.cfi_def_cfa_offset 144
	lea	rsi, [rsp+20]
	movss	DWORD PTR [rsp+4], xmm0
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR [rsp+120], rax
	xor	eax, eax
	call	dec_to_base
	mov	esi, OFFSET FLAT:.LC13
	mov	rdx, rax
	mov	edi, 1
	xor	eax, eax
	call	__printf_chk
	test	bl, bl
	je	.L59
	lea	rsi, [rsp+20]
	mov	edi, 10
	movss	xmm0, DWORD PTR [rsp+4]
	call	dec_to_base
	mov	esi, OFFSET FLAT:.LC14
	mov	rdx, rax
	mov	edi, 1
	xor	eax, eax
	call	__printf_chk
.L59:
	lea	rsi, [rsp+20]
	movss	xmm0, DWORD PTR [rsp+4]
	mov	edi, 8
	call	dec_to_base
	mov	esi, OFFSET FLAT:.LC15
	mov	rdx, rax
	mov	edi, 1
	xor	eax, eax
	call	__printf_chk
	lea	rsi, [rsp+20]
	movss	xmm0, DWORD PTR [rsp+4]
	mov	edi, 2
	call	dec_to_base
	mov	esi, OFFSET FLAT:.LC16
	mov	rdx, rax
	mov	edi, 1
	xor	eax, eax
	call	__printf_chk
	lea	rdi, [rsp+20]
	movss	xmm0, DWORD PTR [rsp+4]
	call	bits_in_memory
	mov	esi, OFFSET FLAT:.LC17
	mov	rdx, rax
	mov	edi, 1
	xor	eax, eax
	call	__printf_chk
	cvtss2sd	xmm2, DWORD PTR [rsp+4]
	lea	rsi, [rsp+20]
	mov	edi, 2
	movss	xmm0, DWORD PTR [rsp+4]
	movsd	QWORD PTR [rsp+8], xmm2
	call	dec_to_base
	mov	rdi, rax
	call	bin_to_dec
	movsd	xmm2, QWORD PTR [rsp+8]
	cvtss2sd	xmm0, xmm0
	xorps	xmm3, xmm3
	movapd	xmm4, xmm2
	movsd	xmm1, QWORD PTR .LC18[rip]
	subsd	xmm4, xmm0
	movapd	xmm0, xmm4
	andps	xmm1, xmm0
	ucomisd	xmm1, xmm3
	jbe	.L58
	movsd	xmm1, QWORD PTR .LC20[rip]
	mov	esi, OFFSET FLAT:.LC21
	mov	edi, 1
	mov	al, 2
	mulsd	xmm1, xmm4
	divsd	xmm1, xmm2
	call	__printf_chk
.L58:
	mov	rax, QWORD PTR [rsp+120]
	xor	rax, QWORD PTR fs:40
	je	.L62
	call	__stack_chk_fail
.L62:
	sub	rsp, -128
	.cfi_def_cfa_offset 16
	pop	rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE36:
	.size	print, .-print
	.section	.text.unlikely
.LCOLDE22:
	.text
.LHOTE22:
	.section	.rodata.str1.1
.LC23:
	.ascii	"Hello!\nThe program helps to undestand how a 32-bit floating"
	.ascii	"-point number looks in other base systems. It can process de"
	.ascii	"cimal -> hexadecimal, octal or binar"
	.string	"y bases only and also shows how its value is located in the memory (in binary only) and what mistake occurs at the binary transfer. Thanks for using Andrey's program.\nBefore you start, please pay to get a full functional revision or consider the examples:\n"
.LC24:
	.string	"Dec: "
.LC25:
	.string	"%f"
	.section	.text.unlikely
.LCOLDB26:
	.section	.text.startup,"ax",@progbits
.LHOTB26:
	.globl	main
	.type	main, @function
main:
.LFB37:
	.cfi_startproc
	push	rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	mov	edi, OFFSET FLAT:.LC23
	xor	ebx, ebx
	sub	rsp, 16
	.cfi_def_cfa_offset 32
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR [rsp+8], rax
	xor	eax, eax
	call	puts
.L66:
	movss	xmm0, DWORD PTR examples[rbx]
	mov	edi, 1
	call	print
	add	rbx, 4
	mov	edi, 10
	call	putchar
	cmp	rbx, 16
	jne	.L66
.L67:
	mov	esi, OFFSET FLAT:.LC24
	mov	edi, 1
	xor	eax, eax
	call	__printf_chk
	lea	rsi, [rsp+4]
	mov	edi, OFFSET FLAT:.LC25
	xor	eax, eax
	call	__isoc99_scanf
	xor	edi, edi
	movss	xmm0, DWORD PTR [rsp+4]
	call	print
	mov	edi, 10
	call	putchar
	jmp	.L67
	.cfi_endproc
.LFE37:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE26:
	.section	.text.startup
.LHOTE26:
	.section	.rodata
	.align 16
	.type	examples, @object
	.size	examples, 16
examples:
	.long	1123549184
	.long	3266183168
	.long	1102669939
	.long	3267798106
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC2:
	.long	2147483647
	.long	0
	.long	0
	.long	0
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC3:
	.long	869711765
	.align 4
.LC6:
	.long	3212836864
	.align 4
.LC7:
	.long	1065353216
	.align 4
.LC8:
	.long	1073741824
	.section	.rodata.cst16
	.align 16
.LC10:
	.long	2147483648
	.long	0
	.long	0
	.long	0
	.align 16
.LC18:
	.long	4294967295
	.long	2147483647
	.long	0
	.long	0
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC20:
	.long	0
	.long	1079574528
	.ident	"GCC: (Ubuntu 5.5.0-12ubuntu1~16.04) 5.5.0 20171010"
	.section	.note.GNU-stack,"",@progbits
