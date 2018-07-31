    @intsub method
    @Ryan Blair, Austin McInnis

    .global intsub

intsub:
    /*parameters in r0, r1*/
    push {r7, lr}
    str r0, [sp, #-4]!
    str r1, [sp, #-4]!

borrow:
    ldr r0, [sp, #4]
    ldr r1, [sp]
    eor r0, r1 @ difference in r0
    mov r7, r0 @ difference in r7
    ldr r0, [sp, #4]
    mvn r0, r0 @ bitwise logical not
    and r1, r0 @ borrow now in r1
    cmp r1, #0
    beq end
    lsl r1, r1, #1
    str r7, [sp, #4] @ r7 back into stack for r0
    str r1, [sp]  @ borrow back into stack for r1
    b borrow

end:
    mov r0, r7
    ldr r1, [sp, #8]!
    pop {r7, pc}
