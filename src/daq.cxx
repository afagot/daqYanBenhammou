// **********************************************************************
// *   DAQ for the GIF 
// *   Y.Benhammou, Alexis Fagot
// *   14/1/2015
// *********************************************************************

#include <fstream>
#include <iostream>
#include <time.h>
#include <signal.h>
#include "v1718.h"
#include "v1190a.h"
#include "MsgSvc.h"
#include <parameter.h>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#define OUTPUTLEVEL LVL_DEBUG

using namespace std;

/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

bool forever = true;

void sighandler1(int sig)
{

  forever = false ;

}


int main (int argc ,char *argv[])
{
  MSG_INFO("****************************************************\n");
  MSG_INFO("******    DAQ Program 14/1/15 Version 1.00    ******\n");
  MSG_INFO("****************************************************\n");

  /**********declare parameter************************************/
  int NQdc,NTmc,NTdc,NScaler,NIO,ret;
  int NEvent=0;
  string Path,Folder,runCount,Setup;
  unsigned long retlong;
  double delta ,deltaover;
  
  signal(SIGTSTP , &sighandler1);  //C-z to stop the loop

  /***********initial vme*****************************************/
  v1718 vme(BASEV1718);


  /**********initial the TDC 1190a *****************/
  v1190a *tdc = new v1190a(vme.GetHandle(),BASEV1190A);
  tdc->Get_Firmware_Rev();
  
  /* START OF THE LOOP */
  MSG_INFO("START OF THE RUN ... \n");
  
  MSG_INFO("To finish the run press Ctrl-z\n");
  
//  logger <<"-------------------------------------------" <<endl;
//  logger <<"Error/Warning:"<<endl;
//  IO[0]->SetNIMPulse(1);
//  Scaler[0]->Reset();
//  int timeout = 45;
//  while (forever)
//    {
//    } //finish run
    
  return 0;
}


