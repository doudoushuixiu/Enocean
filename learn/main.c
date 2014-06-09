#include "EO3000I_API.h"
#include "EO3000I_CFG.h"

#define  RM_CODE_ADDR1 0x7E00
#define  RM_CODE_ADDR2 0x7D00
#define  ID_NUM_ADDR   0x7C00

#define TURE  1
#define FALSE 0

uint32 ID_ADDR[10]={0x7B00,0x7A00,0x7900,0x7800,0x7700,0x7600,0x7500,0x7400,0x7300,0x7200};

code uint8 VERSION_APP[] = {0xE0,'V','E','R','S','I','O','N',1,0,4,0,'A','R','A','D','I','O','T','O','S','E','R','I','A','L',0x00,0xE0};

uint8   key_learn_num=1;  //if user push the Learn button,key_learn_num++ .
uint8	control_line=0;
uint8   learn_mode=0;
uint8   Switch_AB=0;

uint8   A_IO_num=0;    // num of the PTM200(can control line_A)
uint8   B_IO_num=0;    // num of the PTM200(can control line_B)



struct Switch_PTM200{   //define the PTM200's ID & 4 Buttons
	uint32 Switch_ID;	
	uint8  Button_AI;	//0x10
	uint8  Button_AO;	//0x30
	uint8  Button_BI;	//0x50
	uint8  Button_BO;	//0x70	 Turn on:0    Turn off:1     undefine:3
};

struct Switch_PTM200 Line_A[30]={0,3,3,3,3};   //init the line A

struct Switch_PTM200 Line_B[30]={0,3,3,3,3};   //init the line B

typedef struct
{
	// Public 
	uint8		u8Pin;			// e.g. ADIO0
	uint8		u8ActiveState;	// button is pressed if (io_getDigital(u8Button)==bActiveState)
	uint16		u16TimeOutON;	// time [ms] the button has to be pressed to be recognized as pressed
	uint16		u16TimeOutOFF;	// time [ms] the button has to be pressed to be recognized as released	
	// Private
	TIMER_TYPE	tTimer;
 	uint8		u8State;
} BTN_STRUCT;

typedef enum 
{
	BTN_IDLE = 0,
	BTN_EDGE1,
	BTN_TRIGGERED,
	BTN_PRESSED,	//< most important
	BTN_PRESS_HOLD,
	BTN_EDGE2,
	BTN_RELEASE_HOLD,
	BTN_RELEASED	
} BTN_STATE;

BTN_STATE btn_getState(BTN_STRUCT *pBtn)
{
	code uint8 transition_table[8][4]={	0,	1,	0,	1,
										5,	2,	5,	1,
										5,	2,	5,	3,
										5,	4,	5,	4,
										5,	4,	5,	4,
										6,	1,	0,	1,
										6,	1,	7,	1,
										0,	1,	0,	1 };	
	register uint8 u8Input;	
	// Get button state
	io_getDigital(pBtn->u8Pin, &u8Input);
	u8Input = (u8Input == pBtn->u8ActiveState)?1:0;	
	// Get timeout state
	u8Input |= ((time_getTimeOut(&(pBtn->tTimer))==TIME_OUT)?2:0);
	// Get new state
	pBtn->u8State = transition_table[pBtn->u8State][u8Input]; // we want only the state, not action
	// Perform action 
	switch (pBtn->u8State)
	{
		case 1:
			time_setTimerCount(&(pBtn->tTimer), pBtn->u16TimeOutON);
			break;
		case 5:
			time_setTimerCount(&(pBtn->tTimer), pBtn->u16TimeOutOFF);
			break;
	}
	return pBtn->u8State;	
}

BTN_STATE btn_getState(BTN_STRUCT *pBtn);


// Define Learn button (KEY1 push 250ms)
BTN_STRUCT btnLearn = {WSDADIO_2,		// Pin
						0,			    // Active state
						250,		    // Time the button has to be in 'Active state' to be recognized as pressed
						100 };	

// Define Quit button  (KEY2 push 200ms)
BTN_STRUCT btnQuit = {RSDADIO_3,		// Pin
						0,			    // Active state
						200,		    // Time the button has to be in 'Active state' to be recognized as pressed
						100 };

// Define Clean button (KEY2 push 3s)
BTN_STRUCT btnClean = {RSDADIO_3,		// Pin
						0,			    // Active state
						3000,		    // Time the button has to be in 'Active state' to be recognized as pressed
						100 };


void blinkledA(int led_1)
{
		io_setDigital(SCLKDIO_1,1);
		time_wait(100);
		io_setDigital(SCLKDIO_1,0);
		time_wait(100);
		io_setDigital(SCLKDIO_1,1);
		time_wait(100);
		io_setDigital(SCLKDIO_1,0);
		time_wait(100);
		io_setDigital(SCLKDIO_1,led_1);
}

void blinkledB(int led_2)
{
		io_setDigital(SCSEDIO_0,1);
		time_wait(100);
		io_setDigital(SCSEDIO_0,0);
		time_wait(100);
		io_setDigital(SCSEDIO_0,1);
		time_wait(100);
		io_setDigital(SCSEDIO_0,0);
		time_wait(100);
		io_setDigital(SCSEDIO_0,led_2);
}


void testled(int jj)
{
    int num=0;
	for(num=0;num<jj;num++)
	{
		io_setDigital(SCLKDIO_1,0);
		io_setDigital(SCSEDIO_0,0);
		time_wait(200);
		io_setDigital(SCLKDIO_1,1);
		io_setDigital(SCSEDIO_0,1);
		time_wait(200);
	}
}



void Write_info_flash()
{


}



void Mode_Control()
{
	if (btn_getState(&btnLearn)==BTN_PRESSED)
		{	
			if(key_learn_num==1)              //push learn button once£¬ligth the LED1 
			{
				io_setDigital(SCLKDIO_1,1);	  //control LED
				io_setDigital(SCSEDIO_0,0);
				learn_mode=1;                 //start the learn mode
				control_line=1;				  //choice the control line	1
			}

			if(key_learn_num==2)	          //push learn button once again£¬light the LED2 
			{
				io_setDigital(SCLKDIO_1,0);
				io_setDigital(SCSEDIO_0,1);
				learn_mode=1;
				control_line=2;				  //choice the control line	2
			}
			
			if(key_learn_num==3)           	 //push learn button once again£¬light the LED1 & LED2 
			{
				io_setDigital(SCLKDIO_1,1);
				io_setDigital(SCSEDIO_0,1);
				learn_mode=1;				 //choice the control line	1 & 2
				control_line=3;
			}
	
			key_learn_num++;
			if(key_learn_num>3)	             //  loop LED1 & LED2
			{
				key_learn_num=1;
			}
		}
				
	if (btn_getState(&btnQuit)==BTN_PRESSED)  //push the EXIT button for more than 200ms
	{
		io_setDigital(SCLKDIO_1,0);
		io_setDigital(SCSEDIO_0,0);
		learn_mode=0;	  //exit the learn mode
		key_learn_num=1;
		control_line=1;				  //choice the control line 1
		blinkledB(0);
	}
	
	if (btn_getState(&btnClean)==BTN_PRESSED)  //push the clear button for more than 3s
	{
		learn_mode=0;	  //exit the learn mode
		key_learn_num=1;
		control_line=1;				  //choice the control line
		blinkledB(0);
		//do the clear work

		Write_info_flash();
		//write into flash


	}		                        
}


void Learn_mode_function()
{
	uint8   A_find_new_PTM200=1;
	uint8   B_find_new_PTM200=1;
	if(learn_mode==1)
	{
	    uint8   i=0;           // used for searching the ID
		struct myRadioType{ 
	    	CHOICE_TYPE u8Choice; 
	    	uint8  Data; 
	    	uint32 u32Id; 
	    	uint8  u8Status; 
	    	uint8  u8Chk; 
	   	 	uint8  u8Fill[RADIO_BUFF_LENGTH-8];     // align u8Length as last byte in structure !!!
	    	RADIO_TEL_LENGTH u8Length; 
       		}learn_RT1;
		TEL_PARAM_TYPE  pTelIn1;	 //init a input radio
		
		if (radio_getTelegram((TEL_RADIO_TYPE *)&learn_RT1, &pTelIn1) == OK)  //if get a radio
		{
		 	switch(control_line)     
			{
			case 1:{   //choose line 1(A)
					   for(i=0;i<15;i++)
					   {
					   		if(Line_A[i].Switch_ID==learn_RT1.u32Id)   //this PTM200 has been learned.
							{
								if(learn_RT1.Data==0x10||learn_RT1.Data==0x30)
								{
									Line_A[i].Button_AI=1;	   //ligth off
							    	Line_A[i].Button_AO=0;	   //light on
									blinkledA(1);
									break;
								}
								else if(learn_RT1.Data==0x50||learn_RT1.Data==0x70)
								{
									Line_A[i].Button_BI=1;
						  	    	Line_A[i].Button_BO=0;
									blinkledA(1);
									break;
								}
								else
								{
									break;
								}
								A_find_new_PTM200=0;
								break;								
							}

					   }			           
					   if(A_find_new_PTM200==1)   //if this PTM200 is newer.
					   {
						   	if(learn_RT1.Data==0x10||learn_RT1.Data==0x30)   //push button AI or AO
						   	{
								Line_A[A_IO_num].Switch_ID=learn_RT1.u32Id;
								Line_A[A_IO_num].Button_AI=1;	   //ligth off
								Line_A[A_IO_num].Button_AO=0;	   //light on					 
								blinkledA(1);								
							}
							else if(learn_RT1.Data==0x50||learn_RT1.Data==0x70)
							{
								Line_A[A_IO_num].Switch_ID=learn_RT1.u32Id;
								Line_A[A_IO_num].Button_BI=1;
								Line_A[A_IO_num].Button_BO=0;					 
								blinkledA(1);													
						    }
							else         // learn_RT1.Data==0x00 or else
							{
								break;   //exit the switch    
							}
							if(A_IO_num==30)    //max num (PTM200 can learn) is 30
							{
								A_IO_num=0;   
							}
							else if(A_IO_num>=0&&A_IO_num<15)
							{
								A_IO_num++;	   //next key(in PTM200
							}
							break;
					   }					   																					

				   };
/*************************************************************************************************/
			case 2:{	//choose line 2(B)						
					   for(i=0;i<15;i++)
					   {
					   		if(Line_B[i].Switch_ID==learn_RT1.u32Id)   //this PTM200 has been learned.
							{
								if(learn_RT1.Data==0x10||learn_RT1.Data==0x30)
								{
									Line_B[i].Button_AI=1;	   //ligth off
							    	Line_B[i].Button_AO=0;	   //light on
									blinkledB(1);
									break;
								}
								else if(learn_RT1.Data==0x50||learn_RT1.Data==0x70)
								{
									Line_B[i].Button_BI=1;
						  	    	Line_B[i].Button_BO=0;
									blinkledB(1);
									break;
								}
								B_find_new_PTM200=0;
								break;								
							}
					   }
						if(B_find_new_PTM200==1)   //if this PTM200 is newer.
						{
	                        if(learn_RT1.Data==0x10||learn_RT1.Data==0x30)   //push button AI or AO
							{
							 	 Line_B[B_IO_num].Switch_ID=learn_RT1.u32Id;
								 Line_B[B_IO_num].Button_AI=1;	   //ligth off
								 Line_B[B_IO_num].Button_AO=0;	   //light on					 
								 blinkledB(1);								
							}				
							else if(learn_RT1.Data==0x50||learn_RT1.Data==0x70)   //push button AI or AO
							{
								Line_B[B_IO_num].Switch_ID=learn_RT1.u32Id;	   	
								Line_B[B_IO_num].Button_BI=1;	   //ligth off
								Line_B[B_IO_num].Button_BO=0;	   //light on					 
								blinkledB(1);
							}
							else
							{
								break;
							}						
							if(B_IO_num==30)    //loop
							{
								B_IO_num=0;   
							}
							else if(B_IO_num>=0&&B_IO_num<15)
							{
								B_IO_num++;	   //next key(in PTM200)
							}
							break;						
						}
								 	 								
				   };

/*************************************************************************************************/				 
		    case 3:{	//choose line 1 & line 2 (A&B)
						if(learn_RT1.Data==0x10||learn_RT1.Data==0x30)   //push button AI or AO
						{
						 	 Line_A[A_IO_num].Switch_ID=learn_RT1.u32Id;
							 Line_A[A_IO_num].Button_AI=1;	   //ligth off
							 Line_A[A_IO_num].Button_AO=0;	   //light on
							 Line_B[B_IO_num].Switch_ID=learn_RT1.u32Id;
							 Line_B[B_IO_num].Button_AI=1;	   //ligth off
							 Line_B[B_IO_num].Button_AO=0;	   //light on					 
							 blinkledA(1);								
						}				
						if(learn_RT1.Data==0x50||learn_RT1.Data==0x70)   //push button AI or AO
						{
							Line_A[A_IO_num].Switch_ID=learn_RT1.u32Id;	 // line A
							Line_A[A_IO_num].Button_BI=1;
							Line_A[A_IO_num].Button_BO=0;
							Line_B[B_IO_num].Switch_ID=learn_RT1.u32Id;	 // line B 	   	
							Line_B[B_IO_num].Button_BI=1;	   
							Line_B[B_IO_num].Button_BO=0;	   					 
							blinkledA(1);
						}
						
						if(A_IO_num==30)    //loop
						{
							A_IO_num=0;   
						}
						else
						{
							A_IO_num++;	   //next key(in PTM200)
						}
						
						if(B_IO_num==30)    //loop
						{
							B_IO_num=0;   
						}
						else
						{
							B_IO_num++;	   //next key(in PTM200)
						}			
			       };

		    default:break;
			//end
		    }
			
		}
	}
}


void Work_function()
{
	if(learn_mode==0)
	{
		uint8   j=0;           // used for searching the ID 
		struct myRadioType{ 
		    	CHOICE_TYPE u8Choice; 
		    	uint8  Data; 
		    	uint32 u32Id; 
		    	uint8  u8Status; 
		    	uint8  u8Chk; 
		   	 	uint8  u8Fill[RADIO_BUFF_LENGTH-8];     // align u8Length as last byte in structure !!!
		    	RADIO_TEL_LENGTH u8Length; 
	       		}learn_RT2;
		TEL_PARAM_TYPE  pTelIn2;	 //init a input radio
	
		if (radio_getTelegram((TEL_RADIO_TYPE *)&learn_RT2, &pTelIn2) == OK)  //if get a radio
			{
			 	for(j=0;j<15;j++)
				{
					if(learn_RT2.u32Id==Line_A[j].Switch_ID)
					{										
						if(learn_RT2.Data==0x10)       //button:  AI
						{
							if(Line_A[j].Button_AI==1) //line A
							{
								//turn off the light A
								blinkledA(0);
								break;							
							}
							else if(Line_A[j].Button_AI==3)
							{
								break;
							}
							else
							{
								break;
							}		
						}	
						else if(learn_RT2.Data==0x30) //button:  AO
						{
							if(Line_A[j].Button_AO==0)
							{
								//turn on the light 
								blinkledA(1);
								break;							
							}
							else if(Line_A[j].Button_AO==3)
							{
								break;
							}
							else
							{
								break;
							}					
						}
						else if(learn_RT2.Data==0x50) //button:  BI
						{
							if(Line_A[j].Button_BI==1)
							{
								//turn off the light
								blinkledA(0);
								break;								
							}
							else if(Line_A[j].Button_BI==3)
							{
								break;
							}
							else
							{
								break;
							}					
						}
						else if(learn_RT2.Data==0x70) //button:  BO
						{
							if(Line_A[j].Button_BO==0)
							{
								//turn on the light 
								blinkledA(1);
								break;
							}
							else if(Line_A[j].Button_BO==3)
							{
								break;
							}
							else
							{
								break;
							}					
						}
						else  //radio's data is wrong(radio's data list:0x10  0x30  0x50  0x70)
						{
							break;
						}					
					}  //end of line_A
				} //end of search ID
/*******************************************************************************/
			 	for(j=0;j<15;j++)    //search line B
				{
					if(learn_RT2.u32Id==Line_B[j].Switch_ID)
					{										
						if(learn_RT2.Data==0x10)       //button:  AI
						{
							if(Line_B[j].Button_AI==1) //line B
							{
								//turn off the light A
								blinkledB(0);
								break;							
							}
							else if(Line_B[j].Button_AI==3)
							{
								break;
							}
							else
							{
								break;
							}		
						}	
						else if(learn_RT2.Data==0x30) //button:  AO
						{
							if(Line_B[j].Button_AO==0)
							{
								//turn on the light 
								blinkledB(1);
								break;							
							}
							else if(Line_B[j].Button_AO==3)
							{
								break;
							}
							else
							{
								break;
							}					
						}
						else if(learn_RT2.Data==0x50) //button:  BI
						{
							if(Line_B[j].Button_BI==1)
							{
								//turn off the light
								blinkledB(0);
								break;								
							}
							else if(Line_B[j].Button_BI==3)
							{
								break;
							}
							else
							{
								break;
							}					
						}
						else if(learn_RT2.Data==0x70) //button:  BO
						{
							if(Line_B[j].Button_BO==0)
							{
								//turn on the light 
								blinkledB(1);
								break;
							}
							else if(Line_B[j].Button_BO==3)
							{
								break;
							}
							else
							{
								break;
							}					
						}
						else  //radio's data is wrong(radio's data list:0x10  0x30  0x50  0x70)
						{
							break;
						}						
					}  //end of line_B
				} //end of search ID



			}
	}
}


void main()
{		
	mainInit();

	radio_enableRx(1);

	while (1)
	{	     
		CLR_WDT();			      //Clear the watchdog.
										
		Mode_Control();            //choose work mode,while user push the button.

		Learn_mode_function();	  //in the learn mode,learn the PTM200's info.

		Work_function();          //push the button on the PTM200,control the light.

	}
}