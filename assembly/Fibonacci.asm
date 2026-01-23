[org 0x0100]

jmp start

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


NumberPrint:
    push bp
    mov bp, sp

    mov ax, [bp + 4]

    cmp ax, 0
    mov word [es:di], 0x0730
    jmp return

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

        add si, 1

        jmp l2

continue:
    l3:
        cmp si, 0

        je return

        pop dx

        mov word [es:di], dx

        add di, 2

        sub si, 1

        jmp l3
    
   return:
    mov sp, bp
    pop bp
    ret 2


Fibonacci:
    push bp
    mov bp, sp

    mov cx, [bp + 4]      ; number of terms to print
    mov ax, 0             ; first term
    mov bx, 1             ; second term

    mov di, 0             ; start of video memory

FibLoop:
    cmp cx, 0
    je FibEnd

    push ax
    call NumberPrint

    mov dx, bx
    add bx, ax
    mov ax, dx

    mov word [es:di], 0x0720
    add di, 2

    dec cx
    jmp FibLoop

FibEnd:
    mov sp, bp
    pop bp
    ret 2


start:
    mov ax, 0xb800
    mov es, ax

    call clearScreen

    mov ax, 9
    push ax

    call Fibonacci


end:
    mov ax, 0x4c00
    int 0x21