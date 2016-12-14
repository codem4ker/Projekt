section .data
	d_pi:	dq 6.283185307
	dt: dq 0.0001
	height: dd 768
	widht: dd 768

section .text
global drawCurve

drawCurve:
	push rbp
	mov rbp, rsp

	test rdx, rdx			; rdx - a
	jz a_zero
	test r8, r8
	jz b_zero
	movsd xmm1, [d_pi]
	cvtsi2sd xmm2, r8
	mulsd xmm1, xmm2
	movsd xmm0, xmm1
	jmp exit

a_zero:
	test r8, r8				; r8 - b
	jz ab_zero
	movsd xmm1, [d_pi]
	cvtsi2sd xmm2, r8
	divsd xmm1, xmm2
	movsd xmm0, xmm1
	jmp exit

ab_zero:
	movsd xmm0, [dt]			; xmm0 - t
	jmp exit

b_zero:
	movsd xmm1, [d_pi]
	cvtsi2sd xmm2, rdx
	divsd xmm1, xmm2
	movsd xmm0, xmm1

exit:
	mov rsp, rbp
	pop rbp
	ret