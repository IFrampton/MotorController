/*
 * File: P2319ASW01.c
 *
 * Code generated for Simulink model 'P2319ASW01'.
 *
 * Model version                  : 1.229
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:12:40 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "P2319ASW01.h"
#include "P2319ASW01_private.h"
#include "rtwtypes.h"
#include "P2319ASW01_types.h"
#include <string.h>
#include "rt_nonfinite.h"
#define ADCINP_MDLREF_HIDE_CHILD_
#include "ADCINP.h"
#define CLAPAR_MDLREF_HIDE_CHILD_
#include "CLAPAR.h"
#define CURCTL_MDLREF_HIDE_CHILD_
#include "CURCTL.h"
#define GATOUP_MDLREF_HIDE_CHILD_
#include "GATOUP.h"
#define INVCPA_MDLREF_HIDE_CHILD_
#include "INVCPA.h"
#define POSINP_MDLREF_HIDE_CHILD_
#include "POSINP.h"
#define POSTRG_MDLREF_HIDE_CHILD_
#include "POSTRG.h"
#define MODCTL_MDLREF_HIDE_CHILD_
#include "MODCTL.h"
#define SLWINP_MDLREF_HIDE_CHILD_
#include "SLWINP.h"
#define SLWOUP_MDLREF_HIDE_CHILD_
#include "SLWOUP.h"
#define MEDINP_MDLREF_HIDE_CHILD_
#include "MEDINP.h"
#define MEDOUP_MDLREF_HIDE_CHILD_
#include "MEDOUP.h"
#define SPDCTL_MDLREF_HIDE_CHILD_
#include "SPDCTL.h"
#define TRQCTL_MDLREF_HIDE_CHILD_
#include "TRQCTL.h"

/* Exported block signals */
real32_T BdT1;                         /* '<S16>/Model'
                                        * Board temperature 1
                                        */
real32_T BdT2;                         /* '<S16>/Model'
                                        * Board temperature 2
                                        */
real32_T McuT;                         /* '<S16>/Model'
                                        * Microcontroller temperature
                                        */
real32_T HvBusU;                       /* '<S8>/Model'
                                        * The DC bus voltage into the inverter
                                        */
real32_T PhaCurA;                      /* '<S8>/Model'
                                        * Phase A current
                                        */
real32_T PhaCurB;                      /* '<S8>/Model'
                                        * Phase B current
                                        */
real32_T PhaCurC;                      /* '<S8>/Model'
                                        * Phase C current
                                        */
real32_T HvBusCur;                     /* '<S8>/Model'
                                        * The DC bus current into the inverter
                                        */
real32_T ResolverSinCos[2];            /* '<S8>/Model'
                                        * Resolver sine and cosine signals.
                                        */
real32_T MotPosnMag;                   /* '<S13>/Model'
                                        * The magnetic rotor position. Zero degrees represents the rotor magnetic field aligned with the stator's A phase.
                                        */
real32_T MotSpdMag;                    /* '<S13>/Model'
                                        * The magnetic motor speed
                                        */
real32_T MotPosnTrig[6];               /* '<S14>/Model'
                                        * The results of the trig calculations that are used in the reference frame transforms
                                        */
real32_T PhaCurD;                      /* '<S9>/Model'
                                        * The motor current in the rotating d axis direction (non-torque producing).
                                        */
real32_T PhaCurQ;                      /* '<S9>/Model'
                                        * The motor current in the rotating q axis direction (torque producing).
                                        */
real32_T PhaUDCmd;                     /* '<S10>/Model'
                                        * Commanded d-axis phase voltage
                                        */
real32_T PhaUQCmd;                     /* '<S10>/Model'
                                        * Commanded q-axis phase voltage
                                        */
real32_T PhaUACmd;                     /* '<S12>/Model'
                                        * Phase A voltage command
                                        */
real32_T PhaUBCmd;                     /* '<S12>/Model'
                                        * Phase B voltage command
                                        */
real32_T PhaUCCmd;                     /* '<S12>/Model'
                                        * Phase C voltage command
                                        */
real32_T MotTqReqCan;                  /* '<S18>/Model'
                                        * The requested motor torque
                                        */
real32_T MotTqCmdSpdCtl;               /* '<S20>/Model'
                                        * The motor torque commanded by the motor speed controller
                                        */
real32_T PhaCurQTar;                   /* '<S21>/Model'
                                        * The target q-axis current
                                        */
real32_T PhaCurDTar;                   /* '<S21>/Model'
                                        * The target d-axis current
                                        */
real32_T MotTqMax;                     /* '<S21>/Model'
                                        * The maximum motor torque after derates
                                        */
uint16_T ASWIN_BdT1;                   /*
                                        * The raw ADC input value
                                        */
uint16_T ASWIN_BdT2;                   /*
                                        * The raw ADC input value
                                        */
uint16_T ASWIN_McuURef;                /*
                                        * The raw ADC input value
                                        */
uint16_T ASWIN_McuT;                   /*
                                        * The raw ADC input value
                                        */
uint16_T ASWIN_McuUBat;                /*
                                        * The raw ADC input value
                                        */
uint16_T ASWIN_HvBusU;                 /*
                                        * The raw ADC input value
                                        */
uint16_T ASWIN_PhaCurA;                /*
                                        * The raw ADC input value
                                        */
uint16_T ASWIN_PhaCurB;                /*
                                        * The raw ADC input value
                                        */
uint16_T ASWIN_PhaCurC;                /*
                                        * The raw ADC input value
                                        */
uint16_T ASWIN_HvBusCur;               /*
                                        * The raw ADC input value
                                        */
uint16_T ASWIN_PhaUA;                  /*
                                        * The raw ADC input value
                                        */
uint16_T ASWIN_PhaUB;                  /*
                                        * The raw ADC input value
                                        */
uint16_T ASWIN_PhaUC;                  /*
                                        * The raw ADC input value
                                        */
uint16_T ASWIN_ResolverSin;            /*
                                        * The raw ADC input value
                                        */
uint16_T ASWIN_ResolverCos;            /*
                                        * The raw ADC input value
                                        */
uint16_T ASWOUT_PhaAPwmDc;             /* '<S11>/Model'
                                        * The raw modulation command used by the hardware PWM generator
                                        */
uint16_T ASWOUT_PhaBPwmDc;             /* '<S11>/Model'
                                        * The raw modulation command used by the hardware PWM generator
                                        */
uint16_T ASWOUT_PhaCPwmDc;             /* '<S11>/Model'
                                        * The raw modulation command used by the hardware PWM generator
                                        */
int16_T ASWIN_EncoderCt;               /*
                                        * The raw encoder count input
                                        */
int16_T MotSpd;                        /* '<S13>/Model'
                                        * The mechanical motor speed
                                        */
int16_T MotSpdReqCan;                  /* '<S18>/Model'
                                        * The requested motor speed
                                        */
uint8_T ASWOUT_McuData2Da[8];          /* '<S17>/Model'
                                        * The raw message data frame
                                        */
uint8_T ASWIN_McuReqDa[8];             /*
                                        * The raw message data frame
                                        */
uint8_T ASWIN_McuReqCt;                /*
                                        * The raw message counter used to indicate message freshness
                                        */
uint8_T ASWOUT_McuData1Da[8];          /* '<S19>/Model'
                                        * The raw message data frame
                                        */
boolean_T ASWIN_MaiPwrSts;             /*
                                        * The raw input value
                                        */
boolean_T ASWIN_AuxPwrSts;             /*
                                        * The raw input value
                                        */
boolean_T MaiPwrAcv;                   /* '<S16>/Model'
                                        * Main power active flag
                                        */
boolean_T AuxPwrAcv;                   /* '<S16>/Model'
                                        * Auxilary power active flag
                                        */
boolean_T PwrCmd;                      /* '<S15>/Model'
                                        * The command to activate the auxilary power supplies
                                        */
boolean_T ASWOUT_GreenLed;             /* '<S17>/Model'
                                        * The raw output value
                                        */
boolean_T ASWOUT_RedLed;               /* '<S17>/Model'
                                        * The raw output value
                                        */
boolean_T ASWOUT_YellowLed;            /* '<S17>/Model'
                                        * The raw output value
                                        */
boolean_T ASWOUT_ResolverExctEna;      /* '<S17>/Model'
                                        * The raw output value
                                        */
boolean_T ASWOUT_CanPwrPwmEna;         /* '<S17>/Model'
                                        * The raw output value
                                        */
boolean_T ASWOUT_InPwrPwmEna;          /* '<S17>/Model'
                                        * The raw output value
                                        */
boolean_T ASWOUT_MtrPwrPwmEna;         /* '<S17>/Model'
                                        * The raw output value
                                        */
boolean_T ASWOUT_SwPwrPwmEna;          /* '<S17>/Model'
                                        * The raw output value
                                        */
boolean_T ASWOUT_PhaPwmEna;            /* '<S17>/Model'
                                        * The raw modulation enable command used by the hardware PWM generator: 0 = disable, 1 = enable.
                                        */
boolean_T ASWIN_EncoderZ;              /*
                                        * The raw encoder z signal
                                        */
DRIVEMODE DrvMod;                      /* '<S15>/Model'
                                        * The active drive mode
                                        */
DRIVEMODE DrvModReq;                   /* '<S18>/Model'
                                        * The requested drive mode
                                        */

/* Exported data definition */

/* Calibration memory section */
/* Definition for custom storage class: Calibration */
__attribute__ ((section (".cal_data"))) real32_T AuxPwrAcvDebFall_C = 0.0F;/* Referenced by: '<S16>/Model' */

/* Falling edge debounce time for input processing */
__attribute__ ((section (".cal_data"))) real32_T AuxPwrAcvDebRisng_C = 0.0F;/* Referenced by: '<S16>/Model' */

/* Rising edge debounce time for input processing */
__attribute__ ((section (".cal_data"))) boolean_T AuxPwrAcvDialEna_C = true;/* Referenced by: '<S16>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) boolean_T AuxPwrAcvDialVal_C = false;/* Referenced by: '<S16>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) boolean_T AuxPwrStsIvt_C = false;/* Referenced by: '<S16>/Model' */

/* Invert the auxilary power status input */
__attribute__ ((section (".cal_data"))) boolean_T BdT1DialEna_C = true;/* Referenced by: '<S16>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) real32_T BdT1DialVal_C = 0.0F;/* Referenced by: '<S16>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) real32_T BdT1FilTiCon_C = 0.0F;/* Referenced by: '<S16>/Model' */

/* Low pass filter time constant for signal input processing */
__attribute__ ((section (".cal_data"))) real32_T BdT1Gain_C = 1.0F;/* Referenced by: '<S16>/Model' */

/* Gain to convert raw input to engineering units */
__attribute__ ((section (".cal_data"))) real32_T BdT1Ofs_C = 0.0F;/* Referenced by: '<S16>/Model' */

/* Offset to convert raw input to engineering units */
__attribute__ ((section (".cal_data"))) boolean_T BdT2DialEna_C = true;/* Referenced by: '<S16>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) real32_T BdT2DialVal_C = 0.0F;/* Referenced by: '<S16>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) real32_T BdT2FilTiCon_C = 0.0F;/* Referenced by: '<S16>/Model' */

/* Low pass filter time constant for signal input processing */
__attribute__ ((section (".cal_data"))) real32_T BdT2Gain_C = 1.0F;/* Referenced by: '<S16>/Model' */

/* Gain to convert raw input to engineering units */
__attribute__ ((section (".cal_data"))) real32_T BdT2Ofs_C = 0.0F;/* Referenced by: '<S16>/Model' */

/* Offset to convert raw input to engineering units */
__attribute__ ((section (".cal_data"))) boolean_T CanPwrPwmEna_C = false;/* Referenced by: '<S17>/Model' */

/* Enable CanPwr modulation output: 0 = disable, 1 = enable. */
__attribute__ ((section (".cal_data"))) boolean_T DrvModDialEna_C = true;/* Referenced by: '<S15>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) DRIVEMODE DrvModDialVal_C = DISABLED;/* Referenced by: '<S15>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) DRIVEMODE DrvModReqDft_C = DISABLED;/* Referenced by: '<S18>/Model' */

/* The default value used for this signal when the message has timedout */
__attribute__ ((section (".cal_data"))) boolean_T DrvModReqDialEna_C = true;/* Referenced by: '<S18>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) DRIVEMODE DrvModReqDialVal_C = DISABLED;/* Referenced by: '<S18>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) uint16_T EncoderCtPerRev_C = 1000U;/* Referenced by: '<S13>/Model' */

/* The number of encoder counts per mechanical revolution */
__attribute__ ((section (".cal_data"))) real32_T EncoderOfs_C = 0.0F;/* Referenced by: '<S13>/Model' */

/* Offset used to align the encoder z signal with the true zero angle */
__attribute__ ((section (".cal_data"))) real32_T FluxLinkage_C = 0.011F;/* Referenced by: '<S10>/Model' */

/* The permanent magnet flux linkage of the motor */
__attribute__ ((section (".cal_data"))) boolean_T GreenLedDialEna_C = false;/* Referenced by: '<S17>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) boolean_T GreenLedDialVal_C = false;/* Referenced by: '<S17>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) boolean_T GreenLedIvt_C = true;/* Referenced by: '<S17>/Model' */

/* Invert the LED command */
__attribute__ ((section (".cal_data"))) boolean_T HvBusCurDialEna_C = true;/* Referenced by: '<S8>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) real32_T HvBusCurDialVal_C = 0.0F;/* Referenced by: '<S8>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) real32_T HvBusCurFilTiCon_C = 0.0F;/* Referenced by: '<S8>/Model' */

/* Low pass filter time constant for signal input processing */
__attribute__ ((section (".cal_data"))) real32_T HvBusCurGain_C = 0.001548F;/* Referenced by: '<S8>/Model' */

/* Gain to convert raw input to engineering units */
__attribute__ ((section (".cal_data"))) real32_T HvBusCurOfs_C = 0.0F;/* Referenced by: '<S8>/Model' */

/* Offset to convert raw input to engineering units */
__attribute__ ((section (".cal_data"))) boolean_T HvBusUDialEna_C = true;/* Referenced by: '<S8>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) real32_T HvBusUDialVal_C = 0.0F;/* Referenced by: '<S8>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) real32_T HvBusUFilTiCon_C = 0.0F;/* Referenced by: '<S8>/Model' */

/* Low pass filter time constant for signal input processing */
__attribute__ ((section (".cal_data"))) real32_T HvBusUGain_C = 0.0152F;/* Referenced by: '<S8>/Model' */

/* Gain to convert raw input to engineering units */
__attribute__ ((section (".cal_data"))) real32_T HvBusUOfs_C = 0.0F;/* Referenced by: '<S8>/Model' */

/* Offset to convert raw input to engineering units */
__attribute__ ((section (".cal_data"))) boolean_T InPwrPwmEna_C = false;/* Referenced by: '<S17>/Model' */

/* Enable InPwr modulation output: 0 = disable, 1 = enable. */
__attribute__ ((section (".cal_data"))) real32_T LedOffTi_C = 0.5F;/* Referenced by: '<S17>/Model' */

/* The time the LED is off between pulse groups */
__attribute__ ((section (".cal_data"))) uint8_T LedPlsCtDft_C = 1U;/* Referenced by: '<S17>/Model' */

/* The number of on pulses for the LED while in this mode */
__attribute__ ((section (".cal_data"))) uint8_T LedPlsCtOpenLoop_C = 2U;/* Referenced by: '<S17>/Model' */

/* The number of on pulses for the LED while in this mode */
__attribute__ ((section (".cal_data"))) uint8_T LedPlsCtSpdCtl_C = 4U;/* Referenced by: '<S17>/Model' */

/* The number of on pulses for the LED while in this mode */
__attribute__ ((section (".cal_data"))) uint8_T LedPlsCtTqCtl_C = 3U;/* Referenced by: '<S17>/Model' */

/* The number of on pulses for the LED while in this mode */
__attribute__ ((section (".cal_data"))) real32_T MaiPwrAcvDebFall_C = 0.0F;/* Referenced by: '<S16>/Model' */

/* Falling edge debounce time for input processing */
__attribute__ ((section (".cal_data"))) real32_T MaiPwrAcvDebRisng_C = 0.0F;/* Referenced by: '<S16>/Model' */

/* Rising edge debounce time for input processing */
__attribute__ ((section (".cal_data"))) boolean_T MaiPwrAcvDialEna_C = true;/* Referenced by: '<S16>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) boolean_T MaiPwrAcvDialVal_C = false;/* Referenced by: '<S16>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) boolean_T MaiPwrStsIvt_C = false;/* Referenced by: '<S16>/Model' */

/* Invert the main power status input */
__attribute__ ((section (".cal_data"))) boolean_T McuData1DaDialEna_C = false;/* Referenced by: '<S19>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) uint8_T McuData1DaDialVal_CA[8] = { 0U,
  0U, 0U, 0U, 0U, 0U, 0U, 0U } ;       /* Referenced by: '<S19>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) boolean_T McuData2DaDialEna_C = false;/* Referenced by: '<S17>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) uint8_T McuData2DaDialVal_CA[8] = { 0U,
  0U, 0U, 0U, 0U, 0U, 0U, 0U } ;       /* Referenced by: '<S17>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) real32_T McuReqTout_C = 0.07F;/* Referenced by: '<S18>/Model' */

/* Timeout time for the MCUReq message */
__attribute__ ((section (".cal_data"))) boolean_T McuTDialEna_C = true;/* Referenced by: '<S16>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) real32_T McuTDialVal_C = 0.0F;/* Referenced by: '<S16>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) real32_T McuTFilTiCon_C = 0.0F;/* Referenced by: '<S16>/Model' */

/* Low pass filter time constant for signal input processing */
__attribute__ ((section (".cal_data"))) real32_T McuTGain_C = 0.0F;/* Referenced by: '<S16>/Model' */

/* Gain to convert raw input to engineering units */
__attribute__ ((section (".cal_data"))) real32_T McuTOfs_C = 0.0F;/* Referenced by: '<S16>/Model' */

/* Offset to convert raw input to engineering units */
__attribute__ ((section (".cal_data"))) real32_T McuUBatFilTiCon_C = 0.0F;/* Referenced by: '<S16>/Model' */

/* Low pass filter time constant for signal input processing */
__attribute__ ((section (".cal_data"))) real32_T McuUBatGain_C = 0.01173F;/* Referenced by: '<S16>/Model' */

/* Gain to convert raw input to engineering units */
__attribute__ ((section (".cal_data"))) real32_T McuUBatOfs_C = 0.0F;/* Referenced by: '<S16>/Model' */

/* Offset to convert raw input to engineering units */
__attribute__ ((section (".cal_data"))) real32_T McuURefFilTiCon_C = 0.0F;/* Referenced by: '<S16>/Model' */

/* Low pass filter time constant for signal input processing */
__attribute__ ((section (".cal_data"))) real32_T McuURefGain_C = 0.0F;/* Referenced by: '<S16>/Model' */

/* Gain to convert raw input to engineering units */
__attribute__ ((section (".cal_data"))) real32_T McuURefOfs_C = 0.0F;/* Referenced by: '<S16>/Model' */

/* Offset to convert raw input to engineering units */
__attribute__ ((section (".cal_data"))) uint8_T MotPolePairs_C = 4U;/* Referenced by: '<S13>/Model' */

/* The number of pole pairs in the motor */
__attribute__ ((section (".cal_data"))) real32_T MotPosnEstimrGainI_C = 0.0F;/* Referenced by: '<S13>/Model' */

/* Integral gain for MotPosn estimator. */
__attribute__ ((section (".cal_data"))) real32_T MotPosnEstimrGainP_C = 0.0F;/* Referenced by: '<S13>/Model' */

/* Proportional gain for MotPosn estimator. */
__attribute__ ((section (".cal_data"))) boolean_T MotPosnEstimrIntglEna_C =
  false;                               /* Referenced by: '<S13>/Model' */

/* MotPosn estimator integral enable: 0 = disable, 1 = enable. */
__attribute__ ((section (".cal_data"))) boolean_T MotPosnMagDialEna_C = true;/* Referenced by: '<S13>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) real32_T MotPosnMagDialVal_C = 0.0F;/* Referenced by: '<S13>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) real32_T MotPosnOfs_C = 0.0F;/* Referenced by: '<S13>/Model' */

/* Motor position offset. */
__attribute__ ((section (".cal_data"))) boolean_T MotPosnSenMeth_C = true;/* Referenced by: '<S13>/Model' */

/* Motor position sensing method: 0 = encoder, 1 = resolver. */
__attribute__ ((section (".cal_data"))) boolean_T MotPosnTrigDialEna_C = false;/* Referenced by: '<S14>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) real32_T MotPosnTrigDialVal_CA[6] = {
  0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F } ;/* Referenced by: '<S14>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) boolean_T MotSpdDialEna_C = true;/* Referenced by: '<S13>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) int16_T MotSpdDialVal_C = 0;/* Referenced by: '<S13>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) real32_T MotSpdFilTiCon_C = 0.001F;/* Referenced by: '<S13>/Model' */

/* Low pass filter time constant for this signal */
__attribute__ ((section (".cal_data"))) boolean_T MotSpdMagDialEna_C = true;/* Referenced by: '<S13>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) real32_T MotSpdMagDialVal_C = 0.0F;/* Referenced by: '<S13>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) real32_T MotSpdRateLim_C = 1000.0F;/* Referenced by: '<S20>/Model' */

/* The maximum rate at which the motor speed command is allowed to change */
__attribute__ ((section (".cal_data"))) int16_T MotSpdReqCanDft_C = 0;/* Referenced by: '<S18>/Model' */

/* The default value used for this signal when the message has timedout */
__attribute__ ((section (".cal_data"))) boolean_T MotSpdReqCanDialEna_C = true;/* Referenced by: '<S18>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) int16_T MotSpdReqCanDialVal_C = 0;/* Referenced by: '<S18>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) int16_T MotSpdReqMax_C = 1000;/* Referenced by: '<S20>/Model' */

/* The maximum magnitued of the speed command the control will attempt to control to */
__attribute__ ((section (".cal_data"))) uint16_T MotSpdReqThdModChg_C = 50U;/* Referenced by: '<S15>/Model' */

/* The motor speed request below which the drive is allowed to change modes */
__attribute__ ((section (".cal_data"))) uint16_T MotSpdThdModChg_C = 50U;/* Referenced by: '<S15>/Model' */

/* The motor speed below which the drive is allowed to change modes */
__attribute__ ((section (".cal_data"))) boolean_T MotTqCmdSpdCtlDialEna_C =
  false;                               /* Referenced by: '<S20>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) real32_T MotTqCmdSpdCtlDialVal_C = 0.0F;/* Referenced by: '<S20>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) real32_T MotTqCon_C = 0.054F;/* Referenced by: '<S21>/Model' */

/* The motor constant that maps between current and torque */
__attribute__ ((section (".cal_data"))) real32_T MotTqGainBdT1_Ax[5] = { -40.0F,
  40.0F, 50.0F, 60.0F, 70.0F } ;       /* Referenced by: '<S21>/Model' */

/* The axis for the table that maps between the board temperature and the gain that limits the maximum motor torque */
__attribute__ ((section (".cal_data"))) real32_T MotTqGainBdT1_T[5] = { 1.0F,
  1.0F, 0.0F, 0.0F, 0.0F } ;           /* Referenced by: '<S21>/Model' */

/* The table values for the table that maps between the board temperature and the gain that limits the maximum motor torque */
__attribute__ ((section (".cal_data"))) real32_T MotTqGainBdT2_Ax[5] = { -40.0F,
  40.0F, 50.0F, 60.0F, 70.0F } ;       /* Referenced by: '<S21>/Model' */

/* The axis for the table that maps between the board temperature and the gain that limits the maximum motor torque */
__attribute__ ((section (".cal_data"))) real32_T MotTqGainBdT2_T[5] = { 1.0F,
  1.0F, 0.0F, 0.0F, 0.0F } ;           /* Referenced by: '<S21>/Model' */

/* The table values for the table that maps between the board temperature and the gain that limits the maximum motor torque */
__attribute__ ((section (".cal_data"))) real32_T MotTqGainI_C = 0.0001F;/* Referenced by: '<S20>/Model' */

/* Integral gain for motor speed control */
__attribute__ ((section (".cal_data"))) real32_T MotTqGainP_C = 0.0001F;/* Referenced by: '<S20>/Model' */

/* Proportional gain for motor speed control */
__attribute__ ((section (".cal_data"))) boolean_T MotTqMaxDialEna_C = false;/* Referenced by: '<S21>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) real32_T MotTqMaxDialVal_C = 0.0F;/* Referenced by: '<S21>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) real32_T MotTqMaxMotSpd_Ax[5] = { 0.0F,
  1000.0F, 2000.0F, 3000.0F, 4000.0F } ;/* Referenced by: '<S21>/Model' */

/* The axis values for the table that maps between the motor speed and the maximum motor torque */
__attribute__ ((section (".cal_data"))) real32_T MotTqMaxMotSpd_T[5] = { 1.0F,
  1.0F, 1.0F, 1.0F, 1.0F } ;           /* Referenced by: '<S21>/Model' */

/* The table values for the table that maps between the motor speed and the maximum motor torque */
__attribute__ ((section (".cal_data"))) real32_T MotTqReqCanDft_C = 0.0F;/* Referenced by: '<S18>/Model' */

/* The default value used for this signal when the message has timedout */
__attribute__ ((section (".cal_data"))) boolean_T MotTqReqCanDialEna_C = true;/* Referenced by: '<S18>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) real32_T MotTqReqCanDialVal_C = 0.0F;/* Referenced by: '<S18>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) real32_T MotTqReqThdModChg_C = 1.0F;/* Referenced by: '<S15>/Model' */

/* The motor torque request below which the drive is allowed to change modes */
__attribute__ ((section (".cal_data"))) boolean_T MtrPwrPwmEna_C = false;/* Referenced by: '<S17>/Model' */

/* Enable MtrPwr modulation output: 0 = disable, 1 = enable. */
__attribute__ ((section (".cal_data"))) boolean_T PhaAPwmDcDialEna_C = false;/* Referenced by: '<S11>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) uint16_T PhaAPwmDcDialVal_C = 1000U;/* Referenced by: '<S11>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) boolean_T PhaBPwmDcDialEna_C = false;/* Referenced by: '<S11>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) uint16_T PhaBPwmDcDialVal_C = 1000U;/* Referenced by: '<S11>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) boolean_T PhaCPwmDcDialEna_C = false;/* Referenced by: '<S11>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) uint16_T PhaCPwmDcDialVal_C = 600U;/* Referenced by: '<S11>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) boolean_T PhaCurADialEna_C = true;/* Referenced by: '<S8>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) real32_T PhaCurADialVal_C = 0.0F;/* Referenced by: '<S8>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) real32_T PhaCurAFilTiCon_C = 0.0F;/* Referenced by: '<S8>/Model' */

/* Low pass filter time constant for signal input processing */
__attribute__ ((section (".cal_data"))) real32_T PhaCurAGain_C = 0.001548F;/* Referenced by: '<S8>/Model' */

/* Gain to convert raw input to engineering units */
__attribute__ ((section (".cal_data"))) real32_T PhaCurAOfs_C = -3.06F;/* Referenced by: '<S8>/Model' */

/* Offset to convert raw input to engineering units */
__attribute__ ((section (".cal_data"))) boolean_T PhaCurBDialEna_C = true;/* Referenced by: '<S8>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) real32_T PhaCurBDialVal_C = 0.0F;/* Referenced by: '<S8>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) real32_T PhaCurBFilTiCon_C = 0.0F;/* Referenced by: '<S8>/Model' */

/* Low pass filter time constant for signal input processing */
__attribute__ ((section (".cal_data"))) real32_T PhaCurBGain_C = 0.001548F;/* Referenced by: '<S8>/Model' */

/* Gain to convert raw input to engineering units */
__attribute__ ((section (".cal_data"))) real32_T PhaCurBOfs_C = -3.06F;/* Referenced by: '<S8>/Model' */

/* Offset to convert raw input to engineering units */
__attribute__ ((section (".cal_data"))) boolean_T PhaCurCDialEna_C = true;/* Referenced by: '<S8>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) real32_T PhaCurCDialVal_C = 0.0F;/* Referenced by: '<S8>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) real32_T PhaCurCFilTiCon_C = 0.0F;/* Referenced by: '<S8>/Model' */

/* Low pass filter time constant for signal input processing */
__attribute__ ((section (".cal_data"))) real32_T PhaCurCGain_C = 0.001548F;/* Referenced by: '<S8>/Model' */

/* Gain to convert raw input to engineering units */
__attribute__ ((section (".cal_data"))) real32_T PhaCurCOfs_C = -3.06F;/* Referenced by: '<S8>/Model' */

/* Offset to convert raw input to engineering units */
__attribute__ ((section (".cal_data"))) boolean_T PhaCurDDialEna_C = false;/* Referenced by: '<S9>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) real32_T PhaCurDDialVal_C = 0.0F;/* Referenced by: '<S9>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) real32_T PhaCurDTarVal_C = 0.0F;/* Referenced by: '<S21>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) boolean_T PhaCurQDialEna_C = false;/* Referenced by: '<S9>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) real32_T PhaCurQDialVal_C = 0.0F;/* Referenced by: '<S9>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) boolean_T PhaCurQTarDialEna_C = true;/* Referenced by: '<S21>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) real32_T PhaCurQTarDialVal_C = 0.0F;/* Referenced by: '<S21>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) boolean_T PhaPwmEnaDialEna_C = true;/* Referenced by: '<S17>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) boolean_T PhaPwmEnaDialVal_C = false;/* Referenced by: '<S17>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) boolean_T PhaUACmdDialEna_C = false;/* Referenced by: '<S12>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) real32_T PhaUACmdDialVal_C = 0.0F;/* Referenced by: '<S12>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) real32_T PhaUAFilTiCon_C = 0.0F;/* Referenced by: '<S8>/Model' */

/* Low pass filter time constant for signal input processing */
__attribute__ ((section (".cal_data"))) real32_T PhaUAGain_C = 0.0152F;/* Referenced by: '<S8>/Model' */

/* Gain to convert raw input to engineering units */
__attribute__ ((section (".cal_data"))) real32_T PhaUAOfs_C = 0.0F;/* Referenced by: '<S8>/Model' */

/* Offset to convert raw input to engineering units */
__attribute__ ((section (".cal_data"))) boolean_T PhaUBCmdDialEna_C = false;/* Referenced by: '<S12>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) real32_T PhaUBCmdDialVal_C = 0.0F;/* Referenced by: '<S12>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) real32_T PhaUBFilTiCon_C = 0.0F;/* Referenced by: '<S8>/Model' */

/* Low pass filter time constant for signal input processing */
__attribute__ ((section (".cal_data"))) real32_T PhaUBGain_C = 0.0152F;/* Referenced by: '<S8>/Model' */

/* Gain to convert raw input to engineering units */
__attribute__ ((section (".cal_data"))) real32_T PhaUBOfs_C = 0.0F;/* Referenced by: '<S8>/Model' */

/* Offset to convert raw input to engineering units */
__attribute__ ((section (".cal_data"))) boolean_T PhaUCCmdDialEna_C = false;/* Referenced by: '<S12>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) real32_T PhaUCCmdDialVal_C = 0.0F;/* Referenced by: '<S12>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) real32_T PhaUCFilTiCon_C = 0.0F;/* Referenced by: '<S8>/Model' */

/* Low pass filter time constant for signal input processing */
__attribute__ ((section (".cal_data"))) real32_T PhaUCGain_C = 0.0152F;/* Referenced by: '<S8>/Model' */

/* Gain to convert raw input to engineering units */
__attribute__ ((section (".cal_data"))) real32_T PhaUCOfs_C = 0.0F;/* Referenced by: '<S8>/Model' */

/* Offset to convert raw input to engineering units */
__attribute__ ((section (".cal_data"))) real32_T PhaUDAntiWindupGain_C = 25.0F;/* Referenced by: '<S10>/Model' */

/* Gain used to attenuate the integrated error when the output voltage command is saturated to avoid integral windup  */
__attribute__ ((section (".cal_data"))) boolean_T PhaUDCmdDialEna_C = false;/* Referenced by: '<S10>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) real32_T PhaUDCmdDialVal_C = 0.0F;/* Referenced by: '<S10>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) real32_T PhaUDCmdOpenLoop_C = 0.0F;/* Referenced by: '<S10>/Model' */

/* The d-axis phase voltage command in open loop mode */
__attribute__ ((section (".cal_data"))) real32_T PhaUDGainI_C = 50.0F;/* Referenced by: '<S10>/Model' */

/* Integral control gain for d-axis current control */
__attribute__ ((section (".cal_data"))) real32_T PhaUDGainP_C = 0.5F;/* Referenced by: '<S10>/Model' */

/* Proportional control gain for d-axis current control */
__attribute__ ((section (".cal_data"))) real32_T PhaUMaxVal_C = 12.0F;/* Referenced by: '<S10>/Model' */

/* The smallest value the maximum phase voltage is allowed to take on for current control calculations */
__attribute__ ((section (".cal_data"))) real32_T PhaUQAntiWindupGain_C = 25.0F;/* Referenced by: '<S10>/Model' */

/* Gain used to attenuate the integrated error when the output voltage command is saturated to avoid integral windup */
__attribute__ ((section (".cal_data"))) boolean_T PhaUQCmdDialEna_C = false;/* Referenced by: '<S10>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) real32_T PhaUQCmdDialVal_C = 0.0F;/* Referenced by: '<S10>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) real32_T PhaUQCmdOpenLoop_C = 2.0F;/* Referenced by: '<S10>/Model' */

/* The q-axis phase voltage command in open loop mode */
__attribute__ ((section (".cal_data"))) real32_T PhaUQGainI_C = 50.0F;/* Referenced by: '<S10>/Model' */

/* Integral control gain for q-axis current control */
__attribute__ ((section (".cal_data"))) real32_T PhaUQGainP_C = 0.5F;/* Referenced by: '<S10>/Model' */

/* Proportional control gain for q-axis current control */
__attribute__ ((section (".cal_data"))) real32_T PlsOffTi_C = 0.2F;/* Referenced by: '<S17>/Model' */

/* The time the LED is off between two pulses */
__attribute__ ((section (".cal_data"))) real32_T PlsOnTi_C = 0.2F;/* Referenced by: '<S17>/Model' */

/* The time the LED is on during a pulse */
__attribute__ ((section (".cal_data"))) boolean_T PwrCmdDialEna_C = true;/* Referenced by: '<S15>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) boolean_T PwrCmdDialVal_C = false;/* Referenced by: '<S15>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) boolean_T RedLedDialEna_C = false;/* Referenced by: '<S17>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) boolean_T RedLedDialVal_C = false;/* Referenced by: '<S17>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) boolean_T RedLedIvt_C = true;/* Referenced by: '<S17>/Model' */

/* Invert the LED command */
__attribute__ ((section (".cal_data"))) int16_T ReloadRegisterMax_C = 12000;/* Referenced by: '<S11>/Model' */

/* The maximum value of the register used by the hardware PWM generator */
__attribute__ ((section (".cal_data"))) real32_T ResolverCosFilTiCon_C = 0.0F;/* Referenced by: '<S8>/Model' */

/* Low pass filter time constant for signal input processing */
__attribute__ ((section (".cal_data"))) real32_T ResolverCosGain_C = 0.0F;/* Referenced by: '<S8>/Model' */

/* Gain to convert raw input to engineering units */
__attribute__ ((section (".cal_data"))) real32_T ResolverCosOfs_C = 0.0F;/* Referenced by: '<S8>/Model' */

/* Offset to convert raw input to engineering units */
__attribute__ ((section (".cal_data"))) boolean_T ResolverExctEna_C = false;/* Referenced by: '<S17>/Model' */

/* Command to enable resolver excitation waveform generation: 0 = disable, 1 = enable. */
__attribute__ ((section (".cal_data"))) boolean_T ResolverSinCosDialEna_C = true;/* Referenced by: '<S8>/Model' */

/* Signal override enable */
__attribute__ ((section (".cal_data"))) real32_T ResolverSinCosDialVal_CA[2] = {
  0.0F, 1.0F } ;                       /* Referenced by: '<S8>/Model' */

/* Signal override value */
__attribute__ ((section (".cal_data"))) real32_T ResolverSinFilTiCon_C = 0.0F;/* Referenced by: '<S8>/Model' */

/* Low pass filter time constant for signal input processing */
__attribute__ ((section (".cal_data"))) real32_T ResolverSinGain_C = 0.0F;/* Referenced by: '<S8>/Model' */

/* Gain to convert raw input to engineering units */
__attribute__ ((section (".cal_data"))) real32_T ResolverSinOfs_C = 0.0F;/* Referenced by: '<S8>/Model' */

/* Offset to convert raw input to engineering units */
__attribute__ ((section (".cal_data"))) real32_T StatorInductanceD_C = 0.00018F;/* Referenced by: '<S10>/Model' */

/* The motor stator d-axis inductance */
__attribute__ ((section (".cal_data"))) real32_T StatorInductanceQ_C = 0.00018F;/* Referenced by: '<S10>/Model' */

/* The motor stator q-axis inductance */
__attribute__ ((section (".cal_data"))) boolean_T SwPwrPwmEna_C = false;/* Referenced by: '<S17>/Model' */

/* Enable SwPwr modulation output: 0 = disable, 1 = enable. */
__attribute__ ((section (".cal_data"))) boolean_T WakeRetry_C = false;/* Referenced by: '<S15>/Model' */

/* Flag used to force the drive to try and rewake the board by activiting the power command */
__attribute__ ((section (".cal_data"))) real32_T WakeTout_C = 1.0F;/* Referenced by: '<S15>/Model' */

/* The amount of time the control waits for the power activation signal before shutting off the power command and terminating the wake attempt */
__attribute__ ((section (".cal_data"))) boolean_T YellowLedCmd_C = true;/* Referenced by: '<S17>/Model' */

/* Yellow LED activation command. */

/* Block signals (default storage) */
B_P2319ASW01_T P2319ASW01_B;

/* Block states (default storage) */
DW_P2319ASW01_T P2319ASW01_DW;

/* External inputs (root inport signals with default storage) */
ExtU_P2319ASW01_T P2319ASW01_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_P2319ASW01_T P2319ASW01_Y;

/* Real-time model */
static RT_MODEL_P2319ASW01_T P2319ASW01_M_;
RT_MODEL_P2319ASW01_T *const P2319ASW01_M = &P2319ASW01_M_;

/* System initialize for function-call system: '<Root>/Torque_Speed_Control' */
void P2319ASW01_Torque_Speed_Control_Init(void)
{
  /* SystemInitialize for ModelReference: '<S18>/Model' */
  MEDINP_Init();
}

/* Start for function-call system: '<Root>/Torque_Speed_Control' */
void P2319ASW01_Torque_Speed_Control_Start(void)
{
  /* Start for ModelReference: '<S18>/Model' */
  MEDINP_Start();
}

/* Output and update for function-call system: '<Root>/Torque_Speed_Control' */
void P2319ASW01_Torque_Speed_Control(void)
{
  int32_T i;
  for (i = 0; i < 8; i++) {
    /* SignalConversion generated from: '<S18>/Model' incorporates:
     *  Inport: '<Root>/ASWIN_TqSpdCtrl'
     */
    ASWIN_McuReqDa[i] = P2319ASW01_U.ASWIN_TqSpdCtrl_g.ASWIN_McuReqDa[i];
  }

  /* SignalConversion generated from: '<S18>/Model' incorporates:
   *  Inport: '<Root>/ASWIN_TqSpdCtrl'
   */
  ASWIN_McuReqCt = P2319ASW01_U.ASWIN_TqSpdCtrl_g.ASWIN_McuReqCt;

  /* ModelReference: '<S18>/Model' */
  MEDINP();

  /* ModelReference: '<S19>/Model' */
  MEDOUP(&P2319ASW01_B.HvBusCur_a, &P2319ASW01_B.HvBusU_g,
         &P2319ASW01_B.PhaCurQ_f, &P2319ASW01_B.MotSpd_m, &P2319ASW01_B.DrvMod_n);

  /* ModelReference: '<S20>/Model' incorporates:
   *  UnitDelay: '<S20>/Unit Delay'
   */
  SPDCTL(&P2319ASW01_B.MotSpd_m, &P2319ASW01_B.DrvMod_n, &MotSpdReqCan,
         &P2319ASW01_DW.UnitDelay_DSTATE);

  /* ModelReference: '<S21>/Model' */
  TRQCTL(&MotTqCmdSpdCtl, &P2319ASW01_B.DrvMod_n, &MotTqReqCan,
         &P2319ASW01_B.BdT1_f, &P2319ASW01_B.BdT2_b, &P2319ASW01_B.MotSpd_m);

  /* Update for UnitDelay: '<S20>/Unit Delay' */
  P2319ASW01_DW.UnitDelay_DSTATE = MotTqMax;
}

/* System initialize for function-call system: '<Root>/Current_Control' */
void P2319ASW01_Current_Control_Init(void)
{
  /* SystemInitialize for ModelReference: '<S13>/Model' */
  POSINP_Init();
}

/* Output and update for function-call system: '<Root>/Current_Control' */
void P2319ASW01_Current_Control(void)
{
  /* SignalConversion generated from: '<S8>/Model' incorporates:
   *  Inport: '<Root>/ASWIN_CurCtrl'
   */
  ASWIN_HvBusU = P2319ASW01_U.ASWIN_CurCtrl_k.ASWIN_HvBusU;

  /* SignalConversion generated from: '<S8>/Model' incorporates:
   *  Inport: '<Root>/ASWIN_CurCtrl'
   */
  ASWIN_PhaCurA = P2319ASW01_U.ASWIN_CurCtrl_k.ASWIN_PhaCurA;

  /* SignalConversion generated from: '<S8>/Model' incorporates:
   *  Inport: '<Root>/ASWIN_CurCtrl'
   */
  ASWIN_PhaCurB = P2319ASW01_U.ASWIN_CurCtrl_k.ASWIN_PhaCurB;

  /* SignalConversion generated from: '<S8>/Model' incorporates:
   *  Inport: '<Root>/ASWIN_CurCtrl'
   */
  ASWIN_PhaCurC = P2319ASW01_U.ASWIN_CurCtrl_k.ASWIN_PhaCurC;

  /* SignalConversion generated from: '<S8>/Model' incorporates:
   *  Inport: '<Root>/ASWIN_CurCtrl'
   */
  ASWIN_HvBusCur = P2319ASW01_U.ASWIN_CurCtrl_k.ASWIN_HvBusCur;

  /* SignalConversion generated from: '<S8>/Model' incorporates:
   *  Inport: '<Root>/ASWIN_CurCtrl'
   */
  ASWIN_PhaUA = P2319ASW01_U.ASWIN_CurCtrl_k.ASWIN_PhaUA;

  /* SignalConversion generated from: '<S8>/Model' incorporates:
   *  Inport: '<Root>/ASWIN_CurCtrl'
   */
  ASWIN_PhaUB = P2319ASW01_U.ASWIN_CurCtrl_k.ASWIN_PhaUB;

  /* SignalConversion generated from: '<S8>/Model' incorporates:
   *  Inport: '<Root>/ASWIN_CurCtrl'
   */
  ASWIN_PhaUC = P2319ASW01_U.ASWIN_CurCtrl_k.ASWIN_PhaUC;

  /* SignalConversion generated from: '<S8>/Model' incorporates:
   *  Inport: '<Root>/ASWIN_CurCtrl'
   */
  ASWIN_ResolverSin = P2319ASW01_U.ASWIN_CurCtrl_k.ASWIN_ResolverSin;

  /* SignalConversion generated from: '<S8>/Model' incorporates:
   *  Inport: '<Root>/ASWIN_CurCtrl'
   */
  ASWIN_ResolverCos = P2319ASW01_U.ASWIN_CurCtrl_k.ASWIN_ResolverCos;

  /* ModelReference: '<S8>/Model' */
  ADCINP();

  /* SignalConversion generated from: '<S13>/Model' incorporates:
   *  Inport: '<Root>/ASWIN_CurCtrl'
   */
  ASWIN_EncoderCt = P2319ASW01_U.ASWIN_CurCtrl_k.ASWIN_EncoderCt;

  /* SignalConversion generated from: '<S13>/Model' incorporates:
   *  Inport: '<Root>/ASWIN_CurCtrl'
   */
  ASWIN_EncoderZ = P2319ASW01_U.ASWIN_CurCtrl_k.ASWIN_EncoderZ;

  /* ModelReference: '<S13>/Model' */
  POSINP(&P2319ASW01_B.DrvMod_i, &P2319ASW01_B.MotSpdReqCan_j, &ResolverSinCos[0]);

  /* ModelReference: '<S14>/Model' */
  POSTRG(&MotPosnMag);

  /* ModelReference: '<S9>/Model' */
  CLAPAR(&PhaCurA, &PhaCurB, &PhaCurC, &MotPosnTrig[0]);

  /* ModelReference: '<S10>/Model' */
  CURCTL(&PhaCurD, &P2319ASW01_B.PhaCurDTar_m, &HvBusU, &P2319ASW01_B.DrvMod_i,
         &PhaCurQ, &P2319ASW01_B.PhaCurQTar_n, &MotSpdMag);

  /* ModelReference: '<S12>/Model' */
  INVCPA(&PhaUDCmd, &PhaUQCmd, &MotPosnTrig[0]);

  /* ModelReference: '<S11>/Model' */
  GATOUP(&PhaUACmd, &PhaUBCmd, &PhaUCCmd, &HvBusU);
}

/* System initialize for function-call system: '<Root>/Supervisor' */
void P2319ASW01_Supervisor_Init(void)
{
  /* SystemInitialize for ModelReference: '<S16>/Model' */
  SLWINP_Init();
}

/* Output and update for function-call system: '<Root>/Supervisor' */
void P2319ASW01_Supervisor(void)
{
  /* SignalConversion generated from: '<S16>/Model' incorporates:
   *  Inport: '<Root>/ASWIN_Supervisor'
   */
  ASWIN_MaiPwrSts = P2319ASW01_U.ASWIN_Supervisor_g.ASWIN_MaiPwrSts;

  /* SignalConversion generated from: '<S16>/Model' incorporates:
   *  Inport: '<Root>/ASWIN_Supervisor'
   */
  ASWIN_AuxPwrSts = P2319ASW01_U.ASWIN_Supervisor_g.ASWIN_AuxPwrSts;

  /* SignalConversion generated from: '<S16>/Model' incorporates:
   *  Inport: '<Root>/ASWIN_Supervisor'
   */
  ASWIN_BdT1 = P2319ASW01_U.ASWIN_Supervisor_g.ASWIN_BdT1;

  /* SignalConversion generated from: '<S16>/Model' incorporates:
   *  Inport: '<Root>/ASWIN_Supervisor'
   */
  ASWIN_BdT2 = P2319ASW01_U.ASWIN_Supervisor_g.ASWIN_BdT2;

  /* SignalConversion generated from: '<S16>/Model' incorporates:
   *  Inport: '<Root>/ASWIN_Supervisor'
   */
  ASWIN_McuURef = P2319ASW01_U.ASWIN_Supervisor_g.ASWIN_McuURef;

  /* SignalConversion generated from: '<S16>/Model' incorporates:
   *  Inport: '<Root>/ASWIN_Supervisor'
   */
  ASWIN_McuT = P2319ASW01_U.ASWIN_Supervisor_g.ASWIN_McuT;

  /* SignalConversion generated from: '<S16>/Model' incorporates:
   *  Inport: '<Root>/ASWIN_Supervisor'
   */
  ASWIN_McuUBat = P2319ASW01_U.ASWIN_Supervisor_g.ASWIN_McuUBat;

  /* ModelReference: '<S16>/Model' */
  SLWINP();

  /* ModelReference: '<S15>/Model' */
  MODCTL(&P2319ASW01_B.DrvModReq_j, &P2319ASW01_B.MotSpd_e,
         &P2319ASW01_B.MotSpdReqCan_g, &P2319ASW01_B.MotTqReqCan_a, &MaiPwrAcv,
         &AuxPwrAcv);

  /* ModelReference: '<S17>/Model' */
  SLWOUP(&DrvMod, &BdT1, &BdT2, &McuT);
}

/* Model step function for TID0 */
void P2319ASW01_step0(void)            /* Sample time: [0.0001s, 0.0s] */
{
  /* Update the flag to indicate when data transfers from
   *  Sample time: [0.0001s, 0.0s] to Sample time: [0.01s, 0.0s]  */
  P2319ASW01_M->Timing.RateInteraction.b_TID0_1 =
    (P2319ASW01_M->Timing.RateInteraction.TID0_1 == 0);
  (P2319ASW01_M->Timing.RateInteraction.TID0_1)++;
  if ((P2319ASW01_M->Timing.RateInteraction.TID0_1) > 99) {
    P2319ASW01_M->Timing.RateInteraction.TID0_1 = 0;
  }

  /* Update the flag to indicate when data transfers from
   *  Sample time: [0.0001s, 0.0s] to Sample time: [0.1s, 0.0s]  */
  P2319ASW01_M->Timing.RateInteraction.b_TID0_2 =
    (P2319ASW01_M->Timing.RateInteraction.TID0_2 == 0);
  (P2319ASW01_M->Timing.RateInteraction.TID0_2)++;
  if ((P2319ASW01_M->Timing.RateInteraction.TID0_2) > 999) {
    P2319ASW01_M->Timing.RateInteraction.TID0_2 = 0;
  }

  /* RateTransition generated from: '<S2>/Rate Transition' */
  if (P2319ASW01_M->Timing.RateInteraction.TID0_2 == 1) {
    P2319ASW01_B.DrvMod_i = P2319ASW01_DW.RateTransition_6_Buffer0;
  }

  /* End of RateTransition generated from: '<S2>/Rate Transition' */

  /* RateTransition generated from: '<S2>/Rate Transition4' */
  if (P2319ASW01_M->Timing.RateInteraction.TID0_1 == 1) {
    P2319ASW01_B.MotSpdReqCan_j = P2319ASW01_DW.RateTransition4_3_Buffer0;
    P2319ASW01_B.PhaCurQTar_n = P2319ASW01_DW.RateTransition4_5_Buffer0;
    P2319ASW01_B.PhaCurDTar_m = P2319ASW01_DW.RateTransition4_6_Buffer0;
  }

  /* End of RateTransition generated from: '<S2>/Rate Transition4' */

  /* S-Function (fcgen): '<Root>/Function-Call Generator1' incorporates:
   *  SubSystem: '<Root>/Current_Control'
   */
  P2319ASW01_Current_Control();

  /* End of Outputs for S-Function (fcgen): '<Root>/Function-Call Generator1' */

  /* BusCreator generated from: '<Root>/ASWOUT_CurCtrl' incorporates:
   *  Outport: '<Root>/ASWOUT_CurCtrl'
   */
  P2319ASW01_Y.ASWOUT_CurCtrl_l.ASWOUT_PhaAPwmDc = ASWOUT_PhaAPwmDc;
  P2319ASW01_Y.ASWOUT_CurCtrl_l.ASWOUT_PhaBPwmDc = ASWOUT_PhaBPwmDc;
  P2319ASW01_Y.ASWOUT_CurCtrl_l.ASWOUT_PhaCPwmDc = ASWOUT_PhaCPwmDc;

  /* RateTransition generated from: '<S2>/Rate Transition3' */
  if (P2319ASW01_M->Timing.RateInteraction.TID0_1 == 1) {
    P2319ASW01_DW.RateTransition3_1_Buffer = HvBusU;
    P2319ASW01_DW.RateTransition3_12_Buffer = PhaCurQ;
    P2319ASW01_DW.RateTransition3_5_Buffer = HvBusCur;
    P2319ASW01_DW.RateTransition3_9_Buffer = MotSpd;
  }

  /* End of RateTransition generated from: '<S2>/Rate Transition3' */

  /* RateTransition generated from: '<S2>/Rate Transition5' */
  if (P2319ASW01_M->Timing.RateInteraction.TID0_2 == 1) {
    P2319ASW01_DW.RateTransition5_9_Buffer = MotSpd;
  }

  /* End of RateTransition generated from: '<S2>/Rate Transition5' */
}

/* Model step function for TID1 */
void P2319ASW01_step1(void)            /* Sample time: [0.01s, 0.0s] */
{
  int32_T i;

  /* Update the flag to indicate when data transfers from
   *  Sample time: [0.01s, 0.0s] to Sample time: [0.1s, 0.0s]  */
  P2319ASW01_M->Timing.RateInteraction.b_TID1_2 =
    (P2319ASW01_M->Timing.RateInteraction.TID1_2 == 0);
  (P2319ASW01_M->Timing.RateInteraction.TID1_2)++;
  if ((P2319ASW01_M->Timing.RateInteraction.TID1_2) > 9) {
    P2319ASW01_M->Timing.RateInteraction.TID1_2 = 0;
  }

  /* RateTransition generated from: '<S2>/Rate Transition1' */
  if (P2319ASW01_M->Timing.RateInteraction.TID1_2 == 1) {
    P2319ASW01_B.BdT1_f = P2319ASW01_DW.RateTransition1_3_Buffer0;
    P2319ASW01_B.BdT2_b = P2319ASW01_DW.RateTransition1_4_Buffer0;
    P2319ASW01_B.DrvMod_n = P2319ASW01_DW.RateTransition1_6_Buffer0;
  }

  /* End of RateTransition generated from: '<S2>/Rate Transition1' */

  /* RateTransition generated from: '<S2>/Rate Transition3' */
  P2319ASW01_B.HvBusU_g = P2319ASW01_DW.RateTransition3_1_Buffer;

  /* RateTransition generated from: '<S2>/Rate Transition3' */
  P2319ASW01_B.HvBusCur_a = P2319ASW01_DW.RateTransition3_5_Buffer;

  /* RateTransition generated from: '<S2>/Rate Transition3' */
  P2319ASW01_B.MotSpd_m = P2319ASW01_DW.RateTransition3_9_Buffer;

  /* RateTransition generated from: '<S2>/Rate Transition3' */
  P2319ASW01_B.PhaCurQ_f = P2319ASW01_DW.RateTransition3_12_Buffer;

  /* S-Function (fcgen): '<Root>/Function-Call Generator' incorporates:
   *  SubSystem: '<Root>/Torque_Speed_Control'
   */
  P2319ASW01_Torque_Speed_Control();

  /* End of Outputs for S-Function (fcgen): '<Root>/Function-Call Generator' */

  /* Outport: '<Root>/ASWOUT_TqSpdCtrl' incorporates:
   *  BusCreator generated from: '<Root>/ASWOUT_TqSpdCtrl'
   */
  for (i = 0; i < 8; i++) {
    P2319ASW01_Y.ASWOUT_TqSpdCtrl_h.ASWOUT_McuData1Da[i] = ASWOUT_McuData1Da[i];
  }

  /* End of Outport: '<Root>/ASWOUT_TqSpdCtrl' */

  /* RateTransition generated from: '<S2>/Rate Transition2' incorporates:
   *  ModelReference: '<S18>/Model'
   */
  if (P2319ASW01_M->Timing.RateInteraction.TID1_2 == 1) {
    P2319ASW01_DW.RateTransition2_1_Buffer = DrvModReq;
    P2319ASW01_DW.RateTransition2_2_Buffer = MotTqReqCan;
    P2319ASW01_DW.RateTransition2_3_Buffer = MotSpdReqCan;
  }

  /* End of RateTransition generated from: '<S2>/Rate Transition2' */

  /* RateTransition generated from: '<S2>/Rate Transition4' */
  P2319ASW01_DW.RateTransition4_3_Buffer0 = MotSpdReqCan;

  /* RateTransition generated from: '<S2>/Rate Transition4' */
  P2319ASW01_DW.RateTransition4_5_Buffer0 = PhaCurQTar;

  /* RateTransition generated from: '<S2>/Rate Transition4' */
  P2319ASW01_DW.RateTransition4_6_Buffer0 = PhaCurDTar;
}

/* Model step function for TID2 */
void P2319ASW01_step2(void)            /* Sample time: [0.1s, 0.0s] */
{
  int32_T i;

  /* RateTransition generated from: '<S2>/Rate Transition2' */
  P2319ASW01_B.DrvModReq_j = P2319ASW01_DW.RateTransition2_1_Buffer;

  /* RateTransition generated from: '<S2>/Rate Transition2' */
  P2319ASW01_B.MotTqReqCan_a = P2319ASW01_DW.RateTransition2_2_Buffer;

  /* RateTransition generated from: '<S2>/Rate Transition2' */
  P2319ASW01_B.MotSpdReqCan_g = P2319ASW01_DW.RateTransition2_3_Buffer;

  /* RateTransition generated from: '<S2>/Rate Transition5' */
  P2319ASW01_B.MotSpd_e = P2319ASW01_DW.RateTransition5_9_Buffer;

  /* S-Function (fcgen): '<Root>/Function-Call Generator2' incorporates:
   *  SubSystem: '<Root>/Supervisor'
   */
  P2319ASW01_Supervisor();

  /* End of Outputs for S-Function (fcgen): '<Root>/Function-Call Generator2' */

  /* Outport: '<Root>/ASWOUT_Supervisor' incorporates:
   *  BusCreator generated from: '<Root>/ASWOUT_Supervisor'
   */
  P2319ASW01_Y.ASWOUT_Supervisor_h.ASWOUT_GreenLed = ASWOUT_GreenLed;
  P2319ASW01_Y.ASWOUT_Supervisor_h.ASWOUT_RedLed = ASWOUT_RedLed;
  P2319ASW01_Y.ASWOUT_Supervisor_h.ASWOUT_YellowLed = ASWOUT_YellowLed;
  P2319ASW01_Y.ASWOUT_Supervisor_h.ASWOUT_ResolverExctEna =
    ASWOUT_ResolverExctEna;
  for (i = 0; i < 8; i++) {
    P2319ASW01_Y.ASWOUT_Supervisor_h.ASWOUT_McuData2Da[i] = ASWOUT_McuData2Da[i];
  }

  P2319ASW01_Y.ASWOUT_Supervisor_h.ASWOUT_CanPwrPwmEna = ASWOUT_CanPwrPwmEna;
  P2319ASW01_Y.ASWOUT_Supervisor_h.ASWOUT_InPwrPwmEna = ASWOUT_InPwrPwmEna;
  P2319ASW01_Y.ASWOUT_Supervisor_h.ASWOUT_MtrPwrPwmEna = ASWOUT_MtrPwrPwmEna;
  P2319ASW01_Y.ASWOUT_Supervisor_h.ASWOUT_SwPwrPwmEna = ASWOUT_SwPwrPwmEna;
  P2319ASW01_Y.ASWOUT_Supervisor_h.ASWOUT_PhaPwmEna = ASWOUT_PhaPwmEna;

  /* End of Outport: '<Root>/ASWOUT_Supervisor' */

  /* RateTransition generated from: '<S2>/Rate Transition' incorporates:
   *  ModelReference: '<S15>/Model'
   */
  P2319ASW01_DW.RateTransition_6_Buffer0 = DrvMod;

  /* RateTransition generated from: '<S2>/Rate Transition1' */
  P2319ASW01_DW.RateTransition1_3_Buffer0 = BdT1;

  /* RateTransition generated from: '<S2>/Rate Transition1' */
  P2319ASW01_DW.RateTransition1_4_Buffer0 = BdT2;

  /* RateTransition generated from: '<S2>/Rate Transition1' incorporates:
   *  ModelReference: '<S15>/Model'
   */
  P2319ASW01_DW.RateTransition1_6_Buffer0 = DrvMod;
}

/* Model initialize function */
void P2319ASW01_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* Set task counter limit used by the static main program */
  (P2319ASW01_M)->Timing.TaskCounters.cLimit[0] = 1;
  (P2319ASW01_M)->Timing.TaskCounters.cLimit[1] = 100;
  (P2319ASW01_M)->Timing.TaskCounters.cLimit[2] = 1000;

  /* external inputs */
  (void)memset(&P2319ASW01_U, 0, sizeof(ExtU_P2319ASW01_T));

  /* external outputs */
  (void)memset(&P2319ASW01_Y, 0, sizeof(ExtY_P2319ASW01_T));

  /* Model Initialize function for ModelReference Block: '<S8>/Model' */
  ADCINP_initialize(rtmGetErrorStatusPointer(P2319ASW01_M));

  /* Model Initialize function for ModelReference Block: '<S9>/Model' */
  CLAPAR_initialize(rtmGetErrorStatusPointer(P2319ASW01_M));

  /* Model Initialize function for ModelReference Block: '<S10>/Model' */
  CURCTL_initialize(rtmGetErrorStatusPointer(P2319ASW01_M));

  /* Model Initialize function for ModelReference Block: '<S11>/Model' */
  GATOUP_initialize(rtmGetErrorStatusPointer(P2319ASW01_M));

  /* Model Initialize function for ModelReference Block: '<S12>/Model' */
  INVCPA_initialize(rtmGetErrorStatusPointer(P2319ASW01_M));

  /* Model Initialize function for ModelReference Block: '<S13>/Model' */
  POSINP_initialize(rtmGetErrorStatusPointer(P2319ASW01_M));

  /* Model Initialize function for ModelReference Block: '<S14>/Model' */
  POSTRG_initialize(rtmGetErrorStatusPointer(P2319ASW01_M));

  /* Model Initialize function for ModelReference Block: '<S15>/Model' */
  MODCTL_initialize(rtmGetErrorStatusPointer(P2319ASW01_M));

  /* Model Initialize function for ModelReference Block: '<S16>/Model' */
  SLWINP_initialize(rtmGetErrorStatusPointer(P2319ASW01_M));

  /* Model Initialize function for ModelReference Block: '<S17>/Model' */
  SLWOUP_initialize(rtmGetErrorStatusPointer(P2319ASW01_M));

  /* Model Initialize function for ModelReference Block: '<S18>/Model' */
  MEDINP_initialize(rtmGetErrorStatusPointer(P2319ASW01_M));

  /* Model Initialize function for ModelReference Block: '<S19>/Model' */
  MEDOUP_initialize(rtmGetErrorStatusPointer(P2319ASW01_M));

  /* Model Initialize function for ModelReference Block: '<S20>/Model' */
  SPDCTL_initialize(rtmGetErrorStatusPointer(P2319ASW01_M));

  /* Model Initialize function for ModelReference Block: '<S21>/Model' */
  TRQCTL_initialize(rtmGetErrorStatusPointer(P2319ASW01_M));

  /* Start for S-Function (fcgen): '<Root>/Function-Call Generator' incorporates:
   *  SubSystem: '<Root>/Torque_Speed_Control'
   */
  P2319ASW01_Torque_Speed_Control_Start();

  /* End of Start for S-Function (fcgen): '<Root>/Function-Call Generator' */

  /* SystemInitialize for S-Function (fcgen): '<Root>/Function-Call Generator1' incorporates:
   *  SubSystem: '<Root>/Current_Control'
   */
  P2319ASW01_Current_Control_Init();

  /* End of SystemInitialize for S-Function (fcgen): '<Root>/Function-Call Generator1' */

  /* SystemInitialize for S-Function (fcgen): '<Root>/Function-Call Generator' incorporates:
   *  SubSystem: '<Root>/Torque_Speed_Control'
   */
  P2319ASW01_Torque_Speed_Control_Init();

  /* End of SystemInitialize for S-Function (fcgen): '<Root>/Function-Call Generator' */

  /* SystemInitialize for S-Function (fcgen): '<Root>/Function-Call Generator2' incorporates:
   *  SubSystem: '<Root>/Supervisor'
   */
  P2319ASW01_Supervisor_Init();

  /* End of SystemInitialize for S-Function (fcgen): '<Root>/Function-Call Generator2' */
}

/* Model terminate function */
void P2319ASW01_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
