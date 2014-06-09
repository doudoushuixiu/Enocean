/******************************************************************
  \file         EO3000I_API.h
  \ingroup 			ESSL
  \version			$Revision: 40900 $
  \date				  $Date: 2013-11-26 14:52:48 +0100 (Di, 26 Nov 2013) $
  \author 			EnOcean GmbH
  \brief 				Application interface to the EO3000I
  
  This file is the interface to the API library for the application. 
  Note the main page description can be found at the end of this file
  Processor:			EO3000I
  Company:			EnOcean Gmbh
******************************************************************/


#ifndef _EO3000I_API_INCLUDED
#define _EO3000I_API_INCLUDED
 
//! @addtogroup sys_fn_grp System defines
//! System defines !!! DON'T MODIFY  !!!
//! \ingroup ESSL
//! @{
	
#ifdef RELEASE
	typedef unsigned long int  uint32  ; //!< Unsigned Integer 32 bits
	typedef signed long int    sint32  ; //!< Signed Integer 32 bits
	typedef unsigned int       uint16  ; //!< Unsigned Integer 16 bits
	typedef signed int         sint16  ; //!< Signed Integer 16 bits
	typedef unsigned char      uint8   ; //!< Unsigned Integer 8 bits
	typedef signed char        sint8   ; //!< Signed Integer 8 bits
	typedef unsigned char      uchar8  ; //!< Unsigned Character 8 bits
	typedef signed char        schar8  ; //!< Signed Character 32 bits
	typedef float              float32 ; //!< Floating point 32 bits
	typedef bit                bit1    ; //!< Single bit                 

	#define	TRUE	1
	#define	FALSE	0	
	#define	NULL	0

	
#else
	#include <sd_platform_const.h>
#endif

	//! Number of UART fifos. 1 to send (tx), 1 to receive (rx)
	#define UART_BUFF_NUM			2
	//! Length of UART fifo buffer. If not using EnOcean Serial Protocol2, 
	//you can redefine this in your program in order to save memory
	#define UART_MAX_LENGTH			34
	//! Length of RX/TX radio buffers in bytes - the maximum decoded telegram length 
	#define   RADIO_BUFF_LENGTH		21


	//! Define for parameter passing all initialization parameters to the function
	#define SET_ALL_PARAM	 0xFF  		
	//! ON state value
	#define	ON	1
	//! OFF state value
	#define	OFF	0


	//! Function return codes
	typedef enum
	{
		//! <b>0</b> - Action performed. No problem detected
		OK=0,							
		//! <b>1</b> - Action couldn't be carried out within a certain time.  
		TIME_OUT,		
		//! <b>2</b> - The write/erase/verify process failed, the flash page seems to be corrupted
		FLASH_HW_ERROR,				
		//! <b>3</b> - A new UART/SPI byte received
		NEW_RX_BYTE,				
		//! <b>4</b> - No new UART/SPI byte received	
		NO_RX_BYTE,					
		//! <b>5</b> - New telegram received
		NEW_RX_TEL,	  
		//! <b>6</b> - No new telegram received
		NO_RX_TEL,	  
		//! <b>7</b> - Checksum not valid
		NOT_VALID_CHKSUM,
		//! <b>8</b> - Telegram not valid  
		NOT_VALID_TEL,
		//! <b>9</b> - Buffer full, no space in Tx or Rx buffer
		BUFF_FULL,
		//! <b>10</b> - Address is out of memory
		ADDR_OUT_OF_MEM,
		//! <b>11</b> - Invalid function parameter
		NOT_VALID_PARAM,
		//! <b>12</b> - Built in self test failed
		BIST_FAILED,
		//! <b>13</b> - Before entering power down, the short term timer had timed out.	
		ST_TIMEOUT_BEFORE_SLEEP,
		//! <b>14</b> - Maximum number of filters reached, no more filter possible
		MAX_FILTER_REACHED,
		//! <b>15</b> - Filter to delete not found
		FILTER_NOT_FOUND,
		//! <b>16</b> - BaseID out of range
		BASEID_OUT_OF_RANGE,
		//! <b>17</b> - BaseID was changed 10 times, no more changes are allowed
		BASEID_MAX_REACHED,
		//! <b>18</b> - XTAL is not stable
		XTAL_NOT_STABLE,
		//! <b>19</b> - No telegram for transmission in queue  
		NO_TX_TEL,
		//!	<b>20</b> - Waiting before sending broadcast message
		TELEGRAM_WAIT,
		//!	<b>21</b> - Generic out of range return code
		OUT_OF_RANGE,
		//!	<b>22</b> - Function was not executed due to sending lock
		LOCK_SET,
		//! <b>23</b> - New telegram transmitted
		NEW_TX_TEL
	} RETURN_TYPE;

	//! Records enum structure for the API System Log  - DON'T CHANGE !
	//>>Section:EO3000I-API:0x7E00
	typedef enum 
	{
		//! There was no free serial fifo to store information
		ERR_ISRUARTRXTX_RX_OVERFLOW = 0,
		//! There was a UART RX interrupt lost by RMW problematic
		ERR_UART_RX_INT_LOST,
		//! There was a UART TX interrupt lost by RMW problematic
		ERR_UART_TX_INT_LOST,
		//! UART send buffer full
		ERR_UART_SEND_BUFFER_FULL,
		//! Obsolete since API 2.2.5.0 - No free buffer in the Rx radio buffers and no buffer could be released with maturity time 0xFF 
		ERR_RADIORX_NO_FREE_BUFFER,
		//! No free buffer in the Tx radio buffers
		ERR_RADIOTX_NO_FREE_BUFFER,
		//! Obsolete since API 2.2.5.0 - Error in the rx pointers, this may happen if the rx state machine is reinitialised while reading telegram
		ERR_RADIORX_RX_PTR,		
		//! Obsolete since API 2.2.5.0 - Wrong received telegram checksum
		ERR_RADIORX_CHKSUM,	
		//! Obsolete since API 2.2.5.0 - The received telegram is shorter than the minimum size
		ERR_RADIORX_MINSIZE,
		//! Obsolete since API 2.2.5.0 - The rx pointer reached the security value fixed in the Maximum Packet Size
		ERR_RADIORX_MAXSIZE,
		//! Obsolete since API 2.2.5.0 - Telegram EOF not found
		ERR_RADIORX_EOF,	
		//! Obsolete since API 2.2.5.0 - An inverse bit was not correct while decoding telegram
		ERR_RADIORX_DECGROUP,	
		//! Error interrupt detected during Tx statemachine
		ERR_RADIORX_TXERRIRQ,
		//! Obsolete since API 2.2.5.0 - Radio LBT counter
		ERR_RADIOTX_LBT_L,
		ERR_RADIOTX_LBT_H,
		//! Obsolete since API 2.2.5.0 - Radio TX ignore LBT for fitting sub telegram timing
		ERR_RADIOTX_IGNORELBT,
		//! There is no free intermediate buffer, telegram dropped
		ERR_RADIORX_INTBUFFER,
		//! The length of the telegram to send is zero
		ERR_RADIOSEND_LENGTH_ZERO,
		//! The number of telegrams is not 1,2 or 3
		ERR_RADIOSEND_NUMB_SUBTEL_WRONG,
		//! The length of the telegram to send exceeds the radio buffer
		ERR_RADIOSEND_LENGTH_TOO_BIG,
		//! The id of the telegram to send is not in the range of the base id
		ERR_RADIOSEND_BASEID_WRONG, 
		//! Task for flash operation was already occupied when whanted to change value. - called from interrupt
		SMACK_BUSY_TASKINT,
		//! Task for flash operation was already occupied when whanted to change value. - called from main
		SMACK_BUSY_TASKMAIN,
		//! Index of radio buffer where reclaim is stored was busy.
		SMACK_BUSY_RECLAIM_RADIO,
		//! Index of xram buffer where reclaim is stored was busy.
		SMACK_BUSY_RECLAIM_MB,
		//! Temporary mailbox was busy when wanted to use.		
		SMACK_BUSY_TEMP,
		//! In Learn period two sensers wanted to be learn in.
		SMACK_DOUBLE_LRN,
		//! System works with unknown acknowledge code.
		SMACK_WRONG_ACKCODE,
		//! System should learn out sensor - but there is no mailbox to delete.
		SMACK_NOTHIG_TO_DELETE,
		//! Write mailbox was called but no free mailbox available.
		SMACK_NO_FREE_MB,
		//! Smack needed to send telegram but there was no free buffer.
		SMACK_NO_BUFFER_TO_SEND,
		//! Temporary mailbox was timed out. This should never occur, because temp should be ready when reclaiming. When not somewhere the message was lost.		
		SMACK_TEMP_TIMMED_OUT,
		//! No reclaim telegram was sent
		SMACK_RECLAIM_NOT_SENT,
		//! Wakeup of reclaim standby mode not by RX telegram
		SMACK_RECLAIM_WAKEUP_NOT_RX,
		//! No reclaim acknowledge received
		SMACK_RECLAIM_NO_ACK,
		//! Other message after reclaim received, not the expected reclaim acknowledge
		SMACK_RECLAIM_OTHER_MSG,
        //! Chained telegrams with different sequence received. Probably two controller communicating at the same time
        REMAN_MIX_SEQUENCE,
        //! Chained telegrams data was too long and did not fit to the REMAN buffer
        REMAN_BUFFER_OVERFLOW,
		//! error memory size, has to stay as the last enum, 
		API_ERR_MEM_SIZE,
         //! reserved until 128 values
	} API_ERRLOG;
	//>>SectionEnd

	//! System log allocated in API - DON'T CHANGE !
	extern uint8 u8APIErrLog[API_ERR_MEM_SIZE];
 	
//! @}



/*********************************************************************************************/
/************************************ FILTER FUNCTION PROTOTYPES ******************************/
/*********************************************************************************************/

/*!
	\addtogroup filter_grp  filter
	The FILTER module is used to filter received telegrams according:
	- ID
	- CHOICE
	- dBm
	
	When the filter is active telegrams which matches to the data specified with the 
	filter module are dropped and the application does not receive them.
	\ingroup ESSL
    Note:IDX_FILTER_OPERATOR is valid for all filters!!
    Note:FILTER_KIND=APPLY => BLOCK all other type of Telegrams.
*/ 

//! @addtogroup filter_cfg_grp FILTER config parameters
//! Filter initialization parameters. The first enumeration member = 0, the next = 1, etc
//! \ingroup filter_grp
//! @{
	//! Filter initialization parameter indexes
	typedef enum 
	{	
		//! Maximum number of filters [ro]
		IDX_FILTER_MAX = 0,		
		//! Operator of all filters:FILTER_ALL_AND or FILTER_ALL_OR
		//! When using more filters, each filter has to be seen as a logical object with boolean
		//! result. These rsults are then all computed with the adjusted operator AND or OR.
		//! F.e., the operator AND is only sensfull when using different filter types
		//! The operator OR is useful to filter some learned IDs, when only they are allowed.
		IDX_FILTER_OPERATOR		
	} FILTER_PARAM_IDX;
//! @}

//! @addtogroup filter_struct_grp FILTER structures
//! Structures that are used in the filter module
//! \ingroup filter_grp
//! @{
	typedef enum
	{
		//! Filter has type ID
		FILTER_TYPE_ID=0,		
		//! Filter has type Choice
		FILTER_TYPE_CHOICE,		
		//! Filter has type DBM
		FILTER_TYPE_DBM		
	} FILTER_TYPE;

	typedef enum  
	{
		//! Filter blocks criteria
		FILTER_KIND_BLOCK=0,	
		//! Filter applies criteria
		FILTER_KIND_APPLY=128	
	}FILTER_KIND; 
	
	//! IDX_FILTER_OPERATOR OR  applying for all filters
	#define FILTER_ALL_OR  0 	
	//! IDX_FILTER_OPERATOR AND applying for all filters
	#define FILTER_ALL_AND 1	
//! @}

//! @addtogroup filter_fn_grp FILTER functions
//! \copydetails filter_grp
//! \ingroup filter_grp
//! @{

	/************************************************************************************************************************//*!
    Sets the filter parameters for radio communication, delete all filters, and disable filter functionality
    
    \param[in]  	*pu8Param	  			Pointer to the list of parameters to set. See #FILTER_PARAM_IDX
    \param[in]  	u8ParamToSet	  		It has to be #SET_ALL_PARAM to set all parameters from FILTER_PARAM_IDX of the list
    \return 	    -
    
	\note
	This function is allowed to be used in an interrupt callback function ONLY if it is ensured that it is not used at the same time from the main program!

    \sa filter_setConfig, FILTER_PARAM_IDX
	**************************************************************************************************************************/		
	void filter_init(uint8 *pu8Param, uint8 u8ParamToSet);
	
	/************************************************************************************************************************//*!
    Sets one filter parameter
    
    \param[in]  	*pu8Param	  			Pointer to the list of parameters to set. See #filter_param[]
    \param[in]  	u8Index			  		Index of parameter to set. See #FILTER_PARAM_IDX
    \param[in]  	u8NewValue			 	The parameter value
    \return 	    -
    
	\note
	This macro is allowed to be used in an interrupt callback function!

    \sa filter_init                                                                                                         
	**************************************************************************************************************************/		
	#define filter_setConfig(pu8Param, u8Index,u8NewValue)	pu8Param[u8Index]=u8NewValue; filter_init(pu8Param,u8Index);

	/************************************************************************************************************************//*!
    Adds a filter to the filter list and enables filter functionality
    
    \param[in]  	u8filterType			type of filter, See #FILTER_TYPE
	\param[in]		u32compare				compare value of filter (ID=32 bit, CHOICE=8 bit, REPT=1 bit)
	\param[in]		u8filterKind			kind of filter, See #FILTER_KIND
    \return     	OK 						added filter to filter buffer
    \return	    	MAX_FILTER_REACHED	 	filter buffer is full
    
    \note     If #FILTER_TYPE = CHOICE look filterable #CHOICE_TYPE	
    
	Example 1: \n
    Add filter for Choice,only RPS Telegramms are allowed!!
    
     \code
	filter_init(filter_param, SET_ALL_PARAM);
	filter_add(FILTER_TYPE_CHOICE,RADIO_CHOICE_RPS,FILTER_KIND_APPLY);
 	....
	//BLOCKS weaker signal as -70dBm (z.b. -80, -90dBm...)
  	filter_add(FILTER_TYPE_DBM,70,FILTER_KIND_BLOCK);
	....
	//BLOCKS stronger signal as -70dBm (z.b. -60, -50dBm...)
  	filter_add(FILTER_TYPE_DBM,70,FILTER_KIND_APPLY);
	....
	//BLOCKS own telegrams which were repeated by an other module
	uint32 u32Id;
	....
	misc_getId(&u32Id);
	filter_add(FILTER_TYPE_ID, u32Id, FILTER_KIND_BLOCK);
    \endcode

	Example 2: \n
    Add filter for Choice and dBm, only RPS telegrams stronger than -70dBm are received.
    
    \code
 	filter_add(FILTER_TYPE_CHOICE, RADIO_CHOICE_RPS, FILTER_KIND_APPLY); 
	// Reduce filter sensivity, only telegrams with strength > -70dBm are received
	filter_add(FILTER_TYPE_DBM, 70, FILTER_KIND_BLOCK); 
	// Enable filtering
  	filter_enable(TRUE);
    \endcode

	In Dolphin Studio musst set: 
	Filter -> ON
	Filter by -> OPERATION AND
	Filter Count -> 4 (in this case >=2)

	\note The dBm values are unsigned values but actualy the should be interpretted as - dBm values
					   	
    \sa filter_del, filter_dropWeaker, filter_dropStronger, filter_dropChoice, filter_allowChoice, filter_dropId, filter_allowId
	**************************************************************************************************************************/		
	RETURN_TYPE filter_add(FILTER_TYPE u8filterType, uint32 u32compare, FILTER_KIND u8filterKind);

	/************************************************************************************************************************//*!
    BLOCKS weaker signal as -u8dBm dBm (z.b. -80, -90dBm...)
    
    \param[in]  	u8dBm			 		The dBm value is an unsigned value but actualy should be interpretted as - dBm values
    \return     	OK 						added filter to filter buffer
    \return	    	MAX_FILTER_REACHED	 	filter buffer is full
    
    \sa filter_add, filter_dropStronger, filter_dropChoice, filter_allowChoice, filter_dropId, filter_allowId
	**************************************************************************************************************************/		
	#define filter_dropWeaker(u8dBm) filter_add(FILTER_TYPE_DBM,u8dBm,FILTER_KIND_BLOCK);

	/************************************************************************************************************************//*!
    BLOCKS stronger signal as -u8dBm dBm (z.b. -80, -90dBm...)
    
    \param[in]  	u8dBm			 		The dBm value is an unsigned value but actualy should be interpretted as - dBm values
    \return     	OK 						added filter to filter buffer
    \return	    	MAX_FILTER_REACHED	 	filter buffer is full
    
    \sa filter_add, filter_dropWeaker, filter_dropChoice, filter_allowChoice, filter_dropId, filter_allowId
	**************************************************************************************************************************/		
	#define filter_dropStronger(u8dBm) filter_add(FILTER_TYPE_DBM,u8dBm,FILTER_KIND_APPLY);

	/************************************************************************************************************************//*!
    BLOCKS choice u8Choice
    
    \param[in]  	u8Choice				Choice to block
    \return     	OK 						added filter to filter buffer
    \return	    	MAX_FILTER_REACHED	 	filter buffer is full
    
    \sa filter_add, filter_dropStronger, filter_dropWeaker, filter_allowChoice, filter_dropId, filter_allowId
	**************************************************************************************************************************/		
	#define filter_dropChoice(u8Choice) filter_add(FILTER_TYPE_CHOICE,u8Choice,FILTER_KIND_BLOCK);

	/************************************************************************************************************************//*!
    ALLOWS choice u8Choice
    
    \param[in]  	u8Choice				Choice to allow
    \return     	OK 						added filter to filter buffer
    \return	    	MAX_FILTER_REACHED	 	filter buffer is full
    
    \sa filter_add, filter_dropStronger, filter_dropWeaker, filter_dropChoice, filter_dropId, filter_allowId
	**************************************************************************************************************************/		
	#define filter_allowChoice(u8Choice) filter_add(FILTER_TYPE_CHOICE,u8Choice,FILTER_KIND_APPLY);

	/************************************************************************************************************************//*!
    BLOCKS ID
    
    \param[in]  	u32Id					Id to block
    \return     	OK 						added filter to filter buffer
    \return	    	MAX_FILTER_REACHED	 	filter buffer is full
    
    \sa filter_add, filter_dropStronger, filter_dropWeaker, filter_dropChoice, filter_allowChoice, filter_allowId
	**************************************************************************************************************************/		
	#define filter_dropId(u32Id) filter_add(FILTER_TYPE_ID,u32Id,FILTER_KIND_BLOCK);

	/************************************************************************************************************************//*!
    ALLOWS ID
    
    \param[in]  	u32Id					Id to allow
    \return     	OK 						added filter to filter buffer
    \return	    	MAX_FILTER_REACHED	 	filter buffer is full
    
    \sa filter_add, filter_dropStronger, filter_dropWeaker, filter_dropChoice, filter_allowChoice, filter_dropId
	**************************************************************************************************************************/		
	#define filter_allowId(u32Id) filter_add(FILTER_TYPE_ID,u32Id,FILTER_KIND_APPLY);

	/************************************************************************************************************************//*!
    Deletes a filter from the filter list
    
	\param[in]  	u8filterType			type of filter, See #FILTER_TYPE
	\param[in]  	u32compare				compare value of filter (ID=32 bit, CHOICE=8 bit, REPT=1 bit)
	\return     	OK 						filter deleted from the filter buffer
	\return	        FILTER_NOT_FOUND     	could not be found in the filter buffer
	    
	Example 1: \n
    Add filter for ID 4711 and filter all other IDs to dev/null	and then delete filter
    
     \code
	filter_init(filter_param, SET_ALL_PARAM);
	filter_dropId(0x00004711);
	.....
	filter_del(FILTER_TYPE_ID,0x00004711);
	filter_enable(FALSE);
     \endcode

    \sa filter_add, filter_delAll
	**************************************************************************************************************************/		
	RETURN_TYPE filter_del(FILTER_TYPE u8filterType, uint32 u32compare);

	/************************************************************************************************************************//*!
    Deletes all filters from the filter list and disables filter functionality
    
	\param[in]		-
    \return 	    -
    
	Example 1: \n
    Add more filters and then delete filters
    
     \code
	filter_init(filter_param, SET_ALL_PARAM);
	filter_add(FILTER_TYPE_ID,0x00004711,FILTER_KIND_BLOCK);
	filter_add(FILTER_TYPE_ID,0x00004712,FILTER_KIND_BLOCK);
	filter_add(FILTER_TYPE_ID,0x00004713,FILTER_KIND_BLOCK);
	.....
	filter_delAll();
     \endcode

	\note
	This function is allowed to be used in an interrupt callback function ONLY if it is ensured that it is not used at the same time from the main program!

    \sa filter_add, filter_del
	**************************************************************************************************************************/		
	void filter_delAll();

	/************************************************************************************************************************//*!
    Enables or disables filter functionality
    
	\param[in]		u8enable				TRUE=filter functionality enabled, FALSE=filter functionality disabled
    \return 	    -
    
	\note
	This function is allowed to be used in an interrupt callback function ONLY if it is ensured that it is not used at the same time from the main program!

    \sa filter_add, filter_del
	**************************************************************************************************************************/		
	void filter_enable(uint8 u8enable);

//! @}


/*********************************************************************************************/
/************************************ IO MODULE **********************************************/
/*********************************************************************************************/

/*!
	\addtogroup io_grp io
	The IO module is used to access and configure the GPIO pins. The module makes it possible:
	- configure GPIO as digital IO
	- configure GPIO as analogue IO
	- read/write/toggle value on a digital pin
	- read/write analogue value on a pin
	- use the IO pin as an external interrupt source with the help of a callback function
	- configure IO pins for the UART and SPI module
	- configure pull up/downs for the digital IO pins
	
	The IO  module is configured with the help of Dolphin Studio. The Dolphin Studio generates the initialization parameters for the pins 
	in the array io_param[]. These parameters are initiated in the API using the #io_init function. The  possible IO initialization for the pins are 
	showed on the picture below.

	\note
	Be sure to initialise the IO module using Dolphin Studio correctly otherwise the peripherial sw modules will not work correctly.
    The Ports 	WXID_IO,WXOD_IO are low Power with Output 1.8V and Current low.

	\note 
	The default level of an output IO pin is LOW. When the #io_init function is called all pins which are configured as output are set active and LOW. If the application requires that a 
	pin is set always HIGH, he #io_setDigital or io_setPort hast to be called prior INIT_EO3000I.
	\code
	mainInit();
	//Currently ADIO_1 is active and LOW for several us after #io_init was called. Calling io_setDigital will cause that the pin goes low 
	//than high in a periode of few us.
	io_setDigital(ADIO_1,1);	
	\endcode			
    \code
    //This implementation will avoid the behavior described before.
    io_setDigital(ADIO_1,1);	
    mainInit();	
    \endcode			


	\image html gpio_list.png GPIO pins


	
	\ingroup ESSL
*/ 

//! @addtogroup io_cfg_grp IO config parameters
//! IO initialization parameters. The first enumeration member = 0, the next = 1, etc
//! \ingroup io_grp

//! @{
	
	//! IO initialization parameter indexes, all values are [ro]
	typedef enum 
	{	
		IDX_GPIO_CONF = 0,				
		IDX_GPIO0_CONF,				
		IDX_GPIO0_PULL_CONF,
		IDX_GPIO0_DIR,				
		IDX_GPIO1_AN,
		IDX_GPIO1_CONF,				
		IDX_GPIO1_DIG_CONF,				
		IDX_GPIO1_DIR,
		IDX_GPIO1_PULL,				
		IDX_GPIO2_CONF,				
		IDX_GPIO2_DIR,
		IDX_GPIO0,
		IDX_GPIO1,
		IDX_GPIO2,
		IDX_IO_STOP,	

	} IO_PARAM_IDX;

	//! I/O pin codes
    #define GPIO1_SHIFTMASK     10
    #define GPIO2_SHIFTMASK     200

    //! IO pin bitmasks
	typedef enum
	{
		SCSEDIO_0 = 1,
		SCLKDIO_1 = 2,
		WSDADIO_2 = 4,
		RSDADIO_3 = 8,
		ADIO_0 =  GPIO1_SHIFTMASK + 1,
		ADIO_1 =  GPIO1_SHIFTMASK + 2,
		ADIO_2 =  GPIO1_SHIFTMASK + 4,
		ADIO_3 =  GPIO1_SHIFTMASK + 8,
		ADIO_4 =  GPIO1_SHIFTMASK + 16,
		ADIO_5 =  GPIO1_SHIFTMASK + 32,
		ADIO_6 =  GPIO1_SHIFTMASK + 64,
		ADIO_7 =  GPIO1_SHIFTMASK + 128,
		WXID_IO = GPIO2_SHIFTMASK + 1,
		WXOD_IO = GPIO2_SHIFTMASK + 2,
		WAKE_0 =  GPIO2_SHIFTMASK + 4,
		WAKE_1 =  GPIO2_SHIFTMASK + 8,
	
	} 
    PIN_TYPE;


	//! PORT codes
	typedef enum
	{
		//! SCSEDIO_0 - RSDADIO_3
		GPIO0 = 0,
		//! ADIO_0 - ADIO_7
		GPIO1 = 1,
		//! WXID_IO - WAKE_1
		GPIO2 = 2,
	}
	PORT_TYPE;

	//! Analog sources
	typedef enum
	{
		//! ADIO0 Analog input
		GPIO1_ADIO_0 = ADIO_0,
		//! ADIO1 Analog input
		GPIO1_ADIO_1 = ADIO_1,		
		//! ADIO2 Analog input
		GPIO1_ADIO_2 = ADIO_2,		
		//! ADIO3 Analog input
		GPIO1_ADIO_3 = ADIO_3,		
		//! ADIO4 Analog input/output
		GPIO1_ADIO_4 = ADIO_4,		
		//! ADIO5 Analog output
		GPIO1_ADIO_5 = ADIO_5,		
		//! ADIO6 Analog output
		GPIO1_ADIO_6 = ADIO_6,		
		//! ADIO7 Analog output
		GPIO1_ADIO_7 = ADIO_7,		
		//! RF supply voltage regulator output (1,8V)
		RVDD,		
		//! Ground connection for RF (0 V)	
		RVSS,		
		//! Bandgap reference output (1,225 V), only available when radio enabled or analog measurement
		VBG,		
		//! 8 Bit Digital-/Analog-Converter 0 ... 1,225 V
		DAC,		
		//! Voltage temperature dependent (0,7 V - 2 mV/K)
		VTEMP,		
		//! Half of Synthesizer supply voltage regulator (0,9 V)
		SVDD_2,     
		//! Quarter of Unregulated supply voltage input
		VDD_4,		
		//! name all Pins to switch (only for off function needed)
		ALL			
	}
	ANSRC_TYPE;

//! @}

//! @addtogroup io_fn_grp IO functions
//! \copydetails io_grp
//! \ingroup io_grp
//! @{
	
	 /************************************************************************************************************************//*!		
	  Configures the I/O ports and for digital I/O output ports sets the initial value. 
	
	  \param[in]  	*pu8Param	 		Pointer to the list of parameters to configure the I/Os generated by DolphinStudio. See #io_param[]
	  \return    	-

	 \sa IO_PARAM_IDX, io_init
	 **************************************************************************************************************************/		
	 void io_init(uint8 *pu8Param);

	 /************************************************************************************************************************//*!		
	  This function makes it possible to configure the I/O port parameters one by one. Use this function when you need to configure the 
	  I/O port direction dynamical during the program execution (change a port from input to output). This function has the same 
	  effect as the macro io_setConfig which support was dropped in DolphinAPI 2.2.1.0.
	  WARNING: Use this function only if you really need it and if you know what you are doing! If you don't need to change the 
	  the port direction dynamical use the io_init. See notes below for further details. 

	
	  \param[in]  	u8Index			Index of the I/O parameter needed to be changed
	  \param[in]  	u8Value			Value of the parameter
	  \return    	-

      \note 
	  This function does not replace io_init. Use this function only during the program execution AFTER you already called io_init

	  \note 
	  Once you change the direction of the pins you have to also change the PULL settings. The best practice is to generate 
	  two I/O configurations with DolphinStudio, take the difference and set the settings using io_setConfig.

	  \note 
	  It is important to keep the correct order of setting the parameters otherwise you can see glitches on the ports. Make sure to stick 
	  to the following order:\n
	  PORT GPIO0: \n
	  gpio0_conf \n
	  gpio0_dir	 \n
	  gpio0_pull_conf\n	
      \n
	  PORT GPIO1: \n
	  gpio1_an\n
	  gpio1_conf\n
	  gpio1_dir\n
	  gpio1_pull\n
	  gpio1_dig_conf\n
	  \n
	  PORT GPIO2:\n
	  gpio2_conf\n
	  gpio2_dir\n


	  \note	
	  The index IDX_GPIO0, IDX_GPIO1, IDX_GPIO2 has no effect, use the io_setPort instead.

	 \sa IO_PARAM_IDX, io_init
 	 **************************************************************************************************************************/		
	 void io_setConfig(IO_PARAM_IDX u8Index, uint8 u8Value);


	/************************************************************************************************************************//*!
	Sets the digital value of a pin
	
	\param[in]  	u8Pin	  				I/O pin code. See #PIN_TYPE
	\param[in]  	u8Value			  		Value to set in the I/O pin, this can be 1 or 0
	\return     	-

	\note
	It is allowed to use this function in an interrupt callback function!

	\sa io_getDigital, io_togDigital
	**************************************************************************************************************************/		
	void io_setDigital(PIN_TYPE u8Pin, uint8 u8Value);

	/************************************************************************************************************************//*!
	Sets the digital value of the hole port 
	
	\param[in]  	u8Port	  				I/O port code. See #PORT_TYPE
	\param[in]  	u8Value			  		Value to set in the I/O port
	\return     	-

	\note
	It is allowed to use this function in an interrupt callback function!

	\sa io_setPort, io_getPort
		**************************************************************************************************************************/		
	void io_setPort(PORT_TYPE u8Pin, uint8 u8Value);
	
	/************************************************************************************************************************//*!
	Gets the digital value of a pin
	
	\param[in]  	u8Pin	  				I/O pin code. See #PIN_TYPE
	\param[out]  	u8Value			  		Digital value (0 or 1) read from the I/0 pin
	\return 	    -
						   	
	\note
	It is allowed to use this function in an interrupt callback function!

	\sa io_setDigital, io_togDigital
	**************************************************************************************************************************/		
	void io_getDigital(PIN_TYPE u8Pin, uint8 *pu8Value);

	/************************************************************************************************************************//*!
	Gets the digital value of the hole port
    \sa definition 
	
	\param[in]  	u8Port	  				I/O port code. See #PORT_TYPE
	\param[out]  	*u8Value			  	Pointer to a value where the port state is stored
	\return 	    -

	\note
	It is allowed to use this function in a callback function!

	\sa io_setPort, io_getPort
	
	**************************************************************************************************************************/		
	void io_getPort(PORT_TYPE u8Pin, uint8 *pu8Value);

	/************************************************************************************************************************//*!
	Toggles the digital value of an output pin: when pin is '1' writes a '0' and viceversa  
	
	\param[in] 	u8Pin	  				I/O pin code. See #PIN_TYPE
	\return 	-
							   	
	\note
	It is allowed to use this function in a callback function!

	\sa io_getDigital, io_setDigital
	**************************************************************************************************************************/		
	void io_togDigital(PIN_TYPE u8Pin);
	
	/************************************************************************************************************************//*!
	Sets the analog source as output.
									
	\param[in] 	    u8Pin	  Pin output, can be one of the constants from GPIO1_ADIO0 - GPIO1_ADIO7 or ALL (when u8On == 0)
	\param[in]		u8Src	  Analog signal source, can be one of the constants RVDD, RVSS, VBG, DAC, VTEMP, VDD_4
	\param[in]	 	u8On	  Switch output 0=Off, 1=On, 2...255 reserved										 
	\return     	OK        Pin switched
			    	NOT_VALID_PARAM  One of the parameters given is not in allowed range
	
 	 \note
	 Be sure before using this function to configure this pin as analog output

	 \note
	 If you set an analog source to the outputs GPIO1_ADIO4 or GPIO1_ADIO6 then any analog measurement by calling io_measAnalog
	 (or the predefined macros using this function) is NOT possible and will return NOT_VALID_PARAM!

	 \note
	 Due to HW restrictions the following restrictions appear:
	 RVDD, RVSS, VBG, DAC, VDD_4 and VTEMP can only be switched to GPIO1_ADIO4, GPIO1_ADIO5, GPIO1_ADIO6 or GPIO1_ADIO7
	 At the same time the following signals can be switched:
	 - RVDD, RVSS, VBG, DAC, VDD_4 or VTEMP to GPIO1_ADIO5 or GPIO1_ADIO7
	 - RVDD, RVSS, VBG, DAC, VDD_4 or VTEMP to GPIO1_ADIO4 or GPIO1_ADIO6


	**************************************************************************************************************************/		
	RETURN_TYPE io_setAnalog(ANSRC_TYPE u8Pin, ANSRC_TYPE u8Src, uint8 u8On);

	/************************************************************************************************************************//*!
	Sets the DAC
									
	\param[in]  	u8Value	  Value to set on DAC
	\param[in]	 	u8On	  Switch output 0=Off, 1...255 On										 
	\return 	    -
	
	\note
	Due to hardware restrictions it is not possible to simultaneously perform analog measurent and analog output.
	If you use the analog output function io_setDAC(value, ON), be sure to call io_setDAC(0, OFF) before calling analog measurement 
	functions like io_measAnalog() or io_ulpMeasAnalog(). 

	**************************************************************************************************************************/		
	void io_setDAC(uint8 u8Value, uint8 u8On);

	/************************************************************************************************************************//*!
    Radio and analog measurements share the same analog to digital converter. Therefor it is necessary to enable the analog module
    prior of performing measurements. Whilst analog measurements measurements are enabled it is not possible to perform an radio receiving or transmitting.
    Therefor special care needs to be taken when and how long the analog measurements are enabled.
									
	\param[in]  	u8Enable	0=disable, 1=enable no VGA, 2=enable with VGA
	\return 	-

     \note 
     The VGA gain factor is 11.22=21dB

	 \note
	 It is not necessary to disable analog measurement before switching from measurement with or without VGA and reverse! But
	 be sure to disable analog measurement when you want to use radio again.<br>
     Do not call the io_enableAnalog(1 or 2) more than once, before calling io_enableAnalog(0)!!

	**************************************************************************************************************************/		
	void io_enableAnalog(uint8 u8Enable);

	/************************************************************************************************************************//*!
	Measures analog value
									
	\param[in]  	u8RefPos	Positive reference can be either #ANSRC_TYPE or ADIO0 - ADIO7 (see #PIN_TYPE)
	\param[in]		u8RefNeg	Negative reference can be either #ANSRC_TYPE or ADIO0 - ADIO7 (see #PIN_TYPE)
	\param[in] 		u8MeasPos	Positive signal input can be either #ANSRC_TYPE or ADIO0 - ADIO7 (see #PIN_TYPE)
	\param[in] 		u8MeasNeg	Negative signal input can be either #ANSRC_TYPE or ADIO0 - ADIO7 (see #PIN_TYPE)
	\param[in] 		u8Res		Resolution (1-12 bit) is the range of measurement scaled by reference
	\param[out] 	*u16Value	Pointer to Measured value 
	\return 	    OK        	The measurement was successful
				    NOT_VALID_PARAM  One of the parameters given is not in allowed range (u16Value is not modified)

	 \note
	 Be sure to wait a certain ammount of time before the signal gets stable

	 \note
	 For measurement with VGA, only ADIOx inputs are allowed!

	 \note
	 As radio components will be used for analog measurement it is necessary to call io_enableAnalog(1) or io_enableAnalog(2) before calling
	 io_measAnalog(...) to switch analog part working. After calling io_measAnalog(...) the function io_enableAnalog(0) has to be called
	 to switch radio components working. If more than one call to io_measAnalog will be done and between
	 that calls radio is not needed, then here io_enableAnalog(0) need only to be called after the last use of io_measAnalog.

	 \code
	 #define BIT12 (1<<12)
	 uint16 value;
	 float  fVolt;
	 uint8  str[50];
	 io_enableAnalog(1); // configuring hardware for analog measurement
	 io_measAnalog(RVDD, RVSS, GPIO1_ADIO_0, RVSS, 12, &value);
	 ..... // no radio is needed now
	 io_measAnalog(RVDD, RVSS, GPIO1_ADIO_1, RVSS, 12, &value);
	 io_enableAnalog(0); // restoring previous configuration for radio functionality
	 fVolt = 1.8 * value / (BIT12-1);
	 sprintf(str,"%1.3fV (%d)\n",fVolt,value);
	 \endcode

	 \note
	 Example for measurement with and without VGA:
	 \code
	 uint16 value;
	 io_enableAnalog(1); // configuring hardware for analog measurement without VGA
	 io_measAnalog(RVDD, RVSS, GPIO1_ADIO_0, RVSS, 12, &value);
	 ..... // no radio is needed now
	 io_enableAnalog(2); // configuring hardware for analog measurement with VGA
	 io_measAnalog(GPIO1_ADIO_0, GPIO1_ADIO_1, GPIO1_ADIO_1, GPIO1_ADIO_2, 8, &value);
	 io_enableAnalog(0); // restoring previous configuration for radio functionality
	 \endcode

	 \note
	 If you set an analog source to the outputs GPIO1_ADIO_4 or GPIO1_ADIO_6 then any analog measurement by calling io_measAnalog
	 (or the predefined macros using this function) is NOT possible and will return NOT_VALID_PARAM!


	**************************************************************************************************************************/		
	RETURN_TYPE io_measAnalog(ANSRC_TYPE u8RefPos, ANSRC_TYPE u8RefNeg, ANSRC_TYPE u8MeasPos, ANSRC_TYPE u8MeasNeg, uint8 u8Res, uint16 *pu16Value);
  
	/************************************************************************************************************************//*!
	Measures single ended analog value against RVSS. Use RVDD as reference
									
	\param[in]  	u8Pin		Pin to measure
	\param[in]		u8Res		Resolution
	\param[out] 	*pu16Value	Pointer to Measured value 
	\return 	    -
		
	**************************************************************************************************************************/		
	#define io_measSingleRVDD(u8Pin, u8Res, pu16Value) io_measAnalog(RVDD, RVSS, u8Pin, RVSS, u8Res, pu16Value)

	/************************************************************************************************************************//*!
	Measures single ended analog value against RVSS. Uses VBG as reference
									
	\param[in] 		u8Ref		Pin with VBG reference
	\param[in] 		u8Pin		Pin to measure
	\param[in]		u8Res		Resolution
	\param[out] 	*pu16Value	Pointer to Measured value 
	\return 		-
	
	\note
	Be sure to configure 1 pin where the VBG is set as output. 
	Be sure to call io_setAnalog with parameter VBG before calling this function.

	**************************************************************************************************************************/		
	#define io_measSingleVBG(u8Ref, u8Pin, u8Res, pu16Value) io_measAnalog(u8Ref, RVSS, u8Pin, RVSS, u8Res, pu16Value)

	/************************************************************************************************************************//*!
	Measures single ended analog value against external reference. 
									
	\param[in]  	u8Ref		Pin where the external reference is read
	\param[in]  	u8Pin		Pin to measure
	\param[in]		u8Res		Resolution
	\param[out] 		*pu16Value	Pointer to Measured value 
	\return 		-
	
	 \note
	 Be sure to configure 1 pin where the external reference as input is read 

	**************************************************************************************************************************/		
	#define io_measSingleEXT(u8ExtRef, u8Pin, u8Res, pu16Value)	io_measAnalog(u8ExtRef, RVSS, u8Pin, RVSS, u8Res, pu16Value)	

	/************************************************************************************************************************//*!
	Measures analog value for ulp applications
									
	\param[in]  	u8Meas		Input signal to measure, can be either #ANSRC_TYPE or ADIO0 - ADIO7 (see #PIN_TYPE)
	\param[out] 	*ps16Value	Pointer to Measured value. This is a value measured against an internal 0.9V voltage. 
	\return 		OK        	The measurement was successful
					NOT_VALID_PARAM  One of the parameters given is not in allowed range (u16Value is not modified)

	 \note
	 Be sure to wait a certain ammount of time before the signal gets stable

	 \note
	 For measurement with VGA, use #io_ulpMeasAnalogVGA

	 \note
	 As radio components will be used for analog measurement it is necessary to call io_enableAnalog(1) before calling
	 io_ulpMeasAnalog(...) to switch analog part working. After calling io_ulpMeasAnalog(...) the function io_enableAnalog(0) has to be called
	 to switch radio components working. If more than one call to io_measAnalog will be done and between
	 that calls radio is not needed, then here io_enableAnalog(0) need only to be called after the last use of io_ulpMeasAnalog.

	 \note
	 The returned measurement value is the measurement against an internal reference voltage and cannot be used in
	 the application till it is scaled using io_ulpScaleAnalog.
	 To use the ulp analog measurement it is necessary to make single measurements of the negative and positive reference,
	 and the negative and positive measurement pin. If there are same measurements, f.e. RVSS, it has only to be done once.
	
	 \code
	 The following example shows the code for performing three measurements of ADIO_1, ADIO_2 and ADIO_3 against GND. The selected
	 reference is RVDD, the resolution of the result is 8 bit, so when the measurement value is 0xff the voltage of
	 RVDD is measured.

	 sint16 s16negref;
	 sint16 s16posref;
	 sint16 s16adio1value;
	 sint16 s16adio2value;
	 sint16 s16adio3value;
	 uint16 u16adio1value;
	 uint16 u16adio2value;
	 uint16 u16adio3value;
	 INIT_EO3000I
	 io_enableAnalog(1); // configuring hardware for analog measurement no VGA, increase current to Analog current
	 io_ulpMeasAnalog(RVDD, &s16posref); // measure positive reference against internal voltage
	 io_ulpMeasAnalog(RVSS, &s16negref); // measure negative reference against internal voltage
	 io_ulpMeasAnalog(GPIO1_ADIO_1, &s16adio1value); // measure ADIO_1 against internal voltage
	 io_ulpMeasAnalog(GPIO1_ADIO_2, &s16adio2value); // measure ADIO_2 against internal voltage
	 io_ulpMeasAnalog(GPIO1_ADIO_3, &s16adio3value); // measure ADIO_3 against internal voltage
	 io_enableAnalog(0); // restoring previous configuration for radio functionality and reduce current to CPU current
	 io_ulpScaleAnalog(s16posref, s16negref, s16adio1value, s16negref, 8, &u16adio1value); // scale and calculate result for ADIO_1
	 io_ulpScaleAnalog(s16posref, s16negref, s16adio2value, s16negref, 8, &u16adio2value); // scale and calculate result for ADIO_2
	 io_ulpScaleAnalog(s16posref, s16negref, s16adio3value, s16negref, 8, &u16adio3value); // scale and calculate result for ADIO_3
	
	 \endcode

	 \note
	 If you set an analog source to the outputs GPIO1_ADIO_4 or GPIO1_ADIO_6 then any analog measurement by calling io_ulpMeasAnalog
	 is NOT possible and will return NOT_VALID_PARAM!


	\sa io_ulpScaleAnalog, io_ulpMeasAnalogVGA, io_ulpScaleAnalogVGA, io_measAnalog 
	**************************************************************************************************************************/		
	RETURN_TYPE io_ulpMeasAnalog(ANSRC_TYPE u8Meas, sint16 *ps16Value);

	/************************************************************************************************************************//*!
    Scales the 4 with io_ulpMeasAnalog measured values (reference and measurement) to given resolution
    
    \param[in]  	s16RefPos	Measured positive reference (output of io_ulpMeasAnalog)
    \param[in]  	s16RefNeg	Measured negative reference (output of io_ulpMeasAnalog)
    \param[in]  	s16MeasPos	Measured positive measurement value (output of io_ulpMeasAnalog)
    \param[in]  	s16MeasNeg	Measured negative measurement value (output of io_ulpMeasAnalog)
	\param[in]		u8Res		Resolution
	\param[out] 	*pu16Value	Pointer to scaled value 
    \return 		-

	\note
	Example using this function see description of #io_ulpMeasAnalog
    						   	
	\sa io_ulpMeasAnalog, io_ulpMeasAnalogVGA, io_ulpScaleAnalogVGA, io_measAnalog 
	**************************************************************************************************************************/		
	void io_ulpScaleAnalog(sint16 s16RefPos, sint16 s16RefNeg, sint16 s16MeasPos, sint16 s16MeasNeg, uint8 u8Res, uint16 *pu16Value);

	/************************************************************************************************************************//*!
	Measures analog value for ulp applications with VGA (amplifier)
									
	\param[in]  	u8Pos		Positive input signal to measure, can be either #ANSRC_TYPE or ADIO0 - ADIO7 (see #PIN_TYPE)
	\param[in]  	u8Neg		Negative input signal to measure, can be either #ANSRC_TYPE or ADIO0 - ADIO7 (see #PIN_TYPE)
	\param[out] 	*ps16Value	Pointer to Measured value. 
	\return 		OK        	The measurement was successful
					NOT_VALID_PARAM  One of the parameters given is not in allowed range (u16Value is not modified)

	 \note
	 Be sure to wait a certain ammount of time before the signal gets stable

	 \note
	 For measurement without VGA, use #io_ulpMeasAnalog

	 \note
	 As radio components will be used for analog measurement it is necessary to call io_enableAnalog(2) before calling
	 io_ulpMeasAnalogVGA(...) to switch analog part working. After calling io_ulpMeasAnalogVGA(...) the function io_enableAnalog(0) has to be called
	 to switch radio components working. If more than one call to io_ulpMeasAnalogVGA will be done and between
	 that calls radio is not needed, then here io_enableAnalog(0) need only to be called after the last use of io_ulpMeasAnalogVGA.

	 \code
	 The following example shows the code for performing a measurement with ADIO_1 as a reference to GND and ADIO_2 as measurement pin. 
	 The resolution of the result is 8 bit, so when the measurement value is 0xff the voltage of ADIO_1 and ADIO_2 is equal.

	 sint16 s16ref;
	 sint16 s16meas;
	 uint16 u16value;
	 INIT_EO3000I
	 io_enableAnalog(2); // configuring hardware for analog measurement with VGA, increase current to Analog current
	 io_ulpMeasAnalogVGA(GPIO1_ADIO_1, RVSS, &s16ref); // measure reference
	 io_ulpMeasAnalogVGA(GPIO1_ADIO_2, RVSS, &s16meas); // measure measurement value
	 io_enableAnalog(0); // restoring previous configuration for radio functionality and reduce current to CPU current
	 io_ulpScaleAnalogVGA(s16ref, s16meas, 8, &u16value); // scale and calculate result
	
	 \endcode

	 \note
	 If you set an analog source to the outputs GPIO1_ADIO_4 or GPIO1_ADIO_6 then any analog measurement by calling io_ulpMeasAnalogVGA
	 is NOT possible and will return NOT_VALID_PARAM!


	\sa io_ulpScaleAnalog, io_ulpMeasAnalog, io_ulpScaleAnalogVGA, io_measAnalog 
	**************************************************************************************************************************/		
	RETURN_TYPE io_ulpMeasAnalogVGA(ANSRC_TYPE u8Pos, ANSRC_TYPE u8Neg, sint16 *ps16Value);

	/************************************************************************************************************************//*!
    Scales the 2 with io_ulpMeasAnalogVGA measured values (reference and measurement) to given resolution
    
    \param[in]  	s16Ref	Measured reference value (output of io_ulpMeasAnalogVGA)
    \param[in]  	s16Meas	Measured measurement value (output of io_ulpMeasAnalogVGA)
	\param[in]		u8Res		Resolution
	\param[out] 	*pu16Value	Pointer to scaled value 
    \return 		-

	\note
	Example using this function see description of #io_ulpMeasAnalogVGA
    						   	
	\sa io_ulpMeasAnalogVGA, io_ulpMeasAnalog, io_ulpScaleAnalog, io_measAnalog
	**************************************************************************************************************************/		
	void io_ulpScaleAnalogVGA(sint16 s16Ref, sint16 s16Meas, uint8 u8Res, uint16 *pu16Value);

	/************************************************************************************************************************//*!
    Sets function pointer for callback function in interrupt of GPIO1 pins 0, 1 and 2
    
    \param[in]  	*pu16FnPtr	  Pointer to the callback function which will be called when GPIO1 pins 0, 1 or 2 generates an interrupt
    \return 		-
    						   	
    \sa io_ADIO03enableCB, io_ADIO47initCB, io_ADIO47enableCB
	**************************************************************************************************************************/		
	void io_ADIO03initCB(void code *pu16FnPtr);

	/************************************************************************************************************************//*!
    Enables or disables callback when GPIO1 pins 0, 1 or 2 generates an interrupt
    
    \param[in]  	u8Enable	  			\ref TRUE, callback enabled, \ref FALSE, callback disabled
    \return 		-

	\note
	Do not stay in the callback function too long (not more than 100 us because that takes too much time away from the schedule)
	
	\note
	The callback function will be called during an interrupt! Do only use allowed API-Functions in callback function.
	Do not switch the registerbank. Do not use overlaying and optimizing in callback function.
	You are allowed to:
	- allocate local variables 
	- you are allowed to read from flash using code[] 
	- you are allowed to change global variables of the code but before be sure to set them to volatile

	\note
	If you did not initialised callback function pointer and you enable callback function, then the interrupt occurs, but
	function cannot be called and interrupt returns without function. Program will not crash, but resources are used.

	\code

	//define the callback function
	void callback()
	{
		...	  // stay not longer than 100 us!
	}
	
	void yourFunction()
	{
		io_init(io_param);		   // Selection of pins only in DolphinStudio
		io_ADIO03initCB((void *)&callback);	       // Set address of your callback function
		io_ADIO03enableCB(TRUE);				   // This is to enable the interrupt of GPIO1 pin you selected
		isr_genInit(TRUE);						   // This is necessary to enable the general interrupt
		.....
		io_ADIO03enableCB(FALSE);                  // if you need you can temporary disable callback
		.....
		io_ADIO03enableCB(TRUE);                   // and now enable callback again
		.....
		io_ADIO03enableCB(FALSE);                  // finaly disable callback
		isr_genInit(FALSE);                        // and finally disable all external and TIMER1 interrupt
	}

	\endcode
    						   	
    \sa io_ADIO03initCB, io_ADIO47initCB, io_ADIO47enableCB
	**************************************************************************************************************************/		
	void io_ADIO03enableCB(uint8 u8Enable);

	/************************************************************************************************************************//*!
    Sets function pointer for callback function in interrupt of GPIO1 pins 4, 5 and 6
    
    \param[in]  	*pu16FnPtr	  Pointer to the callback function which will be called when GPIO1 pins 4, 5 or 6 generates an interrupt
    \return 		-
    						   	
    \sa io_ADIO47enableCB, io_ADIO03initCB, io_ADIO03enableCB
	**************************************************************************************************************************/		
	void io_ADIO47initCB(void code *pu16FnPtr);

	/************************************************************************************************************************//*!
    Enables or disables callback when GPIO1 pins 4, 5 or 6 generates an interrupt
    
    \param[in]  	u8Enable	  			\ref TRUE, callback enabled, \ref FALSE, callback disabled
    \return 		-

	\note
	Do not stay in the callback function too long (not more than 100 us because that takes too much time away from the schedule)
	
	\note												    
	The callback function will be called during an interrupt! Do only use allowed API-Functions in callback function.
	Do not switch the registerbank. Do not use overlaying and optimizing in callback function.
	You are allowed to:
	- allocate local variables 
	- you are allowed to read from flash using code[] 
	- you are allowed to change global variables of the code but before be sure to set them to volatile

	\note
	If you did not initialised callback function pointer and you enable callback function, then the interrupt occurs, but
	function cannot be called and interrupt returns without function. Program will not crash, but resources are used.

	\code

	//define the callback function
	void callback()
	{
		...	  // stay not longer than 100 us!
	}
	
	void yourFunction()
	{
		io_init(io_param);						   // Selection of pins only in DolphinStudio
		io_ADIO47initCB((void *)&callback); 	   // Set address of your callback function
		io_ADIO47enableCB(TRUE);				   // This is to enable the interrupt of GPIO1 pin you selected
		isr_genInit(TRUE);						   // This is necessary to enable the general interrupt
		.....
		io_ADIO47enableCB(FALSE);                  // if you need you can temporary disable callback
		.....
		io_ADIO47enableCB(TRUE);                   // and now enable callback again
		.....
		io_ADIO47enableCB(FALSE);                  // finaly disable callback
		isr_genInit(FALSE);                        // and finally disable all external and TIMER1 interrupt
	}

	\endcode
    						   	
    \sa io_ADIO47initCB, io_ADIO03initCB, io_ADIO03enableCB
	**************************************************************************************************************************/		
	void io_ADIO47enableCB(uint8 u8Enable);

	
	/************************************************************************************************************************//*!
    Calculates a random 16 bit value reading the noise of the ADC
    
    \param[in]  	u8iterations	Number of iterations for calculating values, as higher es better
								Meaningful minimum value is 4
	\param[out]		*pu16Rnd		Pointer to put the random value back
    \return 		-
    
	\note
	The function reads the noise of the ADC. It is necessary to enable the radio receiver (call radio_enableRx(1);) prior
	calling this function. Otherwise there is no noise and the function will always return 0.
	
	\note
	As more iterations will be done as more the value will be random and as longer the function will take.
	A meaningful value is 10. If the parameter is < 4 then 4 will be taken.
							   	
    \sa 
	**************************************************************************************************************************/		
	void io_getAnalogRnd(uint8 u8Iterations, uint16 *pu16Rnd);

	/************************************************************************************************************************//*!
    Sets function pointer for callback function in interrupt of wake 0 pin
    
    \param[in]  	*pu16FnPtr	  Pointer to the callback function which will be called when wake pin 0 changes
    \return 		-

    \sa io_Wake0enableCB
	**************************************************************************************************************************/		
	void io_Wake0initCB(void code *pu16FnPtr); 

	/************************************************************************************************************************//*!
    Enables or disables callback when wake 0 pin changes
    
    \param[in]  	u8Enable	  			\ref TRUE, callback enabled, \ref FALSE, callback disabled
    \return 		-

	\note
	Do not stay in the callback function too long (not more than 100 us because that takes too much time away from the schedule)
	
	\note
	The callback function will be called during an interrupt! Do only use allowed API-Functions in callback function.
	Do not switch the registerbank. Do not use overlaying and optimizing in callback function.
	You are allowed to:
	- allocate local variables 
	- you are allowed to read from flash using code[] 
	- you are allowed to change global variables of the code but before be sure to set them to volatile

	\note
	If you did not initialised callback function pointer and you enable callback function, then the interrupt occurs, but
	function cannot be called and interrupt returns without function. Program will not crash, but resources are used.

	\code

	//define the callback function
	void callback()
	{
		uint8 u8state;
		io_getPort(GPIO2, &u8state);
		if (u8state & 0x04)
		{
			... staff to do, when wake 0 pin is set
		}
		...	  // stay not longer than 100 us!
	}
	
	void yourFunction()
	{
		io_init(io_param);						   // Selection of pins only in DolphinStudio
		io_Wake0initCB((void *)&callback);  	   // Set address of your callback function
		io_Wake0enableCB(TRUE);				       // This is to enable the interrupt of wake pin 0
		isr_sysInit(TRUE);						   // This is necessary to enable the system interrupt
		.....
		io_Wake0enableCB(FALSE);                   // if you need you can temporary disable callback
		.....
		io_Wake0enableCB(TRUE);                    // and now enable callback again
		.....
		io_Wake0enableCB(FALSE);                   // finaly disable callback
		isr_sysInit(FALSE);                        // and finaly disable all system interrupts
	}

	\endcode
  						   	
    \sa io_Wake0initCB, isr_sysInit
	**************************************************************************************************************************/		
	void io_Wake0enableCB(uint8 u8Enable);

	/************************************************************************************************************************//*!
    Sets function pointer for callback function in interrupt of wake 1 pin
    
    \param[in]  	*pu16FnPtr	  Pointer to the callback function which will be called when wake pin 1 changes
    \return 		-
 
    \sa io_Wake1enableCB
	**************************************************************************************************************************/		
	void io_Wake1initCB(void code *pu16FnPtr); 

	/************************************************************************************************************************//*!
    Enables or disables callback when wake 1 pin changes
    
    \param[in]  	u8Enable	  			\ref TRUE, callback enabled, \ref FALSE, callback disabled
    \return 		-

	\note
	Do not stay in the callback function too long (not more than 100 us because that takes too much time away from the schedule)
	
	\note
	The callback function will be called during an interrupt! Do only use allowed API-Functions in callback function.
	Do not switch the registerbank. Do not use overlaying and optimizing in callback function.
	You are allowed to:
	- allocate local variables 
	- you are allowed to read from flash using code[] 
	- you are allowed to change global variables of the code but before be sure to set them to volatile

	\note
	If you did not initialised callback function pointer and you enable callback function, then the interrupt occurs, but
	function cannot be called and interrupt returns without function. Program will not crash, but resources are used.

	\code

	//define the callback function
	void callback()
	{
		uint8 u8state;
		io_getPort(GPIO2, &u8state);
		if (u8state & 0x08)
		{
			... staff to do, when wake 1 pin is set
		}
		...	  // stay not longer than 100 us!
	}
	
	void yourFunction()
	{
		io_init(io_param);		   					// Selection of pins only in DolphinStudio
		io_Wake1initCB((void *)&callback);  	   // Set address of your callback function
		io_Wake1enableCB(TRUE);				       // This is to enable the interrupt of wake pin 1
		isr_sysInit(TRUE);						   // This is necessary to enable the system interrupt
		.....
		io_Wake1enableCB(FALSE);                   // if you need you can temporary disable callback
		.....
		io_Wake1enableCB(TRUE);                    // and now enable callback again
		.....
		io_Wake1enableCB(FALSE);                   // finaly disable callback
		isr_sysInit(FALSE);                        // and finaly disable all system interrupts
	}

	\endcode
    						   	
    \sa io_Wake0initCB, isr_sysInit
	**************************************************************************************************************************/		
	void io_Wake1enableCB(uint8 u8Enable);

//! @}


/*********************************************************************************************/
/************************************ ISR FUNCTION PROTOTYPES ********************************/
/*********************************************************************************************/
/*!
	\addtogroup isr_grp  isr
	The ISR module offers a control over the system tasks that are running parallel to the application. Using the ISR init function
	the application can:
	- initialise repeating
	- enable/disable interrupts for callback functions
	\ingroup ESSL
*/ 

//! @addtogroup isr_fn_grp ISR functions 
//! \copydetails isr_grp
//! \ingroup isr_grp
//! @{

	/************************************************************************************************************************//*!
	Timer0 interrupt initialization function for standard scheduler. You have to call this function
	in the INIT_EO3000I initialization macro in order to be able to use the API. For more information 
	see #INIT_EO3000I description.
	             	
	\param  	-
	\return 	-

	**************************************************************************************************************************/		
	void isr_timer0Init();
	
	/************************************************************************************************************************//*!
	Enables or disables the general interrupt
	
    \param[in]  	u8Enable	  			\ref TRUE, general interrupt enabled, \ref FALSE, general interrupt disabled
	\return 		-

	\note
	This function has to be called with parameter TRUE, when timer1 interrupt callback is to be used

	**************************************************************************************************************************/		
	void isr_genInit(uint8 u8Enable);

	/************************************************************************************************************************//*!
	Enables or disables the system interrupt
	
    \param[in]  	u8Enable	  			\ref TRUE, system interrupt enabled, \ref FALSE, general interrupt disabled
	\return 		-

	\note
	This function has to be called with parameter TRUE, when wake0 or wake1 interrupt callback is to be used

	**************************************************************************************************************************/		
	void isr_sysInit(uint8 u8Enable);

	/************************************************************************************************************************//*!
	Timer0 interrupt initialization function for SmartACK scheduler. You have to call this function
	in the INIT_EO3000I initialization macro in order to be able to use the SmartACK API. For more information 
	see #INIT_EO3000I description.
	
	\param  	-
	\return 	-

	**************************************************************************************************************************/		
	void isr_timer0_smack_PM_Init();

//! @}


/*********************************************************************************************/
/************************************ MEMORY MODULE ******************************************/
/*********************************************************************************************/
   
/*!
	\addtogroup mem_grp  mem
	The MEM module offers a read/write interface to the following memories:
	- flash program area (Address range: 0x0000 - 0x7EFF, Size: 32 kB)
	- configuration area (Address range: 0x9F00 - 0x9FFF (see #CFG_ADDR, read only), Size: 256 byte)
	- RAM0 (Address range: 0x00 - 0x1F, Size: 32 byte) 
	
	Using the MEM module it is possible to verify flash program area consistancy using Built In Self test routine. Be sure to read \ref flash_arch, \ref cfg_areapage.
	\ingroup ESSL
*/ 

//! @addtogroup mem_struct_grp Memory structures and constants
//! Structures that are used in MEM module
//! \ingroup mem_grp 
//! @{

	//! Configruation area address - use this only for reading. 
	#define CFG_ADDR				0x9F00
	//! Log area address
	#define LOG_ADDR				0x7E00

	//! Configuration Area structure. For more information read chapter \ref cfg_areapage
	typedef union
	{		
		struct raw_cfg_area
		{
			uint8 bytes[256];		
		} raw;
		
		struct val
		{
			//! <b>Offset:0x00</b>\n<b>Group:FirmwareInfo</b>\n Program size in FLASH pages (256 bytes) - indicates the last page where the program in FLASH is saved. This is needed for the correct Flash BIST execution, see \ref BIST.  
			uint8	u8PrgSize;				
			//! <b>Offset:0x01</b>\n<b>Group:-</b>\n Reserved
		 	uint8	u8Reserved;				
			//! <b>Offset:0x02</b>\n<b>Group:-</b>\n Reserved
		 	uint16	u16Reserved0;			 
			//! <b>Offset:0x04</b>\n<b>Group:FirmwareInfo</b>\n Library version, for more info see \ref ApplicationVersion
		 	uint8	u8APIVersion[4];		
			//! <b>Offset:0x08</b>\n<b>Group:FirmwareInfo</b>\n Application version, for more info see \ref ApplicationVersion
		 	uint8	u8AppVersion[4];		 
			//! <b>Offset:0x0C</b>\n<b>Group:FirmwareInfo</b>\n Application description, for more info see \ref ApplicationVersion		 	
			uint8	u8AppDescription[16];
			//! <b>Offset:0x1C</b>\n<b>Group:Calibration</b>\n FracN calibration values for radio RX
		 	uint8	u8FracnRxHi;			
			//! <b>Offset:0x1D</b>\n<b>Group:Calibration</b>\n FracN calibration values for radio RX
			uint8	u8FracnRxLo;			 
			//! <b>Offset:0x1E</b>\n<b>Group:Calibration</b>\n FracN calibration values for radio TX
			uint8	u8FracnTxHi;			
			//! <b>Offset:0x1F</b>\n<b>Group:Calibration</b>\n FracN calibration values for radio TX
			uint8	u8FracnTxLo;			
			//! <b>Offset:0x20</b>\n<b>Group:-</b>\n reserved for more precise short term calibration - not used
		 	uint16	u16Reserved;
			//! <b>Offset:0x22</b>\n<b>Group:Calibration</b>\n SRCO calibration for ShortTerm timer, for more information read \ref timer_calibration
		 	uint16	u16CalibShortTerm;
			//! <b>Offset:0x24</b>\n<b>Group:Calibration</b>\n Flywheel calibration for Flywheel timer, for more information read \ref timer_calibration			
			float32 f32CalibFlywheel;
			//! <b>Offset:0x28</b>\n<b>Group:-</b>\n reserved for more precise watchdog calibration - not used			
		 	uint16	u16Reserved1;
			//! <b>Offset:0x2A</b>\n<b>Group:Calibration</b>\n WRCO calibration for Watchdog timer, for more information read \ref timer_calibration
		 	uint16 u16CalibWatchdog;
			//! //! <b>Offset:0x2C</b>\n<b>Group:Calibration</b>\n Temperature Slope
		 	float32 f32TemperatureSlope;			
			//! <b>Offset:0x30</b>\n<b>Group:-</b>\n Reserved
			uint8  u8Reserved1[3];
			//! <b>Offset:0x33</b>\n<b>Group:-</b>\n u8BaseID, makes possible for a transmitter to simulate devices with multiple ID
			uint8  u8BaseID[44];
			//! <b>Offset:0x5F</b>\n<b>Group:Calibration</b>\n ID conformity check for configuration area, prevents programming a bacuk CFG hex file to an incorrect module
			uint32  u32ConformID;
			//! <b>Offset:0x63</b>\n<b>Group:TracingInfo</b>\n Unique identification of the module manufacturer
			uint8 u8Manufacturer;
			//! <b>Offset:0x64</b>\n<b>Group:TracingInfo</b>\n Configuration area structure revision
			uint8 u8CfgVersion;			
			//! <b>Offset:0x65</b>\n<b>Group:TracingInfo</b>\n Modul frequency
			uint8 u8ModulFrequency;
			//! <b>Offset:0x66</b>\n<b>Group:TracingInfo</b>\n Modul HW type - unique identification of module type
			uint8 u8ModulType;
			//! <b>Offset:0x67</b>\n<b>Group:Firmware</b>\n Firmware radio setting version
			uint8 u8RadioSettingVer[3];
			//! <b>Offset:0x6A</b>\n<b>Group:TracingInfo</b>\n DMC code
			uint8 u8DMC[12];    
			//! <b>Offset:0x76</b>\n<b>Group:TracingInfo</b>\n Modul HW stepcode
            uint8 u8Stepcode;
			//! <b>Offset:0x77</b>\n<b>Group:Calibration</b>\n Temperature sensor calibration value
			float32 f32CalibTemperature;
			//! <b>Offset:0x7B</b>\n<b>Group:Calibration</b>\n AD converter calibration value for temperature
			sint16 s16CalibADTemperature;
            //! <b>Offset:0x7D</b>\n<b>Group:-</b>\n Reserved
			uint8  u8Reserved2[3];         
			//! <b>Offset:0x80</b>\n<b>Group:-</b>\n Reserved for custom application calibration values
			uint8  u8ReservedApp[128];         
		} val;

		
	} CFG_AREA;

	//! Structure to access log area
	typedef union
	{		
		struct raw_log_area{
			uint8 bytes[256];		
		} raw;
		
		struct val_log_area{
			 //! API System log + reserved until 128
			 uint8 u8APIErrLog[128];
			 //! Reserved for APP for example: System Log-Misc values, ID Table, etc.
			 uint8 u8ReservedAPP[128];

		} val;
			  	
	} LOG_AREA;

//! @}

//! @addtogroup mem_fn_grp MEMORY functions
//! \copydetails mem_grp
//! \ingroup mem_grp
//! @{
	/************************************************************************************************************************//*!
	Takes the <em>u16NumBytes</em> bytes from the XDATA address pointing to by <em>pu8SrcAddr</em>     
	and copies them to flash memory. Before writing to the FLASH all accessed FLASH pages are erased (1 page is 256 byte).
	
	\param[in]  	*pu8SrcAddr		Pointer to the bytes source, (only XDATA allowed) 
	\param[in]  	u16DstAddr		Destination memory address, PRG_AREA: 0x0000 - 0x7EFF
	\param[in]  	u16NumBytes		Number of bytes to copy	(1..2048 because this is the max XDATA size)
	
	\return			ADDR_OUT_OF_MEM 	If the u16DstAddr + u16NumBytes is out of FLASH memory range
	\return			FLASH_HW_ERROR	    If there was an error during erase operation
	\return			OK                  if the process was succesfull
							   	

	\note
	When writing to FLASH the bootloader is called. The *pu8SrcAddr must reside in the XDATA!

	\note
	Be sure XTAL is running when calling this function. When running with CRCO the duration of the flash write can take longer.
	Every time you write in a page even if only 2-3 bytes the page will be erased. Therfore be sure to keep a shadow register
	for the area you will to write in the XDATA. 

	\note
	Keep in mind that when writing to the FLASH all the interrupts are disabled. Therfore it is not possible to 
	receive telegrams from radio or uart. 

	\note
	Note when writing to FLASH let's say 256 bytes it takes more than 1 ms time. The system schedule has 1ms
	takt but the interrupts are switched off during flash write and with them also the schedule timer. 
	Therfore all the SW timer and also the system timer will be unprecise.  This has also influence on subtelegram
	timing!

	\note
	Avoid writing too often to FLASH. The FLASH memories has a limited lifecycle and accesing them 
	needs lot of system resources (critical from power or timing point of view)

	\note
	When writing to FLASH_PRG be sure to store data beyond the program area. You can get the size of your
	program in number of flash pages by calling #mem_getDataAddr, #mem_getPrgSize macro
	
	\note 
	You can also rewrite your own program in the FLASH. The mem_write is executed in the FLASH itself
	so be sure to avoid rewriting the mem_writeFlash function otherwise your program will crash.

    \note 
    The writing routine does not verify the bytes written in the flash. In a critical application the application 
    should compare the data written to the flash with the data residing in RAM.

	\note When receiving or sending an UART or radio telegram and simultaneously writing in FLASH memory the effect could be:
	- corrupt UART telegram receiving
	- corrupt radio telegram receiving
	- wrong sub telegram timing for radio telegrams

	\sa mem_writeFlashNoErase, mem_writeFlash, mem_readFlash, mem_getDataAddr, mem_getPrgSize, \ref flash_arch	
	**************************************************************************************************************************/		
	RETURN_TYPE mem_writeFlash(uint8 xdata *pu8SrcAddr,uint16 u16DstAddr, uint16 u16NumBytes);


	/************************************************************************************************************************//*!
	Takes the <em>u16NumBytes</em> bytes from the XDATA address pointing to by <em>pu8SrcAddr</em>  
	and copies them to the flash memory. The FLASH page is not erased before writing to the FLASH. The application must ensure that 
    the page is clear (1 page is 256 byte).
	
	\param[in]  	*pu8SrcAddr		Pointer to the bytes source, (only XDATA allowed) 
	\param[in]  	u16DstAddr		Destination memory address, PRG_AREA: 0x0000 - 0x7F00
	\param[in]  	u16NumBytes		Number of bytes to copy	(1..2048 because this is the max XDATA size)
	
	\return			ADDR_OUT_OF_MEM 	If the u16DstAddr + u16NumBytes is out of FLASH memory range
	\return			FLASH_HW_ERROR	    If there was an error during writing operation
	\return			OK                  if the process was succesfull
							   	

	\note
	<b>You can use this function only if you are absolutly sure the location you are writing to was never written before (after an erase)! Otherwise
	it may happen that flash will be corrupted!</b>

	\note When receiving or sending an UART or radio telegram and simultaneously writing in FLASH memory the effect could be:
	- corrupt UART telegram receiving
	- corrupt radio telegram receiving
	- wrong sub telegram timing for radio telegrams
	
	\note
	When writing to FLASH the bootloader is called. The *pu8SrcAddr must reside in the XDATA!

	\note
	Be sure XTAL is running when calling this function. When running with CRCO the duration of the flash write can take longer.
	Therfore be sure to keep a shadow register for the area you will to write in the XDATA. 

	\note
	Keep in mind that when writing to the FLASH all the interrupts are disabled. Therfore it is not possible to 
	receive telegrams from radio or uart. 

	\note
	Note when writing to FLASH let's say 256 bytes it takes more than 1 ms time. The system schedule has 1ms
	takt but the interrupts are switched off during flash write and with them also the schedule timer. 
	Therfore all the SW timer and also the system timer will be unprecise.  This has also influence on subtelegram
	timing!

	\note
	Avoid writing too often to FLASH. The FLASH memories has a limited lifecycle and accesing them 
	needs lot of system resources (critical from power or timing point of view)

	\note
	When writing to FLASH_PRG be sure to store data beyond the program area. You can get the size of your
	program in number of flash pages by calling #mem_getDataAddr, #mem_getPrgSize macro
	
    \note 
    The writing routine does not verify the bytes written in the flash. In a critical application the application 
    should compare the data written to the flash with the data residing in RAM.

	
	\sa mem_writeFlashNoErase, mem_writeFlash, mem_readFlash, mem_getDataAddr, mem_getPrgSize, \ref flash_arch	
	**************************************************************************************************************************/		
	RETURN_TYPE mem_writeFlashNoErase(uint8 xdata *pu8SrcAddr,uint16 u16DstAddr, uint16 u16NumBytes);

	/************************************************************************************************************************//*!
	Takes the <em>u8NumBytes</em> bytes from the address pointing to by <em>pu8SrcAddr</em>    
	and copies them to the RAM0 (PRAM) memory. 

	
	\param[in]  	*pu8SrcAddr		Pointer to the bytes source addresses.
	\param[in]  	u8DstAddr		Destination memory address (0x00 - 0x1F).
	\param[in]  	u6NumBytes		Number of bytes to copy	(1..32)
	
	\return			ADDR_OUT_OF_MEM If the address is out of memory range
	\return			OK If the process was succesfull
							   	
	
	\sa mem_readRAM0
	
	**************************************************************************************************************************/		
	RETURN_TYPE mem_writeRAM0(uint8 *pu8SrcAddr,uint8 u8DstAddr, uint8 u8NumBytes);
		
	/************************************************************************************************************************//*!
	Reads values from a FLASH memory and places them to an XDATA buffer defined by <b>u8DstAddr</b>.
	\n<b>Note:</b> 
	The destination buffer must be located in XDATA.
	
	\param[out]  	*pu8DstAddr		Pointer to the byte where the information is to be stored
	\param[in]  	u16SrcAddr		Source memory address PRG_AREA: 0x0000 - 0x7EFF
	\param[in]  	u8NumBytes		Number of bytes to read
	\return			OK
	\return			ADDR_OUT_OF_MEM 	If the u16SrcAddr + u16NumBytes is out of FLASH memory range
  		

	\note
	It is not possible to read the CFG area with this function. To read it use the #CFG_AREA union.

	\note
	You can't use this function in the callback functions. To read from flash in a callback use CBYTE or CWORD macro from Keil

	\sa mem_writeFlash, mem_readFlash, mem_getDataAddr, mem_getPrgSize, \ref flash_arch
	
	**************************************************************************************************************************/		
	RETURN_TYPE mem_readFlash(uint8 xdata *pu8DstAddr,uint16 u16SrcAddr, uint16 u16NumBytes);

	/************************************************************************************************************************//*!
	Reads values from a RAM0 (PRAM) memory and places them to a buffer defined by <b>u16DstAddr</b>.
	
	\param[out]  	*pu8DstAddr		Pointer to the byte where the information is to be stored
	\param[in]  	u8SrcAddr		Source memory address (0x00 - 0x1F)
	\param[in]  	u6NumBytes		Number of bytes to copy	(1..32)

	\return			ADDR_OUT_OF_MEM If the address is out of memory range
	\return			OK If the process was succesfull
			

	\note
	After power-up or if the VDD drops below VOFF the RAM0 contents is undefined!
	
	\sa mem_writeRAM0
	
	**************************************************************************************************************************/		
	RETURN_TYPE mem_readRAM0(uint8 *pu8DstAddr,uint8 u8SrcAddr, uint8 u8NumBytes);

	/************************************************************************************************************************//*!
	Performs a built in self test (BIST) on the flash program area. The test calculates a CRC value on the program using the program
	size byte in the CFG_AREA. The result is	compared with the CRC stored in the last byte of the last page of the program = PrgArea[u8PrgSize*256-1]. 
  With the help of this BIST the corruption of the flash can be detected.  
	
	\param  	-	
	\return 	OK				BIST was succesfull \n
	\return 	BIST_FAILED		BIST has failed
									   	
	
	\note
	The CRC is calculated only on the flash pages where the program is stored not on the data following the program flash pages.
	The information how big is the program is stored in the CFG_AREA u8PrgSize variable and can be read out using the macro #mem_getPrgSize.
	
  The BIST CRC is stored in the last page and last byte of the program.  To calculate the BIST for your program you must yous the 
  EOPX postbuild tool. See DolphinStudio manual for more information. 
	
	\sa \ref flash_arch
	**************************************************************************************************************************/		
	RETURN_TYPE	mem_flashBist();

 	/************************************************************************************************************************//*!
	This macro returns the address in the FLASH program area from which the application can store it's data. It is the first free page in 
	the FLASH after the program pages.

	\param[out]  	u16Addr	 Address of the first free FLASH page	
	\return			-
							   	
	
	\sa mem_writeFlash, mem_getPrgSize
	
	**************************************************************************************************************************/		
	#define mem_getDataAddr(u16Addr) *(((uint8*)&u16Addr)) = *((uint8 volatile xdata *) CFG_ADDR); *(((uint8*)&u16Addr + 1)) = 0x00;
	
 	/************************************************************************************************************************//*!
	This macro returns the program size stored in the flash in FLASH pages 

	\param[out]  	u8PrgSize	Program area size in FLASH pages
	\return			-
							   	
	
	\sa mem_writeFlash, mem_getDataAddr
	
	**************************************************************************************************************************/		
	#define mem_getPrgSize(u8PrgSize) *(((uint8*)&u8PrgSize)) = *((uint8 volatile xdata *) CFG_ADDR);


 	/************************************************************************************************************************//*!
	This macro performs a backup of one FLASH page (256 bytes) 

	\param[in]  	u16SrcAddr	Source memory address of data to backup in PRG_AREA: 0x0000 - 0x7F00
	\param[in]		u16DstAddr	Destination memory address of the backup area in PRG_DATA: 0x0000-0x7F00
	\param[in]		pu8Buffer	Pointer to a buffer of 256 byte xdata memory for temporary storing of the FLASH page to backup
	\return			ADDR_OUT_OF_MEM 	If the u16DstAddr + 256 is out of FLASH memory range
	\return			FLASH_HW_ERROR	    If there was an error during writing
	\return			OK                  if the process was succesfull

	\note
	Be sure not to use adresses in your program memory, use #mem_getDataAddr to get the next free page after your program

	\note
	Do not use CFG area

	<b>Example:</b> \n
	 \code
		#define ORIGINAL_DATA 0x7000
		#define BACKUP_DATA	  0x7200
		uint8 xdata buf[256] _at_ 0x600;
		mem_backupFlashPage(ORIGINAL_DATA, BACKUP_DATA, &buf);
	 \endcode

	
	\sa mem_restoreFlashPage, mem_checkBackup, mem_writeFlash, mem_readFlash, mem_getDataAddr
	
	**************************************************************************************************************************/		
	#define mem_backupFlashPage(u16SrcAddr, u16DstAddr, pu8Buffer) \
	   mem_readFlash(pu8Buffer,u16SrcAddr, 256); mem_writeFlash(pu8Buffer, u16DstAddr, 256)

 	/************************************************************************************************************************//*!
	This macro performs a restore of one FLASH page (256 bytes) 

	\param[in]  	u16SrcAddr	Source memory address of the backup area in PRG_DATA: 0x0000-0x7F00
	\param[in]		u16DstAddr	Destination memory address of your original data in PRG_AREA: 0x0000 - 0x7F00
	\param[out]		pu8Buffer	Pointer to a buffer of 256 byte xdata memory for temporary storing of the FLASH page to restore
	\return			ADDR_OUT_OF_MEM 	If the u16DstAddr + 256 is out of FLASH memory range
	\return			FLASH_HW_ERROR	   If there was an error during writing
	\return			OK                 if the process was succesfull

	\note
	Be sure not to use adresses in your program memory, use #mem_getDataAddr to get the next free page after your program

	\note
	Do not use CFG area

	<b>Example:</b> \n
	 \code
		#define ORIGINAL_DATA 0x7000
		#define BACKUP_DATA	  0x7200
		uint8 xdata buf[256] _at_ 0x600;
		mem_restoreFlashPage(BACKUP_DATA, RESTORE_DATA, &buf);
	 \endcode

	
	\sa mem_backupFlashPage, mem_checkBackup, mem_writeFlash, mem_readFlash, mem_getDataAddr
	
	**************************************************************************************************************************/		
	#define mem_restoreFlashPage(u16SrcAddr, u16DstAddr, pu8Buffer) mem_backupFlashPage(u16SrcAddr, u16DstAddr, pu8Buffer)

 	/************************************************************************************************************************//*!
	This macro checks the contents of two FLASH page (256 bytes) for equal data

	\param[in]  	u16SrcAddr	Source memory address of the original data in PRG_DATA: 0x0000-0x7F00
	\param[in]		u16DstAddr	Destination memory address of backuped data in PRG_AREA: 0x0000 - 0x7F00
	\return			0		Both FLASH pages contain the same data
	\return			!= 0	The FLASH pages are different

	<b>Example:</b> \n
	 \code
		#define ORIGINAL_DATA 0x7000
		#define BACKUP_DATA	  0x7200
		uint8 xdata buf[256] _at_ 0x600;
		if (mem_checkBackup(ORIGINAL_DATA, BACKUP_DATA) != 0)
			mem_restoreFlashPage(BACKUP_DATA, RESTORE_DATA, &buf);
	 \endcode

	
	\sa mem_backupFlashPage, mem_restoreFlashPage, mem_writeFlash, mem_readFlash, mem_getDataAddr
	
	**************************************************************************************************************************/		
	#define mem_checkBackup(u16SrcAddr, u16DstAddr) memcmp((uint8 code *)(u16SrcAddr), (uint8 code *)(u16DstAddr), 256)

//! @}



/*********************************************************************************************/
/************************************ PWR MODULE *********************************************/
/*********************************************************************************************/
/*!
	\addtogroup pwr_grp  pwr
	The PWR module is responsible for the power block control of the DOLPHIN. Using the PWR module several 
	ultra low power timers can be activated/deactivated. These timers are used to control the sleep modes of the DOLPHIN.
	The PWR module has the responsibility to:
	- control low power timer
	- enabling/disabling XTAL switching
	- fetch and control reset sources 

	Be sure to read the chapter \ref power_page.	
	\ingroup ESSL
*/ 

//! @addtogroup pwr_struct_grp Power structures and constants
//! Structures that are used in POWER module
//! \ingroup pwr_grp 
//! @{

	
	//! Time unit 'second' measured in microseconds
	#define SEC   1000000
	//! Time unit 'millisecond' measured in microseconds
	#define MSEC  1000			
	//! Time unit 'microsecond' measured in microseconds
	#define USEC  1	

	//! Shortterm calibration constant - it is used to avoid using floating point value for shortterm calibration. 
	#define SHORT_TERM_CALIB_CONST	2048
	//! Watchdog calibration constant - it is used to avoid using floating point value for watchdog calibration. 
	#define WATCHDOG_CALIB_CONST	2048

	//! Low power timers
	typedef enum
	{
	 	//! \ref WatchdogTimer
		WATCHDOG_TIMER = 0,
		//! \ref FlywheelTimer
		FLYWHEEL_TIMER,			
		//! \ref ShortTermTimer
		SHORT_TERM_TIMER	
				
	} SLEEP_TIMER_TYPE;

	//! Low power timers clock period (includes postscaler) used for #CONV_COUNTER_TO_TIME and #CONV_TIME_TO_COUNTER macros 
	typedef enum
	{
	 	//! WDT timer counter incremented every 10ms. For more information see #SLEEP_TIMER_TYPE
		WATCHDOG_CLK   = (10000 * USEC),
	 	//! Flywheel timer counter incremented every ~1 ms (1/1024s). For more information see #SLEEP_TIMER_TYPE 	
		FLYWHEEL_CLK   = (976 * USEC),			        
	 	//! Short term timer counter incremented every 10 us. For more information see #SLEEP_TIMER_TYPE 	
		SHORT_TERM_CLK = (10 * USEC)
					
	} SLEEP_TIMER_CLK_TYPE;

	//! Short term timer modes
   	typedef enum
	{
		//! Continuous mode: the timer counter restarts when reaching the period value.
		SHORT_TERM_CONT = 0,
		//! One shoot mode: the timer counter stops when reaching the period value. 
		SHORT_TERM_ONE, 

 	} SHORT_TERM_TYPE;

	//! Reset causes
	typedef enum
	{
		//! \ref PowerOnReset queried using #pwr_getSystemReset function
		VDD_RESET = 0,
	 	//! \ref PinReset (is set also after downloading the program with the programmer)
		PIN_RESET,
		//! \ref WatchdogReset
		WATCHDOG_RESET,
		//! \ref FlywheelReset
		FLYWHEEL_RESET,
		//! Parity error
		BIST_RESET,
		//! HW Parity error in the Internal or External Memory
		PARITY_RESET,
		//! A memory request from the CPU core does not correspond to any valid memory location. This error may be caused by a S/W malfunction.
		ADDRESS_RESET,
		//! Wake-up pin 0 activated
		WAKE_PIN0_RESET,
		//! Wake-up pin 1 activated
		WAKE_PIN1_RESET,
		//! Unknown reset source - reset reason couldn't be detected
		NO_RESET_DETECTED

	} RESET_TYPE;

	//! Make sure to read the chapter \ref wake_events
	typedef enum
	{
		//! Wake-up pin 0 was activated
		PIN_WAKE0_WAKE = 0,
		//! Wake-up pin 1 was activated
		PIN_WAKE1_WAKE,
		//! Short-term timer counter reach period
		SHORT_TERM_WAKE,
		//! Radio telegram received
		RX_RADIO_TEL_WAKE,
		//! Radio telegram transmission finished
		TX_RADIO_TEL_WAKE,
		//! External pin activated
		PIN_EXT_WAKE,
		//! Timer0 scheduler interrupt
		TIMER0_WAKE,
		//! VDDFAIL interrupt - VDD crossed the VON threshold interrupt
		VDD_FAIL,
		//! Wake-up source is unknown
		NOT_VALID_WAKEUP,
		//! Wake up by radio RX error
		RX_RADIO_ERROR_WAKE
	} WAKE_TYPE;

	//! Configuration flags for external events that wake the CPU from sleep. Make sure to read \ref wake_events
	typedef enum
	{
		//! Don't use any of the listed wake events
		NO_WAKE_FLAG = 0x0,
		//! The wake0 pin event wakes the CPU from standby
		WAKE0_PIN_CFG_WAKE_FLAG	= 0x1,
		//! The wake1 pin event wakes the CPU from standby
		WAKE1_PIN_CFG_WAKE_FLAG	= 0x2,
		//! The scheduler (timer0) event wakes the CPU from standby
		TIMER0_WAKE_FLAG = 0x4
	} WAKE_CFG_TYPE;

	//! Divider type of XTAL stable delay
	typedef enum
	{
		//! 2.50 ms 
		DEFAULT_DELAY = 0x3,
		//! 0.64
		SECOND_SUBTEL_DELAY = 0x5
	} XTAL_DIVIDER_TYPE;

//! @}


//! @addtogroup pwr_fn_grp Power functions
//! \copydetails pwr_grp
//! \ingroup pwr_grp
//! @{

	/************************************************************************************************************************//*!
	Reinitialises the watchdog (WDT) timer counter . 

	\param  	-	
	\return 	OK				Function correctly executed. 	
									   	

	\note
 	The function should be called more frequently than 1/WDTperiod to prevent a WDT reset.
	A WDT reset wake-ups the CPU from any low power mode also. 	
	 
	\note
	The CLR_WDT sets the watchdog counter back. This operation takes at least ca. 30ms. The function returns immediately, but the 
	counter will be actualised only after ca. 30 ms. Therefore if calling the SET_WDT and CLR_WDT functions in a row, CLR_WDT will have no effect.

	\sa   SET_WDT, pwr_resetSleepTimer, \ref watchdog_page	
	**************************************************************************************************************************/		
	#define CLR_WDT() {pwr_resetSleepTimer(WATCHDOG_TIMER);}

	

	/************************************************************************************************************************//*!
	Sets the watchdog timer period. 
		
	\param[in]  	WDTPeriod		Watchdog timer period in the timer counter units	
	\return 		OK				Function correctly executed. 	
									   	

 	\note
	 When the WDT timer reaches the period the CPU, if sleeping, wakes-up. 
	 In any  other case the program execution jumps to the reset vector - i.e. the program will start from the beggining.

	\note
	If no period is set, the WDT period register is 0xFFFFFF. This equals 46.6 hours

	\note
	The SET_WDT sets the watchdog counter. This operation takes at least ca. 30ms. The function returns immediately, but the 
	counter will be actualised only after ca. 30ms.Therefore it is not allowed to call the SET_WDT and CLR_WDT functions in a row.
	Also make sure the watchdog periode is more than 30ms. 
	Example: 

	\code
	CFG_AREA xdata cfg  _at_ CFG_ADDR; //address for reading cfg area
	
	//calculate timer periode for 10 seconds and apply calibration factor
	u32WatchdogPeriode = (uint32)(CONV_TIME_TO_COUNTER(10, SEC, WATCHDOG_CLK) * cfg.val.u16CalibWatchdog)/WATCHDOG_CALIB_CONST;	
	SET_WDT(u32WatchdogCycle);
	\endcode	

 	\sa   pwr_setSleepTimer, CLR_WDT, \ref watchdog_page
	**************************************************************************************************************************/		
	#define SET_WDT(WDTPeriod) pwr_setSleepTimer(WATCHDOG_TIMER,WDTPeriod,0)
	
  	/************************************************************************************************************************//*!
	Converts the value of a low power timer counter to time units. 
	
	\param[in]     counter			Timer counter value 	
	\param[in]     timeUnit		    Time unit of the result. See \ref SEC, \ref MSEC, \ref USEC
	\param[in]     timerClkPeriod	Duration of the low power timer counter to increment. See \ref SLEEP_TIMER_CLK_TYPE
	
	\return		Time expressed in timeUnit units					
									   	

	<b>Example 1:</b> \n
	 Getting the time elapsed in ms since FLYWHEEL timer initialisation
	 \code
	 pwr_getSleepTimerCounter(FLYWHEEL_TIMER, &counter);
	 time = CONV_COUNTER_TO_TIME(counter,MSEC,FLYWHEEL_CLK);
	 \endcode
	
	\note
	 This function can be useful combined with \ref pwr_getSleepTimerCounter 
	 and \ref pwr_getSleepTimerPeriod, since these functions return the timer counter and timer counter period in timer tick units.
	 
	\note									 	
	According to the timer clock period (\ref SLEEP_TIMER_CLK_TYPE) select an appropiate time unit. \n

	\note The converted timer units are <b>NOT CALIBRATED</b>. In order to get calibrate timer units you have to adjust the value with the calibration constant
	from the CFG_AREA. To see how to do this read the calibration section in the \ref power_page.


	\note									 	
	The result is always a natural number. The decimal part is truncated.
	Example: -if the result of the division is 2,01 you get actually 2.
	   		 -if the result of the division is 2,99 you get actually 2.

 	 \sa  CONV_TIME_TO_COUNTER, pwr_getSleepTimerCounter, pwr_getSleepTimerPeriod, \ref power_page
	**************************************************************************************************************************/		
	#define CONV_COUNTER_TO_TIME(counter,timeUnit,timerClkPeriod) ((uint32)counter * (uint32)timerClkPeriod) / timeUnit

 	/************************************************************************************************************************//*!
	Converts a time to a low power timer clock time units. 
	
	\param[in]     time			    Time to convert (no units)	
	\param[in]     timeUnit		    Time units. 	
	\param[in]     timerClkPeriod	Duration of the low power timer counter to increment.
	
	\return 	Time expressed in timeUnit 					
									   	
	 
    <b>Example 1:</b> \n
    Setting a flywheel timer period of 2 seconds
    \code                                              
    // Use the FW calibration in FLASH  (cfg.val.f32CalibFlywheel) to correct the value to write in  pwr_setSleepTimer() in order to obtain FLYWHEEL_PERIOD
    u32FlywheelPeriod = (uint32)(CONV_TIME_TO_COUNTER(3, SEC, FLYWHEEL_CLK)* cfg.val.f32CalibFlywheel);
    pwr_setSleepTimer(FLYWHEEL_TIMER, u32FlywheelPeriod ,0);
    \endcode	

	\note
	This function can be useful to calculate the input parameter of the #pwr_setSleepTimer.
	 
	\note
	As timeUnit use one of the constants \ref SEC, \ref MSEC, \ref USEC. \n
	As timerClkPeriod use one of the period values defined in \ref SLEEP_TIMER_CLK_TYPE \n

	\note
	Flywheel timer counter is incremented every 976,5625 usec and macro works only with integer values. The recommended FLYWHEEL_CLK constant is 976 - 
	compared to 976,5625 this is 576 ppm difference.
	For exacter results please use your own conversation routine using float operations.
	 
	\note 
	The converted counter units are <b>NOT CALIBRATED</b>. In order to calibrate the counter you have to adjust the value with the calibration constant
	from the CFG_AREA. To know how to do this read the calibration section in the \ref power_page.

	\note
	Absolute maximum values of the input parameter time, which depends from input parameter time_unit and the type of the timer:\n
	      
    <table cellspacing="0" width="40%" class="Design1" align="center"  cellpadding="2">  
    <tr><th>Timer type</th>        <th>time unit</th>   <th>max. time value</th>
    <tr><td>WATCHDOG_TIMER</td>    <td>USEC</td>        <td>makes no sense </td> 	</tr>
	<tr><td>WATCHDOG_TIMER</td>    <td>MSEC</td>        <td>100 663 290</td>	</tr>
	<tr><td>WATCHDOG_TIMER</td>    <td>SEC</td> 		<td>100 663</td>        </tr>
	<tr><td>FLYWHEEL_TIMER</td>    <td>USEC</td>        <td>makes no sense</td>	</tr>
	<tr><td>FLYWHEEL_TIMER</td>    <td>MSEC</td>        <td>16 777 215</td>		</tr>
	<tr><td>FLYWHEEL_TIMER</td>    <td>SEC</td> 		<td>16 777</td>         </tr>
	<tr><td>SHORT_TERM_TIMER</td>  <td>USEC</td>        <td>39 321</td>	        </tr>
	<tr><td>SHORT_TERM_TIMER</td>  <td>MSEC</td>        <td>39</td>		        </tr>
	<tr><td>SHORT_TERM_TIMER</td>  <td>SEC</td> 		<td>not possible</td>   </tr>
    </table>
	Consider, that the result has to be converted to a calibrated value for exact timing. This final value may not exceed 24 bits for watchdog and flywheel timer and
	16 bit for shortterm timer.

 	\sa  CONV_COUNTER_TO_TIME, SET_WDT, pwr_setSleepTimer, \ref power_page
	
	**************************************************************************************************************************/		
	#define CONV_TIME_TO_COUNTER(time,timeUnit,timerClkPeriod)           \
	( 															         \
		(((uint32)time > 0xffff) || ((uint32)timeUnit > 0xffff)) ?       \
			/* Overflow in 32 bit mathematics possible */                \
			(															 \
			((uint32)time > (uint32)timeUnit) ?                          \
	 			(((uint32)time / timerClkPeriod)  * (uint32)timeUnit)	 \
			:                                                            \
	 			(((uint32)timeUnit / timerClkPeriod) * (uint32)time)	 \
			)	                                                         \
		:                                                                \
			/* No overflow in 32 bit mathematics possible */             \
	 		(((uint32)time * (uint32)timeUnit) / timerClkPeriod)	     \
	)																     \


	/************************************************************************************************************************//*!
	Stops the indicated low power timer.  
	\param[in]  	timer 			Low power timer to stop. Only \ref FLYWHEEL_TIMER and \ref SHORT_TERM_TIMER are allowed
	
	\return 	OK				Function correctly executed. 	
	\return 	NOT_VALID_PARAM	Wrong input parameter. 	
									   	

	 <b>Example 1:</b> \n
	 The short term timer is stopped here.
	 \code
	 //This saves energy when not using this timer.
	 pwr_disableSleepTimer(SHORT_TERM_TIMER);               
	 \endcode
	
	 <b>Example 2:</b> \n
	 It is NOT possible to stop the watchdog timer. The function returns an error if trying to do so
	 \code
	 return = pwr_disableSleepTimer(WATCHDOG_TIMER);  
	 if(return == OK);
	 {             
	 	//The code here will not be entered
	 }
	 \endcode

	 \note
	This function is allowed to be used in an interrupt callback function ONLY if it is ensured that it is not used at the same time from the main program!

	\sa   pwr_setSleepTimer, pwr_timerSleep, pwr_resetSleepTimer, \ref power_page	
	**************************************************************************************************************************/		
	RETURN_TYPE pwr_disableSleepTimer(SLEEP_TIMER_TYPE timer);

	/************************************************************************************************************************//*!
	Starts the 16MHz crystal oscillator (XTAL). It takes 1.3ms until the crystal oscillator is stable and prepared 	to be selected 
	as the system clock. While the crystal oscillator startup the system clock is still supplied from the RC oscillator which is 
	<b> min:11.7 typ:16 max:22.8Mhz </b> . While running with the  CRCO all the sw modules can be used except the RADIO module. 
	The timings of functions are unprecise. To switch from CRCO to XTAL call the pwr_selectXTAL. 

	\param  	u8Divider	Divider for XTAL delay calculation. Use always DEFAULT_DELAY.
	\return 	-

	\note
	If running from RC oscillator it is not possible to:
	- use the radio block for radio communication
	- all the timings (UART, SPI, system timer) will be not precise

	\note
	This function also starts the ShortTerm timer in order to measure the 1.3ms. 
	This short term timer is switched off in pwr_selectXTAL function!

	\note
	This function is allowed to be used in an interrupt callback function ONLY if it is ensured that it is not used at the same time from the main program!

	\sa  pwr_selectXTAL
	**************************************************************************************************************************/		
	void pwr_enableXTAL(XTAL_DIVIDER_TYPE u8Divider);

	/************************************************************************************************************************//*!
	Waits until the 16MHz crystal oscillator is stable (XTAL) and then selects it. While waiting the CPU goes to standby mode to save energy.
	After the time has passed and XTAL selected the ShortTerm timer is deactivated.

	
	\param  	-
	\return 	-
									   	
	\note 
	Use this function together with pwr_enableXTAL. 

	\note
	This function is allowed to be used in an interrupt callback function ONLY if it is ensured that it is not used at the same time from the main program!

	\sa  pwr_enableXTAL
	**************************************************************************************************************************/		
	void pwr_selectXTAL();


 	/************************************************************************************************************************//*!
	Returns the previously set flywheel tap value.  
	
	\param[out]  	*pu32tapValue 	Value set in the FW tap register
	\return 		OK				Function correctly executed. 	
	
	\return 		OK				Function correctly executed. 	
	\return 		NOT_VALID_PARAM	Wrong input parameter. 	
									   	

	 <b>Example 1:</b> \n
	\code
	pwr_setFlywheelTap(50);
	pwr_getFlywheelTap(&tapValue); //tapValue must be 50 
	\endcode

    \note
    When the flywheel counter reaches the tap value the CPU wakes-up. 
    The flywheel counter is not modified by this event, and it counts up to the FW period.
    The tap is useful to wake up the CPU between FW period intervals.      
	
	\sa   pwr_setFlywheelTap, pwr_setSleepTimer, \ref power_page
	
	**************************************************************************************************************************/		
	RETURN_TYPE pwr_getFlywheelTap(uint32 *pu32tapValue);

								 
 	/************************************************************************************************************************//*!
	Obtains the timer counter of the indicated low power timer.  
	
	\param[in]  	timer 				Low power timer to get the information from
	\param[out]  	*pu32timerCounter	Timer counter value.
	
	\return 		OK					Function correctly executed. 	
	\return 		NOT_VALID_PARAM		Wrong input parameter. 	
									   	

	 <b>Example 1:</b> \n
	 Get the counter of the watchdog timer.
	 \code
	 pwr_getSleepTimerCounter(WATCHDOG_TIMER, &timerCount);             
	 time = CONV_COUNTER_TO_TIME(timerCount,MSEC,WATCHDOG_CLK);             
	 \endcode
	
	\note
	The short term timer and the watchdog counters decrement while counting. 
	The flywheel timer counter is incremented while counting. 

    \note
    The short-term and flywheel timers are active (their counter changes) from the moment the function #pwr_setSleepTimer is called. 
    The watchdog timer is always active and cannot be deactivated

	\note The counter units are <b>NOT CALIBRATED</b>. In order to calibrate the counter value you have to adjust the constant with the calibration constant
	from the CFG_AREA. To know how to do this read the calibration section in the \ref power_page.

			 
 	\sa   pwr_resetSleepTimer, pwr_setSleepTimer, pwr_getSleepTimerPeriod, pwr_getSleepTimerStatus, \ref power_page
	
	**************************************************************************************************************************/		
	RETURN_TYPE pwr_getSleepTimerCounter(SLEEP_TIMER_TYPE timer,uint32 *pu32timerCounter);

 	/************************************************************************************************************************//*!
	Indicates the period set in the corresponding low power timer 
	
	\param[in]  	timer	    			Low power timer to get the period from.		
	\param[out]  	*pu32timerPeriod	    Period value in timer counter units.		
	
	\return 		\ref OK					Function correctly executed. 	
	\return 		\ref NOT_VALID_PARAM	Timer not valid. 	
									   	

	 <b>Example 1:</b> \n
	 Getting the FW timer period in milliseconds. 	
	 \code
	 pwr_getSleepTimerPeriod(FLYWHEEL_TIMER,&timerPeriod); 
	 if(return == OK)
	 {
	 	time = CONV_COUNTER_TO_TIME(timerPeriod,MSEC,FLYWHEEL_CLK);
	 }
	 \endcode

	\note The timer period is <b>NOT CALIBRATED</b>. In order to calibrate the timer period units you have to adjust the value with the calibration constant
	from the CFG_AREA. To know how to do this read the calibration section in the \ref power_page.
	 
	 \sa   pwr_timerSleep, pwr_setSleepTimer, \ref power_page
	**************************************************************************************************************************/		
	RETURN_TYPE pwr_getSleepTimerPeriod(SLEEP_TIMER_TYPE timer, uint32 *pu32timerPeriod);

 	/************************************************************************************************************************//*!
	Indicates if the timer is active or not. 
	
	\param[in]  	timer	    		Low power timer whose state is to be read.		
	\param[out]  	*pu8timerStatus     \ref ON, the timer clock is active. \ref OFF, the timer is stopped 		
	
	\return 		OK					Function correctly executed. 	
	\return 		NOT_VALID_PARAM 	Timer not valid. 	
									   	

	 <b>Example 1:</b> \n
	 This function is useful to configure the flywheel just once in the program execution life. 
	 \code
	 return = pwr_getSleepTimerStatus(FLYWHEEL_TIMER, &timerStatus) ;				
	 if( (return == OK) && (timerStatus == OFF) )
	 {
	 	pwr_setSleepTimer(FLYWHEEL_TIMER, 10000,0);     // The FW timer starts running from this moment.  
		SET_WDT(100000);                                // The WDT period must be bigger than the FW period. 
                                                        // Otherwise WDT reset happens while sleeping
	 }
	
	 //Rest of the program here
	 do
	 {
		pwr_getSleepTimerStable(FLYWHEEL_TIMER, &u8Stable);
	 	// Additionally, the WDT counter must be cleared. Otherwise WDT reset happens. 
	 	CLR_WDT();                     	
	 }
	 while (u8Stable == FALSE); // Dependent of the hardware it can take up to 10 seconds till  flywheel is stable

	 // Go to sleep with the activated timers FW and WDT. No wake-up pin activated (0x00)
	 pwr_timerSleep(0x00,&value);   
	  			  
	 // When FW timer counter reaches the period the CPU restarts execution at the reset vector. 
	 // FW timer status \ref ON until a pwr_disableSleepTimer() call is made. 
	 \endcode
 	
 	\note 
	After setting a timer through \ref pwr_setSleepTimer, the function returns \ref ON. 
	Similarly, when stopping a timer using \ref pwr_disableSleepTimer, the function returns \ref OFF    

	\note 
	The tap value is <b>NOT CALIBRATED</b>. In order to calibrate the timer tap value you have to adjust the value with the calibration constant
	from the CFG_AREA. To know how to do this read the calibration section in the \ref power_page.

	\note
	This function is allowed to be used in an interrupt callback function ONLY if it is ensured that it is not used at the same time from the main program!
	
	\sa   pwr_setSleepTimer, pwr_disableSleepTimer, \ref power_page
	**************************************************************************************************************************/		
	RETURN_TYPE pwr_getSleepTimerStatus(SLEEP_TIMER_TYPE timer, uint8 *pu8timerStatus);

 	/************************************************************************************************************************//*!
	Indicates if the timer is stable and all data is captured. 
	
	\param[in]  	timer	    		Low power timer whose stability is to be read.		
	\param[out]  	*pu8timerStatus     \ref TRUE, the timer runs stable and all data is captured. \ref FALSE, the timer is not ready to use		
	
	\return 		OK					Function correctly executed. 	
	\return 		NOT_VALID_PARAM 	Timer not valid. 	
									   	

	\note
	This function is allowed to be used in an interrupt callback function ONLY if it is ensured that it is not used at the same time from the main program!
	
	\sa   pwr_setSleepTimer, pwr_disableSleepTimer, \ref power_page
	**************************************************************************************************************************/		
	RETURN_TYPE pwr_getSleepTimerStable(SLEEP_TIMER_TYPE timer, uint8 *pu8timerStable);

 	/************************************************************************************************************************//*!
	Reports the cause of the CPU reset. 
	
	\param[out]  	*pu8resetEvent	    	Event that cause the CPU to jump to reset vector. \ref RESET_TYPE		
	
	\return 		-
									   	

	 <b>Example 1:</b> \n
	 Depending on the reset event detected, perform an action.
	 \code
	 pwr_getSystemReset(&resetEvent);
	 switch (resetEvent)
	 {
	 	case VDD_RESET: break;          //Action when VDD drop/power-up detection.
		case WATCHDOG_RESET: break;     //Action for watchdog timer reset.
		case FLYWHEEL_RESET: break;     //Action for flywheel timer time-out.
		case PIN_RESET: break;          //Action for reset pin pressed.
	 }         
	 \endcode
	
	\note 
	 The function can be called as often as needed from any place of the application and returns always the last reset cause.
	 The function will only provide a correct reset cause after \ref pwr_enableXTAL was called once.

	 \sa pwr_selectXTAL, \ref power_page	  
	**************************************************************************************************************************/		
	void pwr_getSystemReset(RESET_TYPE *pu8resetEvent);


 	/************************************************************************************************************************//*!
	Returns the status of the VON threshold. 
	
	\param[out]  	*pu8VON	   Returns the threshold detector status. It equals 1 when VDD > VON, otherwise it is 0.
	\return 		-
									   	
	\note
	This function is allowed to be used in an interrupt callback function ONLY if it is ensured that it is not used at the same time from the main program!

	 
	**************************************************************************************************************************/		
	void pwr_getThresholdVON(uint8 *pu8VON);

 	/************************************************************************************************************************//*!
	Reinitialises the indicated low power timer counter to 0.  
	
	\param[in]  	timer	    		Low power timer counter to reinitialise.			
	\return 		OK					Function correctly executed. 	
	\return 		NOT_VALID_PARAM 	Timer not valid.
	\return			TIME_OUT			Only watchdog: Last reset of timer was still not captured, it was not necessary to reset timer.	
									   	

	 <b>Example 1:</b> \n
	The clear watchdog timer macro uses this function. 
	 \code
	 pwr_resetSleepTimer(WATCHDOG_TIMER);				
	 \endcode
	 
	\note 
	 If the corresponding timer clok was already activated, the timer counter starts counting
	 from its initial value. In case that the timer clock is not active when calling this function,
	 the counter will be reinitialised, but will not increment.

	\note
	This function is allowed to be used in an interrupt callback function ONLY if it is ensured that it is not used at the same time from the main program!

	\sa pwr_setSleepTimer, pwr_getSleepTimerCounter, \ref power_page
	**************************************************************************************************************************/		
	RETURN_TYPE pwr_resetSleepTimer(SLEEP_TIMER_TYPE timer);


 	/************************************************************************************************************************//*!												 
	Sets the period value of a low power timer and starts the timer.  
	
	\param[in]  	timer 			    One of the chip low power timers. \ref SLEEP_TIMER_TYPE
	\param[in] 		timerPeriod		    Timer period in timer counter units.
	\param[in]		shortTermMode	    Short term timer one shot or continuous mode. Only applies to \ref SHORT_TERM_TIMER
	
	\return 		OK				    Function correctly executed. 	
	\return 		NOT_VALID_PARAM	    Wrong input parameter. 	
									   	

	 <b>Example 1:</b> \n
	 This piece of code shows how to count 100 flywheel timer clock ticks (counter units)
	 \code
	 pwr_setSleepTimer(FLYWHEEL_TIMER, 100,0);       //100 is not a time. It indicates that the FW counter must count to 100       
	 \endcode

  \Note the flywheel timer uses as clock signal the external crystal WXTAL. This crystal must be activated for the FW to work.
  To activate the crystal configure the pins WXIDIO and WXODIO  as crystal pins. 
  To do that use Dolphin Studio, marking these two pins as WXTAL.
  Copy the generated initialization to your configuration file EO3000I_CFG.h 
	
	 <b>Example 2:</b> \n
	 If you want to set a timer period in time units, you can do like this.
	 \code
    u32FlywheelPeriod = (uint32)(CONV_TIME_TO_COUNTER(3, SEC, FLYWHEEL_CLK)* cfg.val.f32CalibFlywheel);
    // Setting the FW period cycle and starting the FW timer
    pwr_setSleepTimer(FLYWHEEL_TIMER, u32FlywheelPeriod ,0);
		 \endcode
	

	 <b>Example 3:</b> \n
	 After a short term timer sleep the radio configuration is lost. Here it is shown how to reenable the radio.
	 \code
     void main()
    {
        TEL_RADIO_TYPE  t1;
    	RETURN_TYPE     result;
		TEL_PARAM_TYPE pTel;
		pTel.p_tx.u8SubTelNum = 1;
		pTel.p_tx.u32DestinationId = 0;	
		uint8 u8Stable;
			
    	// Init configuration: I/Os, radio, interrupts... 
    	INIT_EO3000I

        // Initialising a radio RPS telegram to be sent. 
        t1.trps.u8Choice    = RADIO_CHOICE_RPS;
        t1.trps.u8Data      = 0x12;
        t1.trps.u32Id       = 0xFFFFFFFF;
        t1.trps.u8Status    = 0x00;
        t1.trps.u8Length    = RADIO_DEC_LENGTH_RPS;

        // Config the short-term timer for the sleep. The timer runs continously. Period = 0xFFFF * 10 us ~= 0.65 s
    	result = pwr_setSleepTimer(SHORT_TERM_TIMER,0xFFFF,SHORT_TERM_CONT);
    
    	while(1)
    	{
			//Wait till shortterm timer runs stable and all registers are captured
			do
			{
				pwr_getSleepTimerStable(SHORT_TERM_TIMER, &u8Stable);
			}
			while (u8Stable == FALSE);
    		//Go to sleep, without wake-up pins active (0x00). &value returns the wake-up event.
    		pwr_timerSleep(0x00,&value);
  
            // After short-term, the radio config is lost. It is needed to reconfigure the radio before sending
            // extern XTAL enable 
            pwr_enableXTAL();										
            // Loading the radio parameters in the HW radio module
    		radio_init_asm(1);										
            // System uses the external crystal (the radio HW only works with this clock source) 											
    		pwr_selectXTAL();
            
            // Sending 3 times 1 subtelegram. The telegram count is within pTel.
            radio_sendTelegram(&t1,&pTel);
            time_wait(10);
            radio_sendTelegram(&t1,&pTel);
            time_wait(10);
            radio_sendTelegram(&t1,&pTel);
            time_wait(2);
    	}
    }
	 \endcode


    <b>Example 4:</b> \n
	\code
    // Setting a sleep with the flywheel timer waking up the CPU.
    // The CPU wakes up every 200th count of the flywheel timer --> every 200ms.
    // Note: The CPU does not continue execution at the point it went to sleep. 
    // Every time that the CPU wakes up, it starts executing from the reset vector. The FW counter is restarted automatically
    	

    // Setting the WDT and FW only once during the life of the program.
    // Therefore, check if the FW is active. If not, set the timers.
    result = pwr_getSleepTimerStatus(FLYWHEEL_TIMER,&value);
	if( (result == OK) && (value == OFF) )
	{
	 	result = pwr_setSleepTimer(FLYWHEEL_TIMER,200,0);      // The third parameter in the function (0) is only needed when the short-term timer is used.
	 	result = pwr_setSleepTimer(WATCHDOG_TIMER,0xFFFF,0);   // Setting a big WDT period.
	}

	//Wait till flywheel timer runs stable and all registers are captured
	do
	{
		pwr_getSleepTimerStable(FLYWHEEL_TIMER, &u8Stable);
		CLR_WDT();
	}
	while (u8Stable == FALSE);

	//No wake through wake-up pins possible.
	pwr_timerSleep(0x00,&value);

    // After this line, no code would be executed. After a flywheel wake event the program starts execution from the reset vector.
	\endcode

    <b>Example 5:</b> \n
	\code
    // Setting a program to deep sleep: the watchdog timer wakes up the CPU.
    // The CPU wakes up every 200th count of the watchdog timer --> every 2 seconds.
    // Note: every time that the CPU wakes up, it starts executing from the reset vector.
    // The CPU does not continue execution at the point it went to sleep.  	

    // Setting the WDT only once during the life of the program.
    // Therefore, check if a watchdog timer is the cause of the reset.
    pwr_getSystemReset(&value);
	if( value != WATCHDOG_RESET )
	{
	 	result = pwr_setSleepTimer(WATCHDOG_TIMER,200,0);   
	}

	CLR_WDT();

	//No wake through wake-up pins possible.
	pwr_timerSleep(0x00,&value);

    // After this line, no code would be executed. After a watchdog timer wake event the program starts execution from the reset vector.
	\endcode
    	
	\note
	When the flywheel or the watchdog counter reaches the period the CPU starts execution from the program reset vector.
	
	\note
	In the case of short term timer, remember that the timer will be already running when pwr_setSleepTimer function is returned.
    Therfore, place the \ref pwr_setSleepTimer and \ref pwr_timerSleep as near as possible in your code. But do not forget to check
	if the timer runs stable and all registers are captured using \ref pwr_getSleepTimerStable before going to sleep!

	\note The timer period is <b>NOT CALIBRATED</b>. In order to calibrate the timer period you have to adjust the value with the calibration constants
	from the CFG_AREA. To know how to do this read the calibration section in the \ref power_page.

	\note
	The startup time of the watchdog timer is maximum 8 cycles. So the very first watchdog wakeup could be 80 ms longer as expected.

	\note
	When using shortterm sleep for waiting between sub telegrams be sure that the sleep time is longer than the sub telegram need to be sent. Otherwise when
	initializing radio parameters after wakeup too early the telegram could be breaked and the TX statemachine could be set into an errorness state.
		
  	\sa   pwr_disableSleepTimer, pwr_timerSleep, pwr_resetSleepTimer, pwr_getSleepTimerStable \ref power_page
	**************************************************************************************************************************/		
	RETURN_TYPE pwr_setSleepTimer(SLEEP_TIMER_TYPE timer,uint32 timerPeriod,SHORT_TERM_TYPE shortTermMode);

 	/************************************************************************************************************************//*!
	This function puts the CPU in standby mode. The CPU can wake up from standby mode using the wakepins or other interrupt sources. Be sure to read the  \ref power_page
	
	\param[in]  	configWakeUpEvents		Configures some events that can wake-up the CPU from standby. See \ref WAKE_CFG_TYPE 
	\param[out]  	*pu8wakeUpEvent			Indicates the cause of the wake up.	See \ref WAKE_TYPE 	
	\return 		-	
									   	

	\note 
	The WAKE_CFG_TYPE does not specifies all the wake events. Wake events like RX_RADIO_TEL_WAKE, TX_RADIO_TEL_WAKE etc. are triggered by interrupts

	\note
	If you don't want to be wake up by radio Rx interrupt switch off the RadioRx
	
	\note
	To avoid perodically waking up the CPU each ms, the scheduler interrupt is switched off in this function. This can be override using the TIMER0_WAKE_FLAG

	\note
	Be sure there is no ongoing Tx or Rx operation if you don't wan to woken up by RX_RADIO_TEL or TX_RADIO_TEL_WAKE when entering to standby.
	You can proove this using #radio_getOngoingRxTx function.

	\note
	This function is allowed to be used in an interrupt callback function ONLY if it is ensured that it is not used at the same time from the main program!

	\sa   pwr_setSleepTimer, pwr_timerSleep, \ref power_page
	**************************************************************************************************************************/		
	void pwr_standbySleep(WAKE_CFG_TYPE configWakeUpEvents,WAKE_TYPE *pu8wakeUpEvent);

 	/************************************************************************************************************************//*!
	This function puts the CPU in standby mode. The CPU can wake up from standby mode only by short term timer
	
	\param  	-
	\return 	-	
									   	

	\note
	This function is allowed to be used in an interrupt callback function ONLY if it is ensured that it is not used at the same time from the main program!

	\sa   pwr_setSleepTimer, pwr_timerSleep, \ref power_page
	**************************************************************************************************************************/		
	void pwr_standbyST();

 	/************************************************************************************************************************//*!
	Enters the CPU in low power mode with a low power timer controlling the wake-up."SET TO SLEEP". Be sure to read the  \ref power_page
	
	\param[in]  	wakeUpPinFlags	Configures WAKE pin events that can wake-up the CPU rom standby. See #WAKE_CFG_TYPE for more information.
	\param[out]  	*pu8wakeUpEvent	Indicates the cause of the wake up. See #WAKE_TYPE for more information.	
	\return 		-
									   	

	 <b>Example 1:</b> \n
	 Enter in sleep for 10ms with the short term timer.
	 \code
		CFG_AREA xdata cfg  _at_ CFG_ADDR; //address for reading cfg area
		
		void main ()
		{
			 WAKE_CFG_TYPE wakeUpPinFlags = WAKE0_PIN_CFG_WAKE_FLAG;
			 WAKE_TYPE wakeUpEvent;
			 uint16 u16value;
			 uint8  u8Stable;
		
			 INIT_EO3000I
		
			 //enter Short Term sleep between subtelegrams
	    	 u16value =  (CONV_TIME_TO_COUNTER(10, MSEC, SHORT_TERM_CLK) * unigcfg.val.u16CalibShortTerm) / SHORT_TERM_CALIB_CONST;
	 	  	 pwr_setSleepTimer(SHORT_TERM_TIMER, u16value, SHORT_TERM_ONE);
			
			 //Wait till shortterm timer runs stable and all registers are captured
		     do
			 {
			 	pwr_getSleepTimerStable(SHORT_TERM_TIMER, &u8Stable);
			 	CLR_WDT();
			 }
			 while (u8Stable == FALSE);
			 pwr_timerSleep(wakeUpPinFlags, &wakeUpEvent); 
			 switch (wakeUpEvent)
			 {
				 case PIN_WAKE0_WAKE:
				 {
				 	//Action for wake-up pin 0 event
				 }
				 case SHORT_TERM_WAKE:
				 {
				  	//Short term timeout
				 }         
			}
		}
	\endcode
	
	\note
	More than one low power timer can run at the same time. The first timer to time-out wakes the CPU.
	It must be remembered that the watchdog timer is ALWAYS running, and can cause unexpected CPU reset if its counter is not clear periodically.  
		
	\note
	A flywheel or watchdog timer time-out causes the CPU to wake up and start executing from the reset vector, 
	while a short term timer time-out will wake-up the CPU and continue execution.	In all three cases the radio settings are lost
	and must be reinitialised if needed.
	
	\note
	This function switches the radio receiving off and is deactivated after leaving this function. 
	
	\note
	In Deep Sleep, Flywheel Sleep, and Short Term Sleep mode DVDD is switched off! Please take care to avoid reverse supply via IOVDD!

	\note
	If the wake up event is not needed to know the second parameter can be NULL.

	\note
	Be sure to use #pwr_getSleepTimerStable before entering sleep mode to be sure that your timer runs stable and all settings are captured.

	\note
	When using shortterm sleep for waiting between sub telegrams be sure that the sleep time is longer than the sub telegram need to be sent. Otherwise when
	initializing radio parameters after wakeup too early the telegram could be breaked and the TX statemachine could be set into an errorness state.

	\note
	It is not possible to enter to DeepSleep if pwr_enableXTAL was but pwr_selectXTAL was not called. In pwr_selectXTAL the program enters to ShortTerm sleep 
	thus reconfiguring the DeepSleep target. pwr_selectXTAL restores these settings.
	
	\sa   pwr_setSleepTimer, pwr_disableSleepTimer, pwr_resetSleepTimer, pwr_getSystemReset, \ref power_page
	**************************************************************************************************************************/		
	void pwr_timerSleep(WAKE_CFG_TYPE wakeUpPinFlags,WAKE_TYPE *pu8wakeUpEvent);


 	/************************************************************************************************************************//*!
	Sets a flywheel timer counter value that wakes up the CPU. 
    
    \note  the flywheel counter is not affected.Intermediate Wakup after reach TAP.   
	
	\param[in]  	tapValue 		Value of the flywheel timer counter that wakes-up the CPU.
	\return 		-		
									   	

	<b>Example 1:</b> \n
	This piece of code shows how set 2 wake events within a flywheel period. 
	Through the usage of the pwr_setFlywheelTap the flywheel timer counter runs always without being rewritten.
    \note
	FWcounter has to a uint32 value otherwise the code can not work correct!!
	\code
	//Get and clear the reset events
	pwr_getSystemReset(&rstCode);
	
	result = pwr_getSleepTimerStatus(FLYWHEEL_TIMER,&value);
	if( (result == OK) && (value == OFF) )
	{
	    //Setting the flywheel timer period. This is only performed once in the execution cycle
	    result = pwr_setSleepTimer(FLYWHEEL_TIMER,600,0);
	}
	
	CLR_WDT();
	
	//Writing the tap. The next wake setting depends on the current FW counter
	pwr_getSleepTimerCounter(FLYWHEEL_TIMER,&FWcounter);
	
	if(FWcounter < 50)
	{
        //In this case the CPU was awoken because the counter reached the period value.

	    //Setting the next wake up when the FW counter will be 50
	    pwr_setFlywheelTap(50) ;
	}
	else if(FWcounter < 150)
	{
        //In this case the CPU was awoken because the counter reached the value 50.

	    //Setting the next wake up when the FW counter will be 150
	    pwr_setFlywheelTap(150) ;
	}
	else
	{
	    //In this case the CPU was awoken due to the tap = 150. The FW period value, 600, will be next the wake event.
	}
	
	//Wait till flywheel timer runs stable and all registers are captured
	do
	{
		pwr_getSleepTimerStable(FLYWHEEL_TIMER, &u8Stable);
		CLR_WDT();
	}
	while (u8Stable == FALSE);

	//Go to sleep. No wake through wake-up pins possible.
	pwr_timerSleep(0x00,&value);
	\endcode	
	
	\note
	A wake event will happen also when the FW counter reaches its period value. \n
	In that moment, the FW counter starts to count from 0 again.

	\note The tap value is <b>NOT CALIBRATED</b>. In order to calibrate the timer tap value you have to adjust the value with the calibration constant
	from the CFG_AREA. To know how to do this read the calibration section in the \ref power_page.
	
	\note
	This function is allowed to be used in an interrupt callback function ONLY if it is ensured that it is not used at the same time from the main program!

	\sa  pwr_getFlywheelTap, pwr_timerSleep, \ref power_page
	**************************************************************************************************************************/		
	void pwr_setFlywheelTap(uint32 tapValue);


	/************************************************************************************************************************//*!
    Sets function pointer for callback function in interrupt when VDD Failes, when VDD crosses threshold VON. 
    
    \param[in]  	*pu16FnPtr	  Pointer to the callback function which will be called when VDD crosses downwards the VON threshold, i.e. VDD<VON
    \return 		-

	\note
	In order to use this feature be sure to set the VDD Fail checkbox in I/O Configuration of DolphinStudio
    						   	
    \sa pwr_vddFailEnableCB, pwr_isrShortTerm
	**************************************************************************************************************************/		
	void pwr_vddFailInitCB(void code *pu16FnPtr); 

	/************************************************************************************************************************//*!
    Enables or disables callback in interrupt VDD Failes, when VDD crosses threshold VON
    
    \param[in]  	u8Enable	  			\ref TRUE, callback enabled, \ref FALSE, callback disabled
    \return 		-

	\note
	Do not stay in the callback function too long (not more than 100us because that takes too much time away from the schedule)
	
	\note
	The callback function will be called during an interrupt! Do not call other API functions than io_getDigital or io_getPort  in callback function.
	Do not switch the registerbank. Do not use overlaying and optimizing in callback function.
	You are allowed to:
	- allocate local variables 
	- you are allowed to read from flash using code[] 
	- you are allowed to change global variables of the code but before be sure to set them to volatile

	\note
	If you did not initialised callback function pointer and you enable callback function, then the interrupt occurs, but
	function cannot be called and interrupt returns without function. Program will not crash, but resources are used.

	\note
	In order to use this feature be sure to set the VDD Fail checkbox in I/O Configuration of DolphinStudio
    						   	
	\code
	//callback function
	void vdd_callback()
	{
		....	
	}
		
	void main()
	{				
		mainInit();		
		io_setDigital(ADIO_0,0);
		io_setDigital(ADIO_1,1);
		//init VDD Fail interrupt
		pwr_vddFailInitCB((void*)vdd_callback);
		pwr_vddFailEnableCB(TRUE);
		isr_genInit(TRUE);	
		while(1);	    
	}
	\endcode
  	
    					   	
    \sa pwr_vddFailInitCB, pwr_isrShortTerm
	**************************************************************************************************************************/		
	void pwr_vddFailEnableCB(uint8 u8Enable);

	/************************************************************************************************************************//*!
    Shortterm sleep mode intended to be used from callback functions. This function initialises the timer, enters to shorterm sleep mode
	exists from sleep mode after the period and stops the shortterm timer.
    
    \param[in]  	u16TimerPeriode	    Timer period in shortterm timer counter units.
    \return 		-

	\note
	Do not use this function from the main program. Use instead #pwr_setSleepTimer and #pwr_timerSleep. This function
	is intended to be used only from callback functions.
	
	\note
	After returning from the function the xtal has to be started again and the radio has to be initialised.
						   	
	\code
	//! This application enters to shortterm sleep mode for 200ms when the VDD failes - it crosses the VON threshold

	CFG_AREA xdata cfg  _at_ CFG_ADDR; //address for reading cfg area

	void vdd_callback()
	{
		uint16 u16value;
		uint32 i;
	
		io_setDigital(ADIO_2,1);
		//To save energy, go to short term sleep
        u16value =  (CONV_TIME_TO_COUNTER(200, MSEC, SHORT_TERM_CLK) * unigcfg.val.u16CalibShortTerm) / SHORT_TERM_CALIB_CONST;
 	    pwr_setSleepTimer(SHORT_TERM_TIMER, u16value, SHORT_TERM_ONE);

		io_setDigital(ADIO_0,1);
		for (i=0;i<65;i++);
		io_setDigital(ADIO_0,0);
	
		pwr_isrShortTerm(u16value);
	
		io_setDigital(ADIO_0,1);
		for (i=0;i<65;i++);
		io_setDigital(ADIO_0,0);
	
	 	// After short-term, the radio config is lost. It is needed to reconfigure the radio before sending
	    // extern XTAL enable 
	    pwr_enableXTAL();                                       
	    // Loading the radio parameters in the HW radio module
	    radio_init_asm(1);                                      
	    // System uses the external crystal (the radio HW only works with this clock source)                                            
	    pwr_selectXTAL();			
	}
	
	
	void main()
	{
		//Configuration in 
		mainInit();

		io_setDigital(ADIO_2,0);
		io_setDigital(ADIO_1,1);
		pwr_vddFailInitCB((void*)vdd_callback);
		pwr_vddFailEnableCB(TRUE);
		isr_genInit(TRUE);	
		while(1);
	}

	\endcode
  	
    					   	
    \sa pwr_vddFailInitCB, pwr_vddFailEnableCB
	**************************************************************************************************************************/		
	void pwr_isrShortTerm(uint16 timerPeriod);

//! @}




/*********************************************************************************************/
/************************************ RADIO MODULE *******************************************/
/*********************************************************************************************/
/*! 
	\addtogroup radio_grp radio
	Using the RADIO module the EnOcean protocol stack can be used. The radio module enables sending and receiving telegrams.\n
	The module has radio functions for application like TCMxxx which are always supplied with voltage. These functions needs the
	schedule in order to work correctly. The ULP functions are radio functions for energy autarkic devices like PTM or STM.
	For more information about the radio protocol stack read the \ref erp_page chapter.
	
	\ingroup ESSL
*/ 

//! @addtogroup radio_telegram_struct_grp Radio Telegram Structures
//! Structures that are used in RADIO module
//! \ingroup radio_grp 
//! @{

	//! Telegram choice codes applies to radio telegram only
	typedef enum
	{
	 	//! RPS telegram	
		RADIO_CHOICE_RPS = 0xF6,
		//! 1BS telegram
		RADIO_CHOICE_1BS = 0xD5,			
		//! 4BS telegram
		RADIO_CHOICE_4BS = 0xA5,			
		//! HRC telegram 			
		RADIO_CHOICE_HRC = 0xA3,			
		//! SYS telegram 			
		RADIO_CHOICE_SYS = 0xA4,			
		//! SYS_EX telegram 			
		RADIO_CHOICE_SYS_EX = 0xC5,
		//! Smart Ack Learn Reuqest telegram
		RADIO_CHOICE_SM_LRN_REQ = 0xC6,
		//! Smart Ack Learn Answer telegram
		RADIO_CHOICE_SM_LRN_ANS = 0xC7,
		//! Smart Ack Reclaim telegram
		RADIO_CHOICE_RECLAIM = 0xA7,
		//! Smart Request telegram
		RADIO_CHOICE_SIGNAL = 0xD0,
		//! Encapsulated addressable telegram
		RADIO_CHOICE_ADT = 0xA6,
		//! Variable Length Data
    	RADIO_CHOICE_VLD = 0xD2,
		//! Universal Teach In EEP based
		RADIO_CHOICE_UTE = 0xD4,
		//! Manufacturer Specific Communication
		RADIO_CHOICE_MSC = 0xD1,
		//! Chained data message
		RADIO_CHOICE_CDM = 0x40,
		//! Secure telegram	without choice encapsulation
		RADIO_CHOICE_SEC = 0x30,
		//! Secure telegram	with choice encapsulation
		RADIO_CHOICE_SEC_ENCAPS = 0x31,
		//! Non-secure telegram
		RADIO_CHOICE_NON_SEC = 0x32,
		//! Secure teach-in telegram
		RADIO_CHOICE_SEC_TI = 0x35,
		//! GenericProfiles Teach-in
		RADIO_CHOICE_GP_TI  = 0xB0,
		//! GenericProfiles Teach-in request
		RADIO_CHOICE_GP_TR = 0xB1,
		//! GenericProfiles Complete Data
		RADIO_CHOICE_GP_CD = 0xB2,
		//! GenericProfiles Selective Data
		RADIO_CHOICE_GP_SD = 0xB3,

	} CHOICE_TYPE;

	//! Length of the radio telegrams
	typedef enum
	{
		//! RPS decoded telegram length	in bytes
		RADIO_DEC_LENGTH_RPS =			 8,			 
		//! 1BS decoded telegram length	in bytes
		RADIO_DEC_LENGTH_1BS =			 8,			 
		//! 4BS decoded telegram length	in bytes
		RADIO_DEC_LENGTH_4BS =			 11,			 
		//! HRC decoded telegram length	in bytes
		RADIO_DEC_LENGTH_HRC =			 8,			 
		//! SYS decoded telegram length	in bytes
		RADIO_DEC_LENGTH_SYS =			 11,			 
		//! SYS_EX decoded telegram length	in bytes
		RADIO_DEC_LENGTH_SYS_EX =		 16,			 
		//! Smart ack learn request decoded telegram length in bytes
		RADIO_DEC_LENGTH_SM_LRN_REQ =        17,
		//! Smart ack learn answer telegram length in bytes
		RADIO_DEC_LENGTH_SM_LRN_ANS =        15,	 
		//! Smart ack reclaim telegram length in bytes
		RADIO_DEC_LENGTH_SM_REC =        8,
		//! Signal telegram length in bytes
		RADIO_DEC_LENGTH_SIGNAL =        8,	 
		//! U2S decoded telegram length in bytes
		RADIO_DEC_LENGTH_U2S =           6,
		//! T2S decoded telegram length iin bytes
		RADIO_DEC_LENGTH_T2S =           6,			 

	} RADIO_TEL_LENGTH;

	//! Status byte masks
	typedef enum
	{
		//! Bitmask for masking CRC vs CHECKSUM in status byte
		STATUS_CRC= 			 0x80,			 
		//! Bitmask for masking telegram generation bit in status byte
		STATUS_GENERATION =		 0x20,			 
		//! Bitmask for masking normal/unassigned bit in status byte
		STATUS_ASSIGNED =		 0x10,			 
		//! Bitmask for masking repeater / hop counter / path selection bits
		STATUS_REPEATER =		 0x0F,
	} STATUS_MASK;

	//! Radio init parameters
	typedef enum
	{
		//! Trigger chains download
		TRIGGER_CHAINS= 	 0x00,			 
		//! Configure all chains and trigger download
		CFG_ALL       =		 0x01,			 
		//! Configure analog0  chain and trigger download
		CFG_ANALOG0 =		 0x02,			 
	} RADIO_INIT_PARAM;

	//!Macros for choice processing
	#define GET_CHOICE(t)		((t).raw.bytes[0])
	//!Macro for status processing	- be sure that the u8Length of the telegram is set correctly
	#define GET_STATUS(t)  		(t.raw.bytes[t.raw.u8Length-2])
	//!Macro for id processing	- be sure tht the u8Length of the telegram is set correctly
	#define GET_ID(t)  		*((uint32*)&((t).raw.bytes[(t).raw.u8Length-6]))

	//!Destination broadcast ID, you can get the destination ID through TEL_PARAM_TYPE
	#define  BROADCAST_ID       0xFFFFFFFF

	
/************************************************************************************************************************//*!
\code
SYS EX DATA STRUCTURE 
31                24 23       23 22               16 15               12 11       8 7        0|31      0 
|-------------------|-----------|-------------------|-------------------|----------|----------|---------|
|      u8LengthH    | u1LengthL | u7ManufacturerIdH | u4ManufacturerIdL | u4FnNumH | u8FnNumL | u32Data |
|-------------------|-----------|-------------------|-------------------|----------|----------|---------|
\endcode
**************************************************************************************************************************/		

    //! This byte ordering is correct, it is mixed up like this because Keil interprets bytes from the right to left. 
    //! That's why we had to divide the 16bit variables in high and low parts. With this definition we get a structure like showed on the picture beyond
	
	//! Sys_ex datafield definition
    typedef union {
		//! Datafiled structer for header telegrams (IDX = 0)
		struct header{						
			uint8 	 	u8LengthH : 8;
			uint8 		u7ManufacturerIdH : 7;												
			uint8 	 	u1LengthL : 1;
			uint8 		u4FnNumH : 4;													
			uint8 		u4ManufacturerIdL : 4;												
			uint8 		u8FnNumL : 8;
			uint8  		u8Data[4];				//!<The 4 byte datafield is a uint8 field					
		}header;

		//! Datafiled structer for data telegrams (IDX > 0)
		struct _data{
			uint8  		u8Data[8];
		}_data;
	} sys_ex_data;


	//! Smart ack Learn Asnwer telegram datafield definition	
	typedef union {
		//! Datafiled structure for message Learn reply
		struct answer_reply{
			uint16	u16ResponseTime;
			uint8	u8AckCode;
			uint32	u32SensorId;

		}answer_reply;
		//! Datafiled structure for message Learn reply
		struct answer_acknowledge{
			uint16	u16ResponseTime;
			uint8	u8AckCode;
			uint8	u8MailBoxIdx;

		}answer_acknowledge;
	} smart_answer;

	//! Telegram structure used for Radio transmission.
	typedef union {
		struct raw_TEL_RADIO_TYPE
		{
			//! Telegram seen as a array of bytes without logical structure.
			uint8 bytes[RADIO_BUFF_LENGTH];
			//! Radio telegram length, it's not part of the transmitted/received data, it is used only for processing the telegram
			RADIO_TEL_LENGTH u8Length;
		} raw;
				
		//! RPS/1BS/HRC/smart_req radio telegram structure
		struct trps_t1bs_thrc_smart_req{
			CHOICE_TYPE u8Choice;
			uint8  		u8Data;
			uint32 		u32Id;
			uint8  		u8Status;											
			uint8  		u8Chk;
			uint8		u8Fill[RADIO_BUFF_LENGTH-8];
			RADIO_TEL_LENGTH u8Length;
		}trps, t1bs, thrc, smart_req;							   

		//! 4BS/SYS radio telegram structure
		struct t4bs_tsys{
			CHOICE_TYPE u8Choice;
			uint8  		u8Data3;
			uint8  		u8Data2;
			uint8  		u8Data1;
			uint8  		u8Data0;
			uint32 		u32Id;
			uint8  		u8Status;
			uint8  		u8Chk;
			uint8		u8Fill[RADIO_BUFF_LENGTH-11];
			RADIO_TEL_LENGTH u8Length;
		}t4bs,tsys;							   

		//! SYS_EX radio telegram structure
		struct sys_ex{
			CHOICE_TYPE u8Choice;
            //! Note the sequence is correct because Keil takes the bitfield from right to left. See telegram definition for more information
			uint8 	 	u6Index	: 6; 	
			uint8 		u2Seq	: 2; 
			sys_ex_data	u64Data;
			uint32 		u32SenderId;
			uint8  		u8Status;
			uint8  		u8Chk;
			uint8		u8Fill[RADIO_BUFF_LENGTH-16];
			RADIO_TEL_LENGTH u8Length;
		}sys_ex;

		//! smart ack learn request radio telegram structure
		struct sm_lrn_req{
			CHOICE_TYPE u8Choice;
			uint16 	 	u11ManufacturerId	: 11; 	
			uint16 		u5ReqCode			: 5;
			uint8		u8EEP[3];
			uint8		u8RssiDbm;		
			uint32 		u32RepeaterId;
			uint32 		u32SenderId;
			uint8  		u8Status;
			uint8  		u8Chk;
			uint8		u8Fill[RADIO_BUFF_LENGTH-17];
			RADIO_TEL_LENGTH u8Length;
		}sm_lrn_req;

		//! smart ack learn asnwer radio telegram structure
		struct sm_lrn_ans{
			CHOICE_TYPE 	u8Choice;
			uint8  			u8MsgIdx;
			smart_answer	u56Data;
			uint32 			u32SenderId;
			uint8  			u8Status;
			uint8	  		u8Chk;
			uint8			u8Fill[RADIO_BUFF_LENGTH-15];
			RADIO_TEL_LENGTH u8Length;
		}sm_lrn_ans;

		//! smart ack reclaim radio telegram structure
		struct sm_rec{
			CHOICE_TYPE u8Choice;
			uint8		u7MailBoxIdx : 7;
			uint8		u1ReclaimIdx : 1;
			uint32 		u32SenderId;
			uint8  		u8Status;
			uint8  		u8Chk;
			uint8		u8Fill[RADIO_BUFF_LENGTH-8];
			RADIO_TEL_LENGTH u8Length;
		}sm_rec;

		//! signal radio telegram structure
		struct sig{
			CHOICE_TYPE u8Choice;
			uint8		u8SignalIdx;
			uint32 		u32SenderId;
			uint8  		u8Status;
			uint8  		u8Chk;
			uint8		u8Fill[RADIO_BUFF_LENGTH-8];
			RADIO_TEL_LENGTH u8Length;
		}sig;

		//! generic profiles single telegram 
		struct gp_single_raw
		{
			CHOICE_TYPE u8Choice;
			uint8  		u8Data[20];
			RADIO_TEL_LENGTH u8Length;
		} msg_raw;
	
		//! generic profiles chain telegram structures
		struct msg_chain
		{
			CHOICE_TYPE u8Choice;
			uint8 	 	u6Index	: 6; 	   		//!<Note the sequence is correct because Keil takes the bitfield from right to left. See telegram definition for more information
			uint8 		u2Seq	: 2; 
			uint8  		u8Data[19];		   		//!<Data + ID + Status + Checksum
			RADIO_TEL_LENGTH u8Length;
		} msg_chain;
	
		//! Secure teach-in telegram
		struct sec_ti
		{
			CHOICE_TYPE u8Choice;
			uint8 	 	u2Info	: 2; 			//!<Note the sequence is correct because Keil takes the bitfield from right to left. See telegram definition for more information
			uint8 		u2Type	: 2;
			uint8 		u2Count	: 2;
			uint8 		u2Index	: 2; 
			uint8  		u8Data[19];				//!<Data + ID + Status + Checksum
			RADIO_TEL_LENGTH u8Length;
		} sec_ti;

		//! generic profiles chain telegram stucture for the zero telegram
		struct msg_chain_0
		{
			CHOICE_TYPE u8Choice;
			uint8 	 	u6Index	: 6; 			//!<Note the sequence is correct because Keil takes the bitfield from right to left. See telegram definition for more information
			uint8 		u2Seq	: 2; 
			uint16		u16Length;
			uint8  		u8Data[17];		  		//!<Data + ID + Status + Checksum
			RADIO_TEL_LENGTH u8Length;
		} msg_chain_0;

	} TEL_RADIO_TYPE;	


  	//! Telegram parameter structure
	typedef union 
	{
		//! param structure for transmitted telegrams
		struct p_tx {
			//! number of subtelegrams to send 
			uint8  u8SubTelNum;
			//! to send Destination ID
			uint32 u32DestinationId;

		}p_tx;

		//! param structure for received telegrams
		struct p_rx{
			//! number of subtelegrams received	(= number of originals + number of repeated)
			uint8  u8SubTelNum;
			//! received Destination ID
			uint32 u32DestinationId;
			//! u8Dbm of the last subtelegram calculated from RSSI. Note this value is an unsigned value. The real dBm signal is a negative value.
			uint8 u8Dbm;
		}p_rx;
	} TEL_PARAM_TYPE;

//! @}


//! @addtogroup radio_fn_grp RADIO functions
//! Functions used for radio communication
//! \ingroup radio_grp
//! @{

	/************************************************************************************************************************//*!
    Sets the radio parameters
	
	\param[in]		Number of the used radio buffers.
	\param[in]		Used maturity time in system.
	
	
    \return 	

    \note
	  The radio_init_asm files are dependent on the chip frequency. Use the apropriate for you module from the EO3000I_LIB directory.
		
    \note
    This function can be used with the scheduller (line powered applications) and in ultra low power applications.							   	
	
	**************************************************************************************************************************/		
	void radio_init(uint8 u8NumBuffers, uint8 u8MaturityTime);

	/************************************************************************************************************************//*!
    Sets the number of duty cycle slots and initializes Duty Cycle limitation
	
	\param[in]		Number of the duty cyle slots.
	
    \return 	

    \note
	The duty cycle limitation is a regulation which only applies in 868 MHz in Europe
			
    \note
    This function can be used only with the scheduller (line powered applications). For ultra low power applications the user has
	to care to meet the duty cycle limit.							   	
	
	**************************************************************************************************************************/		
	void radio_initDutyCycleLimit(uint8 u8NumSlots);

	/************************************************************************************************************************//*!
    Gets a radio telegram stored in a radio rx buffer.
    
    \param[out]      *pu8RxRadioTelegram	  	Address where the received telegram is copied to.
    \param[out]      *pu8TelParam			Address where the telegram additional parameters are copied to. 
    \return     	OK	  					Radio telegram received and copied.
    \return     	NO_RX_TEL				No radio telegram received.
	
	\note
	Note that the subtelegram number in u8TelParam shows the actual stand of the subtelegram counter. If the function
	is called too early -  before the maturity time limit of the telegram is reached - it is possible that this parameter shows only 
    1 or 2 subtelegrams because only 1 or 2 subtelegram has arrived. It doesn't neceseraly mean that the rest of the subtelegrams are lost. 
    See timing diagram below for explanation.
    \image html subtel_early.png Fetching telegram before all subtelegrams has arrived\n\n
    
    \note
	If you need the exact amount of all received sub telegrams use #radio_waitEndMaturity to enable this feature. But then all telegrams
	are delayed till the end of the maturity time before they will returned by radio_getTelegram.

	\note
	The dBm value in u8TelParam is the strongest value of all up to now received subtelegrams (30 is very strong, 96 is very weak signal).
	Note this value is an unasigned value, in reality it is a negative value. I.e. value 70dBm  in reality is -70dBm
	
	\note
	Different subtelegrams has different dBm level. The radio_getTelegram returns always the lowest dBm value, although it 
    may happen that by the time the radio_getTelegram is called only the 1st subtelegram has been received. To make sure you get 
    realy the lowest dBm among all subtelegrams set the #radio_waitEndMaturity to on.
    
	\note
	If telegram was encapsulated in ADT (Addressing Destination Telegram)than the Destination ID is in u8TelParam.
	If the destinationID is 0xFFFFFFFF  that means either an ADT was received with a BROADCAST_ID or the telegram 
    received was not ADT encapsulated (all not ADT encapsulated are considered to be broadcast).

	\note
	Each received telegram will be stored in one of the available radio buffers. The amount of radio buffers is defined in EO3000i_cfg.h in RADIO_BUFF_NUM. \n
	Only calling radio_getTelegram will release a busy buffer. It is important to call it periodically, because when all buffers are full, new received telegrams
	will be discarded. There is no possibility to determine the order of the received telegrams, because this depends on rx and tx traffic and the number of lost sub telegrams.

	\note
	If a filter is defined, it is also impossible to call radio_getTelegram periodically, because the check, if the filter applies, is in radio_getTelegram.
	If it is not called, the radio buffers get full, even when no telegram is expected by filter rule.

    \note
    This function can only be used with the scheduller (line powered applications).							   	
    
	
    \sa radio_sendTelegram, radio_waitEndMaturity
    **************************************************************************************************************************/		
	RETURN_TYPE radio_getTelegram(TEL_RADIO_TYPE *pu8RxRadioTelegram, TEL_PARAM_TYPE *pu8TelParam);

	/************************************************************************************************************************//*!
    Switchs radio_getTelegram function to return only telegrams where the maturity time is elapsed
    
    \param[in]      bValue				  	FALSE (Default): Return telegrams in radio_getTelegram independent of the maturity time
    										TRUE: Return in radio_getTelegram only telegrams where the maturity time is elapsed
    \return	  				
	
	\note
	If it is necessary to get the correct amount of sub telegrams in TEL_PARAM_TYPE of the radio_getTelegram function, use
	radio_waitEndMaturity(TRUE) once to switch API in state to wait till end of maturity time before returning a telegram.
	So there is always the delay in length of the maturity time!
	
    \note
    This function can only be used with the scheduller (line powered applications).							   	
  
	
    \sa radio_getTelegram
    **************************************************************************************************************************/		
	void radio_waitEndMaturity(bit1 bValue);

	
	/************************************************************************************************************************//*!
	Sends a radio telegram with u8Subtel subtelegrams and optionally also encapsulated to ADT (Address Destination Telegram) with 
	Destination ID. If Destination ID is set to 0 no ecapsulation is done. Encapsulation is made only if Destiantion ID has other value as 0.\n
	
	If no other telegram is to send. Before transmitting the telegram be sure to set the u8Length parameter of 
	the TEL_RADIO_TYPE structure. If there is no free Tx buffer the function returns imediately. 
	
	\param[in]  	*pu8TxRadioTelegram	  Address of the first telegram byte.
	\param[in]  	*pu8TelParam	  	  Param for sending. (Subtelegram number count and Destination ID) If value is NULL, than 3 subtelegram count is used by default and ADT encapsulation is not preformed.
	
	\return    		OK 				Telegram sent. 
	\return    		BUFF_FULL	 	No free Tx buffer available for transmission
	\return	   		NOT_VALID_PARAM	The telegram length in TEL_RADIO_TYPE was not set OR the u8Subtel number is 0 or more than 3 OR the encapsulated ADT telegram length is bigger > 16bytes 
	\return    		ID_OUT_OF_RANGE The ID given in TEL_RADIO_TYPE structure is out of allowed range
	\return			LOCK_SET		Duty cycle limit reached

	\note
	Notice that Rx and Tx use the same buffers. When buffers are full occupied by received telegram, sendTelegram will fail because 
	no buffer for send is free. When send command is called in a infinite cyrcle until send is successful, deadlock will occure.

	\note	
	When you want to transmit more telegrams as there are available telegram buffers and you want to do it during one cycle of the maturity time 
	the telegram sending sequence can't be ensured. \n
	<b>Example 1:</b> \n
	There are 3 available telegram buffers and we want to transmitt telegrams: rTel_a, rTel_b, rTel_c during 1 maturity time. We call the following code:\n
	<code>
	radio_sendTelegram(&rTel_a);\n
	radio_sendTelegram(&rTel_b);\n
	radio_sendTelegram(&rTel_c);\n
	</code>
	The result sequence in the air can be: rTel_a, rTel_c, rTel_b OR rTel_a, rTel_b, rTel_c. To avoid this problem be sure to leave enough time delay between
	telegram transmission.
	
	\note
	Be sure to let enough time between calling the radio_sendTelegram. The receiver has to put each telegram in a different buffer and has 
	to wait the maturity time long until freeing the buffer. When sending too much different telegrams in short time the receiver has to have 
	enougth receiver buffers to store the telegrams. 
	Only resolution is to define enougth buffers or to wait the maturity time (100ms standard) long after sending the next telegram.
	Besides that could sending more telegrams in a row overload a repeater system which is not able to fit the EnOcean sub telegram timing correct. So be carefully
	sending different telegrams in shorter periods than 40 ms.


	<b>Example 1:</b> \n
    This will cause a deadlock optionally, when buffers are full with received telegrams.
    \code
      TEL_RADIO_TYPE		rTel;	  
 	  while (radio_sendTelegram(&rTel, NULL)==BUFF_FULL) 
	  	{};	  
    \endcode

	<b>Example 2:</b> \n
    When sending in while() the radio_getTelegram function must be called, to free a buffer.
    \code
      TEL_RADIO_TYPE		rTel;	  
	  TEL_RADIO_TYPE		r2Tel; 	
 	  while (radio_sendTelegram(&rTel, NULL)==BUFF_FULL) 
	  	{radio_getTelegram(&r2Tel, NULL);};	  
    \endcode

	<b>Example 3:</b> \n
    Try to send a telegram with a specified count of attempts. When still failed, handle situation.
    \code
      TEL_RADIO_TYPE		rTel;	  
	  RETURN_TYPE 		  result; 

	  for(uint8 i =0 ; i < 10;i++)
	  {
 	  	result = radio_sendTelegram(&rTel, NULL);
		if(result == OK)
			break; 
	  }
	  if(result != OK)
	  {
	  	//handle the situation
	  }
    \endcode	  


	\note
	The parameter u32id of TEL_RADIO_TYPE structure defines, what id will be sent in the air. If this parameter is in range
	0 ... 0xff7fffff than the chip ID will be sent. If the ID is 0xffffffff (BROADCAST_ID) the function returns BASEID_OUT_OF_RANGE.

	<b>Example 4:</b> \n
    Send the ID of the Dolphin chip
    \code
      TEL_RADIO_TYPE		rTel;

	  rTel.t4bs.u32id = 0;
	  // do not forget so set the other fields of rTel structure	  
 	  if (radio_sendTelegram(&rTel, NULL)==OK) 
	  	{};
    \endcode

	The user can also define a base ID by itself and use a band of different Ids, starting from
	base_ID+0 to base_ID+127 for telegrams
	<b>Example 5:</b> \n
    Use user defined ID
    \code
      TEL_RADIO_TYPE		rTel;
	  uint8                 buf[256];  // used to store temporary data 

	  if (radio_setBaseId(0xff800000)==OK) // set base id (must be in range of 0xff800000 to 0xffffff80
	  	{};	  
	  rTel.t4bs.u32id = 0xff800000+33;
	  // do not forget so set the other fields of rTel structure	  
 	  if (radio_sendTelegram(&rTel, NULL)==OK) 
	  	{};	  
	  rTel.t4bs.u32id = 0xff800000+128;
 	  if (radio_sendTelegram(&rTel, NULL)==OK) 
	  	{
			// will not be reached, function returns with error code ID_OUT_OF_RANGE because maximum 127 is allowed
		};
    \endcode
	 
	  \note
    This function can only be used with the scheduller (line powered applications).							   	

	\sa radio_getTelegram, radio_setBaseId,pwr_setSleepTimer
	**************************************************************************************************************************/		
	RETURN_TYPE radio_sendTelegram(TEL_RADIO_TYPE *pu8TxRadioTelegram, TEL_PARAM_TYPE *pu8TelParam);

	/************************************************************************************************************************//*!
	Ultra low power function. Use for energy autarkic devices without schedule. This function prepares the telegrams for transmission
	and palces the result to the radio Tx buffer Int. Be sure to set the correct telegram length.
    The function does the following steps:
    - sets the CHIP ID of the telegram
    - calculates the checksum or CRC
    - encodes the telegram
    - places the encoded bytes to radio Tx buffer
	- optionally when specified Destination ID encapsulate to ADT structure
     
	\param[in]     *pu8TxRadioTelegram	Telegram to send
	\param[in]     *puTxParam           Param for sending. (Destination ID) If value is NULL, than ADT encapsulation is not preformed.
	\return    		OK 				    Telegram sent. 
	\return    		NOT_VALID_PARAM		The length for the telegram was not defined.
    
		
	\note 
	Be sure to set the u8Length variable of the telegram
	
	\note
    The ID bytes of the telegram will be overwritten with the CHIP ID       

	\note
	For sending telegrams with more than one sub telegram this function need only be once called, because the encoded telegram 
	remains stored in the internal tx buffer.
	
	\note
  This function can only be used in ultra low power applications without scheduller.							   	

	\sa radio_ulpSend3SubTels, radio_ulpSendTelegram, radio_ulpSubTelTiming
	**************************************************************************************************************************/		
	RETURN_TYPE radio_ulpPrepareTelegram(TEL_RADIO_TYPE *pu8TxRadioTelegram, TEL_PARAM_TYPE *puTxParam);

	/************************************************************************************************************************//*!
	Ultra low power function. Use for energy autarkic devices without schedule. This function transmits three subtelegrams to the air 
    from the radio Tx buffer Int. Before calling first time this function be sure to call the function #radio_ulpPrepareTelegram. 
	The function initiates transmission, performs a short term sleep after sending 1st and 2nd subtelegram and goes to standby mode 
	while the 3rd sub telegram is sent. The sub telegram timing complains with the EnOcean standard. 
	After that returns the control to the application. 		
    
	\param -

		
	\note 
	This function can't be used with schedule! That means you can't use this function with radio receiver on OR with repeater OR with routing. 
    Be sure to comment out any of the schedule initialisation routine  - isr_timer0xxxx()-  from the EO3000I_CFG file #INIT_EO3000I define!
	
	\note
	Be sure to call misc_init prior using that function, because the random generator of the Dolphin chip is used to perform random sub telegram timing.

    
	\sa radio_ulpPrepareTelegram
	**************************************************************************************************************************/		
	void radio_ulpSend3SubTels();

	/************************************************************************************************************************//*!
	Ultra low power function. Use for energy autarkic devices without schedule. This function transmits one subtelegram to the air 
    from the radio Tx buffer Int. Before calling first time this function be sure to call 
    the function #radio_ulpPrepareTelegram. The function initiates transmission and after that returns the control to the application. 		
    
		
	\note 
	This function can't be used with schedule! That means you can't use this function with radio receiver on OR with repeater OR with routing. 
    Be sure to comment out any of the schedule initialisation routine  - isr_timer0xxxx()-  from the EO3000I_CFG file #INIT_EO3000I define!
	
	\note
	The most efficient way using this function is to realise the subtelegram timing with short term sleep, i.e. to 
	enter short term sleep mode after the function returns. If not going to short term sleep mode the Tx state-machine
	keeps running and will consume power.

	\note
	Between the sub telegrams, a short term sleep or standby mode could be performed to save energy. 
	
	\note
	Be sure to enter deep sleep mode only when the sub telegram is sent completely by checking #radio_getOngoingRxTx.
		
	\sa radio_ulpPrepareTelegram, radio_ulpSubTelTiming
	**************************************************************************************************************************/		
	void radio_ulpSendTelegram();

	/************************************************************************************************************************//*!
	Macro calculating random sub telegram timing according EnOcean sub telegram timing specification
	This macro calculates random sub telegram timeslots using random generator of Dolphin chip.
	
	\note
	Be sure to call misc_init() before using this macro.
	
	\note
	For ULP applications we do not recomend to use the possibility to send the 2nd subtelegram in 3rd sub telegram timing area.
	This macro considers that recomendation.		
    
	\param[in]     s       Number of subtelegram to calculate [1..3]
	\param[out]    t 	   Number of timeslot (starting with 0) to send this subtelegram [0..39]

	\note
  This function can only be used in ultra low power applications without scheduller.							   	
		
	\sa radio_ulpPrepareTelegram, radio_ulpSendTelegram
	**************************************************************************************************************************/		
	#define radio_ulpSubTelTiming(s, t)                                                          \
	        	if (s==1) t=0;                                                                   \
				else if (s==2) t=1 + (misc_rndGet() % (10-3));                       \
				else t=20 + (misc_rndGet() % (39-20-3));

	/************************************************************************************************************************//*!
    Gets the number of busy Rx radio buffers. This function can be used to know how many telegram has to be still processed
	by the application until the radio Rx can be switched off.
    
    \param[out]      *pu8No	  	Number of busy buffers
    \return     -		
    
	\note
	This function is allowed to be used in an interrupt callback function ONLY if it is ensured that it is not used at the same time from the main program!

	\note The user is responsible to implement an EnOcean Radio Protocol conform subtelegram timing! See \ref References, 
	EnOcean Radio Protocol specification.

	  \note
    This function can only be used with the scheduller (line powered applications).							   	
	
    \sa radio_getNoTxBusyBuffs
    **************************************************************************************************************************/		
	void radio_getNoRxBusyBuffs(uint8 *pu8No);
	
	/************************************************************************************************************************//*!
    Gets the number of busy Tx radio buffers. This function can be used to know how many telegram has to be still sent
	by the schedule until the Tx radio can be switched off or the CPU can be put to sleep mode.

    \param[out]      *pu8No	  	Number of busy buffers
    \return     	-		
    
	\note
	This function is allowed to be used in an interrupt callback function ONLY if it is ensured that it is not used at the same time from the main program!

	  \note
    This function can only be used with the scheduller (line powered applications).							   	
    
    \sa radio_getNoRxBusyBuffs
    **************************************************************************************************************************/		
	void radio_getNoTxBusyBuffs(uint8 *pu8No);

	/************************************************************************************************************************//*!
    Enable the radio receiver hardware.

    \param[in]      bEnable	  	1 - radio receiver ON 
								0 - radio receiver OFF
    
	\return     	OK			The Radio Rx statemachine was started
	\return     	LOCK_SET	Failed to start the rx statemachine due to ongoing Radio Tx process
    
	\note
	This function is allowed to be used in an interrupt callback function ONLY if it is ensured that it is not used at the same time from the main program!

	  \note
    This function can only be used with the scheduller (line powered applications).							   	
    
    **************************************************************************************************************************/		
	RETURN_TYPE radio_enableRx(bit1 bEnable);

	/************************************************************************************************************************//*!
    Returns the base ID.

    \param[out]      pu32BaseID  	Pointer to store the base ID in
    \return     -		
    
     \note
    This function can be used with the scheduller (line powered applications) and in ultra low power applications.							   	
   
    **************************************************************************************************************************/		
	void radio_readBaseId(uint32 *pu32BaseID); 

	/************************************************************************************************************************//*!
    Stores the base ID.

    \param[in]      u32BaseID 		base ID to change. Is allowed in range from 0xFF800000 to 0xFFFFFF80, the user may change it maximum 10 times

    \return     OK				ID stored
				BASEID_OUT_OF_RANGE	base ID is not in allowed range of: 0xff800000 <= range <=0xffffff80, or the 7 least significant bits are not zero
				BASEID_MAX_REACHED  base ID was changed 10 times, no more changes are allowed
				FLASH_HW_ERROR  error while writing in FLASH memory
				
	\note
	IMPORTANT: This function can only be called 10 times to change the base ID.	There is no possibility to reset this
	constraint. Also power off/on will not allow more than 10 changes!

	\note
	CONSTRAINTS:	The 7 least significant bits of base ID needs to be zero so that the base ID matches with the mask 0xFFFFFF80.
	Valid base ID is for example: 0xFF800000, 0xFF800080, 0xFF800100 ... 0xFF811980, 0xFF811A00 ... 0xFFFFFF00, 0xFFFFFF80

	\note
	It is not possible to use a base ID in components using smart acknowledge. The function #smack_reclaim will only reclaim telegrams with the chip ID.
	And the functions of the post master, regardless if repeater or controller, will also use only the chip ID.

	\note
	It is not possible to use a base ID with remote management, because all remote management answer telegrams use the chip ID.
    
	\note 
	It is possible to emulate BASE_ID + 127 ID's. So one module can emulate 128 senders using the BaseID
    
	\note
	No BaseID with value 0xFFFFFFFF can be used
	
    \note
    This function can be used with the scheduller (line powered applications) and in ultra low power applications.							   	
	
	
    *************************************************************************************************************************/		
	RETURN_TYPE radio_setBaseId(uint32 u32BaseID);

	/************************************************************************************************************************//*!
    Returns the state of the current radio Rx receiving or Tx transmittion. It is usefull to se if there is actual ongoing transmission or receiving 
	before entering to standby.

    \param[out]      *u8TxOn	 If TRUE currently there is an ongoing transmission
	\param[out]      *u8RxOn	 If TRUE currently there is an ongoing receiving

    \return     -
    
    \note
    This function can be used with the scheduller (line powered applications) and in ultra low power applications.							   	

    **************************************************************************************************************************/		
	void radio_getOngoingRxTx(uint8 *u8TxOn, uint8 *u8RxOn);

    /************************************************************************************************************************//*!
	Returns the short term and long term  RSSI signal
	
	\param[out]  	pu16StRssi		Address of the variable where the Short Term Radio Signal Strength should be saved
    \param[out]  	pu16LtRssi		Address of the variable where the Long Term Radio Signal Strength should be saved
	\return		-

								   	
    \note 	
    Two signals, the STRSSI and the LTRSSI are compared to each other to detect telegram start. The
    STRSSI is a filtered magnitude signal, indicating the possible presence of an incoming telegram,
    while the LTRSS represents a long term RSS indicating the background noise. The packet starts are 
    detected as soon as the STRSSI rises above the LTRSSI value.
    
    \note 
    You can use the LTRSSI signal to detect if the radio channel is blocked by a transmitter sending continouse wave.

    \note 
    Don't use the STRSSI to detect the received telegram signal strength. Use instead the dBm parameter delivered 
    by the radio_receiveTelegram function. The dBm parameter is the average signal strength calculated from the whole telegram signal.

    <b>Example:</b> \n
    Detect if there is a communication on the channel, and if yes send the signal strength through UART:
    \code
    #define SIGNAL_STRENGTH 400
    void main()
    {		
        uint8 u8Buff[30];
        uint16 pu16StRssi, pu16LtRssi;
    	mainInit();	
        radio_enableRx(1);    
        pu16LtRssi=0;
        
        while(1)
    	{
            do
            {
                radio_getRSSI (&pu16StRssi, &pu16LtRssi);
            } while (pu16LtRssi<SIGNAL_STRENGTH);
            
            sprintf(u8Buff,"STRSS: %d, LTRSS: %d\n", pu16StRssi, pu16LtRssi);
            while (uart_sendBuffer(u8Buff, strlen(u8Buff))!=OK);
            io_togDigital(ADIO_5);    
    	}
     
    }
    \endcode

	  \note
    This function can only be used with the scheduller (line powered applications).							   	
       							  
	\sa radio_rssiToDbm_asm
	**************************************************************************************************************************/		
	void radio_getRSSI(uint16 *pu16StRssi, uint16 *pu16LtRssi);


	/************************************************************************************************************************//*!
    Calculates dBm from RSSI based on the calibration values in radio init specified by array u8RssiCalib.

    \param      RSSI signal where the LSB bit is the LNA
    \return     dBm value
    
 	  \note
    This function can only be used with the scheduller (line powered applications).							   	

	\sa radio_getRSSI
    **************************************************************************************************************************/		
	uint8 radio_rssiToDbm_asm(uint16 u16RssiLna);

	
	extern code uint8  u8CRC8Table[256];
	/************************************************************************************************************************//*!
	  CRC8 calculation for radio telegrams. Note that the CRC actual value is calculated from all the previous data.
	
	  \param  	u8CRC				Actual value of CRC
	  \param  	u8Data				Data to calculate the CRC from

    <b>Example:</b> \n
    Calculate a CRC for a radio telegram SYS_EX.
    \code

  	uint8 u8Crc, i;
  	TEL_RADIO_TYPE  rTelOut;
    u8Crc=0;
	for (i=0;i<RADIO_DEC_LENGTH_SYS_EX-1;i++)
	{
		u8Crc = proc_crc8(u8Crc,rTelOut.raw.bytes[i] ); 
	} 
	
	\endcode
	  
	
	************************************************************************************************************************************/
	#define proc_crc8(u8CRC, u8Data) (u8CRC8Table[u8CRC ^ u8Data])
	
	
//! @}



	/*********************************************************************************************/
	/************************  MESSAGE TRANSMISSION DEFINES AND PROTOTYPES ***********************/
	/*********************************************************************************************/
/*!
	\addtogroup msg_grp  msg
	The message module allows to send longer radio message by using telegram chaining functionality. 
	\ingroup ESSL
*/ 

//! @addtogroup msg_cfg_grp Message module structures
//! Message structures. 
//! \ingroup msg_grp
//! @{	
	
	//! Message Type
	typedef struct
	{
		//! Message type.
		uint8	u8Choice;
		//! Source ID
		uint32 u32SourceId;
		//! The length of the u8Data
		uint16	u16Length;
		//! The maximal length of the u8Data 
		uint16	u16MaxLength;
		//! Data buffer
		uint8	*u8Data;
	} MESSAGE_TYPE;
	
	//! Message Module Parameters
	typedef struct
	{
		//! Maximal time between two radio telegrams in chain [ms]. Default = 100
		uint16	u16ReceiveTimeout;
		//! Delay between two send radio telegrams in [ms]. Default = 40 ms
		uint16	u16SendDelay;
	} MESSAGE_PARAM;
//! @}

//! @addtogroup msg_fn_grp Message management functions
//! \copydetails msg_grp
//! \ingroup msg_grp
//! @{
	
	/************************************************************************************************************************//*!
	Sends a message via radio. 
	
									
	\param[in]  	pMessage		Pointer to the message to be sent
	\param[in]		pParam			Message transmission parameters
	
	\return 	    OK        		The message has been sent correctly
	\return 	    OUT_OF_RANGE	The message data length exceeds the maximal specified value (512 bytes) 
																								  
	\note This function is BLOCKING. It waits till all radio telegrams are placed in the radio buffers. To define the delay 
		  between radio telegrams use the msg_setParams() function.
	
	\note Messages are splitted by the function into several telegrams - the telegram chaining functionality is applied as explain in \ref tel_chaining_page.
	Telegrams are also sent by this function.


	<b>Example:</b> \n
	
	\code
		uint8				u8Buffer[128];
		TEL_PARAM_TYPE		pParam = { 0xFF, BROADCAST_ID };
	  	MESSAGE_TYPE		pMessage;
		
		pMessage.u8Choice = RADIO_CHOICE_VLD;
		pMessage.u8Data = u8Buffer;
		pMessage.u16MaxLength = sizeof(u8Buffer);
	
		pMessage.u16Length = 10;
		pMessage.u8Data[0] = ...;
	
		u8Ret = msg_send(&pMessage, &pParam);
	\endcode
	
	**************************************************************************************************************************/		
	RETURN_TYPE msg_send(MESSAGE_TYPE *pMessage, TEL_PARAM_TYPE *pParam);
	
	
	/************************************************************************************************************************//*!
	Converts received chained radio telegrams to messages.
									
	\param[out]  	pMessage		Pointer to the message created by the function
	\param[out]		pParam			Received telegrams parameters
	
	\param[in] 		rTel 			Received telegram structure
	\param[in] 		pTel 			Received telegram parameters
		
	\return 	    OK        		Complete message has been received
	\return 	    NO_RX_TEL		The incoming rTel was processed but the chained message is still not complete. Waiting for more telegrams.
	\return 	    NOT_VALID_TEL	The incoming rTel was not processed. 
	\return 	    OUT_OF_RANGE	The message length exceeded the pMessage.u16MaxLength
	

	\note Chained radio telegrams with RADIO_CHOICE_CDM or RADIO_CHOICE_SEC_TI choice are joined in a single message by this function. 

	\note To work correctly the function msg_receive() has to be called everytime that a radio telegram is received by the #radio_getTelegram function.
	
	\note  pParam.p_rx.u32Dbm stores the value of the telegram with highest signal strength.

	\note If a telegram belonging to the message arrives out of the time-out indicated in #msg_setParams it will be discarded for the message and consider to belong to a new message.
	The function does not return a time-out value.



	
	<b>Example:</b> \n
	
	\code
	TEL_RADIO_TYPE		rTel;
	TEL_PARAM_TYPE		pTel;
	PACKET_SERIAL_TYPE	pPacket;
	uint8				u8PacketBuffer[128];
	uint8				u8MsgBuffer[128];
    MESSAGE_TYPE        msge;


	pPacket.u8DataBuffer  = u8PacketBuffer; 
    msge.u8Data           = u8MsgBuffer;
    msge.u16MaxLength     = sizeof(u8MsgBuffer);
	
	
	mainInit();	

	radio_enableRx(1);

	
  	while(1)
	{			
		CLR_WDT();
		
		memset(&rTel, 0x00, sizeof(rTel));
		if ((radio_getTelegram(&rTel, &pTel) == OK)         &&
            (msg_receive(&msge, &pTel, &rTel, &pTel) == OK))
		{
            memcpy(&u8PacketBuffer[0],                 &msge.u8Choice,      1);
            memcpy(&u8PacketBuffer[1],                  msge.u8Data,        msge.u16Length);
            memcpy(&u8PacketBuffer[1+msge.u16Length],  &msge.u32SourceId,   4);
            u8PacketBuffer[1+msge.u16Length+4] = 0x00;                                                  //Status
            memcpy(&u8PacketBuffer[1+msge.u16Length+4+1], &pTel,            sizeof(TEL_PARAM_TYPE) );

            pPacket.u16DataLength     = msge.u16Length + 6; 
            pPacket.u8OptionLength    = sizeof(TEL_PARAM_TYPE);
            pPacket.u8Type            = PACKET_RADIO; 

			while (uart_sendPacket(&pPacket) != OK);
		}  
	}	  
	\endcode
	
	\sa radio_getTelegram, msg_send
	**************************************************************************************************************************/		
	RETURN_TYPE msg_receive(MESSAGE_TYPE *pMessage, TEL_PARAM_TYPE *pParam, TEL_RADIO_TYPE *rTel, TEL_PARAM_TYPE *pTel);
	
	
	
	/************************************************************************************************************************//*!
	Configure message module parameters.
									
	\param[in]  	pParam			Pointer to the message-module parameters to set. See #MESSAGE_PARAM
		
	\return 	    OK        		Parameters set

	\note The time-out for the reception of a complete message (function #msg_receive) 
	and the pause between telegrams when sending a message (function #msg_send() are set with the help of this function.
	
	**************************************************************************************************************************/	
	RETURN_TYPE msg_setParams(MESSAGE_PARAM *pParam);
	
//! @}  

//************************ END FUNCTION PROTOTYPES **********************


/*********************************************************************************************/
/************************************ SECURITY MODULE *******************************************/
/*********************************************************************************************/
/*! 
	\addtogroup sec_grp sec
	Security module. The module's functions are responsible for the encryption, decryption, authentication of messages.
	Several encryption algorithms like AES128 and ARC4 can be used. 
	Rolling code strategy is also included to avoid replay attacks.\n\n

	A detail description of the security protocol and secure strategies implemented can be read under http://www.enocean.com/en/knowledge-base/
	\ingroup ESSL
*/ 

//! @addtogroup sec_struct_grp Secure module structures	and constants
//! Data structures and constant values that are used in SECURITY module
//! \ingroup sec_grp 
//! @{

	//! Amount of bytes of the CMAC subkeys 
	#define  CMAC_SUBKEY_SIZE			16


//!	\name teach-in info byte bit masks
//! @{
    //! INFO field bit mask in teach-in info byte
	#define  TEACH_IN_TYPE_MASK	0x0C
    //! INFO field bit mask in teach-in info byte
	#define  TEACH_IN_INFO_MASK	0x03
//! @} 


//!	\name Teach-in info byte fields values
//! @{
    //! Non-specific type identification 
	#define  TEACH_IN_TYPE_NON_SPEC	0x00
    //! PTM type identification 
	#define  TEACH_IN_TYPE_PTM		0x04
    //! PTM info first rocker 
	#define  TEACH_IN_INFO_ROCKER_A	0x00
    //! PTM info second rocker 
	#define  TEACH_IN_INFO_ROCKER_B	0x01
//! @}


//!	\name SLF byte bit masks
//! @{
    //! Rolling code algorithm identification bit mask in SLF byte
	#define  SLF_RLC_ALGO_MASK	0xC0
    //! Rolling code send/not send bit mask in SLF byte
	#define  SLF_RLC_TX_MASK	0x20
    //! Message authentication code identificator bit mask in SLF byte.
	#define  SLF_MAC_ALGO_MASK	0x18
    //! Encryption identificator bit mask.
	#define  SLF_DATA_ENC_MASK	0x07
//! @} 


//!	\name SLF byte fields values
//! @{
    //! No rolling code identification code 
	#define  SLF_NO_RLC_ALGO	0x00
    //! 16-bit rolling code identification code 
	#define  SLF_RLC_16_BIT		0x40
    //! 24-bit rolling code identification code 
	#define  SLF_RLC_24_BIT		0x80
    //! Not sending rolling code in telegram identification code 
	#define  SLF_RLC_TX_NO		0x00
    //! Sending rolling code in telegram identification code 
	#define  SLF_RLC_TX_YES		0x20
    //! No athentication in telegram identification code 
	#define  SLF_MAC_NO			0x00
    //! 3-byte MAC identification code
	#define  SLF_MAC_3_AES128	0x08
    //! 4-byte MAC identification code
	#define  SLF_MAC_4_AES128	0x10
    //! No encryption identification code
	#define  SLF_ENC_NO			0x00
    //! ARC4 encryption identification code
	#define  SLF_ENC_ARC4		0x02
    //! Variable AES128  encryption identification code
	#define  SLF_ENC_VAES128	0x03
    //! AES128  encryption identification code
	#define  SLF_ENC_AES128		0x04
//! @} 


	//!Security module function return values.
	typedef enum
	{
		SEC_OK	 = 0,				//!< function correctly executed.
		SEC_RLC_OUT_OF_RANGE,		//!< Received rolling code out of range.
		SEC_SIZE_WRONG,				//!< One of the parameters had a not permitted amount of bytes.
		SEC_CMAC_WRONG,				//!< Received and expected CMAC do not match.
		SEC_CHOICE_WRONG,			//!< Message choice not valid.
		SEC_ENC_WRONG,				//!< Encryption method code in SLF byte not allowed.
		SEC_SLF_WRONG,				//!< Not valid SLF code.

	}SEC_RESULT;

	//!Security information structure.
    typedef struct 
	{
		uint8	u8TeachInInfo;			//!< Teach-in info byte : | 4: RESERVED | 2: TYPE | 2: INFO |. Typically initialised by calling #sec_parseTeachIn function after reception of a teach-in radio message.											
		uint8	u8SLF;					//!< Security layer format byte : | 2: RLC_ALGO | 1: RLC_TX | 2: MAC_ALGO | 3: DATA_ENC |. Typically initialised by calling #sec_parseTeachIn function after reception of a teach-in radio message.
		uint32 	u32RLC;					//!< Rolling code value. Typically initialised by calling #sec_parseTeachIn function after reception of a teach-in radio message.
		uint8 	u8Key[16];				//!< Encryption/decryption key. Typically initialised by calling #sec_parseTeachIn function after reception of a teach-in radio message.  
		uint8 	u8KeySize;				//!< Size of the key in bytes. Typically initialised by calling #sec_parseTeachIn function after reception of a teach-in radio message.
		uint8 	u8CMACsubkey1[16];		//!< Subkey1 for the CMAC calculation. Typically initialised by calling #sec_parseTeachIn function after reception of a teach-in radio message.										
		uint8 	u8CMACsubkey2[16];		//!< Subkey2 for the CMAC calculation. Typically initialised by calling #sec_parseTeachIn function after reception of a teach-in radio message.										

	}SECU_TYPE;

//! @}


//! @addtogroup sec_fn_grp Secutity functions
//! Functions used for secure communication
//! \ingroup sec_grp
//! @{

/************************************************************************************************************************//*!
    Sets all the security module parameters
    
    \param[in]  	*pReserved	  			Reserved, can be NULL.
    \param[in]  	RLCwindow	  			In the receiver module, it sets the maximal difference between the received message rolling code and the expected rolling code  
    \return 		-
    
	\note
	A small RLCwindow value increases the security by narrowing the amount of rolling codes that the receiver will test before invalidating a message. 
	On the other hand it increases the risk of desynchronisation between sender and receiver in the event of sender activations without the receiver "listening" to these messages. 
							   	

    \sa sec_convertToNonsecure, sec_convertToSecure
	**************************************************************************************************************************/		
	void sec_init(uint8 *pReserved, uint32 RLCwindow);
	
	/************************************************************************************************************************//*!
    Transforms a secure message into a non-secure message, decrypting the information, checking the CMAC and the rolling codes if necesssary. 
    
    \param[in]  	mssgeSecure	  			Pointer to the secure message.
    \param[out]  	mssgeNonsecure	  		Pointer to the non-secure message.
    \param[in]  	secuInfo  				Pointer to the security information structure.

	\return 		SEC_OK					Function exited correctly.
    \return 		SEC_SIZE_WRONG	    	Some of the input information contains non-valid length
    \return 		SEC_RLC_OUT_OF_RANGE	The received rolling code and the expected rolling code differ in a value bigger than the rolling code window. See #sec_init
	\return			SEC_CMAC_WRONG			The received message contains a wrong CMAC
	\return 		SEC_ENC_WRONG			Wrong encryption method code in the SLF byte.


	\note
	Under mssgeNonsecure->u8Data can be found the decrypted data. This data does include neither rolling code nor CMAC

	\code
		      mssgeSecure->u8Data*			     mssgeNonsecure->u8Data
       |--------------|----------|----------|       |----------|        
	   |	data_enc  |    rlc   |   CMAC 	|  -->	|	data   |     				
	   |--------------|----------|----------|       |----------|
	*The information rlc and CMAC under mssgeSecure->u8Data is optional. 
	The encryption of data, data_enc, is also optional.
	The figure shows simply the most general case of securing information.
	\endcode

	\note
	#SECU_TYPE  secuInfo input parameter provides information about the secure message, such as the encryption method, the presence and amount of CMAC bytes, as well as rolling code and amount of bytes.
   	With this information the function checks and decrypts the secure message.

	\note
	The function reports through the return value if the secure message contains a wrong authentication code (CMAC) or the received rolling code is out of range.

	\note 
	When the received mssgeSecure.u8Choice field is #RADIO_CHOICE_SEC, mssgeSecure->u8Data does not contain the non-secure message choice. This allows saving energy when sending. The mssgeNonsecure->u8Choice returned by the function is	a general #RADIO_CHOICE_NON_SEC.
	When the received mssgeSecure.u8Choice field is #RADIO_CHOICE_SEC_ENCAPS, the mssgeSecure->u8Data includes the Choice of the original plain message. 
	The returned mssgeNonsecure->u8Choice contains the original non-secure choice.  The returned mssgeNonsecure->u8Data	does not include the non-secure choice. Therefore the length of data = data_enc - 1. 

	\note 
	The function uses the CURRENT rolling code stored under secuInfo->u32RLC for the processing of the mssgeSecure.
	When the result of the function is OK, the rolling code value stored under secuInfo->u32RLC is +1 the rolling code in the received radio message.

	\note 
	The function handles the arithmetic overflow of the rolling code. 
	The user does not have to implement additional code to set the rolling value to 0 after the rolling code reaches its maximal value.

	\note
	In the case of variable AES encryption (VAES) the data_enc field can not be longer than 16 bytes.

	\code

    TEL_RADIO_TYPE      rTel;
    TEL_PARAM_TYPE      pTel;
    MESSAGE_TYPE        pMsgSec, pMsgNonSec;
	SECU_TYPE			secuInfo;
    uint8               u8MsgBuffer[32];


    pMsgSec.u8Data           = u8MsgBuffer;
    pMsgNonSec.u8Data        = u8MsgBuffer;		 	// The address where non-secure data will be stored can be the same as the array for the secure information...
    pMsgSec.u16MaxLength     = sizeof(u8MsgBuffer);	// ...if RAM space is a concern
    pMsgNonSec.u16MaxLength  = sizeof(u8MsgBuffer);
    
    
    mainInit(); 

    radio_enableRx(1);

    
    while(1)
    {           
        CLR_WDT();
        
        memset(&rTel, 0x00, sizeof(rTel));
        if ((radio_getTelegram(&rTel, &pTel) == OK)         &&
            (msg_receive(&pMsgSec, &pTel, &rTel, &pTel) == OK))
        {
			// Secure teach-in telegram received?
			if(pMsgSec.u8Choice == RADIO_CHOICE_SEC_TI)
			{
				sec_parseTeachIn(&pMsgSec, &secuInfo);			// The details of the encryption, authentication and rolling code are stored in secuInfo
			}
			// Secure telegram in operation mode?
			else if(pMsgSec.u8Choice == RADIO_CHOICE_SEC_ENCAPS || 
			        pMsgSec.u8Choice == RADIO_CHOICE_SEC			)
			{
				// The non-encrypted information is stored in pMsgNonSec.u8Choice and pMsgNonSec.u8Data. 
				// You may check the return value of the function to be sure that the received mssgeSecure contains correct rolling code and correct authentication CMAC
				sec_convertToNonsecure(&mssgeSecure, &pMsgNonSec, &secuInfo);
			}
        }  
    }
	\endcode     
    						   	
    \sa sec_convertToSecure
	**************************************************************************************************************************/		
	SEC_RESULT	sec_convertToNonsecure(MESSAGE_TYPE *mssgeSecure, MESSAGE_TYPE *mssgeNonsecure, SECU_TYPE *secuInfo);

	/************************************************************************************************************************//*!
    Transforms a non-secure message into a secure message, encrypting the information, adding a CMAC and a rolling codes if necesssary. 
    
    \param[in]  	mssgeNonsecure	  	Pointer to the non-secure message.
    \param[out]  	mssgeSecure		  	Pointer to the secure message.
    \param[in]  	secuInfo  			Pointer to the security information structure.

	\return 		SEC_OK					Function exited correctly.
	\return 		SEC_CHOICE_WRONG		Secure telegrams can not be encrypted again.
    \return 		SEC_SIZE_WRONG	    	Some of the input information contains non-valid length
	\return 		SEC_ENC_WRONG			Wrong encryption method code in the SLF byte.

	\note
	Under mssgeSecure->u8Data can be found the encrypted data, rolling code and CMAC.
		
	\code
		mssgeNonsecure->u8Data					  mssgeSecure->u8Data*
			|----------|		    |--------------|----------|----------|                           
			|	data   |	-->	    |	data_enc   |    rlc   |   CMAC 	 |                        				
			|----------|		    |--------------|----------|----------|                
	*the information rlc and CMAC under mssgeSecure->u8Data	are optional. The encryption of data, data_enc, is also optional.
	The figure shows simply the most general case of securing information.
	\endcode

	\note
	In the case the non-secure message choice field is equal to #RADIO_CHOICE_NON_SEC the non-secure data is used as payload for the calculation of data_enc. In this case the mssgeSecure->u8Choice is #RADIO_CHOICE_SEC   
	In the case the non-secure message choice field is not #RADIO_CHOICE_NON_SEC, the function concatenates the non-secure choice byte to the data field for the calculation of data_enc.
	Therefore, the length of data_enc = length of data + 1. Where 1 is the length of the mssgeNonsecure choice.	The mssgeSecure->u8Choice returned by the function is #RADIO_CHOICE_SEC_ENCAPS

	\note
	The data_enc field length for VAES algorithm can not be bigger than 16 bytes.

	\note
	secuInfo provides the information of what encryption method is to be used, the presence and amount of CMAC bytes, as well as rolling code presence and amount of bytes.
   	According to this information the function creates the secure message.

	\note
	The function uses the CURRENT rolling code stored under secuInfo->u32RLC for the processing of the mssgeSecure.
	Afterwards the function increments the rolling code.
	After the function returns, the rolling code value under secuInfo->u32RLC is +1 than the rolling code used for the message.   

	\note 
	The function handles the arithmetic overflow of the rolling code. 
	The user does not have to implement additional code to set the rolling value to 0 after the rolling code reaches its maximal value.

	\note
	Secure PTM telegram can only be performed when the encryption method is set to VAES. Secure PTM message are 1 data byte long. 
	The 4 most significant bits of the data byte will be cleared by the function.


	\code
	MESSAGE_TYPE 	msgNonSec, msgSec;
	SECU_TYPE 		secuInfo;
	uint8			u8Buff[5] = {0x00, 0x01, 0x02, 0x03};
	uint8			u8BuffSec[11] ;  Choice(1) + Data(4) + RLC(3) + CMAC(3) bytes stored in this buffer.  


	mainInit(); 

	secuInfo.u8SLF 	= SLF_RLC_TX_NO + SLF_RLC_24_BIT + SLF_MAC_3_AES128 + SLF_ENC_VAES128;	  // Defines protocol

	msgNonSec.u8Data 		= u8Buff;					
	msgSec.u8Data 			= u8BuffSec;				
	msgNonSec.u8Choice 		= RADIO_CHOICE_4BS;
	msgNonSec.u16Length 	= sizeof(u8Buff) ;    	
	msgSec.u16MaxLength  	= sizeof(u8BuffSec);		

	secuInfo.u8SLF 	= SLF_RLC_TX_NO + SLF_RLC_24_BIT + SLF_MAC_3_AES128 + SLF_ENC_VAES128;
	secuInfo.u32RLC = 0x00000001;

	sec_convertToSecure(&msgNonSec, &msgSec, &secuInfo);

	while(1)
	{
	 	CLR_WDT();
	}

	\endcode 
	
	    						   	
    \sa sec_convertToNonsecure
	**************************************************************************************************************************/		
	SEC_RESULT  	sec_convertToSecure(MESSAGE_TYPE *mssgeNonsecure,  MESSAGE_TYPE *mssgeSecure, SECU_TYPE *secuInfo);

	/************************************************************************************************************************//*!
    Creates a security teach-in message. 
    
    \param[in]  	secuInfo  				Pointer to the security information structure.
    \param[out]  	teachInMsg	  			Pointer to the non-secure message.

	\return 		SEC_OK					Function exited correctly.
    \return 		SEC_SIZE_WRONG	    	Not enough space in the teachInMsg to place the information. 
	
	\note
	The function reads the information in the SLF byte

	\note
	secuInfo contains all the information about the secure message such as the encryption method, the presence and amount of CMAC bytes, as well as rolling code presence and amount of bytes, and key.
   	With this information the function creates the secure teach-in message.	See within #msg_send, the teach-in message example, for a description of the teach-in message structure. 

	\note
	The current rolling code stored under the #SECU_TYPE structure is sent. The rolling code stored in #SECU_TYPE is not incremented.

	\note
	The function assigns the choice code #RADIO_CHOICE_SEC_TI to the teachInMssge->u8Choice field.

    						   	
    \sa sec_createCMAC, sec_AES128enc
	**************************************************************************************************************************/		
	SEC_RESULT 	sec_createTeachIn(SECU_TYPE *secuInfo, MESSAGE_TYPE *teachInMsg);
	
	/************************************************************************************************************************//*!
    From a received secure teach-in message the function generates the information for the SECU_TYPE structure. 
    
    \param[in]  	teachInMsg	  		Pointer to the non-secure message.
    \param[out]  	secInfo  			Pointer to the security information structure.

    \return 		SEC_CHOICE_WRONG	Message choice value not #RADIO_CHOICE_SEC_TI
    \return 		SEC_SIZE_WRONG		Some of the message fields contain wrong size information
    \return 		SEC_OK				Message correctly parse. Security information is now in secInfo.

	
	\note
	This function is typically implemented by the receiver. 
	The structure of type SECU_TYPE contains the necessary information (such as the key, encryption method, etc) for the decoding of received secure telegrams.
	See within the #msg_send function the teach-in message example for a description of the teach-in message structure.

	\note 
	The rolling code stored under the #SECU_TYPE structure is the expected rolling code to be received from the sender.

    						   	
    \sa sec_createTeachIn, sec_AES128enc
	**************************************************************************************************************************/		
	SEC_RESULT sec_parseTeachIn(MESSAGE_TYPE *teachInMsg, SECU_TYPE *secInfo);
	
//! @}




/*********************************************************************************************/
/************************************ TIMER1 FUNCTION PROTOTYPES ******************************/
/*********************************************************************************************/
/*!
	\addtogroup timer1_grp  timer1
	The TIMER1 module gives an interface to a 16bit HW timer which can be used for custom application purposes. \n 
	This module offers:
	- COUNTER mode - exact timing with callback functions and granularity 0.062 us pro tick using 16MHz clock.
  The counter tick can be adjusted using a 1, 2, 4  postscaler.
	- PWM mode - PWM signal generation on the SCSEDIO0 or ADIO0 or ADIO4 pin 
	
    See the source code and description of the \ref app_rssiexample for more information how the PWM works. 
    	
	\note Timer1 callback function will be called from interrupt. As all interrupts have the same priority (except the UART interrupt) 
    it is possible, that the Timer1 callback has to wait, till radio, scheduler (timer0), i/o callback or uart interrupt is executed. 
    It is not possible to guaranty a minimum time from triggering any interrupt till execution of the interrupt service routine.
	 
	\ingroup ESSL
*/ 

//! @addtogroup timer1_cfg_grp TIMER1 config parameters
//! Structure used for initialisation function of this module
//! \ingroup timer1_grp
//! @{

//http://www.keil.com/support/docs/210.htm

	//! Parameter passing index
		typedef enum 
	{	
		//! In COUNTER mode defines the number of timer ticks the timer counter resets or an interrupt is generated when the callback function is enabled. \n In PWM mode this parameter defines the PWM signal periode
		IDX_TIMER1_PERIOD=0,	
		//! In COUNTER mode the postscaler increases the timer period value
		IDX_TIMER1_POSTSCALER,
		//! In COUNTER mode not used, in PWM mode is the PWM signal dutycycle
		IDX_TIMER1_DUTYCYCLE,
		//! Enabling or disabling PWM mode - when PWM mode is disabled the timer is in COUNTER mode
		IDX_TIMER1_MODE
	} TIMER1_PARAM_IDX;                                    

//! @}


//! @addtogroup timer1_fn_grp TIMER1 functions
//! \copydetails timer1_grp
//! \ingroup timer1_grp
//! @{

	/************************************************************************************************************************//*!
    Sets all the timer1 parameters
    
    \param[in]  	*pu16Param	  			Pointer to the list of parameters to set. See #timer1_param[]
    \param[in]  	u8ParamToSet	  		It has to be #SET_ALL_PARAM to set all parameters in the list
    \return 		-
    						   	
    \sa timer1_setConfig, TIMER1_PARAM_IDX
	**************************************************************************************************************************/		
	void timer1_init(uint16 *pu16Param, uint8 u8ParamToSet);

	/************************************************************************************************************************//*!
    Sets function pointer for callback function in interrupt and enables the callback interrupt generation
    
    \param[in]  	*pu16FnPtr	  			Pointer to the callback function which will be called when timer1 generates an interrupt
    \return 		-
    						   	
    \sa timer1_enableCB
	**************************************************************************************************************************/		
	void timer1_initCB(void code *pu16FnPtr);

	/************************************************************************************************************************//*!
    Enables or disables callback when timer1 generates an interrupt
    
    \param[in]  	u8Enable	  			\ref TRUE, callback enabled, \ref FALSE, callback disabled
    \return 	-

	\note
	Do not stay in the callback function too long (not more than 100 us because that takes too much time away from the schedule)
	
	\note
	The callback function will be called during an interrupt! Do not call other API functions than io_getDigital or io_getPort  in callback function.
	Do not switch the registerbank. Do not use overlaying and optimizing in callback function.

	\note
	If you did not initialised callback function pointer and you enable callback function, then the interrupt occurs, but
	function cannot be called and interrupt returns without function. Program will not crash, but resources are used.

	\code

	//define the callback function
	void callback()
	{
		...	  // stay not too long
	}
	
	void yourFunction()
	{
		timer1_init(timer1_param, SET_ALL_PARAM);  // initialise timer
		timer1_initCB(&callback);                  // set pointer to callback function ?? Typcast (void*) ??? Report 7.11.08 FB
		timer1_enableCB(TRUE);	                   // enable callback
		timer1_enable(TRUE);                       // start Timer1
		isr_genInit(TRUE);						   // This is necessary to enable the general interrupt
		.....
		timer1_enableCB(FALSE);                    // temporary disable callback
		.....
		timer1_enableCB(TRUE);                     // and now enable callback
		.....
		timer1_enableCB(FALSE);                    // finally disable callback
		timer1_enable(FALSE);                      // stop Timer1
		isr_genInit(FALSE);						   // and if necessary disable timer1 interrupt and external interrupts!
	}

	\endcode
    						   	
    \sa timer1_initCB
	**************************************************************************************************************************/		
	void timer1_enableCB(uint8 u8Enable);

	/************************************************************************************************************************//*!
    Enables or disables function of timer1 (in both COUNTER and PWM mode)
    
    \param[in]  	u8Enable	  			\ref TRUE, timer1 function enabled, \ref FALSE, timer1 function disabled
    \return 		-
    						   	
	\note
	After enabling timer1 with timer_enable(TRUE) it will run in a loop until is stopped with timer_enable(FALSE)

	\note
	This function is allowed to be used in an interrupt callback function ONLY if it is ensured that it is not used at the same time from the main program!

    \sa timer1_init
	**************************************************************************************************************************/		
	void timer1_enable(uint8 u8Enable);
	
	/************************************************************************************************************************//*!
    Returns actual counter value
    
	\param[out]  	*pu16Count	  			Pointer to store the counting value of timer1
	\return 		-
    						   	
	\note
	This function is allowed to be used in an interrupt callback function ONLY if it is ensured that it is not used at the same time from the main program!

	**************************************************************************************************************************/		
	void timer1_getTimerCounter(uint16 *pu16Count);

	/************************************************************************************************************************//*!
    Resets actual counter value
    
	\param  	-
	\return 	-
    						   	
	\note
	This function is allowed to be used in an interrupt callback function ONLY if it is ensured that it is not used at the same time from the main program!

	**************************************************************************************************************************/		
	void timer1_resetCounter();

	/************************************************************************************************************************//*!
	Sets one timer1 parameter
	
	\param[in]  	*pu16Param	  			Pointer to the list of parameters to set. See #time_param[]
	\param[in]  	u8Index			  		Index of parameter to set. See #TIME_PARAM_IDX
	\param[in]  	u16NewValue			 	The parameter value
	\return 		-
									   	
    \sa timer1_init, TIMER1_PARAM_IDX
	**************************************************************************************************************************/		
	#define timer1_setConfig(pu16Param, u8Index,u16NewValue) pu16Param[u8Index]=u16NewValue;	timer1_init(pu16Param,u8Index);
//! @}


/*********************************************************************************************/
/************************************ TIME FUNCTION PROTOTYPES ******************************/
/*********************************************************************************************/

/*! 
	\addtogroup time_grp  time
	The TIME module uses a HW system timer that generates a system tick at a fixed rate of one tick per millisecond.  Using this system tick a 
	system scheduler is implemented. Each millisecond the execution of the application is interrupted and the schedule takes over the CPU.
	The schedule executes and one of the SYSTEM-TASKS.\n\n
  
  For more information make sure to read \ref scheduler_page

	\n
	Because most of the radio routines are called from the schedule when linking TIME module the radio module will be also linked to your application.
	\n\n

	The TIME module offers the application the possibility to build it's own SW timers with the precission of 1ms. Using 
	the wait function the application can stop it's execution for a certain ammount of time. The system timer is based on 32bit counter.

	\note
	It may happen that the application receives less than half time slice of the CPU when several interrupts like Radio, UART, are executed one after another.

	\note
	The system timer is based on a 32bit counter therfore the counter will overflow once <b>every 49 days</b>. 
	
	\note
	Some critical functions (like the FLASH write functions in the \ref mem_grp module) needs to disable all the interrupts inclusive 
	the interrupt from the system timer. When the functions execution time is longer than 1ms it may happen that a system tick is lost. 
	Use these functions rarely or calculate with a system tick loss!
	
	\note 
	If you need timing with higher resolution as 1ms use the functions from the \ref timer1_grp module.
	
	\ingroup ESSL  
*/ 


//! @addtogroup time_struct_grp TIME structures
//! Structures that are used in this module
//! \ingroup time_grp
//! @{

	//! SW timers structure
	typedef struct 
	{
		 //! Initial time (ms). Value can be stored by calling API #time_setTimerCount
		 uint32	timeInit	;
		 //! Time interval to measure (ms). Value stored by the user application
	 	 uint32	timeToCount	;
		 //! \brief Timer active flag. 1: ON ; 0: OFF.\n\n
		 //! Note: The value is written to '1' by #time_setTimerCount.\n
		 //! The value is written to '0' by #time_getTimeOut if a time-out happened.
		 uint8 	on			: 1;
		 //! \brief Time-out flag. 1: time-out ; 0: No time-out.\n\n
		 //! Note: The value is written to '1' by the #time_getTimeOut function IF a time-out is detected.\n
		 //! Therefore use the function #time_getTimeOut to poll if a time-out happened. 
		 uint8 	timeOut 	: 1;
		 //! Not used bits
		 uint8 	reserved 	: 6;
	
	} TIMER_TYPE;
//! @}

//! @addtogroup time_fn_grp TIME functions
//! \copydetails time_grp
//! \ingroup time_grp
//! @{
	/************************************************************************************************************************//*!
	Gets the sytem timer counter. 

		 \param[out]  	pu32Time	 System timer, this counter is incremented by interrupt routine every 1ms. /n
                                 Pointer needs to point to allocated memory, because in function value changes not address. 	
		 \return 	 		
									   	
	\note
	This function is allowed to be used in an interrupt callback function ONLY if it is ensured that it is not used at the same time from the main program!

	\sa time_wait, time_setTimerCount, time_getTimeOut
	**************************************************************************************************************************/		
	void time_getTime(uint32 *pu32Time);
	
	/************************************************************************************************************************//*!
    Indicates if a time-out happened in a SW timer
	
	\param[out]  	*pu8timer 		Pointer to the timer structure.  
    \return 		OK				No time-out or timer disabled	
    \return 		TIME_OUT		Time-out 	
									   	
 
	\note
	Function returns TIME_OUT again, when it was previously called with the same TIMER_TYPE and there was TIME_OUT. When this TIMER_TYPE
	is started again using #time_setTimerCount, then the timer is reset. 
	Function returns OK, when time out is still not reached. Also when timer was disabled while time out was not reached, even when
	in the meantime time out would have been reached.

    <b>Example 1:</b> \n
    This piece of code shows the standard way to implement a time-out
    \code
    TIMER_TYPE   myTimer_1;

    time_setTimerCount(&myTimer_1, 10);                  //start a count of 10ms, controlled via myTimer_1		 
    while(time_getTimeOut(&myTimer_1) == 0);    //wait for the time-out before going further.
    \endcode
    
    <b>Example 2:</b> \n
    This will NOT work
    \code
    time_setTimerCount(&myTimer_1, 10);                  //start a count of 10ms, controlled via myTimer_1
    while(myTimer_1.timeOut == 0);                       //good idea, but...		
    \endcode
    	...the <i>overflow</i> flag is only set if the #time_getTimeOut is called\n
    and a time-out happens. Since that function is not called, the flag is never set\n
    and the program waits in the loop until WDT reset.
    	
    <b>Example 3:</b> \n
    This implementation of the time-out would also work
    \code
    TIMER_TYPE   myTimer_1;
    
    time_setTimerCount(&myTimer_1, 10);                  //start a count of 10ms, controlled via myTimer_1		 
    do{
       time_getTimeOut(&myTimer_1);	
    }while(time_getTimeOut(myTimer_1.timeOut == 0);     //wait for the time-out before going further.
    \endcode
    \sa time_getTime, time_setTimerCount, time_wait
	**************************************************************************************************************************/		
	RETURN_TYPE	time_getTimeOut(TIMER_TYPE *pu8timer);
	
	/************************************************************************************************************************//*!
	 Initialises a SW timer for a time measurement 
	
    \param[in]  	*pu8timer 			Pointer to the timer structure. See #TIMER_TYPE
    \param[in]  	u32timeToCount 	Time to measure in ms.
    \return 	    void 	

    \sa time_getTime, time_wait, time_getTimeOut
	**************************************************************************************************************************/		
	void	time_setTimerCount(TIMER_TYPE *pu8timer, uint32 u32timeToCount);
	
	/************************************************************************************************************************//*!
    Performs a dummy loop for the indicated amount of ms. If the system timer is not running i.e. the isr_timer0Init was not called
	the delay is realised with standby mode waking up by short term timer.
	
    \param[in]  	u32Delay 		Amount of ms to wait.	
    \return 		- 	
									   	
    \sa time_getTime, time_setTimerCount, time_getTimeOut

	\note
	Watchdog is not cleared inside this function! This has to be handled by the application.

	\note
	If system timer is not running, 16MHz XTAL is not on and the system runs on CRCO the time_wait can have at worst case cca. 42.5% error.
	
	\note
	If the scheduler is not running (no isr_timer0) the time_wait enters the chip in standby and uses the short term timer interrupt to get out 
	from the standby. Please notice, that while standby mode the CPU clock is stopped and no UART function is given. So wakeup by UART receiving is not possible. 
	
	**************************************************************************************************************************/		
	void	time_wait(uint32 u32Delay);
	
//! @}


/*********************************************************************************************/
/************************************ UART MODULE *******************************************/
/*********************************************************************************************/
/*!
	\addtogroup uart_grp  uart
	The UART module is used for RS232 communication between the DOLPHIN IC and a HOST. 
	It provides the following features:
	- proprietary serial communication using the #uart_sendByte, #uart_getByte
	- proprietary serial communication using the #uart_sendBuffer, #uart_getBuffer
	- serial communcation using the \ref esp2_page
	
	Several baudrates are supported. 
	\note The serial character format is 8 databits, no parity, 1 stopbit.
	
    \note The UART works exclusively in CPU mode. If using UART before the application enters to a sleep mode
    make sure that all pending UART bytes has been transmitted. You can make sure by calling
    \ref uart_getRxStatus function. 
	
	\ingroup ESSL
*/

//! @addtogroup uart_cfg_grp UART config parameters
//! UART initialization parameters. The first enumeration member = 0, the next = 1, etc
//! \ingroup uart_grp 
//! @{

	//! UART initialization parameter indexes
	typedef enum
	{
		//! Baudrate
		IDX_BAUD = 0,
		//! RX ring buffer size [ro]
		IDX_RX_RING_SIZE,
		//! TX ring buffer size [ro]
		IDX_TX_RING_SIZE
	} UART_PARAM_IDX;

	//! UART speed codes
	typedef enum
	{
		//! Speed at 4800 bauds
		BAUD_4800  = 0xCF,
	 	//! Speed at 9600 bauds
		BAUD_9600  = 0x67,
		//! Speed at 19200 bauds
		BAUD_19200 = 0x33,
		//! Speed at 38400 bauds
		BAUD_38400 = 0x19,
		//! Speed at 57600 bauds
		BAUD_57600 = 0x10,	  
	
	} BAUD_TYPE;

//! @}


//! @addtogroup uart_telegram_struct_grp Serial Telegram Structures
//! Structures that are used in UART module
//! \ingroup uart_grp 
//! @{


	//! Telegram ORG codes applies to ESP2 AND ESP3 telegram only
	typedef enum
	{
	 	//! RPS telegram	
		RADIO_ORG_RPS = 0x5,
		//! 1BS telegram
		RADIO_ORG_1BS = 0x6,			
		//! 4BS telegram
		RADIO_ORG_4BS = 0x7,			
		//! HRC telegram 			
		RADIO_ORG_HRC = 0x8,			
		//! SYS telegram 			
		RADIO_ORG_SYS = 0x9,
	} ORG_TYPE;

	//! UART telegram types codes
	typedef enum
	{
		//! Receive radio telegram:  	AIR->DOLPHIN->HOST
		RRT = 0x00,
		//! Transmit radio telegram: 	HOST->DOLPHIN->AIR
		TRT = 0x03,
		//! Receive command telegram  	DOLPHIN->HOST
		RCT = 0x04,
		//! Transmit command telegram:	HOST->DOLPHIN
		TCT = 0x05,
	} HSEQ_TYPE;

	//!Macro for EPM processing
	#define CREATE_EPM(t, param)			t.raw.bytes[t.cmd.u5Length+2] = param.p_rx.u8SubTelNum;     \
											t.raw.bytes[t.cmd.u5Length + 3 ] = param.p_rx.u8Dbm;        \
                                            t.raw.bytes[t.cmd.u5Length + 4 ] = 0;                       \
                                            t.raw.bytes[t.cmd.u5Length + 5 ] = 0;                       \
                                            t.raw.bytes[t.cmd.u5Length + 6 ] = 0;                       \
											t.cmd.u5Length = t.cmd.u5Length + 5;						\


	//! Telegram structure used for UART transmission - ESP2 protocol
	typedef union {
		//! Serial telegram byte without structure.
		struct raw
		{
			uint8  bytes[UART_MAX_LENGTH];
		} raw;

		//! RRT/TRT/RCT/TCT telegram structure
		struct cmd 
		{			
			uint8		u8Synch1;
			uint8		u8Synch2;
			uint8 	 	u5Length	: 5; 		//! Header with length byte. The byte is calculated from ORG until last checksum byte. Whole telegram length is + 3 (synch1, synch2, HEADER)
			HSEQ_TYPE 	u3Hseq		: 3; 	
			ORG_TYPE	u8Org;
			uint8		u8Bytes[UART_MAX_LENGTH - 4];		//! checksum is the last byte of the data	
    			
		}cmd;

	} TEL_SERIAL_TYPE;	

	
    //! Packet structure (ESP3)
    typedef struct
    {
    	uint16	u16DataLength;	         //! Amount of raw data bytes to be received. The most significant byte is sent/received first
    	uint8	u8OptionLength;			 //! Amount of optional data bytes to be received
    	uint8	u8Type;					 //! Packe type code
    	uint8	*u8DataBuffer;			 //! Packe type code

    } PACKET_SERIAL_TYPE;

	//! Packet type (ESP3)
	typedef enum
	{
		PACKET_RESERVED 			= 0x00,	//! Reserved
		PACKET_RADIO 				= 0x01,	//! Radio telegram
		PACKET_RESPONSE				= 0x02,	//! Response to any packet
		PACKET_RADIO_SUB_TEL		= 0x03,	//! Radio subtelegram (EnOcean internal function )
		PACKET_EVENT 				= 0x04,	//! Event message
		PACKET_COMMON_COMMAND 		= 0x05,	//! Common command
		PACKET_SMART_ACK_COMMAND	= 0x06,	//! Smart Ack command
		PACKET_REMOTE_MAN_COMMAND	= 0x07,	//! Remote management command
		PACKET_PRODUCTION_COMMAND	= 0x08,	//! Production command
		PACKET_RADIO_MESSAGE		= 0x09	//! Radio message (chained radio telegrams)
	} PACKET_TYPE;
	
	//! Response type
	typedef enum
	{
		RET_OK 					= 0x00, //! OK ... command is understood and triggered
		RET_ERROR 				= 0x01, //! There is an error occured
		RET_NOT_SUPPORTED 		= 0x02, //! The functionality is not supported by that implementation
		RET_WRONG_PARAM 		= 0x03, //! There was a wrong parameter in the command
		RET_OPERATION_DENIED 	= 0x04, //! Example: memory access denied (code-protected)
		RET_USER				= 0x80	//! Return codes greater than 0x80 are used for commands with special return information, not commonly useable.
	} RESPONSE_TYPE;
	
	//! Common command enum
	typedef enum
	{
		CO_WR_SLEEP			= 1,	//! Order to enter in energy saving mode
		CO_WR_RESET			= 2,	//! Order to reset the device
		CO_RD_VERSION		= 3,	//! Read the device (SW) version / (HW) version, chip ID etc.
		CO_RD_SYS_LOG		= 4,	//! Read system log from device databank
		CO_WR_SYS_LOG		= 5,	//! Reset System log from device databank
		CO_WR_BIST			= 6,	//! Perform Flash BIST operation
		CO_WR_IDBASE		= 7,	//! Write ID range base number
		CO_RD_IDBASE		= 8,	//! Read ID range base number
		CO_WR_REPEATER		= 9,	//! Write Repeater Level off,1,2
		CO_RD_REPEATER		= 10,	//! Read Repeater Level off,1,2
		CO_WR_FILTER_ADD	= 11,	//! Add filter to filter list
		CO_WR_FILTER_DEL	= 12,	//! Delete filter from filter list
		CO_WR_FILTER_DEL_ALL= 13,	//! Delete filters
		CO_WR_FILTER_ENABLE	= 14,	//! Enable/Disable supplied filters
		CO_RD_FILTER		= 15,	//! Read supplied filters
		CO_WR_WAIT_MATURITY	= 16,	//! Waiting till end of maturity time before received radio telegrams will transmitted
		CO_WR_SUBTEL		= 17,	//! Enable/Disable transmitting additional subtelegram info
		CO_WR_MEM			= 18,	//! Write x bytes of the Flash, XRAM, RAM0 ….
		CO_RD_MEM			= 19,	//! Read x bytes of the Flash, XRAM, RAM0 ….
		CO_RD_MEM_ADDRESS	= 20,	//! Feedback about the used address and length of the config area and the Smart Ack Table
		CO_RD_SECURITY		= 21,	//! Read security informations (level, keys)
		CO_WR_SECURITY		= 22,	//! Write security informations (level, keys)
		CO_WR_LEARNMODE		= 23,	//! Set/Reset controller learn mode
		CO_RD_LEARNMODE		= 24,	//! Get controller learn mode state
		CO_WR_SECUREDEVICE_ADD = 25,//! Add secure device to controller
		CO_WR_SECUREDEVICE_DEL = 26,//! Delete secure device from controller
		CO_RD_SECUREDEVICE_BY_INDEX = 27,	//! Read teached in secure devices by index
		CO_WR_MODE = 28,	//! Sets the gateway transceiver mode
		CO_RD_SECUREDEVICE_COUNT = 29,	//! Read number of teached in secure devices
		CO_RD_SECUREDEVICE_BY_ID = 30,	//! Check, if secure device with given Id is teached in
	} COMMON_COMMAND_TYPE;
	
	//! SmartAck command enum
	typedef enum
	{
		SA_WR_LEARNMODE		=1,	//Set/Reset Smart Ack learn mode
		SA_RD_LEARNMODE		=2,	//Get Smart Ack learn mode state
		SA_WR_LEARNCONFIRM	=3,	//Used for Smart Ack to add or delete a mailbox of a client
		SA_WR_CLIENTLEARNRQ	=4,	//Send Smart Ack Learn request (Client)
		SA_WR_RESET			=5,	//Send reset command to every SA sensor
		SA_RD_LEARNEDCLIENTS=6,	//Get Smart Ack learned sensors / mailboxes
		SA_WR_RECLAIMS		=7,	//Set number of reclaim attempts
		SA_WR_POSTMASTER	=8,	//Activate/Deactivate Post master functionality
	} SMARTACK_COMMAND_TYPE;
	
	//! Event enum
	typedef enum
	{
		SA_RECLAIM_NOT_SUCCESSFUL	= 0x01,	//Informs the backbone of a Smart Ack Client to not successful reclaim.
		SA_CONFIRM_LEARN			= 0x02,	//Used for SMACK to confirm/discard learn in/out
		SA_LEARN_ACK				= 0x03,	//Inform backbone about result of learn request
		CO_READY					= 0x04,	//Inform backbone about operational readiness
		CO_EVENT_SECUREDEVICES		= 0x05, //Inform backbone about a secure device
	} EVENT_TYPE;

//! @}

//! @addtogroup uart_fn_grp UART functions
//! \copydetails uart_grp
//! \ingroup uart_grp
//! @{

	/************************************************************************************************************************//*!
	Sets the RS232 parameters
	
	\param[in]  	*pu8Param	  			Pointer to the list of parameters to configure the UART. See #uart_param[]
	\param[in]  	u8ParamToSet	  		It has to be #SET_ALL_PARAM to configure all UART parameters	
	\return 		-									   	
	
	\sa uart_setConfig, uart_PARAM_IDX
	**************************************************************************************************************************/		
	void uart_init(uint8 *pu8Param, uint8 u8ParamToSet);

	/************************************************************************************************************************//*!
	Sets one RS232 parameter
	
	\param[in]  	pu8Param	  			Pointer to the list of parameters to configure the UART. See #uart_param[]
	\param[in]  	u8Index			  		Index of parameter to set. See #uart_PARAM_IDX
	\param[in]  	u8NewValue			 	The parameter value. 
	\return 		-
								   	
	\sa uart_init                                                                 
	**************************************************************************************************************************/		
	#define uart_setConfig(pu8Param, u8Index, u8NewValue)	pu8Param[u8Index]=u8NewValue; uart_init(pu8Param,u8Index);	

	
	/************************************************************************************************************************//*!
	 Reads a byte from the UART rx buffer interface. The interface is configured with the uart_init function.
	
	\param[out]  *pu8Byte		Pointer where the received byte is stored.
	\return	OK					Byte in RX buffer
	\return NO_RX_BYTE			No byte in RX buffer
					
    \note The pointer to the byte or buffer has to reside in XDATA

	\sa uart_sendByte
	**************************************************************************************************************************/		
	RETURN_TYPE uart_getByte(uint8 *pu8Byte);


	/************************************************************************************************************************//*!
	 Sends a byte to UART tx buffer interface. The interface is configured with the uart_init function.
	
	\param[in]	pu8Byte			Byte to send.
	\return		OK				Byte sucessfully send.
	\return 	BUFF_FULL		No space left in UART tx buffer.
					
	\sa uart_getByte
	**************************************************************************************************************************/		
	RETURN_TYPE uart_sendByte(uint8 u8Byte);
	
	/************************************************************************************************************************//*!
	 Receive several bytes through the UART interface. If the number of bytes to be received is bigger than bytes available in Rx
	 buffer the function returns with NO_RX_BYTE.
	
	\param[out] 	*pu8Buffer					Pointer to receive buffer
	\param[in]  	u8NumBytes					Number of bytes to receive
	\return			OK							Bytes receive through UART stored in pu8Buffer.
	\return			NO_RX_BYTE					There are no/not enought bytes in the intern receive buffer.
	
    \note The pointer to the byte or buffer has to reside in XDATA
					
	\sa uart_sendBuffer
	**************************************************************************************************************************/		
	RETURN_TYPE uart_getBuffer(uint8 *pu8Buffer, uint8 u8NumBytes);

	/************************************************************************************************************************//*!
	 Sends several bytes through the UART interface. If the number of bytes to be sent is bigger than the available space in Tx
	 buffer the function returns with BUFF_FULL.
	
	\param[in]  	*pu8Buffer					Pointer to the first byte to send
	\param[in]  	u8NumBytes					Number of bytes to transmit
	\return  		OK							Bytes to send through UART/SPI stored in the tx buffer.
	\return		    BUFF_FULL					No space found in the uart tx buffer. Bytes not sent.

    \note The pointer to the byte or buffer has to reside in XDATA
					
	\sa uart_getBuffer
	**************************************************************************************************************************/		
	RETURN_TYPE uart_sendBuffer(uint8 *pu8Buffer, uint8 u8NumBytes);

	/************************************************************************************************************************//*!
	 Gets a telegram using the EnOcean Serial protocol2 (ESP2.0 - \ref esp2_page).
	
	\param[out]  	*pTel			    Pointer to the telegram structure where to store the telegram
	\return			OK             		New telegram
	\return 		NO_RX_TEL			No new telegram.
	\return 		NOT_VALID_CHKSUM	Received ESP2 serial telegram has an invalid checksum
	
	
	\note	The receiving of the telegram is executed paralel to the application. It is possible that the function returns NO_RX_TEL but it already receives and modifies
    few bytes in the pTel variable. Therefore if a blocking receiving is required use the function in a while statement. See blocking and non blocking example
    for more details.

    \note The pointer to pTel has to reside in XDATA

	\note This function adds the 0xA5 and 0x5A synch bytes to the telegram structure sent i.e the tel->cmd.u8Synch1; tel->cmd.u8Synch2;
        

    Example 1: \n
    Blocking receiving of telegram. The application has to wait until a telegram is received 
    
    \code
	while (uart_getTelegram(pTel) != OK);
	//... process pTel ...
     \endcode
 
    Example 2: \n
    Nonblocking receiving of telegram. The application can do other processing during the serial telegram is receiving 
    
    \code
	if (uart_getTelegram(pTel) == OK)
	{
	   //... process telegram ...
    }
	
    //... do some other code processing but be sure not to use pTel .... 
    \endcode
 
	\sa uart_sendTelegram, misc_serialToRadio, misc_radioToSerial	
	**************************************************************************************************************************/		
	RETURN_TYPE uart_getTelegram(TEL_SERIAL_TYPE *pu8Tel);
	
	/************************************************************************************************************************//*!
	 Sends a UART telegram using the EnOcean Serial protocol2 (ESP2.0 - \ref esp2_page).
	
	\param[in]  	*pu8Tel			Pointer to the telegram to send
	\return			OK				Telegram sent 
	\return 		BUFF_FULL		No space found in the uart tx buffer. Telegram not sent.

    \note The pointer to pTel has to reside in XDATA

    Example 1: \n
    Sending an RCT telegram with 2 data bytes
    \code
    mainInit();
    sTel.cmd.u3Hseq = RCT;	
	sTel.cmd.u8Org = (ORG_TYPE)OK_SYS_WR;    
  
    //fill uart telegram with data
	for (i=0; i<DATA_SIZE; i++)
			sTel.cmd.u8Bytes[i]=i;

    //add 2 because of org and checksum	
    sTel.cmd.u5Length = DATA_SIZE + 2;    

    for (i=0; i<14;i++)
        while (uart_sendTelegram(&sTel) != OK);
    while(1);
    \endcode

    Example 2: \n
    Converting a radio telegram to a serial telegram
    \code
    // Telegram types
    TEL_RADIO_TYPE	rTel;
    TEL_SERIAL_TYPE	sTel;
    mainInit();
    radio_enableRx(1);
    while (1)
    {
        // Handle radio to uart traffic
        if (radio_getTelegram(&rTel, NULL) == OK)
        {
        	io_togDigital(ADIO_0);
        	misc_radioToSerial(&rTel,&sTel);
        	uart_sendTelegram(&sTel);
        }
    }
    \endcode

						
	\sa uart_getTelegram, misc_serialToRadio, misc_radioToSerial
	**************************************************************************************************************************/		
	RETURN_TYPE uart_sendTelegram(TEL_SERIAL_TYPE *pu8Tel);

	/************************************************************************************************************************//*!
	 Retrieve the status of UART TX buffer.
	
	\param[out]  	pu8TxBytesToSend Pointer to status byte		
	\return			-
					
	\note
	This function is allowed to be used in an interrupt callback function ONLY if it is ensured that it is not used at the same time from the main program!

	\sa uart_init, uart_getBuffer, uart_sendBuffer	
	**************************************************************************************************************************/		
	void uart_getTxStatus(uint8 *pu8TxBytesToSend);

	/************************************************************************************************************************//*!
	 Retrieves the status of UART RX buffer.
	
	\param[out]  	pu8RxBytesReceived Pointer to status byte			
	\return			-
					
	\note
	This function is allowed to be used in an interrupt callback function ONLY if it is ensured that it is not used at the same time from the main program!

	\sa uart_init, uart_getBuffer, uart_sendBuffer	
	**************************************************************************************************************************/		
	void uart_getRxStatus(uint8 *pu8RxBytesReceived);

	/************************************************************************************************************************//*!
	 Retrieves a packet with the EnOcean serial protocol3 (ESP3) from the UART.
	
	\param[out]  	pPacket             Address of the received packet			
	\param[in]  	u16MaxLength        Maximal number of data + optional bytes allowed to be received : protocol sync byte, length fields, type, CRC8D, CRC8H are excluede from the count. 
	\return			OK                  Correct packet received
	\return			TIME_OUT            The time between two bytes exceeded 100ms
	\return			NOT_VALID_CHKSUM    Not valid data checksum
	\return			NO_RX_TEL           No complete packet received
	\return			NEW_RX_BYTE         Transmission in progress. The pPacket.u8DataBuffer is being updated
    \return         OUT_OF_RANGE		The telegram data + optianal length	is either 0 or bigger then the allocated packet buffer.		
	
    \note
	Since the EO3000I RAM is 2kB, this is the maximum value of the pPacket buffer, where you store the incoming bytes.
    Therefore, the maximum value that you should set to u16MaxLength is 2kB.

    \note
	The OK code is received only once when the whole packet has been received.
	If the data transmission is in progress the function returns NEW_RX_BYTE. In this state the pPacket.u8DataBuffer can not be modified by application. Changing the pPacket.u8DataBuffer during transmission would cause corrupt data.   
    
	
	\note
    The function starts to measure the time between bytes from the moment that
    it detects a sysnchronizing 0x55 code. If the time between bytes exceeds 100ms, the functions will return an error code TIME_OUT. 
    It is important that you read this function more often than every 100ms. Otherwise the function returns a time-out although bytes have been received

	\note
    Since the function makes use of time resources, in particular the time_setCounter() 
    and time_getTimeOut() functions, enable the system time control in the init macro INIT_EO3000I. 
    There, the functions #pwr_enableXTAL() and #pwr_selectXTAL() must be called, to start the 16MHz external crystal
    The isr_timer0Init() function must also be called to configure and start the system time interrupts.   
      
	\note
    In case that the Header CRC8 is false the function returns NO_RX_TEL.

	\note
    If the data length of the received packet is bigger than u16MaxLength, 
    only the first u16MaxLength bytes are loaded to the packet. 
    The next byte is considered the CRC8D of the telegram
    

    Example 1: \n
    Blocking receiving of telegram. The application has to wait until a telegram is received 
    
    \code
	while (uart_getPacket(pPacket) != OK);
	//... process pPacket ...
     \endcode
 
    Example 2: \n
    Non-blocking receiving of packet. The application can do other processing during the serial packet is receiving 
    
    \code
	if (uart_getTelegram(pPacket) == OK)
	{
	   //... process packet ...
    }
	
    //... do some other code processing but be sure not to use pPacket .... 
     \endcode

	\sa uart_init, uart_getBuffer, uart_getBuffer, uart_sendPacket, pwr_enableXTAL, pwr_selectXTAL, isr_timer0Init	
	**************************************************************************************************************************/		
	RETURN_TYPE uart_getPacket(PACKET_SERIAL_TYPE *pPacket, uint16 u16MaxLength);

	/************************************************************************************************************************//*!
	 Sends a serial packet with the EnOcean serial protocol3 (ESP3) through the UART.
	
	\param[in]  	pPacket             Address of the received packet			
	\return			OK                  Correct packet received
	\return			OUT_OF_RANGE        The length fields are both 0
					
	\note
    The function waits for available space in the UART tx FIFO buffer, if the buffer happens to be full.
    Once there is available place it copies there the next byte to send. 
    It repeats the process of waiting and copying until all bytes in pPacket have been copied to the UART tx FIFO buffer.

	\note
	The function is returned when the last byte has been copied to the UART tx buffer. 
    At this moment, the last byte has not been sent completely through the serial port.

	\sa uart_init, uart_getBuffer, uart_getBuffer, uart_getPacket	
	**************************************************************************************************************************/		
	RETURN_TYPE uart_sendPacket(PACKET_SERIAL_TYPE *pPacket);
//! @}


/*********************************************************************************************/
/************************************ MISC FUNCTION PROTOTYPES ******************************/
/*********************************************************************************************/
/*!
	\addtogroup misc_grp  misc
	The MISC group contains miscellaneous functions and tools like:
	- random number generation
	- ERP to ESP2 conversion and vice-vers
	- system log management
	
	\ingroup ESSL
*/ 


//! @addtogroup misc_fn_grp MISC functions
//! \copydetails misc_grp
//! \ingroup misc_grp
//! @{

	/************************************************************************************************************************//*!
	Miscalaneous API initialisation. This function enables all the interrupt - it has to be called as the last init function.
		
	\param		-
	\return		OK				Telegram conversion succesful
					
	**************************************************************************************************************************/		
	void misc_init();


	/************************************************************************************************************************//*!
	 Converts a serial telegram to a radio telegram. Converts org->choice, sets the radio telegram length parameter, transforms DATA,
	 ID and STATUS byte.
	
	\param[in]  	*pu8serial			Pointer to a serial telegram
	\param[out]		*pu8radio			Pointer to a radio telegram.
	\return			OK					Telegram conversion succesful
					
	\sa misc_radioToSerial, \ref esp2_page, \ref erp_page	
	**************************************************************************************************************************/		
  	RETURN_TYPE misc_serialToRadio(TEL_SERIAL_TYPE *pu8serial, TEL_RADIO_TYPE *pu8radio);
	
	/************************************************************************************************************************//*!
	 Converts a radio telegram to a serial telegram. Converts choice->org, sets the radio telegram length parameter, transforms DATA,
	 ID and STATUS byte.
	
	\param[in]		*pu8radio			Pointer to a radio telegram.
	\param[out]  	*pu8serial			Pointer to a serial telegram
	\return			OK					Telegram conversion succesful
					
	\sa misc_serialToRadio, \ref esp2_page, \ref erp_page	
	**************************************************************************************************************************/		
	RETURN_TYPE misc_radioToSerial(TEL_RADIO_TYPE *pu8radio, TEL_SERIAL_TYPE *pu8serial);

	/************************************************************************************************************************//*!
	 Converts a serial packet to a radio telegram. 
	
	\param[in]  	*pu8packet			Pointer to a packet
	\param[out]		*pu8radio			Pointer to a radio telegram.
	\param[out]  	*pu8param			Pointer to a radio telegram parameter structure.
	\return			OK					Telegram conversion succesful
	\return			NOT_VALID_TEL		Conversion failed. The packet does not contains radio telegram or the data length mismatch.

	\sa misc_radioToPacket, \ref esp3_page, \ref erp_page	
	**************************************************************************************************************************/		
	RETURN_TYPE  misc_packetToRadio(PACKET_SERIAL_TYPE *pu8packet, TEL_RADIO_TYPE *pu8radio, TEL_PARAM_TYPE *pu8param);
	
	/************************************************************************************************************************//*!
	 Converts a radio telegram to a serial packet. Copies radio telegram + telegram param to packet data buffer.
	
	\param[in]		*pu8radio			Pointer to a radio telegram.
	\param[in]  	*pu8param			Pointer to a radio telegram parameter structure.
	\param[out]  	*pu8packet			Pointer to a packet
	\return			OK					Telegram conversion succesful
	\return			NOT_VALID_TEL		Conversion failed. The radio telegram length mismatch.

	\note
	Make sure that the size of the data buffer of the packet is at least 27 bytes
					
	\sa misc_packetToRadio, \ref esp3_page, \ref erp_page	
	**************************************************************************************************************************/		
	RETURN_TYPE misc_radioToPacket(TEL_RADIO_TYPE *pu8radio, TEL_PARAM_TYPE *pu8param, PACKET_SERIAL_TYPE *pu8packet);

	/************************************************************************************************************************//*!
	 Initialises pseudo random bit stream. Function uses u16Seed to initialise the function's random-number generator, 
	 giving it a new seed value. 
	
	\param[in]		u16Seed		Seed value for pseudo-random generator.
	\return			-

	\note
	This function need not to be called, because it will automaticaly be called when using misc_init(). But then always the same
	series of random values will be created after reset.
	If you want to have different random series you have to call this function once with your own seed value, which should be 
	always different. 
	In an ULP application with deep sleep you can f.e. save the seed in RAM0 and create the next seed with random value. Example:

	\code

	// Do not forget to initialise ram0 seek variable with sensefull init value at first power on reset!

	typedef struct 
	{	
		//! Seed value for next initialisation of random generator	
		union 
		{
			uint16	u16Seed;
			struct
			{
				uint8	u8SeedHi;
				uint8	u8SeedLo;
			} seed;
		} seed;	
	} RAM0_SHADOW;
	RAM0_SHADOW			data	sctgram0;
	
	mem_readRAM0((uint8*)&sctgram0, 0x00, sizeof(RAM0_SHADOW));
	// Initialise random generator and next seed
	misc_rndInit(sctgram0.seed.u16Seed);
	do
	{
		sctgram0.seed.seed.u8SeedLo = misc_rndGet()+19;
		sctgram0.seed.seed.u8SeedHi = misc_rndGet()+7;
	} while (sctgram0.seed.u16Seed == 0);
	mem_writeRAM0((uint8*)&sctgram0, 0x00, sizeof(RAM0_SHADOW));

	\endcode
			
	\note
	The first random value, which is returned by #misc_rndGet, is always the lower byte
	of the given seed value! When using the upper algorithm to calculate a new seed	value
	at each reset, then it could be, that the seed values will repeat after a while, depending
	of the amound of #misc_rndGet calls. To be sure, always to start with a really random
	value, it is recommended, to use analog measurement noise to feed the #misc_rndInit
	function using the returned values of #io_ulpMeasAnalog function, or, if radio is
	switched on, the io_getAnalogRnd function to use as random generator. \n
	If it is no problem to always generate the same series of random numbers, the function
	#misc_rndInit should never be used.
						
	\note
	This function is allowed to be used in an interrupt callback function ONLY if it is ensured that it is not used at the same time from the main program!

	\sa misc_rndGet	
	**************************************************************************************************************************/		
	void misc_rndInit(uint16 u16Seed);

	/************************************************************************************************************************//*!
	 Returns an 8-bit random number. If you want different series of random values after reset, it is recommended to call 
	 misc_rndInit function first with different seek values to initialise the random number generator. 
	
	\param		-		
	\return		uint8		random value 

	\note
	This function will also be used by the Dolphin API itself!
					
	\note
	This function is allowed to be used in an interrupt callback function ONLY if it is ensured that it is not used at the same time from the main program!

	\sa misc_rndInit.
	**************************************************************************************************************************/		
	uint8 misc_rndGet();

	/************************************************************************************************************************//*!
	 Returns the 32-bit unique ID of this Chip
	
	\param[out]		*pu32ID		Pointer to ID
	\return			-
					
	\note
	This function is allowed to be used in an interrupt callback function ONLY if it is ensured that it is not used at the same time from the main program!

	**************************************************************************************************************************/		
	void misc_getId(uint32 *pu32ID); 

	/************************************************************************************************************************//*!
	 Checks the 32-bit unique ID of this Chip with param.
	
	
	\param[in]		*u32ID		Pointer to ID
	\return		    uint8		true (1)  match
	                            false (0) no match
	\note
	This function is allowed to be used in an interrupt callback function ONLY if it is ensured that it is not used at the same time from the main program!
					
	**************************************************************************************************************************/		
	uint8 misc_isLocalId(uint32 *u32ID);

	/************************************************************************************************************************//*!
	 This function gets the available stack space in bytes. This value shows not the current stack space but the information 
	 how many bytes were already used by the stack pointer during the application execution. This function can be used for debug 
	 purposes in the APP. If this value is very small -> around 3,4 bytes there is a high risk of stack overflow.  Prior using this 
	 function the interanl data has to be initialised to 0x00. This can be set up in the startup.a51 file.
	
	\param[out]		*pu8StackAval		Pointer to the number of available bytes for stack.
	\return			-
					
	\note
	This function is allowed to be used in an interrupt callback function ONLY if it is ensured that it is not used at the same time from the main program!

	\sa \ref stack_anal
	**************************************************************************************************************************/		
  	void misc_getStackReserve(uint8 *pu8StackAval);

	/************************************************************************************************************************//*!
	Reads the system log from the FLASH LOG_AREA or Program & data area to the XDATA.
	
	\param[in]		pu16SrcAddr		FLASH address of either a LOG_AREA or Program & data area. 
	\param[out]		pu8DstAddr		XDATA destination address of a buffer
	\param[in]      u8Size			Size of the log area.
	
	\code
    //this example initialises the SystemLog, i.e. it copies the values from the Flash to the XDATA buffer.
	misc_logInit((uint8 code*)LOG_ADDR, u8APIErrorLog, sizeof(u8APIErrorLog));
	\endcode
				
	\sa misc_logSet8, misc_logSet16, misc_logChks, \ref system_log
	*************************************************************************************************************************/		
	#define misc_logInit(pu16SrcAddr, pu8DstAddr, u8Size)	\
		memcpy(pu8DstAddr, pu16SrcAddr, u8Size);

	/************************************************************************************************************************//*!
	Compares the checksum over API and Application Log (APP LOG) buffers for changed entries.
	
	\param[in]		pu8APPErrLog	Pointer to application log buffer
	\param[in]		u8SizeAPPErrLog	Size of application log buffer
	\return	    	uint8		true (1)  at least one of the entries changed
	                            false (0) no entry changed

	\note
	This function calculates only with one byte checksum, so when exactly 256 entries changed, the function returns 0.
	
	\sa misc_logInit, misc_logSet8, misc_logSet16, \ref system_log
	*************************************************************************************************************************/		
	uint8 misc_logChks(uint8 *pu8APPErrLog, uint8 u8SizeAPPErrLog); 

	/************************************************************************************************************************//*!
	Increments the 8bit counter in the sytem log. The log numbers will be incremented until 0xFE.
	
	\param[in]		pu8Log			XDATA address of the system log 
	\param[in]		u8LogCode		Log code from a ERRLOG type structure
					
	\sa misc_logSet8, misc_logSet16, \ref system_log
	**************************************************************************************************************************/		
	#define misc_logSet8(pu8Log, u8LogCode)		   \
		if (pu8Log[u8LogCode]!=0x00) pu8Log[u8LogCode]--;			

	/************************************************************************************************************************//*!
	Decrements the 16bit log counter in the system log. The log numbers will be decremented until 0x0000.
	
	\param[in]		pu8Log		XDATA address of the system log 
	\param[in]		u16LogCode		Log code from a ERRLOG type structure
					
	\sa misc_logSet8, misc_logSet16, \ref system_log
	**************************************************************************************************************************/		
	#define misc_logSet16(pu8Log, u16LogCode)			   \
		if ((uint16 xdata*)(pu8Log+u16LogCode) != 0x0000 ) 		\
			((uint16 xdata*)(pu8Log+u16LogCode))[0]--;    

	/************************************************************************************************************************//*!
	Saves the system log from XDATA into the FLASH LOG_AREA.
	
	\param[in]		pu8TmpBuf		Pointer to temporar buffer of 256 bytes for LOG_AREA. 
	\param[in]		pu8APPErrLog	Pointer to application log buffer
	\param[in]		u8SizeAPPErrLog	Size of application log buffer
	
	\code
	typedef enum 
	{
	    ERR_APP8 = 0,
	    ERR_APP16_L,    
	    ERR_APP16_H,        
	    APP_ERR_MEM_SIZE,
	        
	} APP_ERRLOG;

	LOG_AREA code  log_read  _at_ LOG_ADDR;
	LOG_AREA xdata log_buff;
	uint8 u8APPErrLog[API_ERR_MEM_SIZE];					 

    //read API system log from Flash, if you want to reset the log counter skip this step
    misc_logInit(log_read.val.u8APIErrLog, u8APIErrLog, API_ERR_MEM_SIZE);
    //read APP system log from Flash, if you want to reset the log counter skip this step
    misc_logInit(log_read.val.u8ReservedAPP, u8APPErrLog, APP_ERR_MEM_SIZE);
	//calculate first time the checksum of both log buffers for later decision if saving is needed
	misc_logChks(u8APPErrLog, APP_ERR_MEM_SIZE);
	....
    //Anytime we can store an log in the application system log 8 or 16 bit
    misc_logSet8(u8APPErrLog,ERR_APP8);
    misc_logSet16(u8APPErrLog,ERR_APP16_L);
	....
	//At the end of the program the logs, which are in XDATA have to be transfered to FLASH
	misc_logSave(&log_buff, &u8APPErrLog[0], APP_ERR_MEM_SIZE);

	\endcode
				
	\sa misc_logSet8, misc_logSet16, \ref system_log
	*************************************************************************************************************************/		
    	#define misc_logSave(pu8TmpBuf, pu8APPErrLog, u8SizeAPPErrLog)	\
			if (misc_logChks(pu8APPErrLog, u8SizeAPPErrLog) != 0) { \
    		memcpy(pu8TmpBuf.val.u8APIErrLog, u8APIErrLog, API_ERR_MEM_SIZE); \
    		memcpy(pu8TmpBuf.val.u8ReservedAPP, pu8APPErrLog, u8SizeAPPErrLog); \
    		mem_writeFlash((uint8*)pu8TmpBuf, LOG_ADDR, sizeof(LOG_AREA)); }

//! @}

/*********************************************************************************************/
/************************************ SPI FUNCTION PROTOTYPES ********************************/
/*********************************************************************************************/
/*!
	\addtogroup spi_grp  spi
	The SPI module is used for communication between the DOLPHIN IC and a HOST using the SPI protocol. The SPI module supports
	communication where the DOLPHIN acts as SPI-Master and the HOST acts SPI-Slave. 
    \n\n
    The SPI module supports packet transmission. The size of one packet can be 1,2,3 or 4 bytes. The CS can't be modified during packet transmission. The maximum speed of
    one packet transmission is 2Mbit. Between two packets a certain processing delay is needed called interpacket delay.
    \nThe size of the interpacket delay depends on the following factors:
    - duplex mode (half duplex smaller delay)
    - packet size (the bigger packet, the more delay between packets)
    - other active interrupts

    The interpacket delay + the packet transmission speed gives the real SPI communication speed. The following table
    shows the real SPI speed for different packet size @ 2MHz packet clock speed.
    	
	\image html spispeed.PNG SPI Tx speed @ 2MHz SPI clock and different packet size and duplex mode and worst case interrupt calculation

	\n\n
	The initialization of the SPI module  is done through Dolphin Studio. The generated settings are saved to the file EO3000I_CFG.h.
	\n\n
	The SPI interfaces uses the following pins:
	- SCSEDIO0 - Chip select (CS)
	- SCLKDIO1 - SPI clock (CLK) 
	- WSDADIO2 - Master In Slave Out (MISO)
	- RSDADIO3 - Master Out Slave In (MOSI) 
    
    \n\n
    There are two possibilities how control CS (configured with spi_init with the parameters). 
    - manual CS mode
    - automatic CS mode
    
    To manualy controll the CS the function #spi_setCS is used.  In automatic CS the CS raised and lowered between each packet automaticly.
	
	\image html spi_arch.PNG SPI initialization between DOLPHIN and HOST
    
    \note
    In order to determine the real SPI communication speed, be sure to measure the interpacket delay for data that is larger than 4 byte
    and also calculate with the duration of interrupts that can make the interpacket delay larger. 

	
	\note
	Be sure when using both SPI and UART module that the UART module is not configured for pins WSDADIO2, RSDADIO3.
	\ingroup ESSL
*/ 

//! @addtogroup spi_cfg_grp SPI config parameters
//! SPI initialization parameters. 
//! \ingroup spi_grp
//! @{
	//! SPI initialization parameter indexes
	typedef enum 
	{	
		IDX_CCR = 0,
		IDX_CDR
	} SPI_PARAM_IDX;
//! @}

//! @addtogroup spi_struct_grp SPI structures and constants
//! Structures that are used in SPI module
//! \ingroup spi_grp 
//! @{
    
    //! SPI Packet size
	typedef enum 
	{	
	    BYTE_1 = 1,
		BYTE_2 = 2,
        BYTE_3 = 3,
        BYTE_4 = 4,
	} SPI_PACKETSIZE;

    //! Duplex communication mode
    typedef enum
    {
        //! Fullduplex
        FULL = 0x00, 
        //! Halfduplex Tx only
        HALF_TX = 0x60,
        //! Halfduplex Rx only
        HALF_RX = 0x20,
    } DPLX_MODES;
//! @}



                
//! @addtogroup spi_fn_grp SPI functions
//! \copydetails spi_grp
//! \ingroup spi_grp
//! @{

	/**********************************************************************************************************************************//*!
	Initialises the SPI module. 
	
	\param[in] *pu8Param Pointer to parameter array
	
	\return 	-
	                                       
	
	\note
	To generate the parameters for spi_init use DolphinStudio (set the GPIO to SPI in the DolphinStudio).
		
	\sa spi_setCS, spi_getSendBuffer
	************************************************************************************************************************************/ 
	void spi_init(uint8 *pu8Param);

    /**********************************************************************************************************************************//*!
    Sets the CS bit to the given value 
    
    \param[in]      u1Val \ref TRUE, the CS line will be HIGH, \ref FALSE, the CS line will be LOW 
    
    \return 		- 
                                           

    Example 1: \n
    This function is for controlling the CS line in SPI interface 
    
     \code
	spi_init(spi_param);
	spi_setCS(FALSE);
	spi_getSendBuffer(u8SendBuff, u8NoSend, u8GetBuff, u8NoGet);
	spi_setCS(TRUE);
     \endcode
     
    \sa spi_init, spi_getSendBuffer
    ************************************************************************************************************************************/ 
	void spi_setCS(bit1 u1Val);

    /**********************************************************************************************************************************//*!
    Sends and gets data to/from SPI interface. 
    
    \param[in]  *pu8SendBuff  Pointer to character buffer to send, NULL if no characters to send
	\param[out] *pu8GetBuff   Pointer to character buffer to receive, NULL if no characters to get
	\param[in]  u8NoBytes     Number of characters to send/receive, note that this value has to be aligned to u8PacketSize
    \param[in]  u8PacketSize  One transmitted packet size which is transmitted at once (can be 1 - 4 bytes)
    \param[in]  u8Dplx        Duplex mode, full duplex, half duplex rx or half duplex tx can be selected

    \return 	INVALID_PARAM If the u8NoBytes is not aligned to u8PacketSize
    \return 	OK            If there was no problem with SPI
                                           

    Example 1: \n
    Make a full duplex SPI communication, send/receive 12 characters with manual CS and packet size 4
    
     \code
    spi_init(spi_param);
	spi_setCS(FALSE);
    spi_getSendBuffer(u8SendBuffer, u8GetBuffer, 12, BYTE_4, FULL);
	spi_setCS(TRUE);
     \endcode
     
    Example 2: \n
    Make a half duplex Tx SPI communication, send/receive 12 characters with auto CS and packet size 1
    
    \code
    //the auto CS has to be configured in the spi_param with DolphinStudio
	spi_init(spi_param);
    spi_getSendBuffer(u8SendBuffer, NULL, 12, BYTE_1, HALF_TX);
    \endcode
     

    \note
	To generate the parameters for spi_init use DolphinStudio (set the GPIO to SPI in the DolphinStudio)
	and copy generated spi_param to EO3000I_CFG.h. Do not forget to copy io_param too.
    
    \note
	You are responsable for resetting and setting CS pin in manual CS mode.
	
    \note
    If using half duplex communication set puffer pointer not used to NULL.

    \note
    Interrupts in the system (i.e. system tick) can cause a gap between the SPI bytes transmission. This gap can be in worst
    case around 1.3ms. 
    
    \sa spi_init, spi_setCS
    ************************************************************************************************************************************/ 
	RETURN_TYPE spi_getSendBuffer(uint8 *u8SendBuff, uint8 *u8GetBuff, uint8 u8NoBytes, SPI_PACKETSIZE u8PacketSize, DPLX_MODES u8Dplx);



//!@}


/*********************************************************************************************/
/************************************ REPEATER FUNCTION PROTOTYPES ********************************/
/*********************************************************************************************/
/*!
	\addtogroup rep_grp  rep
	The REP module is used for the repeater functionality of Dolphin. For more information be sure to read \ref repeater_page
	The initialization of the REP module  is done through Dolphin Studio. The generated settings are saved to the file EO3000I_CFG.h.

	\note
	By default, repeating functionality is switched OFF.
	
	\note
    For the repeater module to work the scheduler has to run. For more information read \ref time_grp module. 


	\ingroup ESSL
*/ 

//! @addtogroup rep_cfg_grp REP config parameters
//! REP initialization parameters. 
//! \ingroup rep_grp
//! @{
	//! REP initialization parameter indexes
	typedef enum 
	{	
		IDX_REP_ENABLE = 0,
		IDX_REP_LEVEL
	} REP_PARAM_IDX;
//! @}


//! @addtogroup rep_fn_grp REP functions
//! \copydetails rep_grp
//! \ingroup rep_grp
//! @{

	/**********************************************************************************************************************************//*!
	Initialises the REP module. 
	
	\param[in]  *pu8Param Pointer to parameter array
	\param[in]  u8ParamToSet Index of parameters to set.
	
	\return 	-
	                                       
	
	\note 
	To generate the parameters for rep_init use DolphinStudio.

	\note
	If you do only use repeating and no other application, you periodicaly have to call radio_getTelegram to remove the telegrams from buffer.
	
	************************************************************************************************************************************/ 
	void rep_init(uint8 *pu8Param, uint8 u8ParamToSet);

//! @}



// All the visible modules group definitions are done here so that when the library is compilled this groups stay
// The modules that are used only inside the api are not visible here (i.e. proc_)

/**
 *  @ingroup ESSL
 */



/************************* API INTERFACE RELATED TYPES/STRUCTURES/PARAMETERS ***************************/

#define DEBUG_ERRRAWTEL

//! @addtogroup sys_fn_grp System defines
//! System defines !!! DON'T MODIFY  !!!
//! \ingroup ESSL
//! @{
//! This define is for backward compatibility. Dolphin Studio generates this define
#define UART_INIT(param1, param2)	uart_init(param1, param2);					
//! This define is for backward compatibility with projects that included ISD51 support. ISD51 debugging is not suported due to unstability issues. Dolphin Studio generates this define  
#define	ISD51_INIT(u8Baud)		  



//! @}


	/*********************************************************************************************/
	/************************************ SMART ACKNOWLEDGE FUNCTION PROTOTYPES ********************************/
	/*********************************************************************************************/
	/*!
		\addtogroup smack_grp  smart ack
		The smack module enables Smart Acknowledge functionality for Controller, Repeater and Sensor in Dolphin API. Functions handle all time and energy critical
		parts of communication. The functions for line powered Smack Acknowledge actors are same. Controller and Repeater use the same functions, but Controller can
		addtioanlly learn Sensors so it uses special functions for this purpose. 
		\n\n
		The initialization of the SMACK module is done through Dolphin Studio. The generated settings are saved to the file EO3000I_CFG.h.
		\n\n
		\note
		By default, smack functionality is switched OFF.
		\note
		If the repeater is active and has enabled SmartACK postmaster functionality, telegrams located in the mailbox of the postmaster 
        are not available for the application. These telegrams are filtered on the lower API layers and are not 
        received by radio_getTelegram.
         
		\ingroup ESSL
	*/ 

//! @addtogroup smack_cfg_grp Smart Acknowledge initial parameters
//! Smack initialization parameters. 
//! \ingroup smack_grp
//! @{	

	//! Smart Ack initialization parameter indexes
	typedef enum 
	{	
		//! Maximum number of mailboxes [ro]
		IDX_MAILBOX_COUNT = 0,		
		//! Flash address for mailbox storage  [ro]
		IDX_MAILBOX_FLASH_ADDR
	} SMACK_PARAM_IDX;

//! @}


//! @addtogroup smack_fn_grp Smart Acknowledge functions
//! \copydetails smack_grp
//! \ingroup smack_grp

//! @{

	/*!	 \name Reclaim choice encoded defines
		Defines are used for checking in radio_tx for reclaim telegrams.
	 */
 /*!\{*/
	//***********************************RECLAIM TELEGRAM DEFINES

		//!First byte of encoded Reclaim Choice. 
		#define RECLAIM_CHOICE_ENCODED_B0 	0xA2
		//!Second byte of encoded Reclaim Choice.
		#define RECLAIM_CHOICE_ENCODED_B1 	0xD0
	//***********************************RECLAIM TELEGRAM DEFINES END
/*!\}*/

	/*!	 \name Reclaim telegram defines
		For faster Reclaim telegram processing we access telegram data with pointer and relative possition. Defines are constant.
		Also masks to separate reclaim type from mailbox index are listened.
	 */
/*!\{*/
	//***********************************RECLAIM TELEGRAM DEFINES
		//!Possition of the reclaim type.
		#define REC_TYPE_POS		 		1
		//!Possition of the Source Id.
		#define REC_SRC_ID_POS				2
		//!Mask to get relcaim type
		#define REC_TYPE_MASK				0x80
		//!Mask to get mailbox index
		#define REC_MBIDX_MASK				0x7F
	//***********************************RECLAIM TELEGRAM DEFINES	END
/*!\}*/

	/*!	 \name Learn request telegram defines
		For faster Learn Request telegram processing we access telegram data with pointer and relative possition. Defines are constant.
	*/
/*!\{*/
	//***********************************LEARN REQUEST TELEGRAM DEFINES
		//!Possition of the learn request code.
		#define LRN_REQ_REQ_CODE_POS 		1
		//!Possition of the EEP.
		#define LRN_REQ_EEP_POS				5
		//!Possition of the RSSI.
		#define LRN_REQ_RSSI_POS			6 	
		//!Possition of the Candidate Id.
		#define LRN_REQ_CANDIDATE_POS		7 	
		//!Possition of the source Id.
		#define LRN_REQ_SRC_ID_POS 			(RADIO_DEC_LENGTH_SM_LRN_REQ-LEN_SRCID_STAT_CHCK)		
		//!Possition of the status field
		#define LRN_REQ_STATUS_POS			(RADIO_DEC_LENGTH_SM_LRN_REQ-2)
	//***********************************LEARN REQUEST TELEGRAM DEFINES	END
/*!\}*/

	/*!	 \name Learn answer telegram defines
		For faster Learn answer telegram processing we access telegram data with pointer and relative possition. Defines are constant.
		Learn answer can encapsulate Learn Reply or Learn Acknowledge. 
	*/
/*!\{*/
	//***********************************LEARN REQUEST TELEGRAM DEFINES
		//!Possition of the message index.
		#define LRN_ANS_MSG_IDX_POS				1	
		//!Possition of the response time.
		#define LRN_ANS_RESPONSE_TIME_POS		2
		//!Possition of Acknowledge code
		#define LRN_ANS_ACK_CODE_POS			4
		//!Possition of Sensor Id in Learn Reply
		#define LRN_ANS_REP_SENSOR_ID_POS 		5
		//!Possition of Mailbox Index in Learn Acknowledge
		#define LRN_ANS_ACK_MB_IDX_POS	 		5	
	//***********************************LEARN REQUEST TELEGRAM DEFINES	END
/*!\}*/

	/*!	 \name Learn request code defines 
		In Learn Request telegram Learn Request code share one byte with Manufacturer Id. For accessing values we use bite masks and bit operations.
	 */
/*!\{*/
	//***********************************LEARN REQUEST CODES DEFINES
		//!Request code mask of the sharing byte in learn request telegram with Manufacturer Id.  		
		#define REQ_CODE_MASK 				0xF8
		//!Manufacturer Id mask of the sharing byte in learn request telegram with request code.  		
		#define MAN_CODE_MASK				0x07
		//!Default request code send by Sensor.
		#define SENSOR_DEFAULT_REQ_CODE		0x1F
	//***********************************LEARN REQUEST CODES END
/*!\}*/

	/*!	 \name Priority flags defines
		Priority of the Post Master Candidate is evaluated by a hierarchically priority system. So the Flag bits have also a priority.
		The highest priority has the already post master flag. At the end the highest priority is taken as result. In evaluation process
		the flags are used to set the properities: 
		<ol>
			<li>
			ALREDY POST MASTER / CANDIDATE
			</li>
			<li>
			PLACE FOR NEXT MAILBOX / NO PLACE FOR NEXT MAILBOX
			</li>
			<li>
			GOOD RSSI / NOT GOOD RSSI
			</li>
			<li>
			LOCAL / REMOTE
			</li>
		</ol>

		\note TRUE - 1 means the first choice

	 */
/*!\{*/

	//*****************************PRIORITY FLAGS
		#define PF_LOCAL				0x1
		#define PF_RSSI_OK				0x2
		#define PF_PLACE_OK				0x4
		#define PF_PM					0x8
		#define PF_REP					0x10
	//*****************************PRIORITY FLAGS END
/*!\}*/

	/*!	 \name Learn acknowledge code defines
		Learn Acknowledge code is separated into main and second part. The main part idetify the operation and the second gives additional infromation
		about it. For accessing main and second part we use bit masks and bit operations.
	*/
/*!\{*/
	//***********************************LEARN ACKNOWLEDGE CODE
		//!Main acknowledge code for Learn In.
		#define ACK_CODE_LEARN_IN					0x00
		//!Main acknowledge code for discard Learn In.
		#define ACK_CODE_LEARN_DISCARD				0x10
		//!Main acknowledge code for Learn Out.
		#define ACK_CODE_LEARN_OUT					0x20
		//!Mask for main acknowledge code.
		#define ACK_CODE_MAIN_MASK					0xF0
		//!Mask for second acknowledge code.
		#define ACK_CODE_SECOND_MASK				0x0F
	//***********************************LEARN ACKNOWLEDGE CODES
/*!\}*/

	/*!	 \name Discard reason defines
		Discard reason gives more infromation about the reason why was the LearnIn discarted. It is saved in second part of a Learn Acknowledge code.
	 */
 /*!\{*/
	//***********************************DISCARD REASON
		//!Second acknowledge code for discard Learn In - EEP not accepted.
		#define ACK_CODE_EEP_NOT_ACCEPTED			0x01
		//!Second acknowledge code for discard Learn In - declared Post Master has no place for next MailBox.
		#define ACK_CODE_PM_NO_PLACE				0x02
		//!Second acknowledge code for discard Learn In - Controller has no place to Learn In next Sensor.
		#define ACK_CODE_CONTROLLER_NO_PLACE		0x03
		//!RSSI was not good enough.
		#define ACK_CODE_NO_GOOD_RSSI				0x04

	//***********************************DISCARD REASON END

/*!\}*/

	/*!	 \name learn mode defines
		Learn modes of smart ack controller.
	 */
 /*!\{*/
	//***********************************DISCARD REASON
		//!Simple learnmode is used, when only Smart Ack Controller should be selected as postmaster. All learn requests received by repeater will be ignored.
		#define SIMPLE_LEARNMODE					0x00
		//!Advanced learnmode is used, when also repeater can be selected as postmaster. But when Controller reaches sensor, controller is selected.
		#define ADVANCED_LEARNMODE					0x01
		//!Anvanced learnmode select repeater is used, when always the best available repeater will be selected as postmaster. Controller is only selected, when no repeater is in system.
		#define ADVANCED_LEARNMODE_SELECT_REPEATER	0x02

	//***********************************DISCARD REASON END

/*!\}*/


	/*!	 \name Other defines
	 */
 /*!\{*/
		//!Code for no MailBox found.
		#define NO_MAILBOX_FOUND	 	0xFF
		//! Maximum value of response time [ms] - in case of LRN reclaim it must be at least 500
		#define	MAX_RESPONSE_TIME 550	
/*!\}*/
		//!Smart Acknowledge result used in Controller and Sensor application to indicate return or status.
		typedef enum
		{
			SMACK_OK	 = 0,  	//!<Ok message.
			NO_MORE_MAILBOX ,	//!<No more free MailBox available.
			FLASH_FAILURE,		//!<Flash write or read failure.
			NO_RECLAIM_MESSAGE,	//!<No reclaim message received.
			COLLECTING,			//!<Module is collecting learn request telegrams.
			RESULT_READY,		//!<Result from learn request collecting process is ready.
			NO_RESULT,			//!<No result from learn request collecting process is ready.
			LEARN_ON_SIMPLE,	//!<Module is in simple Learn Mode.
			LEARN_ON_ADVANCED,	//!<Module is in advanced Learn Mode.
			LEARN_TIMEOUT,	  	//!<Module just switched of the Learn Mode because of learn period timeout.
			OTHER_MESSAGE       //!<Received other radio telegram while reclaim 	
		}SMACK_RESULT;

		//!Signal telegram message index.
		typedef enum
		{
			RESERVED	 = 0,			//!<RESERVED.
			MAILBOX_EMPTY,				//!<Smart acknowledge - reclaimed mailbox is empty.
			MAILBOX_DOES_NOT_EXIST,		//!<Smart acknowledge - reclaimed mailbox does not exists.
			RESET						//!<Smart acknowledge - rest learn process.
			 	
		}SIGNAL_INDEX;

		//!Smart acknowledge reclaim type.
		typedef enum
		{
		  	LEARN_RECLAIM = 0,	//!<Learn reclaim type.
			DATA_RECLAIM 		//!<Data reclaim type.
			
		}SMACK_RECLAIM_TYPE;

		//!Smart acknowledge learn answer telegram message index.
		typedef enum
		{
		  	LRN_REP = 1,		//!<Learn reply message index.
			LRN_ACK 			//!<Learn acknowledge message index.
			
		}LRN_MSG_IDX;

		//!Smart acknoweldge mailbox handling task.
		typedef enum
		{
			NOTHING	 = 0,		//!<Do nothing.
			ADD_MB ,			//!<Add MailBox.
			DELETE_MB			//!<Delete MailBox.
				 	
		}SMACK_TASK;

		//!Smart acknowledge learn result structure. It is used to Controller to evalute learn result.
		typedef struct
		{
			uint8		 	u8Priority ;	//!<Priority of the PostMaster candidate.
			uint8 			u8ManId_byte1;	//!<Manufacturer Id byte 1 of the learned Sensor.
			uint8		 	u8ManId_byte0;	//!<Manufacturer Id byte 0 of the learned Sensor.
			uint8			u8EEP_byte2;	//!<EEP byte 2 of the learned Sensor.
			uint8			u8EEP_byte1;	//!<EEP byte 1 of the learned Sensor.
			uint8			u8EEP_byte0;	//!<EEP byte 0 of the learned Sensor.
			uint8  			u8dBm;			//!<Rssi in dBm of the Learn Request telegram received by candidate.
			uint32 			u32CandidateId;	//!<Id of Candidate for PostMaster for learned Sensor.
			uint32 			u32SensorId;	//!<Id of the learned Sensor.
			uint8			u8HopCount;	//!<Hop count from candidate to controller.
						
		}LEARN_RESULT;

		//*****************************MAILBOX STRUCTURES
		//!Strucutre for memory occupied by MailBoxes in flash.
		typedef struct
		{
			uint32 u32SensorId;		//!<MailBox Sensor Id.
			uint32 u32ControllerId;	//!<MailBox Controller Id.
			uint8  u8MBIndex;		//!<Index of the MailBox.
		
		}MAILBOX_FLASH;

		//!Strucutre for memory occupied by MailBox in xram.		
		typedef struct
		{
			uint32 u32Timer;					//!<Timer for MailBox. Used for MailBox period.
			uint8  u8Length;					//!<Length of saved Mail.
			uint8  u8Bytes[RADIO_BUFF_LENGTH];	//!<Saved Mail for Sensor. Default length defined by radio buffers.		
		}MAILBOX_XRAM;
	//*****************************MAILBOX STRUCTURES END
							   	
		//! Variable determines the MailBox that should be writen/deleted as next. It is a intern variable of smack module. It is only avaivable because of Remote Management.
		extern volatile MAILBOX_FLASH 	xdata			gMbfAct;		
		//! Variable determines operation that should be perfomed with #gMbfAct. It is a intern variable of smack module. It is only avaivable because of Remote Management.
		extern volatile SMACK_TASK		xdata			gSmTask;
		extern volatile uint8			xdata			u8gGERssiDbm;


	/************************************************************************************************************************//*!
    Function initialises the Smart Acknowledge mode to work. 
    
    \param[in]  	*pu8Param	  			  Pointer to the list of parameters to set. See #SMACK_PARAM_IDX
    \param[in]  	u8ParamToSet	  		It has to be #SET_ALL_PARAM to set all parameters from SMACK_PARAM_IDX of the list
    \return 		-
    
    
	 \note
  	When using smack mode be sure you use the isr_timer0_smack_PM_Init() function instead of isr_timer0Init().

    
	\sa isr_timer0_smack_PM_Init, SMACK_PARAM_IDX
 	**************************************************************************************************************************/			
 	void smack_init(uint16 *pu16Param, uint8 u8ParamToSet);

 	/************************************************************************************************************************//*!
    Function ensures Smart Acknowledge functionality. Nearly all functionality is implemented in interrupt, but some operations
	like writing to flash memory must be performed in user application. The function is used by the smack repeaters only (Devices that
	do not what to learn in Smack Sensors). The devices never go to active Smack Learn mode.
    
    \param[in]  *pu8ShadowBuffer			Memory used for buffering flash operations. It is used only temporary and it must point to 
                                    		xram memory space with size of one flash page - 256 b.
                                    
    \return     SMACK_OK	  			  	Process executed commnon operations. Status in Learn Off.                                
	\return     FLASH_FAILURE		  		The embedded flash operation failed. - FLASH ERROR
	\return		NO_MORE_MAILBOX		  		The embedded flash operation could not write next MB, because no free memory. Should not 
											occure, bsc. SMACK handels memory.    


    \note
    The execution time of the function is usualy short, but if flash write operation is needed it can execute much longer.
    
    \note
    To read some global variables that are accessed also by interrupt functions the function temporary disables TIMER0 interrupt irq.

       
    \sa mem_writeFlash
 	**************************************************************************************************************************/					
	SMACK_RESULT smack_process(uint8 *pu8ShadowBuffer);
	
	
	 	/************************************************************************************************************************//*!
    Function ensures Smart Acknowledge functionality. Nearly all functionality is implemented in interrupt, but some operations
	like writing to flash memory must be performed in user application. The function is also an interface for user application 
	to get Smart Acknoweldge module status. The status is passed as return value. The function makes time - out for learn mode.
	It must be called repeatelly, but specially when learn mode is active. The function calls the #smack_process function.
    
    \param[in]      *pu8ShadowBuffer		Memory used for buffering flash operations. It is used only temporary and it must point to 
                                    xram memory space with size of one flash page - 256 b.
    \return     SMACK_OK	  			  Process executed commnon operations. Status in Learn Off.    
    \return     COLLECTING				  Smart acknowledge module is collecting Learn request messages now.
										                It is important now to limit radio sending operations, because they can avoid receving
										                Learn request messages.
    \return     RESULT_READY		    Smart Acknowledge has finished collecting and evaluating Learn Request messages. 
										                The result can be fetched with smack_getLearnResult.
    \return     LEARN_ON_SIMPLE		  The module is in simple learn mode.
    \return     LEARN_ON_ADVANCED	  The module is in advanced learn mode.
	\return     FLASH_FAILURE		  The embedded flash operation failed. - FLASH ERROR
	\return		NO_MORE_MAILBOX		  The embedded flash operation could not write next MB, because no free memory. Should not 
										occure, bsc. SMACK handels memory.	


    \note
    The execution time of the function is usualy short, but if flash write operation is needed it can execute much longer.
    
    \note
    To read some global variables that are accessed also by interrupt functions the function temporary disables TIMER0 interrupt irq.

    
    \sa mem_writeFlash \sa smack_process
 	**************************************************************************************************************************/	
	SMACK_RESULT smack_processController(uint8 * pu8ShadowBuffer);

  	/************************************************************************************************************************//*!
  	Function checks if the module is not collecting Learn Request messages and then it disables learn mode.
      
  	\return     SMACK_OK		Learn mode is disabled.
  	\return     COLLECTING	  	Learn mode can not be disabled because it collects learn request messages.
  
  	**************************************************************************************************************************/			
  	SMACK_RESULT smack_LearnOff();
  
  	/************************************************************************************************************************//*!
    Function activates the learn mode and activates the learn period timer.
    
    \param[in]      u8Extended		If TRUE enables the advanced learn mode.
	\param[in]		u32TimeOut		Time-Out for the learn mode in ms. When time is 0 then default period of 60 000 ms is used.
	
	\note
	Default Learn mode is simple. That means that only Controller can be Post Master, all repeater are ignored. In advanced learn mode
	also Repeater can become Post Master.
  	
  	**************************************************************************************************************************/			
  	void smack_LearnOn(uint8 u8Extended,uint32 u32TimeOut);

  	/************************************************************************************************************************//*!
    Function is only used in SmartACK sensor and sends one DATA or LEARN RECLAIM telegram and then reclaims the answer. 
    The receiver will be switched on, till
    the answer is received or a timeout of 5 ms elapsed. After the function returns, the receiver is disabled.
    
    \param[in]    u8ReclaimType		    LEARN_RECLAIM = send learn reclaim; DATA_RECLAIM = send data reclaim			  	
    \param[in]    u7MailBoxIdx		    Mailbox index for the mailbox to reclaim
    \param[out]	  *pRxRadioTelegram		Radio structure of reclaimed telegram
    \param[out]	  *pu8TelParam		    Parameter structure of reclaimed telegram			
    \return       SMACK_OK			    Radio telegram received and copied in radio and parameter structures
    \return	      NO_RECLAIM_MESSAGE	There was no or a not to me addressed reclaim message received    
	
    \note
    As this function does only perform one reclaim cycle, it can be called as much as the application wants to try reclaims.

	\note
	Due to the smart acknowledge concept it is not possilbe to use #smack_reclaim with scheduler operation. When using
	timer0 as scheduler, it is not necessary to use smart ack for communication, because the system is line powered.

    <b>Maximum execution time:</b> 8 ms \n
    
	
    \sa radio_getTelegram
  	**************************************************************************************************************************/					
	SMACK_RESULT smack_reclaim(SMACK_RECLAIM_TYPE u8ReclaimType, uint8 u7MailBoxIdx, TEL_RADIO_TYPE *pRxRadioTelegram, TEL_PARAM_TYPE *pu8TelParam);

  	/************************************************************************************************************************//*!
    If there is any, then the function copies the Learn Result from learn request process.
    
	\param[out]      *pAppLrnRes		Learn result structure where the learn result about the last learn request process should be copied. #LEARN_RESULT					  	    						
	\return    		 SMACK_OK		Learn result is copied.	  	
	\return    		 NO_RESULT	  	Learn result is not copied, because non is available.
	  
	\note
	To read some global variables that are accessed also by interrupt functions the function temporary disables TIMER0 interrupt irq.
	  
	**************************************************************************************************************************/				  		
	SMACK_RESULT smack_getLearnResult(LEARN_RESULT *pAppLrnRes);

  	/************************************************************************************************************************//*!
  	Function finalises learn process. It is called also when LearnIn, LearnOut. It handels all MailBox operations and eventually declares PostMaster.
  	The parameter u8AckCode signals the wished final operation (i.e. LearnIn, LearnOut). It is possible to delete mailboxes manually.  
  
  	\param[in]      *pLrnRes	   		The Learn Result that was obtained from smack_getLearnResult. #LEARN_RESULT
  	\param[in]      u8AckCode			Learn Acknowledge code indicates the Controller decision about the learn finalization.
  	\param[in]      u16ResponseTime		Response time for sensor in ms in which the controller can prepare the data and send it to the postmaster. Only actuall if learn finalization is LearnIn.
  
  	\note
  	In order the funtion maybe calls radio_sendTelegram function - to transmit learn reply.
  
	\note
	You can delete Smart Acknowledge mailboxes by two ways manualy:
	- If the mailboxes are local (no repeater in system) the easiest way is to delete the flash page where the smart Acknowledge mailboxes are stored.
	- If the mailboxes are local or in a repeater, the best thing is to use the smack_finalizeLearn function to learn out the sensors. It is nessessary to call smack_processController function after each call to execute the learn out.
	
  	\sa smack_getLearnResult, radio_sendTelegram
  	**************************************************************************************************************************/			
	void smack_finalizeLearn(LEARN_RESULT *pLrnRes,uint8 u8AckCode,uint16 u16ResponseTime);

	/************************************************************************************************************************//*!
    Function enables the controller to communicate with learned Sensors. It either put the telegram to local stored MailBox in case
	Controller is also Post Master. Otherwise the function sends the telegram to Post Master. The Sensor Id is in TEL_PARAM_TYPE as
	input parameter *pu8TelParam. The input parameters are like in radio_sendTelegram and the return type too. 
    
    \param[in]      *pu8TxRadioTelegram				  	
    \param[in]      *pu8TelParam						
    \return         OK 				Telegram sent. 
	\return         BUFF_FULL	 	No free Tx buffer available for transmission.
	\return	        NOT_VALID_PARAM	No Sensor Id listened. Or he telegram length in TEL_RADIO_TYPE was not set OR the u8Subtel number 
								is 0 or more than 3 OR the encapsulated ADT telegram length is bigger > 16bytes.
	\return         ID_OUT_OF_RANGE  The ID given in TEL_RADIO_TYPE structure is out of allowed range.    
	
	\note
	To send telegram the function calls radio_sendTelegram.

    \sa  radio_sendTelegram
 	**************************************************************************************************************************/			
	RETURN_TYPE 	smack_sendDataTelegram(TEL_RADIO_TYPE *pu8TxRadioTelegram, TEL_PARAM_TYPE *pu8TelParam);

//! @}





	/*********************************************************************************************/
	/************************************ REMOTE MANAGEMENT FUNCTION PROTOTYPES ******************/
	/*********************************************************************************************/
	/*!
	\addtogroup reman_grp  reman
	The Remote Management allows EnOcean devices to be configured and maintained through the air interface using 
	radio or serial telegrams. Sensors or switches shall be learned into or deleted from already installed actuators or gateways 
	which are hard to access. The Remote Management uses the SYS_EX telegrams which can be adressed using the ADT encapsulation. 

    Before using the Remote Management module be sure to read the Remote Management_V1.2.pdf specification.
       
    The initialization of the REMAN module is done through Dolphin Studio. The generated settings are saved to the file EO3000I_CFG.h. 
    
		\ingroup ESSL
	*/ 

//! @addtogroup reman_cfg_grp Remote management config parameters
//! Parameters for remote management initialization. 
//! \ingroup reman_grp
//! @{	

	 //! Paramter indexes for initalization.
	typedef enum 
	{
		//!Index of EEP Byte0 and Byte1
	    IDX_EEP_BYTE0_BYTE1=0,
		//!Index of EEP Byte2
        IDX_EEP_BYTE2,
		//!Product manufacturer
		IDX_MANUFACTURERID,
		//!Index for buffer length. It determines how much memory space the application dedicated to remote management buffer for message merging.
		//!It also determines what is the biggest message to receive.
		IDX_BUFF_SIZE,
        //! Memory code adress where the 4byte Code is saved [ro]
        IDX_CODE_ADDR,
        //! Minimum delay between two chained telegrams in message. 
        IDX_TEL_DELAY
	} RM_PARAM_IDX;
	
	//! Paramter indexes for call back function intialization.
	typedef enum
	{
		//! Index for action function call back. [ro]
		IDX_PF_ACTION_COMMAND,
		//! Index for write code function call back. [ro]
		IDX_PF_CODE_WRITE
	} RM_CALLBACKS_IDX;
    
//! @}


//! @addtogroup reman_fn_grp Remote management functions
//! \copydetails reman_grp
//! \ingroup reman_grp

//! @{

	 /*!	\name System defines
		These defines are system specific.
	 */
 /*!\{*/
 	//***********************************RM SYSTEM DEFINES
		//! Default Manufacturer ID.
		#define  RM_DEFAULTMANID	                  0x7FF
		//! Default EEP.
		#define  RM_DEFAULTEEP		                  0x000		
		//!Begin of the answer function codes.
		#define RM_ANSWER_START                       0x600
		//! Value from which rpc codes begin.
		#define RM_RPC_START                          0x200
		//! Initial value of a blank flash page.
		#define LOCK_INIT_VALUE 						  0xFFFFFFFF	
		//! Return value when user application does not do anything further.
		#define EXIT_NO_FURTHER_ANALYSIS                  0x00
	//***********************************REMAN SYSTEM DEFINES END
/*!\}*/


	 /*!	\name Enums
		Enums used in remote management module.
	 */
 /*!\{*/

	//! Learn flags for RMCC remote learn.
	typedef enum
    {
        
        START_LEARN = 0x01,         //!<Defines to enable learn mode.        
        NEXT_CHANNEL,            	//!<Defines to jump to next chanell.		        
        STOP_LEARN,                 //!<Defines to stop the actual learn mode.                
        SMACK_START_SIMPLE_LEARN,   //!<Defines to start Smart Ack simple learn mode, can be applied only on modules where SMACK is implemented.        
        SMACK_START_ADVANCED_LEARN, //!<Defines to start Smart Ack advanced learn mode, can be applied only on modules where SMACK is implemented.        
        SMACK_STOP_LEARN            //!<Defines to stop Smart Ack learn mode, can be applied only on modules where SMACK is implemented.
    }RM_LEARN_FLAG;
	
	
	
	//! Remote manager function codes
	typedef enum
	{
	  	RM_NOT_DEFINED                   = 0x00, //!<Not definet function code, represents the null value.
	  	RM_FN_UNLOCK                     = 0x01, //!<Unlock command.
	  	RM_FN_LOCK                       = 0x02, //!<Lock command.
	  	RM_FN_SET_CODE                   = 0x03, //!<Set security command.
	  	RM_FN_QUERY_ID                   = 0x04, //!<Query ID command.
	  	RM_FN_ACTION_COMMAND             = 0x05, //!<Test command.
	  	RM_FN_PING_COMMAND               = 0x06, //!<Ping command.
	  	RM_FN_QUERY_FUNCTION_COMMAND     = 0x07, //!<Query supported RPC functions command.
	  	RM_FN_QUERY_STATUS               = 0x08, //!<Query debug status of remote manager.
	  	
	  	RM_FN_REMOTE_LEARN               = RM_RPC_START + 0x01, //!<Remote learn RPC code.
	  	RM_FN_REMOTE_CLEAR               = RM_RPC_START + 0x02, //!<Remote clear RPC code, structure to be defined.
	  	RM_FN_REMOTE_WRITE               = RM_RPC_START + 0x03, //!<Remote write RPC code.
	  	RM_FN_REMOTE_READ                = RM_RPC_START + 0x04, //!<Remote read RPC code.
		RM_FN_SMACK_SETTING_READ         = RM_RPC_START + 0x05, //!<RPC for Smack query setting.
		RM_FN_SMACK_SETTING_WRITE        = RM_RPC_START + 0x06, //!<RPC for Smack write setting.
	  	
	  	RM_FN_QUERY_ID_ANS               = RM_ANSWER_START + RM_FN_QUERY_ID,    			//!<Query ID answer.
	  	RM_FN_PING_COMMAND_ANS           = RM_ANSWER_START + RM_FN_PING_COMMAND,   			//!<Ping answer. 
	  	RM_FN_QUERY_FUNCTION_COMMAND_ANS = RM_ANSWER_START + RM_FN_QUERY_FUNCTION_COMMAND,	//!<Query supported RPC functions answer.
	  	RM_FN_QUERY_STATUS_ANS           = RM_ANSWER_START + RM_FN_QUERY_STATUS,			//!<Query status answer.
	  	RM_FN_REMOTE_READ_ANS            = RM_ANSWER_START + RM_FN_REMOTE_READ,				//!<Remote read answer.
		RM_FN_SMACK_SETTING_ANS			 = RM_ANSWER_START + RM_FN_SMACK_SETTING_READ,		//!<RPC Smack query setting answer.
		RM_FN_LEARNED_SENSORS_ANS		 = RM_ANSWER_START + RM_FN_SMACK_SETTING_READ +1	//!<RPC Smack query sensor answer.
	
	}  RM_FN;
	
	
	//! Return codes from RMCC and RPC functions. Values are used in Query Status commands.
	typedef enum
	{
	  	RM_RETURN_CODE_OK              				    = 0x00, //!<OK return code.
	  	RM_RETURN_CODE_WRONG_ID	      			        = 0x01, //!<Wrong target ID code.
	  	RM_RETURN_CODE_WRONG_CODE     				    = 0x02, //!<Wrong securty code return code.
		RM_RETURN_CODE_WRONG_EEP						= 0x03, //!<Wrong EEP.
		RM_RETURN_CODE_WRONG_MANID						= 0x04, //!<Wrong Manufacturer ID.	
		RM_RETURN_CODE_WRONG_DATA_SIZE					= 0x05, //!<Function misses data to execute.
	  	RM_RETURN_CODE_NO_CODE_SET 				        = 0x06, //!<No security code set return code.	
	  	RM_RETURN_CODE_NOT_SENT				            = 0x07, //!<Answer / telegram not send.
		RM_RETURN_CODE_RPC_FAILED		  				= 0x08, //!<RPC failed.
		RM_RETURN_CODE_MESSAGE_TIME_OUT					= 0x09, //!<Previous message was chain period time-out.
	  	RM_RETURN_CODE_TOO_LONG_MESSAGE 			    = 0x0A, //!<Too long message, the sum of to transfer data extends the internal buffer.  	
		RM_RETURN_CODE_MESSAGE_PART_ALREADY_RECEIVED	= 0x0B, //!<In merge process the actual message part was already received. Indicates an possible error state.	
		RM_RETURN_CODE_MESSAGE_NOT_RECEIVED				= 0x0C, //!<Previous message was not received completly.
		RM_RETURN_CODE_ADDRESS_OUT_OF_RANGE				= 0x0D, //!<Specified address is out of range
		RM_RETURN_CODE_DATA_SIZE_EXCEEDED				= 0x0E, //!<Unable to process requested data size
		RM_RETURN_CODE_WRONG_DATA		  				= 0x0F  //!<Data are not in expected range
	} RM_RETURN_CODE;

	//! Smack read settings types - applied for the RPC RM_FN_SMACK_SETTING_READ
	typedef enum
	{
	  	MB_SETTINGS = 0x01,    				//!<Read out mail box settings.
		LEARNED_SENSORS_CONTROLLER          //!<Read out learned sensors. Only from controller.
				
	}SETTINGS_TYPE;
	
	//! Smack write settings operation types
	typedef enum
	{
	  	ADDFLASH_MB = 0x01,   				//!<Defines to add a specified Mail Box.
		DELETEFLASH_MB,                     //!<Defines to delete a specified Mail Box. 
		LEARNIN,                            //!<Defines to Learn In a specified sensor. Only controller.
		LEARNOUT                            //!<Defines to Learn Out a specified sensor. Only controller.

	}OPERATION_TYPE;

/*!\}*/
	
       
	//************************ END TYPES **********************
	
	//************************ FUNCTION PROTOTYPES ************

	/************************************************************************************************************************//*!
    Initialise the remote manager module. This function must be called before the remote manager is used. It initialises 
	the specific module variables.
    
    \param[in]  	*pu8Param	  			Pointer to the list of parameters to set. See #RM_PARAM_IDX
    \param[in]  	u8ParamToSet	  		It has to be #SET_ALL_PARAM to set all parameters from RM_PARAM_IDX of the list
    \return 		-

	\note 
	This function is using TIMER0 so make sure to call it only after isr_timer0Init!
    
	**************************************************************************************************************************/		
	void reman_init(uint16 *pu16Param,uint8 u8ParamToSet); 

	/************************************************************************************************************************//*!
  	Sets the pointer to RPC list. This information is used by query function.
	    
	\param[in]		pu16RpcList		Pointer to RPC list array
	\param[in]		u8RpcCount		Nubmer of RPCs defined in pu16RpcList 
    \return   		-

	Example:
	\code
	code uint16 reman_rpc[] = 	{
			RM_FN_REMOTE_LEARN, RM_DEFAULTMANID,
			RM_FN_REMOTE_WRITE, RM_DEFAULTMANID,
			RM_FN_REMOTE_READ,  RM_DEFAULTMANID };
	...
	reman_setRPC(reman_rpc, 3);
	\endcode
 	**************************************************************************************************************************/	
	void reman_setRPC(uint16* pu16RpcList, uint8 u8RpcCount);

	/************************************************************************************************************************//*!
    Function processes radio telegrams and produces remote management messages. If one or multiple chained SYS_EX telegrams
	was received the #reman_receiveTelegram returns OK. Then u16FnNumber is set to requected remote management function number,
	the u16DataSize is set to received message length. If the function receives RMC command (e.g. ping, query id, unlock, etc.) it is 
    processed  immediately (except Action RMCC). RPC and Action RMCC has to be processed by the application.   The SetCode RMCC is processed 
    inside the function but saving of the code has to be handled by the application (be sure to check out examples)!  \n\n
    If QueryId or Ping RMCC is received, the functions will create the answer. This answer will be send by function #reman_processSend later on, because
	a certain delay has to be inserted between chained telegrams. The reman_processSend must be called periodically in applicaiton
	loop. 
    
	\param[in] *rTel 			Received telegram.
	\param[in] *prpInput 		Input parameters structure. For more details see #TEL_PARAM_TYPE				
    \return    OK 				Remote management message received. 
	\return    NOT_VALID_PARAM	The rTel is not an SYS_EX telegram or the DestinationID of prpInput does not match .
	\return	   NO_RX_TEL		The SEQ or SourceID of rTel does not match. During running transmisson if second remote management controller 
								tries to communicate. 
	
	\note
	To send remote management messages the function reman_processSend needs to be called periodically.
	
    \sa  reman_processSend
 	**************************************************************************************************************************/			
	RETURN_TYPE reman_receiveTelegram(TEL_RADIO_TYPE *pu8RadioTel, TEL_PARAM_TYPE* pInParam, uint16 *u16FnNumber, uint16 *u16DataSize);

	/************************************************************************************************************************//*!
    This function has the same functionality as #reman_receiveTelegram except it does not process RMCC commands. This function
	should be used only in reman controller application.
    																										   
	\param[in] *rTel 			Received telegram.
	\param[in] *prpInput 		Input parameters structure. For more details see #TEL_PARAM_TYPE				
    \return    OK 				Remote management message received. 
	\return    NOT_VALID_PARAM	The rTel is not an SYS_EX telegram or the DestinationID of prpInput does not match .
	\return	   NO_RX_TEL		The SEQ or SourceID of rTel does not match. During running transmisson if second remote management controller 
								tries to communicate. 
	
	\note
	To send remote management messages the function reman_processSend needs to be called periodically.
	
    \sa  reman_processSend
 	**************************************************************************************************************************/			
	RETURN_TYPE reman_receiveTelegramController(TEL_RADIO_TYPE *pu8RadioTel, TEL_PARAM_TYPE* pInParam, uint16 *u16FnNumber, uint16 *u16RmDataSize);

	/************************************************************************************************************************//*!
    Function initialise the internal sending state machine. The telegram is sent after then by #reman_processSend function.
	It also locks the whole remote management module for sending. That means all incoming telegrams are dropped until  
	all telegrams are sent. If sending more than 4 bytes then the data is divided into multiple telegrams which are
	send with certain time difference one after another. This function should be use to answer RPC commands. The answer is
	send back to controller which send the last RPC.
	    
	\param[in] *u8Data 			Buffer where the data to be sent is stored.
	\param[in] *u16DataSize 	Length of the *u8Data field				
	\param[in] u16FunctionCode  The remote management function answer number. 					
	\param[in] u8SendWithDelay 	TRUE if the first message has to be sent with random delay.  When answering to broadcast message this has to be	TRUE. Otherwise FALSE.
    \return    OK 				The sending statemachine was intialised. 
	\return    OUT_OF_RANGE		The u16DataSize exceeded the maximal remote message length.
	
	\note
	To send remote management messages the function reman_processSend needs to be called periodically.
	
    \sa  reman_processSend
 	**************************************************************************************************************************/	
	RETURN_TYPE reman_sendMessage(uint8 *u8Data, uint16 u16DataSize, uint16 u16FunctionCode, uint8 u8SendWithDelay);

	/************************************************************************************************************************//*!
    This function has the same functionality as #reman_sendMessage but additionaly the destination ID can be specified. This function
	should be used only in reman controller application.
	    
	\param[in] *u8Data 			Buffer where the data to be sent is stored.
	\param[in] *u16DataSize 	The input parameters structure. For more details see #TEL_PARAM_TYPE				
	\param[in] u16FunctionCode  The remote management function answer number. 					
	\param[in] u16Manufacturer 	RPC function manufacturer. Default is #RM_DEFAULTMANID.				
	\param[in] u32DestinationID Destination ID.
	\param[in] u8SendWithDelay 	TRUE if the first message has to be sent with random delay.  When answering to broadcast message this has to be	TRUE. Otherwise FALSE.
    \return    OK 				The sending statemachine was intialised. 
	\return    BUFF_FULL		The u16DataSize exceeded the maximal remote message length.
	
	\note
	To send remote management messages the function reman_processSend needs to be called periodically.
	
    \sa  reman_processSend
 	**************************************************************************************************************************/	
	RETURN_TYPE reman_sendMessageController(uint8 *u8Data, uint16 u16DataSize, uint16 u16FunctionCode, uint16 u16Manufacturer, uint32 u32DestinationID, uint8 u8SendWithDelay);

	/************************************************************************************************************************//*!
  	Periodically called funtion to ensure answers to broadcast messages. The function handels the random delay whitout blocking calls.
    It is nesseccaty to call the function periodically in user application.
	    
    \return    OK 				The whole remote management message was send. 
	\return    TELEGRAM_WAIT	Waiting random before answering the broadcast or IDX_TEL_DELAY time between two chainged telegrams.
	\return	   NO_TX_TEL		There are no more telegrams to send. The remote management module is not locked for sending. 
	\return	   NEW_TX_TEL		Part of the message was actually send using radio_sendTelegram.

	\note
	After calling reman_sendMessage() the remote management message is queued to be sent. In order to to send remote management message 
	over the air it has to be split into multiple SYS_EX telegrams. This splitting and sending is handled by the reman_processSend().
	The reman_processSend() has to be called periodically and each time it checks if there is a message to be send. If there is 
	a message to be sends the reman_processSend() splits it to SYS_EX telegrams and sends it using the radio_sendTelegram().

	The reman_processSend() directly calls the radio_sendTelegram() therefore in order to send remote management message it is only 
	required to call reman_sendMessage() once and then call reman_processSend() periodically in the main loop. 
	
	In generally the remote management module (reman_* functions) can be seen as an extra layer between the application and radio_* functions.
	The remote management module provides a transformation from SYS_EX telegrams to remote management messages and vice versa.

	\note
	To send remote management messages the function reman_processSend needs to be called periodically.

    \note
    Modifying the IDX_TEL_DELAY can speed up the transmission of the chained telegrams, but the performance of the REMAN Controller
    or gateway (like TCM300) has to be considerd. I.e. The TCM300 in serial gateway mode with 9600 Baudrate can't process more than 
    58 chained SYS_EX telegrams per second. The value of 50ms is optimised for TCM300 9600 Baud. If the IDX_TEL_DELAY is smaller 
    it is not assured it will work with all the Controllers.    
 	**************************************************************************************************************************/	
	RETURN_TYPE reman_processSend();


	/************************************************************************************************************************//*!
  	Retrieves the lock code for remote management module. After the code was set by the controller the application should store this
	code in flash at specfied address #IDX_CODE_ADDR.

	\param[out]		u32Code		Lock code	    
    \return			-
 	**************************************************************************************************************************/	
	void reman_getCode(uint32 *u32Code);

	/************************************************************************************************************************//*!
  	Retrieves the ManufacturerID for the last RPC command received.

	\param[out]		u16Code		ManufacturerID of last RPC 	    
    \return			-
 	**************************************************************************************************************************/	
	void reman_getRpcManufacturerID(uint16 *u16RpcManufacturerID);
	
	/************************************************************************************************************************//*!
    Sets the last return code of last executed functions. This information is used by query status functions. By default the 
	last error code is set to #RM_RETURN_CODE_OK.
	    
	\param[in]		u16ErrorCode	Error code. See #RM_RETURN_CODE 
    \return    		-
 	**************************************************************************************************************************/	
	void reman_setError(uint16 u16ErrorCode);

//! @}  





//***************************MAIN PAGE DOCUMENTATION*****************************
/*!

	\mainpage Dolphin API Manual

	The DolphinAPI is a powerful abstraction layer for the Dolphin chip. It is  provided as pre-compiled library (no source code) with an easy to use 
    application programming interface (API). The DolphinAPI uses the Keil PK51 tool set and the library is compiled with the C51 Compiler Version 9.05.\n\n
	<b>It offers the following features:</b>
 	
	- Supports both line powered and ultra low power applications
	- Full support of the EnOcean radio protocol stack with transmission and reception of EnOcean radio telegrams
 	- Transmission and reception of custom data via UART and SPI interface
 	- Digital and analog I/O configuration and handling 	
	- Flash manipulation routines
	- Control of the Dolphin chip power modes
	- Customizable HW Timer1 usage as counter with callback possibility or PWM control
	- Software timers
	- Application error diagnostic and stack analysis  
	- Preemptive priority scheduler enabling system task execution parallel to the application (can be turned on/off)
	- Integrated one and two level repeater functionality
	- Integrated SmartACK communication concept
	- Integrated Remote Management protocol
	- EnOcean serial protocol support (for ESP2 and ESP3)
	\n\n

	This manual provides a detailed overview of the DolphinAPI and the Dolphin toolset. It contains the following chapters:\n
	
	- \subpage introduction gives an overview of the toolchain, explains the library architecture and offers a "quick-start" step-by-step tutorial
	- \subpage application_types describes which features set of the library should be used for line powered or ultra low power applications
	- \subpage dolphin_platform provides information about the Dolphin microcontroller
	- \subpage error_diagnostic shows how to use the error diagnostic features of the library to detect errors in the application and some debugging hints
	- \subpage enocean_radio_protocol  provides information about the EnOcean radio protocol
	- \subpage enocean_serial_protocols  provides information about the EnOcean serial protocols
    - \ref example_applications provides several sample programs that show you how to use the DolphinAPI
	- <a href="modules.html"><b>SW Modules</b></a> provides a detailed description of each library module and function interfaces</a>
	- <a href="annotated.html"><b>Data Structures</b></a> provides an overview of all data structures, variable types</a>

		
	<b>Referenced documents:</b>\n	
	\anchor References
	
	<table border="1" cellpadding="2" cellspacing="0" class="Design2">
	<tr> 
		<th width="30%">Document</th>
		<th>Description</th>
		<th width="25%">Location</th>
	</tr>
	<tr> 
		<td>EnOcean Radio Protocol (PDF)</td>
		<td>Summarization of the EnOcean Radio Protocol specification (ERP)</td>
		<td> <a href="http://www.enocean.com/en/knowledge-base/" target="_blank">EnOcean Knowledge Base </a> </td>
	</tr> 
	
	<tr> 
		<td>EnOcean Serial Protocol ESP3 (PDF)</td>
		<td>EnOcean Serial Protocol 3 specification (ESP3)</td>
		<td> <a href="http://www.enocean.com/en/knowledge-base/" target="_blank">EnOcean Knowledge Base </a> </td>
	</tr> 
	
	<tr>
		<td>Smart Acknowledge (PDF)</td>
		<td>Smart Acknowledgment communication specification (SmartACK)</td>
		<td> <a href="http://www.enocean.com/en/knowledge-base/" target="_blank">EnOcean Knowledge Base </a> </td>
	</tr> 
	
	<tr> 
		<td>Remote Management (PDF)</td>
		<td>Remote Management specification (REMAN)</td>
		<td> <a href="http://www.enocean.com/en/knowledge-base/" target="_blank">EnOcean Knowledge Base </a> </td>
	</tr>
	<tr> 
		<td>Dolphin Core Description (PDF)</td>
		<td>Dolphin Chip Core Description</td>
		<td><a href="http://www.enocean.com/en/knowledge-base/" target="_blank">EnOcean Knowledge Base </a></td>
	</tr>
	<tr> 
		<td>DolphinStudio.chm</td>
		<td>DolphinStudio and EOPX manual</td>
		<td><a href="http://www.enocean.com/fileadmin/redaktion/pdf/download/DolphinStudio.chm" target="_blank">DolphinStudio Manual  </a></td>
	</tr>
	<tr> 
		<td>Security of EnOcean Radio Networks (PDF)</td>
		<td>Description of the EnOcean secure radio protocol</td>
		<td><a href="http://www.enocean.com/en/knowledge-base/" target="_blank">EnOcean Knowledge Base </a></td>
	</tr>
	</table>
	
		
	*/
		
//***************************Introduction*****************************
/*!	 		
	\page introduction Introduction
	This chapter gives a quick introduction to library and toolchain usage. It contains the following chapters:\n
		
	- \subpage getting_started is a quick step-by-step tutorial
	- \subpage toolchain explains the Dolphin platform toolchain and their dependencies
	- \subpage architecture gives a description of the library architecture
	- \subpage application_project_structure describes the standard application project structure
	- \subpage dolphinstudio_keiluvision chapter describes how to integrate DolphinStudio to the uVision environment
	- \subpage modules_initialization explains how to initialise the library and the sw modules
	- \subpage converting_older_api describes how to convert existing projects API version 2.1.x.x to API version 2.2.x.x
	
*/

	//***************************Getting Started*****************************
	/*!	 		
		\page getting_started Getting started
	
	   <b>Getting started guide </b>\n
		-# Make sure the whole toolset is installed (see \ref toolchain).					
		-# Create a new application based on the provided template (copy_template.cmd batch file)
		-# Open the project with Keil uVision
		-# Compile the project		
		-# Connect a TCM320 with EVA320 board and EOP300 programmer		
		-# In uVision select Flash->Download to download the compiled hex file		
		-# You should see LMI (RSDADIO3) LED toggling
		

		\note
		Also a good beginner example is \ref app_radiotoserial.  For more examples make sure to read \ref example_applications.
	
	*/

	
	//***************************DolphinStudio & uVision*****************************
	/*!
		\page dolphinstudio_keiluvision Setting up Keil uVision (DolphinStudio, EOPX) 
		This chapter describes how to effectively integrate DolphinStudio and EOPX into Keil uVision. \n
		Three basic adjustments are required: \n
		- setup Keil uVision to start DolphinStudio passing the project folder as argument
		- setup the uVision project for EOPX postbuild step
		- setup the uVision project for EOPX Flash download
		
		
		<h1>Setting up Keil uVision to effectively work with DolphinStudio</h1>
		DolphinStudio can be started directly from Keil uVision environment passing the project folder as argument. 
		The advantages:
			- the EO3000I_CFG.h will be generate directly in your Keil project
			- DolphinStudio profile will be stored in the Keil project folder (\\Profiles)
			- DolphinStudio generates all 3 files automatically into the right folder
					
		Do the following steps to set up DolphinStudio with the Keil uVision environment: 
		
		- Select the Tools -> Customize Tools menu		
		\image html keil_customize.PNG
		
		- Add DolphinStudio to tools menu as shown on following picture:
		\image html keil_tools.png
		
		
		- DolphinStudio is added to your Tools menu. 
		- Start the DolphinStudio from Tools menu. 
		- Notice that the Profiles combo box includes only Default profile. Also the Project directory in Generate EO3000I_CFG page is already set to your Keil project directory. 
		- After you close the DolphinStudio, Profiles directory is created in you Keil project as shown on following picture:

		<h1>Setting Post-build tools</h1>\n
		In order to use the EOPX Postbuild tools following has to be set in Keil uVision: 
			- Options For Target\User\User Program After Build  
			- Add postbuild.txt to the Keil project
				
		After the Build/Rebuild process was successful, the EOPX post-build tools are executed in order to patch the BIST CRC in program area and Program Size byte in configuration area. 
		For more information read \ref flash_architecture.
		
		\image html keil_postbuild.png
		
		<b>Run #1:</b> \n
		eopx.exe -fprg "#H" -fcfg "$H@H_cfg.hex" -script "$Ppostbuild.txt"\n

		\note
		If the fcfg file does not exist, it will be created. 

		
		<h3>Creating postbuild script</h3>\n
		Add new file "postbuild.txt" to your Keil project as shown on following figure: \n
		
		\image html keil_script.png

		<h1>Setting Flash Programming tool</h1>
		In order to use the EOPX Programmer to directly download hex file to the Module after compiling, following has to be set in Keil uVision: 
		- Options For Target\Utilities\External Tool for Flash Programming
		
		\image html keil_eop.png
		
		<b>Command:</b>\n
		eopx.exe\n\n

		<b>Arguments:</b>\n 
		-fprg "#H" -fcfg "$H@H_cfg.hex" -write\n
		\n
		"#H" is replaced by uVision as the output .hex (C:\\MyProject\\Output\\sample.hex)\n
		"$H@H_cfg.hex" is replaced by uVision as configuration area file (C:\\MyProject\\Output\\sample_cfg.hex)\n
		\n

		<b>Optionally:</b>\n
		If you use the the setBist with [first_data_obj] parameter, the -fmap switch needs to be specified. \n
		\n
		 -fmap "$H@H.m51" -write

		\note If you use the template project or any of the examples these options are already configured in the projects.
		\note For more information about the postbuild commands please read the DolphinStudio\\EOPX Programmer\\Postbuild Tools section (see \ref References). 

		 
	*/
	
	//***************************Toolchain*****************************
	/*!	 		
		\page toolchain Toolchain
    The Dolphin platform uses several SW tools to offer easy application development. This chapter describes the various tools and their purpose for the development.
    \n
		<table border="1" cellpadding="2" cellspacing="0" class="Design2">
		<tr> <th width="10%">Software</th><th>Description</th></tr>
		<tr> 
			<td>DolphinStudio</td>		        		 
			<td>
			The EnOcean DolphinStudio software is a graphical user interface allowing easy configuration and programming of the Dolphin chip on TCM 3xx/STM 3xx modules.
			 For more information please read the DolphinStudio manual (see \ref References).
			</td>
		</tr> 
		<tr> 
			<td>EOPX</td>		        				
			<td>EOPX is a command line tool integrating programming and postbuild tool into one application. The tool is part of DolphinStudio but can also be used as a standalone tool.
			EOPX can also used in production environment to download firmware into EnOcean HW modules. The postbuild part of the tool is used by the uVisison (postbuild.txt) to initialise
			firmware Flash configuration values and to calculate Flash CRC codes. For more information please read the DolphinStudio manual (see \ref References).
			</td>
		</tr> 

		<tr> 
			<td>Keil PK51</td>		        				
			<td>The PK51 Professional Developer's Kit for the 8051 microcontroller family supports the EnOcean EO3000I (Dolphin) chip. The DolphinAPI library
			is developed using the PK51 toolset (compiled with C51). Currently the Dolphin platform only supports the usage of the Keil compiler. For more information about the Keil 
			version dependencies please see \ref dependencies chapter. You can use any PK51 license with the Dolphin platform inclusive a limited EnOcean Keil license. For more information 
			about the limited EnOcean license please contact EnOcean. 
			</td>
		</tr> 
		
		<tr> 
			<td>DolphinView</td>		        				
			<td>
			The DolphinView visualises properties of EnOcean radio nodes. It receives, sends and analyses radio telegrams according to the EnOcean radio standard. 
			In combination with a	transceiver it is also possible to simulate e.g. sensors or switch HW modules (e.g. PTM 2x0). It provide detailed information e.g. on subtelegram timing and signal 
			strength. Content of telegrams can be analysed online and is automatically logged with time stamp. DolphinView supports remote management features.
			</td>
		</tr> 		
	</table>

	<div align="center"><b>The following diagram shows the application development flow using the Dolphin platform</b></div>\n
	\image html swdevelopment_flow.PNG 
		\n\n
	<div align="center"><b>The following diagram shows the programming flow</b></div>\n
	\anchor ProgrammingFlow
	\image html programming_flow.PNG 
	
    
	*/

	//***************************API Architecture*****************************
	/*!	 		
		\page architecture Architecture
    	
		The DolphinAPI has a modular architecture. The functionality is grouped into several sw modules. Each module has it's own functions, parameters. 
		By calling functions in your application from a module the whole internal module is linked to your application. For instance if the application doesn't need UART communication, 
		and the module is not initialised the UART module will not be linked to the application. In such case no UART FIFO buffer allocation is needed and there will more RAM and Flash 
		available for your application. 

		<div align="center"><b>The following diagram shows the API architecture</b></div>\n
		\image html api_architecture.PNG
		\n
		
		<b>DolphinAPI Interface</b>\n
		The sw modules of the DolphinAPI can be accessed through the EO3000I_API.h interface. Most of the sw modules are independent. SW modules interacting together are shown as horizontal boxes.
		Some core sw modules are not directly accessible from the application,  such as scheduler, interrupt handlers.  The other sw modules have an interface that can be directly accessed by the application. 
		Each application accessible sw module has two types of interfaces: initialization, function interface. \n
		\n
		All interfaces to the functions have a consistent form:
		- A return value indicates if the function was correctly executed or an eventuality happened. These return codes described in the #RETURN_TYPE.
		- The parameters of the functions are used as an input/output parameters.
		
		\note For more information about the initialization interfaces see \ref modules_initialization.\n
		\note A detailed description of the function interfaces can be found in chapter <a href="modules.html"><b>Modules</b></a>. \n
		\n

		<b>ESSL Layer</b>\n
		The ESSL (EnOcean Software Stack Layer) contains the implementation of the scheduler, power management, serial and radio protocol stack and peripheral components. DolphinAPI does not implement 
		classical kernel architecture. The DolphinAPI and Keil library objects are linked to the application upon compilation time, thus there is no kernel and user space separation. 
		There is also no memory management, the memory for the sw modules is allocated upon compilation time.\n
		\n


		<b>HAL Layer</b>\n
		The HAL is the lowest layer of the library and it interacts directly with the underlying hardware. The HAL layer abstracts the Dolphin HW platform. 
		
		The following variable types are used in the DolphinAPI:
		\dontinclude EO3000I_API.h
		\skip typedef
		\until typedef bit 
		\image html bullet.png
		
		*/

	//***************************Application project structure*****************************
	/*!	 		
		\page application_project_structure Application project structure


		Every application shares the following files. 

        <table border="1" width="50%" cellpadding="2" cellspacing="0" class="Design2">
		<tr> <th>Filename</th><th>Short Description</th></tr>
		<tr> <td>EO3000I_API.lib</td>	        <td>The DolphinAPI library</td></tr>
		<tr> <td>EO3000I_API.h</td>		        <td>Interface definition for the DolphinAPI library</td></tr>
		<tr> <td>EO3000I_CFG.h</td>		        <td>Configuration header file generated by DolphinStudio</td></tr>
		<tr> <td>EO3000I_CFG.c</td>		        <td>Configuration c file generated by DolphinStudio</td></tr>
		<tr> <td>STARTUP.a51</td>		        <td>Configuration assembler file generated by DolphinStudio</td></tr>
		<tr> <td>MAIN.c</td>			        <td>Your application source code</td></tr>
		<tr> <td>Radio setting assembler file (i.e. stm300-315mhz-6dbm-1v23-ba.a51)</td>	<td>HW module radio setting</td></tr>
		</table>
		<p>
		There is a template application structure located in the <b>DolphinAPI\\EO3000I_API\\Examples\\_Template</b> folder. It is recommended to use this template
		for a new application development. The template name can be customized with the help of the <b>copy_template.cmd</b> which is also located in the example
		folder. 
		
		<b>EO3000I_CFG.h</b>\n
		This file is generated by DolphinStudio. It contains various definitions like radio buffer size, radio buffer number, UART buffer size etc.
		This file can be also included in the application source code.

		<b>EO3000I_CFG.c</b>\n
		This file is generated by DolphinStudio. It allocates various buffers like radio, uart, filter buffers etc.. Further it implements the two functions: \ref mainInit and \ref startupInit. These functions contains the calls to the various module initialization functions.
		DolphinStudio controls those functions depending on the user sw module initialization. For more information please read \ref modules_initialization.
		
		<b>STARTUP.a51</b>\n
		This file is generated by DolphinStudio. It contains the standard Keil C51 compiler startup procedures like initializing global variables, registers, stack pointer, etc.. 
		Prior these init functions are executed the \ref startupInit() is called. This allows some module initialization (like \ref pwr_enableXTAL and \ref io_init) immediately after reset or wakeup.
		For more information read http://www.keil.com/support/docs/1296.htm and also \ref modules_initialization.
		
		<b>Radio setting assembler file</b>\n
		Each Dolphin HW module has a dedicated radio setting assembler file. This file contains the initialization of the radio (RF) portion of the Dolphin chip. The radio setting file
		has a certain naming convention:\n\n
		<CENTER><b>[modul_name]-[frequency]mhz-[transmission_power]dbm-[revision]-[modul_stepcode].a51</b></CENTER>
		For instance the radio setting:\n
		<CENTER><b>stm310-315mhz-6dbm-1v25-da.a51</b></CENTER>
		is used for the STM300C DA HW modul, for the 315Mhz Frequency, has a 6dBm transmission power. 
		\note The developer has to make sure that the application is compiled with the correct radio setting.
		\note For more information how the library is configured using the DolphinStudio generated files make sure to read the \ref modules_initialization.
		\note The template project has  a placeholder called radio_init_asm_315/868. Make sure to replace these files with the correct HW modul radio settings.
		
	*/

		
	//***************************Modules Initialization*****************************
	/*!	 		
		\page modules_initialization DolphinAPI Initialization
		
		Before the member function of an API modul can be used the library and some of the sw modules have to be initialised. The modul initialisation function was the following
		structure (there are some exceptions read \ref notes below):
		<CENTER><b>modulename_init(uint8 *pu8Param, uint8 u8ParamToSet)</b></CENTER>		
		The init parameters of a module are defined with a parameter list. Each index of an array corresponds to a parameter from the parameter list. 
		The parameter list for the sw modules are defined in the EO3000I_API.h interface file (e.g. \ref UART_PARAM_IDX).  An array containing the parameter values
		are passed to the init functions using the *pu8Param There is a possibility to change the parameter initialization during runtime using the u8ParamToSet variable (exception io_init). For more information how to do this read \ref dynamic_configuration below.
		\n\n The init parameters and function calls to the module inits are generated by DolphinStudio and are stored in the 
		EO3000I_CFG.c, EO3000I_CFG.h, startup.a51 files. 
		
		\image html dolphin-to-keil.png
		
		DolphinStudio generates the two following init functions in the EO3000I_CFG.c and 
		the initialisation process is separated in 2 steps:
		 
		
		\anchor startupInit <b>startupInit();</b>\n
		This function is called from startup.a51 immediately after reset (wakeup) before the C51 compiler init sequence.  
		As default DolphinStudio always places the following functions here:
		- \ref pwr_enableXTAL(DEFAULT_DELAY); - enables the XTAL 
		- \ref io_init(io_param); initializes the I/O ports here.\n
		Do not use other API functions here, because global variables will be initialized later on. Custom application functions can be also placed here. These function are not allowed to use global initialised variables.  
		
		\anchor mainInit <b>mainInit();</b>\n
		This function has to be called from main.c. As default DolphinStudio always places the following functions here:
		 - radio_init_asm(CFG_ALL); - initialise radio settings
		 - \ref radio_init (RADIO_BUFF_NUM, RADIO_MATURITY_TIME); - initialise radio module
		 - misc_init(); - enabling interrupts
		 - pwr_selectXTAL(); - selecting XTAL
	
		Additional initialisations are placed here depending on which sw modules where activated in DolphinStudio.
		
		<CENTER><b>The DolphinAPI init process is displayed on the picture below:</b></CENTER>\n
		\image html initprocess.png 

		
		\anchor notes
		
		<b>\anchor dynamic_configuration Dynamic module initialization</b>\n
		SW modules their init function has a second parameter <b>u8ParamToSet</b> offers the possibility to set the init parameters selective or during runtime.
		To set 1 parameter the u8ParamToSet has to contain the index of the parameter. 
		The same functionality is ensured by the module_setConfig macro (example \ref uart_setConfig, \ref filter_setConfig, \ref timer1_setConfig etc.). 
		Parameters which can't be changed are signed with an (ro) tag in the documentation. 

		\n
		<b>Example:</b>\n
		Changing the baudrate parameter of the UART function during runtime:
		\code
		uart_setConfig(uart_param, IDX_BAUD, BAUD_9600);
		\endcode
		\n\n

		\note 
		<b>If an older project was created using API 2.1.x.x (or older) version make sure to read chapter \ref converting_older_api. Also note that 
		compatible initialization for API 2.2.x.x can be generated only with DolphinStudio 2.2.x.x and higher version </b>		
		\note 
		The pwr, mem modul does not need to be initialised
		\note
		The init of the time modul and scheduler is different. Make sure to read \ref scheduler chapter
		\note
		Be sure to enable in DolphinStudio only those sw modules which you definitely will use in your application
		\note
		If the application is not changing the init values during execution, using the <b>code</b> specifier the initialization array can be place to the Flash thus saving RAM.
		Make sure to read \ref MemoryTypeVariableSpecifier.
		
		\note
		When a module is initialised with all parameters u8ParamToSet value is \ref SET_ALL_PARAM. 		
		
		\note
		The parameters of the init functions are not prooved for correctness as these are generated by DolphinStudio. This method saves execution speed and flash. Make sure
		always provide correct parameters for the init functions.
		
	*/

	
	//***************************Converting Older API Projects*****************************
	/*!
		\page converting_older_api Converting Older API Projects
	
		Since with API version 2.2.x.x the initialisation has been reworked and the init interface is not compatible to the older API 2.1.x.x versions. Therefore projects 
		that where created with older API needs to be converted to the new format. 
		This chapter describes these steps. Prior reading this chapter make sure to read \ref modules_initialization.
		
		<b>Major changes</b>\n
		- io_init interface has been changed: SET_ALL_PARAM was removed, it is not possible to set the parameters 1 by 1 
		- the initialization arrays are allocated in EO3000I_CFG.c instead of EO3000I_CFG.h
		- EO3000I_INIT was replaced by mainInit() and startupInit function (for more info see \ref modules_initialization)
		- pwr_getSystemReset can be called from any part of the application
		
		
		<b>5 easy steps how to convert a API 2.1.x.x project to API 2.2.x.x></b>\n
		-# For the new API 2.2.x.x version make sure to use the DolphinStudio 2.2.x.x or higher
		-# The profiles between DolphinStudio 2.1.0.0 and DolphinStudio 2.2.0.0 (and higher) are compatible. Take the profiles generated by DolphinStudio 2.1.x.x
		and open it with the DolphinStudio 2.2.x.x
		-# Make sure to control all the Configuration pages and after that save the new configuration files
		-# Open the uVision project and add the following new files: EO3000I_CFG.c, STARTUP.A51
		-# In your main() function replace the EO3000I_INIT with the mainInit(); function
		
		<b>Further tips can you simplify your application:</b>		
		- For the ULP application use the radio_ulpSend3SubTels() function
		- The pwr_getSystemReset can be called anywhere in your application
		- The pwr_selectXTALStandby replace with pwr_selectXTAL()
		
		
		
	*/


//***************************Application types*****************************
/*!	 		
	\page application_types Application types
	
	DolphinAPI can be used for the development of both \ref line_powered  and self-powered \ref ultra_low_power (ULP) applications. 
	Due to the different requirements (mainly energy optimisation) for those application types the API offers optimized functionality.
	For instance in a line powered application the energy is not critical. Thus a telegram transmission can be realised using the system \ref scheduler even if it will take 
	several ms (applying listen before talk, repeating etc.). On the other side ULP applications are limited by energy thus transmitting a 
	telegram has to be done as fast as possible in this case a function is used that can be run directly from the application layer.
	Following this concept in the API library, for the same functionality (for instance telegram transmission) both ULP and line powered functions are available. The main difference
	between ULP and line powered functions is that the line powered functions are using the system \ref scheduler. Another difference is in the io_measAnalog. This function
	is a complex function and offers many features. It also takes a long time to execute. In a reduced energy application oft a simple analog measurement is required.
	This is the reason io_ulpMeasAnalog, io_ulpMeasAnalogVGA, io_ulpScaleAnalog functions where introduced. \n\n
	
	One of the first steps during application development is to decide whether the application is an ultra low power or line powered application. The two concepts and functions shouldn't be  
	mixed. For instance in an ULP application the scheduler is not running and therefore calling #radio_sendTelegram will not work! Or if the scheduler runs in a line powered application
	calling the #radio_ulpSendTelegram function might hang up the program! The application type is selected during \ref modules_initialization with DolphinStudio and will puts the required
	initialisation routines to the \ref mainInit in EO3000I_CFG.c.
	
	\image html ds-application-type.png

	The following chapters describes how to develop ULP or line powered applications. It contains the following chapters:\n		
	- \subpage line_powered explains how to develop a line powered application\n
	- \subpage ultra_low_power explains how to develop ultra low powered application\n
	
	
	\note Every function containing the word <b>ulp</b> is intended to be used by ultra low power applications  (see \ref ulp_functions)
	\note ULP functions are not as "comfortable" as the line powered once thus the application has to do more implementation.
	\note Some features as repeating, remote management are not available for ULP application.
	
*/

	//***************************Line Powered*****************************
	/*!	 		
		\page line_powered Line Powered
		
		Line powered applications are intended to be used for HW modules that have a permanent power supply. These devices are usually line, battery or continuous 
		energy harvester powered. The radio receiver is always on and they don't enter to sleep mode (exception standby). Typical line powered applications are gateways 
		or controllers. In line powered applications the system \ref scheduler is activated and the \ref watchdog_timer Timer is used as
		timer that triggers a system reset if the application hangup.\n\n
			 
		To create a line powered application in DolphinStudio select either the Line powered or Line Powered SmartACK-PostMaster application option. 
		
		\image html ds-application-type-big.png
	
		<b>Line Powered Application</b>
		- The timer0 scheduler is initialised with the help of isr_timer0Init(); function 
		- The application can send and receive several telegrams with the help of radio_sendTelegram, radio_getTelegram 
		- The management of tx and rx radio buffers is done by the library
		- Telegram encoding/decoding, encapsulation/decapsulation is handled by the library
		- The subtelegram timing is handled by the library
		- The application is capable of 1 or 2 level repeater 
		- The application can use the SW Timers from the time module 
	
		Additionally the Remote Management functionality can be configured. 
		
		<b>Line Powered SmartACK-PostMaster Application</b>\n
		- The timer0 scheduler is initialised with the help of isr_timer0_smack_PM_Init(); function 
		- The application has SMACK postmaster functionality
		- All further options are the same as for the Line powered mentioned above 
		
		For further information how the scheduler and watchdog works in line powered application make sure to read the \subpage scheduler and
		\subpage watchdog_timer chapter.
		
		\note 
		Also see example codes for line powered applications:\n
		\ref app_remanesp3 \n
		\ref app_lightcontrol \n
		
		
	*/

		//***************************Scheduler *****************************
		/*!

		\page scheduler Scheduler
		The scheduler provides the following functionality seamless and parallel to the application execution:
		- reception/transmission of radio telegrams 
		- Rx and Tx maturity time management		 
		- 1 and 2 level repeating
		- SmartACK postmaster functionality
		- listen before talk
		- SW timers
		- Remote Management 
				
		DolphinAPI realises a unique preemptive priority scheduler on the system level. There are two types of tasks: 
		- single application task
		- multiple system tasks
		
		System tasks run preemptive to the application task but concurrent to other system tasks, thus a system task can always interrupt the application task.
		(exception ASynchTask1, read below). System tasks always run to	completion and they can't interrupt each other. Exception is the UART ASynchTask that has high priority. 
		This tasks can also preempt other system tasks. There is only one application task; thus no parallel application tasks can be executed. The OS implements no message 
		handling. Some system tasks (i.e. Timer1) can execute application code using static callbacks.\n\n System tasks are divided into synchronous and asynchronous tasks. Most of 
		the synchronous system tasks provide the function of the radio protocol stack.\n\n
		
		<b>Synchronous system tasks</b>\n
		The synchronous system tasks are handled using the scheduler triggered by the Timer0 HW interrupt.
		The scheduler runs on a round robin basis and every task has an 1 ms timer slice. Every 1 ms the execution of the application is interrupted and one of the synchronous system 
		tasks takes over the CPU. Synchronous system tasks are executed sequentially according to their priority and demand. The average duration of the synchronous task is around 
		<b>50 - 150 us</b>. In rare worst case scenarios the execution duration can be up to <b>~1 ms</b> (considering high radio traffic, long radio telegrams, repeater, SmartACK on).\n\n		
	 
		The execution duration is dependent on:
			- active SmartACK Postmaster feature
			- active 1 or 2 level repeater feature
			- the number of radio buffers
			- amount of radio traffic
			- subtelegram length
		\n
		
		
		The following table summarizes all the synchronous system tasks. The list is ordered in descending order of the task priority. Some tasks are executed only if an 
		execution condition is fulfilled.  
		
		<center>
		<table border="1" cellpadding="2" cellspacing="0" class="Design2">
			<tr> <th width="10%">Task</th><th>Description</th><th>Execution Condition</th><th>Approx. Worst case Duration</th></tr>
			<tr> 
				<td>SynchTask1</td>		  
				<td><b>System timer increment</b> - increments a 32bit counter representing the system clock counter (used also by the SW Timers)</td>
				<td>every 1ms</td>
				<td>~20us</td>
			</tr> 
			
			<tr> 
				<td>SynchTask2</td>		        				 
				<td><b>Workaround for the UART communications</b> - if the UART Tx flag is pending, start transmission again </td>
				<td>every 1ms</td>	
				<td>~50us</td>
			</tr> 

			<tr> 
				<td>SynchTask3</td>		        				 
				<td><b>SmartACK postmaster</b> - provides SmartACK mailbox functionality (processes reclaims, etc.)</td>
				<td>every 1ms if SmartACK is active</td>	
				<td>~250us</td>
			</tr> 

			
			<tr> 
				<td>SynchTask4</td>		        				 
				<td><b>Radio buffer update</b> - processes radio buffers, update subtelegram timing. If there is a telegram that has to be transmitted, it is placed to
				the radio HW buffer and transmission is started.</td>
				<td>every 1ms</td>	
				<td>~720us</td>
			</tr> 

			<tr> 
				<td>SynchTask5</td>		        				 
				<td><b>Subtelegram decoding</b> - decodes one received subtelegram and stores it in a free radio buffer</td>
				<td>if no action in SynchTask4 &<br>if new subtelegram was signaled by the AsynchTask2</td>	
				<td>~900us</td>
			</tr> 
			
			<tr> 
				<td>SynchTask6</td>		        				 
				<td><b>Switch subtelegram conversion</b> -  converts a switch subtelegram to RPS subtelegram</td>
				<td>if no action in SynchTask5 &<br>if the last decoded subtelegram by SynchTask5 is a switch telegram</td>	
				<td>~200us</td>
			</tr> 

			<tr> 
				<td>SynchTask7</td>		        				 
				<td><b>Telegram compressing</b> - processes received subtelegrams. The occupied buffers are proved if the subtelegram already exists. If the subtelegram is new and 
				repeating is enabled the repeater option is proved.</td>
				<td>if no action was done in SynchTask6 &<br>if new decoded subtelegram is waiting for processing from a previous run of SynchTask5 or 6</td>	
				<td>~500us</td>
			</tr> 
			
		</table>
		</center>
			
  		 
		 For a better illustration how are the synchronous tasks priority handled see the following pseudo code:
	   	
		\code
		\\This part of code is executed every 1ms when the Timer0 interrupt is activated
		SynchTask1();

		SynchTask2();

		if (SmartACK)
			SynchTask3();

		if (SynchTask4())
			return;
		else if (bNewEncodedSubtelegram) {
			SynchTask5(); 
			return;
		}
		else if {bNewSwitchTelegram) {
			SynchTask6();
			return;
		}
		else  if (bNewDecodedSubtelegram) {
			SynchTask7(); 
			return;
		};
		\endcode

  	  
		<b>Asynchronous system tasks</b>\n
		Asynchronous system tasks are HW module dependent and are connected to HW interrupts.  They are active only when the corresponding module and functionality is activated.
		<center>
		<table border="1" cellpadding="2" width="90%" cellspacing="0" class="Design2">
			<tr> <th width="10%">Task</th><th width="50%">Description</th><th>Approx. Worst case Duration</th></tr>
			<tr> 
				<td><b>Prio High ASynchTask1</b></td>		  
				<td><b>Uart Rx/Tx interrupt</b> - processes uart byte receiving/transmitting and buffer handling</td>
				<td>~50us</td>
			</tr> 
			
			<tr> 
				<td>ASynchTask2</td>		        				 
				<td><b>Radio Rx interrupt</b> - processes incoming subtelegram</td>
				<td>~500us</td>
			</tr> 

			<tr> 
				<td>ASynchTask3</td>		        				 
				<td><b>Radio Tx interrupt</b> - stops running HW state machine</td>
				<td>~930us</td>
			</tr> 

			<tr> 
				<td>ASynchTask4</td>		        				 
				<td><b>Timer1</b> - processes timer1 interrupts and timer1 callbacks</td>
				<td>application dependent</td>
			</tr> 
			
			<tr> 
				<td>ASynchTask5</td>		        				 
				<td><b>IO</b> - processes gpio interrupts and io callbacks</td>
				<td>application dependent</td>
			</tr> 
			
		</table>
		</center>
		
		\note
		The scheduler is activated by calling the #isr_timer0Init or #isr_timer0_smack_PM_Init function. 
				  
		\note
		There is no minimum time guaranty for the user application running between the scheduler interrupts!

		
				  
		*/

		//***************************Watchdog Timer*****************************
		/*!
		\page watchdog_timer Watchdog Timer

		It is very important to understand  that in the EO3000I platform the watchdog timer is used for two different purposes:\n	
		- the timer is used as a safety feature to provide a reset in case of an application deadlock
		- the timer is used to enter and wake up the cpu to/from deep sleep mode. For more information about this read the chapter \ref sleep_modes.\n\n

		This chapter describes how to use the watchdog timer reset to recover the application from a deadlock. 
		For more information about the HW timer read \ref ulp_timers
		

		To configure the watchdog timer to recover the application from a deadlock do the following:\n\n
		- After reset as default the Watchdog period is set to 0xFFFFFF (~ 46.6 hours).
		- At the beginning of the application set the watchdog reset period using the #SET_WDT macro
		- When the period of the watchdog is set, the application has to make sure that the watchdog timer counter is cleared before the counter overflows.
		Otherwise the watchdog will force a watchdog reset. To clear the watchdog counter use the #CLR_WDT macro.
		- To determine if there was a Watchdog reset call the #pwr_getSystemReset
		
		
		*/

	//***************************Ultra Low Power*****************************
	/*!	 		
		\page ultra_low_power Ultra Low Power
		Ultra low power applications are intended to be used for HW modules powered by energy harvesting. In such application scenarios the HW module is most of the time off 
		or in #DeepSleepMode or #FlywheelSleepMode. The radio modul is switched on and off for a very short period of time. Typical ULP applications are energy autonomous sensors, 
		actors. In ULP applications the scheduler is deactivated thus the application has full control over the CPU (no parallel task running). 
		
		To create an ultra low line powered application in DolphinStudio select the Ultra Low Power application option. 
		\image html ds-application-type-big-ulp.png
	
	
		<b>Ultra Low Power Application</b>
		- The application can use various \subpage ulp_timers, \subpage sleep_modes and \subpage wake_events 
		- Make sure to read the chapter about \subpage timer_calibration
		- The application can use various \subpage ulp_functions
		
		
		\note ULP application do not support telegram receiving (exception are applications that support Smart Acknowledge. See the Smart Acknowledge specification \ref References and \ref smack_reclaim receiving )		

		\note 
		Typical example of ultra low powered applications:\n
		\ref app_deepsleep \n
		\ref app_autarkicsens \n
		\ref app_flywheel \n

		*/

		
		
		//***************************Ultra Low Power Timers*****************************
		/*!

		\page ulp_timers Ultra Low Power Timers

There are 3 ULP timers in the Dolphin system as shown in the table below.
\n
			<table border="1" cellpadding="2" cellspacing="0" class="Design2" width="100%" align="center">
			<tr> 
				<th>TimerName</th>						
				<th>TimerEnum</th>		
				<th>Clock Source</th>				
				<th>Width</th> 
				<th>Minimum-period (One-tick)</th> 	
				<th>Maximum-period</th>			
				<th>Typical uncalibrated error</th> 
				<th>Description of the timer and usage </th>
			</tr>
			
			<tr> 
				<td> \anchor WatchdogTimer Watchdog Timer</td>		
				<td>#WATCHDOG_TIMER</td>
				<td>100Hz intern WRCO</td>			
				<td>24 bit</td> 
				<td>10 ms</td>				
				<td>16 777 215 = 46.6 hours</td>	
				<td>40%</td>											
				<td>This timer always runs (can't be disabled). A counter underflow causes a \ref WatchdogReset in any \ref sleep_modes (or in CPU mode). The counter counts down.</td>			  
			</tr>
			
			<tr> 
				<td> \anchor FlywheelTimer Flywheel Timer </td>		
				<td>#FLYWHEEL_TIMER</td>
				<td>32.768 kHz extern Wristwatch XTAL (WXTAL)</td>	
				<td>24 bit</td> 
				<td>~1 ms (1/1024s)</td>		
				<td>16 777 215 = ~4.6 hours</td>		
				<td>delta fWXO, ca. 0.01%</td>			
				<td>Can be enabled/disabled. Needs an external wrist-watch XTAL and the #WXID_IO and #WXOD_IO pins configured as WXTAL (DolphinStudio). If enabled and CPU is in sleep (#pwr_timerSleep), a counter overflow results in a \ref FlywheelReset.  The counter counts up.</td>			  
			</tr>
			
			<tr> 
				<td> \anchor ShortTermTimer ShortTerm Timer</td>	
				<td>#SHORT_TERM_TIMER</td>
				<td>100kHz intern SRCO</td>		
				<td>16 bit</td> 
				<td>10 us</td>				
				<td>65 535 = 0.6 seconds</td>		
				<td>35%</td>												
				<td>Can be enabled/disabled. If enabled and CPU is in sleep (#pwr_timerSleep), a counter overflow results in a CPU wake-up. The CPU will continue the program execution. The counter counts down.</td>			  
			</tr>
			</table>
			<p>

		All the ultra low power timers can be used 
			- in \ref sleep_mode to wakeup at predefined time\n 
			- in \ref cpu_mode to measure time by using the functions  #pwr_getSleepTimerCounter, #pwr_resetSleepTimer, #pwr_getSleepTimerStatus
		
		\note Upon a \ref PowerOnReset, \ref PinReset the ULP timers are put to \anchor InitialState initial state. This is the following:
		- Watchdog periode is set to 0xFFFFFF
		- Flywheel timer is disabled
		- ShortTerm timer is disabled
			
		\note Each timer has a certain error (see \ref References Dolphin User Manual). To reduce this error the timers are calibrated during modul production. For further information please 
		read \ref timer_calibration
		
		\note 
		The Flywheel wristwatch xtal clock frequency (type which is recommended in the datasheet) has not exactly 32 kHz but 32.768 kHz. Thus 1 Flywheel period is not exactly 1ms but 1/1024 s=0,9765625ms. 
		That's why all the time informations in this manual are for the flywheel timer showed as an approximate value with ~. Using the calibration value from the configuration area
		this error can be corrected.
		

		*/

		//***************************Sleep Modes*****************************
		/*!

		\page sleep_modes Sleep Modes

		The standard application execution mode is the \anchor CpuMode CPU mode. After any reset type the chip starts in CPU mode. Typical current consumption is about 3.7 mA (radio off).
		The chip supports various power modes (sleep modes) to reduce current consumption.  To enter in a sleep mode the #pwr_timerSleep function is used. In sleep mode various 
		ULP timers can be activated to control the wakeup behaviour. Additionally its possible to wake up the CPU from sleep mode with the wake pins WAKE0 and WAKE1 (\ref WAKE_PIN0_RESET, \ref WAKE_PIN1_RESET).
		The table shows an overview of the different sleep modes.
		
		<table border="1" cellpadding="2" cellspacing="0" class="Design2" width="100%" align="center">
		<tr> 
			<th>Power Mode</th>		 
			<th>Timer controlling wakeup</th>	       		         
			<th>typical current consumption (see note) </th> 
			<th>Pin State (DVDD)</th>                              
			<th>Wakeup Event</th>                              
			<th>Wakeup State</th> 		    
			<th>Description of the mode </th>
		</tr>
		
		<tr> 
			<td> \anchor DeepSleepMode Deep Sleep Mode</td>	   
			<td> \ref WatchdogTimer</td>                  
			<td>220 nA</td>                 
			<td>Undefined<br>DVDD is off</td>                
			<td>Watchdog, Wake pins</td>                
			<td>\ref WatchdogReset. Startup time ~2ms</td>		
			<td>Used for weak ambient energy powered, event triggered TX applications</td>
		</tr>
			
		<tr> 
			<td> \anchor FlywheelSleepMode Flywheel Sleep Mode</td>     
			<td> \ref FlywheelTimer</td>                  
			<td>720 nA</td>  
			<td>Undefined<br>DVDD is off</td>
			<td>Flywheel, Wake pins</td>	    
			<td>\ref FlywheelReset. Startup time ~2ms</td>		
			<td>Used for high precision system timing, lowest duty-cycle synchronous network.</td>
		</tr>			
		
		<tr> 
			<td> \anchor ShortTermSleepMode ShortTerm Sleep Mode</td>    
			<td> \ref ShortTermTimer</td>                  
			<td>10 uA</td>  
			<td>Undefined<br>DVDD is off</td>
			<td>ShortTerm overflow, Wake pins</td>	 
			<td>Continue in application<br>all RAM's (XDATA, DATA, SFR) retained except radio configuration (need to call radio_init()), XTAL off, running on CRCO. Startup time: ~2ms</td>			   
			<td>Used for short sleep periods that are significantly longer than the XTAL startup time (e.g. between subtelegrams)</td>
		</tr>
			
		<tr> 
			<td> \anchor Standby Standby</td>    		 
			<td>Scheduler (Timer0)</td> 		
			<td>1.4 mA</td> 
			<td>Defined<br>DVDD is on</td>			
			<td> \ref WakeupEvents</td>	 
			<td>Continue in application<br>the whole CPU inclusive all RAM's (XDATA, DATA, SFR) is retained, XTAL still running. Startup time: 10us</td>			   
			<td>Used for waiting for an event</td>
		</tr>
		
		</table>

		\note 
		The current consumption values are only informative, please consult the respective user manuals (see \ref References) 
		
		\note
		Remember that the Watchdog timer is always running and it can't be disabled. It can wake up OR reset the CPU in any sleep mode.
		  
		\note
		In ShortTerm sleep if the FlyWheel timer is running, it's timeout can also reset the CPU     
		*/

		//***************************Wakeup Events and Reset Sources*****************************
		/*!

		\page wake_events Wakeup, Reset Sources
		
		<b>Reset Sources</b>\n
		The reset sources are specified by the #RESET_TYPE enumeration. The reset reason can be queried by the #pwr_getSystemReset function.
		The following table shows which events can cause a reset and in what state is the chip afterwards: 

		<table border="1" cellpadding="2" cellspacing="0" class="Design2" width="100%" align="center">
		<tr> 
			<th>Reset Type</th>		 
			<th>Triggered by Event</th>	       
			<th>Startup State</th> 
			<th>Wakeup Type</th> 
		</tr>
		
		<tr>
			<td> \anchor PowerOnReset Power On Reset</td>	   
			<td> First power up VDD>VON OR<br>Power up after a brownout</td>			
			<td> All processor state is lost, starting in \ref CpuMode<br>XTAL off, running on CRCO, all RAM value lost<br>All timers reseted to \ref InitialState
			Turn on time maximum values: 50 ms -40...+85K, 33 ms -25...+65K</td>			
			<td> #VDD_RESET </td>
		</tr>		
		<tr>
			<td> \anchor PinReset Pin Reset</td>
			<td> Caused by RESET pin assertion</td>			
			<td> All processor state is lost, starting in \ref CpuMode<br>XTAL off, running on CRCO, all RAM value lost<br>All timers reseted to \ref InitialState</td>			
			<td> #PIN_RESET </td>
		</tr>			
		<tr>
			<td> \anchor WatchdogReset Watchdog Reset</td>
			<td> Exit #DeepSleepMode due to:\n
				 - Watchdog counter underflow OR
				 - Application hang up</td>			
			<td> All processor state is lost, starting in \ref CpuMode<br>XTAL off, running on CRCO, RAM0 retained<br>The Watchdog counter keeps running, last periode is set</td>			
			<td> #WATCHDOG_RESET </td>
		</tr>			
		<tr>
			<td> \anchor FlywheelReset Flywheel Reset</td>
			<td> Exit #FlywheelSleepMode due to Flywheel counter overflow</td>			
			<td> All processor state is lost, starting in \ref CpuMode<br>XTAL off, running on CRCO, RAM0 retained<br>The Flywheel counter keeps running, last periode is set</td>			
			<td> #FLYWHEEL_RESET </td>
		</tr>			
			
		</table>

	
			
		<b> \anchor WakeupEvents Wakeup Events</b>\n
		The wakeup events are specified by the #WAKE_TYPE enumeration. The wake events can be used by the #pwr_timerSleep and #pwr_standbySleep function Standby.
		The following table shows which events can wakeup the CPU from which sleep mode. 


		
		<table border="1" cellpadding="2" cellspacing="0" class="Design1" align="center">
		<tr> <th>&nbsp;</th>			<th>DeepSleep</th>				 <th>Flywheel</th>			<th>ShortTerm</th> 				<th>Standby</th> </tr>
		<tr> <td>&nbsp;</td>			<td COLSPAN=3>pwr_timerSleep()</td>  					    <td>pwr_standbySleep()</td>
		<tr> <td>#PIN_WAKE0_WAKE</td>	<td>x</td>    	 	 <td>x</td>	 		  <td>x</td>		<td>x</td> </tr>
		<tr> <td>#PIN_WAKE1_WAKE</td>    <td>x</td>	 	 	 <td>x</td>	   	      <td>x</td>		<td>x</td> </tr>
		<tr> <td>#SHORT_TERM_WAKE</td>	<td>&nbsp;</td>	 	 <td>&nbsp;</td>	  <td>x</td>		<td>&nbsp;</td> </tr>
		<tr> <td>#RX_RADIO_TEL_WAKE</td> <td>&nbsp;</td> 	 <td>&nbsp;</td>	  <td>&nbsp;</td>	<td>x</td> </tr>
		<tr> <td>#TX_RADIO_TEL_WAKE</td> <td>&nbsp;</td> 	 <td>&nbsp;</td>	  <td>&nbsp;</td>	<td>x</td> </tr>
		<tr> <td>#PIN_EXT_WAKE</td>    	<td>&nbsp;</td> 	 <td>&nbsp;</td>	  <td>&nbsp;</td>	<td>x</td> </tr>
		<tr> <td>#TIMER0_WAKE (scheduler)</td>    	<td>&nbsp;</td> 	 <td>&nbsp;</td>	  <td>&nbsp;</td>	<td>x</td> </tr>		
		</table>
		\n\n

		\note 
		\ref app_standby, \ref app_deepsleep provides an example how to use various wakeup events.
		
		*/

		//***************************Calibration of the timers*****************************
		/*!

		\page timer_calibration Calibration of the timers

		The ULP timer oscillators error can be reduced using calibration. To improve the timer accuracy calibration values 
		are stored for each HW module in the CFG_AREA. If a better accuracy is needed it is recommended to apply the calibration
		values on the timer period values in the following way:\n\n

		<b>\ref WatchdogTimer calibration:</b>\n
		The example below shows how to use the 16 bit integer calibration value. 
		Instead of a division with 32bit float a 16 bit value together with
		a constant #WATCHDOG_CALIB_CONST  is used to speed up the end value calculation. 
		The division with #WATCHDOG_CALIB_CONST  is interpreted by the compiler as shifting,
		because 2^11 = 2048, so valuable time is saved in comparison to a float division. 

		\code
		CFG_AREA xdata unigcfg  _at_ CFG_ADDR; //address for reading cfg area

		//calculate timer periode for 10 seconds
		u32WatchdogPeriode = (uint32)(u32WatchdogPeriode*unigcfg.val.u16CalibWatchdog)/WATCHDOG_CALIB_CONST;
		result = pwr_setSleepTimer(WATCHDOG_TIMER, u32WatchdogPeriode, 0);
		\endcode
		
		<b>\ref FlywheelTimer calibration:</b>\n
		The example below shows how to use the 32 bit float calibration value:
		\code
		CFG_AREA xdata unigcfg  _at_ CFG_ADDR; //address for reading cfg area

		//calculate timer periode for 10 seconds
		u32FlywheelPeriod = (uint32)(CONV_TIME_TO_COUNTER(10, SEC, FLYWHEEL_CLK)* unigcfg.val.f32CalibFlywheel);
		result = pwr_setSleepTimer(FLYWHEEL_TIMER, u32FlywheelPeriod, 0);
		\endcode

		<b>\ref ShortTermTimer calibration:</b>\n
		The example below shows how to use the 16 bit integer calibration value:
		Instead of a division with 32bit float a 16 bit value together with
		a constant #SHORT_TERM_CALIB_CONST is used to speed up the end value calculation. 
		The division with #SHORT_TERM_CALIB_CONST is interpreted by the compiler as shifting,
		because 2^11 = 2048, so valuable time is saved in comparison to a float division. 
		\code
		CFG_AREA xdata unigcfg  _at_ CFG_ADDR; //address for reading cfg area

		//enter Short Term sleep between subtelegrams
		u16value =  (CONV_TIME_TO_COUNTER(10, MSEC, SHORT_TERM_CLK) * unigcfg.val.u16CalibShortTerm) / SHORT_TERM_CALIB_CONST;
		pwr_setSleepTimer(SHORT_TERM_TIMER, u16value, SHORT_TERM_ONE);
		\endcode \n\n	

		\note
		When a timer is calibrated the maximum periode can't be always reached. This should be especially considered when using the #CONV_TIME_TO_COUNTER macro because with the
		calibration factor the timer register width can overflow. Be aware if using very small values there is a certain rounding error. 
		
		\note 
		You can find an example of a timer calibration in \ref app_autarkicsens example
		*/

		//***************************Ultra low power functions*****************************
		/*!

		\page ulp_functions Ultra Low Power functions

		There are special designed functions for ultra low power applications available in Dolphin API,  recommended to be used to get the
		best performance. This chapter describes the philosophy of using these functions.

		<b>Radio functions</b>\n

		In ulp applications the scheduler managing the sending/receiving/encoding/decoding of subtelegrams is not running.  Nevertheless it
		is possible to send telegrams also without scheduler. The receiving of telegrams is limited in ulp 
		applications to the Smart Acknowledge functionality, because after the receiving of a telegram the receiver is switched off by the Dolphin API to
		save energy.
		
		There are two possibilities how to transmit telegrams without scheduler:\n
		- using \ref radio_ulpPrepareTelegram, \ref radio_ulpSend3SubTels - in such case the subtelegram timing and sleep mode between subtelegrams
		is handled by the library
		- using \ref radio_ulpPrepareTelegram, \ref radio_ulpSubTelTiming , \ref radio_ulpSendTelegram  - in such case the application has to  
		handle it's own sleep procedure and subtelegram timing
				
		\note When the application is handling it's own subtelegram transmission and timing it has to make sure the timing and number of subtelegrams is conform to the Enocean Radio Protocol specification
		\ref References.
		
		<b>Analog measurements</b>\n

		To perform an analog measurement it is necessary to measure a reference voltage and the source voltage, and then scale it. Because of hardware
		limitation to measure very small and very large voltages, every measurement exists of two measurements again an internal 0.9 V voltage. So in sum we get
		4 measurement values for the scaling computing. As the reference voltage should be constant it is only necessary to measure it once. And if the source voltage
		is a single measurement against VSS it is also possible to measure it once and reuse that measurement value for scaling.

		- #io_ulpMeasAnalog to make a single measurement against the internal 0.9 V voltage.\n
		- #io_ulpScaleAnalog to scale all measured values against a reference voltage.

		The example below shows the use of that functions for performing a single ended measurement of ADIO_1:

		\code
		 sint16 s16negref;
		 sint16 s16posref;
		 sint16 s16adio1value;
		 uint16 u16adio1value;
		 io_enableAnalog(1); // configuring hardware for analog measurement no VGA, increase current to Analog current
		 io_ulpMeasAnalog(RVDD, &s16posref); // measure positive reference against internal voltage
		 io_ulpMeasAnalog(RVSS, &s16negref); // measure negative reference against internal voltage
		 io_ulpMeasAnalog(GPIO1_ADIO_1, &s16adio1value); // measure ADIO_1 against internal voltage
		 io_enableAnalog(0); // restoring previous configuration for radio functionality and reduce current to CPU current
		 io_ulpScaleAnalog(s16posref, s16negref, s16adio1value, s16negref, 8, &u16adio1value); // scale and calculate result for ADIO_1
		\endcode

		The result of the measurement is in u16adio1value, scaled to 8 bit with the reference of RVDD. If a second single measurement of ADIO_2 has to be made, it is
		only necessary to call #io_ulpMeasAnalog with GPIO1_ADIO_2 parameter and to use the previous reference values s16negref and s16posref for scaling this value.
		Besides that it is important to call #io_enableAnalog directly before and after measurement, because it switches on the used analog part which consumes higher
		energy.

		When using the gain amplifier use the #io_ulpMeasAnalogVGA and #io_ulpScaleAnalogVGA in the same matter.

		The difference of using these functions instead of #io_measAnalog or #io_ulpMeasAnalogVGA is the optimized runtime. Especially when performing more than one
		single measurements the repetition of measuring the reference voltages can be avoided.

		<b>Timer functions</b>\n

		It is possible to use the #time_wait function in ultra low power applications for implementing time delays. To save energy this function switches to standby
		mode and will be waked up by the unused timer0 of the Dolphin chip, which is usually reserved for the scheduler. When the scheduler runs in non ulp applications
		the #time_wait function waits in CPU mode using the scheduler for computing the delay.

		\note 
		\ref app_autarkicsens provides a good example how to use ULP function
		

		

		*/

//***************************Dolphin Platform*****************************
/*!	 		
	\page dolphin_platform Dolphin Platform
	
	The Dolphin platform is a system-on-chip transceiver solution for bi-directional ultra low power RF applications which are powered by ambient energy. 
	It comprises a RF transceiver, an 8051 spin off microcontroller core with peripherals. Detailed information about the platform you can find in  
	\ref References, in Dolphin Core Description.
	
	Additional information you can find in the following chapters:	
	- \subpage cpu8051_similar_core - this chapter describes what are the similarities and differences of the Dolphin microcontroller core to the 8051
	- \subpage memory_architecture - this chapter gives on overview of the memory architecture of the microcontroller
	- \subpage flash_architecture, \subpage cfg_areapage - these chapters give an overview of the flash architecture
	
*/

	//***************************8051 similar core*****************************
	/*!	 		
		\page cpu8051_similar_core 8051 Similar Core
		
		The Dolphin microcontroller is an enhanced 8051 core and is based on the industry-standard 8051 architecture. The MCU is an enhanced Intel 8-bit 8051 core 
		with program and data memory located in separate memory spaces (Harvard architecture).  The instruction set supports direct, indirect and register addressing modes.
		The core registers are accumulator, stack pointer and data pointer registers in addition to the general registers.\n\n
		
		More information about the 8051 core you can find here:
			- 8051 tutorial (http://www.8052.com/tut8051)
			- MCSÂ® 51 Microcontroller Family User's Manual http://plit.de/asem-51/mcs51man.htm
			
		\n
		In the following list you can see the features that are compatible to the 8051 core:
		- instruction set and pipeline
		- memory architecture
		- interrupt system (partially)
		
		the following features are proprietary Dolphin implementation:
		- timers
		- uart
		- i/o ports
		- interrupt handling
		- power modes
		- extended address bus
		- flash handling and architecture
		
		<b>Instruction Cycle</b>\n
		As the Dolphin has an enhanced core the instruction execution is significantly faster as by the genuine 8051 Intel. 
		The MCU runs on a 16MHz clock. <b>1 instruction cycle = 6 x XTAL cycles = 375ns</b>. Also some 2-cycle instructions their execution takes in the genuine 8051 2 instruction 
		cycles takes only 1 in the Dolphin core. All these enhancements are also considered in the Keil C51 Simulator when selecting EO3000I platform. \n
		The 1 cycle enhanced instructions are:
		- 92 = MOV bit addr, C
		- 72 = ORL C, bit addr
		- 82 = ANL C, bit addr
		- 86 = MOV dir, @R0 2/2
		- 87 = MOV dir, @R1 2/2
		- 88 = MOV dir, R0 2/2
		- 89 = MOV dir, R1 2/2
		- 8A = MOV dir, R2 2/2
		- 8B = MOV dir, R3 2/2
		- 8C = MOV dir, R4 2/2
		- 8D = MOV dir, R5 2/2
		- 8E = MOV dir, R6 2/2
		- 8F = MOV dir, R7 2/2
		- 92 = MOV bit addr, C
		- A0 = ORL C, /bit addr
		- A3 = INC DPTR
		- A6 = MOV @R0, dir 2/2
		- A7 = MOV @R1, dir 2/2
		- A8 = MOV R0, dir 2/2
		- A9 = MOV R1, dir 2/2
		- AA = MOV R2, dir 2/2
		- AB = MOV R3, dir 2/2
		- AC = MOV R4, dir 2/2
		- AD = MOV R5, dir 2/2
		- AE = MOV R6, dir 2/2
		- AF = MOV R7, dir 2/2
		- B0 = ANL C, /bit addr 2/2
		- C0 = PUSH dir
		- D0 = POP dir
		 
		 									
	*/

	//***************************Memory architecture*****************************
	/*!	 		
 
	\page memory_architecture Memory architecture
	The Dolphin platform has four general types of memory. The memory architecture is the same as 
	for the genuine Intel 8051 (except for RAM0). Therefore make sure to read the \ref cpu8051_similar_core chapter.
	To effectively program the chip it is necessary to have a basic understanding of the memory types:

	- <b>32kB Flash - CODE\n
	Purpose: program execution, data storage\n
	Content lost: flash erase</b>\n					 
	Flash memory where the program and data variables are stored. To store a variable in Keil to this
	memory area use the <b>CODE</b> keyword.
	For more information please read \ref flash_architecture 

	- <b>2kB External Memory - XDATA\n
	Purpose: data storage, (program execution)\n
	Content lost: \ref DeepSleepMode, \ref FlywheelSleepMode, \ref PowerOnReset, \ref PinReset</b>\n
	External memory which is found "off-chip" i.e. not integrated to the microcontroller core but integrated in the 
	Dolphin chip. Since the memory is "off-chip" it requires a dedicated addressing mode and access is slower as to internal memory.\n
	To store a variable in Keil to this memory area use the <b>XDATA</b> keyword. The Dolphin API uses different parts of the XRAM depending on the modules linked to the program. For example
	when using the #mem_writeFlash function the DolphinAPI reserves the first 256 bytes of XDATA for FLASH  operations. \n
	Although the main purpose of the XRAM is to store data it can be also used for program execution. To download a program to XRAM use the EOPX -xram command.
	For more information see DolphinStudio.chm manual in \ref References. The program to the XRAM can be downloaded only if the FLASH code protection bit is not set.

	- <b>256byte Internal Memory - DATA and IDATA\n
	Purpose: data storage\n
	Contents lost: \ref DeepSleepMode, \ref FlywheelSleepMode, \ref PowerOnReset, \ref PinReset</b>\n
	Internal memory integrated on the Dolphin core. This memory area is a shared space between stack and variables.
	To place a variable to this memory area use the <b>DATA</b> or <b>IDATA</b> keyword. Variables in DATA variable 
	is faster than the access to the IDATA.\nDATA variables are accessed directly, IDATA are accessed indirectly, therefore
	variables in DATA are accessed faster. The Dolphin API uses different parts of the DATA and IDATA depending on the module 
	linked to the program. For example when using the \ref radio_grp module the DolphinAPI reserves #RADIO_RXBUFF_NUM bytes 	 
	for (#ug8RxFlags) for radio flags.
		
	- <b>32byte Ultra Low Power Memory - RAM0\n
	Purpose: data storage\n
	Content Lost: \ref PowerOnReset, \ref PinReset </b>\n					 
	Special external memory used to store variables in sleep modes. To store your variables to this memory area 
	use #mem_writeRAM0 function. There is no keyword in Keil for defining variables to be stored in this memory area.
	The DolphinAPI does not uses this memory, it is available for the application.
	
 	\image html mem_architecture.png EO3000I Memory architecture 
	
	<b> \anchor MemoryTypeVariableSpecifier Memory Type Variable Specifier </b>\n
	Following an example how to place data to specific memory location.
	For more information how to use the memory specifiers read the chapter about memory areas in Keil C51 help or here http://www.keil.com/support/man/docs/c51/c51_le_memareas.htm
	
	\code
		uint8 code string[20] = "This is a test";	//constant string stored in Flash Memory
		uint8 xdata var;  //8bit variable stored in External Memory
		uint8 idata var;  //8bit variable stored in Internal Memory - indirect accessed part
		uint8 data var;   //8bit variable stored in Internal Memory - directly accessed part
	\endcode

	\note 
	
	
	\note
  	You can see how much space in which memory is used after the compilation if you open the *.m51 / *.map file.
	For more information read Keil Manual section BL51 / LX51 Linker User's Guide. 
	
	\note
	 Be sure to leave enough space for the STACK in the internal memory, for more information read \ref stack_anal
	
	
*/


	//***************************Flash architecture*****************************
	/*!	 		

	\page flash_architecture Flash architecture
	
	The flash memory size is 32kB and it can used for both program and data storage. 
	It is organised in pages a 256 byte and contains all together 128 pages each of 256 bytes i.e., (128 x 256 byte = 32 k). 
	The smallest block that can be erased is 1 page = 256 bytes. Starting with a freshly erased page 
	(all bytes are initialised to 0xFF), any location within the page can be written. However, once a bit has been written 
	(either to 1 or 0), only by erasing the whole page enables the possibility to write to the same bit location. Failing to 
	do so the data consistency of the the flash can't be ensured!
		
	The flash memory is organised into two parts:
	- \anchor ProgramArea <b>Program Area: 0x0000 - 0x7EFF (127 pages - 32 512 bytes) </b>\n
	Flash area containing program and data information. 
	
	- <b>Configuration area: 0x9F00 - 0x9FFF (1 page - 256 bytes)</b>\n
	Flash area containing hardware identification, hardware calibration and software identification information.  For more information about this area read the \ref cfg_areapage chapter. 
	
	Further the last page of Program Area is logically interpreted as:
	- <b>#LOG_AREA: 0x7E00 - 0x7EFF (1 page - 256 bytes)</b>\n
    This page is intented for storing log information from the Dolphin API and the application.
    This page is used to store system log information of the application (\ref app_log_diag). Using the #LOG_AREA structure the area of this page can be accessed.
    If this page is not used to store log data, it can be used for other purposes.\n 
	An example how to use this page for log data see \ref app_log_diag. \n\n
	
	
	\image html flash_architecture.png FLASH architecture 

	
	<b> \anchor BIST Flash Build In Self Test (BIST)</b>\n
	The Dolphin platform contains a Flash Built In Self Test (BIST) logic. It is useful to verify the program and static data integrity in the flash. 
	The FLASH region on which the BIST integrity check is executed is defined by the user upon compilation time. It is recommended to exclude parts of the flash 
	where dynamic data is stored - i.e. data that keeps changing during application execution. The BIST CRC value is stored as the last byte of the last page
	of the BIST region. EOPX Postbuild Tool saves the program size in pages to the \ref u8PrgSize variable in \ref CFG_AREA.val.u8PrgSize.  
	The following figure shows how is the BIST structured in the flash. 
	
	\image html flash_bist.PNG 
	
	To calculate the BIST for a program the compiled hex file generated with Keil has to patched using the EOPX postbuild tool. For this purpose the following steps have to be executed:
	- Put the <b>setBist</b> command to the postbuild.txt
	- The setBist command aligns the program area hex file to the 256 page boundary and adds as the last byte a CRC value to the hex file and stores the program size value to the CFG file
	- To activate a BIST from the application use the function #mem_flashBist
	- For more information  read the DolphinStudio manual EOPX section, see \ref References


	If you the application have predefined constants in your data area (specified by the BL51 linker and a constant object file) the IntelHex file contains these values. 
	In such case the EOPX postbuild tool needs to differentiate  between the program and data part in the IntelHex file. This can be done by defining the object of the constant 
	in the postbuild.txt. Use the <b>setBist FLASH_DATA2_MOD</b> - where FLASH_DATA2_MOD is the object where the constants are stored. EOPX postbuild will parse the MAP file of the linker 
	to determine where the data starts and program finishes. As an example see the TCM300 source code. \n\n

	
	The following example shall explain how the <setBist> operates:\n
	- if the compiled program size is 256 byte - after patching it with EOPX postbuild tool - it will require 512 bytes (2 pages) in the flash (from 0x0000 - 0x01FF) 
	- the last byte of the downloaded code will be the CRC value (at address 0x01FF) used for the BIST
	- the reason to increase the program size to 512 byte is to store the CRC in the last byte of the last used page without overwriting any program code. Therefore EOPX postbuild tool has to reserves another page
	-	the flash area beyond the program can be used for data storage. 
	
	\image html flash_bist_example.PNG
	
	<b> \anchor CodeprotectionBit Code Protection Bit</b>\n
	The Program and Data area can be protected against readout with the Codeprotection bit (CFG_AREA is not affected by code protection bit and can always be read). When this bit is set 
	the FLASH program can't be read with an extern programmer. To delete this bit the Program-Data area 
	has to be erased. For more information about the Codeprotection bit please read the DolphinStudio manual.

	\note
	You can access the FLASH memory using the \ref mem_grp module functions.
	
	\note
	Read chapter \ref dolphinstudio_keiluvision to see how to configure the Postbuild tools to work with Keil uVision.

	
*/

	//***************************Configuration area*****************************
	/*!	 		

	
	\page cfg_areapage Configuration area

	Flash area containing hardware identification, hardware calibration and software identification information. The CFG_AREA can be <b>always read</b> with the programmer even if the \ref CodeprotectionBit is set.\n
	As the CFG_AREA contains calibration data mandatory for program execution (e.g. calibration values for radio frequency generation) it is recommended not to modify this area during program execution.
  It's recommended to only modify values in a laboratory or production environment using EOPX !
	
		The area is divided to two parts. The first 128 bytes (CFG_AREA.val) contains hardware identification, hardware calibration and software identification information. These informations are put to the following
	groups:
	- SWInfo - information about the firmware residing in the \ref ProgramArea
	- Calibration - modul calibration values (see \ref timer_calibration)
	- TracingInfo - HW modul production tracing information
		
	The other 128 (CFG_AREA.val.u8ReservedApp) bytes are intended to be used by the application. For instance the application can store firmware specific calibration information here.\n 
	Upon a Flash erase the configuration area contents is also lost. Therefore prior erasing the Flash EOPX always reads out the contents of this area 
	and merges the existing data with the application cfg file. For the exact process see \ref ProgrammingFlow.	\n\n

	The API provides the structure #CFG_AREA.val to access all data stored in the configuration area.\n 
	The following examples demonstrates how to access the application version located in the CFG_AREA.\n
	\code	
	CFG_AREA xdata cfg  _at_ CFG_ADDR; //address for reading cfg area
	void main()
	{
		//send the API version through uart
		uart_sendBuffer(&cfg.val.u8AppVersion,4);
	}
	\endcode 

	The variable cfg needs to be global and the memory type specifier <b>xdata</b> is required. Note that even though the CFG_AREA is specified as memory type xdata
	it is actually a special FLASH page (see #flash_arch) and therefore read-only.\n\n

	
	<b> \anchor ApplicationVersion Storing Application version</b>\n	
	There is a memory space reserved in the CFG_AREA to store the library (\ref CFG_AREA.val.u8APIVersion) and application (CFG_AREA.val.u8AppVersion) version. 
	Using the EOPX Postbuild tool with the command <b>setVersion</b> this information is copied into the cfg hex file. The information is very useful to determine which firmware is 
	currently running on the HW module once the module is installed in the field. The information can also be queried through the air using the Remote Management 
	(see Remote Management specification in \ref References).\n\n

	To use this feature, each application should have an array saved in FLASH 
	with the following format:\n
	\code
	code uint8 VERSION_APP[] = {0xE0,'V','E','R','S','I','O','N',VER_MAJOR,VER_MINOR,VER_MICRO,VER_BUILD,'A','T','C','M','3','0',....,'0',0x00,0xE0};		
	\endcode
		
	Where:
    - 0xE0,'V','E','R','S','I','O','N' - characters identifying the version information in the hex file
	- VER_MAJOR,VER_MINOR,VER_MICRO,VER_BUILD - the application version defines
	- 'A','T','C','M','3','0',....,'0' - 'A' is defining the application and the rest characters are the description of the firmware
		
	Example:\n
	\code
	//This array stores the version <b>1.2.0.0</b> of the <b>My App</b> application in FLASH. 
	//EOPX will parse this info from *.hex and burn to the CFG area.
	code uint8 VERSION_APP[] = {0xE0,'V','E','R','S','I','O','N',
															1,2,0,0,                                  // change APP Version here  
															'A',
															'M','y',' ','A','p','p',                  // change APP Description here (max. 15 chars)
															0x00,0xE0};
	\endcode

	\note 
	The array has to begin always with  0xE0,'V','E','R','S','I','O','N', the description has to begin with 'A' and the whole array has to be  finished with 0x00, 0xE0. 
	Between the version number and application description the character 'A' has to be defined.\n\n

	<b>History of the CFG area:</b>\n
	The configuration area structure has been changed several times during the development of the Dolphin platform.  The revision number of the CFG area structure 
	indicates the changes. This version is stored here #CFG_AREA.val.u8CfgVersion. The DolphinAPI library with version 2.x.x.x supports only 
	the revision 3 CFG_AREA structure and later. The table below contains the summarization between versions.

	<table border="1" width="40%" cellpadding="2" cellspacing="0" class="Design1" align="center">
	<tr>   <th>u8CfgVersion</th>      <th>Major changes</th> </tr>      
	<tr>    <td>0xFF, 0x00, 0x01</td>  <td>Configuration area structure of engineering samples</td></tr>
	<tr>    <td>0x02</td>              <td>Added stepcode</td></tr>
	<tr>    <td>0x03</td>              <td>Added and modified calibration values for temperature sensor</td></tr>
	</table>

	\note 
	An example how information from the CFG area can be used to configure your application can be found in \ref app_remanesp3
*/



//***************************Error Diagnostic*****************************
/*!	 		
	\page error_diagnostic Error Diagnostic
	This section describes how to diagnose API and Application (APP) errors. There are several functions implemented in the API to
	help the application track down errors. \n\n

	- \subpage debugging  - provides a tutorial how to debug an application \n
	- \subpage system_log - describes a method to collect runtime log information to identify problems with products in the field\n
	- \subpage stack_anal - describes how to test the stack limits of the application\n
	*/ 
	
	//***************************System Log*****************************
	/*!

	\page system_log System Log
	The DolphinAPI offers a method to store application and library log information in the Flash. These logs can help you identify and diagnose the source of problems 
	with the firmware or module HW. The logs are especially useful for tracking down problems in the field. The logs can be queried both using the EOPX through the programming
	interface or using Remote Management through the radio interface. \n	
	The DolphinAPI has an internal array #u8APIErrLog defined in the XRAM, where the occurrence of the log codes are stored. 
	Every time an error happens the array element at the log code address is incremented by the API. For example if the received telegram has a wrong checksum the log 
	code #ERR_RADIORX_CHKSUM is incremented using the #misc_logSet8 macro. 
	\code
	if (radio_calcChecksum(&rTel) != OK)
	{
		misc_logSet8(u8APIErrLog,ERR_RADIORX_CHKSUM);
		return ERR_CHCK;
	}
	\endcode
	\n
	There are 2 different macros that support log code incrementing: #misc_logSet8 and #misc_logSet16 for 8bit and 16bit codes.
	The log codes are incremented until the maximum value of 0xFE or 0xFFFE. \n\n
	
	<b>Storing System log to Flash memory</b>\n		
	In order to use the system log for diagnostic purposes the API log array  #u8APIErrLog has to regularly (i.e. every few hours or once a day) be stored to Flash memory. 
		
	See the example below how to save both API and Application Log to Flash memory:
	\code
	//structure for reading LOG_AREA
    LOG_AREA code log_read  _at_ LOG_ADDR;
    //structure for writing LOG_AREA
    LOG_AREA xdata log_buff;
    //application Error log
    uint8 u8APPErrLog[APP_ERR_MEM_SIZE];

    //merge u8APPErrLog and  u8ApiErrorLog to buffer log_buff and save it to the flash page
    misc_logSave(&log_buff,u8APPErrLog, APP_ERR_MEM_SIZE);
            
	\endcode


	When reprogramming the application the LOG_AREA values are deleted. Every time the module starts the system log has to 
	be initialised, i.e. read the flash array to the XRAM. This can be done using the #misc_logInit macro.
	See example below:
	\code
	//structure for reading CFG area
	LOG_AREA code log_read  _at_ LOG_ADDR;

	//read API System Log from Flash
	misc_logInit(log_read.val.u8ReservedAPP, u8APPErrLog, APP_ERR_MEM_SIZE);
	\endcode\n\n

	<b>Analysing System Log</b>\n
	The log codes and their addresses are defined in the #API_ERRLOG enum. This enum has a special format.
	Using the DolphinStudio the system log and it's contents can be analysed.\n
	This is done in following way:\n
	- Specify the header in DolphinStudio in the tab "EOPX->System log" where the #API_ERRLOG is stored. 
	- Push the button "Read System Log" 
	.
	DolphinStudio will read the header and search for the comment <b>//>>Section</b>. When found the enum structure is parsed and according the address
	following the <b>//>>SectionEO3000I-API:0x7E80</b> the LOG_AREA flash page is read. The parsed values and comments are than showed in the list box.
	\n\n
	\image html dolphin_error_log.PNG Dolphin Studio System Log 
	\n

	<b>Application System Log</b>\n
	The application can also create it's own system log and store it in the LOG_AREA. Using the special enum structure the APP system log can be analysed
	anytime using the DolphinStudio. The enum system log for the application could be the following:
	\code
	//Custom Application system log
	//>>Section:APP_VALUE_LOG:0x7E80 - this is the address of u8ReservedAPP
	typedef enum 
	{
	// 8bit example of APP system log variable
	ERR_APP8 = 0,
	// 16bit example variable
	ERR_APP16_L,	
	ERR_APP16_H,		
	// log memory size, has to stay as the last enum
	APP_ERR_MEM_SIZE,
		
	} APP_ERRLOG;
	//>>SectionEnd
	\endcode
	This enum has to be defined in the application header/source file. For 16bit log codes the enum values has to have the suffix _L and _H. 
	The application can store it's system log to the LOG_AREA (see #u8ReservedAPP in LOG_AREA). 
	For system log analysis the header/source file has to be given to DolphinStudio.\n\n
	For more information how to use system log see example \ref app_errordiagnostic .\n

	\note Make sure to take a look at the \ref app_log_diag example.
	
	\note Once the \ref CodeprotectionBit is set the LOG area can't be read out using the programmer. In such case use the Remote Management methods to query the 
	information through the radio interface. 

	 \note
    Half of the LOG page is reserved for API errors so the application should place it's log files beyond address 0x7E80.
	*/
	
	//***************************Stack Anal*****************************
	/*!
	
	\page stack_anal Stack Analysis
	The 8051 core has no HW possibility to detect stack overflow situations. That's why the DolphinAPI offers a function for analysing the stack.
	The stack is situated in the internal data memory (for more info see \ref memory_architecture). There are only 256 bytes of internal data available.\n\n

	To know where does the stack of your application begins you can check the M51 file and see where the <b>?STACK</b> is stored. It is always allocated after the last
	variable in the internal data. From this address the STACK will grow upward until the 256 limit. Each time a function is called or there is an interrupt, the stack will grow 2 bytes.
	Because the Dolphin API uses two interrupt levels, it can be possible, that two interrupts are pending same time, so reserve 4 bytes of stack use for that. 
	Each API function prototype shows how many nested function it contains so the application can approximate what is the current stack usage. 
	Of course the application can't see how big stack is required for the interrupts and also can't predict when is an interrupt executed.\n\n
	
	To be sure that there is no stack overflow the amount of stack usage can be calculated using the #misc_getStackReserve function. This function requires that by the 
	startup in startup.a51 the internal data is initialised to 0x00. When calling this function it calculates how many memory addresses in the internal data are still 0x00. 
	From this information the stack usage can be evaluated. If there is situation in the application where only ca. 1-3 bytes of internal data are still 0x00, than the application has 
	to free some more internal data, otherwise there is a danger of a stack overflow.\n\n

	For more information read the #misc_getStackReserve function description. 
	
	\note Make sure to take a look at the \ref app_stack_diag example.\n
	*/


//***************************Debugging*****************************
/*!
	\page debugging Debugging
	There are 2 possibilities to debug Dolphin platform applications:\n\n

		
	<b>Custom UART</b>\n
	Custom debug messages using sprintf, uart_sendBuffer	\n
	<i>Pros:</i>\n
	+Real time\n
	+Fully customized\n\n
	<i>Cons:</i>\n
	-UART blocked\n
	-Custom implementation needed\n
	
	<b>Keil Simulator</b>\n
	Debugging the application in  the simulator\n
	<i>Pros:</i>\n
	+Single stepping\n
	+Breakpoints\n
	+Watch\n\n	
	<i>Cons:</i>\n
	-DolphinHW events not supported  (radio, timers, sleep modes)
	
*/
	

	

//***************************EnOcean Serial Protocols*****************************
/*!	 	

  \page enocean_serial_protocols EnOcean Serial Protocols
  EnOcean devices can use 2 different protocol stack:
  - \subpage esp2_page
  - \subpage esp3_page

  The ESP2 and ESP3 protocol is designed to transfer information between EnOcean device and host using UART interface.

  Telegrams received/transmitted with the ERP protocol can be encapsulated either by ESP2 or ESP3 and transfered to the UART interface.
  The ESP2 is a protocol for the 1st generation EnOcean devices (RCM1xx/TCM1xx) and it has several limitations. That's why the introduction of ESP3 protocol was needed.

  <b>Limitations of ESP2:</b>\n
  - Some of the Radio Telegrams encapsulated by ESP2 have dummy 0x00 bytes (RPS/1BS/HRC)
  - The ORG in some of the Radio Telegrams encapsulated by ESP2 is different than the Radio telegram CHOICE. These orgs are defined in \ref ORG_TYPE
  - The Radio Telegram encapsulation by ESP2 doesn't support the transmission of TEL_PARAM_TYPE information (subtelegram, dBm, Destination ID)
  
  With ESP3 the radio telegrams are encapsulated 1:1 inclusive the TEL_PARAM_TYPE structure.
  
  Basic Differences between ESP2 and ESP3 are summarized in this table:
  
  <table border="1" width="100%" cellpadding="2" cellspacing="0" class="Design1" align="center">
    <tr> <th></th>                     <th>ESP2</th>                                                     <th>ESP3</th>                                  </tr>  
    <tr> <th>Device Support</th>       <td>Supported by both 1st generation and Dolphin platform</td>    <td>Supported only by Dolphin Platform</td>    </tr>
    <tr> <th>Data Overhead</th>        <td>4 bytes</td>                                                  <td>6 bytes</td>                               </tr> 
    <tr> <th>Max. Payload</th>         <td>30 bytes</td>                                                 <td>65535 bytes</td>                           </tr>
    <tr> <th>Speed</th>                <td>device specific, default 9600 baud</td>                       <td>device specific, default 57600</td>        </tr>
    <tr> <th>Type of data</th>         <td>Radio Telegram<br>Command Telegram</td>                       <td>Any type of data</td>                      </tr>
    <tr> <th>Max. number of data types</th> <td>8 (RRT,TRT,RCT,TCT, etc)</td>                            <td>255</td>                                   </tr>
    <tr> <th>Data verification</th>    <td>Checksum</td>                                                 <td>8bit CRC</td>                              </tr>
    <tr> <th>Versioning support</th>    <td>No</td>                                                       <td>Yes</td>                                   </tr>
    <tr> <th>Basic data structure</th> <td>Serial telegram</td>                                          <td>Packet</td>                                </tr>   
  </table>
  \n
  \note
	It's recommended to use ESP3 for new designs!

*/

	//***************************ESP2 protocol*****************************    
	/*!	 
		\page esp2_page EnOcean Serial Protocol 2 (ESP2)

		The ESP2 protocol encapsulates radio telegrams and sends/receives them through the UART interface. The ESP2 can also receive/transmit command telegrams 
		in order to control a device. It is a protocol first generation EnOcean HW modules where using.

		\note
		<b>It's recommended to use ESP3 for new designs!</b>

		The basic structure of the ESP2 protocol is the serial telegram (TEL_SERIAL_TYPE).
	  
		\image html esp_telegram.png ESP2 Serial telegram structure 

		
		A serial telegram contains the following fields (without Sync):
		- 1 byte Header - consisting of 3bit \ref HSEQ_TYPE and 5bit LENGTH
		- 1 byte ORG/SORG -  the \ref HSEQ_TYPE together with \ref ORG_TYPE gives an unique telegram type identification. 
		- x byte DATA - data bytes
		- 1 byte CHECKSUM - controlling checksum
		
		The serial telegram is defined with the \ref TEL_SERIAL_TYPE structure. To send and receive serial telegrams
		use the \ref uart_grp module. When encapsulating a radio telegram to a serial telegram the \ref CHOICE_TYPE of 
		the ERP telegram is converted to \ref ORG_TYPE and vice versa and a dummy bytes are added.	
	  To convert between \ref TEL_SERIAL_TYPE and \ref TEL_RADIO_TYPE use the \ref misc_serialToRadio and \ref misc_radioToSerial functions.


	  <b>Checksum calculation:</b>\n
	  Sum of bytes starting from HEADER byte finishing with the last DATA_BYTE (both inclusive). 
	  Example code to calculate checksum:
	  \code
	  for (BYTE i=2;i< m_ucTelLength + 2; i++)
		checksum += (BYTE)m_ucRawTel[i];
	  \endcode
	  
	  \note CHOICE and RORG are is the same byte in the ERP protocol. ORG and SORG is the same byte in ESP2.
	  
	  \note
	  More information about ESP2 protocol you can find in the respective TCM120, TCM300 user manuals:\n
	  http://www.enocean.com/en/enocean_modules/tcm-300/\n
	  http://www.enocean.com/en/enocean_modules/tcm-120/\n
	  	  
	  \note The usage of ESP2 you can find in example \ref app_radiotoserial.
	*/

	//***************************ESP3 protocol*****************************    
	/*!	 
	\page esp3_page EnOcean Serial Protocol 3 (ESP3)
	
	See \ref References, EnOcean Serial Protocol 3.pdf. \n
	
	\note The usage of ESP3 you can find in example \ref app_radiotoserial, \ref app_radiotoesp3 and \ref app_remanesp3.
	
	*/ 

	//***************************EnOcean Radio Protocol*****************************
	/*!	 	
  
	\page enocean_radio_protocol EnOcean Radio Protocol (ERP)
	 The ERP protocol is designed to transfer information between EnOcean devices using the Radio interface.\n
	 More information about the ERP you can find in EnOcean Radio Protocol.pdf, \ref References.
	 
	  
	Telegram received/sent from the AIR are encapsulated according to the EnOcean Radio Protocol.
	For easier handling/accessing of radio telegrams the Dolphin API uses one orthogonal data structure for all telegram types.   

	\image html erp_telegram.PNG ERP telegram structure 

	A radio telegram contains the following fields:
	- 1 byte Choice (also called RORG) (\ref CHOICE_TYPE) - indicating the telegram type
	- X byte DATA - data bytes
	- 4 byte unique ID identifying the sender (or BaseID)
	- 1 byte STATUS - status byte
	- 1 byte CHECKSUM - controlling checksum
	
    
  The table below summarizes the relation between the EnOcean Radio Protocol (ERP) and the EnOcean Serial Protocol 2 (ESP2, Choice <> ORG) and 
  indicates the telegram transmission time. 
  
    <table border="1" width="80%" cellpadding="2" cellspacing="0" class="Design1" align="center">       
    <tr> <th>Choice/RORG (ERP)</th> <th>ORG/SORG (ESP2)</th>   <th>Length</th>   <th>type</th>          <th>pay load</th>   <th>Transmission time in AIR 868MHz (by 315Mhz +64us) </th>      </tr>
                         
    <tr> <td>0xF6</td>   <td>0x05</td>  <td>8 byte</td>     <td>RPS</td>                       <td>1 byte</td>     <td>896 us</td>      </tr>
    <tr> <td>0xD5</td>   <td>0x06</td>  <td>8 byte</td>     <td>1BS</td>                       <td>1 byte</td>     <td>896 us</td></tr>
    <tr> <td>0xA5</td>   <td>0x07</td>  <td>11 byte</td>    <td>4BS</td>                       <td>4 byte</td>     <td>1184 us</td>   </tr>
    <tr> <td>0xA3</td>   <td>0x08</td>  <td>8 byte</td>     <td>HRC</td>                       <td>1 byte</td>     <td>896 us</td>  </tr>
    <tr> <td>0xA4</td>   <td>0x09</td>  <td>11 byte</td>    <td>SYS</td>                       <td>4 byte</td>     <td>1184 us</td>  </tr>
    <tr> <td>0xC5</td>   <td>0xC5</td>  <td>16 byte</td>    <td>SYS_EX</td>                    <td>8 byte</td>     <td>1856 us</td>  </tr>
    <tr> <td>0xD6</td>   <td>0x10</td>  <td>11 byte</td>    <td>6DT (not supported)</td>       <td>6 byte</td>     <td>1184 us</td> </tr>
    <tr> <td>0xD3</td>   <td>0x11</td>  <td>5 byte</td>     <td>MDA (not supported)</td>       <td>n.a.</td>       <td>608 us</td></tr>
    <tr> <td>0xA6</td>   <td>0xA6</td>  <td>+5 byte</td>    <td>ADT	</td>                      <td>+5 byte</td>    <td>+480 us</td>  </tr>
    <tr> <td>0xC6</td>   <td>0xC6</td>  <td>17 byte</td>    <td>SmartACK Learn Request</td>    <td>10 byte</td>    <td>1760 us</td></tr>
    <tr> <td>0xC7</td>   <td>0xC7</td>  <td>15 byte</td>    <td>SmartACK Learn Answer</td>     <td>7 byte</td>     <td>1568 us</td> </tr>
    <tr> <td>0xA7</td>   <td>0xA7</td>  <td>8 byte</td>     <td>SmartACK Reclaim</td>          <td>n.a.</td>       <td>896 us</td>		 </tr>
    <tr> <td>0xD0</td>   <td>0xD0</td>  <td>8 byte</td>     <td>SmartACK Signal</td>           <td>n.a.</td>       <td>896 us</td>		 </tr>
    <tr> <td>0xD1</td>   <td>0xD1</td>  <td>8..21 byte</td> <td>Manufacture Specific Communication</td> <td>custom</td>  <td>custom</td>		 </tr>
    <tr> <td>0xD2</td>   <td>0xD2</td>  <td>8..21 byte</td> <td>Variable Length Data</td>       <td>1..14 byte</td>     <td>896...2144 us</td>		 </tr>
    <tr> <td>0xD4</td>   <td>0xD4</td>  <td>8..21 byte</td> <td>Variable Length Learn</td>      <td>1..14 byte</td>     <td>896...2144 us</td>		 </tr>
  </table>
  
  \note CHOICE and RORG are is the same byte in the ERP protocol. ORG and SORG is the same byte in ESP2.
  
  \note For the RF transmission additional bits are added, e.g. Preamble, SOF (Start Of Frame), SyncFields, Inverse Bits and EOF (End Of Frame). 

  \note The ERP telegram structure does not contain an explicit telegram length information.
  The length is implicit given by the Choice field. Also see \ref RADIO_TEL_LENGTH. 

  \note The radio telegrams are defined with the \ref TEL_RADIO_TYPE structure. To send and receive radio telegrams
  use the \ref radio_grp module.

  \note All telegrams (RPS, 1BS, 4BS, etc.) are considered to be broadcasts because they don't transmit destination ID.
  To send a telegram as an UNICAST the ADT encapsulation has to be used. For more information please see \subpage adt_page.
  
  \note For more information how the repeater works see \subpage repeater_page.

  \note Telegram chaining, to send 'long' amounts of information is described in \subpage tel_chaining_page
  
  \note Secure telegrams are covered under \subpage security_protocol_page

  \note Duty cycle limitation for 868 MHz in Europe see \subpage duty_cycle_page

  \note Ignore the checksum of the radio telegram delivered in TEL_RADIO_TYPE structure. It is only for internal usage. This value is used intern in the library
  and doesn't have to be valid on the application layer. This is due to the fact that several repeated telegrams can be merged in one telegram, but the checksums 
  are evaluated only once upon the subtelegram reception. 

  
*/



	//***************************Addressed Telegrams (ADT)*****************************
	/*!	 

		\page adt_page Addressed Telegrams (ADT)
	  
		The Dolphin platform extends the approach of only sending broadcast (no destination address => broadcast) telegrams. 
		ADT telegrams now allow to address a telegram to a specific receiver.
		 
		For backward compatibility existing telegrams are encapsulated into ADT telegrams. A dedicated choice/rorg 
		\ref CHOICE_TYPE "RADIO_CHOICE_ADT" (1 byte) is used and 4 byte destination ID are added. Resulting in 5 byte additional 
		length. 
		
		\note In principle all telegrams can be encapsulated. But the current Dolphin API version only supports  
		a max. length of telegrams to be encapsulated. See \ref CHOICE_TYPE for further details. 

		\note Although not encapsulated telegrams are sent as broadcast, there is also a possibility to send ADT encapsulated telegram 
		as a broadcast when the DestinationID is set to 0xFFFFFFFF.
		
		 \image html erp_encapsulation.PNG ERP ADT encapsulated telegram structure 
		
		 The ADT encapsulation and decapsulation are done automatically by the Dolphin API. The additional 
		destination ID information is handled via the TEL_PARAM_TYPE data structure:
			<ul>
			<li>If the \ref TEL_PARAM_TYPE "p_tx.u32DestinationId" is 0 then no encapsulation is done (broadcast). Otherwise if not 0 
		then encapsulation is performed (ADT).
			</li>
			<li>If the received telegram was addressed and decapsulated then the \ref TEL_PARAM_TYPE "p_rx.u32DestinationId" will 
		provide the address information (receiving). For broadcast (with and without encapsulation) telegrams \ref TEL_PARAM_TYPE "p_rx.u32DestinationId" will be 0xFFFFFFFF.
			</li>
			
			</ul>
		
		Also see \ref example_applications "example applications" on how to use addressed telegrams. 
	*/


	//***************************Repeater*****************************
	/*!
		\page repeater_page Repeater				
		Repeaters are necessary when the distance between sender and receiver is too large to establish an adequate radio connection. 
		Then the repeater will be placed in a distance where both, sender and receiver have a good connection to the repeater. 
		The job of the repeater is to receive the telegram from the sender and send it again, so that the target receiver can get it. 
		For a bigger distance it is possible to place maximum two repeaters in a row.
		
		\note
		More information about the Repeater you can find in EnOcean Radio Protocol.pdf, \ref References.
		
		
		To limit the amount of repeated telegrams in an environment with more repeaters we differ between two repeater levels:
		- 1 Level Repeaters repeat only received original radio telegrams
		- 2 Level Repeaters repeat only received original or once repeated radio telegrams.

		The repeater always repeats with 3 subtelegrams. All original and repeated subtelegrams has to arrive within the 100ms maturity time.
		Therefore all original and repeated subtelegrams are saved to the same HW buffer. Thus they appear only as 1 radio telegram to the application.  
		If the subtelegram number is higher than 3 the application can detect that also repeated subtelegrams has been received. Although it is possible
		that the target receiver doesn't hear the original subtelegrams only the repeated one. In such case the application can prove the status 
		of the telegram to see if the telegram was repeated.  If a 2 level repeater receives the original and also the 1 level repeated radio telegram, it will only repeat the 
		telegram once. 
		
		 
		\note
		If you want that a telegram sent from your application is not repeated, set the lower 3 bits of the status byte to 1.
		For instance telegram that is never repeated and uses 8bit checksum would have status 0x0F, telegram with 8bit CRC would have status 0x8F    
		
		\note  
		If a repeater receives original and repeated subtelegrams, the status byte of the 1st subtelegrams defines if the telegram is repeated again or not.
		The same behavior has the API interface. When calling radio_getTelegram you always receive the status byte of the first subtelegram, even if 
		several subtelegrams from repeaters has been received. 
		
		\note
		When you enable the repeater functionality in the API using the \ref rep_grp module the API will repeat every telegram without the interference to the application.
		If you want to indicate for instance with a LED on your module when a telegram is repeated do the following:
		- switch on the repeater 
		- check the status of the telegram received by radio_getTelegram
		- if the status is <2 or <1 (depending on the repeater level you set) flash the LED
		
		
		
	*/


	//***************************Telegram chaining*****************************
	/*!
		\page tel_chaining_page Telegram chaining and messages				
It is not possible to send a radio telegram that is longer than 21 bytes. 
	It is not possible to send a radio telegram that is longer than 21 bytes. 
	If the information to be sent is longer, the Dolphin API allows you to do it by "chaining" telegrams.
	To chain telegram the following sequence must be followed:

	 - The information to be sent must be packed in a message of type #MESSAGE_TYPE.
	 - The #msg_send function, which creates the chained telegrams and send them, must be called from the application. 

	A message is splitted by #msg_send into several chained telegrams following this scheme:
 

					  Message			     						  
				 1 byte    N-Bytes	    4 bytes						
	       |--------------|--------|---------------|               
		   |	CHOICE	  |  DATA  |   SOURCE_ID   |  -->  
		   |--------------|--------|---------------|       
	
					 Telegram 1
			1 byte	    2bits 6 bits     2 bytes	1 byte	 10 bytes	 4 bytes	   1 bytes
	    |--------------|-----|---------|----------|--------|---------|------------|---------------|
		| R-ORG = 0x40 | SEQ | IDX = 0 |LEN = N+1 | CHOICE |  DATA   | SOURCE_ID  | STATUS = 0x00 |  +
	    |--------------|-----|---------|----------|--------|-------- |------------|---------------|
	
	  				 Telegram 2
		      1 byte	 2bits 6 bits   <=13 bytes	 4 bytes	   1 bytes
	     |--------------|-----|--------|---------|------------|----------------|        
	  +  | R-ORG = 0x40 | SEQ | IDX =1 |  DATA   | SOURCE_ID  |  STATUS = 0x00 |  + ...
	     |--------------|-----|--------|---------|------------|----------------|

	
 - There are so many telegrams as are necessary to encapsulate the message DATA.
 - The last telegram contains the minimum necessary DATA length to pack the last message DATA bytes. 
 - Every telegram is sent by #msg_send with choice #RADIO_CHOICE_CDM
 - Every telegram belonging to the same message contains the same SEQ code. SEQ code changes from message to message. #msg_send manages the SEQ value
 - IDX is an index that identifies the order of the telegrams.  The first telegram receives IDX=0, the second IDX=1 and so on.
 - The field LEN indicates the amount of bytes contained in the message CHOICE and DATA fields. The LEN field is sent only in the first telegram. 
 - The message CHOICE field is encapsulated in the first telegram, after the LEN field.
 - DATA is splitted in several telegrams without changing the byte order in the message. The 1st telegram can contain a maximum a 10 DATA bytes. The next telegrams a maximum of 13 bytes.
 - The telegrams SOURCE_ID is the same as in the message. 
 - Telegram STATUS field is 0x00.


 <b>The secure teach-in message telegram chaining</b>\n
 This special message, used during the secure teach-in procedure (see #sec_createTeachIn), is splitted in a slightly different form by the #msg_send function.
 The reason for it is to save energy.

 
	                                          Teach-in message
	        1 byte      4 bits     2 bits    2 bits  1 byte  2 bytes  16 bytes      4 bytes 
	  |---------------|---------- |--------|-------|-------|-------|----------|-----------|        
	  | CHOICE = 0x35 | RESERVED  |  TYPE  |  INFO | SLF   |  RLC  |    KEY   | SOURCE_ID | -->
	  |---------------|---------- |--------|-------|-------|-------|----------|-----------|       
	                  |                                                       |
	                  |<-------------------------- DATA --------------------->|
	                                                                               
	
	                                    Telegram 1
	    1 byte        2bits   2 bits   2 bits  2 bits  1 byte 2 bytes 10 bytes   4 bytes       1 byte
	  |--------------|-------|--------|-------|-------|-----|-------|--------|-----------|--------------|
	  | R-ORG = 0x35 | IDX=0 | CNT=2  |  TYPE | INFO  | SLF |  RLC  |   KEY  | SOURCE_ID |STATUS = 0x00 | +
	  |--------------|-------|--------|-------|-------|-----|-------|--------|-----------|--------------|
	
	                                    Telegram 2
	          1 byte       2bits   6 bits    6 bytes    4 bytes          1 byte
	     |--------------|-------|----------|--------|-----------------|----------------|       
	 +   | R-ORG = 0x35 | IDX=1 | RESERVED |   KEY  |    SOURCE_ID    | STATUS = 0x00  |     
	     |--------------|-------|----------|--------|-----------------|----------------|


 - All telegrams are sent with choice #RADIO_CHOICE_SEC_TI
 - The DATA contained in the original message is part of the a #SECU_TYPE type variable, which contains the information about the security protocol in operation mode.
 - In the first telegram the field CNT indicates the amount of telegrams sent in total.
 - The field IDX (index) identifies the order of the telegram.
 - The DATA bytes that do not fit in the 1st telegram are packed in the 2nd telegram
 - The telegram SOURCE_ID is the same as the message ID.
 - The telegram STATUS is 0x00.


	*/
	//***************************EnOcean Secure Radio Protocol*****************************
	/*!	 	
  
	\page security_protocol_page Security

	The ERP includes security. Telegram data can be encrypted and authenticated. These mechanisms avoid telegram eavesdropping and replay attacks. The secure protocol is described in detail under http://www.enocean.com/en/knowledge-base/.
  	The module \ref sec_grp implements data structures and the algorithms necessary to manage encryption/decryption, telegram authentication and rolling code management. 

	There are two radio structures that transport secure-related information. 

	<b>Security telegram</b>\n
	This telegram is sent in operation mode, once the secure protocol has been established by a teach-in message.\n\n
    <table border="1" width="80%" cellpadding="2" cellspacing="0" class="Design1" align="center">       
    <tr> <td>RORG-S</td>  <td>DATA</td>   <td>RLC</td>   <td>CMAC</td>  <td>SOURCE ID</td>  <td>STATUS</td> </tr> 
	</table>

	- RORG-S    [8 bits]            Secure (S) message CHOICE/RORG identificator. Its code is #RADIO_CHOICE_SEC_TI.
	- DATA      [8/16/../112 bits]  Encrypted DATA
	- RLC       [0/16/24 bits]      Current rolling code in the sender.
	- CMAC      [0/24/32 bits]      Cipher message authentication code. 
	- SOURCE ID [32 bits]           Sender ID.


	<b>Teach-in message</b>\n
	Establishes rules for the secure protocol between sender and receiver.\n\n
    <table border="1" width="80%" cellpadding="2" cellspacing="0" class="Design1" align="center">       
    <tr> <td>RORG-TS</td>  <td>TEACH_IN_INFO</td>   <td>SLF</td>   <td>RLC</td>  <td>KEY</td>  <td>SOURCE ID</td>  </tr> 
	</table>

	- RORG-TS        [8 bits]        Secure (S) teach-in message CHOICE/RORG identificator. Its code is #RADIO_CHOICE_SEC_TI.
	- TEACH_IN_INFO  [8 bits]        General information about security protocol. the 4 most significant bits are reserved.  
	- SLF            [8 bits]        Security Layer Format. Specifies the secure protocol comunication that will be established in operation mode: rolling code field length, CMAC length, encryption algorithm 
	- RLC            [0/16/24 bits]  Current Rolling Code in the sender to synchronise the receiver.
	- KEY            [<=128]         Sender private key.
	- SOURCE ID      [32 bits]       Sender ID.
	 
	Security API module information is found under \ref sec_grp.\n

    More detailed information about the security protocol can be read under http://www.enocean.com/en/knowledge-base/ 
*/

	//***************************EnOcean Duty Cycle limitation *****************************
	/*!	 	
  
	\page duty_cycle_page Duty Cycle limitation

Applicable regulation in Europe 868 MHz only requires that any given EnOcean device will not exceed a transmission duty cycle of 1% based on a 60 minute rolling window. This means that for any given 60 minute interval, no more than 36 seconds of transmission are allowed.

To do so, the 60 minute regulatory interval is divided into n time slots of equal length. The number n of time slots can be adjusted in EO3000I_cfg.h by use of Dolphin Studio. For each of these time slots, the total transmission time is then recorded. In addition to that, the transmission time in the current time slot is also recorded.
New telegrams will only be transmitted if the total transmission time in the previous n time slots (representing a full 60 minute interval), the transmission time in the current time slot and the transmission time of the current telegram combined do not exceed the regulatory limit.
EnOcean recommends ten time slots per hour (n=10). This choice provides a good compromise between memory requirements and estimation accuracy. Compliance with the duty cycle limit of 1% will be guaranteed under all conditions by this implementation.

To enable automatic supervision of the duty cycle limitation enable functionality in Dolphin Studio and generate the configuration files. Then a call to \ref radio_initDutyCycleLimit is performed in mainInit().

\note
If you can ensure duty cycle limitation in your application disable functionality in Dolphin Studio

\note
In all ultra low power applications usually duty cycle limitation is no issue due to the limited energy ressources. It is in the responsibility of the application to ensure the duty cycle limitation.	

*/

//***************************APPLICATION EXAMPLES*****************************
// Examples of the applications can be found in the Client_APP directory with the file names app_xxx.c

/*!
 \page example_applications Example Applications
 	Here you can find the source code of several simple application to demonstrate the functionality of the DolphinAPI.
 	The source codes are also part of the DolphinAPI package (folder Examples). The Example Projects are created for both uVision3 and uVision4
	\n\n
	There are several targets in the Examples project:
	- Simulator_868 - Compiled with 868MHz radio settings, when starting Debugger Keil Simulator starts
	- Simulator_315 - Compiled with 315MHz radio settings, when starting Debugger Keil Simulator starts
	- Simulator_902 - Compiled with 902MHz radio settings, when starting Debugger Keil Simulator starts
	
	\note 
	<b>As standard target use the Simulator_868/315 Target.</b>
	
	\n\n
	The examples are optimized for the EVA320-2 and EVA300-3. If you want to run the examples on the ASIC EVA board you 
	have to adjust the pin initialization. \n\n
	Each example contains a .dat file. This is a profile file from DolphinStudio. For more information how to work with the profiles read the DolphinStudio chm manual 
	Working with DolphinStudio\EO3000 Configuration\Profiles in \ref References.	
	\n\n
	<table border="1" cellpadding="2" cellspacing="0" class="Design1" align="center">
	  <tr> <th>Example name</th><th>Optimized for EVA board</th></tr>
  	<tr> <td>\subpage app_adt</td>  			             <td>EVA300-2</td></tr>
  	<tr> <td>\subpage app_autarkicsens</td>            <td>EVA320-2</td></tr>
  	<tr> <td>\subpage app_deepsleep</td>               <td>EVA320-2</td></tr>
  	<tr> <td>\subpage app_errordiagnostic</td>	       <td>EVA300-2</td></tr>
    <tr> <td>\subpage app_flywheel</td>	               <td>EVA300-2</td></tr>
  	<tr> <td>\subpage app_lightcontrol</td>		         <td>EVA300-3</td></tr>
    <tr> <td>\subpage app_radiotoserial</td>		       <td>EVA320-2</td></tr>
    <tr> <td>\subpage app_radiotoesp3</td>		         <td>EVA320-2</td></tr>
    <tr> <td>\subpage app_readanalog</td>		           <td>EVA320-2</td></tr>
    <tr> <td>\subpage app_reman</td>		             <td>EVA300-3</td></tr>  	
    <tr> <td>\subpage app_securelightcontrol</td>		 <td>EVA300-3</td></tr>  	
    <tr> <td>\subpage app_smartack</td>		             <td>EVA300-3/EVA320-2</td></tr>  	
  	<tr> <td>\subpage app_standby</td>  		           <td>EVA320-2</td></tr>  
  	<tr> <td>\subpage app_stm300</td>  		           <td>EVA320-2</td></tr>  
    <tr> <td>\subpage app_tcm300</td>  		           <td>EVA300-3</td></tr>  
    <tr> <td>\subpage app_vld</td>  		            <td>EVA300-3/EVA320-2</td></tr>
    <tr> <td>\subpage app_rssiexample</td>               <td>EVA300-3</td></tr>
    <tr> <td>\subpage app_remanesp3</td>               <td>EVA300-3</td></tr>

	
		
  </table>
	<p>
*/

//*******************************ADT Example***************************
/*!  
	\page app_adt ADT Telegrams 
	Application demonstrating how to use addressed telegrams (ADT - Address Destination Telegrams).
	\n\n In previous EnOcean systems no destination address was used meaning that all telegrams were handled like broadcast messages.
  By enhancing the telegrams with a destination address (destinationID) its possible to send a telegrams to a specific module. 
  \n\n For instance (see picture below) a Gateway wants to request a sensor value from Sensor 3. It first sends an 
  ADT telegram to Sensor 3. Then Sensor 3 replies with an 1BS telegram (broadcast). Sensor 1 and Sensor 2 do not reply 
  because they were not addressed.

  
 	\image html adt_example.png ADT application example    
  
  To demonstrate this a system of one \subpage app_adt_gateway "Gateway" and one \subpage app_adt_sensor "Sensor" are implemented.
  For both functionalities a separated software project exists.   
     

	\page app_adt_gateway ADT Gateway
  \n\n  

  The picture below shows the traffic. The messages Nr. 1,3,4,5 are the requests of the Gateway (ID 0x40000F)
  to the Sensors (IDs 0x400040, 0x400041, 0x400042). And message Nr. 2 and 6 are the replies of 
  Sensor (ID 0x400040) with the Sensor data 0x55.
 	\image html adt_winetel.PNG ADT WinEtel showing ADT telegrams        
         
	\n\n Application file - main.c
	\include ADT-AddressDestinationTelegram\ADTGateway\main.c
	\n\n Config file - EO3000I_CFG.h
	\include ADT-AddressDestinationTelegram\ADTGateway\EO3000I_CFG.h

	\page app_adt_sensor ADT Sensor
  \n\n  

  \n\n Application file - main.c
	\include ADT-AddressDestinationTelegram\ADTSensor\main.c
	\n\n Config file - EO3000I_CFG.h
	\include ADT-AddressDestinationTelegram\ADTSensor\EO3000I_CFG.h
*/

//*******************************Autarkic Sensor Example***************************
/*!  
	\page app_autarkicsens Autarkic Sensor
  \n\n Application file - main.c
	\include AutarkicSensor\main.c
	\n\n Config file - EO3000I_CFG.h
	\include AutarkicSensor\EO3000I_CFG.h
*/

//*******************************Deep Sleep Example****************************
/*!      
	\page app_deepsleep DeepSleep
	\n\n Application file - main.c
	\include Deepsleep\main.c
	\n\n Config file - EO3000I_CFG.h
	\include Deepsleep\EO3000I_CFG.h
*/  

//*******************************Error Diag Example****************************
/*!  
	\page app_errordiagnostic Error Diagnostic
  These applications demonstrates how to detect dynamical errors or problems in application. For 
  more information be sure to read the \ref err_diag chapter.
  
  There are 2 examples that demonstrates how to detect problems: \subpage app_log_diag, \subpage app_stack_diag.  

	\page app_log_diag SystemLog
	\n\n Application file - main.c
	\include ErrorDiagnostic\SystemLog\main.c
	\n\n Config file - EO3000I_CFG.h
	\include ErrorDiagnostic\SystemLog\EO3000I_CFG.h

  \page app_stack_diag StackUsage
  \n\n Application file - main.c
	\include ErrorDiagnostic\StackUsage\main.c
	\n\n Config file - EO3000I_CFG.h
	\include ErrorDiagnostic\StackUsage\EO3000I_CFG.h
     
*/  

//*******************************Flywheel Example****************************
/*!      
	\page app_flywheel Flywheel	
	\n\n Application file - main.c
	\include Flywheel\main.c
	\n\n Config file - EO3000I_CFG.h
	\include Flywheel\EO3000I_CFG.h
*/  

//*******************************Light Control Example****************************
/*!      
	\page app_lightcontrol Light Control Example
  \n\n Application file - main.c
	\include LightControl\main.c
	\n\n Config file - EO3000I_CFG.h
	\include LightControl\EO3000I_CFG.h
	\n\n Module for handling buttons - mod_button.c
	\include LightControl\mod_button.c
	\n\n Module for handling buttons - mod_button.h
	\include LightControl\mod_button.h
*/  

    
//*******************************Radio to Serial Example****************************
/*!      
	\page app_radiotoserial Radio To Serial Example
	Simple application demonstrating receiving telegrams with the radio module and sending it to the serial port using the ESP2 protocol
	\n\n Application file - main.c
	\include RadioToSerial\main.c
	\n\n Config file - EO3000I_CFG.h
	\include RadioToSerial\EO3000I_CFG.h
*/  


//*******************************Read Analog Example****************************
/*!      
	\page app_readanalog ReadAnalog Example
	Application demonstrating  reading analog values triggered by UART.
	\n\n Application file - main.c
	\include ReadAnalog\main.c
	\n\n Config file - EO3000I_CFG.h
	\include ReadAnalog\EO3000I_CFG.h
*/  

//***************************Remote Management Example*****************************
/*!

	\page app_reman Remote Management Example
	The Remote Management allows EnOcean devices to be configured and maintained through the air interface using 
	radio or serial telegrams. Sensors or switches shall be learned into or deleted from already installed actuators or gateways 
	which are hard to access.

    In Remote Management two actors are specified:\n
    1. Remote Managmenet Controller  - is device that sends remote commands.\n
    2. Remote device - is device that receives commands and is beeing managed.\n
    
    There are two possibilities how to evaluate Remote Management:    
    1. Program your own controller firmware:
        - program one module with the Device firmware
        - extend the Controller firmware functionality and program it the second module
        
    2. Using TCM300 and DolphinView
        - program one module with the Device firmware
        - program another module with the TCM300 firmware
        - put the TCM300 in Mode-1
        - connect the TCM300 to a PC where DolphinView is running
    
    
	\subpage reman_device_page\n
    \subpage reman_controller_page\n
	
	\page reman_device_page REMAN Device
    <b>REMAN Device application example files</b>
	\n\n REMAN Device Application file - main.c
	\include RemoteManagement\RemanDevice\main.c
	\n\n REMAN Device Application include file - main.h
	\include RemoteManagement\RemanDevice\main.h
	\n\n Config file - EO3000I_CFG.h
	\include RemoteManagement\RemanDevice\EO3000I_CFG.h

   	\page reman_controller_page REMAN Controller Application
	<b>REMAN Controller application example files</b>
	\n\n REMAN Controller Application file - main.c
	\include RemoteManagement\RemanController\main.c
	\n\n REMAN Controller Application include file - main.h
	\include RemoteManagement\RemanController\main.h
	\n\n Config file - EO3000I_CFG.h
	\include RemoteManagement\RemanController\EO3000I_CFG.h

    

*/

//*******************************Secure Light Control****************************
/*!      
	\page app_securelightcontrol Secure Light Control Example
	\n\n Application file - main.c
	\include SecureLightControl\main.c
	\n\n Config file - EO3000I_CFG.h
	\include SecureLightControl\EO3000I_CFG.h
*/  


	//***************************SmartACK Example*****************************
/*!

	\page app_smartack SmartACK Example
	The SmartACK concept is used to for bidirectional communication between energy autarkic sensors and line powered
	HW modules. The DolphinAPI has a built in support for this concept. For detailed information how the SmartACK works 
	be sure to read the SMACK Specification.pdf (not available in current install package).\n\n

	The current installation package provides 3 SmartACK examples. One Controller, one sensor and TCM300 repeater.
	The TCM300 example supports smart ack repeating, where it has full post master functionality.\n\n

	<b>Usage of the example programs</b>
	- download the Controller application to the ASIC
	- download the Sensor application to another ASIC
	- test Controller functionality by sending data telegrams from a PTM switch
	- when it works the ADIO3 should toggle by every telegram and the telegram should be received using WinEtel
	- test Sensor functionality by waking up the sensor using Wake0, it will send a data telegram with data 0xEE - no controller learned on sensor side
	- if no WAKE0 pin is pressed, the sensor wakes up periodically each hour and sends a DATA telegram

	- enter the Controller to learn mode by pressing ADIO0 switch, ADIO4 should be on	
	- send a LearnReclaim telegram from the sensor using WAKE1
	- exit learn mode by pressing ADIO0, ADIO4 should switch off

	- now the Sensor ID is learned in the Controller and the Controller ID is learned in the Sensor
	- to verify this, by pushing the WAKE0 the Sensor sends a data telegram which contains:
		- 0x04 when there was no Data Acknowledge  from the Controller on a 3x Data Reclaim tries with the previous telegram but controller ID is learned in
		- 0x01 - 0x03 number of Data Reclaim tries until the Sensor has received Data Acknowledge from the controller
		- 0xEE if no controller ID is learned
	- note that the data from the sensor data telegram contains the status of the previous Reclaim process
	- to learn out the sensor repeat the learn process again 
		

	\subpage controller_page\n
	\subpage sensor_page\n
	
	
	\page controller_page Controller Application
	<b>Controller application example files</b>
	\n\n Controller Application file - main.c
	\include SmartACK\Controller\main.c
	\n\n Controller Application include file - main.h
	\include SmartACK\Controller\main.h
	\n\n Controller Application file for learn - executeLearn.c
	\include SmartACK\Controller\executeLearn.c
	\n\n Config file - EO3000I_CFG.h
	\include SmartACK\Controller\EO3000I_CFG.h

	
	\page sensor_page Sensor Application
	\n\n Sensor Application file - main.c
	\include SmartACK\Sensor\main.c
	\n\n Sensor Application include file - main.h
	\include SmartACK\Sensor\main.h
	\n\n Sensor Application evaluation file - evaluation.c
	\include SmartACK\Sensor\evaluation.c
	\n\n Config file - EO3000I_CFG.h
	\include SmartACK\Sensor\EO3000I_CFG.h
*/



//*******************************Standby Example****************************
/*!      
	\page app_standby Standby Example
	\n\n Application file - main.c
	\include Standby\main.c
	\n\n Config file - EO3000I_CFG.h
	\include Standby\EO3000I_CFG.h
*/  


//*******************************STM300 Example****************************
/*!      
	\page app_stm300 STM300 Firmware
	Source code of the STM300 module implementation. The project can be found in the download area of the EnOcean web page.
    http://www.enocean.com/en/download/ 
	
*/  

//*******************************TCM300 Example****************************
/*!      
	\page app_tcm300 TCM300 Firmware
	Source code of the TCM300 module implementation. The project can be found in the download area of the EnOcean web page.
    http://www.enocean.com/en/download/ 
*/  

//*******************************VLD Example***************************
/*!  
  \page app_vld VLD Telegrams 
	Application demonstrating how to use variable length data telegrams (VLD - Variable Length Data).
	
  \n\nThe Dolphin platform allows to send and receive telegrams with a variable length. The telegram type #RADIO_CHOICE_VLD  
  was reserved for this telegram type. 

  \note A second telegram type #RADIO_CHOICE_UTE is reserved for Universal Teach In EEP based telegram.
  
  To demonstrate the usage of the VLD telegrams a system of one \subpage app_vld_tx "Sender" and one \subpage app_vld_rx "Receiver" is implemented.
  For both functionalities a separated software project exists.   
     
  \page app_vld_tx VLD Sender Demo
  \n\n  
  \n\n Application file - main.c
	\include VLDExampleTx\main.c
	\n\n Config file - EO3000I_CFG.h
	\include VLDExampleTx\EO3000I_CFG.h

  \page app_vld_rx VLD Receiver Demo
  \n\n  
	\n\n Application file - main.c
	\include VLDExampleRx\main.c
	\n\n Config file - EO3000I_CFG.h
	\include VLDExampleRx\EO3000I_CFG.h
*/  
  

//*******************************Radio to Serial Example****************************
/*!      
	\page app_radiotoesp3 Radio To ESP3 Example
	Simple application demonstrating receiving telegrams with the radio module and sending it to the serial port using the ESP3 protocol
	\n\n Application file - main.c
	\include RadioToESP3\main.c
	\n\n Config file - EO3000I_CFG.h
	\include RadioToESP3\EO3000I_CFG.h
*/  
  
//*******************************Receive Radio Strength Indication (RSSI) Example****************************
/*!      
	\page app_rssiexample RSSI Example
	Simple application demonstrating how to show the Receive Radio Strength Indication (RSSI) and the usage of PWM.
	\n\n Application file - main.c
	\include RSSI\main.c
	\n\n Config file - EO3000I_CFG.h
	\include RSSI\EO3000I_CFG.h
*/  
  
//*******************************Remote Management with ESP2 and ESP3 advanced example****************************
/*!      
	\page app_remanesp3 REMAN with ESP3 and learn mode
	Advanced application demonstrating how to use Remote Management with learn modes. The application supports both ESP2 and ESP3, 4channel learn mode.
	This example was moved to application note AN503. Please download it from here: http://www.enocean.com/de/application-notes/
	
*/  
 

	
#endif
