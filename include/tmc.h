// **********************************************************************
// *   TMC 
// *   YBenhammou
// *   27/03/2012
// **********************************************************************
#ifndef __LINUX
#define __LINUX
#endif
#include "pro.h"
#include "CAENVMElib.h"
#include "v1718.h"
#include <iostream>
#include <vector>

using namespace std;

#ifndef _tmc_h
#define _tmc_h


#define STATUS_NO_TRIG  0X01
#define STATUS_OVERFLOW 0X02
#define STATUS_NO_EOD   0X04

//Structure to store an event
typedef struct
{
  Data16 nWords;
  Data16 status;
  Data16 t0;
  Data16 eOD;
  std::vector<int> *channel;
  std::vector<int> *moduleId;
  std::vector<int> *data;
  std::vector<int> *slope;
} tmc_event;

  
class tmc
{
private : 
  long			m_handle;
  unsigned long 	m_address;
  CVDataWidth           m_dataWidth;
  CVAddressModifier     m_addressModifier;               
public:
  tmc(long handle,unsigned long address);
  ~tmc();
  
  Data16 GetDready();
  Data16 SetDready(Data16);
  void Set(Data16);
  void StartRun();
  void GetRunFlag();
  void GetEvent();
  tmc_event* GetEvent(int);
  void StartTmcLed();
  void Reset();
  vector<Data16> GetEventV(int a);
};		
#endif
