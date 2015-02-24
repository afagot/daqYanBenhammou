/************************************************************************/
/*									*/
/* File: vme_rcc_driver.h						*/
/*									*/
/* This is the private header file for RCC VMEbus driver		*/
/*									*/
/* 26. Oct. 01  MAJO  created						*/
/* 02. Nov. 01  JOP   interrupts					*/
/* 26. Nov. 01  JOP   bus errors					*/
/* 17. Apr. 02  JOP   RORA						*/
/*									*/
/************ C 2001 - The software with that certain something *********/

#ifndef _VME_RCC_DRIVER_H 
#define _VME_RCC_DRIVER_H

#include <linux/types.h>
#include "vme_rcc_common.h"
#include "vme_rcc_ioctl.h"

#define VME_VCTSIZE      256
#define VME_DMADONESIZE  64  //max. number of completed DMA transactions

// I/O registers
#define CMOSA            0x70
#define CMOSD            0x71
#define BID1             0x35
#define BID2             0x36

/******************/
/*Type definitions*/
/******************/
typedef struct 
{
  u_int vbase;
  u_int vtop;
  u_int pbase;
  u_int ptop;
  u_int am;   
  u_int enab; 
  u_int wp;   
  u_int rp;   
  u_int space;
} mstslvmap_t;

typedef struct 
{
  mstslvmap_t master[8];
  mstslvmap_t slave[8]; 
} all_mstslvmap_t;  

//  a link between an interrupt and a program is described by a LINK DESCRIPTOR

typedef struct
{
  int                 pid;            // pid of linked process, 0 if not linked 
  u_int               vct;            // vector #
  u_int               lvl;            // level
  u_int               type;           // type
  u_int               pending;        // interrupt pending 
  u_int               total_count;    // total # interrupts with this vector (after LINK)
  VME_IntHandle_t*    group_ptr;      // pointer to the structure of vectors with same handle 
  struct semaphore    sem;            // its semaphore
  int                 sig;            // its signal
} link_dsc_t;

typedef struct
{
  link_dsc_t    	link_dsc[VME_VCTSIZE];
  struct semaphore      link_dsc_sem;
} link_dsc_table_t;

//  a link between BERR and a program is described by a BERR LINK DESCRIPTOR

typedef struct
{
  int                 pid;            // pid of linked process, 0 if not linked 
  int                 sig;            // its signal
} berr_link_dsc_t;

typedef struct
{
  berr_link_dsc_t 	berr_link_dsc[VME_MAX_BERR_PROCS];
  struct semaphore      proc_sem;
} berr_proc_table_t;

// holds info about the bus errors - filled by the BERR ISR
typedef struct
{
  u_int    vmeadd;            // last latched VMEbus address 
  u_int    am;                // and its AM code
  u_int    lword;             // Only for VP-100
  u_int    ds0;               // Only for VP-100
  u_int    ds1;               // Only for VP-100
  u_int    wr;                // Only for VP-100
  int	   multiple;
  int      count;
} berr_dsc_t;
 
typedef struct InterruptCounters_t {
  unsigned int acfail;
  unsigned int sysfail;
  unsigned int sw_int;
  unsigned int sw_iack;
  unsigned int verr;
  unsigned int lerr;
  unsigned int dma;
  unsigned int virq[7];
  unsigned int vown;
} InterruptCounters_t;
 
/********/
/*Macros*/
/********/
#ifdef VMERCC_DEBUG
  #define kdebug(x) printk x
#else
  #define kdebug(x)
#endif


/******************************/
/*Standard function prototypes*/
/******************************/
static int vme_rcc_open(struct inode *ino, struct file *filep);
static int vme_rcc_release(struct inode *ino, struct file *filep);
static int vme_rcc_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg);
static int vme_rcc_mmap(struct file *file, struct vm_area_struct *vma);
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,3,0)
  static int vme_rcc_table_read(char *buf, char **start, off_t offset, int len, int unused);
#endif
int init_module(void);
void cleanup_module(void);
static void vme_rcc_vmaClose(struct vm_area_struct *vma);

/*****************************/
/*Special function prototypes*/
/*****************************/
static int init_universe(void);
static int cleanup_universe(void);
static int berr_check(u_int *addr, u_int *multi, u_int *am);
static void fill_mstmap(u_int d1, u_int d2, u_int d3, u_int d4, mstslvmap_t *mstslvmap);
static void fill_slvmap(u_int d1, u_int d2, u_int d3, u_int d4, mstslvmap_t *mstslvmap);
static void vme_dmaTimeout(unsigned long arg);
static void vme_intTimeout(unsigned long arg);
static void vme_dma_handler(void);
static void vme_irq_handler(int level);
static void universe_irq_handler (int irq, void *dev_id, struct pt_regs *regs);
static void init_cct_berr(void);
static void mask_cct_berr(void);
static int cct_berrInt(void);
static void read_berr_capture(void);

#endif
