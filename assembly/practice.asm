[org 0x0100]

jmp start

hours: db 0
minutes: db 0
seconds: db 0
oldisr: dd 0
ticks: db 0

clearScreen:
    push bp
    mov bp, sp
    push ax
    push es

    mov ax, 0xb800
    mov es, ax

    mov ax, 0x0720
    mov cx, 4000

    xor di, di

    rep stosw

    pop es
    pop ax
    mov sp, bp
    pop bp
    ret

PrintNum:
    push bp
    mov bp, sp
    push es
    push ax
    push bx
    push cx
    push dx
    push di

    mov ax, 0xb800
    mov es, ax

    mov ax, [bp + 4]
    mov di, [bp + 6]
    mov bx, 10
    mov cx, 0

    nextDigit:
        mov dx, 0
        div bx
        add dl, 0x30
        push dx
        inc cx
        cmp ax, 0
        jnz nextDigit

    nextPos:
        pop dx
        mov dh, 0x07
        mov [es:di], dx
        add di, 2
        loop nextPos

    pop di
    pop dx
    pop cx
    pop bx
    pop ax
    pop es
    pop bp
    ret 4

clockDisplay:
    push bp
    mov bp, sp
    push ax
    push es

    mov ax, 0xb800
    mov es, ax

    xor ax, ax
    mov al, [seconds]
    push ax
    push 0
    call PrintNum
    
    ;mov word [es:4], 0x073A
    
    xor ax, ax
    mov al, [minutes]
    push ax
    push 36
    call PrintNum
    
    ;mov word [es:10], 0x073A
    
    xor ax, ax
    mov al, [seconds]
    push ax
    push 70
    call PrintNum

    pop es
    pop ax
    mov sp, bp
    pop bp
    ret

timer:
    push ax
    push bx
    push cx
    push dx
    push ds
    push es

    push cs
    pop ds

    inc byte [ticks]
    cmp byte [ticks], 18
    jne exit

    mov byte [ticks], 0

    inc byte [seconds]
    cmp byte [seconds], 60
    jb  display          ; if seconds < 60 → just display

    mov byte [seconds], 0
    inc byte [minutes]
    cmp byte [minutes], 60
    jb  display          ; if minutes < 60 → display

    mov byte [minutes], 0
    inc byte [hours]
    cmp byte [hours], 24
    jb  display          ; if hours < 24 → display

    mov byte [hours], 0  ; reset after 23:59:59

    display:
        call clockDisplay

    exit:
        mov al, 20h
        out 20h, al

        pop es
        pop ds
        pop dx
        pop cx
        pop bx
        pop ax
        iret

start:

    call clearScreen

    xor ax, ax
    mov es, ax

    cli
    mov word [es:8*4], timer
    mov [es:8*4 + 2], cs
    sti

    mov dx, (end - start + 256) / 16 + 1
    mov ax, 0x3100
    int 0x21

end: