#ifndef _IOM_SWAP_H
  #define _IOM_SWAP_H

  /*Prototypes*/
  #ifdef __powerpc__
    #define BSWAP(x) bswap(x)
    #define SSWAP(x) sswap(x)
    #define BSWAP_LE(x) (x) 
    #define SSWAP_LE(x) (x) 
    #define MEMCPY_ENDIAN memcpy 
    #define SYNC __asm__("eieio")
  #endif

  #ifdef __i386__
    #define BSWAP(x) (x)
    #define SSWAP(x) (x)
    #define BSWAP_LE(x) bswap(x)
    #define SSWAP_LE(x) sswap(x)
    #define MEMCPY_ENDIAN swap_memcpy 
    #define SYNC 
  #endif

  #ifdef __i960
    #define BSWAP(x) (x)
    #define SSWAP(x) (x)
    #define BSWAP_LE(x) bswap(x)
    #define SSWAP_LE(x) sswap(x)
    #define MEMCPY_ENDIAN xmemcpy 
    #define SYNC
  #endif



  #ifdef __cplusplus
    extern "C" {
  #endif

  extern unsigned int bswap(unsigned int word);
  extern unsigned int sswap(unsigned short word);
  extern void *swap_memcpy (void * s, const void * ct, unsigned int n);

  #ifdef __cplusplus
    }
  #endif

#endif
