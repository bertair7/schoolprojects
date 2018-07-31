    @intadd method
    @Ryan Blair, Austin McInnis

    .global intadd

intadd:
    /*parameters in r0, r1*/
    push {r7, lr}
    str r0, [sp, #-4]!
    str r1, [sp, #-4]!

carry:
    ldr r0, [sp, #4]
    ldr r1, [sp]
    eor r0, r1 @ sum in r0
    mov r7, r0 @ sum in r7
    ldr r0, [sp, #4]
    and r1, r0 @ carry now in r1
    cmp r1, #0
    beq end
    lsl r1, r1, #1
    str r7, [sp, #4] @ r7 back into stack for r0
    str r1, [sp]  @ carry back into stack for r1
    b carry

end:
    mov r0, r7
    str r1, [sp, #8]!
    pop {r7, pc}
