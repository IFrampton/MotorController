#include "BspDma.h"

unsigned char BspDma::_nextChannel = 0;
alignas(512) unsigned long BspDma::_descriptorTable[4][4];
bool BspDma::_initialized = false;

void BspDma::Initialize(void)
{
	// Enable clocks
	SYSCON->SYSAHBCLKCTRL |= (1 << 8); // Enable Clock to SCT
	SYSCON->SYSAHBCLKCTRL |= (1 << 29); // Enable Clock to DMA
	// Clear the Reset input for the SCT
	SYSCON->PRESETCTRL |= (1 << 8);
	// Setup DMA
	DMA0->CTRL = (1 << 0); // Enable DMA Controller
	DMA0->SRAMBASE = (unsigned long)_descriptorTable[0];
	// Update Initialized Status for other function calls
	_initialized = true;
}

void BspDma::SetupReceiveFromPeripheral(DmaChannelData *data, unsigned char channel, unsigned char pri, unsigned char *source, unsigned char *dest, unsigned char dataBytes, unsigned char length, bool reArm)
{
	if(!_initialized)
		return;
	pri &= 0x7;
	channel &= 0x3;
	// dataBytes: 0 = 1, 1 = 2, 2 = 4
	if(dataBytes > 3)
		dataBytes = 3;
	dataBytes--;
	DMA0->COMMON[0].ENABLESET = (1 << channel);

	DMA0->CHANNEL[channel].CFG = (pri << 16)	|	// CHPRIORITY = ? (Priority is set by the function caller)
								 (0 << 15)		|	// DSTBURSTWRAP = 0 (No burst wrap for destination)
								 (0 << 14)		|	// SRCBURSTWRAP = 0 (No burst wrap for source)
								 (0 << 8)		|	// BURSTPOWER = 0 (execute a single transfer / trigger)
								 (0 << 6)		|	// TRIGBURST = 0 (Execute a single transfer / trigger)
								 (0 << 5)		|	// TRIGTYPE = 0 (Edge triggered (momentary))
								 (1 << 4)		|	// TRIGPOL = 1 (rising edge trigger)
								 (0 << 1)		|	// HWTRIGEN = 0 (Disable Hardware triggers)
								 (1 << 0)		;	// PERIPHREQEN = 1 (Enable Peripheral requests)
	unsigned long xferConfig =   ((length-1) << 16)	|	// XFERCOUNT = ? (Transfer Length is set by the function caller)
								 (1 << 14)		|	// DSTINC = 1 (The destination address is incremented by 1 each time)
								 (0 << 12)		|	// SRCINC = 0 (The source address is not incremented each time (always points to the peripheral))
								 (dataBytes << 8)|	// WIDTH = ? (The transfer width (data type) is set by the function caller)
								 (0 << 5)		|	// SETINTB = 0 (Do not set interrupt B)
								 (0 << 4)		|	// SETINTA = 0 (Do not set interrupt A)
								 (1 << 3)		|	// CLRTRIG = 1 (Clear Trigger when this descriptor is exhausted)
								 (1 << 2)		|	// SWTRIG = 0 (Do not trigger in software)
								 (reArm << 1)	|	// RELOAD = 1 (Reload the channel structure when complete)
								 (1 << 0)		;	// CFGVALID = 1 (The Configuration is Valid)

	_descriptorTable[channel][1] = (unsigned long)source;
	_descriptorTable[channel][2] = (unsigned long)dest;

	DMA0->CHANNEL[channel].XFERCFG = xferConfig;
	DMA0->COMMON[0].SETVALID = (1 << channel);

	if(data == 0)
		return;
	data->Location = ((unsigned long *)&DMA0->CHANNEL[channel].XFERCFG);
	data->Data = xferConfig;
	_nextChannel++;
}

void BspDma::InitiateTransferToPeripheral(DmaChannelData *data, unsigned char channel, unsigned char pri, unsigned char *source, unsigned char *dest, unsigned char dataBytes, unsigned char length, bool reArm)
{
	if(!_initialized)
		return;
	pri &= 0x7;
	channel &= 0x3;
	// dataBytes: 0 = 1, 1 = 2, 2 = 4
	if(dataBytes > 3)
		dataBytes = 3;
	dataBytes--;
	DMA0->COMMON[0].ENABLESET = (1 << channel);

	DMA0->CHANNEL[channel].CFG = (pri << 16)	|	// CHPRIORITY = ? (Priority is set by the function caller)
								 (0 << 15)		|	// DSTBURSTWRAP = 0 (No burst wrap for destination)
								 (0 << 14)		|	// SRCBURSTWRAP = 0 (No burst wrap for source)
								 (0 << 8)		|	// BURSTPOWER = 0 (execute a single transfer / trigger)
								 (0 << 6)		|	// TRIGBURST = 0 (Execute a single transfer / trigger)
								 (0 << 5)		|	// TRIGTYPE = 0 (Edge triggered (momentary))
								 (1 << 4)		|	// TRIGPOL = 1 (rising edge trigger)
								 (0 << 1)		|	// HWTRIGEN = 0 (Disable Hardware triggers)
								 (1 << 0)		;	// PERIPHREQEN = 1 (Enable Peripheral requests)
	unsigned long xferConfig =   ((length - 1) << 16)	|	// XFERCOUNT = ? (Transfer Length is set by the function caller)
								 (0 << 14)		|	// DSTINC = 1 (The destination address is not incremented each time (always points to the peripheral))
								 (1 << 12)		|	// SRCINC = 0 (The source address is incremented by 1 each time)
								 (dataBytes << 8)|	// WIDTH = ? (The transfer width (data type) is set by the function caller)
								 (0 << 5)		|	// SETINTB = 0 (Do not set interrupt B)
								 (0 << 4)		|	// SETINTA = 0 (Do not set interrupt A)
								 (1 << 3)		|	// CLRTRIG = 1 (Clear Trigger when this descriptor is exhausted)
								 (1 << 2)		|	// SWTRIG = 0 (Do not trigger in software)
								 (reArm << 1)	|	// RELOAD = 1 (Reload the channel structure when complete)
								 (1 << 0)		;	// CFGVALID = 1 (The Configuration is Valid)

	_descriptorTable[channel][1] = (unsigned long)source;
	_descriptorTable[channel][2] = (unsigned long)dest;

	DMA0->CHANNEL[channel].XFERCFG = xferConfig;
	DMA0->COMMON[0].SETVALID = (1 << channel);

	if(data == 0)
		return;
	data->Location = ((unsigned long *)&DMA0->CHANNEL[channel].XFERCFG);
	data->Data = xferConfig;
	_nextChannel++;
}

void BspDma::LinkAdditionalTransferToPeripheral(DmaChannelData *data, unsigned char channel, unsigned char pri, unsigned char *source, unsigned char *dest, unsigned char dataBytes, unsigned char length, bool reArm)
{
	if(!_initialized)
		return;
	pri &= 0x7;
	channel &= 0x3;
	if(_nextChannel >= sizeof(_descriptorTable) / (4 * sizeof(long)))
		return;
	// dataBytes: 0 = 1, 1 = 2, 2 = 4
	if(dataBytes > 3)
		dataBytes = 3;
	dataBytes--;
	// No need to reconfigure the channel, just change xferConfig
	unsigned long oldXferConfig = (DMA0->CHANNEL[channel].XFERCFG &	// Modify the existing configuration
													   ~(1 << 3)) |	// Turn off the clear for the trigger
														 (1 << 2) |	// Enable the software trigger (which is usually removed)
														 (1 << 1) ;	// Enable the automatic reload to call the second transfer
	unsigned long xferConfig =   ((length - 1) << 16)	|	// XFERCOUNT = ? (Transfer Length is set by the function caller)
								 (0 << 14)		|	// DSTINC = 1 (The destination address is not incremented each time (always points to the peripheral))
								 (1 << 12)		|	// SRCINC = 0 (The source address is incremented by 1 each time)
								 (dataBytes << 8)|	// WIDTH = ? (The transfer width (data type) is set by the function caller)
								 (0 << 5)		|	// SETINTB = 0 (Do not set interrupt B)
								 (0 << 4)		|	// SETINTA = 0 (Do not set interrupt A)
								 (1 << 3)		|	// CLRTRIG = 1 (Clear Trigger when this descriptor is exhausted)
								 (1 << 2)		|	// SWTRIG = 0 (Do not trigger in software)
								 (reArm << 1)	|	// RELOAD = ? (Reload the channel structure when complete)
								 (1 << 0)		;	// CFGVALID = 1 (The Configuration is Valid)

	_descriptorTable[channel][0] = (unsigned long)oldXferConfig;
	_descriptorTable[channel][3] = (unsigned long)&_descriptorTable[_nextChannel][0];
	_descriptorTable[_nextChannel][0] = (unsigned long)xferConfig;
	_descriptorTable[_nextChannel][1] = (unsigned long)source;
	_descriptorTable[_nextChannel][2] = (unsigned long)dest;
	_descriptorTable[_nextChannel][3] = (unsigned long)&_descriptorTable[channel][0];

	DMA0->CHANNEL[channel].XFERCFG = xferConfig;
	DMA0->COMMON[0].SETVALID = (1 << channel);

	if(data == 0)
		return;
	data->Location = ((unsigned long *)&DMA0->CHANNEL[channel].XFERCFG);
	data->Data = oldXferConfig;
	_nextChannel++;
}
