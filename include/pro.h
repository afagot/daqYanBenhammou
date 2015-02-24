/************************************************************************/
/* package: online_v2.1                                                 */
/* file: pro.h                                                          */
/* created by EJW 03.04.2000                                            */
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

#ifndef PRO
#define PRO

#include <stdio.h>

#define OK   0
#define ERR -1

/*Bit operations.*/
#define TEST_BIT(b,r)   ( ((r) & (1<<(b))) >> (b) )
#define SET_BIT(b,r)    r = (r) | (1<<(b))
#define CLEAR_BIT(b,r)  r = (r) & (~(1<<(b)))
#define TOGGLE_BIT(b,r) r = (r) ^ (1<<(b))

typedef enum {FALSO, VERDAD} Booleano;

typedef unsigned char Uchar;
typedef Uchar    Data8;

typedef unsigned short Ushort;
typedef Ushort    Data16;
typedef Ushort    Word16;

typedef unsigned int Uint;
typedef Uint    Data32;
typedef Uint    Word32;

#endif
