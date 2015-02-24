// **********************************************************************
// *   v792
// *   Y.Benhammou
// *   29/07/2009
// **********************************************************************

#include "v792.h"
#include "CAENVMElib.h"
#include "pro.h"
v792::v792(long handle,unsigned long address)
{
  m_address=address;
  m_dataWidth=cvD16;
  m_addressModifier=cvA24_U_DATA;
  m_handle=handle;
  for (int i=0;i<32;i++)
    m_enabledChannels[i]=1;
}

v792::~v792()
{
}

void v792::FastClear()
{
  int ret;
  Data16 data=0x00;
  ret = CAENVME_ReadCycle(m_handle,m_address+0x102E,&data,m_addressModifier,cvD16);
  if (ret<0)
    {
      perror ("error in Fast Clear\n");
    }
}


void v792::ClearBuffer()
{
  int ret;
  Data16 data=0x04;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x1032,&data,m_addressModifier,cvD16);
  if (ret<0)
    {
      perror ("error in Clear Buffer\n");
    }
}

void v792::SetSoftwareReset()
{
  int ret;
  Data16 data=0x080;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x1006,&data,m_addressModifier,cvD16);
  if (ret<0)
    {
      perror ("error in Set Software Reset\n");
    }
}

void v792::SetResetRelease()
{
  int ret;
  Data16 data=0x080;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x1008,&data,m_addressModifier,cvD16);
  if (ret<0)
    {
      perror ("error in Set Reset Release\n");
    }
}


void v792::SetControlRegister1()
{
  int ret;
  Data16 data=0xDB;
  ret = CAENVME_ReadCycle(m_handle,m_address+0x1010,&data,m_addressModifier,cvD16);
  if (ret<0)
    {
      perror ("error in Fast Clear\n");
    }
}


void v792::EnableLowThreshold()
{
  int ret;
  Data16 data=0x10;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x1032,&data,m_addressModifier,cvD16);
  if (ret<0)
    {
      perror ("error in Enable Low Threshold\n");
    }
}


void v792::EnableOverflow()
{
  int ret;
  Data16 data=0x08;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x1032,&data,m_addressModifier,cvD16);
  if (ret<0)
    {
      printf ("error in Enable Overflow\n");
    }
}

void v792::SetThreshold(int channel,int threshold)
{
  int ret;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x1080+channel*2,&threshold,m_addressModifier,cvD16);
  if (ret<0)
    {
      perror ("error in Set threshold\n");
    }
}



void v792::Set()
{
  cout << "Setting the QDC ..."<<endl;
  ClearBuffer();
  FastClear();
  SetSoftwareReset();
  SetResetRelease();	
  EnableLowThreshold();
  EnableOverflow();
  for (int i=0;i<32;i++)
    {
      //SetThreshold(i,7);
    }
  //SetThreshold(9,7);
  //SetThreshold(10,7);
  //SetThreshold(11,7);
  //SetThreshold(12,7);

}

unsigned long v792::GetOutputBuffer()
{
  int ret;
  unsigned long tdata;
  ret = CAENVME_ReadCycle(m_handle,m_address,&tdata,m_addressModifier,cvD32);
  if (ret<0)	
    {
      perror ("error in Get output buffer\n");
      return 0xFFFFFFFF;
    }
  return tdata;
}

int v792::GetFirmwarerevision()
{
  int ret;
  int tdata;
  ret = CAENVME_ReadCycle(m_handle,m_address+0x1000,&tdata,m_addressModifier,cvD16);
  if (ret<0)	
    {
      perror ("error in Get firmware revision\n");
      return -1;
    } else {
    int tmpOut = tdata&0xffff;
    cout << "Getv792Firmwarerevision -> " << tmpOut << endl;
  }
  return tdata&0xffff;
}

int v792::GetGeoAddress()
{
  int ret;
  int tdata;
  ret = CAENVME_ReadCycle(m_handle,m_address+0x1002,&tdata,m_addressModifier,m_dataWidth);
  if (ret<0)	
    {
      perror ("error in Get geo address\n");
      return -1;
      
    } else {
    cout << "Getv792GeoAddress -> " << tdata << endl;
	}
  return tdata;
}

int v792::SetGeoAddress(int GeoAddress)
{
  int ret;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x1002,&GeoAddress,m_addressModifier,m_dataWidth);
  return ret;
}

int v792::GetMCSTnCBLT()
{
  int ret;
  int tdata;
  ret = CAENVME_ReadCycle(m_handle,m_address+0x1004,&tdata,m_addressModifier,m_dataWidth);
  if (ret<0)	
    {
      perror ("error in Get MCST/CBLT\n");
      return -1;
    }
  return tdata;
}

int v792::SetMCSTnCBLT(int MCSTnCBLT)
{
  int ret;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x1004,&MCSTnCBLT,m_addressModifier,m_dataWidth);
  return ret;
}

int v792::GetBitSet1()
{
  int ret;
  int tdata;
  ret = CAENVME_ReadCycle(m_handle,m_address+0x1006,&tdata,m_addressModifier,m_dataWidth);
  if (ret<0)	
    {
      perror ("error in Get Bit set 1\n");
      return -1;
    }
  return tdata;
}

int v792::SetBitSet1(int BitSet1)
{
  int ret;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x1006,&BitSet1,m_addressModifier,m_dataWidth);
  return ret;
}

int v792::GetBitClear1()
{
  int ret;
  int tdata;
  ret = CAENVME_ReadCycle(m_handle,m_address+0x1008,&tdata,m_addressModifier,m_dataWidth);
  if (ret<0)	
    {
      perror ("error in Get Bit clear 1\n");
      return -1;
    }
  return tdata;
}

int v792::SetBitClear1(int BitClear1)
{
  int ret;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x1008,&BitClear1,m_addressModifier,m_dataWidth);
  return ret;
}

int v792::GetInterruptLevel()
{
  int ret;
  int tdata;
  ret = CAENVME_ReadCycle(m_handle,m_address+0x100A,&tdata,m_addressModifier,m_dataWidth);
  if (ret<0)	
    {
      perror ("error in Get interrupt level\n");
      return -1;
    }
  return tdata;
}

int v792::SetInterruptLevel(int InterruptLevel)
{
  int ret;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x100A,&InterruptLevel,m_addressModifier,m_dataWidth);
  return ret;
}

int v792::GetInterruptVector()
{
  int ret;
  int tdata;
  ret = CAENVME_ReadCycle(m_handle,m_address+0x100C,&tdata,m_addressModifier,m_dataWidth);
  if (ret<0)	
    {
      perror ("error in Get interrupt vector\n");
      return -1;
    }
  return tdata;
}

int v792::SetInterruptVector(int InterruptVector)
{
  int ret;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x100C,&InterruptVector,m_addressModifier,m_dataWidth);
  return ret;
}

int v792::GetStatus()
{
  int ret;
  unsigned long tdata;
  ret = CAENVME_ReadCycle(m_handle,m_address+0x100E,&tdata,m_addressModifier,m_dataWidth);
  if (ret<0)	
    {
      perror ("error in Get status\n");
      return -1;
    } else {
    int tmpOut = tdata&0x1FF;
    cout << "Getv792Status -> " << tmpOut << endl;
  }
  return tdata&0x1FF;
}

int v792::GetDataReady()
{
  int ret;
  unsigned long tdata;
  ret = CAENVME_ReadCycle(m_handle,m_address+0x100E,&tdata,m_addressModifier,cvD16);
  if (ret<0)	
    {
      perror ("error in Get status\n");
      return -1;
    }
  return tdata&0x01;
}

int v792::GetControlRegister1()
{
  int ret;
  int tdata;
  ret = CAENVME_ReadCycle(m_handle,m_address+0x1010,&tdata,m_addressModifier,m_dataWidth);
  if (ret<0)	
    {
      perror ("error in Get Control Register1\n");
      return -1;
    }
  return tdata;
}

int v792::SetControlRegister1(int ControlRegister1)
{
  int ret;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x1010,&ControlRegister1,m_addressModifier,m_dataWidth);
  return ret;
}

int v792::GetAddressDecoderHigh()
{
  int ret;
  int tdata;
  ret = CAENVME_ReadCycle(m_handle,m_address+0x1012,&tdata,m_addressModifier,m_dataWidth);
  if (ret<0)	
    {
      perror ("error in Get Address Decoder High\n");
      return -1;
    }
  return tdata;
}

int v792::SetAddressDecoderHigh(int AddressDecoderHigh)
{
  int ret;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x1012,&AddressDecoderHigh,m_addressModifier,m_dataWidth);
  return ret;
}

int v792::GetAddressDecoderLow()
{
  int ret;
  int tdata;
  ret = CAENVME_ReadCycle(m_handle,m_address+0x1014,&tdata,m_addressModifier,m_dataWidth);
  if (ret<0)	
    {
      perror ("error in Get Address Decoder Low\n");
      return -1;
    }
  return tdata;
}

int v792::SetAddressDecoderLow(int AddressDecoderLow)
{
  int ret;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x1014,&AddressDecoderLow,m_addressModifier,m_dataWidth);
  return ret;
}

int v792::SetSingleShotReset()
{
  int ret;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x1016,&ret,m_addressModifier,m_dataWidth);
  return ret;
}

int v792::SetMCSTnCBLTControl(int MCSTnCBLTControl)
{
  int ret;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x101A,&MCSTnCBLTControl,m_addressModifier,m_dataWidth);
  return ret;
}

int v792::GetEventTrigger()
{
  int ret;
  int tdata;
  ret = CAENVME_ReadCycle(m_handle,m_address+0x1020,&tdata,m_addressModifier,m_dataWidth);
  if (ret<0)	
    {
      perror ("error in Get Event Trigger\n");
      return -1;
    }
  return tdata;
}

int v792::SetEventTrigger(int EventTrigger)
{
  int ret;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x1020,&EventTrigger,m_addressModifier,m_dataWidth);
  return ret;
}

int v792::GetStatusRegister2()
{
  int ret;
  int tdata;
  ret = CAENVME_ReadCycle(m_handle,m_address+0x1022,&tdata,m_addressModifier,m_dataWidth);
  if (ret<0)	
    {
      perror ("error in Get status register 2\n");
      return -1;
    }
  return tdata;
}

int v792::GetEventCounterLow()
{
  int ret;
  unsigned long tdata;
  ret = CAENVME_ReadCycle(m_handle,m_address+0x1024,&tdata,m_addressModifier,m_dataWidth);
  if (ret<0)	
    {
      perror ("error in Get Event Counter low\n");
      return -1;
    }
  return tdata&0xFFFF;
}

int v792::GetEventCounterHigh()
{
  int ret;
  unsigned long tdata;
  ret = CAENVME_ReadCycle(m_handle,m_address+0x1026,&tdata,m_addressModifier,m_dataWidth);
  if (ret<0)	
    {
      perror ("error in Get Event Counter high\n");
      return -1;
    }
  return tdata&0xFF;
}

int v792::SetIncrementEventRegister()
{
  int ret;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x1028,&ret,m_addressModifier,m_dataWidth);
  return ret;
}

int v792::SetIncrementOffsetRegister()
{
  int ret;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x102A,&ret,m_addressModifier,m_dataWidth);
  return ret;
}

int v792::GetFastClearWindow()
{
  int ret;
  int tdata;
  ret = CAENVME_ReadCycle(m_handle,m_address+0x102E,&tdata,m_addressModifier,m_dataWidth);
  if (ret<0)	
    {
      perror ("error in Get Fast Clear Window\n");
      return -1;
    }
  return tdata;
}

int v792::SetFastClearWindow(int FastClearWindow)
{
  int ret;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x102E,&FastClearWindow,m_addressModifier,m_dataWidth);
  return ret;
}

int v792::GetBitSet2()
{
  int ret;
  int tdata;
  ret = CAENVME_ReadCycle(m_handle,m_address+0x1032,&tdata,m_addressModifier,m_dataWidth);
  if (ret<0)	
    {
      perror ("error in Get Bit set 2\n");
      return -1;
    }
  return tdata;
}

int v792::SetBitSet2(int BitSet2)
{
  int ret;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x1032,&BitSet2,m_addressModifier,m_dataWidth);
  return ret;
}

int v792::SetBitClear2(int BitClear2)
{
  int ret;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x1034,&BitClear2,m_addressModifier,m_dataWidth);
  return ret;
}

int v792::SetWMemoryTestAddress(int WMemoryTestAddress)
{
  int ret;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x1036,&WMemoryTestAddress,m_addressModifier,m_dataWidth);
  return ret;
}

int v792::SetMemoryTestWordHigh(int MemoryTestWordHigh)
{
  int ret;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x1038,&MemoryTestWordHigh,m_addressModifier,m_dataWidth);
  return ret;
}

int v792::SetMemoryTestWordLow(int MemoryTestWordLow)
{
  int ret;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x103A,&MemoryTestWordLow,m_addressModifier,m_dataWidth);
  return ret;
}

int v792::SetCrateSelect(int CrateSelect)
{
  int ret;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x103C,&CrateSelect,m_addressModifier,m_dataWidth);
  return ret;
}

int v792::SetTestEventWrite(int TestEventWrite)
{
  int ret;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x103E,&TestEventWrite,m_addressModifier,m_dataWidth);
  return ret;
}

int v792::SetEventCounterReset()
{
  int ret;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x1040,&ret,m_addressModifier,m_dataWidth);
  return ret;
}

int v792::GetIped()
{
  int ret;
  int tdata;
  ret = CAENVME_ReadCycle(m_handle,m_address+0x1060,&tdata,m_addressModifier,m_dataWidth);
  if (ret<0)	
    {
      perror ("error in Get Iped\n");
      return -1;
    }
  return (tdata&0xFF);
}

int v792::SetIped(int Iped)
{
  int ret;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x1060,&Iped,m_addressModifier,m_dataWidth);
  return ret;
}

int v792::SetRMemoryTestAddress(int RMemoryTestAddress)
{
  int ret;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x1064,&RMemoryTestAddress,m_addressModifier,m_dataWidth);
  return ret;
}

int v792::SetSWComm()
{
  int ret;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x1068,&ret,m_addressModifier,m_dataWidth);
  return ret;
}

int v792::GetSlideConstant()
{
  int ret;
  int tdata;
  ret = CAENVME_ReadCycle(m_handle,m_address+0x106A,&tdata,m_addressModifier,m_dataWidth);
  if (ret<0)	
    {
      perror ("error in Get Slide Constant\n");
      return -1;
    }
  return tdata;
}

int v792::SetSlideConstant(int SlideConstant)
{
  int ret;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x106A,&SlideConstant,m_addressModifier,m_dataWidth);
  return ret;
}

int v792::GetAAD()
{
  int ret;
  int tdata;
  ret = CAENVME_ReadCycle(m_handle,m_address+0x1070,&tdata,m_addressModifier,m_dataWidth);
  if (ret<0)	
    {
      perror ("error in Get AAD\n");
      return -1;
    }
  return tdata;
}

int v792::GetBAD()
{
  int ret;
  int tdata;
  ret = CAENVME_ReadCycle(m_handle,m_address+0x1072,&tdata,m_addressModifier,m_dataWidth);
  if (ret<0)	
    {
      perror ("error in Get BAD\n");
      return -1;
    }
  return tdata;
}

int v792::GetTreshold(int Channel)
{
  int ret;
  int tdata;
  ret = CAENVME_ReadCycle(m_handle,m_address+0x1080+Channel*2,&tdata,m_addressModifier,m_dataWidth);
  if (ret<0)	
    {
      perror ("error in Get Treshold\n");
      return -1;
    }
  return tdata&0xFF;
}

int v792::SetTreshold(int Channel,int Treshold)
{
  int ret;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x1080+Channel*2,&Treshold,m_addressModifier,m_dataWidth);
  return ret;
}

int  v792::GetIdentifier(char * tchaine)
{
  int ret;
  int tData;
  int tVersion;
  int tSerial;
  int tManufacturer;
  int tBoardId;
  int tRevision;
  
  CAENVME_ReadCycle(m_handle,m_address+0x8026,&tData,m_addressModifier,m_dataWidth);
  tManufacturer=tData<<16;
  CAENVME_ReadCycle(m_handle,m_address+0x802A,&tData,m_addressModifier,m_dataWidth);
  tManufacturer+=(tData<<8);
  CAENVME_ReadCycle(m_handle,m_address+0x802E,&tData,m_addressModifier,m_dataWidth);
  tManufacturer+=tData;
  
  CAENVME_ReadCycle(m_handle,m_address+0x8032,&tVersion,m_addressModifier,m_dataWidth);
  
  CAENVME_ReadCycle(m_handle,m_address+0x8036,&tData,m_addressModifier,m_dataWidth);
  tBoardId=tData<<16;
  CAENVME_ReadCycle(m_handle,m_address+0x803A,&tData,m_addressModifier,m_dataWidth);
  tBoardId+=(tData<<8);
  CAENVME_ReadCycle(m_handle,m_address+0x803E,&tData,m_addressModifier,m_dataWidth);
  tBoardId+=tData;
  
  CAENVME_ReadCycle(m_handle,m_address+0x804E,&tRevision,m_addressModifier,m_dataWidth);
  
  CAENVME_ReadCycle(m_handle,m_address+0x8F02,&tData,m_addressModifier,m_dataWidth);
  tSerial=(tData<<8);
  CAENVME_ReadCycle(m_handle,m_address+0x8F06,&tData,m_addressModifier,m_dataWidth);
  tSerial+=tData;
  
  sprintf(tchaine, "Board Id=%s\nManufacturer=%s\nSerial number=%s\nVersion=%s\nRevision=%s\n",
	  tBoardId,tManufacturer,tSerial,tVersion,tRevision);
  return 0;	
}
int  v792::GetActive(int channel)
{
  return m_enabledChannels[channel];
}

int *v792::GetData()
{
  int res;
  Data32 tdata;
  int a,status,channels,nch,s,adcCounts,ovf,evtCount;
  int *chan=new int[32];
  
  res=CAENVME_ReadCycle(m_handle,m_address+0x00,&tdata,m_addressModifier,cvD32);
  status = (tdata >> 24) & 0x07;
  //cout<<"qdc status:"<<status<<endl;
  if(status==2)
    {
      channels = (tdata>>8) & 0x003F;
      for(int m=0; m<channels; m++)
	{
	  s = (tdata >> 24) & 0x07;
	  res=CAENVME_ReadCycle(m_handle,m_address+0x00,&tdata,m_addressModifier,cvD32);
	  nch = (tdata>>16) & 0x003F;
	  adcCounts = tdata & 0x0FFF;
	  ovf = tdata & 0x1000;
	  if(ovf)
	    {
	      chan[nch] = 0x1000;
	    }
	  else
	    {
	      chan[nch] = adcCounts;
	    }
          }
      res=CAENVME_ReadCycle(m_handle,m_address+0x00,&tdata,m_addressModifier,cvD32);
      s = (tdata >> 24) & 0x07;
      if(s==4)
	{
	  evtCount = tdata & 0xFFFFFF;
	}                                     
    }
  
  else
    {
      cout << "NO DATA IN THE QDC " << endl;
      for(int m=0; m<32; m++)
	{
	  chan[m]=0;
	}
      
    }
  
  return(chan);
}



