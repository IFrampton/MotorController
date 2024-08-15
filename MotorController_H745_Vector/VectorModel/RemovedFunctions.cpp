// RemovedFunctions.c
// Contains definitions for model functions that are not used in the code due to impracticality, inefficiency,
// poor functionality, or myopic architecture design.

extern "C"
{
#include "P2319ASW01.h"
}
#include "DataMan.h"

extern "C"
{

// For Now, support this heinous kluge

/* Exported block signals */
real32_T PhaUA;                        /* '<Root>/LowPassFilter5'
                                        * Phase A voltage
                                        */
real32_T PhaUB;                        /* '<Root>/LowPassFilter6'
                                        * Phase B voltage
                                        */
real32_T PhaUC;                        /* '<Root>/LowPassFilter7'
                                        * Phase C voltage
                                        */

void ADCINP(void)
{
	if (ResolverSinCosDialEna_C)
	{
		ResolverSinCos[0] = ResolverSinCosDialVal_CA[0];
		ResolverSinCos[1] = ResolverSinCosDialVal_CA[1];
	}
	else
	{
		ResolverSinCos[0] = DataMan::_variables.AnalogIn.Motor.Feedback[0];
		ResolverSinCos[1] = DataMan::_variables.AnalogIn.Motor.Feedback[1];
	}
	if (HvBusUDialEna_C)
	{
		HvBusU = HvBusUDialVal_C;
	}
	else
	{
		HvBusU = DataMan::_variables.AnalogIn.Motor.BusVoltage;
	}

	if (PhaCurADialEna_C)
	{
		PhaCurA = PhaCurADialVal_C;
	}
	else
	{
		PhaCurA = DataMan::_variables.AnalogIn.Motor.Current[0];
	}

	if (PhaCurBDialEna_C)
	{
		PhaCurB = PhaCurBDialVal_C;
	}
	else
	{
		PhaCurB = DataMan::_variables.AnalogIn.Motor.Current[1];
	}

	if (PhaCurCDialEna_C)
	{
		PhaCurC = PhaCurCDialVal_C;
	}
	else
	{
		PhaCurC = DataMan::_variables.AnalogIn.Motor.Current[2];
	}

	if (HvBusCurDialEna_C)
	{
		HvBusCur = HvBusCurDialVal_C;
	}
	else
	{
		HvBusCur = DataMan::_variables.AnalogIn.Motor.BusCurrent;
	}

	PhaUA = DataMan::_variables.AnalogOut.Motor.Voltage[0];
	PhaUB = DataMan::_variables.AnalogOut.Motor.Voltage[1];
	PhaUC = DataMan::_variables.AnalogOut.Motor.Voltage[2];
}

void POSINP(const DRIVEMODE *rtu_DrvMod, const int16_T *rtu_MotSpdReqCan, const
            real32_T rtu_ResolverSinCos[2])
{
	if (MotPosnMagDialEna_C)
	{
		MotPosnMag = MotPosnMagDialVal_C;
	}
	else
	{
	    MotPosnMag = DataMan::_variables.AnalogOut.Motor.Phase;
	}

	if (MotSpdDialEna_C)
	{
		MotSpd = MotSpdDialVal_C;
	}
	else
	{
	    MotSpd = (unsigned short)(DataMan::_variables.AnalogOut.Motor.MotorSpeed * 10.0f);
	}

	if (MotSpdMagDialEna_C)
	{
		MotSpdMag = MotSpdMagDialVal_C;
	}
	else
	{
	    MotSpdMag = (unsigned short)(DataMan::_variables.AnalogOut.Motor.MotorSpeed * 10.0f * DataMan::_config.Analog->Motor.FrequencyToSpeedFactor);
	}
}

void POSTRG(const real32_T *rtu_MotPosnMag)
{
	if (MotPosnTrigDialEna_C)
	{
	    for (short i = 0; i < 6; i++)
	    {
	    	MotPosnTrig[i] = MotPosnTrigDialVal_CA[i];
	    }
	}
	else
	{
	    for (short i = 0; i < 6; i++)
	    {
	    	MotPosnTrig[i] = DataMan::_variables.AnalogOut.Motor.Point[i];
	    }
	}
}

void CLAPAR(const real32_T *rtu_PhaCurA, const real32_T *rtu_PhaCurB, const
            real32_T *rtu_PhaCurC, const real32_T rtu_MotPosnTrig[6])
{
	if (PhaCurDDialEna_C)
	{
		PhaCurD = PhaCurDDialVal_C;
	}
	else
	{
		PhaCurD = DataMan::_variables.AnalogOut.Motor.ReactiveCurrent;
	}

	if (PhaCurQDialEna_C)
	{
		PhaCurQ = PhaCurQDialVal_C;
	}
	else
	{
		PhaCurQ = DataMan::_variables.AnalogOut.Motor.RealCurrent;
	}
}

#ifdef OVERRIDE_GATOUP_DISASTER
void GATOUP(const real32_T *rtu_PhaUACmd, const real32_T *rtu_PhaUBCmd, const
            real32_T *rtu_PhaUCCmd, const real32_T *rtu_HvBusU)
{
	if (PhaAPwmDcDialEna_C)
	{
	    ASWOUT_PhaAPwmDc = PhaAPwmDcDialVal_C;
	}
	else
	{
	    ASWOUT_PhaAPwmDc = DataMan::_variables.AnalogOut.Motor.PWM[0] >> 1;
	}

	if (PhaBPwmDcDialEna_C)
	{
		ASWOUT_PhaBPwmDc = PhaBPwmDcDialVal_C;
	}
	else
	{
	    ASWOUT_PhaBPwmDc = DataMan::_variables.AnalogOut.Motor.PWM[1] >> 1;
	}

	if (PhaCPwmDcDialEna_C)
	{
		ASWOUT_PhaCPwmDc = PhaCPwmDcDialVal_C;
	}
	else
	{
		ASWOUT_PhaCPwmDc = DataMan::_variables.AnalogOut.Motor.PWM[2] >> 1;
	}
}
#endif


void ADCINP_initialize()
{
}

void POSINP_Init()
{
}

void POSINP_initialize()
{
}

void POSTRG_initialize()
{
}

void CLAPAR_initialize()
{
}
}
