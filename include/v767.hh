// **********************************************************************
// *   v767
// *   Y.Benhammou
// *   28/12/2009
// **********************************************************************
#ifndef __LINUX
#define __LINUX
#endif

#include "CAENVMElib.h"
#include "v767.h"
// #include <function>

#ifndef _v767_hh
#define _v767_hh
class v767
{
private :
  long                    Handle;
  unsigned long           Address;
  CVDataWidth             DataWidth;
  CVAddressModifier       AddressModifier;
public:
  v767(long handle,unsigned long address);
  ~v767();
  int Set();
  void SoftReset();
  Data16 getDready();
  tdc_event *getEvent();
  int Clear();
  Data16 getErrorTDC0();
  Data16 getErrorTDC1();
  Data16 getErrorTDC2();
  Data16 getErrorTDC3();
  Data16 write_op_reg(unsigned long address, int code);
  Data16 read_op_reg(unsigned long address);
};
#endif             
