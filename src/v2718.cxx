// **********************************************************************
// *   CAEN v2718 VME OPTIC interface
// *   Y. Benhammou
// *   05/02/2012
// **********************************************************************

#ifndef __LINUX
#define __LINUX
#endif

#include <iostream>

#include "CAENVMElib.h"
#include "v2718.h"

v2718::v2718(unsigned short device)
{
	if( CAENVME_Init(cvV2718, device, 0, &Handle) != cvSuccess ) 
	{
    		perror("\n\n Error opening the v2718 controller device\n");
		exit(1);
    	}

/*		man.addr = 0xEE000000 ;      
		man.level = 1 ;           
		man.am = cvA32_U_DATA ;            
		man.dtsize = cvD16 ;        
		man.basaddr = 0xEE000000 ; 
		man.blts = 256 ;          
		man.ncyc = 1 ;            
		man.autoinc = 0 ;  
*/


	CAENVME_SetFIFOMode(Handle,1); 
	printf ("Handle=%x\n",Handle);
	Level = cvIRQ1 ;           
	AM = cvA32_U_DATA ;            
	DataSize = cvD16 ;        
	BaseAddress = 0xEE ; 
	BlockSize = 256 ;          
	NbCycles = 1 ;            
	Address=0xEE;
}


v2718::~v2718()
{
	CAENVME_End(Handle);
}

int v2718::SetAddress(unsigned short address)
{
	Address=address;
	return 0;
}

unsigned short v2718::GetAddress(void)
{
	return Address;
}

int v2718::SetData(unsigned short data)
{
	Data=data;
	return 0;
}

unsigned short v2718::GetData(void)
{
	return Data;
}

int v2718::SetAM(CVAddressModifier am)
{
	AM=am;
	return 0;
}

CVAddressModifier v2718::GetAM(void)
{
	return AM;
}

int v2718::SetDatasize(CVDataWidth datasize)
{
	DataSize=datasize;
	return 0;
}

CVDataWidth v2718::GetDataSize(void)
{
	return DataSize;
}

int v2718::SetBaseAddress(unsigned short baseaddress)
{
	BaseAddress=baseaddress;
	return 0;
}

unsigned short v2718::GetBaseAddress(void)
{
	return BaseAddress;
}

int v2718::SetBlockSize(unsigned short blocksize)
{
	BlockSize=blocksize;
	return 0;
}

unsigned short v2718::GetBlockSize(void)
{
	return BlockSize;
}

int v2718::SetNbCycles(unsigned short nbcycles)
{
	NbCycles=nbcycles;
	return 0;
}

unsigned short v2718::GetNbCycles(void)
{
	return NbCycles;
}

int v2718::SetLevel(CVIRQLevels level)
{
	Level=level;
	return 0;
}

CVIRQLevels v2718::GetLevel(void)
{
	return Level;
}

int v2718::SetDevice(unsigned short device)
{
	Device=device;
	return 0;
}

unsigned short v2718::GetDevice(void)
{
	return Device;
}

long v2718::GetHandle(void)
{
	return Handle;
}

int v2718::WriteToVME(unsigned long address, unsigned long data,CVAddressModifier am,CVDataWidth dtsize) 
{
	CVErrorCodes		ret;

	if(dtsize == cvD64)
	{
		perror(" Can't execute a D64 Write Cycle");
			return -1;
	}
	ret = CAENVME_WriteCycle(Handle,Address,&Data,AM,DataSize);
	switch (ret)
	{
		case cvSuccess   : printf(" Cycle(s) completed normally\n");
			return 0;
		case cvBusError	 : perror(" Bus Error !!!");
			return -1;
		case cvCommError : perror(" Communication Error !!!");
			return -1;
		default          : perror(" Unknown Error !!!");
			return -1;
	}
	return 0;
}

int v2718::ReadFromVME(unsigned long address, unsigned long data,CVAddressModifier am,CVDataWidth dtsize) 
{
	CVErrorCodes		ret;

	address=address;
	Data=data;
	AM=am;
	DataSize=dtsize;
	if(dtsize == cvD64)
	{
		perror(" Can't execute a D64 Read Cycle");
		return -1;
	}
	ret = CAENVME_ReadCycle(Handle,Address,&Data,AM,DataSize);
	switch (ret)
	{
		case cvSuccess   : printf(" Cycle(s) completed normally\n");
	       		if ( dtsize == cvD32 )
				printf(" Data Read : %x\n ",data);;
                	if ( dtsize == cvD16 )
				printf(" Data Read : %x\n",data & 0xffff);
                	if ( dtsize == cvD8 )
			        printf(" Data Read : %x\n",data & 0xff);
			break ;
		case cvBusError	 : perror(" Bus Error !!!\n");
			break ;				   
		case cvCommError : perror(" Communication Error !!!\n");
			break ;
		default          : perror(" Unknown Error !!!\n");
			break ;
	}
	return 0;
}

int v2718::GetIrqStatus(void) 
{
	CVErrorCodes	ret ;

	printf(" CHECK IRQ\n");
	CAENVME_IRQCheck(Handle,&IrqStatus);		// Check IRQ Status

	printf(" IRQ status: %i\n",IrqStatus);
	if(IrqStatus & (1<<(Level-1)))
	{
		ret = CAENVME_IACKCycle(Handle,Level,&Data,DataSize);
 		switch (ret)
		{
			case cvSuccess   : printf(" Cycle completed normally");
					   printf(" Int. Ack. on IRQ : %x  : StatusID = %x\n",Level,Data);
					break ;
			case cvBusError	 : perror(" Bus Error !!!\n");
					   break ;				   
			case cvCommError : perror(" Communication Error !!!\n");
					   break ;
			default          : perror(" Unknown Error !!!\n");
					   break ;

	        }
	}
	else
		printf(" Interrupt request IRQ %x not active\n",Level);
	return 0;	
}

int v2718::StartPulser(void)
{
	short int Data;
	unsigned char *period,*width,*pulsenumber;
	CVTimeUnits *unit;
	CVIOSources *start,*reset;
	CVErrorCodes ret;
	ret=CAENVME_SetPulserConf(Handle,cvPulserA,7,3,cvUnit25ns,0,cvManualSW,cvManualSW);
	printf("error on set = %d \n",ret);
	sleep(3);
	ret=CAENVME_SetOutputConf(Handle,cvOutput1,cvDirect,cvActiveHigh,cvManualSW);
	printf("error on outputconf = %d \n",ret);
	ret=CAENVME_GetPulserConf(Handle,cvPulserA,period,width,unit,pulsenumber,start,reset);
	printf(" period : %s \n",*period);
	ret = CAENVME_ReadCycle(Handle,Address+0x16,&Data,AM,cvD16);
	printf("error on readcycle = %d \n",ret);
	printf("data = %X4 \n",Data);
	sleep(3);
	ret=CAENVME_StartPulser(Handle,cvPulserA);
	printf("error on start = %d \n",ret);
	sleep(1000);
	return 0;
}
