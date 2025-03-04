//******************************************************************************
//! \file           npi_tl_uart.h
//! \brief          NPI Transport Layer Module for UART
//
//   Revised        $Date: 2015-07-20 15:51:01 -0700 (Mon, 20 Jul 2015) $
//   Revision:      $Revision: 44375 $
//
//  Copyright 2015 Texas Instruments Incorporated. All rights reserved.
//
// IMPORTANT: Your use of this Software is limited to those specific rights
// granted under the terms of a software license agreement between the user
// who downloaded the software, his/her employer (which must be your employer)
// and Texas Instruments Incorporated (the "License").  You may not use this
// Software unless you agree to abide by the terms of the License. The License
// limits your use, and you acknowledge, that the Software may not be modified,
// copied or distributed unless used solely and exclusively in conjunction with
// a Texas Instruments radio frequency device, which is integrated into
// your product.  Other than for the foregoing purpose, you may not use,
// reproduce, copy, prepare derivative works of, modify, distribute, perform,
// display or sell this Software and/or its documentation for any purpose.
//
//  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
//  PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,l
//  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
//  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
//  TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
//  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
//  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
//  INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
//  OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
//  OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
//  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
//
//  Should you have any questions regarding your right to use this Software,
//  contact Texas Instruments Incorporated at www.TI.com.
//******************************************************************************
#ifndef NPI_TL_UART_H
#define NPI_TL_UART_H

#ifdef __cplusplus
extern "C"
{
#endif

// ****************************************************************************
// includes
// ****************************************************************************
#include "_hal_types.h"

// ****************************************************************************
// defines
// ****************************************************************************

#define NPI_UART_FC_THRESHOLD 48
#define NPI_UART_IDLE_TIMEOUT 6
#define NPI_UART_INT_ENABLE TRUE

#if !defined(NPI_UART_BR)
#define NPI_UART_BR 115200
#endif // !NPI_UART_BR

// UART ISR Buffer define
#define UART_ISR_BUF_SIZE 32
#define UART_ISR_BUF_CNT 2
  
// ****************************************************************************
// typedefs
// ****************************************************************************
// typedef unsigned short uint16;


  // -----------------------------------------------------------------------------
//! \brief      Typedef for call back function mechanism to notify NPI TL that
//!             an NPI transaction has occurred
//! \param[in]  uint16     number of bytes received
//! \param[in]  uint16     number of bytes transmitted      
//!
//! \return     void
// ----------------------------------------------------------------------------- 
typedef void (*npiCB_t)(uint16 Rxlen, uint16 Txlen);

//*****************************************************************************
// globals
//*****************************************************************************

//*****************************************************************************
// function prototypes
//*****************************************************************************

// -----------------------------------------------------------------------------
//! \brief      This routine initializes the transport layer and opens the port
//!             of the device.
//!
//! \param[in]  tRxBuf - pointer to NPI TL Tx Buffer
//! \param[in]  tTxBuf - pointer to NPI TL Rx Buffer
//! \param[in]  npiCBack - NPI TL call back function to be invoked at the end of 
//!             a UART transaction                     
//!
//! \return     void
// -----------------------------------------------------------------------------
void NPITLUART_initializeTransport(char *tRxBuf, char *tTxBuf, npiCB_t npiCBack);

// -----------------------------------------------------------------------------
//! \brief      This routine reads data from the UART
//!
//! \return     void
// -----------------------------------------------------------------------------
void NPITLUART_readTransport(void);

// -----------------------------------------------------------------------------
//! \brief      This routine writes copies buffer addr to the transport layer.
//!
//! \param[in]  len - Number of bytes to write.
//!
//! \return     uint16 - number of bytes written to transport
// -----------------------------------------------------------------------------
uint16 NPITLUART_writeTransport(uint16);

// -----------------------------------------------------------------------------
//! \brief      This routine stops any pending reads
//!
//! \return     void
// -----------------------------------------------------------------------------
void NPITLUART_stopTransfer(void);

// -----------------------------------------------------------------------------
//! \brief      This routine is called from the application context when MRDY is
//!             de-asserted
//!
//! \return     void
// -----------------------------------------------------------------------------
void NPITLUART_handleMrdyEvent(void);



#ifdef __cplusplus
}
#endif

#endif /* NPI_TL_UART_H */
