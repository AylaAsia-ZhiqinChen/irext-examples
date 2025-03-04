/**************************************************************************************************
  Filename:       hal_types.h
  Revised:        $Date: 2008-03-20 17:17:05 -0700 (Thu, 20 Mar 2008) $
  Revision:       $Revision: 16618 $

  Description:    Describe the purpose and contents of the file.


  Copyright 2006-2013 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights
  granted under the terms of a software license agreement between the user
  who downloaded the software, his/her employer (which must be your employer)
  and Texas Instruments Incorporated (the "License").  You may not use this
  Software unless you agree to abide by the terms of the License. The License
  limits your use, and you acknowledge, that the Software may not be modified,
  copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio
  frequency transceiver, which is integrated into your product.  Other than for
  the foregoing purpose, you may not use, reproduce, copy, prepare derivative
  works of, modify, distribute, perform, display or sell this Software and/or
  its documentation for any purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
  PROVIDED ``AS IS'' WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
  TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
  INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
  OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
  OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com.
**************************************************************************************************/

#ifndef _HAL_TYPES_H
#define _HAL_TYPES_H

#include <stdint.h>

/* ------------------------------------------------------------------------------------------------
 *                                               Types
 * ------------------------------------------------------------------------------------------------
 */
typedef signed char int8;
typedef unsigned char uint8;

typedef signed short int16;
typedef unsigned short uint16;

typedef signed long int32;
typedef unsigned long uint32;

//typedef unsigned char   bool;

typedef uint32 halDataAlign_t;
#define bool _Bool

/* ------------------------------------------------------------------------------------------------
 *                                        Compiler Macros
 * ------------------------------------------------------------------------------------------------
 */
/* ----------- IAR Compiler ----------- */
#ifdef __IAR_SYSTEMS_ICC__
#define ASM_NOP    asm("NOP")

/* ----------- KEIL Compiler ----------- */
#elif defined __KEIL__
#define ASM_NOP   __nop()

/* ----------- CCS Compiler ----------- */
#elif defined __TI_COMPILER_VERSION || defined __TI_COMPILER_VERSION__
#define ASM_NOP    asm(" NOP")

/* ----------- GNU Compiler ----------- */
#elif defined __GNUC__
#define ASM_NOP __asm__ __volatile__ ("nop")

/* ---------- MSVC compiler ---------- */
#elif _MSC_VER
#define ASM_NOP __asm NOP

/* ----------- Unrecognized Compiler ----------- */
#else
#error "ERROR: Unknown compiler."
#endif


/* ------------------------------------------------------------------------------------------------
 *                                        Standard Defines
 * ------------------------------------------------------------------------------------------------
 */
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL 0L
#endif


/* ------------------------------------------------------------------------------------------------
 *                                       Memory Attributes
 * ------------------------------------------------------------------------------------------------
 */

#if defined (__IAR_SYSTEMS_ICC__)
#define XDATA
#define CODE
#define DATA_ALIGN(x)               _Pragma data_alignment=(x)
#define PACKED                      __packed
#define PACKED_STRUCT               PACKED struct
#define PACKED_TYPEDEF_STRUCT       PACKED typedef struct
#define PACKED_TYPEDEF_CONST_STRUCT PACKED typedef const struct
#define PACKED_TYPEDEF_UNION        PACKED typedef union

#elif defined __TI_COMPILER_VERSION || defined __TI_COMPILER_VERSION__
#define XDATA
#define CODE
#define DATA
#define NEARFUNC
#define PACKED                      __attribute__((__packed__))
#define PACKED_STRUCT               struct PACKED
#define PACKED_TYPEDEF_STRUCT       typedef struct PACKED
#define PACKED_TYPEDEF_CONST_STRUCT typedef const struct PACKED
#define PACKED_TYPEDEF_UNION        typedef union PACKED

#elif defined (__GNUC__)
#define PACKED __attribute__((__packed__))
#endif

/**************************************************************************************************
 */
#endif
