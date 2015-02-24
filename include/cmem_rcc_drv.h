/************************************************************************/
/*									*/
/*  This is the common header file for the CMEM_RCC driver & library	*/
/*									*/
/*  12. Dec. 01  MAJO  created						*/
/*									*/
/*******C 2001 - The software with that certain something****************/

#ifndef _CMEM_RCC_IOCTL_H
#define _CMEM_RCC_IOCTL_H

#include "cmem_rcc_common.h"

#ifdef CMEM_RCC_KERNEL_DEBUG
  #define kdebug(x) printk x
#else
  #define kdebug(x)
#endif


#ifdef CMEM_RCC_LIB_DEBUG
  #define debug(x) printf x
#else
  #define debug(x)
#endif

// Constants
#define MAX_BUFFS 100  // Max. number of buffers for all processes

// Types
typedef struct
  {
    unsigned int paddr;
    unsigned int kaddr;
    unsigned int size;
    unsigned int pid;
    unsigned int order;
    char name[40];
  } buffer_t;
  
/*************/
/*ioctl codes*/
/*************/
enum
{
  CMEM_RCC_GET=1,
  CMEM_RCC_FREE
};

#endif

