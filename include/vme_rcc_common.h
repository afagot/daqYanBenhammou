/************************************************************************/
/*									*/
/* File: vme_rcc_common.h						*/
/*									*/
/* This is the common public header file for RCC VMEbus library		*/
/* and driver								*/
/*									*/
/*  2. Nov. 01  MAJO  created						*/
/*  2. Nov. 01  JOP   interrupts					*/
/*  26 Nov. 01  JOP   bus errors					*/
/*  19 Apr. 02  JOP   ROAK / RORA					*/
/*  27 May. 02  JOP   modify interrupt API				*/
/*									*/
/************ C 2001 - The software with that certain something *********/

#ifndef _VME_RCC_COMMON_H 
#define _VME_RCC_COMMON_H

#ifdef __KERNEL__
  #include <linux/types.h>
  #define P_ID_VMERCC 2   // Needs to be re-defined here since we do not want to include rcc_error.h at this level
#else
  #include <sys/types.h>
#endif

/***************/
/*CCT SBC types*/
/***************/
#define VP_UNKNOWN 0
#define VP_PSE     1
#define VP_PMC     2
#define VP_100     3
#define VP_CP1     4


#define VME_MAXVECTOR 10	// Max # vectors per handle
#define VME_MAXINTERRUPT 20	// Max # vectors per handle
#define VME_MAX_BERR_PROCS 10	// Max # processes with BERR handling

enum {
  VME_LEVELISDISABLED = 0,
  VME_INT_ROAK,
  VME_INT_RORA
};

/*************/
/*error codes*/
/*************/

/*error codes*/
enum
{
  VME_SUCCESS = 0,
  VME_NOTKNOWN = (P_ID_VMERCC <<8)+1,
  VME_UNKNOWN,
  VME_NOTOPEN,
  VME_RANGE,
  VME_BUSERROR,
  VME_ALIGN,
  VME_NOCHAINMEM,
  VME_NOBUSERROR,
  VME_TOOLONG,
  VME_DMABUSY,          // 10
  VME_TIMEOUT,
  VME_FILE,
  VME_NOMAP,
  VME_NOSTATMAP,
  VME_IRGBUSY,
  VME_EIO,
  VME_EFAULT,
  VME_VIRT,
  VME_REMAP,
  VME_ENOSYS,		// 20
  VME_NOSIZE,
  VME_CMEM_FAIL,
  VME_ERESTARTSYS,
  VME_DMAERR,
  VME_PCI_ERR,
  VME_VME_ERR,
  VME_PROTOCOL_ERR,
  VME_NOT_EXECUTED,     
  VME_MUNMAP,
  VME_ILLREV,		// 30
  VME_IOREMAP,
  VME_REQIRQ,
  VME_TOOMANYINT,
  VME_TOOMANYHDL,
  VME_INTUSED,
  VME_ILLINTLEVEL,
  VME_ILLINTTYPE,
  VME_INTCONF,
  VME_LVLDISABLED,
  VME_LVLISNOTRORA,	// 40
  VME_ILLINTHANDLE,
  VME_INTBYSIGNAL,
  VME_NOINTERRUPT,
  VME_ENOMEM,           
  VME_KMALLOC,
  VME_BERRTBLFULL,
  VME_BERRNOTFOUND,
  VME_ERROR_FAIL,
  VME_ILL_TO,
  VME_NODOMEMEM,	// 50
  VME_NO_CODE,
  VME_UNKNOWN_BOARD,
  VME_NOCRCSRMAP
};


/******************/
/*type definitions*/
/******************/
typedef struct 
{
  u_int vmebus_address;
  u_int window_size;
  u_int address_modifier;
  u_int options; 
} VME_MasterMap_t;

typedef struct 
{
  u_int system_iobus_address;
  u_int window_size;
  u_int address_width;
  u_int options;
} VME_SlaveMap_t;

typedef struct
{
  u_int vmebus_address;
  u_int address_modifier;
  u_int lword;
  u_int ds0;
  u_int ds1;
  u_int wr;
  int  multiple;
} VME_BusErrorInfo_t;

#endif
