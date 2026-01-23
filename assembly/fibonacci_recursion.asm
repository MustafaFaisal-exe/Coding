[org 0x0100]

jmp start

n: dw 7

fib: dw 0

fibonacci:
    push bp
    mov bp, sp

    mov ax, [bp + 4]

    cmp ax, 0
    je zero
    cmp ax, 1
    je one

    mov bx, ax
    dec bx
    push bx
    call fibonacci
    mov cx, ax

    mov bx, [bp + 4]
    sub bx, 2
    push bx
    call fibonacci

    add ax, cx

    jmp end_func

zero:
    mov ax, 0
    jmp end_func

one:
    mov ax, 1

end_func:
    pop bp
    ret 2 

start:
    mov ax, [n]
    push ax
    call fibonacci

    mov [fib], ax


end:
    mov ax, 0x4c00
    int 0x21