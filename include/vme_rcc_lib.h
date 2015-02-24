/************************************************************************/
/*									*/
/* File: vme_rcc_lib.h							*/
/*									*/
/* This is the private header file for RCC VMEbus library		*/
/*									*/
/*  2. Nov. 01  MAJO  created						*/
/*  2. Nov. 01  JOP   interrupts					*/
/*									*/
/************ C 2001 - The software with that certain something *********/

#ifndef _VME_RCC_LIB_H 
#define _VME_RCC_LIB_H

#include <linux/types.h>
#include "vme_rcc_common.h"
#include "vme_rcc_ioctl.h"

/***************/
/*error strings*/
/***************/
#define VME_SUCCESS_STR        "Function successfully executed"
#define VME_NOTKNOWN_STR       "Input parameter has illegal value"
#define VME_UNKNOWN_STR        "Unknown type of error"
#define VME_NOTOPEN_STR        "The library has not yet been opened"
#define VME_RANGE_STR          "Input parameter is out ofrange"
#define VME_BUSERROR_STR       "VMEbus bus error received"
#define VME_ALIGN_STR          "Misaligned address/size"
#define VME_NOCHAINMEM_STR     "Not enough memory available for DMA chain"
#define VME_NOBUSERROR_STR     "There was no bus error information"
#define VME_TOOLONG_STR        "Overflow of internal chain"
#define VME_DMABUSY_STR        "The DMA controller is busy"
#define VME_TIMEOUT_STR        "The time-out has expired"
#define VME_FILE_STR           "Error from file operation (open/close)"
#define VME_NOMAP_STR          "All master mappings are in use"
#define VME_NOSTATMAP_STR      "Static mapping does not fit parameters"
#define VME_IRGBUSY_STR        "The interrupg generator is busy"
#define VME_EIO_STR            "Unix: I/O error"
#define VME_EFAULT_STR         "Unix: Bad address"
#define VME_VIRT_STR           "Failed to get user virtual address"
#define VME_REMAP_STR          "Error from remap_page_range() kernel function"
#define VME_ENOSYS_STR         "Unix: Function not implemented"
#define VME_NOSIZE_STR         "A <size> parameter is zero"
#define VME_CMEM_FAIL_STR      "Error from CMEM_RCC library"
#define VME_ERESTARTSYS_STR    "Unix: driver got interrupted in down_interruptible"
#define VME_DMAERR_STR         "Error in DMA transfer, see status words in transfer list"
#define VME_PCI_ERR_STR        "Error on PCI"
#define VME_VME_ERR_STR        "VMEbus BERR"
#define VME_PROTOCOL_ERR_STR   "Protocol error"
#define VME_NOT_EXECUTED_STR   "This transfer has not been executed"
#define VME_MUNMAP_STR         "Error from call to munmap()"
#define VME_ILLREV_STR         "Universe has wrong revision (too old)"
#define VME_IOREMAP_STR        "Error from call to ioremap()"
#define VME_REQIRQ_STR         "Error from call to request_irq()"
#define VME_TOOMANYINT_STR     "Too many interrupt items"
#define VME_TOOMANYHDL_STR     "Too many Interrupt handles"
#define VME_INTUSED_STR        "Vector already in use"
#define VME_ILLINTLEVEL_STR    "Illegal Interrupt Level"
#define VME_ILLINTTYPE_STR     "Illegal Interrupt Type"
#define VME_INTCONF_STR        "Illegal level, type combination"
#define VME_LVLDISABLED_STR    "Level is disabled"
#define VME_LVLISNOTRORA_STR   "Level is not RORA"
#define VME_ILLINTHANDLE_STR   "Illegal interrupt handle"
#define VME_INTBYSIGNAL_STR    "Interrupted by signal"
#define VME_NOINTERRUPT_STR    "No pending interrupt found"
#define VME_ENOMEM_STR         "No memory"
#define VME_KMALLOC_STR        "Error in driver from call to kmalloc"
#define VME_BERRTBLFULL_STR    "BERR process table full"
#define VME_BERRNOTFOUND_STR   "Entry in BERR process table not found"
#define VME_ILL_TO_STR         "value for time_out is out of range"
#define VME_NODOMEMEM_STR      "No morememory left in DMA done list"
#define VME_NO_CODE_STR        "No error code available"
#define VME_UNKNOWN_BOARD_STR  "Failed to determine board type"
#define VME_NOCRCSRMAP_STR     "There is no mapping for CR/CSR space access"

/***************************************/
/*Various upper limits for arrays, etc.*/
/***************************************/
#define VME_MAX_MASTERMAP        32  //Max number of master mappings
#define VME_MAX_SLAVEMAP          4  //Max number of slave mappings
#define VME_MAXCHAINEL           16  //Max number of elements in DMA chain (>VME_MAXBLOCK)
#define VME_MAXCHAIN             16  //Max number of internal DMA chains
#define DMA_DESC_SIZE            (VME_MAXCHAINEL * VME_MAXCHAIN * sizeof(VME_DmaChain_t)) 

#define VME_DMA_MAX_BLOCK_SIZE   0x800000 //Max size of single DMA
#define VME_MAX_INTHANDLE	 10	  // Max # interrupt handles

/***************************************/
/*Definitions to be used in the library*/
/*do not modify                        */
/***************************************/
#define DEVICE                  "/dev/vme_rcc"
#define DMA_CHAIN_END           1
#define CRCSR_BASE              0
#define CRCSR_SIZE              0x01000000
#define CRCSR_OPT               0
#define CRCSR_OFF               0x80000

/******************/
/*type definitions*/
/******************/

/********/
/*Macros*/
/********/
#define ISOPEN {if(!is_open) return(VME_NOTOPEN);}
#define PE(x) {printf("Error from vme_rcc library: %s\n",x);     break;}

#ifdef DEBUG
  #define debug(x) printf x
#else
  #define debug(x)
#endif


#ifdef __cplusplus
extern "C" {
#endif
/******************************/
/* Internal service functions */
/******************************/
#ifdef __cplusplus
}
#endif


#endif
