[org 0x0100]

jmp start

height: dw 0
width: dw 0

clearScreen:
    push bp
    mov bp, sp

    mov di, 0
    
    loopClr:
        mov word [es:di], 0x0720

        add di, 2

        cmp di, 4000

        jne loopClr

    mov sp, bp
    pop bp
    ret

ClearArea:
    push bp
    mov bp, sp

    ;[bp + 4] = right
    ;[bp + 6] = bottom
    ;[bp + 8] = left
    ;[bp + 10] = top
    
    mov ax, 160
    mul word [bp + 10]

    add ax, [bp + 8]

    mov bx, 160

    sub bx, [bp + 4]

    sub bx, [bp + 8]

    mov [width], bx

    mov bx, ax                ;saving the value of ax

    mov ax, [bp + 6]     ; bottom
    mov cx, ax
    mov ax, 25
    sub ax, cx
    sub ax, [bp + 10]    ; bottom - top
    mov [height], ax

    mov dx, 0                   ;dx = height counter

    mov di, bx

    mov cx, 0

    h:
        w:
            mov word [es:di], 0x7020
            add di, 2
            add cx, 2
            cmp cx, [width]
            jl w

        add bx, 160
        mov di, bx
        mov cx, 0

        add dx, 1
        cmp dx, [height]
        jl h

    mov sp, bp
    pop bp
    ret 4

start:

    mov ax, 0xB800
    mov es, ax

    call clearScreen

    push 0             ;top
    push 0            ;left
    push 12            ;bottom
    push 0            ;right

    call ClearArea


end:
    mov ax, 0x4c00
    int 0x21