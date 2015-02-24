/************************************************************************/
/*									*/
/*  This is the common header file for the CMEM_RCC 			*/
/*  driver, library & applications					*/
/*									*/
/*  12. Dec. 01  MAJO  created						*/
/*									*/
/*******C 2001 - The software with that certain something****************/

#ifndef _CMEM_RCC_COMMON_H
#define _CMEM_RCC_COMMON_H


#define MAX_CMEM_BUFFERS 100  // Max. number of buffers per process
#define CMEM_MAX_NAME 40

typedef struct
{
  unsigned int paddr;
  unsigned int uaddr;
  unsigned int size;
  unsigned int order;
  unsigned int used;
  unsigned long kaddr;
  char name[CMEM_MAX_NAME];
} cmem_rcc_t;

typedef unsigned int CMEM_Error_code_t;

#endif
