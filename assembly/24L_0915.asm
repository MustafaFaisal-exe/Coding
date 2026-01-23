[org 0x0100]

jmp start 

loseMessage: db 'Game Lost', 0
winMessage: db 'Game Win', 0
message: db 'Press Enter to play again...Press Escape to exit', 0 
position: dw 3760
direction: db 'r'
ticks: db 0
oldtimerisr: dd 0
oldkbisr: dd 0
collision: db 0

clearScreen:
    push bp
    mov bp, sp
    pusha

    mov ax, 0xb800
    mov es, ax

    mov di, 0

    clear:
        mov word [es:di], 0x7020
        add di, 2
        cmp di, 4000
        jne clear

    popa
    mov sp, bp
    pop bp
    ret

draw_obstacles:
    push bp
    mov bp, sp
    pusha

    mov ax, 0xb800
    mov es, ax

    mov cx, 7                                ;cx = size of obstacles

    ;parameters
    ;(row, column, verticle/horizontal)
    mov ax, word [bp + 4]   ; al = row
    mov bl, 160
    mul bl                    ; ax = row * 160
    mov bx, [bp + 6]         ; bx = column
    shl bx, 1                 
    mov dx, [bp + 8]         ; dx = vertical/horizontal (0 = vertical, 1 = horizontal)

    cmp dx, 0
    jne horizontal_alignment
    mov dx, 160        ; vertical step
    jmp continueDisplay
    horizontal_alignment:
    mov dx, 2          ; horizontal step

    continueDisplay:
        mov di, ax
        add di, bx

    display:
        mov word [es:di], 0x2220
        add di, dx
        dec cx
        cmp cx, 0
        jne display

    popa
    mov sp, bp
    pop bp
    ret

place_obstacles:
    push bp
    mov bp, sp
    pusha

    mov ax, 0xb800
    mov es, ax

    ;Boundary

    ;Horizontal
    mov di, 0

    hor:
        mov word [es:di], 0x6020
        mov word [es:di + 3840], 0x6020
        add di, 2
        cmp di, 160
        jne hor

    ;Verticle
    mov di, 0
    ver:
        mov word [es:di], 0x6020
        add di, 160
        cmp di, 4000
        jne ver

    ;Verticle Right obstacle (green)
    mov di, 158
    right_border:
        mov word [es:di], 0x2220
        mov word [es:di - 2], 0x2220
        add di, 160
        cmp di, 4158
        jne right_border

    ;Red goal
    mov di, 0
    goal:
        mov word [es:di], 0x4420
        mov word [es:di + 160], 0x4420
        add di, 2
        cmp di, 8
        jne goal
    
    ; Obstacle 1 - Vertical far left
    push 0
    push 10
    push 4
    call draw_obstacles
    add sp, 6

    ; Obstacle 2 - Horizontal upper left
    push 1
    push 28
    push 6
    call draw_obstacles
    add sp, 6

    ; Obstacle 3 - Horizontal lower middle-left
    push 1
    push 32
    push 13
    call draw_obstacles
    add sp, 6

    ; Obstacle 4 - Vertical center
    push 0
    push 45
    push 6
    call draw_obstacles
    add sp, 6

    ; Obstacle 5 - Vertical right-center
    push 0
    push 60
    push 4
    call draw_obstacles
    add sp, 6

    ; Obstacle 6 - Horizontal upper right
    push 1
    push 66
    push 6
    call draw_obstacles
    add sp, 6

    popa
    mov sp, bp
    pop bp
    ret

timer:
    pusha

    inc byte [ticks]

    cmp byte [ticks], 2
    jne return_timer_isr
    
    mov byte [ticks], 0

    push es
    push di
    mov ax, 0xb800
    mov es, ax
    mov di, [position]
    mov ah, [es:di + 1]      ; Get existing attribute
    and ah, 0xF0             ; Keep background
    or ah, 0x07              ; Set to space color
    mov al, ' '              ; Space character
    mov [es:di], ax
    pop di
    pop es

    cmp byte [direction], 'r'
    jne cmp_left
    add word [position], 2
    jmp move_done

    cmp_left:
        cmp byte [direction], 'l'
        jne cmp_down
        sub word [position], 2
        jmp move_done

    cmp_down:
        cmp byte [direction], 'd'
        jne cmp_up
        add word [position], 160
        jmp move_done

    cmp_up:
        cmp byte [direction], 'u'
        sub word [position], 160
        jmp move_done

    move_done:
        call display_star

    return_timer_isr:
        popa
        jmp far [cs:oldtimerisr]


kbisr:
    push ax
    in al, 0x60

    cmp al, 0x48
    jne check_down
    mov byte [direction], 'u'
    jmp return_kb_isr

    check_down:
        cmp al, 0x50
        jne check_left
        mov byte [direction], 'd'
        jmp return_kb_isr

    check_left:
        cmp al, 0x4B
        jne check_right
        mov byte [direction], 'l'
        jmp return_kb_isr

    check_right:
        cmp al, 0x4D
        jne check_releases
        mov byte [direction], 'r'
        jmp return_kb_isr

    check_releases:
        cmp al, 0xC8
        je return_kb_isr
        cmp al, 0xD0
        je return_kb_isr
        cmp al, 0xCB
        je return_kb_isr
        cmp al, 0xCD
        je return_kb_isr

    return_kb_isr:
        mov al, 0x20
        out 0x20, al
        pop ax
        iret

display_star:
    push ax
    push bx
    push es

    mov ax, 0xb800
    mov es, ax
    
    mov bx, [position]
    
    ; existing attribute
    mov ah, [es:bx + 1]
    and ah, 0xF0

    cmp ah, 0x60          ; check for orange background
    jne skip_orange
    call change_direction
    jmp continue
    skip_orange:
        ;check collisions
        cmp ah, 0x20
        jne next_collision
        mov byte [collision], 1
        jmp continue

    next_collision:
        cmp ah, 0x40
        jne continue
        mov byte [collision], 2

    continue:
        or ah, 0x01             ; Set foreground to blue
        mov al, '*'
        mov [es:bx], ax

    pop es
    pop bx
    pop ax
    ret

lose:
    push ax
    push es

    call clearScreen

    mov ah, 0x13
    mov al, 1
    mov bh, 0
    mov bl, 0x70
    mov dx, 0x0C23
    mov cx, 9
    push cs
    pop es
    mov bp, loseMessage
    int 0x10

    pop es
    pop ax
    ret

win:
    push ax
    push es

    call clearScreen

    mov ah, 0x13
    mov al, 1
    mov bh, 0
    mov bl, 0x70
    mov dx, 0x0C23
    mov cx, 8
    push cs
    pop es
    mov bp, winMessage
    int 0x10

    pop es
    pop ax
    ret

change_direction:

    mov al, [direction]

    cmp al, 'u'
    jne left
    mov byte [direction], 'd'
    jmp done

    left:
        cmp al, 'l'
        jne down
        mov byte [direction], 'r'
        jmp done

    down:
        cmp al, 'd'
        jne done
        mov byte [direction], 'u'

    done:
        ret

start:
    call clearScreen
    call place_obstacles

    xor ax, ax
    mov es, ax

    cli
    mov ax, [es:9*4]
    mov [oldkbisr], ax
    mov ax, [es:9*4 + 2]
    mov [oldkbisr + 2], ax

    mov ax, [es:8*4]
    mov [oldtimerisr], ax
    mov ax, [es:8*4 + 2]
    mov [oldtimerisr + 2], ax

    mov word [es:8*4], timer
    mov word [es:8*4 + 2], cs

    mov word [es:9*4], kbisr
    mov word [es:9*4 + 2], cs
    sti

    call display_star

    l1:
        cmp byte [collision], 0
        je l1
        
    ;collision detected
    ;collision = 1 : collided with obstacle
    ;collision = 2 : collided with goal

    cmp byte [collision], 1
    jne check_win
    call lose
    jmp end

    check_win:
        cmp byte [collision], 2
        call win

end:
    cli
    xor ax, ax
    mov es, ax
    
    mov ax, [oldkbisr]
    mov [es:9*4], ax
    mov ax, [oldkbisr + 2]
    mov [es:9*4 + 2], ax
    
    mov ax, [oldtimerisr]
    mov [es:8*4], ax
    mov ax, [oldtimerisr + 2]
    mov [es:8*4 + 2], ax
    sti

    mov ah, 0x13
    mov al, 1
    mov bh, 0
    mov bl, 0x70
    mov dx, 0x0D10
    mov cx, 48
    push cs
    pop es
    mov bp, message
    int 0x10

    mov ah, 0x00
    int 0x16

    cmp al, 0x0D    ; Check if Enter
    jne check_escape
    
    mov byte [collision], 0
    mov word [position], 3920
    mov byte [direction], 'r'
    mov byte [ticks], 0
    jmp start

    check_escape:
        cmp al, 0x1B    ; Check if Escape
        je terminate
        jmp end
    
terminate:
    call clearScreen
    mov ax, 0x4c00
    int 0x21