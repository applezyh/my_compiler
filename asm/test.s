    .global print
    .global newline
    .global getint
    .global a
    .global main
a:
    push {lr}
    ldr r0, [sp, #12]
    push {r0}
    ldr r0, [sp, #12]
    pop {r1}
    mul r0, r1, r0
    push {r0}
    ldr r0, [sp, #8]
    pop {r1}
    mul r0, r1, r0
    add sp, sp, #0
    pop {r1}
    push {r0}
    mov pc, r1
main:
    push {lr}
    sub sp, sp, #4
    mov r0, #1
    push {r0}
    mov r0, #2
    push {r0}
    mov r0, #3
    push {r0}
    bl a
    pop {r0}
    add sp, sp, #12
    str r0, [sp, #0]
    sub sp, sp, #4
    mov r0, #0
    str r0, [sp, #0]
    sub sp, sp, #4
    mov r0, #122
    str r0, [sp, #0]
    ldr r0, [sp, #0]
    push {r0}
    bl print
    add sp, sp, #4
    bl newline
    add sp, sp, #0
    ldr r0, [sp, #8]
    push {r0}
    bl print
    add sp, sp, #4
    bl newline
    add sp, sp, #0
    add sp, sp, #12
    pop {r0}
    mov r1, #0
    push {r1}
    mov pc, r0

//cost 0.161000ms.
