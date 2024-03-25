// SineTable.h
// Header file for Sine Table, used to generate output sine wave for resolver and input to TIM3.
// Includes templates for table and parsing functions

#ifndef SINE_TABLE_H
#define SINE_TABLE_H

#ifdef __cplusplus
class SineTable
{
	private: static float _sineTableFactor;
	private: static float _sineTable[513];
	private: static long  _intSineTable[63];
	public:  static inline float *GetSineTableAddress(void) {return _sineTable;}
	public:  static inline long  *GetIntSineTableAddress(void) {return _intSineTable;}
	public:  static inline long  GetIntTableLength(void) {return(sizeof(_intSineTable) / sizeof(long));}
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
		angle += 120.0f / 360.0f * sizeof(_sineTable) / sizeof(float);
		index = (long)angle;
		rem = angle - float(index);
		index &= (sizeof(_sineTable) / sizeof(float)) - 2;
		prevSample = _sineTable[index];
		nextSample = _sineTable[index + 1];
		sampleDifference = nextSample - prevSample;
		*sine = prevSample + sampleDifference * rem;
		sine++;
		angle += 120.0f / 360.0f * sizeof(_sineTable) / sizeof(float);
		index = (long)angle;
		rem = angle - float(index);
		index &= (sizeof(_sineTable) / sizeof(float)) - 2;
		prevSample = _sineTable[index];
		nextSample = _sineTable[index + 1];
		sampleDifference = nextSample - prevSample;
		*sine = prevSample + sampleDifference * rem;
	}
};
#endif

#endif // SINE_TABLE_H

