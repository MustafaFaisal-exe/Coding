[org 0x0100]

jmp start

; PCB layout
; ax, bx, cx, dx, si, di, bp, sp, ip, cs, ds, ss, es, flags, next, dummy
;  0,  2,  4,  6,  8, 10, 12, 14, 16, 18, 20, 22, 24,    26,   28,    30

pcb: times 32*16 dw 0           ;space for 32 PCBs
stack: times 32*256 dw 0        ;space for 32 512 byte stacks
nextPcb: dw 1                   ;index of next free pcb
current: dw 0                   ;index of current pcb
lineNo: dw 0                    ;line number for next thread

; subRoutine to print a number on the screen
; takes the row no., column no., and number to be printed as parameters

printnum:
    push bp
    mov bp, sp
    push es
    push ax
    push bx
    push cx
    push dx
    push di

    mov di, 80            ;load di with columns per row
    mov ax, [bp + 8]      ;load ax with row number
    mul di                ;multiply with columns per row
    mov di, ax            ;save result in di
    add di, [bp + 6]      ;add column number
    shl di, 1             ;turn into byte count
    add di, 8             ;to end of number location

    mov ax, 0xb800
    mov es, ax            ;point es to video base
    mov ax, [bp + 4]      ;load number in ax
    mov bx, 16            ;use base 16 for division
    mov cx, 4             ;initialize count of digits

    nextDigit:
        mov dx, 0         ;zero upper half of dividend
        div bx            ;divide by 16
        add dl, 0x30      ;convert digit into ascii value
        cmp dl, 0x39      ;is the digit an alphabet?
        jbe skipAlpha     ;no, skip addition
        add dl, 7         ;yes, make in alphabet code

    skipAlpha:
        mov dh, 0x07
        mov [es:di], dx
        sub di, 2
        loop nextDigit

    pop di
    pop dx
    pop cx
    pop bx
    pop ax
    pop es
    pop bp
    ret 6

; my task SubRoutine to be run as a thread
; takes line number as parameter

myTask:
    push bp
    mov bp, sp
    sub sp, 2         ;thread local variable
    push ax
    push bx
    push cx

    mov ax, [bp + 4]      ;load line number parameter
    push ax
    mov cx, 10
    mul cx
    mov bx, 70
    sub bx, ax
    pop ax
    
    mov word [bp - 2], 0  ;initialize local variable

    printAgain:
        push ax               ;line number 
        push bx               ;column number
        push word [bp - 2]    ;number to be printed
        call printnum         ;print the number
        inc word [bp - 2]     ;increment the local variable
        jmp printAgain

    pop cx
    pop bx
    pop ax
    mov sp, bp
    pop bp
    ret

; subRoutine to register a new thread
; takes the sedment, offset, of the thread routine and a paramter
; for the target thread

initPcb:
    push bp
    mov bp, sp
    push ax
    push bx
    push cx
    push si

    mov bx, [nextPcb]        ;read next available pcb index
    cmp bx, 32               ;are all PCBs used
    je exit                  ;if yes then exit

    mov cl, 5
    shl bx, cl               ;multiply by 32 for PCB start

    mov ax, [bp + 8]         ;read segment parameter
    mov [pcb + bx + 18], ax  ;save in pcb space for cs
    mov ax, [bp + 6]         ;read offset parameter
    mov [pcb + bx + 16], ax  ;save in pcb space for ip

    mov [pcb + bx + 22], ds  ;set stack to our segment

    mov si, [nextPcb]       ;read this pcb index
    mov cl, 9
    shl si, cl              ;multiply by 512
    add si, 256*2 + stack   ;end of stack for this thread
    mov ax, [bp + 4]        ;read parameter for subRoutine
    sub si, 2               ;decrement thread stack pointer
    mov [si], ax            ;pushing param on thread stack
    sub si, 2               ;space for return address
    mov [pcb + bx + 14], si ;save si in pcb space for sp

    mov word [pcb + bx + 26], 0x0200       ;initialize thread flags

    mov ax, [pcb + 28]         ;set as next of new thread
    mov [pcb + bx + 28], ax    ;set as next of new thread
    mov ax, [nextPcb]          ;read new thread index
    mov [pcb + 28], ax         ;set as next of 0th thread
    inc word [nextPcb]         ;this pcb is now used

    exit:
        pop si
        pop cx
        pop bx
        pop ax
        pop bp
        ret 6

; timer interrupt service routine

timer:
    push ds
    push bx

    push cs
    pop ds                ;initialize ds to data segment

    mov bx, [current]     ;read index of current in bx
    shl bx, 1
    shl bx, 1
    shl bx, 1
    shl bx, 1
    shl bx, 1
    mov [pcb + bx + 0], ax            ;save ax in current pcb
    mov [pcb + bx + 4], cx            ;save cx in current pcb
    mov [pcb + bx + 6], dx            ;save dx in current pcb
    mov [pcb + bx + 8], si            ;save dx in current pcb
    mov [pcb + bx + 10], di            ;save di in current pcb
    mov [pcb + bx + 12], bp           ;save bp in current pcb
    mov [pcb + bx + 24], es           ;save es in current pcb

    pop ax                            ;read original bx from stack
    mov [pcb + bx + 2], ax            ;save bx in current pcb
    pop ax                            ;read original ds from stack
    mov [pcb + bx + 20], ax           ;save ds in current pcb
    pop ax                            ;read original ip from stack
    mov [pcb + bx + 16], ax           ;save ip in current pcb
    pop ax                            ;read original cs from stack
    mov [pcb + bx + 18], ax           ;save cs in current pcb
    pop ax                            ;read original flags in current pcb
    mov [pcb + bx + 26], ax           ;save flags in current pcb
    mov [pcb + bx + 22], ss           ;save ss in current pcb
    mov [pcb + bx + 14], sp           ;save sp in current pcb

    mov bx, [pcb + bx + 28]           ;read next pcb of this pcb
    mov [current], bx                 ;update current to new pcb
    mov cl, 5
    shl bx, cl                        ;multiply by 32 for pcb start

    mov cx, [pcb + bx + 4]            ;read cx of new process
    mov dx, [pcb + bx + 6]            ;read dx of new process
    mov si, [pcb + bx + 8]            ;read si of new process
    mov di, [pcb + bx + 10]           ;read di of new process
    mov bp, [pcb + bx + 12]           ;read bp of new process
    mov es, [pcb + bx + 24]           ;read es of new process
    mov ss, [pcb + bx + 22]           ;read ss of new process
    mov sp, [pcb + bx + 14]           ;read sp of new process

    push word [pcb + bx + 26]         ;push flags of new process
    push word [pcb + bx + 18]         ;push cs of new process
    push word [pcb + bx + 16]         ;push ip of new process
    push word [pcb + bx + 20]         ;push ds of new process

    mov al, 0x20
    out 0x20, al                      ;send EOI to PIC

    mov ax, [pcb + bx + 0]            ;read ax of new process
    mov bx, [pcb + bx + 2]            ;read bx of new process
    pop ds                            ;read ds of new process
    iret

start:
    xor ax, ax
    mov es, ax              ;point es to IVT bse

    ;change timer here

    cli
    mov word [es:8*4], timer              ;hook timer interrupt
    mov [es:8*4 + 2], cs
    Sti

    nextKey:
        xor ah, ah          ;service 0 - get keyStroke
        int 0x16            ;bios keyboard services

        push cs             ;use current code segment
        mov ax, myTask
        push ax             ;use mytask as offset
        push word [lineNo]  ;thread parameter
        call initPcb        ;register the thread

        inc word [lineNo]   ;update line number

        jmp nextKey         ;wait for next keypress