;֧�ֳ����̰�
;PT1Tmp	 : ����״̬�Ĵ���
;PT1Save : ��������Ĵ��� 
KEY_pro:
		btfss		KEY1msflag
		return	
		bcf			KEY1msflag
			
		
		
		movlw		00001000b
		andwf		PT1,w
		movwf		PT1Tmp
		
		xorwf		PT1Save,w
		btfss		status,z
		goto		PT1_Update
		
		incf		KEYms,f
		
		movlw		00001000b
		xorwf		PT1Tmp,w
		goto		$+3
		clrf		KEYms
		return
		
		movlw		50
		xorwf		KEYms,w
		btfsc		status,z
		goto		PT1_Enable
		
		movlw		200			;���� 100msִ��һ��
		xorwf		KEYms,w
		btfsc		status,z
		goto		PT1_Enable
		
		return

PT1_Enable:
		movlw		100
		movwf		KEYms
							
		;�˴���Ӷ�Ӧ������������
		;btfss		KEY			
		;goto		KEY_Enable
		
		return

PT1_Update:
		movfw		PT1Tmp
		movwf		PT1Save		
		clrf		KEYLongTim
		clrf		KEYms
		bcf			keyflag
		
		btfsc		KEY		
		bcf			keyEnflag
		return

Buzz_B:
		bsf			buzzflag	
		movlw		1
		movwf		buzzTim	
		return		
Buzz_BB:
		bsf			buzzflag
		movlw		3
		movwf		buzzTim		
		return
Buzz_B_BB:			
		bsf			buzzflag	
		movlw		6
		movwf		buzzTim			
		return		
; ��������ʱ		
Buzz_pro:
		btfss		buzz1sflag
		return
		bcf			buzz1sflag
		
		btfss		workflag
		return
		
		movlw		1
		subwf		workSecond,w
		btfss		status,c
		goto		$+3
		decf		workSecond,f
		return
		
		movlw		1
		subwf		workNum,w
		btfss		status,c
		goto		$+10 ;8			
		decf		workNum,f
		movlw		29
		movwf		workSecond
		
		btfsc		warningflag		;��ѹ����ʱ��30/s����������ʾ   V02
		return
		
		bsf			buzzflag	;��������һ��
		movlw		1
		movwf		buzzTim
		return		
		
		bcf			workflag
		clrf		MODE		;�ػ�
		goto		Buzz_B_BB	
		return		

		
		
		
		
		
		
		
		
		
		
		
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	