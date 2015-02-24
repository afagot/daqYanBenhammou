// *************************************************************************************************************
// *   CAEN v1718 VME USB interface
// *   Y. Benhammou
// *   27/07/2009
// *************************************************************************************************************

#ifndef __LINUX
#define __LINUX
#endif

#include <iostream>

#include "CAENVMElib.h"
#include "v1718.h"
#include "MsgSvc.h"

v1718::v1718(unsigned short device)
{
   MSG_INFO("Initialization VME...\n");
  
   if( CAENVME_Init(cvV1718, device, 0, &Handle) != cvSuccess ) 
   {
      perror("\n\nError opening the v1718 controller device\n");
      exit(1);
   }
   
   CAENVME_SetFIFOMode(Handle,1); 
   Level = cvIRQ1 ;           
   AM = cvA24_U_DATA ;            
   DataSize = cvD16 ;        
   BaseAddress = 0x00 ; 
   BlockSize = 256 ;          
   NbCycles = 1 ;            
   Address=0;
   MSG_INFO("Initialization VME OK\n");
}

// *************************************************************************************************************

v1718::~v1718()
{
  CAENVME_End(Handle);
}

// *************************************************************************************************************

int v1718::SetAddress(unsigned short address)
{
  Address=address;
  return 0;
}

// *************************************************************************************************************

unsigned short v1718::GetAddress(void)
{
  return Address;
}

// *************************************************************************************************************

int v1718::SetData(unsigned short data)
{
  Data=data;
  return 0;
}

// *************************************************************************************************************

unsigned short v1718::GetData(void)
{
  return Data;
}

// *************************************************************************************************************

int v1718::SetAM(CVAddressModifier am)
{
  AM=am;
  return 0;
}

// *************************************************************************************************************

CVAddressModifier v1718::GetAM(void)
{
  return AM;
}

// *************************************************************************************************************

int v1718::SetDatasize(CVDataWidth datasize)
{
  DataSize=datasize;
  return 0;
}

// *************************************************************************************************************

CVDataWidth v1718::GetDataSize(void)
{
  return DataSize;
}

// *************************************************************************************************************

int v1718::SetBaseAddress(unsigned short baseaddress)
{
  BaseAddress=baseaddress;
  return 0;
}

// *************************************************************************************************************

unsigned short v1718::GetBaseAddress(void)
{
  return BaseAddress;
}

// *************************************************************************************************************

int v1718::SetBlockSize(unsigned short blocksize)
{
  BlockSize=blocksize;
  return 0;
}

// *************************************************************************************************************

unsigned short v1718::GetBlockSize(void)
{
  return BlockSize;
}

// *************************************************************************************************************

int v1718::SetNbCycles(unsigned short nbcycles)
{
  NbCycles=nbcycles;
  return 0;
}

// *************************************************************************************************************

unsigned short v1718::GetNbCycles(void)
{
  return NbCycles;
}

// *************************************************************************************************************

int v1718::SetLevel(CVIRQLevels level)
{
  Level=level;
  return 0;
}

// *************************************************************************************************************

CVIRQLevels v1718::GetLevel(void)
{
  return Level;
}

// *************************************************************************************************************

int v1718::SetDevice(unsigned short device)
{
  Device=device;
  return 0;
}

// *************************************************************************************************************

unsigned short v1718::GetDevice(void)
{
  return Device;
}

// *************************************************************************************************************

long v1718::GetHandle(void)
{
  return Handle;
}

// *************************************************************************************************************

int v1718::WriteToVME(unsigned long address, unsigned long data,CVAddressModifier am,CVDataWidth dtsize) 
{
   CVErrorCodes ret;
  
   if(dtsize == cvD64)
   {
      perror("Can't execute a D64 Write Cycle");
      return -1;
   }
   ret = CAENVME_WriteCycle(Handle,Address,&Data,AM,DataSize);
   
   switch (ret)
   {
      case cvSuccess       : printf("Cycle(s) completed normally\n");
         return 0;
      case cvBusError      : perror("Bus Error !!!");
         return -1;
      case cvCommError     : perror("Communication Error !!!");
         return -1;
      default              : perror("Unknown Error !!!");
         return -1;
   }
   return 0;
}

// *************************************************************************************************************

int v1718::ReadFromVME(unsigned long address, unsigned long data,CVAddressModifier am,CVDataWidth dtsize) 
{
   CVErrorCodes ret;
  
   address=address;
   Data=data;
   AM=am;
   DataSize=dtsize;
   
   if(dtsize == cvD64)
   {
      perror("Can't execute a D64 Read Cycle");
      return -1;
   }
   ret = CAENVME_ReadCycle(Handle,Address,&Data,AM,DataSize);
   
   switch (ret)
   {
      case cvSuccess       : printf("Cycle(s) completed normally\n");
         if ( dtsize == cvD32 )  printf("Data Read : %lu\n",data);
         if ( dtsize == cvD16 )  printf("Data Read : %lu\n",data & 0xffff);
         if ( dtsize == cvD8 )   printf("Data Read : %lu\n",data & 0xff);
         break ;
      case cvBusError	   : perror("Bus Error !!!\n");
         break ;				   
      case cvCommError     : perror("Communication Error !!!\n");
         break ;
      default              : perror("Unknown Error !!!\n");
         break ;
   }
   return 0;
}

// *************************************************************************************************************

int v1718::GetIrqStatus(void) 
{
   CVErrorCodes	ret ;
  
   printf("CHECK IRQ\n");
   CAENVME_IRQCheck(Handle,&IrqStatus);		// Check IRQ Status
  
   printf("IRQ status: %i\n",IrqStatus);
   
   if(IrqStatus & (1<<(Level-1)))
   {
      ret = CAENVME_IACKCycle(Handle,Level,&Data,DataSize);
      switch (ret)
	   {
	      case cvSuccess    : printf("Cycle completed normally\n");
	         printf("Int. Ack. on IRQ : %x  : StatusID = %lu\n",Level,Data);
	         break ;
	      case cvBusError   : perror("Bus Error !!!\n");
	         break ;				   
	      case cvCommError  : perror("Communication Error !!!\n");
	         break ;
	      default           : perror("Unknown Error !!!\n");
	         break ;
	  
	   }
   }
   else
      printf("Interrupt request IRQ %x not active\n",Level);
   return 0;	
}
