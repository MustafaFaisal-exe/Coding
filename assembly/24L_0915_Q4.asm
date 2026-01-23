[org 0x0100]

jmp start

row1: times 80 dw 0
row2: times 80 dw 0

swap:
    push bp
    mov bp, sp

    mov dx, 0

    l1:
        mov ax, 0x0100
        mov es, ax

        mov ax, 0xb800
        mov ds, ax

        mov si, dx

        mov di, row1

        mov cx, 80

        rep movsw       ;copy row1

        mov si, dx

        add si, 160

        mov di, row2

        mov cx, 80      ;copy row2

        rep movsw

        mov ax, 0x0100
        mov ds, ax

        mov ax, 0xb800
        mov es, ax

        mov di, dx

        add di, 160

        mov si, row1

        mov cx, 80

        rep movsw

        mov di, dx

        mov si, row2

        mov cx, 80
        rep movsw

        add dx, 320

        cmp dx, 4000

        jl l1

    mov sp, bp
    pop bp
    ret


start:
    mov ax, 0xb800
    mov es, ax

    mov ax, [row1]

    mov ax, [row2]

    call swap


end:
    mov ax, 0x4c00
    int 0x21