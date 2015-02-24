// *************************************************************************************************************
// *   v1190a 
// *   Alexis Fagot
// *   20/01/2015
// *   Based on v1290a file from :
// *   Avia Raviv & Y. Benhammou
// *   14/03/2012
// *************************************************************************************************************
#include "pro.h"
#include "v1190a.h"
#include "CAENVMElib.h"
   
using namespace std;
  
v1190a::v1190a(long handle, unsigned long address)
{
   Address=address;              //See page 35
   DataWidth=cvD16;              //See in CAENVMEtypes.h CVDataWidth enum
   AddressModifier=cvA24_U_DATA; //See in CAENVMEtypes.h CVAddressModifier enum
   Handle=handle;
}

// *************************************************************************************************************
 
v1190a::~v1190a()
{
}

// *************************************************************************************************************

void v1190a::Get_Firmware_Rev()
{
	int a;
	unsigned short tdata;
	int ret=0;
	
	//Firmware revision
	ret=CAENVME_ReadCycle(Handle,Address+ADD_FW_REV_V1190A,&tdata,AddressModifier,cvD16);
	
	printf("The firmware is : %04X (it should be 18)\n",(tdata & 0x00FF));
   /*or all first 8 places one by one*/
}

// *************************************************************************************************************

int v1190a::set()
{
	int res;
	
	cout << "------- START TO SET THE TDC --------------" <<endl;
	cout << "Reset the TDC..." << endl;
	
	int reset=0x0;
	
	//Reset the TDC (Software clear) and wait 2 s
	res=CAENVME_WriteCycle(Handle,Address+ADD_SW_CLEAR_V1190A,&reset,AddressModifier,DataWidth);
    sleep(2);

	//Test : try to write/read 16 bit word
	Data16 test=365;
	res=CAENVME_WriteCycle(Handle,Address+ADD_DUMMY16_V1190A,&test,AddressModifier,DataWidth);
	
	test=0;
	res=CAENVME_ReadCycle(Handle,Address+ADD_DUMMY16_V1190A,&test,AddressModifier,DataWidth);
	
	printf("The result of the write/read test is : %4X (it should be 365)\n",test);

	//Status of the TDC (Status register)
	cout <<"Status of the TDC..."<< endl;
	
	Data16 status;
	
	res=CAENVME_ReadCycle(Handle,Address+ADD_STATUS_V1190A,&status,AddressModifier,DataWidth);
	printf("TDC STATUS is : %4X\n",status);


	//Check the communication with the micro controller
	cout << "Control of the communication with the uController"<<endl;
	write_op_reg(Address, OPCODE_READ_SPARE_V1190A);
	
	printf("Test of the uController gives : 0x%4X  (it should be 0x5555)\n", read_op_reg(Address));

	//Disable TDC test mode
	write_op_reg(Address, OPCODE_DIS_TEST_MODE_V1190A);
	
	/*** TRIGGER ***/

	//Set trigger matching mode
	write_op_reg(Address, OPCODE_TRG_MATCH_V1190A);

	//Set window width :
	//time unit is 25 ns, 0x14 = 20 x 25 = 500 ns
	cout << "Window width is set to default value 0x14 (500ns)" << endl;
	write_op_reg(Address, OPCODE_SET_WIN_WIDTH_V1190A);
	write_op_reg(Address, 0x14);


	//Set window offset to -250ns
	cout << "Window offset is set to -0x10 (-250 ns)" <<endl;
	write_op_reg(Address, OPCODE_SET_WIN_OFFSET_V1190A);
	write_op_reg(Address, -0x10);

	//Enable substraction of trigger time
	write_op_reg(Address, OPCODE_EN_SUB_TRG_V1190A);

	//Disable substraction of trigger time
//	write_op_reg(Address, OPCODE_DIS_SUB_TRG_V1190A); 

	//Read trigger configuration
	cout << "Trigger configuration :" <<endl;
	write_op_reg(Address, OPCODE_READ_TRG_CONF_V1190A);
	
	Data16 MatchWindowWidth,WindowOffset,ExtraSearchWindowWidth,RejectMargin,TriggerTimeSubtraction;
	MatchWindowWidth        =read_op_reg(Address);
	WindowOffset            =read_op_reg(Address);
	ExtraSearchWindowWidth  =read_op_reg(Address);
	RejectMargin            =read_op_reg(Address);
	TriggerTimeSubtraction  =read_op_reg(Address);
	
	printf("Match Window Width : 0x%4X\n"        ,MatchWindowWidth);
	printf("Window Offset : 0x%4X\n"             ,WindowOffset);
	printf("Extra Search Window Width : 0x%4X\n" ,ExtraSearchWindowWidth);
	printf("Reject Margin : 0x%4X\n"             ,RejectMargin);
	printf("Trigger Time Subtraction : 0x%4X\n"  ,TriggerTimeSubtraction);
	/***  END OF TRIGGER  ***/

	/*** TDC EDGE DETECTION & RESOLUTION ***/
	//Edge detection selection
	cout << "Edge detection set to trailing and leading (11)"<< endl;
	write_op_reg(Address,OPCODE_SET_DETECTION_V1190A);
   write_op_reg(Address,EdgeMode_Both);

	//Edge detection readout
	write_op_reg(Address,OPCODE_READ_DETECTION_V1190A);
	
	Data16 edge;
	edge=read_op_reg(Address);
	printf ("Edge readout : %4X\n",(edge & 0b11));

	//Resolution readout
	write_op_reg(Address,OPCODE_READ_RES_V1190A);
	printf ("Resoltion : %4X\n",(read_op_reg(Address) & 0b11));	

	
	//Set channel dead time to 5ns
	cout << "Channel dead time between hits set to 5ns (00)" << endl;
	write_op_reg(Address,OPCODE_SET_DEAD_TIME_V1190A);
	write_op_reg(Address,DT_5ns);

	//Channel dead time readout
	write_op_reg(Address,OPCODE_READ_DEAD_TIME_V1190A);
	
	Data16 deadtime;
	deadtime=read_op_reg(Address);
	printf("Channel dead time : %4X\n", (deadtime & 0b11));
	/*** END OF TDC EDGE DETECTION & RESOLUTION ***/


	/*** TDC READOUT  ***/
	//Enable TDC header and trailer
	write_op_reg(Address,OPCODE_EN_HEAD_TRAILER_V1190A);

	//TDC header/trailer status readout
	write_op_reg(Address,OPCODE_READ_HEAD_TRAILER_V1190A);
	printf("TDC header/trailer status (on/off) : %4X\n", (read_op_reg(Address) & 0b1));

	//Maximum number of hits per event readout
	write_op_reg(Address,OPCODE_READ_EVENT_SIZE_V1190A);
	printf("Maximum number of hit/event = %4X\n", (read_op_reg(Address) & 0b1111));
	/***  END TDC READOUT  ***/

	/*** CHANNEL ENABLE ***/
	//Enable channels according a 16 bit pattern
	cout << "Enabling the channels ..."<<endl;
	write_op_reg(Address,OPCODE_WRITE_EN_PATTERN_V1190A);	
	write_op_reg(Address,0xFFFF);
	write_op_reg(Address,0xFFFF);

	//Enabled channels readout
	write_op_reg(Address,OPCODE_READ_EN_PATTERN_V1190A);
	printf("Channels enabled (0-15):  %4X\n", (read_op_reg(Address) & 0xFFFF));
	printf("Channels enabled (16-31):  %4X\n", (read_op_reg(Address) & 0xFFFF));

	return(0);

}

// *************************************************************************************************************

Data16 v1190a::getDready()
{
   Data16 temp;
   if (CAENVME_ReadCycle(Handle,Address+ADD_STATUS_V1190A,&temp,AddressModifier,DataWidth)==1)
	{
	   return (temp & NO_BUFFER_EMPTY_V1190A);
	}
   else 
	{
	   return (-1);
	}
}

// *************************************************************************************************************

vector<Data32> v1190a::getEventHighRateV()
{
   //Read the number of event in the buffer
   std::vector<Data32> v32;
   v32.clear();
   Data32 data;
   Data16 NEvt,iNEvt;
   int res;
   res=CAENVME_ReadCycle(Handle,Address+ADD_EVENT_STORED_V1190A,&NEvt,AddressModifier,DataWidth);
   
   cout << "Number of event stored in the buffer : "<< NEvt <<endl;
   
   for (int i=0;i<NEvt;i++)
   {
	   res=CAENVME_ReadCycle(Handle,Address+ADD_OUT_BUFFER_V1190A,&data,AddressModifier,cvD32);
      res=CAENVME_ReadCycle(Handle,Address+ADD_EVENT_STORED_V1190A,&iNEvt,AddressModifier,DataWidth);
      
      cout << "Number of event stored in the buffer : "<< iNEvt <<endl;
	   v32.push_back(data);
   }

   return v32;
}

// *************************************************************************************************************

void v1190a::getEvent()
{
   //Check the number of events in the buffer
   Data32 data;
   Data16 EventStored;
   int res; 
   res=CAENVME_ReadCycle(Handle,Address+0x1020,&EventStored,AddressModifier,DataWidth);
  
   cout << "Number of event stored in the buffer : "<< EventStored <<endl;
  
   while(EventStored !=0)
   {
	   res=CAENVME_ReadCycle(Handle,Address+ADD_OUT_BUFFER_V1190A,&data,AddressModifier,cvD32);
//	   cout << "raw data : "<< data <<endl;
	   switch(data & STATUS_TDC_V1190A)
		{
			case(GLOBAL_HEADER_V1190A):
						cout << "GLOBAL HEADER" ;
						cout << "\tEvent Count : " << ((data>>5) & 0x3FFFFF)<<endl;
						break;
			case(GLOBAL_TRAILER_V1190A):
						cout << "GLOBAL TRAILER";
						cout << "\tWord Count : " << (data & 0x001FFFE0)<<endl;
						break;
			case(TDC_HEADER_V1190A):
						cout << "TDC HEADER";
						cout << "\tEvent id : " << ( (data>>12) & 0x00FFF) << endl;
						break;
			case(TDC_DATA_V1190A):
						cout << "Data";
						cout << "\tRise/Fall : " << ((data>>26) & 0x01) ;
						cout << "\tChannel : " <<((data>>21) & 0x01F ) ;
						cout << "\tValue : " << ( data & 0x001FFFFF)<<endl ;
						break;
		}		
   }
}

// *************************************************************************************************************

Data16 v1190a::read_op_reg(unsigned long Address)
{
   //Checks the Read OK bit
   int time = 0;
   Data16 ro_bit;

   do
   {
      CAENVME_ReadCycle(Handle,Address+ADD_MICRO_HND_V1190A,&ro_bit,AddressModifier,DataWidth);
      time++;
   } while(ro_bit != READ_OK && time < 100000);
   
   if(time == 100000)
   {
      printf("Reads - timeout error\n");
      exit(0);
    }
   else
   {
      sleep(1);      /*** delay 12ms, internal delay ***/
      //Reads opcode
      CAENVME_ReadCycle(Handle,Address+ADD_MICRO_V1190A,&ro_bit,AddressModifier,DataWidth );
      return ro_bit;
   }
}

// *************************************************************************************************************

Data16 v1190a::write_op_reg(unsigned long Address, int code)
{
   //Checks the Write OK bit
   int time = 0;
   Data16 wo_bit;
   do
   {
      CAENVME_ReadCycle(Handle,Address+ADD_MICRO_HND_V1190A,&wo_bit,AddressModifier,DataWidth );
      time++;
   } while(wo_bit != WRITE_OK && time < 100000);
   
   if(time == 100000)
   {
      printf("Write opcode - timeout error\n");
      exit(0);
   }
   else
   {
      sleep(1);      /*** delay 12 msec, internal delay ***/
      //Writes opcode = code
      CAENVME_WriteCycle(Handle,Address+ADD_MICRO_V1190A,&code,AddressModifier,DataWidth);
      return 0;
    }
}

