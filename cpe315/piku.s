.syntax unified
.global main
main:
	push {ip, lr}
	ldr r0, =line1
	bl printf
	ldr r0, =line2
	bl printf
	ldr r0, =line3
	bl printf

	mov r0, #0
	pop {ip, pc}

line1:
	.asciz "Hi Raspberry Pi.\n"

line2:
	.asciz "We are Austin and Ryan.\n"

line3:
	.asciz "Welcome to our world!\n"
