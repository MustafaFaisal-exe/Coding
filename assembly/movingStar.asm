[org 0x0100]

jmp start

; PCB layout
; ax, bx, cx, dx, si, di, bp, sp, ip, cs, ds, ss, es, flags, next, dummy
;  0,  2,  4,  6,  8, 10, 12, 14, 16, 18, 20, 22, 24,    26,   28,    30

pcb: times 32*16 dw 0
stack: times 16*256 dw 0        ;space for 32 512 byte stacks
nextPcb: dw 1                   ;index of next free pcb
current: dw 0                   ;index of current pcb
lineNo: dw 0                    ;line number for next thread

clearScreen:
    push bp
    mov bp, sp

    mov di, 0
    clear:
        mov word [es:di], 0x0720
        add di, 2
        cmp di, 4000
        jne clear

    mov sp, bp
    pop bp
    ret

delay:
    push cx
    mov cx, 1 ; change the values to increase delay time
    delay_loop1:
        push cx
        mov cx, 0xFFFF
        delay_loop2:
            loop delay_loop2
        pop cx
        loop delay_loop1
    pop cx
    ret

MoveStar:
    push bp
    mov bp, sp

    mov cx, di             ;initial value of di

    display:
        firstHalf:
            call delay
            mov byte [es:di], 0x20
            mov byte [es:si], 0x20
            add di, 2
            sub si, 2
            mov byte [es:di], 0x2A
            mov byte [es:si], 0x2A
            cmp si, di
            jle secondHalf
            jmp firstHalf

        secondHalf:
            call delay
            mov byte [es:di], 0x20
            mov byte [es:si], 0x20
            sub di, 2
            add si, 2
            mov byte [es:di], 0x2A
            mov byte [es:si], 0x2A
            cmp di, cx
            jne secondHalf
            jmp display
                
initpcb:
    push bp
    mov bp, sp
    push ax
    push bx
    push cx
    push si

    mov bx, [nextPcb]
    cmp bx, 26
    je exit

    mov cl, 5
    shl bx, cl

    mov ax, [bp + 8]
    mov [pcb + bx + 18], ax
    mov ax, [bp + 6]
    mov [pcb + bx + 16], ax
    mov [pcb + bx + 22], ds
    mov word [pcb + bx + 24], 0xb800

    push ax
    mov ax, [lineNo]
    mov cx, 160
    mul cx
    mov word [pcb + bx + 10], ax
    add ax, 158
    mov word [pcb + bx + 8], ax
    pop ax

    mov si, [nextPcb]
    mov cl, 9
    shl si, cl
    add si, 256*2 + stack
    mov ax, [bp + 4]
    sub si, 2
    mov [si], ax
    sub si, 2
    mov [pcb + bx + 14], si


    mov word [pcb + bx + 26], 0x0200

    mov ax, [pcb + 28]
    mov [pcb + bx + 28], ax
    mov ax, [nextPcb]
    mov [pcb + 28], ax
    inc word [nextPcb]

    exit:
        pop si
        pop cx
        pop bx
        pop ax
        pop bp
        ret 6

    mov sp, bp
    pop bp
    ret

timer:
    ;save previous, restore new
    push ds
    push bx

    push cs
    pop ds

    mov bx, [current]
    mov cl, 5
    shl bx, cl

    ;Save previous
    mov [pcb + bx + 0], ax
    mov [pcb + bx + 4], cx
    mov [pcb + bx + 6], dx
    mov [pcb + bx + 8], si
    mov [pcb + bx + 10], di
    mov [pcb + bx + 12], bp
    mov [pcb + bx + 24], es

    pop ax
    mov [pcb + bx + 2], ax
    pop ax
    mov [pcb + bx + 20], ax
    pop ax
    mov [pcb + bx + 16], ax
    pop ax
    mov [pcb + bx + 18], ax
    pop ax
    mov [pcb + bx + 26], ax

    mov [pcb + bx + 22], ss
    mov [pcb + bx + 14], sp

    mov bx, [pcb + bx + 28]

    mov [current], bx

    mov cl, 5
    shl bx, cl

    mov cx, [pcb + bx + 4]
    mov dx, [pcb + bx + 6]
    mov si, [pcb + bx + 8]
    mov di, [pcb + bx + 10]
    mov bp, [pcb + bx + 12]
    mov sp, [pcb + bx + 14]
    mov ss, [pcb + bx + 22]
    mov es, [pcb + bx + 24]

    push word [pcb + bx + 26]
    push word [pcb + bx + 18]
    push word [pcb + bx + 16]
    push word [pcb + bx + 20]

    mov al, 0x20
    out 0x20, al

    mov ax, [pcb + bx + 0]
    mov bx, [pcb + bx + 2]
    pop ds
    iret

start:
    mov ax, 0xb800
    mov es, ax
    call clearScreen

    xor ax, ax
    mov es, ax

    cli
    mov word [es:8*4], timer
    mov word [es:8*4 + 2], cs
    sti

    mov ax, 0xb800
    mov es, ax

    nextKey:
        xor ah, ah          ;service 0 - get keyStroke
        int 0x16            ;bios keyboard services

        push cs             ;use current code segment
        mov ax, MoveStar
        push ax             ;use mytask as offset
        push word [lineNo]  ;thread parameter
        call initpcb        ;register the thread

        inc word [lineNo]   ;update line number

        jmp nextKey