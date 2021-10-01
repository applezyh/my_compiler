.section .data


    .global print
    .global getint
    .global newline
    .global main
main:
    push {lr}
    sub sp, sp, #4
    mov r0, #1
    str r0, [sp, #0]
    ldr r0, [sp, #0]
    cmp r0, #6
    bne .L2
.L3:
    ldr r0, [sp, #0]
    cmp r0, #8
    beq .L1
.L2:
    ldr r0, [sp, #0]
    cmp r0, #1
    bne .L4
.L5:
    ldr r0, [sp, #0]
    cmp r0, #1
    beq .L1
.L4:
    ldr r0, [sp, #0]
    cmp r0, #3
    bne .L0
.L1:
    mov r0, #3
    str r0, [sp, #0]
.L0:
    ldr r0, [sp, #0]
    push {r0}
    bl print
    add sp, sp, #4
    bl newline
    add sp, sp, #4
    pop {pc}

//cost 0.173000ms.
