    @intmul method
    @Ryan Blair, Austin McInnis

    .global intmul

intmul:
    /*parameters in r0, r1*/
    push {r7, lr}
    str r0, [sp, #-4]!
    str r1, [sp, #-4]!

product:
    ldr r0, [sp, #4] @ r0 - multiplicand
    ldr r1, [sp] @ r1 - multiplier
    cmp r1, #0
    beq end
    and r1, r1, #1
    cmp r1, #1
    bne shift
    mov r1, r0
    mov r0, r7
    bl intadd
    mov r7, r0 @ product in r7

shift:
    ldr r0, [sp, #4]
    ldr r1, [sp]
    lsl r0, r0, #1
    lsr r1, r1, #1
    str r0, [sp, #4]
    str r1, [sp]
    b product

end:
    mov r0, r7
    ldr r1, [sp, #8]!
    pop {r7, pc}
