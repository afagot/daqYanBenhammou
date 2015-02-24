/************************************************************************/
/*									*/
/* File: vme_rcc.h							*/
/*									*/
/* This is the public header file for RCC VMEbus library		*/
/*									*/
/* 12. Oct. 01  MAJO  created						*/
/*									*/
/* 011101 JOP add error codes						*/
/* 020418 JOP ROAK / RORA						*/
/* 020527 JOP update interrupt API					*/
/*									*/
/************ C 2001 - The software with that certain something *********/

#ifndef _VME_RCC_H 
#define _VME_RCC_H

#include <linux/types.h>
#include "vme_rcc_common.h"

/***********************************/
/*VMEbus transfer type  definitions*/
/***********************************/
#define VME_RP         0x01
#define VME_WP         0x02
#define VME_A16        0x0
#define VME_A24        0x1
#define VME_A32        0x2
#define VME_CRCSR      0x5
#define VME_AM09       (VME_A32)
#define VME_AM39       (VME_A24)
#define VME_AM29       (VME_A16)
#define VME_AM2f       (VME_CRCSR)
#define VME_DMA_READ   0x00
#define VME_DMA_WRITE  0x80000000
#define VME_DMA_D32    0x00800000
#define VME_DMA_D64    0x00c00000
#define VME_DMA_DEF    0x00020100 //A32, program, data, BLT
#define VME_DMA_D32W   (VME_DMA_DEF | VME_DMA_D32 | VME_DMA_WRITE)
#define VME_DMA_D32R   (VME_DMA_DEF | VME_DMA_D32 | VME_DMA_READ)
#define VME_DMA_D64W   (VME_DMA_DEF | VME_DMA_D64 | VME_DMA_WRITE)
#define VME_DMA_D64R   (VME_DMA_DEF | VME_DMA_D64 | VME_DMA_READ)

/************************************************/
/*Identifier definitions for CR/CSR space access*/
/*                                              */
/* Bits 31..30  Number of bytes to read         */
/* Bits 29..00  Offset of first byte            */
/************************************************/
#define ONE_BYTE           0x20000000
#define TWO_BYTE           0x40000000
#define THREE_BYTE         0x80000000
#define FOUR_BYTE          0xc0000000

#define CR_CHECKSUM        (ONE_BYTE   | 0x00003)
#define CR_LENGTH          (THREE_BYTE | 0x00007)
#define CR_CRACCESSWIDTH   (ONE_BYTE   | 0x00013)
#define CR_CSRACCESSWIDTH  (ONE_BYTE   | 0x00017)
#define CR_CRCSRSPEC       (ONE_BYTE   | 0x0001b)
#define CR_ASCII1          (ONE_BYTE   | 0x0001f)
#define CR_ASCII2          (ONE_BYTE   | 0x00023)
#define CR_MANUFID         (THREE_BYTE | 0x00027)
#define CR_BOARDID         (FOUR_BYTE  | 0x00033)
#define CR_REVID           (FOUR_BYTE  | 0x00043)
       
#define CSR_BAR            (ONE_BYTE   | 0x7ffff)
#define CSR_BSR            (ONE_BYTE   | 0x7fffb)
#define CSR_BCR            (ONE_BYTE   | 0x7fff7)
#define CSR_ADER7          (FOUR_BYTE  | 0x7ffd3)
#define CSR_ADER6          (FOUR_BYTE  | 0x7ffc3)
#define CSR_ADER5          (FOUR_BYTE  | 0x7ffb3)
#define CSR_ADER4          (FOUR_BYTE  | 0x7ffa3)
#define CSR_ADER3          (FOUR_BYTE  | 0x7ff93)
#define CSR_ADER2          (FOUR_BYTE  | 0x7ff83)
#define CSR_ADER1          (FOUR_BYTE  | 0x7ff73)
#define CSR_ADER0          (FOUR_BYTE  | 0x7ff63)


/***************************************/
/*various upper limits for arrays, etc.*/
/***************************************/
#define VME_MAXBLOCK    32  //Max number of blocks in VME_BlockTransferList_t
#define VME_MAXSTRING   256 

/******************/
/*type definitions*/
/******************/
typedef unsigned int   VME_ErrorCode_t;

typedef struct 
{
  u_int vmebus_address;
  u_int system_iobus_address;
  u_int size_requested;
  u_int control_word;
  u_int size_remaining;
  u_int status_word;
} VME_BlockTransferItem_t;

typedef struct 
{
  int                     number_of_items;
  VME_BlockTransferItem_t list_of_items[VME_MAXBLOCK];
} VME_BlockTransferList_t;

typedef struct
{
  u_char vector;
  u_int level;
  u_int type;
} VME_InterruptItem_t;

typedef struct
{
  int                 number_of_items;
  VME_InterruptItem_t list_of_items[VME_MAXINTERRUPT];
} VME_InterruptList_t;

typedef struct 
{
  u_char vector;
  u_int  level;
  u_int type;
  u_int  multiple;
} VME_InterruptInfo_t;

/************/
/*Prototypes*/
/************/
#ifdef __cplusplus
extern "C" {
#endif


/*******************************/ 
/*Official functions of the API*/
/*******************************/ 
int VME_ErrorPrint(VME_ErrorCode_t error_code);
int VME_ErrorString(VME_ErrorCode_t error_code, char *error_string);
int VME_ErrorNumber(VME_ErrorCode_t error_code, int *error_number);
VME_ErrorCode_t VME_Open(void);
VME_ErrorCode_t VME_Close(void);
VME_ErrorCode_t VME_ReadCRCSR(int slot_number, u_int crcsr_identifier, u_int *value);
VME_ErrorCode_t VME_WriteCRCSR(int slot_number, u_int crcsr_identifier, u_int value);
VME_ErrorCode_t VME_MasterMap(VME_MasterMap_t *master_map, int *master_mapping);
VME_ErrorCode_t VME_MasterMapVirtualAddress(int master_mapping, u_int *virtual_address);
VME_ErrorCode_t VME_ReadSafeUInt(int master_mapping, u_int address_offset, u_int *value);
VME_ErrorCode_t VME_ReadSafeUShort(int master_mapping, u_int address_offset, u_short *value);
VME_ErrorCode_t VME_ReadSafeUChar(int master_mapping, u_int address_offset, u_char *value);
VME_ErrorCode_t VME_WriteSafeUInt(int master_mapping, u_int address_offset, u_int value);
VME_ErrorCode_t VME_WriteSafeUShort(int master_mapping, u_int address_offset, u_short value);
VME_ErrorCode_t VME_WriteSafeUChar(int master_mapping, u_int address_offset, u_char value);
VME_ErrorCode_t VME_MasterUnmap(int master_mapping);
VME_ErrorCode_t VME_MasterMapDump(void);
VME_ErrorCode_t VME_BusErrorRegisterSignal(int signal_number);
VME_ErrorCode_t VME_BusErrorInfoGet(VME_BusErrorInfo_t *bus_error_info);
VME_ErrorCode_t VME_SlaveMap(VME_SlaveMap_t *slave_map, int *slave_mapping);
VME_ErrorCode_t VME_SlaveMapVmebusAddress(int slave_mapping, u_int *vmebus_address);
VME_ErrorCode_t VME_SlaveUnmap(int slave_mapping);
VME_ErrorCode_t VME_SlaveMapDump(void);
VME_ErrorCode_t VME_BlockTransferInit(VME_BlockTransferList_t *block_transfer_list, int *block_transfer);
VME_ErrorCode_t VME_BlockTransferStart(int block_transfer);
VME_ErrorCode_t VME_BlockTransferWait(int block_transfer, int time_out, VME_BlockTransferList_t *block_transfer_list);
VME_ErrorCode_t VME_BlockTransferEnd(int block_transfer);
VME_ErrorCode_t VME_BlockTransfer(VME_BlockTransferList_t *block_transfer_list, int time_out);
VME_ErrorCode_t VME_BlockTransferDump(void);
VME_ErrorCode_t VME_BlockTransferStatus(VME_BlockTransferList_t *block_transfer_list, int position_of_block, VME_ErrorCode_t *status);
VME_ErrorCode_t VME_BlockTransferRemaining(VME_BlockTransferList_t *block_transfer_list, int position_of_block, int *remaining);
VME_ErrorCode_t VME_InterruptLink(VME_InterruptList_t* vmebus_interrupt_list, int *interrupt);
VME_ErrorCode_t VME_InterruptReenable(int interrupt);
//  VME_ErrorCode_t VME_InterruptDisable(int interrupt);
//  VME_ErrorCode_t VME_InterruptSetLevel(int level, int irq_mode);
//  VME_ErrorCode_t VME_InterruptRORAEnable(int level);
VME_ErrorCode_t VME_InterruptWait(int interrupt, int time_out, VME_InterruptInfo_t* ir_info);
VME_ErrorCode_t VME_InterruptRegisterSignal(int interrupt, int signal_number);
VME_ErrorCode_t VME_InterruptInfoGet(int interrupt, VME_InterruptInfo_t* ir_info);
VME_ErrorCode_t VME_InterruptUnlink(int interrupt);
VME_ErrorCode_t VME_InterruptGenerate(int level, u_char vector);
VME_ErrorCode_t VME_InterruptDump(void);
VME_ErrorCode_t VME_UniverseMap(u_int *virtual_address);
VME_ErrorCode_t VME_UniverseUnmap(u_int virtual_address);
VME_ErrorCode_t VME_CCTSetSwap(u_char data);
VME_ErrorCode_t VME_IOPOKE(u_int offset, u_char value);
VME_ErrorCode_t VME_IOPeek(u_int offset, u_char *value);
VME_ErrorCode_t VME_Update(unsigned int *data);
VME_ErrorCode_t VME_PCIMap(int pci_address, u_int *virtual_address, u_int size);
VME_ErrorCode_t VME_PCIUnmap(u_int virtual_address, u_int size);
void VME_ReadFastUInt(int master_mapping, u_int address_offset, u_int *value);
void VME_ReadFastUShort(int master_mapping, u_int address_offset, u_short *value);
void VME_ReadFastUChar(int master_mapping, u_int address_offset, u_char *value);
void VME_WriteFastUInt(int master_mapping, u_int address_offset, u_int value);
void VME_WriteFastUShort(int master_mapping, u_int address_offset, u_short value);
void VME_WriteFastUChar(int master_mapping, u_int address_offset, u_char value);

/******************************/
/* Internal service functions */
/******************************/
VME_ErrorCode_t vmercc_err_get(err_pack err, err_str pid, err_str code);

/**********************************/ 
/*Additional (temporary) functions*/
/**********************************/
VME_ErrorCode_t VME_test(void);


#ifdef __cplusplus
}
#endif

#endif
