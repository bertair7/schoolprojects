    .syntax unified

    @ Template file for Lab 3
    @ partner names here
    @ Ryan Blair, Austin McInnis
    .arch armv6
    .fpu vfp 

    @ --------------------------------
    .global main
main:
    @ driver function main lives here, modify this for your other functions
    push {lr}
    str r0, [sp, #-16]!
    str r1, [sp, #-4]!

loop:
    ldr r0, =prompt1
    mov r1, sp
    bl printf
    ldr r0, =scanint
    mov r1, sp
    bl scanf
    ldr r5, [sp]        @ r5 = 1st number

two:
    ldr r0, =prompt2
    mov r1, sp
    bl printf
    ldr r0, =scanint
    mov r1, sp
    bl scanf
    ldr r6, [sp]        @ r6 = 2nd number

sign:
    ldr r0, =prompt3    
    mov r1, sp
    bl printf
    ldr r0, =scanchar
    mov r1, sp
    bl scanf
    ldr r1, =myadd
    ldrb r1, [r1]       @ r1 = '+'
    ldrb r0, [sp]
    cmp r0, r1
    bne not_add
    mov r0, r5
    mov r1, r6
    bl intadd
    b good

not_add:
    ldr r1, =mysub
    ldrb r1, [r1]
    cmp r0, r1
    bne not_sub
    mov r0, r5
    mov r1, r6
    bl intsub
    b good

not_sub:
    ldr r1, =mymul
    ldrb r1, [r1]
    cmp r0, r1
    bne bad
    mov r0, r5
    mov r1, r6
    bl intmul

good:
    mov r2, r0      @ result in r2
    ldr r0, =result
    mov r1, r2
    bl printf
    b next

bad:
    ldr r0, =invalid
    mov r1, sp
    bl printf

next:
    ldr r0, =again
    mov r1, sp
    bl printf
    @ You'll need to scan characters for the operation and to determine
    @ if the program should repeat.
    @ To scan a character, and compare it to another, do the following
    ldr     r0, =scanchar
    mov     r1, sp          @ Save stack pointer to r1, you must create space
    bl      scanf           @ Scan user's answer
    ldr     r1, =yes        @ Put address of 'y' in r1
    ldrb    r1, [r1]        @ Load the actual character 'y' into r1
    ldrb    r0, [sp]        @ Put the user's value in r0
    cmp     r0, r1          @ Compare user's answer to char 'y'
    beq     loop            @ branch to appropriate location

    /*mov r0, #1*/
    ldr r1, [sp, #20]!
    pop {pc}

yes:
    .byte   'y'
myadd:
    .byte   '+'
mysub:
    .byte   '-'
mymul:
    .byte   '*'
scanchar:
    .asciz  " %c"
scanint:
    .ascii  "%d"
prompt1:
    .ascii  "Enter number 1: \000"
prompt2: 
    .ascii  "Enter number 2: \000" 
prompt3:
    .ascii  "Enter operation: \000"
result: 
    .ascii  "Result is: %d\000"
invalid:
    .ascii  "Invalid Operation Entered. \000"
again:
    .ascii  "\012Again? \000"
