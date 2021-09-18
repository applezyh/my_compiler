    .global getchar
    .global getint
getint:
    push {lr}
    bl getchar
	sub r0, #48
    pop {r1}
	push {r0}
    mov pc, r1

//cost 0.047000ms.
