;֧�ֳ����̰�
;KEYTmp	 : ����״̬�Ĵ���
;KEYSave : ��������Ĵ��� 

;����Ӧ���������� KEYTmp���ڴ�����ʱ��ֱ���ж�KEYn����������
;KEYTmp			EQU			50H
;DEFINE			KEY1		KEYTmp,0
;DEFINE			KEY2		KEYTmp,1
;DEFINE			KEY3		KEYTmp,2
;DEFINE			KEY4		KEYTmp,3

KEY_pro:
		btfss		fKEY1ms
		return	
		bcf			fKEY1ms
		
		;�˴���Ӷ�ȡ��������
		;����Ӧ���������� KEYTmp, �͵�ƽ��ʾ����ʹ��
		
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
		
		movlw		200			;���� 100msִ��һ�Σ��޸Ĵ˴��ɵ���Ƶ��
		xorwf		KEYms,w		
		btfsc		status,z
		goto		KEY_Enable
		
		return

KEY_Enable:
		movlw		100
		movwf		KEYms
		
		btfss		fKEY	;���δ����д����ʵ�ֳ���
		return
		bsf			fKEY
		
		;�˴���Ӷ�Ӧ������������
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

		
		
	

		
		
		
		
		
		
		
		
		
		
		
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	