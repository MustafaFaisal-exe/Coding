[org 0x0100]

jmp start

printA:
    mov ax, 0x7041

MakeBorders:
    push bp
    mov bp, sp

    mov ax, 0xB800
    mov es, ax
    mov di, 0

    clear:
        mov word[es:di], 0x7020
        add di, 2
        cmp di, 4000
        jne clear
    
    
    ;Printing A
    ;Horizontal layers
    mov di, 0
    
    hor:
        mov word [es:di], 0x7441
        mov word [es:di + 3680], 0x7441

        mov word [es:di + 160], 0xF042
        mov word [es:di + 3680 - 160], 0xF042

        add di, 2

        cmp di, 160

        jne hor

    ;Verticle lines

    mov di, 160

    ver:
        mov word [es:di], 0x7441
        mov word [es:di + 158], 0x7441

        mov word [es:di + 2], 0xF042
        mov word [es:di + 158 - 2], 0xF042

        add di, 160

        cmp di, 3680

        jne ver
    
    mov sp, bp
    pop bp
    ret

start:
    call MakeBorders

end:
    mov ax, 0x4c00
    int 0x21