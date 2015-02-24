/************************************************************************/
/*                                                                      */
/*   file: iom_smem.h                                                   */
/*   author: Markus Joos, CERN-EP/ESS                                   */
/*                                                                      */
/*   History:                                                           */
/*   26.Feb.99  MAJO  created                                           */
/*                                                                      */
/*******Copyright 1999 - The software with that certain something********/

#ifndef _IOM_SMEM_H
#define _IOM_SMEM_H
 
#ifdef DEBUG
#define debug(x) printf x
#else
#define debug(x)
#endif


/*for the linux version*/
typedef struct
{
char name[100];
unsigned int vaddr;
unsigned int paddr;
unsigned int size;
} T_mmap_table;

#define MAXIMAPS 100



enum smem_errors 
{
SMEME_OK = 0x00,
SMEME_EFAULT = (P_ID_SMEM <<8) + 1,
SMEME_EINVAL,
SMEME_ENOMEM,
SMEME_UNKNOWN,
SMEME_DEV,
SMEME_MMAP,
SMEME_MUNMAP,
SMEME_FDCLOSE,
SMEME_NOCODE,
SMEME_CAPA_FAIL,
SMEME_SETMAP,
SMEME_DELMAP,
SMEME_ILLNAME,
SMEME_ERROR_FAIL
};

#define SMEME_OK_STR          "No error"
#define SMEME_EFAULT_STR      "EFAULT received from smem_create/smem_remove"
#define SMEME_EINVAL_STR      "EINVAL received from smem_create/smem_remove"
#define SMEME_ENOMEM_STR      "ENOMEM received from smem_create"
#define SMEME_UNKNOWN_STR     "Unknown error received from smem_create"
#define SMEME_DEV_STR         "Failed to open the /dev/mem device"
#define SMEME_MMAP_STR        "Error received from mmap"
#define SMEME_MUNMAP_STR      "Error received from munmap"
#define SMEME_FDCLOSE_STR     "Error on closing /dev/mem"
#define SMEME_CAPA_FAIL_STR   "Error from call to capability server"
#define SMEME_SETMAP_STR      "Error from call to set_map"
#define SMEME_DELMAP_STR      "Error from call to del_map"
#define SMEME_NOCODE_STR      "Unknown error"
#define SMEME_ILLNAME_STR     "smem_open has already been called with this name"

#ifdef __cplusplus
extern "C" {
#endif

/*Prototypes*/
extern int smem_close(char *name, char *vaddr, unsigned int length);
extern int smem_open(char *name,char *physaddr,unsigned int size, char **vaddr);
extern int smem_dump(void);
extern int set_map(unsigned int va,unsigned int pa, unsigned int size, char *name);
extern int del_map(char *name, unsigned int vaddr, unsigned int size);

#ifdef __cplusplus
}
#endif

#endif
