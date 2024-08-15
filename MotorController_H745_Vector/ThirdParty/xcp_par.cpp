/** @file xcp_par.c
 *
 * @brief XCP Transport Layer implementation.
 */

#include "xcp_par.h"
#include "XcpBasic.h"
//#include "can.h"
#include "BspCan.h"

unsigned char _xcpTxCanHandle = 0;
unsigned char _xcpRxCanHandle = 0;
unsigned char _xcpLen = 0;
bool _xcpExt = false;
unsigned long _xcpId = 0;
unsigned long _xcpData[2] = {0, 0};

void DoNothing()
{
}

void InitializeXcp()
{
	_xcpTxCanHandle = BspCan::GetTxHandle();
	_xcpRxCanHandle = BspCan::Subscribe(CAN_ID_XCP_RX, false);
	XcpInit();
}

void Xcp_10ms_Tick()
{
	if(BspCan::CheckForNewData(_xcpRxCanHandle))
	{
		BspCan::GetData(_xcpRxCanHandle, &_xcpId, &_xcpLen, _xcpData, &_xcpExt);
		XcpCommand((const volatile long unsigned int *)_xcpData);
	}
	// Call Internal event if necessary
	//if(XcpStimEventStatus(0))
	//{
		XcpEvent(0);
	//}
}



/**
 * @brief Request for the transmission of a DTO or CTO message.
 * @param[in] len length of message data
 * @param[in] msg pointer to message
 */
void ApplXcpSend(vuint8 len, const BYTEPTR msg)
{
//    can_msg_t tx_msg;
//
//    for (uint8_t byte = 0U; byte < 8U; byte++)
//    {
//        tx_msg.payload[byte] = (byte < len) ? msg[byte] : 0U;
//    }

//    tx_msg.length = len;
//    can_tx_msg(CAN_ID_XCP_TX, tx_msg);
	BspCan::Transmit(_xcpTxCanHandle, CAN_ID_XCP_TX, (unsigned long *)msg, 8, false);
    XcpSendCallBack();
}

/**
 * @brief Pointer conversion.
 * @param[in] addr_ext 8-bit address extension
 * @param[in] addr 32-bit address
 * @return Pointer to the address specified by the parameters
 */
MTABYTEPTR ApplXcpGetPointer(__attribute__((unused)) vuint8 addr_ext,
                             vuint32                        addr)
{
    return (MTABYTEPTR)addr;
}

/**
 * @brief Get calibration page.
 * @param[in] segment logical data segment number
 * @param[in] mode access mode
 * @return Logical data page number
 */
vuint8 ApplXcpGetCalPage(__attribute__((unused)) vuint8 segment,
                         __attribute__((unused)) vuint8 mode)
{
    return 0U;
}

/**
 * @brief Set calibration page.
 * @param[in] segment logical data segment number
 * @param[in] page logical data page number
 * @param[in] mode access mode
 * @return Return code
 */
vuint8 ApplXcpSetCalPage(vuint8 segment, vuint8 page,
                         __attribute__((unused)) vuint8 mode)
{
    vuint8 return_code = 0U;

    if (page != 0U)
    {
        return_code = CRC_PAGE_NOT_VALID;
    }
    if (segment != 0U)
    {
        return_code = CRC_OUT_OF_RANGE;
    }

    return return_code;
}

/*** end of file ***/
