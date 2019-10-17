.data
MY_BLOCK    byte "■",0
MY_CIRCLE   byte "●",0
MY_FOOD     byte "★",0
MY_BLANK    byte "  ",0 

.code 
PrintBlock proc X:word,Y:word
    invoke SetCursorPosition,X,Y
    invoke crt_printf,addr MY_BLOCK
    ret
PrintBlock endp

PrintCircle proc X:word,Y:word
    invoke SetCursorPosition,X,Y
    invoke crt_printf,addr MY_CIRCLE
    ret
PrintCircle endp

PrintFood proc X:word,Y:word
    invoke SetCursorPosition,X,Y
    invoke crt_printf,addr MY_FOOD
    ret
PrintFood endp

PrintBlank proc X:word,Y:word
    invoke SetCursorPosition,X,Y
    invoke crt_printf,addr MY_BLANK
    ret
PrintBlank endp