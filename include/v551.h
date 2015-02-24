// **********************************************************************
// *   v551
// *   Y. Benhammou 
// *   2010
// **********************************************************************
#ifndef __LINUX
#define __LINUX
#endif

#include "CAENVMElib.h"
#include <unistd.h>
#ifndef _v551_h
#define _v551_h

/* CSR Space. */
#define IRQ_VEC_551       0x0000
#define IRQ_LEV_551       0x0002
#define SOFT_CLEAR_551    0x0004
#define SOFT_TRIG_551     0x0006
#define STAT_REG_551      0x0008
#define TEST_REG_551      0x000A
#define NUM_CHANNELS_551  0x000C
#define T1_REG_551        0x000E
#define T2_REG_551        0x0010
#define T3_REG_551        0x0012
#define T4_REG_551        0x0014
#define T5_REG_551        0x0016
#define VCAL_DAC_551      0x0018

/* CR Space. */
#define FIX_CODE_551      0x00FA
#define MANU_ID_551       0x00FC
#define SERIAL_551        0x00FE

/* STATUS BITS */
/* data ready */
#define DY_551          0x0008
#define NO_DY_551       0x0000
/* busy */
#define B_551           0x0010
#define NO_B_551        0x0000
/* active sequence */
#define AS_551          0x0020
#define NO_AS_551       0x0000
                                



class v551
{
	private : 
		long			Handle;
		unsigned long 		Address;
		CVAddressModifier 	AddressModifier;
	public:
		 v551(long handle,unsigned long address);
 		~v551();
		int  v551SetAddress(unsigned long  address);
		unsigned long   v551GetAddress(void);
		int  Getv551Identifier(char *tchaine);
		int  Getv551Identifier();
		int Setv551Configuration(unsigned short NumberOfChannels,unsigned short T1,unsigned short T2, unsigned short T3, unsigned short T4, unsigned short T5);
		int  Setv551InterruptVector(unsigned short InterruptVector);
		int  Setv551InterruptLevel(unsigned short InterruptLevel);
		int  Setv551Clear();
		int  Setv551Trigger();
		int  Getv551DataReady();
		int  Getv551StatusRegister();
		int  Setv551StatusRegister(unsigned short RegisterValue);
		int  Getv551TestRegister();
		int  Setv551TestRegister(unsigned short RegisterValue);
		int  Getv551NumberOfChannels();
		int  Setv551NumberOfChannels(unsigned short NumberOfChannels);
		int  Getv551T1Value();
		int  Setv551T1Value(unsigned short T1);
		int  Getv551T2Value();
		int  Setv551T2Value(unsigned short T2);
		int  Getv551T3Value();
		int  Setv551T3Value(unsigned short T3);
		int  Getv551T4Value();
		int  Setv551T4Value(unsigned short T4);
		int  Getv551T5Value();
		int  Setv551T5Value(unsigned short T5);
		int  Setv551InternalDAC(unsigned short DACValue);
		int  Getv551InternalDelay();
		int  Getv551Veto();
		int  Getv551AutoTrigger();
		int  Setv551SetInternalDelay(unsigned short tdelay);
		int  Setv551SetVeto(unsigned short tveto);
		int  Setv551SetAutoTrigger(unsigned short tautotrigger);
		int  set();
                int Write16(int address,short int data);
                int Read16(int address,short int *data);    
		int Write32(int address,int data);
		int Read32(int address,int *data);
};
#endif
