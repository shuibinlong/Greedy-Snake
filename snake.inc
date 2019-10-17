.data
MY_SNAKE_ACC byte ?
MY_SNAKE_DIR byte ? ; 0 - up, 1 - down, 2 - left, 3 - right
MY_SNAKE_LEN word ? 
MY_SNAKE_POS word 300 dup(?)
;----------------------------------------------------------
SNAKE_X word ?
SNAKE_Y word ?

.code
InitSnake proc
    ; 初始蛇态，长度为3
    mov esi,0
    mov ebx,offset MY_SNAKE_POS
    mov word ptr [ebx+esi],14
    mov word ptr [ebx+esi+2],8
    add esi,4
    mov word ptr [ebx+esi],15
    mov word ptr [ebx+esi+2],8
    add esi,4
    mov word ptr [ebx+esi],16
	mov word ptr [ebx+esi+2],8
	add esi,4
    shr esi,2
    mov MY_SNAKE_LEN,si
    mov MY_SNAKE_DIR,3
    mov MY_SCORE,0
    mov MY_SNAKE_ACC,0
    ret
InitSnake endp

DrawSnake proc  ; 画出蛇身
    invoke SetFontColor,6
    movzx ecx,MY_SNAKE_LEN
    mov edx,0
mySnakeDraw:
    push ecx
    push edx
    mov esi,offset MY_SNAKE_POS
    add esi,edx
    mov ax,word ptr[esi]
    mov SNAKE_X,ax
    mov ax,word ptr[esi+2]
    mov SNAKE_Y,ax
    .if ecx==1
        invoke SetFontColor,15
    .endif
    invoke PrintCircle,SNAKE_X,SNAKE_Y
    pop edx
    pop ecx
    add edx,4
    loop mySnakeDraw
    ret
DrawSnake endp

OverEdge proc   ; 判断蛇头是否碰到墙壁，0-未碰壁，1-碰壁
    local X:word,Y:word

    mov ebx,offset MY_SNAKE_POS
    movzx esi,MY_SNAKE_LEN
    sub esi,1
    imul esi,4
    mov ax,word ptr[ebx+esi]
    mov X,ax
    mov ax,word ptr[ebx+esi+2]
    mov Y,ax
    mov eax,1
    .if X>10 && X<39 && Y>1 && Y<30
        dec eax
    .endif
    ret
OverEdge endp

HitItself proc  ; 判断蛇头是否和蛇身重合,0-不重合，1-重合
    local X:word,Y:word
    local flag:byte

    ; 获得蛇头位置
    mov ebx,offset MY_SNAKE_POS
    movzx esi,MY_SNAKE_LEN
    dec esi
    imul esi,4
    mov ax,word ptr[ebx+esi]
    mov X,ax
    mov ax,word ptr[ebx+esi+2]
    mov Y,ax

    ; 遍历蛇身
    mov flag,0
    movzx ecx,MY_SNAKE_LEN
    dec ecx                 ; 除去蛇头
    mov edx,0
myHitLoop:
    push ecx
    push edx
    mov esi,offset MY_SNAKE_POS
    add esi,edx
    mov ax,word ptr[esi]
    mov cx,ax
    mov ax,word ptr[esi+2]
    .if flag==0 && X==cx && Y==ax
        mov flag,1
    .endif
    pop edx
    pop ecx
    add edx,4
    loop myHitLoop

    movzx eax,flag
    ret
HitItself endp

isGetFood proc  ; 判断是否吃到食物，0-没吃到，1-吃到
    mov ebx,offset MY_SNAKE_POS
    movzx esi,MY_SNAKE_LEN
    dec esi
    imul esi,4
    mov cx,word ptr[ebx+esi]
    mov dx,word ptr[ebx+esi+2]
    mov eax,0
    .if cx==MY_FOOD_X && dx==MY_FOOD_Y
        inc eax
    .endif
    ret
isGetFood endp

isGetBonus proc  ; 判断是否吃到bonus食物，0-没吃到，1-吃到
    mov ebx,offset MY_SNAKE_POS
    movzx esi,MY_SNAKE_LEN
    dec esi
    imul esi,4
    mov cx,word ptr[ebx+esi]
    mov dx,word ptr[ebx+esi+2]
    mov eax,0
    .if cx==MY_FOOD_SP_X && dx==MY_FOOD_SP_Y
        inc eax
    .endif
    ret
isGetBonus endp

Growing proc    ; 蛇身前进一格
    mov ebx,offset MY_SNAKE_POS
    movzx esi,MY_SNAKE_LEN
    dec esi
    imul esi,4
    mov cx,word ptr[ebx+esi]
    mov dx,word ptr[ebx+esi+2]
    add esi,4
    .if MY_SNAKE_DIR==0     ; up
        dec dx
    .elseif MY_SNAKE_DIR==1 ; down
        inc dx
    .elseif MY_SNAKE_DIR==2 ; left
        dec cx
    .elseif MY_SNAKE_DIR==3 ; right
        inc cx
    .endif
    mov [ebx+esi],cx
    mov [ebx+esi+2],dx
    mov ax,MY_SNAKE_LEN
    inc ax
    mov MY_SNAKE_LEN,ax
    invoke DrawSnake
    ret
Growing endp

Moving proc
    local X:word,Y:word
    ; 删除蛇尾
    mov esi,offset MY_SNAKE_POS
    mov ax,[esi]
    mov X,ax
    mov ax,[esi+2]
    mov Y,ax
    invoke PrintBlank,X,Y

    ; 原蛇身平移一格
    movzx ecx,MY_SNAKE_LEN
    dec ecx
    mov edx,0
myMovLoop:
    mov esi,offset MY_SNAKE_POS
    add esi,edx
    mov ax,[esi+4]
    mov [esi],ax
    mov ax,[esi+6]
    mov [esi+2],ax
	add edx,4
    loop myMovLoop
    mov ax,MY_SNAKE_LEN
    dec ax
    mov MY_SNAKE_LEN,ax

    invoke Growing  ; 蛇头前进
    ret
Moving endp

RefreshDirection proc  ; 读取键盘输入，0-ESC键，1-方向键，2-其它键，3-未按下任何按键
    invoke crt__kbhit
    .if eax <= 0
        mov eax,3
        ret
    .endif
    invoke crt__getch
    .if eax==224
        invoke crt__getch
        .if eax==72     ; up
            .if MY_SNAKE_DIR!=1
                .if MY_SNAKE_DIR==0
                    mov MY_SNAKE_ACC,1
                .else
                    mov MY_SNAKE_DIR,0
                .endif
                invoke SetFontColor,MY_MENU_COL
                invoke _SetCursorPosition,9,10
                invoke crt_printf,addr MENU_DIR_UP
            .endif
        .elseif eax==80 ; down
            .if MY_SNAKE_DIR!=0
                .if MY_SNAKE_DIR==1
                    mov MY_SNAKE_ACC,1
                .else
                    mov MY_SNAKE_DIR,1
                .endif
                invoke SetFontColor,MY_MENU_COL
                invoke _SetCursorPosition,9,10
                invoke crt_printf,addr MENU_DIR_DOWN
            .endif
        .elseif eax==75 ; left
            .if MY_SNAKE_DIR!=3
                .if MY_SNAKE_DIR==2
                    mov MY_SNAKE_ACC,1
                .else
                    mov MY_SNAKE_DIR,2
                .endif
                invoke SetFontColor,MY_MENU_COL
                invoke _SetCursorPosition,9,10
                invoke crt_printf,addr MENU_DIR_LEFT
            .endif
        .elseif eax==77 ; right
            .if MY_SNAKE_DIR!=2
                .if MY_SNAKE_DIR==3
                    mov MY_SNAKE_ACC,1
                .else
                    mov MY_SNAKE_DIR,3
                .endif
                invoke SetFontColor,MY_MENU_COL
                invoke _SetCursorPosition,9,10
                invoke crt_printf,addr MENU_DIR_RIGHT
            .endif
        .endif
        mov eax,1
    .elseif eax==27     ; ESC
        mov eax,0
    .else
        mov eax,2
    .endif
    ret
RefreshDirection endp

; RefreshDirection proc  ; 读取键盘输入，0-ESC键，1-其它键，2-未按下任何按键
;     call ReadKey
;     jnz LookForKey
;     mov eax,2
;     ret
; LookForKey:
;     .if al!=27
;         .if ah==72      ; up
;             .if MY_SNAKE_DIR!=1 && MY_SNAKE_DIR !=0
;                 mov MY_SNAKE_DIR,0
;                 invoke SetFontColor,MY_MENU_COL
;                 invoke _SetCursorPosition,9,10
;                 invoke crt_printf,addr MENU_DIR_UP
;             .endif
;         .elseif ah==80  ; down
;             .if MY_SNAKE_DIR!=0 && MY_SNAKE_DIR !=1
;                 mov MY_SNAKE_DIR,1
;                 invoke SetFontColor,MY_MENU_COL
;                 invoke _SetCursorPosition,9,10
;                 invoke crt_printf,addr MENU_DIR_DOWN
;             .endif
;         .elseif ah==75  ; left
;             .if MY_SNAKE_DIR!=3 && MY_SNAKE_DIR !=2
;                 mov MY_SNAKE_DIR,2
;                 invoke SetFontColor,MY_MENU_COL
;                 invoke _SetCursorPosition,9,10
;                 invoke crt_printf,addr MENU_DIR_LEFT
;             .endif
;         .elseif ah==77  ; right
;             .if MY_SNAKE_DIR!=2 && MY_SNAKE_DIR !=3
;                 mov MY_SNAKE_DIR,3
;                 invoke SetFontColor,MY_MENU_COL
;                 invoke _SetCursorPosition,9,10
;                 invoke crt_printf,addr MENU_DIR_RIGHT
;             .endif
;         .endif
;         mov eax,1
;     .else   ; ESC
;         mov eax,0
;     .endif
;     ret
; RefreshDirection endp