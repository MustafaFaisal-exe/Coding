[org 0x0100]
jmp start

; Syed Asadullah Gilani 24L-0853
; Ubaid -ur- Rehman 24L-0808

buffer: times 80 dw 0                    ; buffer to store one row
car_buffer: times 400 dw 0               ; buffer for 5 rows of car

game_over_flag: db 0
score: dw 0
coins_collected: dw 0
game_started: db 0                       ; Flag to check if game has started

oldisr: dd 0                             ; space for saving old ISR address

SCREEN_WIDTH equ 80
SCREEN_HEIGHT equ 25
frame_count: dw 0
random_pick: dw 0x1234

MAX_ENEMY_CARS equ 4
enemy_car_active: times MAX_ENEMY_CARS db 0
enemy_car_row: times MAX_ENEMY_CARS dw 0
enemy_car_col: times MAX_ENEMY_CARS dw 0

; Coins - max 6
MAX_COINS equ 6
coin_active: times MAX_COINS db 0
coin_row: times MAX_COINS dw 0
coin_col: times MAX_COINS dw 0

; Player car position (fixed in center lane)
player_row: dw 19
player_col: dw 39

LANE1_COL equ 28
LANE2_COL equ 39
LANE3_COL equ 52

COLOR_ENEMY_CAR equ 0x11                ; Bright blue
COLOR_COIN equ 0x0E                     ; Bright yellow
COLOR_PLAYER_CAR equ 0x4F               ; Red background


game_paused: db 0                        ; NEW: Flag for pause state
oldtimer: dd 0                           ; NEW: space for saving old timer ISR

title: db '====== DEATHLANE ======', 0
welcome_msg: db 'Welcome to DeathLane!', 0
instruction1: db 'Use LEFT and RIGHT arrows to move', 0
instruction2: db 'Collect coins ($) for points', 0
instruction3: db 'Avoid blue enemy cars!', 0
student1: db 'Syed Asadullah Gilani', 0
roll1: db '24L-0853', 0
student2: db 'Ubaid-ur-Rehman', 0
roll2: db '24L-0808', 0
press_key: db 'Press ANY KEY to start...', 0

game_over_text: db 'GAME OVER!', 0
your_score: db 'Your Score: ', 0
coins_text: db 'Coins Collected: ', 0
play_again: db 'Press R to Restart or ESC to Exit', 0
temp_col: db 0 ;temporary storage for column

exit_confirm: db 'Are you sure you want to exit?', 0
exit_yes_no: db 'Press Y (Yes) or N (No)', 0

; Exit dialog strings
exit_message: db 'Exit Game?', 0
exit_yes: db 'Y - Yes', 0
exit_no: db 'N - No', 0

kbisr:
    push ax
    push bx
    push es
    
    in al, 0x60
    
    test al, 0x80
    jnz near kb_done

    ; Check if game hasn't started yet (intro screen)
    cmp byte [game_started], 0
    jne check_pause_or_game

    ; Intro screen: any key starts game
    mov byte [game_started], 1
    jmp kb_done

check_pause_or_game:
    cmp byte [game_paused], 1
    je pause_key_check

    ; Normal gameplay
    cmp al, 0x01          ; ESC
    je show_exit_confirmation
    cmp al, 0x4B          ; LEFT arrow
    je move_left
    cmp al, 0x4D          ; RIGHT arrow
    je near move_right
    jmp kb_done

pause_key_check:
    cmp al, 0x15          ; 'Y' key
    je handle_yes
    cmp al, 0x31          ; 'N' key
    je handle_no
    jmp kb_done        

handle_yes:
    mov byte [game_paused], 0
    mov byte [game_over_flag], 1
    jmp kb_done

handle_no:
    mov byte [game_paused], 0
    
    ; Redraw full screen
    call clrscr
    call gb1
    call gb2
    call road
    call track
    call track2
    call ytrack
    call ytrack2
    call trees
    call draw_all_enemy_cars
    call draw_all_coins
    call car              ; ? critical: redraw player!
    jmp kb_done

show_exit_confirmation:
    mov byte [game_paused], 1
    call show_exit_dialog
    jmp kb_done

move_left:
    call clearCar
    mov bx, [player_col]
    cmp bx, LANE2_COL
    je left_to_lane1
    cmp bx, LANE3_COL
    je right_to_lane2
    jmp kb_done   ; already in leftmost lane

left_to_lane1:
    mov word [player_col], LANE1_COL
    call check_sideways_collision
    jmp kb_done

right_to_lane2:
    mov word [player_col], LANE2_COL
    call check_sideways_collision
    jmp kb_done

move_right:
    call clearCar
    mov bx, [player_col]
    cmp bx, LANE1_COL
    je lane1_to_lane2
    cmp bx, LANE2_COL
    je lane2_to_lane3
    jmp kb_done   ; already in rightmost lane

lane1_to_lane2:
    mov word [player_col], LANE2_COL
    call check_sideways_collision
    jmp kb_done

lane2_to_lane3:
    mov word [player_col], LANE3_COL
    call check_sideways_collision
    jmp kb_done

kb_done:
    ; Send EOI to PIC
    mov al, 0x20
    out 0x20, al
    ;end of interrupt

    pop es
    pop bx
    pop ax
    iret

hooking:
    push ax
    push es
    
    ; Save old ISR
    xor ax, ax
    mov es, ax
    mov ax, [es:9*4]
    mov [oldisr], ax
    mov ax, [es:9*4+2]
    mov [oldisr+2], ax
    
    ; Install new ISR
    cli
    mov word [es:9*4], kbisr
    mov [es:9*4+2], cs
    sti
    
    pop es
    pop ax
    ret

unhook:
    push ax
    push es
    
    xor ax, ax
    mov es, ax
    
    cli
    mov ax, [oldisr]
    mov [es:9*4], ax
    mov ax, [oldisr+2]
    mov [es:9*4+2], ax
    sti
    
    pop es
    pop ax
    ret

clrscr:
    push ax
    push es
    push di
    push cx
    mov ax, 0xB800
    mov es, ax
    xor di, di
    mov ax, 0x0720                    ; Black background, white space
    mov cx, 2000
    cld
    rep stosw
    pop cx
    pop di
    pop es
    pop ax
    ret

printstr:
    push ax
    push bx
    push cx
    push dx
    push di
    push es
    push si
    mov ax, 0xB800
    mov es, ax
    
    ; Calculate position
    mov al, dh
    mov ah, 0
    mov cx, 80
    mul cx
    mov cl, dl
    mov ch, 0
    add ax, cx
    shl ax, 1
    mov di, ax

printstr_loop:
    lodsb
    cmp al, 0
    je printstr_done
    
    mov [es:di], al
    mov [es:di+1], bl
    add di, 2
    jmp printstr_loop

printstr_done:
    pop si
    pop es
    pop di
    pop dx
    pop cx
    pop bx
    pop ax
    ret

; Input: AX = number, DH = row, DL = col, BL = attribute
printnum:
    pusha
    push es
    
    mov [cs:temp_col], dl
    
    mov cx, ax          ; save number
    mov ax, 0xB800
    mov es, ax
    
    mov al, dh
    mov ah, 0
    mov bx, 80
    mul bx            
    mov dl, [cs:temp_col] 
    mov dh, 0
    add ax, dx          ; + DL
    shl ax, 1           ; * 2
    mov di, ax
    
    mov ax, cx          ; restore number
    mov bx, 10
    xor cx, cx          ; digit count

    ; Handle 0
    test ax, ax
    jnz .not_zero
    mov byte [es:di], '0'
    mov byte [es:di+1], bl
    pop es
    popa
    ret

.not_zero:
    ; Push digits onto stack
    mov bx, 10
.digit_loop:
    xor dx, dx
    div bx
    add dl, '0'
    push dx
    inc cx
    test ax, ax
    jnz .digit_loop

    ; Pop and print
.print_loop:
    pop ax              ; AL = ASCII digit
    mov [es:di], al
    mov [es:di+1], bl   ; attr
    add di, 2
    loop .print_loop

    pop es
    popa
    ret

; Input: DH = row, DL = col, BH = height, BL = width, AL = attribute
draw_box:
    push ax
    push bx
    push cx
    push dx
    push di
    push es
    mov cx, 0xB800
    mov es, cx
    
    push ax                            ; Save attribute
    
    ; Calculate starting position
    mov al, dh
    mov ah, 0
    mov cx, 80
    mul cx
    mov cl, dl
    mov ch, 0
    add ax, cx
    shl ax, 1
    mov di, ax
    
    pop cx                             ; Get attribute in CL
    mov ch, 0
    
    ; Top border
    mov al, 0xC9                      ; Top-left corner
    stosb
    mov al, cl
    stosb
    
    push bx
    mov cl, bl
    dec cl
    dec cl

draw_top:
    mov al, 0xCD                    
    stosb
    push ax
    mov al, ch
    stosb
    pop ax
    dec cl
    jnz draw_top
    
    mov al, 0xBB                    
    stosb
    mov al, ch
    stosb
    pop bx
    
    ; Side borders
    dec bh
    dec bh

draw_sides:
    add di, 160
    sub di, bx
    sub di, bx
    
    mov al, 0xBA                    
    stosb
    mov al, ch
    stosb
    
    push cx
    mov cl, bl
    dec cl
    dec cl

draw_middle:
    mov al, ' '
    stosb
    push ax
    mov al, ch
    stosb
    pop ax
    dec cl
    jnz draw_middle
    pop cx
    
    mov al, 0xBA                 
    stosb
    mov al, ch
    stosb
    
    dec bh
    jnz draw_sides
    
    ; Bottom border
    add di, 160
    sub di, bx
    sub di, bx
    
    mov al, 0xC8                    
    stosb
    mov al, ch
    stosb
    
    push bx
    mov cl, bl
    dec cl
    dec cl

draw_bottom:
    mov al, 0xCD                   
    stosb
    push ax
    mov al, ch
    stosb
    pop ax
    dec cl
    jnz draw_bottom
    
    mov al, 0xBC                     
    stosb
    mov al, ch
    stosb
    pop bx
    
    pop es
    pop di
    pop dx
    pop cx
    pop bx
    pop ax
    ret

calculate_center:
    push ax
    push cx
    push si
    
    mov cx, 0
count_loop:
    lodsb
    test al, al
    jz done_count
    inc cx
    jmp count_loop
done_count:
    ; DL = (80 - CX) / 2
    mov ax, 80
    sub ax, cx
    shr ax, 1
    mov dl, al
    
    pop si            
    pop cx
    pop ax
    ret

intro_screen:
    pusha
    call clrscr
    
    mov dh, 3
    mov dl, 15
    mov bh, 18
    mov bl, 50
    mov al, 0x0C                      ; Bright red
    call draw_box
    
    ; Print title
    mov si, title
    call calculate_center
    mov dh, 5
    mov bl, 0x4E                      ; Red bg, yellow text
    call printstr
    
    ; Print welcome message
    mov si, welcome_msg
    mov dh, 8
    mov bl, 0x0F                      ; Bright white
    call printstr
    
    ; Print instructions
    mov si, instruction1
    mov dh, 11
    mov bl, 0x0A                      ; Bright green
    call printstr
    
    mov si, instruction2
    mov dh, 12
    mov bl, 0x0E                      ; Yellow
    call printstr
    
    mov si, instruction3
    mov dh, 13
    mov bl, 0x0C                      ; Bright red
    call printstr
    
    ; Student info
    mov si, student1
    mov dh, 16
    mov bl, 0x0B                      ; Cyan
    call printstr
    
    mov si, roll1
    mov dh, 17
    mov bl, 0x07                      ; Gray
    call printstr
    
    mov si, student2
    mov dh, 18
    mov bl, 0x0B                      ; Cyan
    call printstr
    
    mov si, roll2
    mov dh, 19
    mov bl, 0x07                      ; Gray
    call printstr
    
    mov si, press_key
    mov dh, 22
    mov bl, 0x9E                      ; Yellow, blinking
    call printstr
    
    popa
    ret

game_over_screen:
    push ax
    push bx
    push cx
    push dx
    push si
    call clrscr
    
    ; Draw box
    mov dh, 6
    mov dl, 20
    mov bh, 12
    mov bl, 40
    mov al, 0x4F                    
    call draw_box
    
    ; "GAME OVER!"
    mov si, game_over_text
    mov dh, 8
    mov dl, 35
    mov bl, 0x4F
    call printstr
    
    ; "Your Score: "
    mov si, your_score
    mov dh, 11
    mov dl, 25
    mov bl, 0x0F
    call printstr
    
    mov ax, [score]
    mov dh, 11                            ; same row
    add dl, 32                           
    mov bl, 0x0E                          ; yellow
    call printnum
    
    ; "Coins Collected: "
    mov si, coins_text
    mov dh, 13
    mov dl, 25
    mov bl, 0x0F
    call printstr
    
    ; Print coins value
    mov ax, [coins_collected]
    mov dh, 13
    add dl, 37                            ; "Coins Collected: " is 17 chars
    mov bl, 0x0E
    call printnum
    
    ; "Press R to Restart or ESC to Exit"
    mov si, play_again
    mov dh, 16
    mov bl, 0x0A                          ; bright green
    call printstr
    
    pop si
    pop dx
    pop cx
    pop bx
    pop ax
    ret

road:
    push ax
    push es
    push bx
    push si
    push dx
    mov ax, 0xB800
    mov es, ax
    mov bx, 0

rows3:
    mov si, 21

cols3:
    mov ax, bx
    mov dx, 160
    mul dx
    mov dx, si
    add dx, dx
    add ax, dx
    mov di, ax
    mov word [es:di], 0x7820
    inc si
    cmp si, 59
    jl cols3
    inc bx
    cmp bx, 25
    jl rows3
    
    pop dx
    pop si
    pop bx
    pop es
    pop ax
    ret

ytrack:
    push ax
    push es
    push bx
    push si
    push dx
    mov ax, 0xB800
    mov es, ax
    mov bx, 0

rows8:
    mov si, 57

cols8:
    mov ax, bx
    mov dx, 160
    mul dx
    mov dx, si
    add dx, dx
    add ax, dx
    mov di, ax
    mov word [es:di], 0x0EDB
    inc si
    cmp si, 58
    jl cols8
    inc bx
    cmp bx, 25
    jl rows8
    
    pop dx
    pop si
    pop bx
    pop es
    pop ax
    ret

ytrack2:
    push ax
    push es
    push bx
    push si
    push dx
    mov ax, 0xB800
    mov es, ax
    mov bx, 0

rows9:
    mov si, 22

cols9:
    mov ax, bx
    mov dx, 160
    mul dx
    mov dx, si
    add dx, dx
    add ax, dx
    mov di, ax
    mov word [es:di], 0x0EDB
    inc si
    cmp si, 23
    jl cols9
    inc bx
    cmp bx, 25
    jl rows9
    
    pop dx
    pop si
    pop bx
    pop es
    pop ax
    ret

gb1:
    push ax
    push es
    push bx
    push si
    push dx
    mov ax, 0xB800
    mov es, ax
    mov bx, 0

rows:
    mov si, 0

cols:
    mov ax, bx
    mov dx, 160
    mul dx
    mov dx, si
    add dx, dx
    add ax, dx
    mov di, ax
    mov word [es:di], 0x2ADB
    inc si
    cmp si, 21
    jl cols
    inc bx
    cmp bx, 25
    jl rows
    
    pop dx
    pop si
    pop bx
    pop es
    pop ax
    ret

gb2:
    push ax
    push es
    push bx
    push si
    push dx
    mov ax, 0xB800
    mov es, ax
    mov bx, 0

rows2:
    mov si, 59

cols2:
    mov ax, bx
    mov dx, 160
    mul dx
    mov dx, si
    add dx, dx
    add ax, dx
    mov di, ax
    mov word [es:di], 0x2ADB
    inc si
    cmp si, 80
    jl cols2
    inc bx
    cmp bx, 25
    jl rows2
    
    pop dx
    pop si
    pop bx
    pop es
    pop ax
    ret

track:
    push ax
    push es
    push bx
    push si
    push dx
    mov ax, 0xB800
    mov es, ax
    mov bx, 0

rows4:
    mov si, 35

cols4:
    mov ax, bx
    mov dx, 160
    mul dx
    mov dx, si
    add dx, dx
    add ax, dx
    mov di, ax
    mov word [es:di], 0x0FDB
    inc si
    cmp si, 36
    jl cols4
    inc bx
    inc bx
    cmp bx, 25
    jl rows4
    
    pop dx
    pop si
    pop bx
    pop es
    pop ax
    ret

track2:
    push ax
    push es
    push bx
    push si
    push dx
    mov ax, 0xB800
    mov es, ax
    mov bx, 0

rows5:
    mov si, 45

cols5:
    mov ax, bx
    mov dx, 160
    mul dx
    mov dx, si
    add dx, dx
    add ax, dx
    mov di, ax
    mov word [es:di], 0x0FDB
    inc si
    cmp si, 46
    jl cols5
    inc bx
    inc bx
    cmp bx, 25
    jl rows5
    
    pop dx
    pop si
    pop bx
    pop es
    pop ax
    ret

trees:
    push ax
    push bx
    push cx
    push dx
    push si
    push di
    push es
    mov ax, 0xB800
    mov es, ax
    mov bx, 5

left_trees:
    mov si, 5
    mov ax, bx
    mov dx, 160
    mul dx
    mov cx, si
    add cx, cx
    add ax, cx
    mov di, ax
    mov word [es:di], 0x6620
    add di, 160
    mov word [es:di], 0x6620
    mov ax, bx
    sub ax, 2
    mov dx, 160
    mul dx
    mov cx, si
    add cx, cx
    add ax, cx
    mov di, ax
    
    mov word [es:di], 0x2020
    add di, 160
    mov word [es:di], 0x2020
    sub di, 2
    mov word [es:di], 0x2020
    add di, 4
    mov word [es:di], 0x2020
    add di, 158
    mov word [es:di], 0x2020
    sub di, 2
    mov word [es:di], 0x2020
    add di, 4
    mov word [es:di], 0x2020
    sub di, 6
    mov word [es:di], 0x2020
    add di, 8
    mov word [es:di], 0x2020
    add bx, 6
    cmp bx, 23
    jl left_trees
    
    mov bx, 5

right_trees:
    mov si, 75
    mov ax, bx
    mov dx, 160
    mul dx
    mov cx, si
    add cx, cx
    add ax, cx
    mov di, ax
    mov word [es:di], 0x6620
    add di, 160
    mov word [es:di], 0x6620
    mov ax, bx
    sub ax, 2
    mov dx, 160
    mul dx
    mov cx, si
    add cx, cx
    add ax, cx
    mov di, ax
    
    mov word [es:di], 0x2020
    add di, 160
    mov word [es:di], 0x2020
    sub di, 2
    mov word [es:di], 0x2020
    add di, 4
    mov word [es:di], 0x2020
    add di, 158
    mov word [es:di], 0x2020
    sub di, 2
    mov word [es:di], 0x2020
    add di, 4
    mov word [es:di], 0x2020
    sub di, 6
    mov word [es:di], 0x2020
    add di, 8
    mov word [es:di], 0x2020
    add bx, 6
    cmp bx, 23
    jl right_trees
    
    pop es
    pop di
    pop si
    pop dx
    pop cx
    pop bx
    pop ax
    ret

car:
    push ax
    push bx
    push cx
    push di
    push es
    mov ax, 0xB800
    mov es, ax
    
    mov ax, [player_row]
    mov bx, [player_col]
    
    ; Calculate base position
    mov cx, SCREEN_WIDTH
    mul cx
    shl ax, 1
    mov di, ax
    mov ax, bx
    shl ax, 1
    add di, ax
    
    ; Row 1: Roof (3 chars centered)
    add di, 2
    mov word [es:di], 0x4FDB
    mov word [es:di+2], 0x4FDB
    mov word [es:di+4], 0x4FDB
    sub di, 2
    
    ; Row 2: Windshield with windows
    add di, SCREEN_WIDTH * 2
    mov word [es:di], 0x4FDB
    mov word [es:di+2], 0x1F20
    mov word [es:di+4], 0x1F20
    mov word [es:di+6], 0x1F20
    mov word [es:di+8], 0x4FDB

    mov ax, [score]
    mov dh, 20
    mov dl, [player_col]
    add dl, 2
    mov bl, 0xF0        ; black digits on white background
    call printnum
    
    ; Row 3: Body with headlights
    add di, SCREEN_WIDTH * 2
    mov word [es:di], 0x4E4F
    mov word [es:di+2], 0x4FDB
    mov word [es:di+4], 0x4FDB
    mov word [es:di+6], 0x4FDB
    mov word [es:di+8], 0x4E4F
    
    ; Row 4: Bumper
    add di, SCREEN_WIDTH * 2
    mov word [es:di], 0x4FDB
    mov word [es:di+2], 0x4FDB
    mov word [es:di+4], 0x4FDB
    mov word [es:di+6], 0x4FDB
    mov word [es:di+8], 0x4FDB
    
    pop es
    pop di
    pop cx
    pop bx
    pop ax
    ret

clearCar:
    push ax
    push bx
    push cx
    push di
    push es
    mov ax, 0xB800
    mov es, ax
    
    mov ax, [player_row]
    mov bx, [player_col]
    
    mov cx, SCREEN_WIDTH
    mul cx
    shl ax, 1
    mov di, ax
    mov ax, bx
    shl ax, 1
    add di, ax
    mov ax, 0x7820
    mov cx, 4

clear_car_rows:
    push cx
    push di
    mov cx, 5

clear_car_cols:
    mov [es:di], ax
    add di, 2
    loop clear_car_cols
    pop di
    add di, SCREEN_WIDTH * 2
    pop cx
    loop clear_car_rows
    
    pop es
    pop di
    pop cx
    pop bx
    pop ax
    ret

MoveScreen:
    push ax
    push cx
    push si
    push di
    push es
    push ds
    mov ax, 0xb800
    mov es, ax
    mov ds, ax
    mov si, 3840
    mov di, 4000
    mov cx, 80
    cld
    rep movsw
    mov si, 3838
    mov di, 3998
    std
    mov cx, 1920
    rep movsw
    cld
    mov si, 4000
    mov di, 0
    mov cx, 80
    rep movsw
    pop ds
    pop es
    pop di
    pop si
    pop cx
    pop ax
    ret

delay:
    push cx
    push dx
    mov cx, 0000h                      
    mov dx, 0x8000                    
    mov ah, 86h
    int 15h
    pop dx
    pop cx
    ret

get_random:
    push dx
    push bx
    push cx
    
    mov al, 0x00 ;seconds reg
    out 0x70, al
    nop
    nop
    in al, 0x71
    mov ah, al
    
    mov al, 0x02 ;minutes reg
    out 0x70, al
    nop
    nop
    in al, 0x71
    add al, ah
    
    ; incrementing game tick for more randomness
    mov bx, [frame_count]
    add ax, bx
    
    ;linear cong generator
    mov bx, [random_pick]
    imul bx, 25173                     ; Use a 16-bit multiplier
    add bx, 13849                      ; Use a 16-bit increment
    mov [random_pick], bx
    
    ;all methods
    xor ax, bx
    rol ax, 3
    
    pop cx
    pop bx
    pop dx
    ret

get_random_lane:
    push bx
    push dx
    
    call get_random ;0-65535
    
    mov dx, ax
    shr dx, 3
    and dx, 0x7FFF ;clear high
    
    mov ax, dx
    mov dx, 0
    mov bx, 3
    div bx
    
    cmp dx, 0 ;remainder to pick lane
    je rand_lane1
    cmp dx, 1
    je rand_lane2
    jmp rand_lane3

rand_lane1:
    mov ax, LANE1_COL
    jmp rand_lane_done

rand_lane2:
    mov ax, LANE2_COL
    jmp rand_lane_done

rand_lane3:
    mov ax, LANE3_COL

rand_lane_done:
    pop dx
    pop bx
    ret

check_sideways_collision:
    push ax
    push bx
    push cx
    push si
    push dx
    
    mov cx, MAX_ENEMY_CARS
    mov si, 0

check_sideways_loop:
    cmp byte [enemy_car_active + si], 0
    je skip_sideways_check
    mov bx, si
    shl bx, 1
    mov ax, [enemy_car_row + bx]
    mov dx, [enemy_car_col + bx]
    
    ;player region
    cmp ax, 15
    jl skip_sideways_check
    cmp ax, 23
    jg skip_sideways_check
    
    ;player col
    mov bx, [player_col]

    ;collide
    sub bx, 3
    cmp dx, bx
    jl skip_sideways_check
    add bx, 8
    cmp dx, bx
    jg skip_sideways_check
    
    ;gameOver
    mov byte [game_over_flag], 1
    jmp sideways_collision_done

skip_sideways_check:
    inc si
    cmp si, MAX_ENEMY_CARS
    jl check_sideways_loop

sideways_collision_done:
    pop dx
    pop si
    pop cx
    pop bx
    pop ax
    ret

check_position_occupied:
    push bp
    push cx
    push si
    push di
    push bx
    
    mov bp, ax
    mov di, bx
    
    mov cx, MAX_ENEMY_CARS
    mov si, 0

check_enemy_pos:
    cmp byte [enemy_car_active + si], 0
    je skip_check_enemy ;enemy not active
    
    mov bx, si
    shl bx, 1 ;enemies are db 0,1,2,3.
    mov ax, [enemy_car_row + bx]
    mov bx, [enemy_car_col + bx]
    
    cmp bx, di
    jne skip_check_enemy
    
    ;avoid overlap
    mov cx, bp
    sub cx, ax
    cmp cx, -5
    jl skip_check_enemy
    cmp cx, 5
    jg skip_check_enemy
    
    mov ax, 1
    jmp check_done

skip_check_enemy:
    inc si
    cmp si, MAX_ENEMY_CARS
    jl check_enemy_pos
    
    mov cx, MAX_COINS
    mov si, 0

check_coin_pos:
    cmp byte [coin_active + si], 0
    je skip_check_coin
    
    mov bx, si ;si is the coin we check 0,1,2,3.
    shl bx, 1
    mov ax, [coin_row + bx]
    mov bx, [coin_col + bx]
    
    cmp bx, di
    jne skip_check_coin
    
    ;avoid overlap
    mov cx, bp
    sub cx, ax
    cmp cx, -3
    jl skip_check_coin
    cmp cx, 3
    jg skip_check_coin
    
    mov ax, 1
    jmp check_done

skip_check_coin:
    inc si
    cmp si, MAX_COINS
    jl check_coin_pos
    
    mov ax, 0

check_done:
    pop bx
    pop di
    pop si
    pop cx
    pop bp
    ret

spawn_enemy_car:
    push ax
    push bx
    push cx
    push si
    push di
    
    mov cx, MAX_ENEMY_CARS
    mov si, 0

find_enemy_slot: ;finding space
    cmp byte [enemy_car_active + si], 0 ;0,1,2,3.
    je found_enemy_slot
    inc si
    loop find_enemy_slot
    jmp spawn_enemy_done

found_enemy_slot:
    mov di, si
    
    mov cx, 5 ;random positions

try_spawn_enemy:
    push cx
    
    call get_random_lane ;any lane
    mov bx, ax ;lane
    mov ax, 2 ;row
    
    call check_position_occupied
    cmp ax, 0
    je position_free_enemy
    
    pop cx
    loop try_spawn_enemy
    jmp spawn_enemy_done

position_free_enemy:
    pop cx

    ;activating the enemies
    mov byte [enemy_car_active + di], 1
    
    shl di, 1 ;word array
    mov word [enemy_car_row + di], 2
    mov word [enemy_car_col + di], bx

spawn_enemy_done:
    pop di
    pop si
    pop cx
    pop bx
    pop ax
    ret

spawn_coin:
    push ax
    push bx
    push cx
    push si
    push di
    
    mov cx, MAX_COINS
    mov si, 0

find_coin_slot:
    cmp byte [coin_active + si], 0
    je found_coin_slot
    inc si
    loop find_coin_slot
    jmp spawn_coin_done

found_coin_slot:
    mov di, si
    
    mov cx, 5

try_spawn_coin:
    push cx
    
    call get_random_lane
    mov bx, ax
    mov ax, 3
    
    call check_position_occupied
    cmp ax, 0
    je position_free_coin
    
    pop cx
    loop try_spawn_coin
    jmp spawn_coin_done

position_free_coin:
    pop cx
    
    mov byte [coin_active + di], 1
    
    shl di, 1
    mov word [coin_row + di], 3
    mov word [coin_col + di], bx

spawn_coin_done:
    pop di
    pop si
    pop cx
    pop bx
    pop ax
    ret

clear_single_enemy_car:
    push ax
    push bx
    push cx
    push di
    push es
    mov cx, 0xB800
    mov es, cx
    mov cx, SCREEN_WIDTH
    mul cx
    shl ax, 1
    mov di, ax
    mov ax, bx
    shl ax, 1
    add di, ax
    mov ax, 0x7820
    
    ; Row 1
    mov [es:di], ax
    mov [es:di+2], ax
    mov [es:di+4], ax
    
    ; Row 2
    add di, SCREEN_WIDTH * 2
    mov [es:di], ax
    mov [es:di+2], ax
    mov [es:di+4], ax
    
    ; Row 3
    add di, SCREEN_WIDTH * 2
    mov [es:di], ax
    mov [es:di+2], ax
    mov [es:di+4], ax
    
    ; Row 4
    add di, SCREEN_WIDTH * 2
    mov [es:di], ax
    mov [es:di+2], ax
    mov [es:di+4], ax
    
    pop es
    pop di
    pop cx
    pop bx
    pop ax
    ret

draw_single_enemy_car:
    push ax
    push bx
    push cx
    push di
    push es
    mov cx, 0xB800
    mov es, cx
    mov cx, SCREEN_WIDTH
    mul cx
    shl ax, 1
    mov di, ax
    mov ax, bx
    shl ax, 1
    add di, ax
    
    ; Row 1: Roof
    mov word [es:di], 0x11DB
    mov word [es:di+2], 0x11DB
    mov word [es:di+4], 0x11DB
    
    ; Row 2: Windows
    add di, SCREEN_WIDTH * 2
    mov word [es:di], 0x11DB
    mov word [es:di+2], 0x3020
    mov word [es:di+4], 0x11DB
    
    ; Row 3: Body with eyes
    add di, SCREEN_WIDTH * 2
    mov word [es:di], 0x1E6F
    mov word [es:di+2], 0x11DB
    mov word [es:di+4], 0x1E6F
    
    ; Row 4: Bumper
    add di, SCREEN_WIDTH * 2
    mov word [es:di], 0x11DB
    mov word [es:di+2], 0x11DB
    mov word [es:di+4], 0x11DB
    
    pop es
    pop di
    pop cx
    pop bx
    pop ax
    ret

draw_single_coin:
    push ax
    push bx
    push cx
    push di
    push es
    mov cx, 0xB800
    mov es, cx
    mov cx, SCREEN_WIDTH
    mul cx
    shl ax, 1
    mov di, ax
    mov ax, bx
    shl ax, 1
    add di, ax
    mov byte [es:di], '$'
    mov byte [es:di+1], COLOR_COIN
    pop es
    pop di
    pop cx
    pop bx
    pop ax
    ret

clear_all_enemy_cars:
    push ax
    push bx
    push cx
    push si
    mov cx, MAX_ENEMY_CARS ;loop 4 times.
    mov si, 0

clear_enemy_loop:
    cmp byte [enemy_car_active + si], 0
    je skip_clear_enemy
    mov bx, si
    shl bx, 1
    mov ax, [enemy_car_row + bx]
    mov bx, [enemy_car_col + bx]
    call clear_single_enemy_car

    ;clear before scrolling and draw after scrolling.

skip_clear_enemy:
    inc si
    loop clear_enemy_loop
    
    pop si
    pop cx
    pop bx
    pop ax
    ret

draw_all_enemy_cars:
    push ax
    push bx
    push cx
    push si
    mov cx, MAX_ENEMY_CARS ;loop 4 times.
    mov si, 0

draw_enemy_loop:
    cmp byte [enemy_car_active + si], 0
    je skip_draw_enemy
    mov bx, si
    shl bx, 1
    mov ax, [enemy_car_row + bx]
    mov bx, [enemy_car_col + bx]
    call draw_single_enemy_car

skip_draw_enemy:
    inc si
    loop draw_enemy_loop
    
    pop si
    pop cx
    pop bx
    pop ax
    ret

draw_all_coins:
    push ax
    push bx
    push cx
    push si
    mov cx, MAX_COINS
    mov si, 0

draw_coin_loop:
    cmp byte [coin_active + si], 0
    je skip_draw_coin
    mov bx, si
    shl bx, 1
    mov ax, [coin_row + bx]
    mov bx, [coin_col + bx]
    call draw_single_coin

skip_draw_coin:
    inc si
    loop draw_coin_loop
    
    pop si
    pop cx
    pop bx
    pop ax
    ret
update_enemy_cars:
    push ax
    push bx
    push cx
    push si
    push dx
    mov cx, MAX_ENEMY_CARS
    mov si, 0

update_enemy_loop:
    cmp byte [enemy_car_active + si], 0
    je skip_update_enemy
    mov bx, si
    shl bx, 1
    
    ; Check if car is about to go off screen
    mov dx, [enemy_car_row + bx]
    cmp dx, 21                         ; If car reaches row 21, it will be off-screen after scroll
    jge deactivate_enemy
    
    ;move car down
    inc word [enemy_car_row + bx]
    jmp skip_update_enemy

deactivate_enemy:
    ; Clear the car completely before deactivating
    mov ax, [enemy_car_row + bx]
    mov bx, [enemy_car_col + bx]
    call clear_single_enemy_car
    
    ; Deactivate the enemy
    mov byte [enemy_car_active + si], 0
    add word [score], 10

skip_update_enemy:
    inc si
    loop update_enemy_loop
    
    pop dx
    pop si
    pop cx
    pop bx
    pop ax
    ret

update_coins:
    push ax
    push bx
    push cx
    push si
    mov cx, MAX_COINS
    mov si, 0

update_coin_loop:
    cmp byte [coin_active + si], 0
    je skip_update_coin
    mov bx, si
    shl bx, 1
    inc word [coin_row + bx]
    cmp word [coin_row + bx], 24
    jl skip_update_coin
    mov byte [coin_active + si], 0 ;deactivating the coins

skip_update_coin:
    inc si
    loop update_coin_loop
    
    pop si
    pop cx
    pop bx
    pop ax
    ret

;front collision
check_collisions:
    push ax
    push bx
    push cx
    push si
    push dx
    
    ; Check enemy car collisions
    mov cx, MAX_ENEMY_CARS
    mov si, 0

check_enemy_collision:
    cmp byte [enemy_car_active + si], 0
    je skip_enemy_collision
    mov bx, si
    shl bx, 1
    mov ax, [enemy_car_row + bx]
    mov dx, [enemy_car_col + bx]
    
    ; Check if enemy is in player's area (rows 15-23)
    cmp ax, 15
    jl skip_enemy_collision
    cmp ax, 23
    jg skip_enemy_collision
    
    ; Check if same column (player is at 39, enemy is 3 wide)
    mov bx, [player_col]
    
    ; Check overlap
    sub bx, 3
    cmp dx, bx
    jl skip_enemy_collision
    add bx, 8
    cmp dx, bx
    jg skip_enemy_collision
    
    ;collision
    mov byte [game_over_flag], 1
    jmp collision_done

skip_enemy_collision:
    inc si
    loop check_enemy_collision
    
    ; Check coin collisions
    mov cx, MAX_COINS
    mov si, 0

check_coin_collision:
    cmp byte [coin_active + si], 0
    je skip_coin_collision
    mov bx, si
    shl bx, 1
    mov ax, [coin_row + bx]
    mov dx, [coin_col + bx]
    
    ; Check if coin is in player's row range
    cmp ax, 19
    jl skip_coin_collision
    cmp ax, 23
    jg skip_coin_collision
    
    ; Check column overlap
    mov bx, [player_col]
    cmp dx, bx
    jl skip_coin_collision
    add bx, 5
    cmp dx, bx
    jg skip_coin_collision
    
    ;collected
    mov byte [coin_active + si], 0
    add word [score], 10               
    inc word [coins_collected]

skip_coin_collision:
    inc si
    loop check_coin_collision

collision_done:
    pop dx
    pop si
    pop cx
    pop bx
    pop ax
    ret

timer:
    push ax
    push bx
    push cx
    push dx
    
    cmp byte [game_paused], 1
    je timer_done
    cmp byte [game_over_flag], 1
    je timer_done
    cmp byte [game_started], 0
    je timer_done
    
    ; Increment frame counter
    inc word [frame_count]
    
    ; Clear objects before scrolling
    call clear_all_enemy_cars
    call clearCar
    
    ; Scroll the screen
    call MoveScreen
    
    call track
    call track2
    call ytrack
    call ytrack2
    call car
    
    call draw_all_enemy_cars
    call draw_all_coins
    
    call update_enemy_cars
    call update_coins
    
    call check_collisions
    
    mov ax, [frame_count]
    mov dx, 0
    mov bx, 40
    div bx
    cmp dx, 0
    jne skip_spawn_enemy_timer
    call spawn_enemy_car

skip_spawn_enemy_timer:
    mov ax, [frame_count]
    mov dx, 0
    mov bx, 25
    div bx
    cmp dx, 5
    jne timer_done
    call spawn_coin

timer_done:
    ; Call old timer ISR
    pushf
    call far [cs:oldtimer]
    
    pop dx
    pop cx
    pop bx
    pop ax
    iret

show_exit_dialog:
    pusha
    push es

    mov ax, 0xB800
    mov es, ax
    xor di, di       
    mov di, (11 * 80 + 35) * 2     ; video offset for row 11, col 35

    mov si, exit_message          
    mov ah, 0x4F                   ; white on red (4F would be brighter red bg)
.eloop1:
    lodsb
    test al, al
    jz .done1
    mov [es:di], ax               
    add di, 2
    jmp .eloop1
.done1:
    mov di, (13 * 80 + 28) * 2
    mov si, exit_yes
    mov ah, 0x0F                   ; bright white on black
.eloop2:
    lodsb
    test al, al
    jz .done2
    mov [es:di], ax
    add di, 2
    jmp .eloop2
.done2:
    mov di, (13 * 80 + 52) * 2
    mov si, exit_no
    mov ah, 0x0F
.eloop3:
    lodsb
    test al, al
    jz .done3
    mov [es:di], ax
    add di, 2
    jmp .eloop3
.done3:

    pop es
    popa
    ret

hook_timer:
    push ax
    push es
    
    ; Save old timer ISR
    xor ax, ax
    mov es, ax
    mov ax, [es:0x1C*4]
    mov [oldtimer], ax
    mov ax, [es:0x1C*4+2]
    mov [oldtimer+2], ax
    
    ; Install new timer ISR
    cli
    mov word [es:0x1C*4], timer
    mov [es:0x1C*4+2], cs
    sti
    
    pop es
    pop ax
    ret

unhook_timer:
    push ax
    push es
    
    xor ax, ax
    mov es, ax
    
    cli
    mov ax, [oldtimer]
    mov [es:0x1C*4], ax
    mov ax, [oldtimer+2]
    mov [es:0x1C*4+2], ax
    sti
    
    pop es
    pop ax
    ret

start:
    ; Hook keyboard interrupt first
    call hooking

    call hook_timer

main_menu:
    ; Show intro screen
    call intro_screen

wait_for_start:
    ; Wait until game_started flag is set by keyboard ISR
    cmp byte [game_started], 0
    je wait_for_start
    
    ; Initialize game screen
    call clrscr
    call gb1
    call gb2
    call road
    call track
    call track2
    call ytrack
    call ytrack2
    call trees
    call car

gameloop:
    ; Check if game over
    cmp byte [game_over_flag], 0
    jne show_game_over
    
    ; Game loop now just waits, timer ISR handles everything
    call delay
    jmp gameloop

show_game_over:
    call unhook
    call unhook_timer
    
    call game_over_screen

wait_for_choice:
    ; Use BIOS keyboard read
    mov ah, 0
    int 0x16              ; Wait for ANY keypress
    
    ; Any key pressed ? exit to DOS
    ;call clrscr
    mov ax, 0x4C00
    int 0x21
    
    ; If game_started is 0, restart from intro
    cmp byte [game_started], 0
    je main_menu