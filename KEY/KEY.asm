;支持长按短按
;KEYTmp	 : 按键状态寄存器
;KEYSave : 按键保存寄存器 

;将对应按键保存在 KEYTmp，在处理按键时可直接判断KEYn来处理任务
;KEYTmp			EQU			50H
;DEFINE			KEY1		KEYTmp,0
;DEFINE			KEY2		KEYTmp,1
;DEFINE			KEY3		KEYTmp,2
;DEFINE			KEY4		KEYTmp,3

KEY_pro:
		btfss		fKEY1ms
		return	
		bcf			fKEY1ms
		
		;此处添加读取按键操作
		;将对应按键保存在 KEYTmp, 低电平表示按键使能
		
		movlw		0ffh
		andwf		KEYTmp		
		
		xorwf		KEYSave,w
		btfss		status,z
		goto		KEY_Update
		
		incf		KEYms,f
		
		movlw		0ffh
		xorwf		KEYTmp,w
		goto		$+3
		clrf		KEYms
		return
		
		movlw		50
		xorwf		KEYms,w
		btfsc		status,z
		goto		KEY_Enable
		
		movlw		200			;长按 100ms执行一次，修改此处可调整频率
		xorwf		KEYms,w		
		btfsc		status,z
		goto		KEY_Enable
		
		return

KEY_Enable:
		movlw		100
		movwf		KEYms
		
		btfss		fKEY	;屏蔽此三行代码可实现长按
		return
		bsf			fKEY
		
		;此处添加对应按键动作处理
		;btfss		KEYx			
		;goto		KEYx_Enable
		
		return

PT1_Update:
		movfw		KEYTmp
		movwf		KEYSave		
		clrf		KEYLongTim
		clrf		KEYms
		bcf			fKEY
		
		return

		
		
	

		
		
		
		
		
		
		
		
		
		
		
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	