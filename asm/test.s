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
    str r0, [sp, #0]
    ldr r0, [sp, #0]
    push {r0}
    bl print
    add sp, sp, #4
    bl newline
    add sp, sp, #4
    pop {pc}

//cost 0.318000ms.
