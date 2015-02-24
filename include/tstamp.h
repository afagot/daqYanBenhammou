/************************************************************************/
/*                                                                      */
/*   file: tstamplib.h                                                  */
/*   author: Markus Joos, CERN-EP/ESS                                   */
/*                                                                      */
/*   This is the header of the timestamping library.                    */
/*                                                                      */
/*   History:                                                           */
/*   22.Sep.98  MAJO  created                                           */
/*    3.Mar.99  MAJO  major rewrite; macros added                       */
/*    5.Mar.99  MAJO  default handles and include statement for		*/
/*                    event symbols added                               */
/*    27.Jul.99 JOP   move my_ts_events.h out                           */
/*                                                                      */
/*******Copyright Ecosoft 2001 - Made from 80% recycled bytes************/ 
#include "iom_error.h"

#ifndef _TSTAMPLIB_H
  #define _TSTAMPLIB_H

  typedef struct tstamp
  { 
    unsigned int high;
    unsigned int low;
    unsigned int data;
  } tstamp;

  #define TS_DUMMY 1
 
  #ifdef TSTAMP

    /*constants*/
/*    #define FREQUENCY_LOW     16777216.0*/
    #define FREQUENCY_LOW     16500000.0
    #define FREQUENCY_HIGH    (1.0/256.0)
    #define TS_FULL           1
    #define TS_STOP_TS        2
    #define TS_START_TS       ~TS_STOP_TS
    #define MAX_OPENS         10
  
    enum
      {
      TS_H1=1,
      TS_H2,
      TS_H3,
      TS_H4,
      TS_H5,
      TS_H6,
      TS_H7,
      TS_H8,
      TS_H9,
      TS_H10
      };

    /*macros*/
    static int tstamp_ret;

      #define TS_OPEN(size,ts_handle)\
      {\
      tstamp_ret=ts_open(size,ts_handle);\
      if(tstamp_ret)\
        iom_error_print(stdout,tstamp_ret);\
      }

      #define TS_SAVE(handle, name)\
      {\
      tstamp_ret=ts_save(handle,name);\
      if(tstamp_ret)\
        iom_error_print(stdout,tstamp_ret);\
      }
      
      #define TS_CLOSE(handle)\
      {\
      tstamp_ret=ts_close(handle);\
      if(tstamp_ret)\
        iom_error_print(stdout,tstamp_ret);\
      }
      
      #define TS_RECORD(handle,udata) ts_record(handle,udata)
      #define TS_START(handle) ts_start(handle)
      #define TS_SETT0 ts_sett0()
      #define TS_PAUSE(handle) ts_pause(handle) 
      #define TS_RESUME(handle) ts_resume(handle)
      #define TS_DURATION( t1, t2) ts_duration(t1, t2)
      #define TS_CLOCK(time) ts_clock(time)
      #define TS_DELAY(time) ts_delay(time)
  #else
      #define TS_OPEN(size,ts_handle)
      #define TS_SAVE(handle, name)
      #define TS_CLOSE(handle)
      #define TS_RECORD(handle,udata)
      #define TS_START(handle)
      #define TS_PAUSE(handle)
      #define TS_RESUME(handle)
      #define TS_DURATION( t1, t2)
      #define TS_CLOCK(time) 
      #define TS_DELAY(time) 
      #define TS_SETT0
  #endif

  /*error codes*/
  enum
  {
  TSE_OK = 0,
  TSE_IS_CLOSED = (P_ID_TS <<8)+1,
  TSE_WHAT,
  TSE_SMEM,
  TSE_NO_FREQ,
  TSE_FILE,
  TSE_ILL_HANDLE,
  TSE_ILL_SIZE,
  TSE_PFILE,
  TSE_NO_REF,
  TSE_ERROR_FAIL,
  TSE_NOCODE
  };
  
  #define TSE_OK_STR           "No error"  
  #define TSE_WHAT_STR         "Error received from iom_what library"
  #define TSE_SMEM_STR         "Error received from iom_smem library"
  #define TSE_NO_FREQ_STR      "Failed to set frequency"
  #define TSE_FILE_STR         "Failed to open /proc/cpuinfo"
  #define TSE_ILL_HANDLE_STR   "Parameter >handle< is out of range"
  #define TSE_IS_CLOSED_STR    "The library has not been opened"
  #define TSE_ILL_SIZE_STR     "Parameter >size< is out of range"
  #define TSE_PFILE_STR        "Failed to open/close data file"
  #define TSE_NO_REF_STR       "Reference time missing (ts_sett0)"
  #define TSE_ERROR_FAIL_STR   "Failed to initialise the error system"
  #define TSE_NOCODE_STR       "Unknown error code"

  #define ERR_CASE(a) case a: strcpy (en_str, a ## _STR) ; \
    result = WHATE_OK ; break
   
   
  #ifdef __cplusplus
    extern "C" {
  #endif

  /*prototypes*/
  float ts_duration(tstamp t1, tstamp t2); 
  err_type ts_open(int size, int handle);
  err_type ts_close(int handle);
  err_type ts_save(int handle, char *name);
  err_type ts_elapsed (tstamp t1, float *time);
  err_type ts_get_freq(void);
  err_type ts_record(int handle, int udata);
  err_type ts_sett0(void);
  err_type ts_start(int handle);
  err_type ts_pause(int handle); 
  err_type ts_resume(int handle);
  err_type ts_clock(tstamp *time);
  err_type ts_delay(unsigned int usecs);
  err_type packTS_err_get (err_pack err, err_str pid_str, err_str en_str);


  #ifdef __cplusplus
    }
  #endif
#endif
