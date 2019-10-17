.data
CMD_CLEAN 		byte "cls",0
MY_BLANKS 		byte "                ",0
MY_BLANKS_		byte "                                                ",0

.code
DrawGame proc
	call Clrscr	; 清空屏幕

	; 绘制地图
	invoke SetFontColor,3
	invoke InitMap
	invoke SetCursorPosition,0,31

	; 绘制侧边栏
	invoke DrawMainMenu
	invoke SetCursorPosition,0,31
	ret
DrawGame endp

UpdateScore proc bonus:word
	mov ax,bonus
	imul ax,MY_DIFFICULTY
	add ax,MY_SCORE
	mov MY_SCORE,ax
	invoke SetFontColor,MY_MENU_COL
	invoke _SetCursorPosition,9,8
	movzx eax,MY_SCORE
	call WriteDec
	ret
UpdateScore endp

Playing proc
	local tmpscore:word

	invoke InitSnake		; 初始化蛇
	invoke DrawSnake
	invoke InitFood			; 初始化食物属性
	invoke Drawfood

myGaming:		; 游戏二级循环
    invoke OverEdge
	cmp eax,0
	jne deathSnake
	invoke HitItself
	cmp eax,0
	jne deathSnake
	invoke SetCursorPosition,0,31
	invoke RefreshDirection
	.if eax==0	; 按下ESC
		invoke DrawESCMenu
		.if eax==1		; 继续游戏
			invoke SetCursorPosition,1,26
			invoke crt_printf,addr MY_BLANKS
			invoke SetCursorPosition,1,28
			invoke crt_printf,addr MY_BLANKS
			invoke SetCursorPosition,1,30
			invoke crt_printf,addr MY_BLANKS
			invoke SetCursorPosition,0,31
		.elseif eax==2	; 重新开始
			invoke PlaySound, offset MY_SOUND_BACKGROUND,NULL,131081
			invoke SetFontColor,0
			invoke crt_system,addr CMD_CLEAN
			invoke ShowWelcome
			invoke ShowSelection
			invoke PlaySound, offset NULL,NULL,NULL
    		invoke PlaySound, offset MY_SOUND_BEGIN,NULL,131073
			invoke DrawGame
			invoke InitSnake
			invoke DrawSnake
			invoke InitFood
			invoke Drawfood
			jmp myGaming
		.elseif eax==3	; 退出游戏
			mov eax,0
			ret
		.endif
	.endif
	invoke isGetFood
	.if eax==1	; 吃到食物
		invoke PlaySound, offset MY_SOUND_GROWTH,NULL,131073
		invoke Growing ; 蛇身增长
		invoke SetCursorPosition,0,31
		invoke UpdateScore,1
		invoke SetCursorPosition,0,31
		invoke Drawfood
		invoke SetCursorPosition,0,31
	.else		; 正常移动
		invoke Moving
    	invoke SetCursorPosition,0,31
	.endif
	.if MY_FOOD_SP_BAR>0	; 存在奖励食物
		invoke BonusTwinkling
		invoke SetCursorPosition,0,31
		invoke isGetBonus	; 吃到奖励食物
		.if eax==1
			invoke PlaySound, offset MY_SOUND_GROWTH,NULL,131073
			invoke Growing
			invoke SetCursorPosition,0,31
			mov ax,MY_FOOD_SP_BAR
			shr ax,2
			or ax,1
			mov tmpscore,ax
			invoke UpdateScore,tmpscore
			mov MY_FOOD_SP_BAR,0
			invoke _SetCursorPosition,29,0
			invoke crt_printf,addr MY_BLANKS_
			invoke SetCursorPosition,0,31
		.endif
	.endif
	movzx eax,MY_SPEED
	.if MY_SNAKE_ACC	; 如果方向键相同，则加速蛇的移动
		shr eax,1
		mov MY_SNAKE_ACC,0
	.endif
	call Delay
	jmp myGaming

deathSnake:	; 蛇死亡，游戏结束
	invoke PlaySound, offset NULL,NULL,NULL
	invoke PlaySound, offset MY_SOUND_DEATH,NULL,131073
	invoke ShowDeathMenu
	ret
Playing endp