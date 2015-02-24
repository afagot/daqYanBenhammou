// **********************************************************************
// *   v792 
// *   Y.Benhammou
// *   18/04/2012
// **********************************************************************
#ifndef __LINUX
#define __LINUX
#endif

#include "CAENVMElib.h"
#include <iostream>

using namespace std;


#ifndef _v262_h
#define _v262_h
class v262
{
 private : 
  long			m_handle;
  unsigned long 	m_address;
  CVDataWidth		m_dataWidth;
  CVAddressModifier 	m_addressModifier;
  
 public:
  v262(long handle,unsigned long address);
  ~v262();
  int SetNIMPulse(int);
  int ClearScale();
  unsigned long GetData(int);
  unsigned long *GetData();
  void GetSerialNumber();
  
};
#endif
		
