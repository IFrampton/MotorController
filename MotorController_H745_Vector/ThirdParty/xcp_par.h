/** @file xcp_par.h
 *
 * @brief XCP Transport Layer implementation.
 */

#ifndef XCP_PAR_H_
#define XCP_PAR_H_

#include <stdint.h>
#include "cmsis_gcc.h"
#include "xcp_cfg.h"

//#define ApplXcpInterruptEnable  __enable_irq
//#define ApplXcpInterruptDisable __disable_irq

#define ApplXcpInterruptEnable DoNothing
#define ApplXcpInterruptDisable DoNothing


#if !defined(BYTEPTR)
#define BYTEPTR vuint8 *
#endif

#if !defined(MTABYTEPTR)
#define MTABYTEPTR vuint8 *
#endif

#if defined(__cplusplus)
void 	   InitializeXcp();
void	   Xcp_10ms_Tick();
extern "C"
{
#endif

void	   DoNothing();
void       ApplXcpSend(vuint8 len, const BYTEPTR msg);
MTABYTEPTR ApplXcpGetPointer(vuint8 addr_ext, vuint32 addr);
vuint8     ApplXcpGetCalPage(vuint8 segment, vuint8 mode);
vuint8     ApplXcpSetCalPage(vuint8 segment, vuint8 page, vuint8 mode);

#if defined(__cplusplus)
}
#endif

#endif /* XCP_PAR_H_ */

/*** end of file ***/
