// **********************************************************************
// *   v1290a
// *   Avia Raviv & Y. Benhammou
// *   14/03/2012
// **********************************************************************
#include "pro.h"
#include "v1290a.h"
#include "CAENVMElib.h"
   
using namespace std;
  
v1290a::v1290a(long handle, unsigned long address)
{
   Address=address;
   DataWidth=cvD16;
   AddressModifier=cvA24_U_DATA;
   Handle=handle;
}
 
v1290a::~v1290a()
{
} 

void v1290a::Get_Firmware_Rev()
{
	int a;
	unsigned short tdata;
	int ret=0;
	ret=CAENVME_ReadCycle(Handle,Address+0x1026,&tdata,AddressModifier,cvD16);
	a=tdata & 0x00FF;
	//cout << "Firmwar rev. register " << a << " should be : 18 " <<endl;
	printf("firmware %4X should be 18 \n",a);
/*or all first 8 places one by one*/
}

int v1290a::set()
{
	int res;
	cout <<"------- START TO SET THE TDC --------------"<<endl;
	cout << "Reset the TDC"<< endl;
	//reset the TDC and wait 2 s
	int reset=0x0;
	res=CAENVME_WriteCycle(Handle,Address+0x1016,&reset,AddressModifier,DataWidth);
   	sleep(2);   

	//test to write/read 16 bit word
	Data16 test=365;
	res=CAENVME_WriteCycle(Handle,Address+0x1204,&test,AddressModifier,DataWidth);
	test=0;
	res=CAENVME_ReadCycle(Handle,Address+0x1204,&test,AddressModifier,DataWidth);
	cout << "result of the write/read test (should be 365) : "<< test <<endl;


	//status of the TDC
	cout <<" Status of the TDC "<< endl;
	Data16 status;
	res=CAENVME_ReadCycle(Handle,Address+0x1002,&status,AddressModifier,DataWidth);
	printf("TDC STATUS : %4X \n",status);


	// check the communication with the micro controller
	cout << "check the communication with the uController"<<endl;
	write_op_reg(Address, 0xC400);
	printf("Test of the uController (should be 0x5555) : 0x%4X\n", read_op_reg(Address));

	// set disable TDC test mode
	write_op_reg(Address, 0xC600);


	/***  TRIGGER  ***/
	 /*** sets stop trigger matching mode opcode = 0x0000 page 49 ***/
	write_op_reg(Address, 0x0000);

	/*** sets window width opcode = 0x1000 page 51 ***/
	/*** time unit is 25 ns, 0x14 = 500 ns ***/
	/*** 200 ns/25 = 8 = 0x0008 ***/
	cout << "window width set to 0x14 (500ns)" << endl;
	write_op_reg(Address, 0x1000); 
	write_op_reg(Address, 0x0014); 


	/*** sets window offset opcode = 0x1100  page 51 ***/
	/*** window offset = -250ns/25=-10   ***/
	cout << "window offset set to -10 (-250 ns) " <<endl;
	write_op_reg(Address, 0x1100);
	write_op_reg(Address, -10);

	/*** sets enable substraction of trigger time page 52 ***/
	write_op_reg(Address, 0x1400); 

	/*** sets disable substraction of trigger time page 52 ***/
//	write_op_reg(Address, 0x1500); 

	/*** read trigger configuration  page 52 ***/
	cout << "Trigger configuration :" <<endl;
	Data16 MatchWindowWidth,WindowOffset,ExtraSearchWindowWidth,RejectMargin,TriggerTimeSubtraction;
	write_op_reg(Address, 0x1600);
	MatchWindowWidth=read_op_reg(Address);
	WindowOffset=read_op_reg(Address);
	ExtraSearchWindowWidth=read_op_reg(Address);
	RejectMargin=read_op_reg(Address);
	TriggerTimeSubtraction=read_op_reg(Address);
	printf("Match Window Width : 0x%4X \n",(MatchWindowWidth));
	printf("Window Offset : 0x%4X \n",(WindowOffset));
	printf("Extra Search Window Width : 0x%4X\n",(ExtraSearchWindowWidth));
	printf("Reject Margin : 0x%4X \n",(RejectMargin));
	printf("Trigger Time Subtraction : 0x%4X \n",(TriggerTimeSubtraction));
	/***  END OF TRIGGER  ***/

	/*** TDC EDGE DETECTION & RESOLUTION ***/
	/*** Edge detection page 53 ***/
	cout << "Edge detection set to rise and fall (11)"<< endl;
	write_op_reg(Address, 0x2200);
        write_op_reg(Address,0x0003);    /*raise and fall*/

	/*** Readout edge detection ***/
	write_op_reg(Address, 0x2300);
	Data16 edge;
	edge=read_op_reg(Address);
	printf ("Readout edge = %4X \n",(edge & 0x0003));

	/*** Read resolution ***/
	/*** page 54 ***/
	write_op_reg(Address, 0x2600);
	printf ("Resoltion (11 correspond to 25 ns)  = %4X \n",(read_op_reg(Address) & 0x0003));	

	
	/*** Set channel dead time to 5ns (page 55)***/
	cout << "Channel dead time between hits set to 5ns (00)" << endl;
	write_op_reg(Address, 0x2800);
	write_op_reg(Address, 0x0000); /*5ns (default)*/

	/*** Read channel dead time ***/
	write_op_reg(Address, 0x2900);
	Data16 timede;
	timede=read_op_reg(Address);
	printf("Channel dead time (00=5ns) = %4X \n", (timede & 0x0000));
	/*** END OF TDC EDGE DETECTION & RESOLUTION ***/


	/*** TDC READOUT  ***/
	/*** enable TDC header and TRAILER ***/
	write_op_reg(Address, 0x3000);

	/*** read TDC header/trailer on/off ***/
	write_op_reg(Address, 0x3200);
	printf("TDC header/trailer on/off (1/0) = %4X \n", (read_op_reg(Address) & 0x0001));

	/*** read maximum number of hits per event ***/
	write_op_reg(Address, 0x3400);
	 printf("Maximum number of hit/event = %4X \n", (read_op_reg(Address) & 0x000F));

	/***  END TDC READOUT  ***/

	/*** CHANNEL ENABLE ***/

	//enable channels according a 16 bit pattern
	cout << "Enabling the channels ..."<<endl;
	write_op_reg(Address, 0x4400);	
	write_op_reg(Address, 0xFFFF);
	write_op_reg(Address, 0xFFFF);

	/*** read enable channels ***/
	write_op_reg(Address, 0x4500);
	printf("Channels enabled (0-15):  %4X \n", (read_op_reg(Address) & 0xFFFF));
	printf("Channels enabled (16-31):  %4X \n", (read_op_reg(Address) & 0xFFFF));

	return(0);

}

Data16 v1290a::getDready()
{
 Data16 temp;
 if (CAENVME_ReadCycle(Handle,Address+0x1002,&temp,AddressModifier,DataWidth)==1)
	{
	return (temp & 0x0001);
	}
 else 
	{
	return (-1);
	}
}
  

vector<Data32> v1290a::getEventHighRateV()
{
  // read the number of event in the buffer
  std::vector<Data32> v32;
  Data32 data;
  v32.clear();
  Data16 NEvt,NEvt1;
  int res;
  res=CAENVME_ReadCycle(Handle,Address+0x1020,&NEvt,AddressModifier,DataWidth);
  cout << "Number of event stored in the buffer : "<< NEvt <<endl;
  for (int i=0;i<NEvt;i++)
  {
	res=CAENVME_ReadCycle(Handle,Address+0x0000,&data,AddressModifier,cvD32);
  res=CAENVME_ReadCycle(Handle,Address+0x1020,&NEvt1,AddressModifier,DataWidth);
  cout << "Number of event stored in the buffer : "<< NEvt1 <<endl;
	v32.push_back(data);
  }

return v32;
}



void v1290a::getEvent()
{
  Data32 data;
  Data16 EventStored;
  int res; 
  // check the number of events in the buffer p. 80 
  res=CAENVME_ReadCycle(Handle,Address+0x1020,&EventStored,AddressModifier,DataWidth);
  cout << "Number of event stored in the buffer : "<< EventStored <<endl;
  while(EventStored !=0)
  {
	res=CAENVME_ReadCycle(Handle,Address+0x0000,&data,AddressModifier,cvD32);
//	cout << "raw data : "<< data <<endl;
	switch(data & STATUS_TDC)
		{
			case(GLOBAL_HEADER):
						cout << "GLOBAL HEADER " ;
						cout << " Event Count : " << ((data>>5) & 0x3FFFFF)<<endl;
						break;
			case(GLOBAL_TRAILER):
						cout <<"GLOBAL TRAILER ";
						cout <<"Word Count " << (data & 0x001FFFE0)<<endl;
						break;
			case(TDC_HEADER):
						cout <<"TDC HEADER ";
						cout <<"Event id : " << ( (data>>12) & 0x00FFF) << endl;
						break;
			case(TDC_DATA):
						cout <<"Data ";
						cout << " Rise/Fall : "<< ((data>>26) & 0x01) ;
						cout << " Channel : "<<((data>>21) & 0x01F ) ;
						cout << " Value : "<< ( data & 0x001FFFFF)<<endl ;
						break;
						
		}		
  }
}

Data16 v1290a::read_op_reg(unsigned long Address)
{
  int time = 0;
  Data16 ro_bit;
  /*** checks the Read OK bit ***/

  do
    {
 CAENVME_ReadCycle(Handle,Address+0x1030,&ro_bit,AddressModifier,DataWidth);
      time++;
    } while(ro_bit != 0x02 && time < 100000);
  if(time == 100000)
    {
      printf("Reads - timeout error\n");
      exit(0);
    }
  else
    {
      sleep(1); /*** delay 12 msec, internal delay ***/
      /*** reads opcode ***/
 CAENVME_ReadCycle(Handle,Address+0x102E,&ro_bit,AddressModifier,DataWidth );
 return ro_bit;
    }
}

Data16 v1290a::write_op_reg(unsigned long Address, int code)
{
  int time = 0;
  Data16 wo_bit;
  /*** checks the Write OK bit ***/
  do
    {
 CAENVME_ReadCycle(Handle,Address+0x1030,&wo_bit,AddressModifier,DataWidth );
      time++;
//            std::cout<<"wo_bit=WO="<<wo_bit<<std::endl;
    } while(wo_bit != 0x01 && time < 100000);
  if(time == 100000)
    {
      printf("Write opcode - timeout error\n");
      exit(0);
    }
  else
    {
      sleep(1); /*** delay 12 msec, internal delay ***/
      /*** writes opcode = code ***/
      //  std::cout<<"in write_op_reg: code="<<code<<std::endl;
CAENVME_WriteCycle(Handle,Address+0x102E,&code, AddressModifier,DataWidth);
      return 0;
    }
}

