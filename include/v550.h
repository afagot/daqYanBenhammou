// **********************************************************************
// *   v550 
// *   YBenhammou
// *   09/2009
// **********************************************************************
#ifndef __LINUX
#define __LINUX
#endif

#include "CAENVMElib.h"
#include "v1718.h"

#ifndef _v550_h
#define _v550_h
class v550
{
	private : 
		long			Handle;
		unsigned long 		Address;
		CVAddressModifier 	AddressModifier;
	public:
		v550(long handle,unsigned long address);
		~v550();

		int v550SetAddress(unsigned long  address);
		unsigned long  v550GetAddress(void);
		int Getv550Identifier(char *tchaine);
		int Getv550Identifier(void);
		int Setv550TestPattern(int channel,int TestPattern);
		int Getv550WordCounter(int channel);
		unsigned long Getv550FIFO(int channel);
		int Setv550Clear();
		int Getv550NumberOfChannels(int channel);
		int Setv550NumberOfChannels(int NumberOfChannels0,int NumberOfChannels1);
		int Getv550StatusRegister();
		int Setv550StatusRegister(int RegisterValue);
		int Getv550DataReady(int channel);
		int Getv550FIFOEmpty(int channel);
		int Setv550InterruptRegister(int RegisterValue);
		int Getv550PedestalCh0(int offset);
		int Getv550TresholdCh0(int offset);
		int Getv550PedestalCh1(int offset);
		int Getv550TresholdCh1(int offset);
		int Setv550PedestalCh0(int offset,int PedestalValue);
		int Setv550TresholdCh0(int offset,int TresholdValue);
		int Setv550PedestalCh1(int offset,int PedestalValue);
		int Setv550TresholdCh1(int offset,int TresholdValue);
		int Setv550MemoryOwner(int owner);
};		
#endif
