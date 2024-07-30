// SineTable.h
// Header file for Sine Table, used to generate output sine wave for resolver and input to TIM3.
// Includes templates for table and parsing functions

#ifndef SINE_TABLE_H
#define SINE_TABLE_H

//#define STEP_SINE
#define SYNC_SINE_WITH_PWM

#ifdef __cplusplus
class SineTable
{
	private: static float _sineTableFactor;
	private: static float _sineTable[513];
#ifdef STEP_SINE
	private: static unsigned short  _intSineTable[64];
#else
#ifdef SYNC_SINE_WITH_PWM
	private: static unsigned short  _intSineTable[200];
#else
	private: static unsigned short  _intSineTable[256];
#endif
#endif
	private: static float _arcSineTable[362];
	private: static float _arcCosineTable[362];
	public:  static inline float *GetSineTableAddress(void) {return _sineTable;}
	public:  static inline unsigned short  *GetIntSineTableAddress(void) {return &_intSineTable[0];}
	public:  static inline short  GetIntTableLength(void) {return(sizeof(_intSineTable) / sizeof(short));}
	public:  static inline float Sine(float degrees)
	{
		float angle = degrees * _sineTableFactor;
		long index = (long)(angle);
		float rem = angle - float(index);
		index &= (sizeof(_sineTable) / sizeof(float)) - 2;
		float prevSample = _sineTable[index];
		float nextSample = _sineTable[index + 1];
		float sampleDifference = nextSample - prevSample;
		return (prevSample + sampleDifference * rem);
	}
	public:  static inline void Sine_3Phase(float degrees, float *sine)
	{
		float angle = degrees * _sineTableFactor;
		long index = (long)angle;
		float rem = angle - float(index);
		index &= (sizeof(_sineTable) / sizeof(float)) - 2;
		float prevSample = _sineTable[index];
		float nextSample = _sineTable[index + 1];
		float sampleDifference = nextSample - prevSample;
		*sine = prevSample + sampleDifference * rem;
		sine++;
		angle += 120.0f / 360.0f * (sizeof(_sineTable) / sizeof(float) - 1);
		index = (long)angle;
		rem = angle - float(index);
		index &= (sizeof(_sineTable) / sizeof(float)) - 2;
		prevSample = _sineTable[index];
		nextSample = _sineTable[index + 1];
		sampleDifference = nextSample - prevSample;
		*sine = prevSample + sampleDifference * rem;
		sine++;
		angle += 120.0f / 360.0f * (sizeof(_sineTable) / sizeof(float) - 1);
		index = (long)angle;
		rem = angle - float(index);
		index &= (sizeof(_sineTable) / sizeof(float)) - 2;
		prevSample = _sineTable[index];
		nextSample = _sineTable[index + 1];
		sampleDifference = nextSample - prevSample;
		*sine = prevSample + sampleDifference * rem;
	}
	public:  static inline float ArcSine(float amplitude)
	{
		float idx = ((amplitude + 1.0f) * 180.0f);
		long index = (long)idx;
		float rem = idx - (float)index;
		float first = _arcSineTable[index];
		float difference = _arcSineTable[index+1] - first;
		return first + difference * rem;
	}
	public:  static inline float ArcCosine(float amplitude)
	{
		float idx = ((amplitude + 1.0f) * 180.0f);
		long index = (long)idx;
		float rem = idx - (float)index;
		float first = _arcCosineTable[index];
		float difference = _arcCosineTable[index+1] - first;
		return first + difference * rem;
	}
};
#endif

#endif // SINE_TABLE_H

