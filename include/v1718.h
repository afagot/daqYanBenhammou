// **********************************************************************
// *   v1718 
// *   y.benhammou
// *   26/07/09
// **********************************************************************
#ifndef __LINUX
#define __LINUX
#endif

#include "CAENVMElib.h"

#ifndef _v1718_h
#define _v1718_h

#define BASEV1718 0x000000

class v1718
{
	private : 
		int32_t			                  Handle;
		short 	 		                  Device;
		
		unsigned long 		               Address ;			// Address
		unsigned long		               Data ;          	// Data
		CVIRQLevels		                  Level ;			   // Interrupt level
		unsigned char		               IrqStatus;		   // IRQ status   
		CVAddressModifier	               AM ;			      // Addressing Mode
		CVDataWidth 		               DataSize ;		   // Data Format
		unsigned long		               BaseAddress ;		// Base Address
		unsigned long		               BlockSize ;			// Block size for blt (bytes)
		unsigned short		               NbCycles ;			// Number of cycles
		
		
	public:
		v1718(unsigned short address);
		~v1718();
		int SetAddress(unsigned short address);
		unsigned short GetAddress(void);
		int SetData(unsigned short data);
		unsigned short GetData(void);
		int SetAM(CVAddressModifier am);
		CVAddressModifier GetAM(void);
		int SetDatasize(CVDataWidth datasize);
		CVDataWidth GetDataSize(void);
		int SetBaseAddress(unsigned short baseaddress);
		unsigned short GetBaseAddress(void);
		int SetBlockSize(unsigned short blocksize);
		unsigned short GetBlockSize(void);
		int SetNbCycles(unsigned short nbcycles);
		unsigned short GetNbCycles(void);
		int SetLevel(CVIRQLevels level);
		CVIRQLevels GetLevel(void);
		int SetDevice(unsigned short device);
		unsigned short GetDevice(void);
		long GetHandle(void);
		int WriteToVME(unsigned long address, unsigned long data,CVAddressModifier am,CVDataWidth dtsize) ;
		int ReadFromVME(unsigned long address, unsigned long data,CVAddressModifier am,CVDataWidth dtsize) ;
		int GetIrqStatus(void) ;
};		
#endif
