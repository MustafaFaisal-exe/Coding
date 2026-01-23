[org 0x0100]

jmp start

zero:
    mov word [es:di], 0x0730
    jmp end

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

start:
    mov ax, 0xb800
    mov es, ax

    call clearScreen

    ;printing 67 on console
    mov di, 0
    mov ax, 65535
    cmp ax, 0
    je zero
    mov cx, ax
    mov bx, 10
    mov si, 0
    l2:
        mov dx, 0
        cmp cx, 0

        je continue
        div bx

        mov cx, ax

        add dl, 0x30              
        mov dh, 0x07 

        push dx

        add di, 2
        add si, 1

        jmp l2

continue:
    mov di, 0
    l3:
        cmp si, 0

        je end

        pop dx

        mov word [es:di], dx

        add di, 2

        sub si, 1

        jmp l3


end:
    mov ax, 0x4c00
    int 0x21