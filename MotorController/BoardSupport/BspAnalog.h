#include "LPC5502.h"

#ifndef BSP_ANALOG_H
#define BSP_ANALOG_H

#if defined (__cplusplus)
class BspAnalog
{
	/* Define Structures */
	public: struct AnalogConfig
	{
		long Offset[10];
		float Gain[10];
	};
	public: struct AnalogInputs
	{
		float Data[10];
	};

	/* Define Variables */
	public:  static AnalogConfig *_config;
	//private: static AnalogInputs *_inputs;
	private: static bool _initialized;
	public:  static bool _channel4;
	public:  static void (*_callback)(void);
	/* Define Functions */
	public:  static void Initialize(void);
	private: static unsigned char Calibrate(void);
	public:  static void SetupAnalogChannel(void);
	public:  static void SetupReadCompleteCallback(void (*callback)(void)) {_callback = callback;}
	public:  static void LinkMemorySpace(AnalogConfig *data){_config = data;}
	public:  static float inline GetAnalogSample() {return (2.0f);}
	private: static void DummyFunction(void);
};
extern "C"
{
	int main(void);
}
#endif

#endif //BSP_ANALOG_H
