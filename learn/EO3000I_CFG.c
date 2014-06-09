//Generated on 28.05.2014 09:09 by DolphinStudio 2.3.0.0
#include "EO3000I_CFG.h"


//*********************API INIT*************************** 

//Note: Function is called from startup.a51. Global variables are not yet initialized!
void startupInit()
{
	pwr_enableXTAL(DEFAULT_DELAY);
	io_init(io_param);
}


//Note: Function is called from main()
void mainInit()
{
	radio_init_asm(CFG_ALL);
	radio_init(RADIO_BUFF_NUM, RADIO_MATURITY_TIME);
	radio_initDutyCycleLimit(NUM_OF_DUTY_CYCLE_SLOTS);
	isr_timer0Init();
	misc_init();
	pwr_selectXTAL();
}

//*********************RADIO PARAM***************************

//! Radio buffers allocation	
 volatile uint8 xdata u8gRadioBuff[RADIO_BUFF_NUM][RADIO_BUFF_LENGTH];	
 //! Radio tx buffers additional allocation for state 		
 volatile uint8 xdata u8gRadioBuffTXState[RADIO_BUFF_NUM];		
 //! Radio flags		
 volatile uint8 idata u8gFlags[RADIO_BUFF_NUM];	
 //! buffers Rx subtelegrams counters. Index indicates the buffer number.	
 volatile uint8 idata u8gRadioBuffsRxSubtel[RADIO_BUFF_NUM];		
 //! buffers Tx subtelegrams counters. Index indicates the buffer number. 		
 volatile uint8 idata u8gRadioBuffsTxSubtel[RADIO_BUFF_NUM];	
 //! buffers time stamp counters. Index indicates the buffer number.	
 volatile uint8 idata u8gRadioBuffsTimeStamp[RADIO_BUFF_NUM];	
 //! buffers received bytes counters. Index indicates the buffer number.		
 volatile uint8 idata u8gRadioBuffsBytes[RADIO_BUFF_NUM];	
 //! buffers dBm values. Value indicating signal strength upon telegram reception. 
 volatile uint8 xdata u8gRxRadioBuffsDbm[RADIO_BUFF_NUM];	
 //! Tx buffers time to send subtelegram. Index indicates the buffer number. 
 volatile uint8 idata u8gTxRadioBuffsTimeToSend[RADIO_BUFF_NUM];

//*********************DUTY CYCLE PARAM***************************
//! Duty cycle buffer counter allocation and initialization	
volatile uint8 xdata u8gDutyTimeSlots[NUM_OF_DUTY_CYCLE_SLOTS]=0;	


//*********************FILTER PARAM***************************

//! Filter buffer allocation for value of filter
volatile uint32 xdata u32gFilterValue[FILTER_NUM];
//! Filter buffer allocation containing FILTER_TYPE (Bit 0..1 and FILTER_KIND Bit 7)
volatile uint8  xdata u8gFilterCfg[FILTER_NUM];

uint8 filter_param[]	= {
 		FILTER_NUM, //IDX_FILTER_MAX
 		FILTER_ALL_AND	//IDX_FILTER_OPERATOR 
 };

//*********************IO PARAM***************************

uint8 code	io_param[]	= {	
 		0x07,	//IDX_GPIO_CONF 
 		0x00,	//IDX_GPIO0_CONF 
 		0x0C,	//IDX_GPIO0_PULL_CONF 
 		0x03,	//IDX_GPIO0_DIR 
 		0x00,	//IDX_GPIO1_AN 
 		0x00,	//IDX_GPIO1_CONF 
 		0x03,	//IDX_GPIO1_DIG_CONF 
 		0x00,	//IDX_GPIO1_DIR 
 		0xFF,	//IDX_GPIO1_PULL 
 		0x04,	//IDX_GPIO2_CONF 
 		0x00,	//IDX_GPIO2_DIR 
 		0x00,	//IDX_GPIO0 
 		0x00,	//IDX_GPIO1 
 		0x00 	//IDX_GPIO2 
 };

// I/O Configuration overview
// 
//      Pin:  Interface     Direction  Pull   Init Value
// SCSEDIO0:  Digital I/O   Out        None   0
// SCLKDIO1:  Digital I/O   Out        None   0
// WSDADIO2:  Digital I/O   In         Up     0
// RSDADIO3:  Digital I/O   In         Up     0
//    ADIO0:  Digital I/O   In         Up     0
//    ADIO1:  Digital I/O   In         Up     0
//    ADIO2:  Digital I/O   In         Up     0
//    ADIO3:  Digital I/O   In         Up     0
//    ADIO4:  Digital I/O   In         Up     0
//    ADIO5:  Digital I/O   In         Up     0
//    ADIO6:  Digital I/O   In         Up     0
//    ADIO7:  Digital I/O   In         Up     0
//   WXIDIO:  Digital I/O   In         Up     0
//   WXODIO:  Digital I/O   In         Up     
//    WAKE0:  Digital I/O   In         None   
//    WAKE1:  Digital I/O   In         None   

