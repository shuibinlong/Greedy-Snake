.data
STD_OUTPUT_HANDLE   EQU -11

FOREGROUND_BLUE     EQU 1
BACKGROUND_BLUE     EQU 16
BACKGROUND_GREEN    EQU 32
BACKGROUND_RED      EQU 64
; ---------------------------
MY_HADNLE   dword ?

.code
; 设置光标位置
_SetCursorPosition proc X:word,Y:word
    local pos:coord
    mov ax,X
    mov pos.X,ax
    mov ax,Y
    mov pos.Y,ax
    invoke SetConsoleCursorPosition,MY_HADNLE,pos
    ret
_SetCursorPosition endp

SetCursorPosition proc X:word,Y:word
    local pos:coord
    mov ax,X
    add ax,ax
    mov pos.X,ax
    mov ax,Y
    mov pos.Y,ax
    invoke SetConsoleCursorPosition,MY_HADNLE,pos
    ret
SetCursorPosition endp

; 设置文本颜色
SetFontColor proc ColorID:word
    invoke SetConsoleTextAttribute,MY_HADNLE,ColorID
	ret
SetFontColor endp

; 设置背景颜色
SetBackColor proc
    invoke SetConsoleTextAttribute,MY_HADNLE,(FOREGROUND_BLUE or BACKGROUND_BLUE or BACKGROUND_GREEN or BACKGROUND_RED)
    ret
SetBackColor endp

; 随机数
Random proc L:word,R:word
    movzx eax,R
    call RandomRange
    .if ax<L
        add ax,L
    .endif
    ret
Random endp