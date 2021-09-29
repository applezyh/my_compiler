.section .data
a:
    .word 100


    .global print
    .global getint
    .global newline
    .global f
    .global main
f:
    push {lr}
    ldr r0, [sp, #4]
    cmp r0, #1
    beq .L2
    ldr r0, [sp, #4]
    cmp r0, #2
    bne .L1
.L1:
    add sp, sp, #0
    pop {r0}
    mov r1, #1
    push {r1}
    mov pc, r0
    b .L2
.L0:
    ldr r0, [sp, #4]
    push {r0}
    mov r1, #1
    pop {r2}
    sub r1, r2, r1
    push {r1}
    bl f
    pop {r0}
    add sp, sp, #4
    push {r0}
    ldr r0, [sp, #8]
    push {r0}
    mov r1, #2
    pop {r2}
    sub r1, r2, r1
    push {r1}
    bl f
    pop {r0}
    add sp, sp, #4
    pop {r1}
    add r0, r1, r0
    add sp, sp, #0
    pop {r1}
    push {r0}
    mov pc, r1
.L2:
main:
    push {lr}
    sub sp, sp, #4
    mov r0, #20
    push {r0}
    bl f
    pop {r0}
    add sp, sp, #4
    str r0, [sp, #0]
    ldr r0, [sp, #0]
    push {r0}
    bl print
    add sp, sp, #4
    bl newline
    add sp, sp, #4
    pop {pc}

//cost 0.177000ms.
