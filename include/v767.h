// **********************************************************************
// *   v767
// *   Y.Benhammou
// *   28/12/2009
// **********************************************************************
#ifndef __LINUX
#define __LINUX
#endif

#include "CAENVMElib.h"
#include <function.h>

#ifndef _v767_h
#define _v767_h
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
};
#endif              
