// **********************************************************************
// *   v262
// *   Y.Benhammou
// *   18/04/2012
// **********************************************************************

#include "v262.h"
#include "CAENVMElib.h"
#include "pro.h"
#include "MsgSvc.h"

v262::v262(long handle,unsigned long address)
{
  m_address=address;
  m_dataWidth=cvD16;
  m_addressModifier=cvA24_U_DATA;
  m_handle=handle;
  
  MSG_INFO("Initalization of the I/O 0x%X..\n",m_address);

}

v262::~v262()
{
}


int v262::SetNIMPulse(int channel)
{
  int ret;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x08,&channel,m_addressModifier,m_dataWidth);
  if (ret<0)
    {
      perror ("error in Set NIM Pulse\n");
    }
}

int v262::ClearScale()
{
  int ret;
  Data16 data=0x00;
  ret = CAENVME_WriteCycle(m_handle,m_address+0x50,&data,m_addressModifier,m_dataWidth);
  if (ret<0)
    {
      perror ("error in Clear Scale\n");
    }
  
  for (int i=0;i<16;i++)
    {
      data+=GetData(i);
    }
  return data;
}

unsigned long v262::GetData(int channel)
{
  int ret;
  unsigned long data;
  ret = CAENVME_ReadCycle(m_handle,m_address+0x0A+channel*4,&data,m_addressModifier,cvD32);
  if (ret<0)
    {
      perror ("error in Get Data\n");
    }
  return data;
}


unsigned long * v262::GetData()
{
  unsigned long *data = new unsigned long[16];
  for(int i=0;i<16;i++)
    {
      data[i]=GetData(i);
    }
  return data;
  
}

void v262::GetSerialNumber()
{
  int ret;
  unsigned long data;
  ret = CAENVME_ReadCycle(m_handle,m_address+0xFE,&data,m_addressModifier,cvD16);
  if (ret<0)
    {
      perror ("error in Get Serial Number\n");
    }
  MSG_INFO("S/N :%lu\n",(data&0x0FFF));
}


