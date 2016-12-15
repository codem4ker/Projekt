section .data
	d_pi:	dq 6.283185307
	dt: dq 0.0001
	height: dd 768
	width: dd 768
	one: dq 1.0

section .text
global drawCurve

drawCurve:
	push rbp
	mov rbp, rsp

	push r12
	push r13				; r13 - widht / 2
	push r14
	push r15
	sub rsp, 6
	movsd [rbp-10], xmm6
	movsd [rbp-12], xmm7

	pxor xmm5, xmm5			; xmm5 - counter
	
	mov r13, [width]
	sar r13, 1
	cvtsi2sd xmm7, r13

	test rdx, rdx			; rdx - a
	jz a_zero
	test r8, r8
	jz b_zero
	movsd xmm1, [d_pi]
	cvtsi2sd xmm2, rdx		; xmm2 - a
	cvtsi2sd xmm3, r8		; xmm3 - b
	mulsd xmm1, xmm3
	movsd xmm0, xmm1
	movsd xmm1, [dt]
	divsd xmm0, xmm1
	cvttsd2si r11, xmm0
	add r11, 1
	jmp loop

a_zero:
	test r8, r8				; r8 - b
	jz ab_zero
	movsd xmm1, [d_pi]
	cvtsi2sd xmm3, r8		; xmm3 - b
	pxor xmm2, xmm2
	divsd xmm1, xmm3
	movsd xmm0, xmm1
	movsd xmm1, [dt]
	divsd xmm0, xmm1
	cvttsd2si r11, xmm0
	add r11, 1
	jmp loop

ab_zero:
	mov r11, 1
	pxor xmm2, xmm2
	pxor xmm3, xmm3
	jmp loop

b_zero:
	movsd xmm1, [d_pi]
	cvtsi2sd xmm2, rdx
	pxor xmm3, xmm3
	divsd xmm1, xmm2
	movsd xmm0, xmm1
	movsd xmm1, [dt]
	divsd xmm0, xmm1
	cvttsd2si r11, xmm0
	add r11, 1

loop:
	movsd xmm4, xmm2			; a
	mulsd xmm4, xmm5			; a * i
	movsd [rsp], xmm4
	fld qword [rsp]
	fsin
	fstp qword [rsp]
	movsd xmm4, [rsp]			; sin(a*i)
	addsd xmm4, [one]			; sin(a*i)+1
	mulsd xmm4, xmm7			; (sin(a*i)+1)*width/2
	cvttsd2si r10, xmm4
	;add r10, 10					; r10 = x = (sin(a*i)+1)*width/2 + 10

	movsd xmm4, xmm3			; b
	mulsd xmm4, xmm5			; b * i
	movsd [rsp], xmm4
	fld qword [rsp]
	fsin
	fstp qword [rsp]
	movsd xmm4, [rsp]			; sin(b*i)
	addsd xmm4, [one]			; sin(b*i)+1
	mulsd xmm4, xmm7			; (sin(b*i)+1)*width/2
	cvttsd2si r12, xmm4
	;add r12, 10					; r12 = y = (sin(b*i)+1)*width/2 + 10

	mov r14, [width]
	imul r14, 3
	imul r14, r12

	mov r15, r10
	imul r15, 3

	mov r13, rcx
	add r13, r14
	add r13, r15
	add r13, 1
	mov byte [r13], 255

	addsd xmm5, [dt]
	dec r11
	jnz loop

end:
	movsd xmm6, [rbp-10]
	movsd xmm7, [rbp-12]
	add rsp, 6
	pop r15
	pop r14
	pop r13
	pop r12
	mov rsp, rbp
	pop rbp
	ret