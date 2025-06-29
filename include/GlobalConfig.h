/******************************************************************************
 ** COPYRIGHT:           Rudi Bauer
 ** DESCRIPTION:    	 Global Conbfiguration
 ** DATE CREATED:        25.12.2022
  ******************************************************************************/

#ifndef GLOBALCONFIG_H
#define GLOBALCONFIG_H

/******************************************************************************
*   TYPE DEFINITIONS
******************************************************************************/
/* Standard types */
typedef unsigned char       u8;             /* unsigned byte */
typedef signed char         s8;             /* signed byte */
typedef unsigned short int  u16;            /* unsigned 2 byte-word */
typedef signed short int    s16;            /* signed 2 byte-word */
typedef unsigned long int   u32;            /* unsigned 4 byte-word */
typedef signed long int     s32;            /* signed 4 byte-word */

/* Bitfields */
typedef unsigned char       bitfield8;      /* for 1 byte-bitfield */
typedef unsigned short int  bitfield16;     /* for 2 byte-bitfield */
typedef unsigned long  int  bitfield32;     /* for 4 byte-bitfield */


/******************************************************************************
*   DEFINES AND MACROS
******************************************************************************/
#define U8_MIN ((u8) 0U)
#define U8_MAX ((u8) 0xFFU)                  /* 255 */

#define S8_MIN ((s8) 0x80)                   /* -128 */
#define S8_MAX ((s8) 0x7F)                   /*  127 */

#define U16_MIN ((u16) 0U)
#define U16_MAX ((u16) 0xFFFFU)              /* 65535 */

#define S16_MIN ((s16)  0x8000)              /* -32768 */
#define S16_MAX ((s16)  0x7FFF)              /*  32767  */

#define U32_MIN ((u32) 0UL)
#define U32_MAX ((u32) 0xFFFFFFFFUL)         /* 4294967295 */

#define S32_MIN ((s32) 0x80000000L)          /* -2147483648  */
#define S32_MAX ((s32) 0x7FFFFFFFL)          /*  2147483647  */

#define TRUE   1
#define FALSE  0

#define ON   1
#define OFF  0

#define NULL_PTR ((void *) 0)

// Error Codes
#define ERRCODE_NONE			0
#define ERRCODE_NO_TIME			1
#define ERRCODE_DHT_NO_DATA	2

// Debug config
#define USE_SERIAL_DEBUG TRUE
#define ENABLE_AVR_DEBUG FALSE

/******************************************************************************
*   EXTERN VARIABLES AND CONSTANTS DECLARATIONS
******************************************************************************/
extern char programVersion[];
extern u8 errorCode;

#endif /* GLOBALCONFIG_H */
