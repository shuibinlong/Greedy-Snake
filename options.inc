.data
MY_LABEL_BLANKS byte "                                                    ",0
MY_LABEL_DIFF   byte "请选择游戏难度：",0
MY_LABEL_KEY    byte "(上下键选择，回车确认)",0
MY_LABEL_EASY   byte "简单模式",0
MY_LABEL_NORM   byte "普通模式",0
MY_LABEL_MID    byte "中等模式",0
MY_LABEL_HARD   byte "困难模式",0

MY_MENU_BOARD1  byte "╔══════════════════════════════════════╗",0
MY_MENU_BOARD2  byte "║                                      ║",0
MY_MENU_BOARD3  byte "╠══════════════════════════════════════╣",0
MY_MENU_BOARD4  byte "╚══════════════════════════════════════╝",0
MY_MENU_TITLE   byte "游戏结束",0
MY_MENU_MSG1    byte "很遗憾，你挂了！",0
MY_MENU_MSG2    byte "方向盘还是不够熟练诶TAT",0
MY_MENU_MSG3    byte "本局得分：",0
MY_MENU_MSG4    byte "本局评价：",0
MY_MENU_MSG5    byte "这位蛇勇士，是否重新开始？",0
MY_MENU_YES     byte "好鸭，再战一次",0
MY_MENU_NO      byte "不辽，还是学习有意思",0

.code
ShowSelection proc
    invoke SetFontColor,3               ; 覆盖原先画面
    invoke SetCursorPosition,13,26
    invoke crt_printf,addr MY_LABEL_BLANKS
    invoke SetCursorPosition,13,27
    invoke crt_printf,addr MY_LABEL_BLANKS
    
    invoke SetCursorPosition,6,21
    invoke crt_printf,addr MY_LABEL_DIFF
    invoke SetCursorPosition,6,22
    invoke crt_printf,addr MY_LABEL_KEY
    invoke SetCursorPosition,27,22
    mov MY_DIFFICULTY,1
    invoke SetBackColor                 ; 第一个选项默认选中
    invoke crt_printf,addr MY_LABEL_EASY
    invoke SetCursorPosition,27,24
    invoke SetFontColor,3
    invoke crt_printf,addr MY_LABEL_NORM
    invoke SetCursorPosition,27,26
    invoke crt_printf,addr MY_LABEL_MID
    invoke SetCursorPosition,27,28
    invoke crt_printf,addr MY_LABEL_HARD
    invoke SetCursorPosition,0,31

chooseLabel:
    call ReadChar ; 从缓冲区读入字符
    mov MY_CHAR,ah
    cmp MY_CHAR,72
    je chooseUp
    cmp MY_CHAR,80
    je chooseDown
    cmp MY_CHAR,28
    je chooseEnter
    jmp chooseBack

chooseUp:           ; 上方向键
    cmp MY_DIFFICULTY,1
    jle chooseBack
    cmp MY_DIFFICULTY,2
    je chooseUp_2
    cmp MY_DIFFICULTY,3
    je chooseUp_3
    cmp MY_DIFFICULTY,4
    je chooseUp_4
    jmp chooseBack

chooseUp_2:
    invoke SetCursorPosition,27,22          ; 给待选中项设置背景色
    invoke SetBackColor
    invoke crt_printf,addr MY_LABEL_EASY

    invoke SetCursorPosition,27,24          ; 将已选中项取消背景色
    invoke SetFontColor,3
    invoke crt_printf,addr MY_LABEL_NORM
    mov ax,MY_DIFFICULTY
    dec ax
    mov MY_DIFFICULTY,ax
    jmp chooseBack

chooseUp_3:
    invoke SetCursorPosition,27,24
    invoke SetBackColor
    invoke crt_printf,addr MY_LABEL_NORM

    invoke SetCursorPosition,27,26
    invoke SetFontColor,3
    invoke crt_printf,addr MY_LABEL_MID
    mov ax,MY_DIFFICULTY
    dec ax
    mov MY_DIFFICULTY,ax
    jmp chooseBack

chooseUp_4:
    invoke SetCursorPosition,27,26
    invoke SetBackColor
    invoke crt_printf,addr MY_LABEL_MID

    invoke SetCursorPosition,27,28
    invoke SetFontColor,3
    invoke crt_printf,addr MY_LABEL_HARD
    mov ax,MY_DIFFICULTY
    dec ax
    mov MY_DIFFICULTY,ax
    jmp chooseBack

chooseDown:         ; 下方向键     
    cmp MY_DIFFICULTY,4
    jge chooseBack
    cmp MY_DIFFICULTY,1
    je chooseDown_1
    cmp MY_DIFFICULTY,2
    je chooseDown_2
    cmp MY_DIFFICULTY,3
    je chooseDown_3
    jmp chooseBack

chooseDown_1:
    invoke SetCursorPosition,27,24
    invoke SetBackColor
    invoke crt_printf,addr MY_LABEL_NORM
    
    invoke SetCursorPosition,27,22
    invoke SetFontColor,3
    invoke crt_printf,addr MY_LABEL_EASY
    mov ax,MY_DIFFICULTY
    inc ax
    mov MY_DIFFICULTY,ax
    jmp chooseBack

chooseDown_2:
    invoke SetCursorPosition,27,26
    invoke SetBackColor
    invoke crt_printf,addr MY_LABEL_MID
    
    invoke SetCursorPosition,27,24
    invoke SetFontColor,3
    invoke crt_printf,addr MY_LABEL_NORM
    mov ax,MY_DIFFICULTY
    inc ax
    mov MY_DIFFICULTY,ax
    jmp chooseBack

chooseDown_3:
    invoke SetCursorPosition,27,28
    invoke SetBackColor
    invoke crt_printf,addr MY_LABEL_HARD
    
    invoke SetCursorPosition,27,26
    invoke SetFontColor,3
    invoke crt_printf,addr MY_LABEL_MID
    mov ax,MY_DIFFICULTY
    inc ax
    mov MY_DIFFICULTY,ax
    jmp chooseBack

chooseBack:
    invoke SetCursorPosition,0,31
    jmp chooseLABEL

chooseEnter:    ; 回车键
    invoke SetCursorPosition,0,31
    mov ax,MY_DIFFICULTY    ; 根据难度选择速度，值越大速度越慢，值越小速度越快
    cmp ax,1
    mov MY_SPEED,120
    je outLABEL
    cmp ax,2
    mov MY_SPEED,90
    je outLABEL
    cmp ax,3
    mov MY_SPEED,60
    je outLABEL
    mov MY_SPEED,30

outLABEL:
	ret
ShowSelection endp

ShowDeathMenu proc  ; 游戏结束，绘制界面
    local key:word

    mov eax,100
    call Delay
    invoke SetFontColor,11
    invoke SetCursorPosition,10,8
    invoke crt_printf,addr MY_MENU_BOARD1
    invoke SetCursorPosition,10,9
    invoke crt_printf,addr MY_MENU_BOARD2
    invoke SetCursorPosition,10,10
    invoke crt_printf,addr MY_MENU_BOARD2
    invoke SetCursorPosition,10,11
    invoke crt_printf,addr MY_MENU_BOARD2
    invoke SetCursorPosition,10,12
    invoke crt_printf,addr MY_MENU_BOARD2
    invoke SetCursorPosition,10,13
    invoke crt_printf,addr MY_MENU_BOARD2
    invoke SetCursorPosition,10,14
    invoke crt_printf,addr MY_MENU_BOARD2
    invoke SetCursorPosition,10,15
    invoke crt_printf,addr MY_MENU_BOARD2
    invoke SetCursorPosition,10,16
    invoke crt_printf,addr MY_MENU_BOARD2
    invoke SetCursorPosition,10,17
    invoke crt_printf,addr MY_MENU_BOARD2
    invoke SetCursorPosition,10,18
    invoke crt_printf,addr MY_MENU_BOARD3
    invoke SetCursorPosition,10,19
    invoke crt_printf,addr MY_MENU_BOARD2
    invoke SetCursorPosition,10,20
    invoke crt_printf,addr MY_MENU_BOARD2
    invoke SetCursorPosition,10,21
    invoke crt_printf,addr MY_MENU_BOARD2
    invoke SetCursorPosition,10,22
    invoke crt_printf,addr MY_MENU_BOARD4

    invoke SetFontColor,14
    invoke SetCursorPosition,18,9
    invoke crt_printf,addr MY_MENU_TITLE
    invoke SetFontColor,MY_MENU_COL
    invoke SetCursorPosition,16,11
    invoke crt_printf,addr MY_MENU_MSG1
    invoke SetCursorPosition,14,13
    invoke crt_printf,addr MY_MENU_MSG2
    invoke SetCursorPosition,21,15
    movzx eax,MY_SCORE
    call WriteDec
    invoke PrintFood,21,17
    .if MY_SCORE>=5
        invoke PrintFood,22,17
        .if MY_SCORE>=15
            invoke PrintFood,23,17
            .if MY_SCORE>=30
                invoke PrintFood,24,17
                .if MY_SCORE>=50
                    invoke PrintFood,25,17
                .endif
            .endif
        .endif
    .endif
    invoke SetFontColor,6
    invoke SetCursorPosition,16,15
    invoke crt_printf,addr MY_MENU_MSG3
    invoke SetCursorPosition,16,17
    invoke crt_printf,addr MY_MENU_MSG4
    invoke SetFontColor,14
    invoke SetCursorPosition,11,19
    invoke crt_printf,addr MY_MENU_MSG5
    mov key,1
    invoke SetBackColor
    invoke SetCursorPosition,11,21
    invoke crt_printf,addr MY_MENU_YES
    invoke SetFontColor,MY_MENU_COL
    invoke _SetCursorPosition,39,21
    invoke crt_printf,addr MY_MENU_NO

chooseLoop:
    invoke SetCursorPosition,0,31
    call ReadChar
    mov MY_CHAR,ah
    .if MY_CHAR==75     ; left
        .if key==2
            invoke SetBackColor
            invoke SetCursorPosition,11,21
            invoke crt_printf,addr MY_MENU_YES
            invoke SetFontColor,MY_MENU_COL
            invoke _SetCursorPosition,39,21
            invoke crt_printf,addr MY_MENU_NO
            mov ax,key
            dec ax
            mov key,ax
        .endif
    .elseif MY_CHAR==77 ; right
        .if key==1
            invoke SetFontColor,MY_MENU_COL
            invoke SetCursorPosition,11,21
            invoke crt_printf,addr MY_MENU_YES
            invoke SetBackColor
            invoke _SetCursorPosition,39,21
            invoke crt_printf,addr MY_MENU_NO
            mov ax,key
            inc ax
            mov key,ax
        .endif
    .elseif MY_CHAR==28    ; enter
        jmp chooseOut
    .endif
    jmp chooseLoop

chooseOut:
    .if key==1
        mov eax,1
    .elseif key==2
        mov eax,0
    .endif
    ret
ShowDeathMenu endp 