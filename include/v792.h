// **********************************************************************
// *   v792 
// *   Y.Benhammou
// *   29/07/2009
// **********************************************************************
#ifndef __LINUX
#define __LINUX
#endif

#include "CAENVMElib.h"
#include <iostream>
using namespace std;


#ifndef _v792_h
#define _v792_h
class v792
{
private : 
  long			m_handle;
  unsigned long 	m_address;
  CVDataWidth		m_dataWidth;
  CVAddressModifier 	m_addressModifier;
  int 			m_enabledChannels[32];
  
public:
  v792(long handle,unsigned long address);
  ~v792();
  void FastClear();
  void ClearBuffer();
  void SetSoftwareReset();
  void SetResetRelease();
  void SetControlRegister1();
  void EnableLowThreshold();
  void EnableOverflow();
  void SetThreshold(int,int);
  void Set();
  unsigned long GetOutputBuffer();
  int GetFirmwarerevision();
  int GetGeoAddress();
  int SetGeoAddress(int GeoAddress);
  int GetMCSTnCBLT();
  int SetMCSTnCBLT(int MCSTnCBLT);
  int GetBitSet1();
  int SetBitSet1(int BitSet1);
  int GetBitClear1();
  int SetBitClear1(int BitClear1);
  int GetInterruptLevel();
  int SetInterruptLevel(int InterruptLevel);
  int GetInterruptVector();
  int SetInterruptVector(int InterruptVector);
  int GetStatus();
  int GetDataReady();
  int GetControlRegister1();
  int SetControlRegister1(int ControlRegister1);
  int GetAddressDecoderHigh();
  int SetAddressDecoderHigh(int AddressDecoderHigh);
  int GetAddressDecoderLow();
  int SetAddressDecoderLow(int AddressDecoderLow);
  int SetSingleShotReset();
  int SetMCSTnCBLTControl(int MCSTnCBLTControl);
  int GetEventTrigger();
  int SetEventTrigger(int EventTrigger);
  int GetStatusRegister2();
  int GetEventCounterLow();
  int GetEventCounterHigh();
  int SetIncrementEventRegister();
  int SetIncrementOffsetRegister();
  int GetFastClearWindow();
  int SetFastClearWindow(int FastClearWindow);
  int GetBitSet2();
  int SetBitSet2(int BitSet2);
  int SetBitClear2(int BitClear2);
  int SetWMemoryTestAddress(int WMemoryTestAddress);
  int SetMemoryTestWordHigh(int MemoryTestWordHigh);
  int SetMemoryTestWordLow(int MemoryTestWordLow);
  int SetCrateSelect(int CrateSelect);
  int SetTestEventWrite(int TestEventWrite);
  int SetEventCounterReset();
  int GetIped();
  int SetIped(int Iped);
  int SetRMemoryTestAddress(int RMemoryTestAddress);
  int SetSWComm();
  int GetSlideConstant();
  int SetSlideConstant(int SlideConstant);
  int GetAAD();
  int GetBAD();
  int GetTreshold(int Channel);
  int SetTreshold(int Channel,int Treshold);
  int GetIdentifier(char * tchaine);
  int GetActive(int channel);
  int *GetData();

};
#endif
		
