.section .data


    .global print
    .global getint
    .global newline
    .global main
main:
    push {lr}
    sub sp, sp, #4
    movw r0, #57600
    movt r0, #1525
    mov r1, #0
    sub r0, r1, r0
    str r0, [sp, #0]
    ldr r0, [sp, #0]
    push {r0}
    bl print
    add sp, sp, #4
    bl newline
    add sp, sp, #4
    pop {r0}
    mov r1, #0
    push {r1}
    mov pc, r0

//cost 3.411000ms.
