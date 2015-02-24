/************************************************************************/
/*									*/
/*  This is the common header file for the CMEM_RCC 			*/
/*  library & applications						*/
/*									*/
/*  12. Dec. 01  MAJO  created						*/
/*									*/
/*******C 2001 - The software with that certain something****************/

#ifndef _CMEM_RCC_H
#define _CMEM_RCC_H

#include "cmem_rcc_common.h"

// Error codes
enum
{
  CMEM_RCC_SUCCESS = 0,
  CMEM_RCC_ERROR_FAIL = (P_ID_CMEM_RCC <<8)+1,
  CMEM_RCC_FILE,
  CMEM_RCC_NOTOPEN,
  CMEM_RCC_IOCTL,
  CMEM_RCC_MMAP,
  CMEM_RCC_MUNMAP,
  CMEM_RCC_OVERFLOW,
  CMEM_RCC_TOOBIG,
  CMEM_RCC_ILLHAND,
  CMEM_RCC_NO_CODE
};

//Error strings
#define CMEM_RCC_SUCCESS_STR      "No error"
#define CMEM_RCC_ERROR_FAIL_STR   "Failed to install the error library"
#define CMEM_RCC_FILE_STR         "Failed to open /dev/cmem_rcc"
#define CMEM_RCC_NOTOPEN_STR      "Library has not yet been opened"
#define CMEM_RCC_IOCTL_STR        "Error from call to ioctl function"
#define CMEM_RCC_MMAP_STR         "Error from call to mmap function"
#define CMEM_RCC_MUNMAP_STR       "Error from call to munmap function"
#define CMEM_RCC_NO_CODE_STR      "Unknown error"
#define CMEM_RCC_OVERFLOW_STR     "All descritors are in use"
#define CMEM_RCC_TOOBIG_STR       "Size is too big"
#define CMEM_RCC_ILLHAND_STR      "Invalid handle"

/************/
/*Prototypes*/
/************/
#ifdef __cplusplus
extern "C" {
#endif

CMEM_Error_code_t CMEM_Open(void);
CMEM_Error_code_t CMEM_Close(void);
CMEM_Error_code_t CMEM_SegmentAllocate(unsigned int size, char *name, int *segment_identifier);
CMEM_Error_code_t CMEM_SegmentFree(int segment_identifier);
CMEM_Error_code_t CMEM_SegmentSize(int segment_identifier, unsigned int *actual_size);
CMEM_Error_code_t CMEM_SegmentPhysicalAddress(int segment_identifier, unsigned int *physical_address);
CMEM_Error_code_t CMEM_SegmentVirtualAddress(int segment_identifier, unsigned int *virtual_address);
CMEM_Error_code_t CMEM_Dump(void);
CMEM_Error_code_t CMEM_err_get(err_pack err, err_str pid, err_str code);

#ifdef __cplusplus
}
#endif

#endif
