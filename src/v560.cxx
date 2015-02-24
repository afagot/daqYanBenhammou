// **********************************************************************
// *   v560
// *   Y.Benhammou && Y.Munwes
// *   17/04/2012
// **********************************************************************

#include "v560.h"
#include "CAENVMElib.h"
#include "MsgSvc.h"
#include "pro.h"

v560::v560(long handle,unsigned long address)
{
  
  m_address=address;
  m_dataWidth=cvD16;
  m_addressModifier=cvA24_U_DATA;
  m_handle=handle;

  time(&m_date);
  gettimeofday(&m_start,NULL);
  gettimeofday(&m_last,NULL);

  MSG_INFO("Initalization of the scaler 0x%X ..\n",m_address);

}

v560::~v560()
{
}

int v560::GetSerialNumber()
{
  int ret=0;
  unsigned long tdata;
  int a;
  ret = CAENVME_ReadCycle(m_handle,m_address+0x00FC,&tdata,m_addressModifier,cvD16);
  a=tdata & 0x03FF;
  MSG_INFO("Serial number %d\n",a);
  a=tdata & 0xFC00;
  MSG_INFO("Serial number %d\n",a);
  return ret;
}  
int v560::GetChannel(int channel)
{
  unsigned long Data;
  int ret=0;
  ret = CAENVME_ReadCycle(m_handle,m_address+0x0010+channel*4,&Data,m_addressModifier,cvD32);
  return (int)Data;
}                             

void v560::Reset()
{
  short int Data=0;
  int ret=0;
  ret = CAENVME_ReadCycle(m_handle,m_address+0x50,&Data,m_addressModifier,cvD16);
}                             

char * v560::GetFullDate()
{
  time(&m_date);
  char *temp = ctime(&m_date);
  return temp;
}


double v560::GetTotalTime()
{
  timeval now;
  gettimeofday(&now,NULL);
  return(now.tv_sec-m_start.tv_sec);
}



double v560::GetDeltaTime()
{
  timeval now;
  gettimeofday(&now,NULL);
  return(now.tv_sec-m_last.tv_sec);
}

void v560::ResetTimer()
{
  timeval now;
  gettimeofday(&now,NULL);
  m_last=now;
}

