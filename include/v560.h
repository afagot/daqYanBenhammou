// **********************************************************************
// *   v560 
// *   YBenhammou
// *   04/2010
// **********************************************************************
#ifndef __LINUX
#define __LINUX
#endif

#include "CAENVMElib.h"
#include "v1718.h"
#include <iostream>
#include "tstamp.h"
#include "universe.h"
#include <sys/timeb.h>
#include <time.h>
#include <sys/time.h>

using namespace std;

#ifndef _v560_h
#define _v560_h
class v560
{
 private : 
  long		            m_handle;
  unsigned long             m_address;
  CVDataWidth               m_dataWidth;
  CVAddressModifier         m_addressModifier;
  time_t		m_date;
  timeval		m_start;
  timeval		m_last;

 public:
  v560(long handle,unsigned long address);
  ~v560();
  
  int GetSerialNumber();
  int GetChannel(int channel);
  void Reset();
  char * GetFullDate();
  double GetTotalTime();
  double GetDeltaTime();
  void ResetTimer();

};		
#endif
