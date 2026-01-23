[org 0x0100]

jmp start

n: dw 5
fact: dw 0

factorial:
    push bp
    mov bp, sp

    mov ax, [bp + 4]

    cmp ax, 1
    jne recurse
    mov ax, 1
    jmp done


recurse:
    dec ax
    push ax
    call factorial

    mov bx, [bp + 4]
    mul bx

done:
    pop bp
    ret 2

start:
    mov ax, [n]
    push ax
    call factorial
    mov [fact], ax


end:
    mov ax, 0x4c00
    int 0x21