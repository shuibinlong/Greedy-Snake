.data
MY_FOOD_X       word ?
MY_FOOD_Y       word ?
MY_FOOD_SP_X    word ?
MY_FOOD_SP_Y    word ?
MY_FOOD_SP_FLAG byte ?
MY_FOOD_SP_INIT byte "☰☰☰☰☰☰☰☰☰☰☰☰☰☰☰☰☰☰☰☰☰☰☰☰☰☰☰☰☰☰☰☰☰☰☰☰☰☰☰☰☰☰",0

.code
InitFood proc
    mov MY_FOOD_CNT,0
    mov MY_FOOD_SP_BAR,0
    mov MY_FOOD_SP_FLAG,0
    ret
InitFood endp

DrawBigFood proc
    local flag:byte
    mov flag,1
    .while flag
        invoke Random,11,38
        mov MY_FOOD_SP_X,ax
        mov cx,ax
        invoke Random,2,29
        mov MY_FOOD_SP_Y,ax
        .if cx==MY_FOOD_X && ax==MY_FOOD_Y
            .continue
        .endif
        mov flag,0
        movzx ecx,MY_SNAKE_LEN
        mov edx,0
myDrawBigCheck:
        push ecx
        push edx
        mov esi,offset MY_SNAKE_POS
        add esi,edx
        mov ax,word ptr[esi]
		mov cx,ax
        mov ax,word ptr[esi+2]
		.if flag==0 && MY_FOOD_SP_X==cx && MY_FOOD_SP_Y==ax
			mov flag,1
		.endif
        pop edx
        pop ecx
        add edx,4
        loop myDrawBigCheck
    .endw
    mov MY_FOOD_SP_BAR,42
    ; 绘制初始化进度条
    invoke SetFontColor,11
    invoke _SetCursorPosition,29,0
    invoke crt_printf,addr MY_FOOD_SP_INIT
    ; 绘制奖励食物
    invoke SetFontColor,18
    invoke PrintBlock,MY_FOOD_SP_X,MY_FOOD_SP_Y
    invoke SetFontColor,0
    ret
DrawBigFood endp

DrawFood proc
    local flag:byte    
    mov flag,1
    .while flag
        invoke Random,11,38
        mov MY_FOOD_X,ax
        invoke Random,2,29
        mov MY_FOOD_Y,ax
        mov flag,0
        movzx ecx,MY_SNAKE_LEN
        mov edx,0
myDrawCheck:
        push ecx
        push edx
        mov esi,offset MY_SNAKE_POS
        add esi,edx
        mov ax,word ptr[esi]
		mov cx,ax
        mov ax,word ptr[esi+2]
		.if flag==0 && MY_FOOD_X==cx && MY_FOOD_Y==ax
			mov flag,1
		.endif
        pop edx
        pop ecx
        add edx,4
        loop myDrawCheck
    .endw
    invoke SetFontColor,13
    invoke PrintFood,MY_FOOD_X,MY_FOOD_Y
    mov ax,MY_FOOD_CNT
    inc ax
    mov MY_FOOD_CNT,ax
    ; 是否生成奖励食物
    mov dx,0
    mov ax,MY_FOOD_CNT
    mov cx,5
    div cx
    .if dx==0
        invoke DrawBigFood
    .endif
    ret
DrawFood endp

BonusTwinkling proc
    local tmp_x:word
    invoke SetFontColor,18
    .if MY_FOOD_SP_FLAG==0
        invoke PrintBlank,MY_FOOD_SP_X,MY_FOOD_SP_Y
        mov MY_FOOD_SP_FLAG,1
    .else
        invoke PrintBlock,MY_FOOD_SP_X,MY_FOOD_SP_Y
        mov MY_FOOD_SP_FLAG,0
    .endif
    mov ax,MY_FOOD_SP_BAR
    dec ax
    mov MY_FOOD_SP_BAR,ax
    invoke SetFontColor,0
    mov ax,29
    add ax,MY_FOOD_SP_BAR
    mov tmp_x,ax
    invoke _SetCursorPosition,tmp_x,0
    invoke crt_printf,addr MY_BLANK
    .if MY_FOOD_SP_BAR==0
        invoke PrintBlank,MY_FOOD_SP_X,MY_FOOD_SP_Y
    .endif
    ret
BonusTwinkling endp