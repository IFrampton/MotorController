// Motor.h
// Header file for simplified Board support Motor operating logic
// Includes templates for motor programs and inlined functions

#ifndef FCCP_H
#define FCCP_H

#ifdef USE_EXTENDED_ADDRESSES
	#define SUPPORTED_SUBSCRIPTIONS 64 //Not to exceed 255.
	#define SUBSCRIPTION_OFFSET_MASK 0xFFFF
	#define SUBSCRIPTION_BITSHIFT_FACTOR 8
#else
	#define SUPPORTED_SUBSCRIPTIONS 15 // Note: This is limited by teh number of bits available in the response
	#define SUBSCRIPTION_OFFSET_MASK 0xFF
	#define SUBSCRIPTION_BITSHIFT_FACTOR 4
#endif
#define SUPPORTED_SNAPSHOT_CHANNELS 10
//#define VERIFY_SAMPLE_COUNT_BEFORE_TRIGGER

#ifdef __cplusplus
class Fccp
{
	private: enum SupportedPacketHandlers
	{
		Handler_OneTime,
		Handler_Subscribe,
		Handler_Subscribe_Alt,
		Handler_Snapshot,
		NUMBER_OF_HANDLERS
	};
	private: static const unsigned long SnapshotTimeout = 300000;
#ifdef USE_EXTENDED_ADDRESSES
	private: static const unsigned long Id_RequestOneTimeData = 0x3FF70000;
	private: static const unsigned long Id_RequestSubscribedData = 0x3FF80000;
	private: static const unsigned long Id_RequestSnapshotData = 0x3FF90000;
	private: static const unsigned long Id_ResponseOneTimeData = 0x3FF00000;
	private: static const unsigned long Id_ResponseSubscribedData = 0x3FF20000;
	private: static const unsigned long Id_ResponseSnapshotData = 0x3FF30000;
	private: static const bool UseExtended = true;
#else
	private: static const unsigned long Id_RequestOneTimeData = 0x700;
	private: static const unsigned long Id_RequestSubscribedData = 0x701;
	private: static const unsigned long Id_RequestSnapshotData = 0x702;
	private: static const unsigned long Id_ResponseOneTimeData = 0x000;
	private: static const unsigned long Id_ResponseSubscribedData = 0x200;
	private: static const unsigned long Id_ResponseSnapshotData = 0x300;
	private: static const bool UseExtended = false;
#endif
	public: enum DataTypes
	{
		DataType_Bool,
		DataType_Int8,
		DataType_Int16,
		DataType_Int32,
		DataType_Float,
		DataType_Int64,
		DataType_Double,
		DataType_Definition,
		NUM_DATA_TYPES
	};
	private: enum ExtractTypes
	{
		Type_DataType = 0x3F,
		Type_Nvm = 0x40,
		Type_RelativeAddr = 0x80
	};
	private: enum ResponseStatus
	{
		Response_Sts_Success,
		Response_Sts_Fail
	};
	private: enum OneTimeControl
	{
		OneTime_Ctrl_Read,
		OneTime_Ctrl_Write
	};
	private: enum SpecialValues
	{
		Special_SaveIdentifier = 0xAA,
		Special_SaveControl = 0x55,
		Special_SaveType = 0x81,
		Special_SaveCode = 0xC6,
		Special_SaveData = 0xA45BC3E2
	};
	private: struct RequestOneTimeData
	{
		unsigned char Identifier;
		unsigned char Control;
		unsigned char Type;
		unsigned char Code;
		union// OneTimeDataPayload
		{
			struct// Ctrl0_ReadData // Updates the display with the internal data
			{
				unsigned long Address;
			};
			struct// Ctrl1_WriteData // Must be followed by a request with a matching identifier or it is ignored
			{
				unsigned long Data;
			};
		};
	};
	private: struct ResponseOneTimeData
	{
		unsigned char Identifier;
		unsigned char Status;
		unsigned char Type;
		unsigned char Spare;
		unsigned long Data;
	};
	private: struct RequestSubscribedData
	{
		unsigned char Identifier;
		unsigned char Type;
		unsigned short Rate;
		unsigned long Address;
	};
	private: struct ResponseSubscribedData
	{
		unsigned long Data[2];
	};
	private: enum SnapshotPage
	{
		SnapshotPage0_TriggerAddressDefinition,
		SnapshotPage1_TriggerLevelDefinition,
		SnapshotPage2_TriggerFilterDefinition,
		SnapshotPage3_TimeDefinition,
		SnapshotPage4_ChannelDefinition,
		SnapshotPage5_NextDataPoint
	};
	private: enum TriggerType
	{
		TriggerType_RisingEdge,
		TriggerType_FallingEdge
	};
	private: enum SnapshotStatus
	{
		SnapshotStatus_Done = 0x80,
		SnapshotStatus_Retransmit = 0x40
	};
	private: struct RequestSnapshotData
	{
		union// SnapshotDataPayload
		{
			struct// Page0_TriggerDefinition1
			{
				unsigned char Identifier;
				unsigned char Page;
				unsigned char TriggerDataType;
				unsigned char Pad1;
				unsigned long TriggerAddress;
			};
			struct// Page1_TriggerDefinition2
			{
				unsigned char unk1; //Identifier
				unsigned char unk2; //Page
				unsigned char TriggerType;
				unsigned char Pad2;
				float TriggerLevel;
			};
			struct// Page2_TriggerFilterDefinition
			{
				unsigned char unk3; //Identifier
				unsigned char unk4; //Page
				unsigned char Spare1;
				unsigned char Pad3;
				float TriggerFilterTimeConstant;
			};
			struct// Page3_TimeDefinition
			{
				unsigned char unk5; //Identifier
				unsigned char unk6; //Page
				unsigned char ChannelCount;
				unsigned char Pad4;
				unsigned long SamplesBeforeTrigger;
			};
			struct// Page4_ChannelDefinition
			{
				unsigned char unk7; //Identifier
				unsigned char unk8; //Page
				unsigned char Index;
				unsigned char ChannelDataType;
				unsigned long ChannelAddress;
			};
			struct// Page5_NextDataPoint
			{
				unsigned char unk9;  //Identifier
				unsigned char unk10; //Page
				unsigned char PacketNum;
				unsigned char Status;
				unsigned long DataIndex;
			};
		};
	};
	private: struct ResponseSnapshotData
	{
		unsigned long Data[2];
	};
	public: struct CanData
	{
		bool Extended;
		unsigned char Length;
		unsigned long Identifier;
		unsigned long Data[2];
	};
	public:  struct SubscriptionDesc
	{
		unsigned long *Address;
		unsigned short Rate;
		unsigned short Counter;
	};
	public:  struct SnapshotDesc
	{
		unsigned char ConfiguredIdentifier;
		unsigned char TriggerDataType;
		unsigned char *TrigAddress;
		unsigned char TriggerType;
		float TriggerLevel;
		float TriggerFilterTimeConstant;
		unsigned char IntendedChannelCount;
		unsigned long SamplesBeforeTrigger;
		unsigned long ChannelAddress[SUPPORTED_SNAPSHOT_CHANNELS];
		unsigned char ChannelCount;
		unsigned long SamplesToCapture;
		unsigned long UpdateIndex;
		unsigned long TransmitIndex;
		unsigned long DataValidSamples;
		unsigned long NextPacketNum;
		unsigned long NextPacketIndex;
		unsigned long Samples;
		unsigned long TransmitSamples;
		unsigned long ConfigSteps;
		bool (*TriggerHandler)();
		bool Configured;
		bool WasConfigured;
		bool Triggered;
		bool Transmitting;
		bool NextPacketReady;
		bool PrevCondition;
	};
	private: static RequestOneTimeData _lastWrittenData;
	private: static char _rxHandles[NUMBER_OF_HANDLERS];
	private: static char _txHandles[NUMBER_OF_HANDLERS];
	private: static CanData _canData[NUMBER_OF_HANDLERS];
	private: static unsigned long _txData[NUMBER_OF_HANDLERS][2];
	private: static float _dummyVariable;
	//<KLUDGE> These should be private
	public:  static void Initialize();
	private: static bool _forceFlash;
	public:  static void Logic();
	private: static void OneTimePacketHandler();
	private: static SubscriptionDesc _subscriptions[SUPPORTED_SUBSCRIPTIONS];
	private: static unsigned char _subscriptionsToUpdate;
	private: static unsigned short _subscriptionAddressOffset;
	private: static unsigned char _subscribedMessages;
	private: static unsigned char _handlerToggle;
	private: static void SubscribePacketHandler();
	private: static SnapshotDesc _snapshot;
	private: static unsigned char _snapshotId;
	private: static unsigned long _snapshotBuffer[65536];
	private: static unsigned long _timeoutCounter[6];

	private: static void SnapshotPacketHandler();
	public:  static _inline_ void SnapshotHandler()
	{
		// Only deal with snapshot data when a snapshot is actively being captured.
		// This routine runs in the high-speed task, so additional logic hit the processor loading pretty hard.
		if(_snapshot.Configured)
		{
			register unsigned long *snapshotAddress = (unsigned long *)_snapshot.ChannelAddress;
			register unsigned long *snapshotBuffer = _snapshotBuffer;
			register unsigned long ref = _snapshot.UpdateIndex;
			for(char x = _snapshot.ChannelCount; x; x--)
			{
				*(snapshotBuffer + ref++) = *(unsigned long *)*(snapshotAddress++);
				ref &= (sizeof(_snapshotBuffer) / sizeof(unsigned long) - 1);
			}
			// Keep track of the updated index
			_snapshot.UpdateIndex = ref;
			// Prevents overwriting Pre-Trigger Data
			if(_snapshot.Triggered)
			{
				// Configured is removed as soon as enough samples have been captured.
				// Note: _snapshot.Samples starts out at the 'Samples before Trigger'
				// Setting from the interface.
				if(++_snapshot.Samples >= _snapshot.SamplesToCapture)
				{
					_snapshot.Configured = false;
					_snapshot.Transmitting = true;
				}
			}
			else
			{
				// We could verify that the data is valid before proceeding (that we have captured enough data before
				// the trigger event), but this adds a lot of load and very little benefit.
#ifdef VERIFY_SAMPLE_COUNT_BEFORE_TRIGGER
				if(++_snapshot.DataValidSamples > _snapshot.SamplesBeforeTrigger)
				{
#endif
					// The trigger handler is selected when the snapshot is configured. This allows
					// diverse triggers to be processed.
					if(_snapshot.TriggerHandler())
					{
						_snapshot.Triggered = true;
						unsigned long txIdx = _snapshot.UpdateIndex - _snapshot.SamplesBeforeTrigger * _snapshot.ChannelCount;
						txIdx &= (sizeof(_snapshotBuffer) / sizeof(unsigned long) - 1);
						_snapshot.TransmitIndex = txIdx;
					}
#ifdef VERIFY_SAMPLE_COUNT_BEFORE_TRIGGER
				}
#endif
			}
		}
	}
	public:  static bool NullTrigger()
	{
		return false;
	}
	public:  static bool BoolRisingTrigger()
	{
		bool condition = *(bool *)_snapshot.TrigAddress;
		bool trig = condition && !_snapshot.PrevCondition;
		_snapshot.PrevCondition = condition;
		return trig;
	}
	public:  static bool BoolFallingTrigger()
	{
		bool condition = *(bool *)_snapshot.TrigAddress;
		bool trig = !condition && _snapshot.PrevCondition;
		_snapshot.PrevCondition = condition;
		return trig;
	}
	public:  static bool Int8RisingTrigger()
	{
		bool condition = *(char *)_snapshot.TrigAddress >= (*(long *)(&_snapshot.TriggerLevel) & 0xFF);
		bool trig = condition && !_snapshot.PrevCondition;
		_snapshot.PrevCondition = condition;
		return trig;
	}
	public:  static bool Int8FallingTrigger()
	{
		bool condition = *(char *)_snapshot.TrigAddress >= (*(long *)(&_snapshot.TriggerLevel) & 0xFF);
		bool trig = !condition && _snapshot.PrevCondition;
		_snapshot.PrevCondition = condition;
		return trig;
	}
	public:  static bool Int16RisingTrigger()
	{
		bool condition = *(short *)_snapshot.TrigAddress >= (*(long *)(&_snapshot.TriggerLevel) & 0xFFFF);
		bool trig = condition && !_snapshot.PrevCondition;
		_snapshot.PrevCondition = condition;
		return trig;
	}
	public:  static bool Int16FallingTrigger()
	{
		bool condition = *(short *)_snapshot.TrigAddress >= (*(long *)(&_snapshot.TriggerLevel) & 0xFFFF);
		bool trig = !condition && _snapshot.PrevCondition;
		_snapshot.PrevCondition = condition;
		return trig;
	}
	public:  static bool Int32RisingTrigger()
	{
		bool condition = *(long *)_snapshot.TrigAddress >= (*(long *)(&_snapshot.TriggerLevel));
		bool trig = condition && !_snapshot.PrevCondition;
		_snapshot.PrevCondition = condition;
		return trig;
	}
	public:  static bool Int32FallingTrigger()
	{
		bool condition = *(long *)_snapshot.TrigAddress >= (*(long *)(&_snapshot.TriggerLevel));
		bool trig = !condition && _snapshot.PrevCondition;
		_snapshot.PrevCondition = condition;
		return trig;
	}
	public:  static bool FloatRisingTrigger()
	{
		bool condition = *(float *)_snapshot.TrigAddress >= (*(float *)(&_snapshot.TriggerLevel));
		bool trig = condition && !_snapshot.PrevCondition;
		_snapshot.PrevCondition = condition;
		return trig;
	}
	public:  static bool FloatFallingTrigger()
	{
		bool condition = *(float *)_snapshot.TrigAddress >= (*(float *)(&_snapshot.TriggerLevel));
		bool trig = !condition && _snapshot.PrevCondition;
		_snapshot.PrevCondition = condition;
		return trig;
	}

};
#endif

#endif // FCCP_H

