[org 0x0100]

jmp start

line: times 80 dw 0

RigthAlign:
    push bp
    mov bp, sp

    mov dx, 0

    mov ax, 0x0100
    mov es, ax
    mov ax, 0xb800
    mov ds, ax

    Right:
        mov ax, 0x0100
        mov es, ax

        mov ax, 0xb800
        mov ds, ax

        mov si, dx

        mov di, line

        mov cx, 80

        rep movsw

        ;got the row. now manipulate it

        ;reverse loop and find black spaces and shift right the row 

        ;shifting the row towards right once

        mov ax, 0x0100
        mov ds, ax

        mov ax, 0xb800
        mov es, ax

        mov cx, 0 
         
         ;Shift right the string until the spaces on the right no longer exists

        l1:
            mov si, line
            mov bx, 158

            cmp cx, 80
            je continue

            add cx, 1

            mov ax, [ds:si + bx]
            cmp ax, 0x0720
            jne continue
 
            shift_right:
                mov ax, [ds:si + bx - 2]
                mov [ds:si + bx], ax

                sub bx, 2
                cmp bx, 0
                jne shift_right

            mov word [ds:si + bx], 0x0720
            jmp l1


        continue:

        ;printing the row in another place

        mov si, line

        mov di, dx

        mov cx, 80

        rep movsw

        add dx, 160

        cmp dx, 4000

        jne Right
    

    mov sp, bp
    pop bp
    ret

start:

    mov ax, [line]

    call RigthAlign


end:
    mov ax, 0x4c00
    int 0x21