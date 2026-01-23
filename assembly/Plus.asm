[org 0x0100]

jmp start

clearScreen:
    push bp
    mov bp, sp

    mov di, 0

    l1:
        mov word [es:di], 0x0720

        add di, 2

        cmp di, 4000

        jne l1

    mov sp, bp
    pop bp
    ret

Plus:
    push bp
    mov bp, sp

    mov cx, [bp + 6]          ;ax = verticle length
    mov bx, [bp + 4]          ;bx = horizontal length

    ;horizontal Line

    mov di, 1280
    mov si, 0

    hor:
        mov word [es:di], 0x022A

        add di, 2
        add si, 1

        cmp si, bx
        jne hor

    ;Verticle Line

    mov di, 18
    mov si, 0

    ver:
        mov word [es:di], 0x022A

        add di, 160

        add si, 1

        cmp si, cx

        jne ver
    
    mov sp, bp
    pop bp
    ret 2

start:

    mov ax, 0xb800
    mov es, ax

    call clearScreen

    push 20             ; Verical
    push 40             ; Horizontal

    call Plus

    jmp end


end:
    mov ax, 0x4c00
    int 0x21