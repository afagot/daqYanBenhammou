// *************************************************************************************************************
// *   v1190a 
// *   Alexis Fagot
// *   20/01/2015
// *   Based on v1290a file from :
// *   Avia Raviv & Y. Benhammou
// *   14/03/2011
// *************************************************************************************************************
#ifndef __LINUX
#define __LINUX
#endif

#include <iostream>
#include "pro.h"
#include <math.h>
#include <fcntl.h>
#include <sys/io.h>
#include <errno.h>
#include <sys/types.h>
#include <signal.h>
#include "get_input.h"
#include "tstamp.h"

#include "universe.h"
#include <sys/timeb.h>
#include <time.h>
#include <unistd.h>
#include <online.h>
//#include <general.h>
#include <iostream>
#include <vector>
using std::vector;

#include "v1718.h"

#ifndef _v1190a_h
#define _v1190a_h



#define ERR -1

// *************************************************************************************************************

/*** Base address (A24) of the model V1190A ***/

#define BASEV1190A                           0xEE0000

// *************************************************************************************************************

/*** Address map for the model V1190A ***/

#define ADD_OUT_BUFFER_V1190A				      0x0000			/* Output buffer relative address */
#define ADD_CONTROL_V1190A					      0x1000			/* Control register relative address */
#define ADD_STATUS_V1190A					      0x1002			/* Status register relative address */
#define ADD_INT_LEVEL_V1190A					   0x100A			/* Interrupt level register relative address */
#define ADD_INT_VECTOR_V1190A				      0x100C			/* Interrupt vector register relative address */
#define ADD_GEO_V1190ARESS_V1190A				0x100E			/* Geo Address register relative address */
#define ADD_MCST_CBLT_V1190ARESS_V1190A		0x1010			/* MCST/CBLT Base Address register relative address */
#define ADD_MCST_CBLT_CTRL_V1190A			   0x1012			/* MCST/CBLT Control register relative address */
#define ADD_MOD_RESET_V1190A					   0x1014			/* Module reset register relative address */
#define ADD_SW_CLEAR_V1190A					   0x1016			/* Software clear register relative address */
#define ADD_SW_EVENT_RESET_V1190A			   0x1018			/* Software event reset register relative address */
#define ADD_SW_TRIGGER_V1190A				      0x101A			/* Software trigger register relative address */
#define ADD_EVENT_COUNTER_V1190A				   0x101C			/* Event counter register relative address */
#define ADD_EVENT_STORED_V1190A				   0x1020			/* Event stored register relative address */
#define ADD_ALMOST_FULL_LVL_V1190A			   0x1022			/* Almost full level register relative address */
#define ADD_BLT_EVENT_NUM_V1190A				   0x1024			/* BLT event number register relative address */
#define ADD_FW_REV_V1190A					      0x1026			/* Firmware revision register relative address */
#define ADD_TESTREG_V1190A					      0x1028			/* Testreg register relative address */
#define ADD_OUT_PROG_CTRL_V1190A				   0x102C			/* Output prog control register relative address */
#define ADD_MICRO_V1190A						   0x102E			/* Micro register relative address */
#define ADD_MICRO_HND_V1190A					   0x1030			/* Micro handshake register relative address */
#define ADD_SEL_FLASH_V1190A					   0x1032			/* Select Flash register relative address */
#define ADD_FLASH_V1190A						   0x1034			/* Flash register relative address */
#define ADD_COMP_SRAM_PAGE_V1190A			   0x1036			/* Compensation SRAM Page register relative address */
#define ADD_EVENT_FIFO_V1190A				      0x1038			/* Event FIFO register relative address */
#define ADD_EVENT_FIFO_STORED_V1190A			0x103C			/* Event FIFO stored register relative address */
#define ADD_EVENT_FIFO_STATUS_V1190A			0x103E			/* Event FIFO status register relative address */
#define ADD_DUMMY32_V1190A					      0x1200			/* Dummy 32 register relative address */
#define ADD_DUMMY16_V1190A					      0x1204			/* Dummy 16 register relative address */
#define ADD_ROM_OUI_2_V1190A					   0x4024			/* Manufacturer identifier (IEEE OUI) (MSB) relative address */
#define ADD_ROM_OUI_1_V1190A					   0x4028			/* Manufacturer identifier (IEEE OUI) relative address */
#define ADD_ROM_OUI_0_V1190A					   0x402C			/* Manufacturer identifier (IEEE OUI) (LSB) relative address */
#define ADD_ROM_VERSION_V1190A				   0x4030			/* Purchased version of the Mod.V1190 relative address */
#define ADD_ROM_BOARD_ID_2_V1190A			   0x4034			/* Board identifier (MSB) relative address */
#define ADD_ROM_BOARD_ID_1_V1190A			   0x4038			/* Board identifier relative address */
#define ADD_ROM_BOARD_ID_0_V1190A   			0x403C			/* Board identifier (LSB) relative address */
#define ADD_ROM_REVISION_3_V1190A   			0x4040			/* Hardware revision identifier relative address */
#define ADD_ROM_REVISION_2_V1190A   			0x4044			/* Hardware revision identifier relative address */
#define ADD_ROM_REVISION_1_V1190A   			0x4048			/* Hardware revision identifier relative address */
#define ADD_ROM_REVISION_0_V1190A   			0x404C			/* Hardware revision identifier relative address */
#define ADD_ROM_SERIAL_1_V1190A	   			0x4080			/* Serial number (MSB) relative address */
#define ADD_ROM_SERIAL_0_V1190A	   			0x4084			/* Serial number (LSB) relative address */

#define NO_BUFFER_EMPTY_V1190A 	            0x0001

// *************************************************************************************************************

#define STATUS_TDC_V1190A                    0xF8000000

//#define STATUS_TDC_V1190A                  0x70000000
//#define HEADER_TDC_V1190A                  0x40000000


//#define EOB_TDC_V1190A                     0x10000000


#define FIFO_WORDCOUNT_MASK_V1190A           0x0000FFFF
#define FIFO_WORDCOUNT_RSHIFT_V1190A         0x00000000
#define TYPE_MASK_V1190A                     0xF8000000

#define FILLER_LONG_V1190A                   0xc0000000
#define GLOBAL_HEADER_V1190A                 0x40000000
#define GLOBAL_TRAILER_V1190A                0x80000000
#define GLOBAL_TRIGGER_TIME_TAG_V1190A       0x88000000

#define TDC_HEADER_V1190A                    0x08000000
#define TDC_DATA_V1190A                      0x00000000
#define TDC_ERROR_V1190A                     0x20000000
#define TDC_TRAILER_V1190A                   0x18000000

#define WRITE_OK                             0X0001
#define READ_OK                              0X0002

#define SIZE_V1190A                          0x7D00
#define MAXDATA_V1190A                       512 

#define MAXDATA                              1024 

// *************************************************************************************************************

/*** Micro register opcodes ***/

typedef enum
{
	// Micro register opcodes: ACQUISITION MODE
	 OPCODE_TRG_MATCH_V1190A					   = 0x0000,		/* Trigger matching mode micro opcode */
	 OPCODE_CONT_STORE_V1190A					   = 0x0100,		/* Continuos storage micro opcode */
	 OPCODE_READ_ACQ_MOD_V1190A				   = 0x0200,		/* Read acquisition mode micro opcode */
	 OPCODE_SET_KEEP_TOKEN_V1190A				   = 0x0300,		/* Set keep_token micro opcode */
	 OPCODE_CLEAR_KEEP_TOKEN_V1190A			   = 0x0400,		/* Clear keep_token micro opcode */
	 OPCODE_LOAD_DEF_CONFIG_V1190A			   = 0x0500,		/* Load default configuration micro opcode */
	 OPCODE_SAVE_USER_CONFIG_V1190A			   = 0x0600,		/* Save User configuration micro opcode */
	 OPCODE_LOAD_USER_CONFIG_V1190A			   = 0x0700,		/* Load User configuration micro opcode */
	 OPCODE_AUTOLOAD_USER_CONFIG_V1190A		   = 0x0800,		/* Set auto load User configuration micro opcode */
	 OPCODE_AUTOLOAD_DEF_CONFIG_V1190A		   = 0x0900,		/* Set auto load default configuration micro opcode */

	// Micro register opcodes: TRIGGER
	 OPCODE_SET_WIN_WIDTH_V1190A				   = 0x1000,		/* Set window width micro opcode */
	 OPCODE_SET_WIN_OFFSET_V1190A				   = 0x1100,		/* Set window offset micro opcode */
	 OPCODE_SET_SW_MARGIN_V1190A				   = 0x1200,		/* Set extra search margin micro opcode */
	 OPCODE_SET_REJ_MARGIN_V1190A				   = 0x1300,		/* Set reject margin micro opcode */
	 OPCODE_EN_SUB_TRG_V1190A					   = 0x1400,		/* Enable subtraction of trigger time micro opcode */
	 OPCODE_DIS_SUB_TRG_V1190A				      = 0x1500,		/* Disable subtraction of trigger time micro opcode */
	 OPCODE_READ_TRG_CONF_V1190A				   = 0x1600,		/* Read trigger configuration micro opcode */

	// Micro register opcodes: TDC EDGE DETECTION & RESOLUTION
	 OPCODE_SET_DETECTION_V1190A				   = 0x2200,		/* Enable paired meas. leading/ trailing edge micro opcode */
	 OPCODE_READ_DETECTION_V1190A				   = 0x2300,		/* Read edge detection configuration micro opcode */
	 OPCODE_SET_TR_LEAD_LSB_V1190A			   = 0x2400,		/* Set LSB of leading/trailing edge micro opcode */
	 OPCODE_SET_PAIR_RES_V1190A				   = 0x2500,		/* Set leading time and width res. when pair micro opcode */
	 OPCODE_READ_RES_V1190A					      = 0x2600,		/* Read resolution micro opcode */
	 OPCODE_SET_DEAD_TIME_V1190A				   = 0x2800,		/* Set channel dead time between hits micro opcode */
	 OPCODE_READ_DEAD_TIME_V1190A				   = 0x2900,		/* Read channel dead time between hits micro opcode */

	// Micro register opcodes: TDC READOUT
	 OPCODE_EN_HEAD_TRAILER_V1190A			   = 0x3000,		/* Enable TDC header and trailer micro opcode */
	 OPCODE_DIS_HEAD_TRAILER_V1190A			   = 0x3100,		/* Disable TDC header and trailer micro opcode */
	 OPCODE_READ_HEAD_TRAILER_V1190A			   = 0x3200,		/* Read status TDC header and trailer micro opcode */
	 OPCODE_SET_EVENT_SIZE_V1190A				   = 0x3300,		/* Set maximum number of hits per event micro opcode */
	 OPCODE_READ_EVENT_SIZE_V1190A			   = 0x3400,		/* Read maximum number of hits per event micro opcode */
	 OPCODE_EN_ERROR_MARK_V1190A				   = 0x3500,		/* Enable TDC error mark micro opcode */
	 OPCODE_DIS_ERROR_MARK_V1190A				   = 0x3600,		/* Disable TDC error mark micro opcode */
	 OPCODE_EN_ERROR_BYPASS_V1190A			   = 0x3700,		/* Enable bypass TDC if error micro opcode */
	 OPCODE_DIS_ERROR_BYPASS_V1190A			   = 0x3800,		/* Disable bypass TDC if error micro opcode */
	 OPCODE_SET_ERROR_TYPES_V1190A			   = 0x3900,		/* Set TDC internal error type micro opcode */
	 OPCODE_READ_ERROR_TYPES_V1190A			   = 0x3A00,		/* Read TDC internal error type micro opcode */
	 OPCODE_SET_FIFO_SIZE_V1190A				   = 0x3B00,		/* Set effective size of readout FIFO micro opcode */
	 OPCODE_READ_FIFO_SIZE_V1190A				   = 0x3C00,		/* Read effective size of readout FIFO micro opcode */

	// Micro register opcodes: CHANNEL ENABLE
	 OPCODE_EN_CHANNEL_V1190A					   = 0x4000,		/* Enable channel nn micro opcode */
	 OPCODE_DIS_CHANNEL_V1190A				      = 0x4100,		/* Disable channel nn micro opcode */
	 OPCODE_EN_ALL_CH_V1190A					   = 0x4200,		/* Enable all channels micro opcode */
	 OPCODE_DIS_ALL_CH_V1190A					   = 0x4300,		/* Disable all channels micro opcode */
	 OPCODE_WRITE_EN_PATTERN_V1190A			   = 0x4400,		/* Write enable pattern for channels micro opcode */
	 OPCODE_READ_EN_PATTERN_V1190A			   = 0x4500,		/* Read enable pattern for channels micro opcode */
	 OPCODE_WRITE_EN_PATTERN32_V1190A			= 0x4600,		/* Write 32 bit enable pattern for channels micro opcode */
	 OPCODE_READ_EN_PATTERN32_V1190A			   = 0x4700,		/* Read 32 bit enable pattern for channels micro opcode */

	// Micro register opcodes: ADJUST
	 OPCODE_SET_GLOB_OFFSET_V1190A			   = 0x5000,		/* Set global offset micro opcode */
	 OPCODE_READ_GLOB_OFFSET_V1190A			   = 0x5100,		/* Read global offset micro opcode */
	 OPCODE_SET_ADJUST_CH_V1190A				   = 0x5200,		/* Set channel nn adjust micro opcode */
	 OPCODE_READ_ADJUST_CH_V1190A				   = 0x5300,		/* Read channel nn adjust micro opcode */
	 OPCODE_SET_RC_ADJ_V1190A					   = 0x5400,		/* Set RC adjust of tdc 0n micro opcode */
	 OPCODE_READ_RC_ADJ_V1190A				      = 0x5500,		/* Read RC adjust of tdc 0n micro opcode */
	 OPCODE_SAVE_RC_ADJ_V1190A				      = 0x5600,		/* Save RC adjust on EEPROM micro opcode */

	// Micro register opcodes: MISCELLANEOUS
	 OPCODE_READ_TDC_ID_V1190A				      = 0x6000,		/* Read programmed ID of TDC 0n micro opcode */
	 OPCODE_READ_MICRO_REV_V1190A				   = 0x6100,		/* Read firmware revision of microcontroller micro opcode */
	 OPCODE_RESET_DLL_PLL_V1190A				   = 0x6200,		/* Reset DLL and PLL micro opcode */

	// Micro register opcodes: ADVANCED
	 OPCODE_WRITE_SETUP_REG_V1190A			   = 0x7000,		/* Write word nn into the scan path setup micro opcode */
	 OPCODE_READ_SETUP_REG_V1190A				   = 0x7100,		/* Read word nn into the scan path setup micro opcode */
	 OPCODE_UPDATE_SETUP_REG_V1190A			   = 0x7200,		/* Load the scan path setup micro opcode */
	 OPCODE_DEFAULT_SETUP_REG_V1190A			   = 0x7300,		/* Reload the default scan path setup micro opcode */
	 OPCODE_READ_ERROR_STATUS_V1190A			   = 0x7400,		/* Read errors in the TDC 0n status micro opcode */
	 OPCODE_READ_DLL_LOCK_V1190A				   = 0x7500,		/* Read the DLL LOCK bit of the TDC 0n micro opcode */
	 OPCODE_READ_STATUS_STREAM_V1190A			= 0x7600,		/* Read the TDC 0n status micro opcode */
	 OPCODE_UPDATE_SETUP_TDC_V1190A			   = 0x7700,		/* Load the scan path setup on TDC nn micro opcode */

	// Micro register opcodes: DEBUG AND TEST
	 OPCODE_WRITE_EEPROM_V1190A				   = 0xC000,		/* Write 1 byte into the EEPROM micro opcode */
	 OPCODE_READ_EEPROM_V1190A				      = 0xC100,		/* Read 1 byte from the EEPROM micro opcode */
	 OPCODE_MICROCONTROLLER_FW_V1190A			= 0xC200,		/* Read the controller firmware revision/date micro opcode */
	 OPCODE_WRITE_SPARE_V1190A				      = 0xC300,		/* Write a 16 bit spare variable micro opcode */
	 OPCODE_READ_SPARE_V1190A					   = 0xC400,		/* Read a 16 bit spare variable micro opcode */
	 OPCODE_EN_TEST_MODE_V1190A				   = 0xC500,		/* Enable TDC test mode micro opcode */
	 OPCODE_DIS_TEST_MODE_V1190A				   = 0xC600,		/* Disable TDC test mode micro opcode */
	 OPCODE_SET_TDC_TEST_OUTPUT_V1190A		   = 0xC700,		/* Set TDC 0n signal test output micro opcode */
	 OPCODE_SET_DLL_CLOCK_V1190A				   = 0xC800,		/* Set DLL clock source micro opcode */
	 OPCODE_READ_TDC_SETUP_SCAN_PATH_V1190A	= 0xC900,		/* Read all Setup Scan Path on TDC 0n micro opcode */
}  OPCODES_MICRO_V1190A;

// *************************************************************************************************************

/*** Types ***/

typedef unsigned char Uchar;
typedef Uchar                                Data8;

typedef unsigned short Ushort;
typedef Ushort                               Data16;
typedef Ushort                               Word16;

typedef unsigned int Uint;
typedef Uint                                 Data32;
typedef Uint                                 Word32;

// *************************************************************************************************************

/*** Parameters ***/

typedef enum _EdgeMode {
  EdgeMode_Pair                              = 0b00,
  EdgeMode_Trailing                          = 0b01,
  EdgeMode_Leading                           = 0b10,
  EdgeMode_Both                              = 0b11
  
} EdgeMode;

typedef enum _Resolution {
  Res_100ps                                  = 0b00,
  Res_200ps                                  = 0b01,
  Res_400ps                                  = 0b10,
  Res_800ps                                  = 0b11
} Resolution;

typedef enum _DeadTime {
  DT_5ns                                     = 0b00,
  DT_10ns                                    = 0b01,
  DT_30ns                                    = 0b10,
  DT_100ns                                   = 0b11
} DeadTime;

typedef enum _HitMax {
  HITS_0                                     = 0b0000,
  HITS_1                                     = 0b0001,
  HITS_2                                     = 0b0010,
  HITS_4                                     = 0b0011,
  HITS_8                                     = 0b0100,
  HITS_16                                    = 0b0101,
  HITS_32                                    = 0b0110,
  HITS_64                                    = 0b0111,
  HITS_128                                   = 0b1000,
  HITS_UNLIMITED                             = 0b1001       /* No limit on hits. */
} HitMax;

typedef enum _ReadMode {
  LOW_RATE                                   = 0,
  HIGH_RATE                                  = 1
} ReadMode;

// *************************************************************************************************************

/*** Event storage ***/

typedef struct
{
  Data32                                     event_number;
  Data8                                      channel[MAXDATA];
  Data32                                     word_counter_tdc;
  Data32                                     tdc_data[MAXDATA];
  Data8                                      slope[MAXDATA];
} ntdc_event;

typedef struct
{
  int                                        n_words;
  Data32                                     tdc_data[MAXDATA];
} dataFIFO;

// *************************************************************************************************************

/*** CLASS ***/

class v1190a
{
 private : 
     long                                    Handle;
     unsigned long                           Address;
     CVDataWidth                             DataWidth;
     CVAddressModifier                       AddressModifier;
 public:
   
   v1190a(long handle, unsigned long address);
   ~v1190a();
   void Get_Firmware_Rev();
   int set();
   Data16 getDready();
   vector<Data32> getEventHighRateV();
   void getEvent();
   Data16 write_op_reg(unsigned long Address, int code);
   Data16 read_op_reg(unsigned long Address);


/*   Data16 write_op_reg_V1190A(Word32 log_add_v767, Data16 code);
   Data16 read_op_reg_V1190A(Word32 log_add_v767);
   Data16 read_op_reg_V1190A(long Handle,unsigned long Address,CVAddressModifier AddressModifier, CVDataWidth DataWidth);
   Data16 write_op_reg_V1190A(long Handle,unsigned long Address,CVAddressModifier AddressModifier, CVDataWidth DataWidth,Data16 code);
   int Set();
   void SoftClear();
   Data16 getDready();
   Data16 getErrorTDC();
   ntdc_event *getEvent();
   void setEnableFIFO();
   Data16 getEnableFIFO();
   dataFIFO *getEventFIFOHighRate();
   ntdc_event *getEventFIFO();
   Data16 EventCounter();
   Data16 getFIFOFull();
   Data16 getDreadyFIFO(); 
   void WaitMicroWrite();
   void SetTriggerMatchMode();
   void SetContinuosStorageMode();
   void SetWindowWidth(unsigned int nWidth);
   void SetWindowOffset( int nOffset);
   void SetExtraSearchMargin(unsigned int nMargin);
   void SetRejectMargin(unsigned int nMargin);
   void EnableTriggerTimeSubtraction();
   void DisableTriggerTimeSubtraction();
   void SetEdgeDetectMode(EdgeMode nEdgeMode);
   void SetEnableTDCEncapsulation();
   void SetDisableTDCEncapsulation();
   void SetEnableErrorMark();
   void SetDisableErrorMark();
   void SetErrorEnables(unsigned short nErrors);
   void SetEnableAllChannels();
   void SetDisableAllChannels();
   void EnableChannel(unsigned short nChannel);
   void DisableChannel(unsigned short nChannel);
   void SetIndividualLSB(Resolution nResolution);
   void SetDoubleHitResolution(DeadTime nDeadTime) ;
   void SetMaxHitsPerEvent(HitMax nHits);
   void GetTriggerConfiguration();
   void Initialize();
*/
};


#endif
		
