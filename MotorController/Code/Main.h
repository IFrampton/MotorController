#ifndef MAIN_H
#define MAIN_H

#if defined (__cplusplus)
class Main
{
	/* Enumerated Type Definitions */
	enum DigitalOutputs
	{
		GREEN_LED,
		RED_LED,
		BLUE_LED,
		TOTAL_OUTPUTS
	};
	/* Variable Declarations */
	private: static unsigned char _digitalLeds[TOTAL_OUTPUTS];
	private: static long _counterValueOnLastUpdate;
	private: static unsigned long _idleTaskCounter;
	private: static long _updatePeriod;
	private: static unsigned long _periodCounter;
	private: static unsigned long _timePeriod;
	private: static unsigned char _ledTracker;
	private: static unsigned long _pwm[12];
	private: static bool _writeToFlash;
	/* Function Declarations */
	public:  static void InitialBootup(void);
	private: static void IdleTask(unsigned long slowTimerFrequency);
	private: static void ToggleLed(void);
	private: static void CheckToWrite(void);
	private: static void HighPriTimer(void);
	private: static void PwmUpdate(void);
};
extern "C"
{
	int main(void);
}
#endif

#endif //MAIN_H
