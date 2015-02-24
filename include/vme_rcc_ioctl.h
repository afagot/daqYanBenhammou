/************************************************************************/
/*									*/
/* File: vme_rcc_ioctl.h						*/
/*									*/
/* This header file contains definitions for the ioctl function calls	*/
/* linking the RCC VMEbus library to the driver				*/
/*									*/
/* 26. Oct. 01  MAJO  created						*/
/* 02. Nov. 01  JOP   interrupts					*/
/* 26. Nov. 01  JOP   bus errors					*/
/* 18. Apr. 02  JOP   ROAK / RORA					*/
/* 27. May. 02  JOP   modify interrupt API				*/
/*									*/
/************ C 2001 - The software with that certain something *********/

#ifndef _VME_RCC_IOCTL_H 
#define _VME_RCC_IOCTL_H

#include <linux/types.h>

/*************/
/*ioctl codes*/
/*************/
enum 
{
  VMEMASTERMAP = 1,
  VMEMASTERUNMAP,
  VMEMASTERMAPDUMP,
  VMEBERRREGISTERSIGNAL,
  VMEBERRINFO,
  VMESLAVEMAP,
  VMESLAVEMAPDUMP,
  VMESCSAFE,
  VMEDMASTART,
  VMEDMAPOLL,
  VMEDMADUMP,
  VMELINK,
  VMESETLEVEL,
  VMEINTENABLE,
  VMEINTDISABLE,
  VMEWAIT,
  VMEREGISTERSIGNAL,
  VMEINTERRUPTINFOGET,
  VMEUNLINK,
  VMETSTART,
  VMETSTOP,
  VMEUNIVERSEMAP,
  VMEIOPEEK,
  VMEIOPOKE,
  VMEUPDATE,
  /*VMEGETID,*/
  VMETEST
};


/*******************/
/* Other constants */
/*******************/
#define TEXT_SIZE1              3000
#define TEXT_SIZE2              20000

/******************/
/*type definitions*/
/******************/
typedef struct 
{
  VME_MasterMap_t  in;
  u_int            pci_address;
  u_int            virt_address;  //for the user
  u_int            kvirt_address; //for the kernel
  u_int            used;
}VME_MasterMapInt_t;

typedef struct 
{
  VME_SlaveMap_t  in;
  u_int           vme_address;
  u_int           used;
}VME_SlaveMapInt_t;

typedef struct 
{
  u_int kvirt_address;
  u_int offset;
  u_int data;
  u_int nbytes;
  u_int rw;
}VME_SingleCycle_t;

typedef struct 
{
  u_int dctl;         //Universe chain descriptor
  u_int dtbc;         //Universe chain descriptor
  u_int dla;          //Universe chain descriptor
  u_int reserved1;    //Universe chain descriptor
  u_int dva;          //Universe chain descriptor
  u_int reserved2;    //Universe chain descriptor
  u_int dcpp;         //Universe chain descriptor
  u_int reserved3;    //Universe chain descriptor
  u_int ref;          //used by the library
  u_int reserved4[7]; //the size of the whole structure has to be a multiple of 32 bytes
} VME_DmaChain_t;

typedef struct
{
  u_int handle;
  u_int pid;  
  u_int ctrl;
  u_int counter;
  u_int timeout;
  int timeoutval;
} VME_DMAhandle_t;

typedef struct
{
  u_int nvectors;
  u_int vector[VME_MAXINTERRUPT];	// use int internally
  u_int level;			// SAME for all vectors
  u_int type;			// SAME for all vectors
} VME_IntHandle_t;

typedef struct
{
  u_int level;
  u_int type;
} VME_IntEnable_t;

typedef struct
{
  VME_IntHandle_t int_handle;
  int timeout;
  u_int level;
  u_int type;
  u_int vector;	// use int internally
  u_int multiple;
} VME_WaitInt_t;

typedef struct
{
  VME_IntHandle_t int_handle;
  int signum;
} VME_RegSig_t;

typedef struct
{
  u_int paddr;
  u_int handle;
} VME_DMAstart_t;

typedef struct
{
  u_int offset;
  u_char data;
} VME_IO_t;

typedef struct
{
  u_int irq_mode[8];
} VME_Update_t;



/********/
/*Macros*/
/********/
#ifdef __powerpc__
  #define BSWAP(x) bswap(x)
  #define SYNC __asm__("eieio")
#endif

#ifdef __i386__
  #define BSWAP(x) (x)
  #define SYNC
#endif

#endif

