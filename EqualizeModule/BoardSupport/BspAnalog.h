#include "LPC822.h"

#ifndef BSP_ANALOG_H
#define BSP_ANALOG_H

#define AVERAGE_SAMPLES

#if defined (__cplusplus)
class BspAnalog
{
	/* Define Structures */
	public: struct AnalogConfig
	{
		long Offset[4];
		long Gain[4];
		unsigned char BitShift[4];
	};
	public: struct AnalogInputs
	{
		unsigned short RawData[4];
		long Data[4];
	};

	/* Define Variables */
	public:  static AnalogConfig *_config;
	//private: static AnalogInputs *_inputs;
	public:  static unsigned short _analogData[4][4];
	public:  static unsigned char _dataIndex;
	private: static bool _initialized;
	public:  static bool _channel4;
	public:  static void (*_callback)(void);
	/* Define Functions */
	public:  static void Initialize(void);
	private: static unsigned char Calibrate(void);
	public:  static void SetupAnalogChannel(void);
	public:  static void SetupReadCompleteCallback(void (*callback)(void)) {_callback = callback;}
	public:  static void LinkMemorySpace(AnalogConfig *data){_config = data;}
	public:  static long inline GetAnalogSample() {return (2);}
	public:  static void UpdateAnalog(void);
	private: static void DummyFunction(void);
};
extern "C"
{
	int main(void);
}
#endif

#endif //BSP_ANALOG_H
