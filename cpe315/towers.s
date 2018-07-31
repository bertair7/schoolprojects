	.arch armv6
	.fpu vfp
    	.align 2
	.text

    .global	print
print:
	stmfd	sp!, {r3, lr}
	mov	r3, r0
	mov	r2, r1
	ldr	r0, startstring
	mov	r1, r3
	bl	printf
	ldmfd	sp!, {r3, pc}

    .global	towers
towers:
   /* Save Registers */
    	push {r4, r5, lr} @Save Link Register 
   /* Save a copy of all 3 original parameters */
	sub sp, sp, #12 
	str r0, [sp, #8] @r0 - numDiscs
	str r1, [sp, #4] @r1 - start
	str r2, [sp] @r2 - goal
if:
   /* Compare numDisks with 2 or (numDisks - 2)*/
	cmp r0, #2
   /* Check if less than, else branch to else */
   	bge else
   /* set start to start for printing */
	ldr r0, [sp, #4]
   /* set goal to goal for printing */
	ldr r1, [sp]
   /* call print function */
	bl print
   /* Set return register to 1 */
	mov r0, #1
   /* branch to endif */
	b endif
else:
   /* Use a saved variable for peg and set it to 6 */
	mov r5, #6 @r5 - peg
   /* Subract start from peg and store to itself */
	sub r5, r5, r1
   /* Subtract goal from peg and store to itself (peg = 6 - start - goal)*/
	sub r5, r5, r2
   /* subtract 1 from original numDisks and store it to numDisks parameter */
    ldr r0, [sp, #8]
	sub r0, r0, #1
   /* Set goal as peg */
	mov r2, r5
   /* Call towers function */
	bl towers
   /* Save result to saved variable for total steps */
	mov r4, r0 @ r4 - steps
   /* Set numDiscs to 1 */
	mov r0, #1
   /* Set start to original start */
	ldr r1, [sp, #4]
   /* Set goal to original goal */
	ldr r2, [sp]
   /* Call towers function */
	bl towers
   /* Add result to total steps so far */
   	add r4, r4, r0
   /* Set numDisks to original numDisks - 1 */
	ldr r0, [sp, #8]
    	sub r0, r0, #1
   /* set start to peg */
    	mov r1, r5
   /* set goal to original goal */
	ldr r2, [sp]
   /* Call towers function */
    	bl towers
   /* Add result to total steps so far and save it to return register */
	add r4, r4, r0
	mov r0, r4

endif:
   /* Restore Registers */
	add sp, sp, #12
	pop {r4, r5, pc}

    .global	main
main:
	str	lr, [sp, #-4]!
	sub	sp, sp, #20
	ldr	r0, printdata
	bl	printf
	ldr	r0, printdata+4
	add	r1, sp, #12
	bl	__isoc99_scanf
	ldr	r0, [sp, #12]
	mov	r1, #1
	mov	r2, #3
	bl	towers
	str	r0, [sp]
	ldr	r0, printdata+8
	ldr	r1, [sp, #12]
	mov	r2, #1
	mov	r3, #3
	bl	printf
	mov	r0, #0
	add	sp, sp, #20
	ldr	pc, [sp], #4
end:

startstring:
	.word	string0

printdata:
	.word	string1
	.word	string2
	.word	string3

string0:
	.ascii	"Move from peg %d to peg %d\012\000"
string1:
	.ascii	"Enter the number of disks to be moved: \000"
string2:
	.ascii	"%d\000"
	.space	1
string3:
	.ascii	"\012%d disks moved from peg %d to peg %d in %d step"
	.ascii	"s\012\000"
