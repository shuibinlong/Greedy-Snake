.data
MY_MAP  word 10,1,11,1,12,1,13,1,14,1,15,1,16,1,17,1,18,1,19,1,20,1,21,1,22,1,23,1,24,1,25,1,26,1,27,1,28,1,29,1
        word 30,1,31,1,32,1,33,1,34,1,35,1,36,1,37,1,38,1,39,1
        word 10,2,39,2,10,3,39,3,10,4,39,4,10,5,39,5,10,6,39,6,10,7,39,7,10,8,39,8,10,9,39,9,10,10,39,10,10,11,39,11
        word 10,12,39,12,10,13,39,13,10,14,39,14,10,15,39,15,10,16,39,16,10,17,39,17,10,18,39,18,10,19,39,19,10,20,39,20
        word 10,21,39,21,10,22,39,22,10,23,39,23,10,24,39,24,10,25,39,25,10,26,39,26,10,27,39,27,10,28,39,28,10,29,39,29
        word 10,30,11,30,12,30,13,30,14,30,15,30,16,30,17,30,18,30,19,30,20,30,21,30,22,30,23,30,24,30,25,30,26,30
        word 27,30,28,30,29,30,30,30,31,30,32,30,33,30,34,30,35,30,36,30,37,30,38,30,39,30
MAP_X   word ?
MAP_Y   word ?
;------------------------------------------------------------------------------------------------------------------------
MENU_TITLE_EN       byte    "Greedy Snake",0
MENU_TITLE_CN       byte    "贪吃蛇",0
MENU_DIFF           byte    "难度：",0
MENU_SPEED          byte    "速度：",0
MENU_SCORE          byte    "得分：",0
MENU_DIR            byte    "方向：",0
MENU_SUB_MENU       byte    "菜单：",0
MENU_INIT_SCORE     byte    "0",0
MENU_INIT_SPEED1    byte    "▂",0
MENU_INIT_SPEED2    byte    "▃",0
MENU_INIT_SPEED3    byte    "▅",0
MENU_INIT_SPEED4    byte    "▆",0
MENU_DIR_UP         byte    "向上运动",0
MENU_DIR_DOWN       byte    "向下运动",0
MENU_DIR_LEFT       byte    "向左运动",0
MENU_DIR_RIGHT      byte    "向右运动",0
MENU_BOARD1         byte    "╔══════════════╗",0
MENU_BOARD2         byte    "║              ║",0
MENU_BOARD3         byte    "╚══════════════╝",0
MENU_BOARD_TITLE    byte    "Hint",0
MENU_BOARD_MSG1     byte    "方向键移动",0
MENU_BOARD_MSG2     byte    "ESC键暂停游戏",0
MENU_AUTHOR_TITLE   byte    "作者：",0
MENU_AUTHOR_1       byte    "龙水彬",0
MENU_AUTHOR_2       byte    "吴兴勇",0
MENU_AUTHOR_3       byte    "向思疑",0
MENU_VERSION_TITLE  byte    "版本号：",0
MENU_VERSION        byte    "v1.1.0",0
MENU_SUB_STAY       byte    "继续游戏",0
MENU_SUB_RESTART    byte    "重新开始",0
MENU_SUB_EXIT       byte    "退出游戏",0           



.code
InitMap proc
    mov ecx,117
    mov edx,0
myMapDraw:
    push ecx
    push edx
	mov ebx,offset MY_MAP
	add ebx,edx
    mov esi,0
	mov ax,word ptr[ebx+esi]
    mov MAP_X,ax
	add esi,2
	mov ax,word ptr[ebx+esi]
	mov MAP_Y,ax
    invoke PrintBlock,MAP_X,MAP_Y
    mov eax,5
    call Delay
    pop edx
	pop ecx
    add edx,4
	loop myMapDraw
    ret
InitMap endp

DrawMainMenu proc
    ; 标题
    invoke SetFontColor,10
    invoke SetCursorPosition,2,1
    invoke crt_printf,addr MENU_TITLE_EN
    invoke _SetCursorPosition,7,2
    invoke crt_printf,addr MENU_TITLE_CN

    ; 难度、得分、速度
    invoke SetFontColor,6
    invoke SetCursorPosition,1,4
    invoke crt_printf,addr MENU_DIFF
    invoke _SetCursorPosition,9,4
    cmp MY_DIFFICULTY,1
    je diffColor_1
    cmp MY_DIFFICULTY,2
    je diffColor_2
    cmp MY_DIFFICULTY,3
    je diffColor_3
    mov MY_MENU_COL,12
    invoke SetFontColor,12  ; Red
    invoke crt_printf,addr MY_LABEL_HARD
    invoke _SetCursorPosition,9,6
    invoke crt_printf,addr MENU_INIT_SPEED1
    invoke _SetCursorPosition,11,6
    invoke crt_printf,addr MENU_INIT_SPEED2
    invoke _SetCursorPosition,13,6
    invoke crt_printf,addr MENU_INIT_SPEED3
    invoke _SetCursorPosition,15,6
    invoke crt_printf,addr MENU_INIT_SPEED4
    invoke _SetCursorPosition,9,8
    invoke crt_printf,addr MENU_INIT_SCORE
    invoke _SetCursorPosition,9,10
    invoke crt_printf,addr MENU_DIR_RIGHT
    jmp diffOut

diffColor_1:
    mov MY_MENU_COL,15
    invoke SetFontColor,15  ; White
    invoke crt_printf,addr MY_LABEL_EASY
    invoke _SetCursorPosition,9,6
    invoke crt_printf,addr MENU_INIT_SPEED1
    invoke _SetCursorPosition,9,8
    invoke crt_printf,addr MENU_INIT_SCORE
    invoke _SetCursorPosition,9,10
    invoke crt_printf,addr MENU_DIR_RIGHT
    jmp diffOut

diffColor_2:
    mov MY_MENU_COL,11
    invoke SetFontColor,11  ; Blue
    invoke crt_printf,addr MY_LABEL_NORM
    invoke _SetCursorPosition,9,6
    invoke crt_printf,addr MENU_INIT_SPEED1
    invoke _SetCursorPosition,11,6
    invoke crt_printf,addr MENU_INIT_SPEED2
    invoke _SetCursorPosition,9,8
    invoke crt_printf,addr MENU_INIT_SCORE
    invoke _SetCursorPosition,9,10
    invoke crt_printf,addr MENU_DIR_RIGHT
    jmp diffOut

diffColor_3:
    mov MY_MENU_COL,13
    invoke SetFontColor,13  ; Pink
    invoke crt_printf,addr MY_LABEL_MID
    invoke _SetCursorPosition,9,6
    invoke crt_printf,addr MENU_INIT_SPEED1
    invoke _SetCursorPosition,11,6
    invoke crt_printf,addr MENU_INIT_SPEED2
    invoke _SetCursorPosition,13,6
    invoke crt_printf,addr MENU_INIT_SPEED3
    invoke _SetCursorPosition,9,8
    invoke crt_printf,addr MENU_INIT_SCORE
    invoke _SetCursorPosition,9,10
    invoke crt_printf,addr MENU_DIR_RIGHT
    jmp diffOut

diffOut:
    invoke SetFontColor,6
    invoke SetCursorPosition,1,6
    invoke crt_printf,addr MENU_SPEED
    invoke SetCursorPosition,1,8
    invoke crt_printf,addr MENU_SCORE
    invoke SetCursorPosition,1,10
    invoke crt_printf,addr MENU_DIR

    ; 操作声明
    invoke _SetCursorPosition,1,12
    invoke crt_printf,addr MENU_BOARD1
    invoke _SetCursorPosition,1,13
    invoke crt_printf,addr MENU_BOARD2
    invoke _SetCursorPosition,1,14
    invoke crt_printf,addr MENU_BOARD2
    invoke _SetCursorPosition,1,15
    invoke crt_printf,addr MENU_BOARD2
    invoke _SetCursorPosition,1,16
    invoke crt_printf,addr MENU_BOARD2
    invoke _SetCursorPosition,1,17
    invoke crt_printf,addr MENU_BOARD3
    invoke _SetCursorPosition,7,13
    invoke SetFontColor,7
    invoke crt_printf,addr MENU_BOARD_TITLE
    invoke SetFontColor,15
    invoke _SetCursorPosition,4,15
    invoke crt_printf,addr MENU_BOARD_MSG1
    invoke _SetCursorPosition,3,16
    invoke crt_printf,addr MENU_BOARD_MSG2

    ; 关于作者
    invoke SetFontColor,6
    invoke SetCursorPosition,1,19
    invoke crt_printf,addr MENU_AUTHOR_TITLE
    invoke SetFontColor,14
    invoke _SetCursorPosition,9,19
    invoke crt_printf,addr MENU_AUTHOR_1
    invoke _SetCursorPosition,9,20
    invoke crt_printf,addr MENU_AUTHOR_2
    invoke _SetCursorPosition,9,21
    invoke crt_printf,addr MENU_AUTHOR_3

    ; 版本号
    invoke SetFontColor,6
    invoke SetCursorPosition,1,23
    invoke crt_printf,addr MENU_VERSION_TITLE
    invoke SetFontColor,15
    invoke SetCursorPosition,5,23
    invoke crt_printf,addr MENU_VERSION
    
    ret
DrawMainMenu endp

DrawESCMenu proc
    local key:word
    ; 默认界面
    invoke SetFontColor,6
    invoke SetCursorPosition,1,26
    invoke crt_printf,addr MENU_SUB_MENU
    invoke _SetCursorPosition,9,26
    invoke SetBackColor
    invoke crt_printf,addr MENU_SUB_STAY
    invoke SetCursorPosition,0,31
    mov key,1
    mov eax,50
    call Delay
    invoke _SetCursorPosition,9,28
    invoke SetFontColor,MY_MENU_COL
    invoke crt_printf,addr MENU_SUB_RESTART
    invoke SetCursorPosition,0,31
    mov eax,50
    call Delay
    invoke _SetCursorPosition,9,30
    invoke crt_printf,addr MENU_SUB_EXIT
    
    ; 选择监控
chooseLoop:
    invoke SetCursorPosition,0,31
    call ReadChar
    mov MY_CHAR,ah
    .if MY_CHAR==72         ; up
        .if key==2
            invoke _SetCursorPosition,9,26
            invoke SetBackColor
            invoke crt_printf,addr MENU_SUB_STAY
            invoke _SetCursorPosition,9,28
            invoke SetFontColor,MY_MENU_COL
            invoke crt_printf,addr MENU_SUB_RESTART
            mov ax,key
            dec ax
            mov key,ax
        .elseif key==3
            invoke _SetCursorPosition,9,28
            invoke SetBackColor
            invoke crt_printf,addr MENU_SUB_RESTART
            invoke SetFontColor,MY_MENU_COL
            invoke _SetCursorPosition,9,30
            invoke crt_printf,addr MENU_SUB_EXIT
            mov ax,key
            dec ax
            mov key,ax
        .endif
    .elseif MY_CHAR==80    ; down
        .if key==1
            invoke _SetCursorPosition,9,26
            invoke SetFontColor,MY_MENU_COL
            invoke crt_printf,addr MENU_SUB_STAY
            invoke _SetCursorPosition,9,28
            invoke SetBackColor
            invoke crt_printf,addr MENU_SUB_RESTART
            mov ax,key
            inc ax
            mov key,ax
        .elseif key==2
            invoke _SetCursorPosition,9,28
            invoke SetFontColor,MY_MENU_COL
            invoke crt_printf,addr MENU_SUB_RESTART
            invoke _SetCursorPosition,9,30
            invoke SetBackColor
            invoke crt_printf,addr MENU_SUB_EXIT
            mov ax,key
            inc ax
            mov key,ax
        .endif
    .elseif MY_CHAR==28    ; enter
        jmp chooseOut
    .endif
    jmp chooseLoop

chooseOut:
    movzx eax,key
    ret
DrawESCMenu endp