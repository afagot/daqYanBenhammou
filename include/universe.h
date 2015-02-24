#ifndef __universe_h
#define __universe_h

/* Full register space of Tundra Universe ASIC */

/* UCSR Registers */
typedef struct {
volatile unsigned int pci_id;				/* 000 */
volatile unsigned int pci_csr;				/* 004 */
volatile unsigned int pci_class;			/* 008 */
volatile unsigned int pci_misc0;			/* 00C */
volatile unsigned int pci_bs;				/* 010 */
volatile unsigned int pci_bs1;				/* 014 */
volatile unsigned int reserved1 [9];			/* 018 - 038 */
volatile unsigned int pci_misc1;			/* 03C */
volatile unsigned int reserved2[48];			/* 040 */
volatile unsigned int lsi0_ctl;		   	        /* 100 */
volatile unsigned int lsi0_bs;	        		/* 104 */
volatile unsigned int lsi0_bd;	        		/* 108 */
volatile unsigned int lsi0_to;	        		/* 10C */
volatile unsigned int reserved3;        		/* 110 */
volatile unsigned int lsi1_ctl;	        	        /* 114 */
volatile unsigned int lsi1_bs;		        	/* 118 */
volatile unsigned int lsi1_bd;		        	/* 11C */
volatile unsigned int lsi1_to;		        	/* 120 */
volatile unsigned int reserved4;	        	/* 124 */
volatile unsigned int lsi2_ctl;	        		/* 128 */
volatile unsigned int lsi2_bs;		        	/* 12C */
volatile unsigned int lsi2_bd;		        	/* 130 */
volatile unsigned int lsi2_to;		        	/* 134 */
volatile unsigned int reserved5;	        	/* 138 */
volatile unsigned int lsi3_ctl;	        		/* 13C */
volatile unsigned int lsi3_bs;		        	/* 140 */
volatile unsigned int lsi3_bd;		        	/* 144 */
volatile unsigned int lsi3_to;		        	/* 148 */
volatile unsigned int reserved6[9];	        	/* 14C-16C */
volatile unsigned int scyc_ctl;				/* 170 */
volatile unsigned int scyc_addr;			/* 174 */
volatile unsigned int scyc_en;				/* 178 */
volatile unsigned int scyc_cmp;				/* 17C */
volatile unsigned int scyc_swp;				/* 180 */
volatile unsigned int lmisc;				/* 184 */
volatile unsigned int slsi;            			/* 188 */
volatile unsigned int l_cmderr;				/* 18C */
volatile unsigned int laerr;				/* 190 */
volatile unsigned int reserved7[3]; 			/* 194-19C */
volatile unsigned int lsi4_ctl;	        		/* 1A0 */
volatile unsigned int lsi4_bs;		        	/* 1A4 */
volatile unsigned int lsi4_bd;		        	/* 1A8 */
volatile unsigned int lsi4_to;		        	/* 1AC */
volatile unsigned int reserved8;	        	/* 1B0 */
volatile unsigned int lsi5_ctl;	        		/* 1B4 */
volatile unsigned int lsi5_bs;		        	/* 1B8 */
volatile unsigned int lsi5_bd;		        	/* 1BC */
volatile unsigned int lsi5_to;		        	/* 1C0 */
volatile unsigned int reserved9;	        	/* 1C4 */
volatile unsigned int lsi6_ctl;	        		/* 1C8 */
volatile unsigned int lsi6_bs;		        	/* 1CC */
volatile unsigned int lsi6_bd;		        	/* 1D0 */
volatile unsigned int lsi6_to;		        	/* 1D4 */
volatile unsigned int reserved10;	        	/* 1D8 */
volatile unsigned int lsi7_ctl;	        		/* 1DC */
volatile unsigned int lsi7_bs;		        	/* 1E0 */
volatile unsigned int lsi7_bd;		        	/* 1E4 */
volatile unsigned int lsi7_to;		        	/* 1E8 */
volatile unsigned int reserved11[5];	        	/* 1EC - 1FC*/
volatile unsigned int dctl;				/* 200 */
volatile unsigned int dtbc;				/* 204 */
volatile unsigned int dla;				/* 208 */
volatile unsigned int reserved12;			/* 20c */
volatile unsigned int dva;				/* 210 */
volatile unsigned int reserved13;			/* 214 */
volatile unsigned int dcpp;				/* 218 */
volatile unsigned int reserved14;			/* 21C */
volatile unsigned int dgcs;				/* 220 */
volatile unsigned int d_llue;				/* 224 */
volatile unsigned int reserved15[(0x300-0x228)/4];	/* 228 - 2FC */
volatile unsigned int lint_en;				/* 300 */
volatile unsigned int lint_stat;			/* 304 */
volatile unsigned int lint_map0;			/* 308 */
volatile unsigned int lint_map1;			/* 30C */
volatile unsigned int vint_en;				/* 310 */
volatile unsigned int vint_stat;			/* 314 */
volatile unsigned int vint_map0;			/* 318 */
volatile unsigned int vint_map1;			/* 31C */
volatile unsigned int statid;				/* 320 */
volatile unsigned int vx_statid[7];			/* 324 - 33C */
volatile unsigned int lint_map2;			/* 340 */
volatile unsigned int vint_map2;			/* 344 */
volatile unsigned int mbox0;				/* 348 */
volatile unsigned int mbox1;				/* 34C */
volatile unsigned int mbox2;				/* 350 */
volatile unsigned int mbox3;				/* 354 */
volatile unsigned int sema0;				/* 358 */
volatile unsigned int sema1;			 	/* 35C */
volatile unsigned int reserved16[(0x400-0x360)/4];      /* 360 - 3FC */
volatile unsigned int mast_ctl;				/* 400 */
volatile unsigned int misc_ctl;				/* 404 */
volatile unsigned int misc_stat;			/* 408 */
volatile unsigned int user_am;				/* 40C */
volatile unsigned int reserved17[(0xf00-0x410)/4];      /* 410 - EFC */
volatile unsigned int vsi0_ctl;				/* F00 */
volatile unsigned int vsi0_bs;				/* F04 */
volatile unsigned int vsi0_bd;				/* F08 */
volatile unsigned int vsi0_to;				/* F0C */
volatile unsigned int reserved18;			/* F10 */
volatile unsigned int vsi1_ctl;				/* F14 */
volatile unsigned int vsi1_bs;				/* F18 */
volatile unsigned int vsi1_bd;				/* F1C */
volatile unsigned int vsi1_to;				/* F20 */
volatile unsigned int reserved19;			/* F24 */
volatile unsigned int vsi2_ctl;				/* F28 */
volatile unsigned int vsi2_bs;				/* F2C */
volatile unsigned int vsi2_bd;				/* F30 */
volatile unsigned int vsi2_to;				/* F34 */
volatile unsigned int reserved20;			/* F38 */
volatile unsigned int vsi3_ctl;				/* F3C */
volatile unsigned int vsi3_bs;				/* F40 */
volatile unsigned int vsi3_bd;				/* F44 */
volatile unsigned int vsi3_to;				/* F48 */
volatile unsigned int reserved21[(0xf64-0xf4c)/4];      /* FC4 - F60 */
volatile unsigned int lm_ctl;				/* F64 */
volatile unsigned int tl_bs;				/* F68 */
volatile unsigned int reserved22;		        /* F6C */
volatile unsigned int vrai_ctl;				/* F70 */
volatile unsigned int vrai_bs;				/* F74 */
volatile unsigned int reserved23[2];                    /* F78 - F7C */
volatile unsigned int vcsr_ctl;                   	/* F80 */
volatile unsigned int vcsr_to;                   	/* F84 */
volatile unsigned int v_amerr;				/* F88 */
volatile unsigned int vaerr;				/* F8C */
volatile unsigned int vsi4_ctl;				/* F90 */
volatile unsigned int vsi4_bs;				/* F94 */
volatile unsigned int vsi4_bd;				/* F98 */
volatile unsigned int vsi4_to;				/* F9C */
volatile unsigned int reserved24;			/* FA0 */
volatile unsigned int vsi5_ctl;				/* FA4 */
volatile unsigned int vsi5_bs;				/* FA8 */
volatile unsigned int vsi5_bd;				/* FAC */
volatile unsigned int vsi5_to;				/* FB0 */
volatile unsigned int reserved25;			/* FB4 */
volatile unsigned int vsi6_ctl;				/* FB8 */
volatile unsigned int vsi6_bs;				/* FBC */
volatile unsigned int vsi6_bd;				/* FC0 */
volatile unsigned int vsi6_to;				/* FC4 */
volatile unsigned int reserved26;			/* FC8 */
volatile unsigned int vsi7_ctl;				/* FCC */
volatile unsigned int vsi7_bs;				/* FD0 */
volatile unsigned int vsi7_bd;				/* FD4 */
volatile unsigned int vsi7_to;				/* FD8 */
volatile unsigned int reserved27[6];     		/* FDC - FF0 */
volatile unsigned int vcsr_clr;                   	/* FF4 */
volatile unsigned int vcsr_set;                   	/* FF8 */
volatile unsigned int vcsr_bs;                   	/* FFC */
}universe_regs_t;

/* Universe II Register Offsets */

#define PCI_ID		0x0000
#define PCI_CSR		0x0004
#define PCI_CLASS	0x0008
#define PCI_MISC0	0x000C
#define PCI_BS0		0x0010
#define PCI_BS1		0x0014
#define PCI_MISC1	0x003C

#define LSI0_CTL	0x0100
#define LSI0_BS		0x0104
#define LSI0_BD		0x0108
#define LSI0_TO		0x010C

#define LSI1_CTL	0x0114
#define LSI1_BS		0x0118
#define LSI1_BD		0x011C
#define LSI1_TO		0x0120
#define LSI2_CTL	0x0128
#define LSI2_BS		0x012C
#define LSI2_BD		0x0130
#define LSI2_TO		0x0134

#define LSI3_CTL	0x013C
#define LSI3_BS		0x0140
#define LSI3_BD		0x0144
#define LSI3_T		O0x0148

#define SCYC_CTL	0x0170
#define SCYC_ADDR	0x0174
#define SCYC_EN		0x0178
#define SCYC_CMP	0x017C
#define SCYC_SWP	0x0180
#define LMISC		0x0184
#define SLSI		0x0188
#define L_CMDERR	0x018C
#define LAERR		0x0190

#define LSI4_CTL	0x01A0
#define LSI4_BS		0x01A4
#define LSI4_BD		0x01A8
#define LSI4_TO		0x01AC

#define LSI5_CTL	0x01B4
#define LSI5_BS		0x01B8
#define LSI5_BD		0x01BC
#define LSI5_TO		0x01C0

#define LSI6_CTL	0x01C8
#define LSI6_BS		0x01CC
#define LSI6_BD		0x01D0
#define LSI6_TO		0x01D4

#define LSI7_CTL	0x01DC
#define LSI7_BS		0x01E0
#define LSI7_BD		0x01E4
#define LSI7_TO		0x01E8

#define DCTL		0x0200
#define DTBC		0x0204
#define DLA		0x0208
#define DVA		0x0210
#define DCPP		0x0218
#define DGCS		0x0220
#define D_LLUE		0x0224

#define LINT_EN		0x0300
#define LINT_STAT       0x0304
#define LINT_MAP0       0x0308
#define LINT_MAP1       0x030C
#define VINT_EN		0x0310
#define VINT_STAT       0x0314
#define VINT_MAP0       0x0318
#define VINT_MAP1       0x031C
#define STATID		0x0320
#define V1_STATID       0x0324
#define V2_STATID       0x0328
#define V3_STATID       0x032C
#define V4_STATID       0x0330
#define V5_STATID       0x0334
#define V6_STATID       0x0338
#define V7_STATID       0x033C

#define LINT_MAP2	0x340
#define VINT_MAP2	0x344
#define MBOX0		0x348
#define MBOX1		0x34C
#define MBOX2		0x350
#define MBOX3		0x354
#define SEMA0		0x358
#define SEMA1		0x35C

#define MAST_CTL	0x0400
#define MISC_CTL	0x0404
#define MISC_STAT	0x0408
#define USER_AM		0x040C

#define VSI0_CTL	0x0F00
#define VSI0_BS		0x0F04
#define VSI0_BD		0x0F08
#define VSI0_TO		0x0F0C

#define VSI1_CTL	0x0F14
#define VSI1_BS		0x0F18
#define VSI1_BD		0x0F1C
#define VSI1_TO		0x0F20

#define VSI2_CT		L0x0F28
#define VSI2_BS		0x0F2C
#define VSI2_BD		0x0F30
#define VSI2_TO		0x0F34

#define VSI3_CTL	0x0F3C
#define VSI3_BS		0x0F40
#define VSI3_BD		0x0F44
#define VSI3_TO		0x0F48

#define LM_CTL		0xF64
#define LM_BS		0xF68

#define VRAI_CTL	0x0F70
#define VRAI_BS		0x0F74
#define VCSR_CTL	0x0F80
#define VCSR_TO		0x0F84
#define V_AMERR		0x0F88
#define VAERR		0x0F8C

#define VSI4_CTL	0x0F90
#define VSI4_BS		0x0F94
#define VSI4_BD		0x0F98
#define VSI4_TO		0x0F9C

#define VSI5_CTL	0x0FA4
#define VSI5_BS		0x0FA8
#define VSI5_BD		0x0FAC
#define VSI5_TO		0x0FB0

#define VSI6_CTL	0x0FB8
#define VSI6_BS		0x0FBC
#define VSI6_BD		0x0FC0
#define VSI6_TO		0x0FC4

#define VSI7_CTL	0x0FCC
#define VSI7_BS		0x0FD0
#define VSI7_BD		0x0FD4
#define VSI7_TO		0x0FD8

#define VCSR_CLR	0x0FF4
#define VCSR_SET	0x0FF8
#define VCSR_BS		0x0FFC

/* Interrupt Control Registers - "borrowed" from the Hannapel driver */
#define BM_LINT_ACFAIL             0x00008000
#define BM_LINT_SYSFAIL            0x00004000
#define BM_LINT_SW_INT             0x00002000
#define BM_LINT_SW_IACK            0x00001000
#define BM_LINT_VERR               0x00000400
#define BM_LINT_LERR               0x00000200
#define BM_LINT_DMA                0x00000100
#define BM_LINT_VIRQ               0x000000FE
#define BM_LINT_VIRQ7              0x00000080
#define BM_LINT_VIRQ6              0x00000040
#define BM_LINT_VIRQ5              0x00000020
#define BM_LINT_VIRQ4              0x00000010
#define BM_LINT_VIRQ3              0x00000008
#define BM_LINT_VIRQ2              0x00000004
#define BM_LINT_VIRQ1              0x00000002
#define BM_LINT_VOWN               0x00000001
#define BM_VX_STATID_STATID        0x000000FF
#define OF_VX_STATID_STATID        0
#define BM_VX_STATID_ERR           0x00000100

#endif /* __universe_h */
