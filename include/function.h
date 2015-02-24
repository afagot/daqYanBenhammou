#include"CAENVMElib.h"
#include <unistd.h>

#define ERR -1

/*CSR Space.*/
#define OUT_BUFFER_767 0x0000
#define GEO_REG_767    0x0004
#define BIT_SET_767    0x0006
#define BIT_CLR_767    0x0008
#define IRQ_LEVEL_767  0x000A
#define IRQ_VECTOR_767 0x000C
#define STAT_REG1_767  0x000E
#define CTRL_REG1_767  0x0010
#define ADER_32_767    0x0012
#define ADER_24_767    0x0014
#define MCST_ADDR_767  0x0016
#define RESET_767      0x0018
#define MCST_CTRL_767  0x0020

#define STAT_REG2_767  0x0048
#define CTRL_REG2_767  0x004A
#define EVENT_CNT_767  0x004C
#define EVENT_CLR_767  0x004E
#define OP_HAND_767    0x0050
#define OP_REG_767     0x0052
#define CLEAR_767      0x0054
#define TEST_WDH_767   0x0056
#define TEST_WDL_767   0x0058
#define SOFT_TRIG_767  0x005A

/*OP_HAND bits.*/
#define RD_OK_767      0
#define WR_OK_767      1

/* OUT BUFFER */
#define STATUS_TDC              0x00600000
#define HEADER_TDC              0x00400000
#define DATA_TDC                0x00000000
#define EOB_TDC                 0x00200000
#define NOT_VALID_DATA_TDC      0x00600000
                                                  
/*STAT_REG1 bits.*/
/* data ready */
#define DRDY_767                        0x0001
#define NO_DRDY_767                     0x0000

/* busy */
#define BUSY_767                        0x0004
#define NO_BUSY_767                     0x0000

/*STAT_REG2 bits.*/
#define BUFFER_EMPTY_767                0x0001
#define NO_BUFFER_EMPTY_767             0x0000
#define BUFFER_FULL_767                 0x0002
#define NO_BUFFER_FULL_767              0x0000
#define BUFFER_ALMOST_FULL_767          0x0004
#define NO_BUFFER_ALMOST_FULL_767       0x0000
#define NO_TDC_ERR0R                    0x0000

/*CR Space.*/
#define MANU_ID_767    0x1026
#define BOARD_ID_767   0x1032
#define REV_ID_767     0x104E
#define SLAVE_PAR_767  0x10E2
#define IRQ_CAP_767    0x1026
#define FN0_DAW_767    0x1102
#define FN1_DAW_767    0x1106
#define FN0_AMCM_767   0x1122
#define FN1_AMCM_767   0x1142
#define FN0_ADCM_767   0x1622
#define FN1_ADCM_767   0x1632
#define SERIAL_767     0x1F02        

typedef unsigned char Uchar;
typedef Uchar    Data8;

typedef unsigned short Ushort;
typedef Ushort    Data16;
typedef Ushort    Word16;

typedef unsigned int Uint;
typedef Uint    Data32;
typedef Uint    Word32;
                                   
Data16 write_op_reg(long ,unsigned long ,CVAddressModifier , CVDataWidth ,Data16 );
Data16 read_op_reg(long ,unsigned long ,CVAddressModifier , CVDataWidth );
void delay(int msec);

