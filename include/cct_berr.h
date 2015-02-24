/************************************************************************/
/*                                                                      */
/* File: cct_berr.h                                                     */
/*                                                                      */
/* VME bus error register for VP PMC/C1x and VP CPI/Pxx boards          */
/* "borrowed" from the CCT driver                                       */
/*                                                                      */
/*  29. Nov. 01  MAJO  created                                          */
/*                                                                      */
/************ C 2001 - The software with that certain something *********/

#define BERR_INT_PORT           0x212
#define BERR_INT_ENABLE         0x10
#define BERR_INT_MASK           0x20
#define BERR_VP100              0x213
