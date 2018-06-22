INF_Pro:   ;100us
		banksel		flag1
		btss		INFStart
        ret	 
                      
        btss		INFHL
     	ljump		INF_GetLowTime
        btsc		INFHL
        ljump 		INF_GetHighTime                  
        
INF_GetHighTime:
		btss		INF		
        goto		$+9			;出现下降沿
		
        incr		INFTime,1
        
        btsc		INFLongAN	;长按
		ljump		INFLong_AN
		
        ldwi		60			
 		subwr		INFTime,0
        btsc		status,c
        ljump		INF_Read_Err
        ret
         
		btsc		INFLongAN
		ljump		INFLong_AN_Lead
		
        ldwi		30
        subwr		INFTime,0
        btsc		status,c
        ljump		INF_Lead		;引导码>3ms
        
        ldwi		10
        subwr		INFTime,0
        btsc		status,c
        bsr			INFRxdData4,0	;1			
		btss		status,c
        bcr			INFRxdData4,0	;0
       
        ;接收数据位	
        incr		INFBitNum,1
        ldwi		32
        subwr		INFBitNum,0
        btss		status,z
        ljump		INF_Data_lmove
        clrr		INFBitNum
                            
        ;数据判断		
        ldr			INFRxdData1,0
        btss		status,z
        ljump		INF_Read_Err
        
        ldwi		HEADCODE2
        xorwr		INFRxdData2,0
        btss		status,z
        ljump		INF_Read_Err
        
        comr		INFRxdData3,0
        xorwr		INFRxdData4,0
        btss		status,z
        ljump		INF_Read_Err	;err
        
        ldr			INFRxdData3,0	
   		str			INFctrlcode	
        ldr			INFRxdData3,0
		str			INFLongTemp	
		
		clrr		flag2	
		lcall		INF_Long_En        		
        		 
		ldr			MODER,0		
		btsc		status,z
		ret
		banksel		IOCA
		ldwi		11100000b
        str			IOCA
        banksel		flag1  
        ret
       	
INF_GetLowTime: 		
 		btsc		INF
        goto		$+3        			        
        incr		INFTime,1
        ret       		     
        bsr			INFHL
		clrr		INFTime   
		 
        ret   
;------------ 长按 -------------	
INFLong_TIME:
		btss		INF1ms
		ret
		bcr			INF1ms

		btss		INFLongAN
		ret
        
		ldr			INFLongTime,0
		btsc		status,z
		goto		$+3
		decr		INFLongTime,1
		ret
		ljump		INF_Long_Err		
		
INFLong_AN_Lead:
		ldwi		30
        subwr		INFTime,0
        btss		status,c
        ljump		INF_Lead		;长按引导码 < 3ms
		btsc		status,c
		ljump		INF_Long_Err	
		ret
		
INFLong_AN:		
		ldwi		30
        subwr		INFTime,0
        btsc		status,c
        ljump		INF_Long_En		;长按有效			
		ret
INF_Long_Err:
		bcr			INFLongAN
		clrr		INFLongTime
		clrr		INFLongTemp
		ljump		INF_Read_Err
		
INF_Long_En:
        bsr			INFLongAN			;开启长按
		ldwi		120
		str			INFLongTime			;长按间隔小于120ms
		
		lcall		INF_Data_Handle		
		lcall		INF_Read_End
		ret
;----------------------------		
INF_Data_lmove:
        bcr         status,c  
        rlr         INFRxdData4,1
        rlr         INFRxdData3,1
        rlr         INFRxdData2,1
        rlr         INFRxdData1,1
        clrr		INFTime
        bcr			INFHL		
		
        ret
        
INF_Lead:                
        ;引导码
        btss		INFLead
        ljump		INF_Read_Err
        		
        clrr		INFTime
        bcr			INFHL
		bcr			INFLead		
        ret		    

INF_Read_End:		   
INF_Read_Err:		;无效时序  
		banksel		flag1
		bcr			INFStart      
        bcr			INFLead
        bcr			INFHL
        clrr		INFTime
        clrr		INFBitNum
		clrr		INFRxdData4
        clrr		INFRxdData3
        clrr		INFRxdData2
        clrr		INFRxdData1
        clrr		INFctrlcode
       
        banksel		IOCA
		bsr			IOCA,7	
        banksel		flag1
                
        ret	                       

INF_Start:
		banksel		IOCA
		bcr			IOCA,7	
        
        banksel		flag1
		bsr			INFStart
        bsr			INFLead
 	           
 		ret
 
;	数据处理
INF_Data_Handle: 		
		;ldwi		BRIGHTCODE
		;xorwr		INFLongTemp,0
		;btsc		status,z
		;ljump		BRIGHTCODE_MODE
        	
		ret

		


		
		
		
		

 
 
 