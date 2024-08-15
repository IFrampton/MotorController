#include "DataMan.h"
#include "BspCan.h"
#include "Fccp.h"

Fccp::RequestOneTimeData Fccp::_lastWrittenData;
Fccp::CanData Fccp::_canData[NUMBER_OF_HANDLERS];
char Fccp::_rxHandles[NUMBER_OF_HANDLERS];
char Fccp::_txHandles[NUMBER_OF_HANDLERS];
unsigned long Fccp::_txData[NUMBER_OF_HANDLERS][2] = {{0,0},{0,0},{0,0}};
float Fccp::_dummyVariable = -345.67f;

void Fccp::Initialize()
{
	// Make sure that no variables are accidentally written
	_lastWrittenData.Control = OneTime_Ctrl_Read;
	_rxHandles[Handler_OneTime] = BspCan::Subscribe(Id_RequestOneTimeData, UseExtended);
	_txHandles[Handler_OneTime] = BspCan::GetTxHandle();
	_rxHandles[Handler_Subscribe] = BspCan::Subscribe(Id_RequestSubscribedData, UseExtended);
	_txHandles[Handler_Subscribe] = BspCan::GetTxHandle();
	_rxHandles[Handler_Snapshot] = BspCan::Subscribe(Id_RequestSnapshotData, UseExtended);
	_txHandles[Handler_Snapshot] = BspCan::GetTxHandle();

	// Set the rate to a very large number for channels that we don't want to transmit.
	for(long x = 0; x < SUPPORTED_SUBSCRIPTIONS; x++)
	{
		_subscriptions[x].Rate = 0xFFFF;
	}

	for(long x = 0; x < SUPPORTED_SNAPSHOT_CHANNELS; x++)
	{
		_snapshot.ChannelAddress[x] = (unsigned long)(&_dummyVariable);
	}
}

bool Fccp::_forceFlash = false;

// Handles the main loop for the FCCP protocol.
void Fccp::Logic()
{
	OneTimePacketHandler();
	SubscribePacketHandler();
	SnapshotPacketHandler();
	//<KLUDGE> This allows testing of writing feature without a functional interface
	if(_forceFlash)
	{
		_forceFlash = false;
		DataMan::SaveToNonVolatile();
	}
}

void Fccp::OneTimePacketHandler()
{
	if(BspCan::CheckForNewData(_rxHandles[Handler_OneTime]))
	{
		BspCan::GetData(_rxHandles[Handler_OneTime], &_canData[Handler_OneTime].Identifier, &_canData[Handler_OneTime].Length, _canData[Handler_OneTime].Data, &_canData[Handler_OneTime].Extended);
		if(_canData[Handler_OneTime].Length == 8)
		{
			register RequestOneTimeData *data = (RequestOneTimeData *)&_canData[Handler_OneTime].Data;
			// First, check if this is a read or write request
			if(data->Control == OneTime_Ctrl_Write)
			{
				register unsigned long *source = (unsigned long *)_canData[Handler_OneTime].Data;
				register unsigned long *dest = (unsigned long *)&_lastWrittenData;
				*(dest++) = *(source++);
				*(dest++) = *(source++);
			}
			else
			{
				// Does this read request match the immediately preceding write request?
				// If so, write the previously-received data to the address defined in the packet
				if((data->Identifier == _lastWrittenData.Identifier) && (_lastWrittenData.Control == OneTime_Ctrl_Write) && (_lastWrittenData.Type == data->Type))
				{
					DataMan::WriteData(data->Address, data->Type & Type_DataType, data->Type & Type_Nvm, data->Type & Type_RelativeAddr, _lastWrittenData.Data);
				}
				// If the transaction was not a write, check for the 'save' flag.
				else
				{
					// Save requires a special message (unlikely to occur under normal circumstances).
					if((data->Identifier == Special_SaveIdentifier) &&
						(data->Control == Special_SaveControl) &&
						(data->Type == Special_SaveType) &&
						(data->Code == Special_SaveCode) &&
						(data->Data == Special_SaveData))
					{
						DataMan::SaveToNonVolatile();
					}

				}
				// Don't accidentally trigger again
				_lastWrittenData.Control = OneTime_Ctrl_Read;
				register ResponseOneTimeData *resp = (ResponseOneTimeData *)&_txData[Handler_OneTime];
				resp->Identifier = data->Identifier;
				resp->Status = Response_Sts_Success;
				resp->Type = data->Type;
				resp->Spare = data->Code;
				resp->Data = DataMan::GetData(data->Address, data->Type & Type_DataType, data->Type & Type_Nvm, data->Type & Type_RelativeAddr);
				// Send Response
				BspCan::Transmit(_txHandles[Handler_OneTime], Id_ResponseOneTimeData, &_txData[Handler_OneTime][0], 8, false);
			}
		}
	}
}

Fccp::SubscriptionDesc Fccp::_subscriptions[SUPPORTED_SUBSCRIPTIONS];
unsigned char Fccp::_subscribedMessages = 0;
unsigned char Fccp::_subscriptionsToUpdate = 0;
unsigned short Fccp::_subscriptionAddressOffset = 0;
unsigned char Fccp::_handlerToggle = 0;

void Fccp::SubscribePacketHandler()
{
	if(BspCan::CheckForNewData(_rxHandles[Handler_Subscribe]))
	{
		BspCan::GetData(_rxHandles[Handler_Subscribe], &_canData[Handler_Subscribe].Identifier, &_canData[Handler_Subscribe].Length, _canData[Handler_Subscribe].Data, &_canData[Handler_Subscribe].Extended);
		if(_canData[Handler_Subscribe].Length == 8)
		{
			register RequestSubscribedData *data = (RequestSubscribedData *)&_canData[Handler_Subscribe].Data;
			// prevent excessive or invalid subscriptions
			if((data->Identifier > SUPPORTED_SUBSCRIPTIONS) || (data->Identifier <= 0))
			{
				return;
			}
			// Note: While subscription 0 is valid internally, it is not valid on the bus.
			// It is passed on the bus as subscription 1
			data->Identifier--;
			// Note: Make sure that address boundaries are respected.
			_subscriptions[data->Identifier].Address = (unsigned long *)(unsigned long)DataMan::GetAddress(data->Address, data->Type & Type_DataType, data->Type & Type_Nvm, data->Type & Type_RelativeAddr);
			_subscriptions[data->Identifier].Rate = data->Rate;
			_subscriptions[data->Identifier].Counter = 0;
		}
	}
	// Handler toggles between Handler_Subscribe and Handler_Subscribe_Alt each time to give more chance for
	// each message to send (this allows operation with the CAN bus closer to 100%.
	_handlerToggle++;
	_handlerToggle &= 0x1;
	unsigned char handlerIndex = Handler_Subscribe + _handlerToggle;
	_subscriptionsToUpdate = 0;
	_subscriptionAddressOffset = 0;
	for(short x = 0; x < SUPPORTED_SUBSCRIPTIONS; x++)
	{
		// Will not time out if rate is set to max.
		if(++_subscriptions[x].Counter > _subscriptions[x].Rate)
		{
			// Note: While subscription 0 is valid internally, it is not valid on the bus.
			// It is passed on the bus as subscription 1
			if(_subscriptionsToUpdate < 2)
			{
				// Only Reset Counter if data was sent
				_subscriptions[x].Counter = 1;
				_subscriptionAddressOffset += ((x+1) << (_subscriptionsToUpdate * SUBSCRIPTION_BITSHIFT_FACTOR));
				_txData[handlerIndex][_subscriptionsToUpdate] = *_subscriptions[x].Address;
				_subscriptionsToUpdate++;
			}
		}
	}
	if(_subscriptionsToUpdate > 0)
	{
		// Send Response
		// Note: Subscription 0 is not supported.
		BspCan::Transmit(_txHandles[handlerIndex], Id_ResponseSubscribedData + (_subscriptionAddressOffset & SUBSCRIPTION_OFFSET_MASK), &_txData[handlerIndex][0], 8, false);
	}
}

Fccp::SnapshotDesc Fccp::_snapshot;
unsigned char Fccp::_snapshotId = 0;
unsigned long Fccp::_snapshotBuffer[65536];
unsigned long Fccp::_timeoutCounter[6] = {0,0,0,0,0,0};

void Fccp::SnapshotPacketHandler()
{
	if(BspCan::CheckForNewData(_rxHandles[Handler_Snapshot]))
	{
		BspCan::GetData(_rxHandles[Handler_Snapshot], &_canData[Handler_Snapshot].Identifier, &_canData[Handler_Snapshot].Length, _canData[Handler_Snapshot].Data, &_canData[Handler_Snapshot].Extended);
		if(_canData[Handler_Snapshot].Length == 8)
		{
			register RequestSnapshotData *data = (RequestSnapshotData *)&_canData[Handler_Snapshot].Data;
			// prevent excessive or invalid subscriptions
			switch(data->Page)
			{
				case SnapshotPage0_TriggerAddressDefinition:
				{
					// If a previous snapshot has already been triggered, don't interrupt it to start a new one.
					if(!_snapshot.Triggered && !_snapshot.Transmitting)
					{
						// This message will restart the configuration;
						_snapshot.Configured = false;
						_snapshot.ConfigSteps = 0; // None of the packets have been received
						_snapshot.ChannelCount = 0; // No Channels have been configured
						_snapshot.ConfiguredIdentifier = data->Identifier; // This is now the snapshot being configured
						switch(data->TriggerDataType)
						{
							case DataType_Bool:
							{
								_snapshot.TriggerDataType = DataType_Bool;
								// Note: The GetAddress Function is always 32-bit aligned. The trigger may not be.
								unsigned long address = (unsigned long)DataMan::GetAddress(data->TriggerAddress, data->TriggerDataType & Type_DataType, data->TriggerDataType & Type_Nvm, data->TriggerDataType & Type_RelativeAddr);
								// Retrieve additional Address data;
								address += data->TriggerAddress & 0x3;
								_snapshot.TrigAddress = (unsigned char *)address;
								break;
							}
							case DataType_Int8:
							{
								_snapshot.TriggerDataType = DataType_Int8;
								// Note: The GetAddress Function is always 32-bit aligned. The trigger may not be.
								unsigned long address = (unsigned long)DataMan::GetAddress(data->TriggerAddress, data->TriggerDataType & Type_DataType, data->TriggerDataType & Type_Nvm, data->TriggerDataType & Type_RelativeAddr);
								// Retrieve additional Address data;
								address += data->TriggerAddress & 0x3;
								_snapshot.TrigAddress = (unsigned char *)address;
								break;
							}
							case DataType_Int16:
							{
								_snapshot.TriggerDataType = DataType_Int16;
								// Note: The GetAddress Function is always 32-bit aligned. The trigger may not be.
								unsigned long address = (unsigned long)DataMan::GetAddress(data->TriggerAddress, data->TriggerDataType & Type_DataType, data->TriggerDataType & Type_Nvm, data->TriggerDataType & Type_RelativeAddr);
								// Retrieve additional Address data;
								address += data->TriggerAddress & 0x2;
								_snapshot.TrigAddress = (unsigned char *)address;
								break;
							}
							case DataType_Int32:
							{
								_snapshot.TriggerDataType = DataType_Int32;
								_snapshot.TrigAddress = (unsigned char *)DataMan::GetAddress(data->TriggerAddress, data->TriggerDataType & Type_DataType, data->TriggerDataType & Type_Nvm, data->TriggerDataType & Type_RelativeAddr);
								break;
							}
							case DataType_Float:
							default:
							{
								_snapshot.TriggerDataType = DataType_Float;
								_snapshot.TrigAddress = (unsigned char *)DataMan::GetAddress(data->TriggerAddress, data->TriggerDataType & Type_DataType, data->TriggerDataType & Type_Nvm, data->TriggerDataType & Type_RelativeAddr);
								break;
							}
						}
						// Page 0 has been received
						_snapshot.ConfigSteps |= (1 << 0);
					}
					break;
				}
				case SnapshotPage1_TriggerLevelDefinition:
				{
					// Make sure that this is to configure the same snapshot that has previously been started with
					// page 0. if not, don't do anything (the interface is doing something weird
					if((data->Identifier == _snapshot.ConfiguredIdentifier) && !_snapshot.Configured)
					{
						switch(_snapshot.TriggerDataType)
						{
							case DataType_Bool:
							{
								switch(data->TriggerType)
								{
									case TriggerType_RisingEdge:
									default:
									{
										_snapshot.TriggerHandler = BoolRisingTrigger;
										break;
									}
									case TriggerType_FallingEdge:
									{
										_snapshot.TriggerHandler = BoolFallingTrigger;
										break;
									}
								}
								// This is not used for Boolean, but copy it anyway
								_snapshot.FloatTriggerLevel = data->TriggerLevel;
								break;
							}
							case DataType_Int8:
							{
								switch(data->TriggerType)
								{
									case TriggerType_RisingEdge:
									default:
									{
										_snapshot.TriggerHandler = Int8RisingTrigger;
										break;
									}
									case TriggerType_FallingEdge:
									{
										_snapshot.TriggerHandler = Int8FallingTrigger;
										break;
									}
								}
								_snapshot.FloatTriggerLevel = data->TriggerLevel;
								break;
							}
							case DataType_Int16:
							{
								switch(data->TriggerType)
								{
									case TriggerType_RisingEdge:
									default:
									{
										_snapshot.TriggerHandler = Int16RisingTrigger;
										break;
									}
									case TriggerType_FallingEdge:
									{
										_snapshot.TriggerHandler = Int16FallingTrigger;
										break;
									}
								}
								_snapshot.FloatTriggerLevel = data->TriggerLevel;
								break;
							}
							case DataType_Int32:
							{
								switch(data->TriggerType)
								{
									case TriggerType_RisingEdge:
									default:
									{
										_snapshot.TriggerHandler = Int32RisingTrigger;
										break;
									}
									case TriggerType_FallingEdge:
									{
										_snapshot.TriggerHandler = Int32FallingTrigger;
										break;
									}
								}
								_snapshot.FloatTriggerLevel = data->TriggerLevel;
								break;
							}
							case DataType_Float:
							default:
							{
								switch(data->TriggerType)
								{
									case TriggerType_RisingEdge:
									default:
									{
										_snapshot.TriggerHandler = FloatRisingTrigger;
										break;
									}
									case TriggerType_FallingEdge:
									{
										_snapshot.TriggerHandler = FloatFallingTrigger;
										break;
									}
								}
								_snapshot.FloatTriggerLevel = data->TriggerLevel;
								break;
							}
						}
						// Page 1 has been received
						_snapshot.ConfigSteps |= (1 << 1);
						// All pages have been received and all Channels configured
						_snapshot.Configured = (_snapshot.ConfigSteps == 0x1F) && (_snapshot.ChannelCount == _snapshot.IntendedChannelCount);
					}
					break;
				}
				case SnapshotPage2_TriggerFilterDefinition:
				{
					// Make sure that this is to configure the same snapshot that has previously been started with
					// page 0. if not, don't do anything (the interface is doing something weird
					if((data->Identifier == _snapshot.ConfiguredIdentifier) && !_snapshot.Configured)
					{
						// there is an unused byte in this packet, which could indicate the filter type or something.
						//_snapshot.TriggerFilterType = data->Spare1;
						_snapshot.TriggerFilterTimeConstant = data->TriggerFilterTimeConstant;
						// Page 2 has been received
						_snapshot.ConfigSteps |= (1 << 2);
						// All pages have been received and all Channels configured
						_snapshot.Configured = (_snapshot.ConfigSteps == 0x1F) && (_snapshot.ChannelCount == _snapshot.IntendedChannelCount);
					}
					break;
				}
				case SnapshotPage3_TimeDefinition:
				{
					// Make sure that this is to configure the same snapshot that has previously been started with
					// page 0. if not, don't do anything (the interface is doing something weird
					if((data->Identifier == _snapshot.ConfiguredIdentifier) && !_snapshot.Configured)
					{
						_snapshot.IntendedChannelCount = data->ChannelCount;
						// Determine how many samples to capture
						if(data->ChannelCount > 0)
						{
							_snapshot.SamplesToCapture = (sizeof(_snapshotBuffer)/sizeof(unsigned long)) / data->ChannelCount;
						}
						else
						{
							_snapshot.SamplesToCapture = (sizeof(_snapshotBuffer) / sizeof(unsigned long));
						}
						// The snapshot is constantly rolling over. There is no way to capture more samples before the trigger
						// than what are stored in the buffer.
						if(data->SamplesBeforeTrigger >= _snapshot.SamplesToCapture)
						{
							_snapshot.SamplesBeforeTrigger = _snapshot.SamplesToCapture;
							_snapshot.Samples = _snapshot.SamplesToCapture;
						}
						else
						{
							_snapshot.SamplesBeforeTrigger = data->SamplesBeforeTrigger;
							_snapshot.Samples = data->SamplesBeforeTrigger;
						}

						// Page 3 has been received
						_snapshot.ConfigSteps |= (1 << 3);
						// All pages have been received and all Channels configured
						_snapshot.Configured = (_snapshot.ConfigSteps == 0x1F) && (_snapshot.ChannelCount == _snapshot.IntendedChannelCount);
					}
					break;
				}
				case SnapshotPage4_ChannelDefinition:
				{
					// Make sure that this is to configure the same snapshot that has previously been started with
					// page 0. if not, don't do anything (the interface is doing something weird
					if((data->Identifier == _snapshot.ConfiguredIdentifier) && !_snapshot.Configured)
					{
						// This makes sure that a channel setup packet wasn't dropped and prevents
						// subscribing to too many channels
						if(data->PacketNum == _snapshot.ChannelCount)
						{
							_snapshot.ChannelAddress[_snapshot.ChannelCount] = (unsigned long)DataMan::GetAddress(data->ChannelAddress, data->ChannelDataType & Type_DataType, data->ChannelDataType & Type_Nvm, data->ChannelDataType & Type_RelativeAddr);
							if(_snapshot.ChannelCount < SUPPORTED_SNAPSHOT_CHANNELS - 1)
							{
								_snapshot.ChannelCount++;
							}
						}
						else
						{
							// Should probably send an error here
						}
						// Page 4 has been received
						_snapshot.ConfigSteps |= (1 << 4);
						// All pages have been received and all Channels configured
						_snapshot.Configured = (_snapshot.ConfigSteps == 0x1F) && (_snapshot.ChannelCount == _snapshot.IntendedChannelCount);
					}
					break;
				}
				case SnapshotPage5_NextDataPoint:
				{
					if(_snapshot.Transmitting)
					{
						// Don't check if packet number has incremented of if index has changed. This is used for validation
						// on the interface side and it may need to re-request a packet.
						if((data->Status & SnapshotStatus_Done))
						{
							_snapshot.Transmitting = false;
							_snapshot.Triggered = false;
						}
						else
						{
							_snapshot.NextPacketReady = true;
							_snapshot.NextPacketNum = data->PacketNum;
							_snapshot.NextPacketIndex = data->DataIndex;
						}
					}
					break;
				}
				default:
				{
					// If the page doesn't match, there is no point in doing anything
					// TODO: Maybe adding an error here?
					break;
				}
			}
			// Reset Samples for validity check (makes sure that enough samples have been logged in the buffer before
			// enabling the trigger).
			if(_snapshot.Configured && !_snapshot.WasConfigured)
			{
				_snapshot.DataValidSamples = 0;
			}
			_snapshot.WasConfigured = _snapshot.Configured;
		}
	}
	// No messages are being requested. Give up adter a while and revert to listening for another snapshot
	if(_snapshot.Transmitting)
	{
		_timeoutCounter[0]++;
		if(++_timeoutCounter[0] >= SnapshotTimeout)
		{
			_timeoutCounter[0] = 0;
			_snapshot.NextPacketReady = false;
			_snapshot.Triggered = false;
			_snapshot.Transmitting = false;
		}
	}
	// Catch the end of the data Capture and send the first packet so the interface knows it is ready.
	if(!_snapshot.Configured && _snapshot.WasConfigured)
	{
		_snapshot.NextPacketReady = true;
		_snapshot.NextPacketIndex = 0;
		_snapshot.NextPacketNum = _snapshot.ConfiguredIdentifier;
		_snapshot.WasConfigured = _snapshot.Configured;
	}
	if(_snapshot.NextPacketReady)
	{
		_snapshot.NextPacketReady = false;
		unsigned long index = _snapshot.NextPacketIndex + _snapshot.TransmitIndex;
		index &= (sizeof(_snapshotBuffer) / sizeof(unsigned long) - 1);
		_txData[Handler_Snapshot][0] = _snapshotBuffer[index];
		index++;
		index &= (sizeof(_snapshotBuffer) / sizeof(unsigned long) - 1);
		_txData[Handler_Snapshot][1] = _snapshotBuffer[index];
		// Requested Packet Number is part of the response identifier
		BspCan::Transmit(_txHandles[Handler_Snapshot], Id_ResponseSnapshotData + _snapshot.NextPacketNum, &_txData[Handler_Snapshot][0], 8, false);
		_timeoutCounter[0] = 0;
	}
}


