// BspAnalog.h
// Header file for simplified Board support Analog features.
// Includes templates for Analog functions and inlined functions

#ifndef VECTORCONTROL_H
#define VECTORCONTROL_H
#include "stm32h7xx.h"
#ifdef __cplusplus
extern "C"
{
#endif
#include "P2319ASW01.h"
#ifdef __cplusplus
}
#endif

extern unsigned long _calDataSize;

#ifdef __cplusplus
class VectorControl
{
	public: static const long SamplesToAverage = 1;
	public: static const long ExternalSamplesToAverage = 10;

	public: struct VectorConfig
	{
		//unsigned char VectorData[_calDataSize];
		/* Calibration memory section */
		/* Definition for custom storage class: Calibration */
		real32_T AuxPwrAcvDebFall_C;/* Referenced by: '<S16>/Model' */

		/* Falling edge debounce time for input processing */
		real32_T AuxPwrAcvDebRisng_C;/* Referenced by: '<S16>/Model' */

		/* Rising edge debounce time for input processing */
		boolean_T AuxPwrAcvDialEna_C;/* Referenced by: '<S16>/Model' */

		/* Signal override enable */
		boolean_T AuxPwrAcvDialVal_C;/* Referenced by: '<S16>/Model' */

		/* Signal override value */
		boolean_T AuxPwrStsIvt_C;/* Referenced by: '<S16>/Model' */

		/* Invert the auxilary power status input */
		boolean_T BdT1DialEna_C;/* Referenced by: '<S16>/Model' */

		/* Signal override enable */
		real32_T BdT1DialVal_C;/* Referenced by: '<S16>/Model' */

		/* Signal override value */
		real32_T BdT1FilTiCon_C;/* Referenced by: '<S16>/Model' */

		/* Low pass filter time constant for signal input processing */
		real32_T BdT1Gain_C;/* Referenced by: '<S16>/Model' */

		/* Gain to convert raw input to engineering units */
		real32_T BdT1Ofs_C;/* Referenced by: '<S16>/Model' */

		/* Offset to convert raw input to engineering units */
		boolean_T BdT2DialEna_C;/* Referenced by: '<S16>/Model' */

		/* Signal override enable */
		real32_T BdT2DialVal_C;/* Referenced by: '<S16>/Model' */

		/* Signal override value */
		real32_T BdT2FilTiCon_C;/* Referenced by: '<S16>/Model' */

		/* Low pass filter time constant for signal input processing */
		real32_T BdT2Gain_C;/* Referenced by: '<S16>/Model' */

		/* Gain to convert raw input to engineering units */
		real32_T BdT2Ofs_C;/* Referenced by: '<S16>/Model' */

		/* Offset to convert raw input to engineering units */
		boolean_T CanPwrPwmEna_C;/* Referenced by: '<S17>/Model' */

		/* Enable CanPwr modulation output: 0 = disable, 1 = enable. */
		boolean_T DrvModDialEna_C;/* Referenced by: '<S15>/Model' */

		/* Signal override enable */
		DRIVEMODE DrvModDialVal_C;/* Referenced by: '<S15>/Model' */

		/* Signal override value */
		DRIVEMODE DrvModReqDft_C;/* Referenced by: '<S18>/Model' */

		/* The default value used for this signal when the message has timedout */
		boolean_T DrvModReqDialEna_C;/* Referenced by: '<S18>/Model' */

		/* Signal override enable */
		DRIVEMODE DrvModReqDialVal_C;/* Referenced by: '<S18>/Model' */

		/* Signal override value */
		uint16_T EncoderCtPerRev_C;/* Referenced by: '<S13>/Model' */

		/* The number of encoder counts per mechanical revolution */
		real32_T EncoderOfs_C;/* Referenced by: '<S13>/Model' */

		/* Offset used to align the encoder z signal with the true zero angle */
		real32_T FluxLinkage_C;/* Referenced by: '<S10>/Model' */

		/* The permanent magnet flux linkage of the motor */
		boolean_T GreenLedDialEna_C;/* Referenced by: '<S17>/Model' */

		/* Signal override enable */
		boolean_T GreenLedDialVal_C;/* Referenced by: '<S17>/Model' */

		/* Signal override value */
		boolean_T GreenLedIvt_C;/* Referenced by: '<S17>/Model' */

		/* Invert the LED command */
		boolean_T HvBusCurDialEna_C;/* Referenced by: '<S8>/Model' */

		/* Signal override enable */
		real32_T HvBusCurDialVal_C;/* Referenced by: '<S8>/Model' */

		/* Signal override value */
		real32_T HvBusCurFilTiCon_C;/* Referenced by: '<S8>/Model' */

		/* Low pass filter time constant for signal input processing */
		real32_T HvBusCurGain_C;/* Referenced by: '<S8>/Model' */

		/* Gain to convert raw input to engineering units */
		real32_T HvBusCurOfs_C;/* Referenced by: '<S8>/Model' */

		/* Offset to convert raw input to engineering units */
		boolean_T HvBusUDialEna_C;/* Referenced by: '<S8>/Model' */

		/* Signal override enable */
		real32_T HvBusUDialVal_C;/* Referenced by: '<S8>/Model' */

		/* Signal override value */
		real32_T HvBusUFilTiCon_C;/* Referenced by: '<S8>/Model' */

		/* Low pass filter time constant for signal input processing */
		real32_T HvBusUGain_C;/* Referenced by: '<S8>/Model' */

		/* Gain to convert raw input to engineering units */
		real32_T HvBusUOfs_C;/* Referenced by: '<S8>/Model' */

		/* Offset to convert raw input to engineering units */
		boolean_T InPwrPwmEna_C;/* Referenced by: '<S17>/Model' */

		/* Enable InPwr modulation output: 0 = disable, 1 = enable. */
		real32_T LedOffTi_C;/* Referenced by: '<S17>/Model' */

		/* The time the LED is off between pulse groups */
		uint8_T LedPlsCtDft_C;/* Referenced by: '<S17>/Model' */

		/* The number of on pulses for the LED while in this mode */
		uint8_T LedPlsCtOpenLoop_C;/* Referenced by: '<S17>/Model' */

		/* The number of on pulses for the LED while in this mode */
		uint8_T LedPlsCtSpdCtl_C;/* Referenced by: '<S17>/Model' */

		/* The number of on pulses for the LED while in this mode */
		uint8_T LedPlsCtTqCtl_C;/* Referenced by: '<S17>/Model' */

		/* The number of on pulses for the LED while in this mode */
		real32_T MaiPwrAcvDebFall_C;/* Referenced by: '<S16>/Model' */

		/* Falling edge debounce time for input processing */
		real32_T MaiPwrAcvDebRisng_C;/* Referenced by: '<S16>/Model' */

		/* Rising edge debounce time for input processing */
		boolean_T MaiPwrAcvDialEna_C;/* Referenced by: '<S16>/Model' */

		/* Signal override enable */
		boolean_T MaiPwrAcvDialVal_C;/* Referenced by: '<S16>/Model' */

		/* Signal override value */
		boolean_T MaiPwrStsIvt_C;/* Referenced by: '<S16>/Model' */

		/* Invert the main power status input */
		boolean_T McuData1DaDialEna_C;/* Referenced by: '<S19>/Model' */

		/* Signal override enable */
		uint8_T McuData1DaDialVal_CA[8];       /* Referenced by: '<S19>/Model' */

		/* Signal override value */
		boolean_T McuData2DaDialEna_C;/* Referenced by: '<S17>/Model' */

		/* Signal override enable */
		uint8_T McuData2DaDialVal_CA[8];       /* Referenced by: '<S17>/Model' */

		/* Signal override value */
		real32_T McuReqTout_C;/* Referenced by: '<S18>/Model' */

		/* Timeout time for the MCUReq message */
		boolean_T McuTDialEna_C;/* Referenced by: '<S16>/Model' */

		/* Signal override enable */
		real32_T McuTDialVal_C;/* Referenced by: '<S16>/Model' */

		/* Signal override value */
		real32_T McuTFilTiCon_C ;/* Referenced by: '<S16>/Model' */

		/* Low pass filter time constant for signal input processing */
		real32_T McuTGain_C;/* Referenced by: '<S16>/Model' */

		/* Gain to convert raw input to engineering units */
		real32_T McuTOfs_C;/* Referenced by: '<S16>/Model' */

		/* Offset to convert raw input to engineering units */
		real32_T McuUBatFilTiCon_C;/* Referenced by: '<S16>/Model' */

		/* Low pass filter time constant for signal input processing */
		real32_T McuUBatGain_C;/* Referenced by: '<S16>/Model' */

		/* Gain to convert raw input to engineering units */
		real32_T McuUBatOfs_C;/* Referenced by: '<S16>/Model' */

		/* Offset to convert raw input to engineering units */
		real32_T McuURefFilTiCon_C;/* Referenced by: '<S16>/Model' */

		/* Low pass filter time constant for signal input processing */
		real32_T McuURefGain_C;/* Referenced by: '<S16>/Model' */

		/* Gain to convert raw input to engineering units */
		real32_T McuURefOfs_C;/* Referenced by: '<S16>/Model' */

		/* Offset to convert raw input to engineering units */
		uint8_T MotPolePairs_C;/* Referenced by: '<S13>/Model' */

		/* The number of pole pairs in the motor */
		real32_T MotPosnEstimrGainI_C;/* Referenced by: '<S13>/Model' */

		/* Integral gain for MotPosn estimator. */
		real32_T MotPosnEstimrGainP_C;/* Referenced by: '<S13>/Model' */

		/* Proportional gain for MotPosn estimator. */
		boolean_T MotPosnEstimrIntglEna_C; /* Referenced by: '<S13>/Model' */

		/* MotPosn estimator integral enable: 0 = disable, 1 = enable. */
		boolean_T MotPosnMagDialEna_C;/* Referenced by: '<S13>/Model' */

		/* Signal override enable */
		real32_T MotPosnMagDialVal_C;/* Referenced by: '<S13>/Model' */

		/* Signal override value */
		real32_T MotPosnOfs_C;/* Referenced by: '<S13>/Model' */

		/* Motor position offset. */
		boolean_T MotPosnSenMeth_C;/* Referenced by: '<S13>/Model' */

		/* Motor position sensing method: 0 = encoder, 1 = resolver. */
		boolean_T MotPosnTrigDialEna_C;/* Referenced by: '<S14>/Model' */

		/* Signal override enable */
		real32_T MotPosnTrigDialVal_CA[6];/* Referenced by: '<S14>/Model' */

		/* Signal override value */
		boolean_T MotSpdDialEna_C;/* Referenced by: '<S13>/Model' */

		/* Signal override enable */
		int16_T MotSpdDialVal_C;/* Referenced by: '<S13>/Model' */

		/* Signal override value */
		real32_T MotSpdFilTiCon_C;/* Referenced by: '<S13>/Model' */

		/* Low pass filter time constant for this signal */
		boolean_T MotSpdMagDialEna_C;/* Referenced by: '<S13>/Model' */

		/* Signal override enable */
		real32_T MotSpdMagDialVal_C;/* Referenced by: '<S13>/Model' */

		/* Signal override value */
		real32_T MotSpdRateLim_C;/* Referenced by: '<S20>/Model' */

		/* The maximum rate at which the motor speed command is allowed to change */
		int16_T MotSpdReqCanDft_C;/* Referenced by: '<S18>/Model' */

		/* The default value used for this signal when the message has timedout */
		boolean_T MotSpdReqCanDialEna_C;/* Referenced by: '<S18>/Model' */

		/* Signal override enable */
		int16_T MotSpdReqCanDialVal_C;/* Referenced by: '<S18>/Model' */

		/* Signal override value */
		int16_T MotSpdReqMax_C;/* Referenced by: '<S20>/Model' */

		/* The maximum magnitued of the speed command the control will attempt to control to */
		uint16_T MotSpdReqThdModChg_C;/* Referenced by: '<S15>/Model' */

		/* The motor speed request below which the drive is allowed to change modes */
		uint16_T MotSpdThdModChg_C;/* Referenced by: '<S15>/Model' */

		/* The motor speed below which the drive is allowed to change modes */
		boolean_T MotTqCmdSpdCtlDialEna_C;  /* Referenced by: '<S20>/Model' */

		/* Signal override enable */
		real32_T MotTqCmdSpdCtlDialVal_C;/* Referenced by: '<S20>/Model' */

		/* Signal override value */
		real32_T MotTqCon_C;/* Referenced by: '<S21>/Model' */

		/* The motor constant that maps between current and torque */
		real32_T MotTqGainBdT1_Ax[5];       /* Referenced by: '<S21>/Model' */

		/* The axis for the table that maps between the board temperature and the gain that limits the maximum motor torque */
		real32_T MotTqGainBdT1_T[5];           /* Referenced by: '<S21>/Model' */

		/* The table values for the table that maps between the board temperature and the gain that limits the maximum motor torque */
		real32_T MotTqGainBdT2_Ax[5];       /* Referenced by: '<S21>/Model' */

		/* The axis for the table that maps between the board temperature and the gain that limits the maximum motor torque */
		real32_T MotTqGainBdT2_T[5];           /* Referenced by: '<S21>/Model' */

		/* The table values for the table that maps between the board temperature and the gain that limits the maximum motor torque */
		real32_T MotTqGainI_C;/* Referenced by: '<S20>/Model' */

		/* Integral gain for motor speed control */
		real32_T MotTqGainP_C;/* Referenced by: '<S20>/Model' */

		/* Proportional gain for motor speed control */
		boolean_T MotTqMaxDialEna_C;/* Referenced by: '<S21>/Model' */

		/* Signal override enable */
		real32_T MotTqMaxDialVal_C;/* Referenced by: '<S21>/Model' */

		/* Signal override value */
		real32_T MotTqMaxMotSpd_Ax[5];/* Referenced by: '<S21>/Model' */

		/* The axis values for the table that maps between the motor speed and the maximum motor torque */
		real32_T MotTqMaxMotSpd_T[5];           /* Referenced by: '<S21>/Model' */

		/* The table values for the table that maps between the motor speed and the maximum motor torque */
		real32_T MotTqReqCanDft_C;/* Referenced by: '<S18>/Model' */

		/* The default value used for this signal when the message has timedout */
		boolean_T MotTqReqCanDialEna_C;/* Referenced by: '<S18>/Model' */

		/* Signal override enable */
		real32_T MotTqReqCanDialVal_C;/* Referenced by: '<S18>/Model' */

		/* Signal override value */
		real32_T MotTqReqThdModChg_C;/* Referenced by: '<S15>/Model' */

		/* The motor torque request below which the drive is allowed to change modes */
		boolean_T MtrPwrPwmEna_C;/* Referenced by: '<S17>/Model' */

		/* Enable MtrPwr modulation output: 0 = disable, 1 = enable. */
		boolean_T PhaAPwmDcDialEna_C;/* Referenced by: '<S11>/Model' */

		/* Signal override enable */
		uint16_T PhaAPwmDcDialVal_C;/* Referenced by: '<S11>/Model' */

		/* Signal override value */
		boolean_T PhaBPwmDcDialEna_C;/* Referenced by: '<S11>/Model' */

		/* Signal override enable */
		uint16_T PhaBPwmDcDialVal_C;/* Referenced by: '<S11>/Model' */

		/* Signal override value */
		boolean_T PhaCPwmDcDialEna_C;/* Referenced by: '<S11>/Model' */

		/* Signal override enable */
		uint16_T PhaCPwmDcDialVal_C;/* Referenced by: '<S11>/Model' */

		/* Signal override value */
		boolean_T PhaCurADialEna_C;/* Referenced by: '<S8>/Model' */

		/* Signal override enable */
		real32_T PhaCurADialVal_C;/* Referenced by: '<S8>/Model' */

		/* Signal override value */
		real32_T PhaCurAFilTiCon_C;/* Referenced by: '<S8>/Model' */

		/* Low pass filter time constant for signal input processing */
		real32_T PhaCurAGain_C;/* Referenced by: '<S8>/Model' */

		/* Gain to convert raw input to engineering units */
		real32_T PhaCurAOfs_C;/* Referenced by: '<S8>/Model' */

		/* Offset to convert raw input to engineering units */
		boolean_T PhaCurBDialEna_C;/* Referenced by: '<S8>/Model' */

		/* Signal override enable */
		real32_T PhaCurBDialVal_C;/* Referenced by: '<S8>/Model' */

		/* Signal override value */
		real32_T PhaCurBFilTiCon_C;/* Referenced by: '<S8>/Model' */

		/* Low pass filter time constant for signal input processing */
		real32_T PhaCurBGain_C;/* Referenced by: '<S8>/Model' */

		/* Gain to convert raw input to engineering units */
		real32_T PhaCurBOfs_C;/* Referenced by: '<S8>/Model' */

		/* Offset to convert raw input to engineering units */
		boolean_T PhaCurCDialEna_C;/* Referenced by: '<S8>/Model' */

		/* Signal override enable */
		real32_T PhaCurCDialVal_C;/* Referenced by: '<S8>/Model' */

		/* Signal override value */
		real32_T PhaCurCFilTiCon_C;/* Referenced by: '<S8>/Model' */

		/* Low pass filter time constant for signal input processing */
		real32_T PhaCurCGain_C;/* Referenced by: '<S8>/Model' */

		/* Gain to convert raw input to engineering units */
		real32_T PhaCurCOfs_C;/* Referenced by: '<S8>/Model' */

		/* Offset to convert raw input to engineering units */
		boolean_T PhaCurDDialEna_C;/* Referenced by: '<S9>/Model' */

		/* Signal override enable */
		real32_T PhaCurDDialVal_C;/* Referenced by: '<S9>/Model' */

		/* Signal override value */
		real32_T PhaCurDTarVal_C;/* Referenced by: '<S21>/Model' */

		/* Signal override value */
		boolean_T PhaCurQDialEna_C;/* Referenced by: '<S9>/Model' */

		/* Signal override enable */
		real32_T PhaCurQDialVal_C;/* Referenced by: '<S9>/Model' */

		/* Signal override value */
		boolean_T PhaCurQTarDialEna_C;/* Referenced by: '<S21>/Model' */

		/* Signal override enable */
		real32_T PhaCurQTarDialVal_C;/* Referenced by: '<S21>/Model' */

		/* Signal override value */
		boolean_T PhaPwmEnaDialEna_C;/* Referenced by: '<S17>/Model' */

		/* Signal override enable */
		boolean_T PhaPwmEnaDialVal_C;/* Referenced by: '<S17>/Model' */

		/* Signal override value */
		boolean_T PhaUACmdDialEna_C;/* Referenced by: '<S12>/Model' */

		/* Signal override enable */
		real32_T PhaUACmdDialVal_C;/* Referenced by: '<S12>/Model' */

		/* Signal override value */
		real32_T PhaUAFilTiCon_C;/* Referenced by: '<S8>/Model' */

		/* Low pass filter time constant for signal input processing */
		real32_T PhaUAGain_C;/* Referenced by: '<S8>/Model' */

		/* Gain to convert raw input to engineering units */
		real32_T PhaUAOfs_C;/* Referenced by: '<S8>/Model' */

		/* Offset to convert raw input to engineering units */
		boolean_T PhaUBCmdDialEna_C;/* Referenced by: '<S12>/Model' */

		/* Signal override enable */
		real32_T PhaUBCmdDialVal_C;/* Referenced by: '<S12>/Model' */

		/* Signal override value */
		real32_T PhaUBFilTiCon_C;/* Referenced by: '<S8>/Model' */

		/* Low pass filter time constant for signal input processing */
		real32_T PhaUBGain_C;/* Referenced by: '<S8>/Model' */

		/* Gain to convert raw input to engineering units */
		real32_T PhaUBOfs_C;/* Referenced by: '<S8>/Model' */

		/* Offset to convert raw input to engineering units */
		boolean_T PhaUCCmdDialEna_C;/* Referenced by: '<S12>/Model' */

		/* Signal override enable */
		real32_T PhaUCCmdDialVal_C;/* Referenced by: '<S12>/Model' */

		/* Signal override value */
		real32_T PhaUCFilTiCon_C;/* Referenced by: '<S8>/Model' */

		/* Low pass filter time constant for signal input processing */
		real32_T PhaUCGain_C;/* Referenced by: '<S8>/Model' */

		/* Gain to convert raw input to engineering units */
		real32_T PhaUCOfs_C;/* Referenced by: '<S8>/Model' */

		/* Offset to convert raw input to engineering units */
		real32_T PhaUDAntiWindupGain_C;/* Referenced by: '<S10>/Model' */

		/* Gain used to attenuate the integrated error when the output voltage command is saturated to avoid integral windup  */
		boolean_T PhaUDCmdDialEna_C;/* Referenced by: '<S10>/Model' */

		/* Signal override enable */
		real32_T PhaUDCmdDialVal_C;/* Referenced by: '<S10>/Model' */

		/* Signal override value */
		real32_T PhaUDCmdOpenLoop_C;/* Referenced by: '<S10>/Model' */

		/* The d-axis phase voltage command in open loop mode */
		real32_T PhaUDGainI_C;/* Referenced by: '<S10>/Model' */

		/* Integral control gain for d-axis current control */
		real32_T PhaUDGainP_C;/* Referenced by: '<S10>/Model' */

		/* Proportional control gain for d-axis current control */
		real32_T PhaUMaxVal_C;/* Referenced by: '<S10>/Model' */

		/* The smallest value the maximum phase voltage is allowed to take on for current control calculations */
		real32_T PhaUQAntiWindupGain_C;/* Referenced by: '<S10>/Model' */

		/* Gain used to attenuate the integrated error when the output voltage command is saturated to avoid integral windup */
		boolean_T PhaUQCmdDialEna_C;/* Referenced by: '<S10>/Model' */

		/* Signal override enable */
		real32_T PhaUQCmdDialVal_C;/* Referenced by: '<S10>/Model' */

		/* Signal override value */
		real32_T PhaUQCmdOpenLoop_C;/* Referenced by: '<S10>/Model' */

		/* The q-axis phase voltage command in open loop mode */
		real32_T PhaUQGainI_C;/* Referenced by: '<S10>/Model' */

		/* Integral control gain for q-axis current control */
		real32_T PhaUQGainP_C;/* Referenced by: '<S10>/Model' */

		/* Proportional control gain for q-axis current control */
		real32_T PlsOffTi_C;/* Referenced by: '<S17>/Model' */

		/* The time the LED is off between two pulses */
		real32_T PlsOnTi_C;/* Referenced by: '<S17>/Model' */

		/* The time the LED is on during a pulse */
		boolean_T PwrCmdDialEna_C;/* Referenced by: '<S15>/Model' */

		/* Signal override enable */
		boolean_T PwrCmdDialVal_C;/* Referenced by: '<S15>/Model' */

		/* Signal override value */
		boolean_T RedLedDialEna_C;/* Referenced by: '<S17>/Model' */

		/* Signal override enable */
		boolean_T RedLedDialVal_C;/* Referenced by: '<S17>/Model' */

		/* Signal override value */
		boolean_T RedLedIvt_C;/* Referenced by: '<S17>/Model' */

		/* Invert the LED command */
		int16_T ReloadRegisterMax_C;/* Referenced by: '<S11>/Model' */

		/* The maximum value of the register used by the hardware PWM generator */
		real32_T ResolverCosFilTiCon_C;/* Referenced by: '<S8>/Model' */

		/* Low pass filter time constant for signal input processing */
		real32_T ResolverCosGain_C;/* Referenced by: '<S8>/Model' */

		/* Gain to convert raw input to engineering units */
		real32_T ResolverCosOfs_C;/* Referenced by: '<S8>/Model' */

		/* Offset to convert raw input to engineering units */
		boolean_T ResolverExctEna_C;/* Referenced by: '<S17>/Model' */

		/* Command to enable resolver excitation waveform generation: 0 = disable, 1 = enable. */
		boolean_T ResolverSinCosDialEna_C;/* Referenced by: '<S8>/Model' */

		/* Signal override enable */
		real32_T ResolverSinCosDialVal_CA[2]; /* Referenced by: '<S8>/Model' */

		/* Signal override value */
		real32_T ResolverSinFilTiCon_C;/* Referenced by: '<S8>/Model' */

		/* Low pass filter time constant for signal input processing */
		real32_T ResolverSinGain_C;/* Referenced by: '<S8>/Model' */

		/* Gain to convert raw input to engineering units */
		real32_T ResolverSinOfs_C;/* Referenced by: '<S8>/Model' */

		/* Offset to convert raw input to engineering units */
		real32_T StatorInductanceD_C;/* Referenced by: '<S10>/Model' */

		/* The motor stator d-axis inductance */
		real32_T StatorInductanceQ_C;/* Referenced by: '<S10>/Model' */

		/* The motor stator q-axis inductance */
		boolean_T SwPwrPwmEna_C;/* Referenced by: '<S17>/Model' */

		/* Enable SwPwr modulation output: 0 = disable, 1 = enable. */
		boolean_T WakeRetry_C;/* Referenced by: '<S15>/Model' */

		/* Flag used to force the drive to try and rewake the board by activiting the power command */
		real32_T WakeTout_C;/* Referenced by: '<S15>/Model' */

		/* The amount of time the control waits for the power activation signal before shutting off the power command and terminating the wake attempt */
		boolean_T YellowLedCmd_C;/* Referenced by: '<S17>/Model' */
		real32_T Spare[16];
	};
	public: struct VectorDigitalConfig
	{
		bool Spare;
	};
	public: struct VectorInputs
	{
		real32_T BdT1;
		real32_T BdT2;
		real32_T McuT;
		real32_T HvBusU;
		real32_T PhaCurA;
		real32_T PhaCurB;
		real32_T PhaCurC;
		real32_T HvBusCur;
		real32_T ResolverSinCos[2];
		uint16_T ASWIN_BdT1;
		uint16_T ASWIN_BdT2;
		uint16_T ASWIN_McuURef;
		uint16_T ASWIN_McuT;
		uint16_T ASWIN_McuUBat;
		uint16_T ASWIN_HvBusU;
		uint16_T ASWIN_PhaCurA;
		uint16_T ASWIN_PhaCurB;
		uint16_T ASWIN_PhaCurC;
		uint16_T ASWIN_HvBusCur;
		uint16_T ASWIN_PhaUA;
		uint16_T ASWIN_PhaUB;
		uint16_T ASWIN_PhaUC;
		uint16_T ASWIN_ResolverSin;
		uint16_T ASWIN_ResolverCos;
		int16_T ASWIN_EncoderCt;
		boolean_T ASWIN_MaiPwrSts;
		boolean_T ASWIN_AuxPwrSts;
		uint8_T ASWIN_McuReqDa[8];
		uint8_T ASWIN_McuReqCt;
		boolean_T ASWIN_EncoderZ;
		DRIVEMODE DrvModReq;
	};
	public: struct VectorDigitalInputs
	{
		bool Spare;
	};
	public: struct VectorOutputs
	{
		real32_T MotPosnMag;
		real32_T MotSpdMag;
		real32_T MotPosnTrig[6];
		real32_T PhaCurD;
		real32_T PhaCurQ;
		real32_T PhaUDCmd;
		real32_T PhaUQCmd;
		real32_T PhaUACmd;
		real32_T PhaUBCmd;
		real32_T PhaUCCmd;
		real32_T MotTqReqCan;
		real32_T MotTqCmdSpdCtl;
		real32_T PhaCurQTar;
		real32_T PhaCurDTar;
		real32_T MotTqMax;
		uint16_T ASWOUT_PhaAPwmDc;
		uint16_T ASWOUT_PhaBPwmDc;
		uint16_T ASWOUT_PhaCPwmDc;
		int16_T MotSpd;
		int16_T MotSpdReqCan;
		uint8_T ASWOUT_McuData2Da[8];
		uint8_T ASWOUT_McuData1Da[8];
		boolean_T MaiPwrAcv;
		boolean_T AuxPwrAcv;
		boolean_T PwrCmd;
		boolean_T ASWOUT_GreenLed;
		boolean_T ASWOUT_RedLed;
		boolean_T ASWOUT_YellowLed;
		boolean_T ASWOUT_ResolverExctEna;
		boolean_T ASWOUT_CanPwrPwmEna;
		boolean_T ASWOUT_InPwrPwmEna;
		boolean_T ASWOUT_MtrPwrPwmEna;
		boolean_T ASWOUT_SwPwrPwmEna;
		boolean_T ASWOUT_PhaPwmEna;
		DRIVEMODE DrvMod;
	};
	public: struct VectorDigitalOutputs
	{
		bool Spare;
	};
	private: static VectorConfig *_config;
	//private: static VectorDigitalConfig *_digitalConfig;
	private: static VectorInputs *_analogIn;
	//private: static VectorDigitalInputs *_digitalIn;
	private: static VectorOutputs *_analogOut;
	//private: static VectorDigitalOutputs *_digitalOut;

	public: static void LinkData(VectorConfig *config, VectorInputs *analogIn, VectorOutputs *analogOut)
	{
		_config = config;
		_analogIn = analogIn;
		_analogOut = analogOut;
	}
	public: static void UpdateConfig();
	public: static void UpdateInputsToXcp();//float *analogData);
	public: static void UpdateOutputsFromXcp();
	public: static void UpdateInputsToInt();
	public: static void UpdateOutputsFromInt();
};
#endif

#endif //VECTORCONTROL_H
