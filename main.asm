include Irvine32.inc
include msvcrt.inc
include winmm.inc
include param.inc
include tool.inc
include point.inc
include welcome.inc
include options.inc
include map.inc
include food.inc
include snake.inc
include game.inc

includelib Irvine32.lib
includelib msvcrt.lib
includelib winmm.lib

.data
; ----------------------------------------------
CMD_CHINESE byte "chcp 65001",0
CMD_WINDOW_SIZE byte "mode con cols=82 lines=32",0 ; 32
CMD_WINDOW_TITLE byte "title Greedy Snake",0

.code
; 初始化
Init proc
    invoke GetStdHandle,STD_OUTPUT_HANDLE
    mov MY_HADNLE,eax
	invoke crt_system,addr CMD_CHINESE      ; 设置终端显示编码为UTF-8
    invoke crt_system,addr CMD_WINDOW_TITLE ; 设置窗口标题
    invoke crt_system,addr CMD_WINDOW_SIZE  ; 设置窗口大小
    ret
Init endp

main proc
	invoke Init
    
myGame:
    invoke PlaySound, OFFSET MY_SOUND_BACKGROUND,NULL,131081
    invoke crt_system,addr CMD_CLEAN    ; 重置屏幕
    invoke ShowWelcome                  ; 欢迎界面
    invoke ShowSelection                ; 选择难度
    invoke PlaySound, OFFSET MY_SOUND_BEGIN,NULL,131073
    invoke DrawGame                     ; 绘制游戏界面
    invoke Playing
    cmp eax,0
    jg myGame

	invoke SetCursorPosition,0,31
    invoke ExitProcess,0                ; 退出游戏
main endp

end main