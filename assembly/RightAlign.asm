[org 0x0100]

jmp start

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

start:


end:
    mov ax, 0x4c00
    int 0x21