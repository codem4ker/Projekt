section .data
pi:	dq 3.1415926535
dt: dq 0.0001

section .text
global drawCurve

drawCurve:
	push rbp
	mov rbp, rsp

	mov rsp, rbp
	pop rbp
	ret