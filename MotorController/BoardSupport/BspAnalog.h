#include "LPC5502.h"

#ifndef BSP_ANALOG_H
#define BSP_ANALOG_H

#if defined (__cplusplus)
class BspAnalog
{
	/* Define Structures */
	public: struct AnalogConfig
	{
		long Offset[16];
		float Gain[16];
	};
	public: struct AnalogInputs
	{
		float Data[16];
	};

	/* Define Variables */
	private: static AnalogConfig *_config;
	//private: static AnalogInputs *_inputs;
	private: static bool _initialized;
	/* Define Functions */
	public:  static void Initialize(void);
	public:  static void SetupAnalogChannel(void);
	public:  static void LinkMemorySpace(AnalogConfig *data){_config = data;}
	public:  static float inline GetAnalogSample() {return (2.0f);}
};
extern "C"
{
	int main(void);
}
#endif

#endif //BSP_ANALOG_H
