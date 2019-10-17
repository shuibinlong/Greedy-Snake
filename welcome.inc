.data 
CMD_PAUSE byte "pause",0
; ----------------------------------------------
MY_WELCOME byte "欢迎来到贪吃蛇俱乐部",0
; ----------------------------------------------
MY_V    word 0,14
        word 1,14
        word 2,15
        word 3,16
        word 4,17
        word 5,18
        word 6,17
        word 7,16
        word 8,15
        word 9,14

MY_LAB  word 7,10 ; S
		word 8,10
		word 6,11
		word 7,12
		word 8,13
		word 6,14
		word 7,14

	    word 10,10 ; N
		word 10,11
		word 10,12
		word 10,13
		word 10,14
		word 11,11
		word 12,12
		word 13,13
		word 14,10
		word 14,11
		word 14,12
		word 14,13
		word 14,14

		word 16,14 ; A
		word 17,13
		word 18,12
		word 19,11
		word 19,12
		word 20,10
		word 20,12
		word 21,11
		word 21,12
		word 22,12
		word 23,13
		word 24,14

		word 26,10 ; K
		word 26,11
		word 26,12
		word 26,13
		word 26,14
		word 27,12
		word 28,11
		word 28,13
		word 29,10
		word 29,14

		word 31,10 ; E
		word 31,11
		word 31,12
		word 31,13
		word 31,14
		word 32,10
		word 32,12
		word 32,14
		word 33,10
		word 33,12
		word 33,14


WEL_X    word ?
WEL_Y    word ?

.code
DrawBoard proc
	mov ecx,53
	mov edx,0
myWelDraw:
	push ecx
    push edx
	mov ebx,offset MY_LAB
	add ebx,edx
    mov esi,0
	mov ax,word ptr[ebx+esi]
    mov WEL_X,ax
	add esi,2
	mov ax,word ptr[ebx+esi]
	mov WEL_Y,ax
    invoke PrintBlock,WEL_X,WEL_Y
    pop edx
	pop ecx
    add edx,4
	loop myWelDraw
	ret
DrawBoard endp

ShowWelcome proc
    invoke SetFontColor,5
    invoke DrawBoard
    invoke SetFontColor,2
    invoke SetCursorPosition,15,26
    invoke crt_printf,addr MY_WELCOME
    invoke SetFontColor,3
    invoke SetCursorPosition,13,27
    invoke crt_system,addr CMD_PAUSE
    ret
ShowWelcome endp