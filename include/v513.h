// **********************************************************************
// *   v513 
// *   YBenhammou
// *   07/2010
// **********************************************************************
#ifndef __LINUX
#define __LINUX
#endif

#include "CAENVMElib.h"
#include "v1718.h"
#include <iostream>
using namespace std;

#ifndef _v513_h
#define _v513_h
class v513
{
	private : 
		long			Handle;
		unsigned long 		Address;
		CVDataWidth             DataWidth;
                CVAddressModifier       AddressModifier;               
	public:
		v513(long handle,unsigned long address);
		~v513();

//		int GetSerialNumber();
//		int GetChannel(int channel);
    int SetChannelOutput(int channel);
    int GetIdentifier();
    short int GetInRegister();
    int GetOutRegister(short int);
  int SetReset();
};		
#endif
