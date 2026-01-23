[org 0x0100]

jmp start

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

clrscr:
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

MovingStar:
    push bp
    mov bp, sp

    mov di, 0

    move:
        call delay

        mov word [es:di], 0x072A

        mov word [es:di - 2], 0x0720

        add di, 2

        cmp di, 4000

        jne move
    
    mov sp, bp
    pop bp
    ret

start:
    mov ax, 0xb800
    mov es, ax

    call clrscr

    call MovingStar


end:
    mov ax, 0x4c00
    int 0x21