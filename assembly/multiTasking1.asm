[org 0x0100]

jmp start

; ax, bx, ip, cs, flags

taskStates: dw 0, 0, 0, 0, 0   ;task 0 registers
            dw 0, 0, 0, 0, 0   ;task 1 registers
            dw 0, 0, 0, 0, 0   ;task 2 registers
            dw 0, 0, 0, 0, 0   ;task 3 registers
            dw 0, 0, 0, 0, 0   ;task 4 registers

current:    db 0               ;index of current task
chars:      db '\|/-'          ;shapes to form a circle

; 1st task to be multitasked

taskOne:
    mov al, [chars + bx]
    mov [es:0], al
    inc bx
    and bx, 3
    jmp taskOne

; 2nd task to be multitasked

taskTwo:
    mov al, [chars + bx]
    mov [es:158], al
    inc bx
    and bx, 3
    jmp taskTwo

taskThree:
    mov al, [chars + bx]
    mov [es:3840], al
    inc bx
    and bx, 3
    jmp taskThree

taskFour:
    mov al, [chars + bx]
    mov [es:3998], al
    inc bx
    and bx, 3
    jmp taskFour


; Timer isr

timer:
    push ax
    push bx

    mov bl, [cs:current]           ;read index of current task
    mov ax, 10                     ;space used by one task state
    mul bl                         ;multiply to get start of task state
    mov bx, ax                     ;load start of task state in bx

    pop ax                             ;read original value of bx
    mov [cs:taskStates + bx + 2], ax   ;space for saving bx
    pop ax                             ;read original value of ax
    mov [cs:taskStates + bx], ax       ;space for saving bx
    pop ax                             ;read original value of ip
    mov [cs:taskStates + bx + 4], ax   ;space for saving ip
    pop ax                             ;read original value of cs
    mov [cs:taskStates + bx + 6], ax   ;space for saving cs
    pop ax                             ;read original value of flags
    mov [cs:taskStates + bx + 8], ax   ;space for saving flags

    inc byte [cs:current]          ;update current task index
    cmp byte [cs:current], 5       ;is task index out of range?
    jne SkipReset                  ;no, proceed
    mov byte [cs:current], 0       ;yes, reset to task 0

    SkipReset:
        mov bl, [cs:current]       ;read index of current task
        mov ax, 10                 ;space used by one task state
        mul bl                     ;multiply to get to the start of task state
        mov bx, ax                 ;load state of task state in bx

        mov al, 0x20
        out 0x20, al               ;send EOI to PIC

        push word [cs:taskStates + bx + 8]       ;flags of new task
        push word [cs:taskStates + bx + 6]       ;cs of new task
        push word [cs:taskStates + bx + 4]       ;ip of new task
        mov ax, [cs:taskStates + bx + 0]         ;ax of new task
        mov bx, [cs:taskStates + bx + 2]         ;bx of new task

        iret

start:
    mov word [taskStates + 10 + 4], taskOne      ;initialize ip
    mov [taskStates + 10 + 6], cs                ;initialize cs
    mov word [taskStates + 10 + 8], 0X0200       ;initialize flags

    mov word [taskStates + 20 + 4], taskTwo      ;initialize ip
    mov [taskStates + 20 + 6], cs                ;initialize cs
    mov word [taskStates + 20 + 8], 0x0200       ;initialize flags

    mov word [taskStates + 30 + 4], taskThree    ;initialize ip
    mov [taskStates + 30 + 6], cs                ;initialize cs
    mov word [taskStates + 30 + 8], 0X0200       ;initialize flags

    mov word [taskStates + 40 + 4], taskFour     ;initialize ip
    mov [taskStates + 40 + 6], cs                ;initialize cs
    mov word [taskStates + 40 + 8], 0X0200       ;initialize flags

    mov byte [current], 0                        ;set current task index

    xor ax, ax
    mov es, ax
    cli
    mov word [es:8*4], timer
    mov [es:8*4 + 2], cs                         ;hook timer interrupt
    mov ax, 0xb800
    mov es, ax
    xor bx, bx
    Sti
    jmp $

end:
    mov ax, 0x4c00
    int 0x21