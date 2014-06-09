//Generated on 28.05.2014 09:09 by DolphinStudio 2.3.0.0

#ifndef _EO3000I_CFG_H_INCLUDED
#define _EO3000I_CFG_H_INCLUDED
#include "EO3000I_API.h"


//! Function Prototypes
void radio_init_asm(RADIO_INIT_PARAM u8PowerUp);
void startupInit();
void mainInit();


//*********************RADIO PARAM***************************
#define RADIO_BUFF_NUM 10
#define RADIO_MATURITY_TIME 100

//! Radio buffers allocation	
 extern volatile uint8 xdata u8gRadioBuff[RADIO_BUFF_NUM][RADIO_BUFF_LENGTH];	
 //! Radio tx buffers additional allocation for state 		
 extern volatile uint8 xdata u8gRadioBuffTXState[RADIO_BUFF_NUM];		
 //! Radio flags		
 extern volatile uint8 idata u8gFlags[RADIO_BUFF_NUM];	
 //! buffers Rx subtelegrams counters. Index indicates the buffer number.	
 extern volatile uint8 idata u8gRadioBuffsRxSubtel[RADIO_BUFF_NUM];		
 //! buffers Tx subtelegrams counters. Index indicates the buffer number. 		
 extern volatile uint8 idata u8gRadioBuffsTxSubtel[RADIO_BUFF_NUM];	
 //! buffers time stamp counters. Index indicates the buffer number.	
 extern volatile uint8 idata u8gRadioBuffsTimeStamp[RADIO_BUFF_NUM];	
 //! buffers received bytes counters. Index indicates the buffer number.		
 extern volatile uint8 idata u8gRadioBuffsBytes[RADIO_BUFF_NUM];	
 //! buffers dBm values. Value indicating signal strength upon telegram reception. 
 extern volatile uint8 xdata u8gRxRadioBuffsDbm[RADIO_BUFF_NUM];	
 //! Tx buffers time to send subtelegram. Index indicates the buffer number. 
 extern volatile uint8 idata u8gTxRadioBuffsTimeToSend[RADIO_BUFF_NUM];

//*********************DUTY CYCLE PARAM***************************
//! Max. number of duty cycle slots plus one for internal calculation
#define NUM_OF_DUTY_CYCLE_SLOTS 11
//! Duty cycle buffer counter allocation
extern volatile uint8 xdata u8gDutyTimeSlots[NUM_OF_DUTY_CYCLE_SLOTS];


//*********************FILTER PARAM***************************

//! Max. number of filters
#define FILTER_NUM	1

//! Filter buffer allocation for value of filter
extern volatile uint32 xdata u32gFilterValue[FILTER_NUM];
//! Filter buffer allocation containing FILTER_TYPE (Bit 0..1 and FILTER_KIND Bit 7)
extern volatile uint8  xdata u8gFilterCfg[FILTER_NUM];

extern uint8 filter_param[];

//*********************IO PARAM***************************

extern uint8 code	io_param[];

#endif //_EO3000I_CFG_H_INCLUDED

