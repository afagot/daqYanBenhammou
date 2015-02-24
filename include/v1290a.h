// **********************************************************************
// *   v1290a 
// *   Avia Raviv & Y. Benhammou
// *   14/03/2011
// **********************************************************************
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

#ifndef _v1290a_h
#define _v1290a_h



#define ERR -1

#define OUT_BUFFER_1290 	0x0000
#define CTRL_REG_1290   	0x1000
#define STAT_REG_1290   	0x1002
#define IRQ_LEVEL_1290  	0x100A
#define IRQ_VECTOR_1290 	0x100C
#define GEO_REG_1290    	0x100E
#define MCST_ADDR_1290  	0x1010
#define MCST_CTRL_1290  	0x1012
#define RESET_1290		0x1014
#define SOFT_CLR_1290    	0x1016
#define SOFT_EVENT_RESET_1290 	0x1018
#define SOFT_TRIG_1290        	0x101A
#define EVENT_COUNT_1290      	0x101C
#define EVENT_STORED_1290     	0x1020
#define ALMOST_FULL_1290      	0x1022
#define BLT_EVENT_NUM_1290    	0x1024
#define FIRMWARE_REVIS_1290   	0x1026
#define TESTREG_1290          	0x1028
#define OUT_PROG_CTRL_1290    	0x102C
#define MICRO_1290            	0x102E
#define MICRO_HAND_1290       	0x1030
#define SELECT_FLASH_1290     	0x1032
#define FLASH_MEMORY_1290     	0x1034
#define SRAM_PAGE_1290        	0x1036
#define EVENT_FIFO_1290       	0x1038
#define EVENT_FIFO_STORED_1290	0x103C
#define EVENT_FIFO_STATUS_1290	0x103E
#define DUMMY32_1290           	0x1200
#define DUMMY16_1290           	0x1204

#define NO_BUFFER_EMPTY_1290 	0x0001

#define BASE1290 0xAA0000

// 31/03/11 

#define STATUS_TDC    0xF8000000

//#define STATUS_TDC_1290    0x70000000
//#define HEADER_TDC_1290    0x40000000


//#define EOB_TDC_1290       0x10000000


#define FIFO_WORDCOUNT_MASK   0x0000FFFF
#define FIFO_WORDCOUNT_RSHIFT 0x00000000
#define TYPE_MASK             0xF8000000

#define FILLER_LONG             0xc0000000
#define GLOBAL_HEADER           0x40000000
#define GLOBAL_TRAILER          0x80000000
#define GLOBAL_TRIGGER_TIME_TAG 0x88000000

#define TDC_HEADER    0x08000000
#define TDC_DATA      0x00000000
#define TDC_ERROR     0x20000000
#define TDC_TRAILER   0x18000000

#define WRITE_OK 0X0001
#define READ_OK  0X0002

#define SIZE1290 0x7D00
#define MAXDATA_1290 512 

#define SIZE767 0x7D00
#define MAXDATA 1024 


typedef unsigned char Uchar;
typedef Uchar    Data8;

typedef unsigned short Ushort;
typedef Ushort    Data16;
typedef Ushort    Word16;

typedef unsigned int Uint;
typedef Uint    Data32;
typedef Uint    Word32;

typedef enum _EdgeMode {
  EdgeMode_Pair       = 0 ,
  EdgeMode_Leading    = 2,
  EdgeMode_Trailing   = 1,
  EdgeMode_Both       = 3
  
} EdgeMode;

typedef enum _Resolution {
  Res_25ps    = 3,
  Res_100ps   = 2,
  Res_200ps   = 1,
  Res_800ps   = 0
} Resolution;

typedef enum _DeadTime {
  DT_5ns       = 0,
  DT_10ns      = 1,
  DT_30ns      = 2,
  DT_100ns     = 3
} DeadTime;
typedef enum _HitMax {
  HITS_0       = 0,                   // No hits.
  HITS_1       = 1,
  HITS_2       = 2,
  HITS_4       = 3,
  HITS_8       = 4,
  HITS_16      = 5,
  HITS_32      = 6,
  HITS_64      = 7,
  HITS_128     = 8,
  HITS_UNLIMITED = 9          // No limit on hits.
} HitMax;
typedef enum _ReadMode {
  LOW_RATE     = 0,
  HIGH_RATE    = 1
} ReadMode;

/*Storage of an event.*/
typedef struct
{
  Data32 event_number;
  Data8 channel[MAXDATA];
  Data32 word_counter_tdc;
  Data32 tdc_data[MAXDATA];
  Data8 slope[MAXDATA];
} ntdc_event;

typedef struct
{
  int n_words;
  Data32 tdc_data[MAXDATA];
} dataFIFO;

class v1290a
{
 private : 
     long                    Handle;
     unsigned long           Address;
     CVDataWidth             DataWidth;
     CVAddressModifier       AddressModifier;
 public:
   
   v1290a(long handle, unsigned long address);
   ~v1290a();
   void Get_Firmware_Rev();
   int set();
   Data16 getDready();
   vector<Data32> getEventHighRateV();
   void getEvent();
   Data16 write_op_reg(unsigned long Address, int code);
   Data16 read_op_reg(unsigned long Address);


/*   Data16 write_op_reg_1290(Word32 log_add_v767, Data16 code);
   Data16 read_op_reg_1290(Word32 log_add_v767);
   Data16 read_op_reg_1290(long Handle,unsigned long Address,CVAddressModifier AddressModifier, CVDataWidth DataWidth);
   Data16 write_op_reg_1290(long Handle,unsigned long Address,CVAddressModifier AddressModifier, CVDataWidth DataWidth,Data16 code);
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
		
