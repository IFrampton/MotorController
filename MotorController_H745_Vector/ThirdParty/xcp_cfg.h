/** @file xcp_cfg.c
 *
 * @brief XCP Protocol Layer configuration.
 */

#if !defined(XCP_CFG_H_)
#define XCP_CFG_H_

#include <stdint.h>

typedef volatile uint8_t  vuint8;
typedef volatile uint16_t vuint16;
typedef volatile uint32_t vuint32;

#define CAN_ID_XCP_RX 0x701U // CAN ID for incoming XCP message
#define CAN_ID_XCP_TX 0x702U // CAN ID for outgoing XCP message
#define CAN_ID_UDS_RX 0x703U // CAN ID for incoming UDS message
#define CAN_ID_UDS_TX 0x704U // CAN ID for outgoing UDS message

/* XCP transport layer */
#define XCP_TRANSPORT_LAYER_VERSION 0x0103
#define kXcpMaxCTO                  8 /* Maximum CTO Message Length */
#define kXcpMaxDTO                  8 /* Maximum DTO Message Length */

/* ROM memory qualifiers */
#define MEMORY_ROM const
#define V_MEMROM0
#define MEMORY_CONST

/* Alignment requirements */
/* Specify, whether the microcontroller allows unaligned memory access or not */
#define XCP_DISABLE_UNALIGNED_MEM_ACCESS

/* General settings */
#define XCP_DISABLE_PARAMETER_CHECK
#define XCP_ENABLE_COMM_MODE_INFO
#define XCP_DISABLE_USER_COMMAND

/* Block transfer */
#define XCP_DISABLE_BLOCK_UPLOAD
#define XCP_DISABLE_BLOCK_DOWNLOAD

/* Enable transmission of event messages */
#define XCP_DISABLE_SEND_EVENT

/* Service request message */
#define XCP_DISABLE_SERV_TEXT
#define XCP_DISABLE_SERV_TEXT_PUTCHAR
#define XCP_DISABLE_SERV_TEXT_PRINT

/* Disable/Enable Interrupts */
/* Has to be defined only if xcpSendCallBack may interrupt xcpEvent */
#define XcpInterruptDisable()
#define XcpInterruptEnable()

/* Custom initialization not needed */
#define ApplXcpInit()

/* Custom background processing not needed */
#define ApplXcpBackground()

/* Flush of transmit queue not needed */
#define ApplXcpSendFlush()

/* Calibration settings */
#define XCP_ENABLE_CALIBRATION

/* XCP page switching */
#define XCP_ENABLE_CALIBRATION_PAGE

/* XCP protocol data acquisition parameters (DAQ) */
#define XCP_ENABLE_DAQ
#define XCP_DISABLE_SEND_QUEUE
#define XCP_DISABLE_SEND_DIRECT
#define XCP_DISABLE_DAQ_HDR_ODT_DAQ
#define kXcpDaqMemSize  3000
#define kXcpStiOdtCount 1
#define XCP_ENABLE_DAQ_PROCESSOR_INFO
#define XCP_ENABLE_DAQ_RESOLUTION_INFO
#define XCP_DISABLE_DAQ_PRESCALER
#define XCP_DISABLE_DAQ_OVERRUN_INDICATION
#define XCP_DISABLE_DAQ_RESUME
#define XCP_DISABLE_DAQ_TIMESTAMP
#define XCP_DISABLE_DAQ_EVENT_INFO
#define XCP_DISABLE_STIM

#define XCP_CPUTYPE_LITTLEENDIAN

/* define here configuration parameters for customizing XcpBasic driver */

#endif /* XCP_CFG_H_ */

/*** end of file ***/
