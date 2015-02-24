/************************************************************************/
/* package: online_v2.1                                                 */
/* file: online.h                                                       */
/* created by JAWA 05.08.2002                                           */
/* history:                                                             */
/* online_v1.0 - basic code                                             */
/* online_v1.1 - reject events without data from Precision Chambrers    */
/*               and from TGC, name of output data file is a date and   */
/*               time of run                                            */
/* online_v1.2 - couting of reject data, a results is printing on       */
/*               a screen at the end of DAQ                             */
/* online_v2.0 - pedestals and thresholds of C-RAMS are calculating     */
/*               using a PAW routines                                   */
/* online_v2.1 - new format of binary output file. That format includes */
/*               the number of run, the data and the time of run        */
/************************************************************************/

#ifndef ONLINE
#define ONLINE

//#define NUMCH 	960     /*Monitor: number of adc channels for run.mon2. This must be a multiplicative of 32*/
#define MAXNUMCHANNELS 1056 /*3.11 p.13.*/

#define MAXZEROCOUNT	14
#define	MAXFITPROBS	14000
#define THR_PERCENTAGE .80
#define THR_HI_PERCENT	10.00

#define OK	 0
#define FAIL	 3
#define QUIT	 2
#define DISABLED 1
#define ENABLED	 0

/*** librarys ***/
#include <stdio.h>
#include "pro.h"
#include <math.h>
#include <fcntl.h>
#include <sys/io.h>
#include <errno.h>
#include <sys/types.h>
#include <signal.h>
// #include "rcc_error.h"
// #include "vme_rcc.h"
#include "get_input.h"
// #include "tstamp.h"
#include "universe.h"
#include <sys/timeb.h>
#include <time.h>
#include <unistd.h>
#include <v550.h>
#include <v551.h>
/*** routines ***/


int clear_v550(v550 v550_i,v551 v551_i);
void vme_write16(Word32 address, Data16 datum);
void vme_write32(Word32 address, Data32 datum);
Data16 vme_read16(Word32 address);
Data32 vme_read32(Word32 address);

//void delay(int time);

//unsigned int sleep(unsigned int seconds);
//ssize_t write(int fd, const void *buf, size_t count);
//ssize_t read(int fd, void *buf, size_t count);
//int close(int fd);
//int atoi(const char *nptr);
//void quitsig();
//void quitproc();

#endif
