/*
 * File: P2319ASW01.h
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

#ifndef RTW_HEADER_P2319ASW01_h_
#define RTW_HEADER_P2319ASW01_h_
#ifndef P2319ASW01_COMMON_INCLUDES_
#define P2319ASW01_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* P2319ASW01_COMMON_INCLUDES_ */

#include "P2319ASW01_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmCounterLimit
#define rtmCounterLimit(rtm, idx)      ((rtm)->Timing.TaskCounters.cLimit[(idx)])
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetErrorStatusPointer
#define rtmGetErrorStatusPointer(rtm)  ((const char_T **)(&((rtm)->errorStatus)))
#endif

#ifndef rtmStepTask
#define rtmStepTask(rtm, idx)          ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

#ifndef rtmTaskCounter
#define rtmTaskCounter(rtm, idx)       ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

/* Block signals (default storage) */
typedef struct {
  real32_T PhaCurQTar_n;               /* '<S2>/Rate Transition4' */
  real32_T PhaCurDTar_m;               /* '<S2>/Rate Transition4' */
  real32_T BdT1_f;                     /* '<S2>/Rate Transition1' */
  real32_T BdT2_b;                     /* '<S2>/Rate Transition1' */
  real32_T HvBusU_g;                   /* '<S2>/Rate Transition3' */
  real32_T HvBusCur_a;                 /* '<S2>/Rate Transition3' */
  real32_T PhaCurQ_f;                  /* '<S2>/Rate Transition3' */
  real32_T MotTqReqCan_a;              /* '<S2>/Rate Transition2' */
  int16_T MotSpdReqCan_j;              /* '<S2>/Rate Transition4' */
  int16_T MotSpd_m;                    /* '<S2>/Rate Transition3' */
  int16_T MotSpdReqCan_g;              /* '<S2>/Rate Transition2' */
  int16_T MotSpd_e;                    /* '<S2>/Rate Transition5' */
  DRIVEMODE DrvMod_i;                  /* '<S2>/Rate Transition' */
  DRIVEMODE DrvMod_n;                  /* '<S2>/Rate Transition1' */
  DRIVEMODE DrvModReq_j;               /* '<S2>/Rate Transition2' */
} B_P2319ASW01_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real32_T UnitDelay_DSTATE;           /* '<S20>/Unit Delay' */
  real32_T RateTransition4_5_Buffer0;  /* '<S2>/Rate Transition4' */
  real32_T RateTransition4_6_Buffer0;  /* '<S2>/Rate Transition4' */
  real32_T RateTransition3_1_Buffer;   /* '<S2>/Rate Transition3' */
  real32_T RateTransition3_12_Buffer;  /* '<S2>/Rate Transition3' */
  real32_T RateTransition3_5_Buffer;   /* '<S2>/Rate Transition3' */
  real32_T RateTransition1_3_Buffer0;  /* '<S2>/Rate Transition1' */
  real32_T RateTransition1_4_Buffer0;  /* '<S2>/Rate Transition1' */
  real32_T RateTransition2_2_Buffer;   /* '<S2>/Rate Transition2' */
  int16_T RateTransition4_3_Buffer0;   /* '<S2>/Rate Transition4' */
  int16_T RateTransition3_9_Buffer;    /* '<S2>/Rate Transition3' */
  int16_T RateTransition5_9_Buffer;    /* '<S2>/Rate Transition5' */
  int16_T RateTransition2_3_Buffer;    /* '<S2>/Rate Transition2' */
  DRIVEMODE RateTransition_6_Buffer0;  /* '<S2>/Rate Transition' */
  DRIVEMODE RateTransition1_6_Buffer0; /* '<S2>/Rate Transition1' */
  DRIVEMODE RateTransition2_1_Buffer;  /* '<S2>/Rate Transition2' */
} DW_P2319ASW01_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  ASWIN_Supervisor ASWIN_Supervisor_g; /* '<Root>/ASWIN_Supervisor' */
  ASWIN_TqSpdCtrl ASWIN_TqSpdCtrl_g;   /* '<Root>/ASWIN_TqSpdCtrl' */
  ASWIN_CurCtrl ASWIN_CurCtrl_k;       /* '<Root>/ASWIN_CurCtrl' */
} ExtU_P2319ASW01_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  ASWOUT_Supervisor ASWOUT_Supervisor_h;/* '<Root>/ASWOUT_Supervisor' */
  ASWOUT_TqSpdCtrl ASWOUT_TqSpdCtrl_h; /* '<Root>/ASWOUT_TqSpdCtrl' */
  ASWOUT_CurCtrl ASWOUT_CurCtrl_l;     /* '<Root>/ASWOUT_CurCtrl' */
} ExtY_P2319ASW01_T;

/* Real-time Model Data Structure */
struct tag_RTM_P2319ASW01_T {
  const char_T *errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    struct {
      uint32_T TID[3];
      uint32_T cLimit[3];
    } TaskCounters;

    struct {
      uint32_T TID0_1;
      boolean_T b_TID0_1;
      uint32_T TID0_2;
      boolean_T b_TID0_2;
      uint32_T TID1_2;
      boolean_T b_TID1_2;
    } RateInteraction;
  } Timing;
};

/* Block signals (default storage) */
extern B_P2319ASW01_T P2319ASW01_B;

/* Block states (default storage) */
extern DW_P2319ASW01_T P2319ASW01_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_P2319ASW01_T P2319ASW01_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_P2319ASW01_T P2319ASW01_Y;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real32_T BdT1;                  /* '<S16>/Model'
                                        * Board temperature 1
                                        */
extern real32_T BdT2;                  /* '<S16>/Model'
                                        * Board temperature 2
                                        */
extern real32_T McuT;                  /* '<S16>/Model'
                                        * Microcontroller temperature
                                        */
extern real32_T HvBusU;                /* '<S8>/Model'
                                        * The DC bus voltage into the inverter
                                        */
extern real32_T PhaCurA;               /* '<S8>/Model'
                                        * Phase A current
                                        */
extern real32_T PhaCurB;               /* '<S8>/Model'
                                        * Phase B current
                                        */
extern real32_T PhaCurC;               /* '<S8>/Model'
                                        * Phase C current
                                        */
extern real32_T HvBusCur;              /* '<S8>/Model'
                                        * The DC bus current into the inverter
                                        */
extern real32_T ResolverSinCos[2];     /* '<S8>/Model'
                                        * Resolver sine and cosine signals.
                                        */
extern real32_T MotPosnMag;            /* '<S13>/Model'
                                        * The magnetic rotor position. Zero degrees represents the rotor magnetic field aligned with the stator's A phase.
                                        */
extern real32_T MotSpdMag;             /* '<S13>/Model'
                                        * The magnetic motor speed
                                        */
extern real32_T MotPosnTrig[6];        /* '<S14>/Model'
                                        * The results of the trig calculations that are used in the reference frame transforms
                                        */
extern real32_T PhaCurD;               /* '<S9>/Model'
                                        * The motor current in the rotating d axis direction (non-torque producing).
                                        */
extern real32_T PhaCurQ;               /* '<S9>/Model'
                                        * The motor current in the rotating q axis direction (torque producing).
                                        */
extern real32_T PhaUDCmd;              /* '<S10>/Model'
                                        * Commanded d-axis phase voltage
                                        */
extern real32_T PhaUQCmd;              /* '<S10>/Model'
                                        * Commanded q-axis phase voltage
                                        */
extern real32_T PhaUACmd;              /* '<S12>/Model'
                                        * Phase A voltage command
                                        */
extern real32_T PhaUBCmd;              /* '<S12>/Model'
                                        * Phase B voltage command
                                        */
extern real32_T PhaUCCmd;              /* '<S12>/Model'
                                        * Phase C voltage command
                                        */
extern real32_T MotTqReqCan;           /* '<S18>/Model'
                                        * The requested motor torque
                                        */
extern real32_T MotTqCmdSpdCtl;        /* '<S20>/Model'
                                        * The motor torque commanded by the motor speed controller
                                        */
extern real32_T PhaCurQTar;            /* '<S21>/Model'
                                        * The target q-axis current
                                        */
extern real32_T PhaCurDTar;            /* '<S21>/Model'
                                        * The target d-axis current
                                        */
extern real32_T MotTqMax;              /* '<S21>/Model'
                                        * The maximum motor torque after derates
                                        */
extern uint16_T ASWIN_BdT1;            /*
                                        * The raw ADC input value
                                        */
extern uint16_T ASWIN_BdT2;            /*
                                        * The raw ADC input value
                                        */
extern uint16_T ASWIN_McuURef;         /*
                                        * The raw ADC input value
                                        */
extern uint16_T ASWIN_McuT;            /*
                                        * The raw ADC input value
                                        */
extern uint16_T ASWIN_McuUBat;         /*
                                        * The raw ADC input value
                                        */
extern uint16_T ASWIN_HvBusU;          /*
                                        * The raw ADC input value
                                        */
extern uint16_T ASWIN_PhaCurA;         /*
                                        * The raw ADC input value
                                        */
extern uint16_T ASWIN_PhaCurB;         /*
                                        * The raw ADC input value
                                        */
extern uint16_T ASWIN_PhaCurC;         /*
                                        * The raw ADC input value
                                        */
extern uint16_T ASWIN_HvBusCur;        /*
                                        * The raw ADC input value
                                        */
extern uint16_T ASWIN_PhaUA;           /*
                                        * The raw ADC input value
                                        */
extern uint16_T ASWIN_PhaUB;           /*
                                        * The raw ADC input value
                                        */
extern uint16_T ASWIN_PhaUC;           /*
                                        * The raw ADC input value
                                        */
extern uint16_T ASWIN_ResolverSin;     /*
                                        * The raw ADC input value
                                        */
extern uint16_T ASWIN_ResolverCos;     /*
                                        * The raw ADC input value
                                        */
extern uint16_T ASWOUT_PhaAPwmDc;      /* '<S11>/Model'
                                        * The raw modulation command used by the hardware PWM generator
                                        */
extern uint16_T ASWOUT_PhaBPwmDc;      /* '<S11>/Model'
                                        * The raw modulation command used by the hardware PWM generator
                                        */
extern uint16_T ASWOUT_PhaCPwmDc;      /* '<S11>/Model'
                                        * The raw modulation command used by the hardware PWM generator
                                        */
extern int16_T ASWIN_EncoderCt;        /*
                                        * The raw encoder count input
                                        */
extern int16_T MotSpd;                 /* '<S13>/Model'
                                        * The mechanical motor speed
                                        */
extern int16_T MotSpdReqCan;           /* '<S18>/Model'
                                        * The requested motor speed
                                        */
extern uint8_T ASWOUT_McuData2Da[8];   /* '<S17>/Model'
                                        * The raw message data frame
                                        */
extern uint8_T ASWIN_McuReqDa[8];      /*
                                        * The raw message data frame
                                        */
extern uint8_T ASWIN_McuReqCt;         /*
                                        * The raw message counter used to indicate message freshness
                                        */
extern uint8_T ASWOUT_McuData1Da[8];   /* '<S19>/Model'
                                        * The raw message data frame
                                        */
extern boolean_T ASWIN_MaiPwrSts;      /*
                                        * The raw input value
                                        */
extern boolean_T ASWIN_AuxPwrSts;      /*
                                        * The raw input value
                                        */
extern boolean_T MaiPwrAcv;            /* '<S16>/Model'
                                        * Main power active flag
                                        */
extern boolean_T AuxPwrAcv;            /* '<S16>/Model'
                                        * Auxilary power active flag
                                        */
extern boolean_T PwrCmd;               /* '<S15>/Model'
                                        * The command to activate the auxilary power supplies
                                        */
extern boolean_T ASWOUT_GreenLed;      /* '<S17>/Model'
                                        * The raw output value
                                        */
extern boolean_T ASWOUT_RedLed;        /* '<S17>/Model'
                                        * The raw output value
                                        */
extern boolean_T ASWOUT_YellowLed;     /* '<S17>/Model'
                                        * The raw output value
                                        */
extern boolean_T ASWOUT_ResolverExctEna;/* '<S17>/Model'
                                         * The raw output value
                                         */
extern boolean_T ASWOUT_CanPwrPwmEna;  /* '<S17>/Model'
                                        * The raw output value
                                        */
extern boolean_T ASWOUT_InPwrPwmEna;   /* '<S17>/Model'
                                        * The raw output value
                                        */
extern boolean_T ASWOUT_MtrPwrPwmEna;  /* '<S17>/Model'
                                        * The raw output value
                                        */
extern boolean_T ASWOUT_SwPwrPwmEna;   /* '<S17>/Model'
                                        * The raw output value
                                        */
extern boolean_T ASWOUT_PhaPwmEna;     /* '<S17>/Model'
                                        * The raw modulation enable command used by the hardware PWM generator: 0 = disable, 1 = enable.
                                        */
extern boolean_T ASWIN_EncoderZ;       /*
                                        * The raw encoder z signal
                                        */
extern DRIVEMODE DrvMod;               /* '<S15>/Model'
                                        * The active drive mode
                                        */
extern DRIVEMODE DrvModReq;            /* '<S18>/Model'
                                        * The requested drive mode
                                        */

/* Model entry point functions */
extern void P2319ASW01_initialize(void);
extern void P2319ASW01_step0(void);
extern void P2319ASW01_step1(void);
extern void P2319ASW01_step2(void);
extern void P2319ASW01_terminate(void);

/* Exported data declaration */

/* Calibration memory section */
/* Declaration for custom storage class: Calibration */
extern __attribute__ ((section (".cal_data"))) real32_T AuxPwrAcvDebFall_C;/* Referenced by: '<S16>/Model' */

/* Falling edge debounce time for input processing */
extern __attribute__ ((section (".cal_data"))) real32_T AuxPwrAcvDebRisng_C;/* Referenced by: '<S16>/Model' */

/* Rising edge debounce time for input processing */
extern __attribute__ ((section (".cal_data"))) boolean_T AuxPwrAcvDialEna_C;/* Referenced by: '<S16>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) boolean_T AuxPwrAcvDialVal_C;/* Referenced by: '<S16>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) boolean_T AuxPwrStsIvt_C;/* Referenced by: '<S16>/Model' */

/* Invert the auxilary power status input */
extern __attribute__ ((section (".cal_data"))) boolean_T BdT1DialEna_C;/* Referenced by: '<S16>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T BdT1DialVal_C;/* Referenced by: '<S16>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T BdT1FilTiCon_C;/* Referenced by: '<S16>/Model' */

/* Low pass filter time constant for signal input processing */
extern __attribute__ ((section (".cal_data"))) real32_T BdT1Gain_C;/* Referenced by: '<S16>/Model' */

/* Gain to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T BdT1Ofs_C;/* Referenced by: '<S16>/Model' */

/* Offset to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) boolean_T BdT2DialEna_C;/* Referenced by: '<S16>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T BdT2DialVal_C;/* Referenced by: '<S16>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T BdT2FilTiCon_C;/* Referenced by: '<S16>/Model' */

/* Low pass filter time constant for signal input processing */
extern __attribute__ ((section (".cal_data"))) real32_T BdT2Gain_C;/* Referenced by: '<S16>/Model' */

/* Gain to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T BdT2Ofs_C;/* Referenced by: '<S16>/Model' */

/* Offset to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) boolean_T CanPwrPwmEna_C;/* Referenced by: '<S17>/Model' */

/* Enable CanPwr modulation output: 0 = disable, 1 = enable. */
extern __attribute__ ((section (".cal_data"))) boolean_T DrvModDialEna_C;/* Referenced by: '<S15>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) DRIVEMODE DrvModDialVal_C;/* Referenced by: '<S15>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) DRIVEMODE DrvModReqDft_C;/* Referenced by: '<S18>/Model' */

/* The default value used for this signal when the message has timedout */
extern __attribute__ ((section (".cal_data"))) boolean_T DrvModReqDialEna_C;/* Referenced by: '<S18>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) DRIVEMODE DrvModReqDialVal_C;/* Referenced by: '<S18>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) uint16_T EncoderCtPerRev_C;/* Referenced by: '<S13>/Model' */

/* The number of encoder counts per mechanical revolution */
extern __attribute__ ((section (".cal_data"))) real32_T EncoderOfs_C;/* Referenced by: '<S13>/Model' */

/* Offset used to align the encoder z signal with the true zero angle */
extern __attribute__ ((section (".cal_data"))) real32_T FluxLinkage_C;/* Referenced by: '<S10>/Model' */

/* The permanent magnet flux linkage of the motor */
extern __attribute__ ((section (".cal_data"))) boolean_T GreenLedDialEna_C;/* Referenced by: '<S17>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) boolean_T GreenLedDialVal_C;/* Referenced by: '<S17>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) boolean_T GreenLedIvt_C;/* Referenced by: '<S17>/Model' */

/* Invert the LED command */
extern __attribute__ ((section (".cal_data"))) boolean_T HvBusCurDialEna_C;/* Referenced by: '<S8>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T HvBusCurDialVal_C;/* Referenced by: '<S8>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T HvBusCurFilTiCon_C;/* Referenced by: '<S8>/Model' */

/* Low pass filter time constant for signal input processing */
extern __attribute__ ((section (".cal_data"))) real32_T HvBusCurGain_C;/* Referenced by: '<S8>/Model' */

/* Gain to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T HvBusCurOfs_C;/* Referenced by: '<S8>/Model' */

/* Offset to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) boolean_T HvBusUDialEna_C;/* Referenced by: '<S8>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T HvBusUDialVal_C;/* Referenced by: '<S8>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T HvBusUFilTiCon_C;/* Referenced by: '<S8>/Model' */

/* Low pass filter time constant for signal input processing */
extern __attribute__ ((section (".cal_data"))) real32_T HvBusUGain_C;/* Referenced by: '<S8>/Model' */

/* Gain to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T HvBusUOfs_C;/* Referenced by: '<S8>/Model' */

/* Offset to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) boolean_T InPwrPwmEna_C;/* Referenced by: '<S17>/Model' */

/* Enable InPwr modulation output: 0 = disable, 1 = enable. */
extern __attribute__ ((section (".cal_data"))) real32_T LedOffTi_C;/* Referenced by: '<S17>/Model' */

/* The time the LED is off between pulse groups */
extern __attribute__ ((section (".cal_data"))) uint8_T LedPlsCtDft_C;/* Referenced by: '<S17>/Model' */

/* The number of on pulses for the LED while in this mode */
extern __attribute__ ((section (".cal_data"))) uint8_T LedPlsCtOpenLoop_C;/* Referenced by: '<S17>/Model' */

/* The number of on pulses for the LED while in this mode */
extern __attribute__ ((section (".cal_data"))) uint8_T LedPlsCtSpdCtl_C;/* Referenced by: '<S17>/Model' */

/* The number of on pulses for the LED while in this mode */
extern __attribute__ ((section (".cal_data"))) uint8_T LedPlsCtTqCtl_C;/* Referenced by: '<S17>/Model' */

/* The number of on pulses for the LED while in this mode */
extern __attribute__ ((section (".cal_data"))) real32_T MaiPwrAcvDebFall_C;/* Referenced by: '<S16>/Model' */

/* Falling edge debounce time for input processing */
extern __attribute__ ((section (".cal_data"))) real32_T MaiPwrAcvDebRisng_C;/* Referenced by: '<S16>/Model' */

/* Rising edge debounce time for input processing */
extern __attribute__ ((section (".cal_data"))) boolean_T MaiPwrAcvDialEna_C;/* Referenced by: '<S16>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) boolean_T MaiPwrAcvDialVal_C;/* Referenced by: '<S16>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) boolean_T MaiPwrStsIvt_C;/* Referenced by: '<S16>/Model' */

/* Invert the main power status input */
extern __attribute__ ((section (".cal_data"))) boolean_T McuData1DaDialEna_C;/* Referenced by: '<S19>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) uint8_T McuData1DaDialVal_CA[8];/* Referenced by: '<S19>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) boolean_T McuData2DaDialEna_C;/* Referenced by: '<S17>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) uint8_T McuData2DaDialVal_CA[8];/* Referenced by: '<S17>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T McuReqTout_C;/* Referenced by: '<S18>/Model' */

/* Timeout time for the MCUReq message */
extern __attribute__ ((section (".cal_data"))) boolean_T McuTDialEna_C;/* Referenced by: '<S16>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T McuTDialVal_C;/* Referenced by: '<S16>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T McuTFilTiCon_C;/* Referenced by: '<S16>/Model' */

/* Low pass filter time constant for signal input processing */
extern __attribute__ ((section (".cal_data"))) real32_T McuTGain_C;/* Referenced by: '<S16>/Model' */

/* Gain to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T McuTOfs_C;/* Referenced by: '<S16>/Model' */

/* Offset to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T McuUBatFilTiCon_C;/* Referenced by: '<S16>/Model' */

/* Low pass filter time constant for signal input processing */
extern __attribute__ ((section (".cal_data"))) real32_T McuUBatGain_C;/* Referenced by: '<S16>/Model' */

/* Gain to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T McuUBatOfs_C;/* Referenced by: '<S16>/Model' */

/* Offset to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T McuURefFilTiCon_C;/* Referenced by: '<S16>/Model' */

/* Low pass filter time constant for signal input processing */
extern __attribute__ ((section (".cal_data"))) real32_T McuURefGain_C;/* Referenced by: '<S16>/Model' */

/* Gain to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T McuURefOfs_C;/* Referenced by: '<S16>/Model' */

/* Offset to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) uint8_T MotPolePairs_C;/* Referenced by: '<S13>/Model' */

/* The number of pole pairs in the motor */
extern __attribute__ ((section (".cal_data"))) real32_T MotPosnEstimrGainI_C;/* Referenced by: '<S13>/Model' */

/* Integral gain for MotPosn estimator. */
extern __attribute__ ((section (".cal_data"))) real32_T MotPosnEstimrGainP_C;/* Referenced by: '<S13>/Model' */

/* Proportional gain for MotPosn estimator. */
extern __attribute__ ((section (".cal_data"))) boolean_T MotPosnEstimrIntglEna_C;/* Referenced by: '<S13>/Model' */

/* MotPosn estimator integral enable: 0 = disable, 1 = enable. */
extern __attribute__ ((section (".cal_data"))) boolean_T MotPosnMagDialEna_C;/* Referenced by: '<S13>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T MotPosnMagDialVal_C;/* Referenced by: '<S13>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T MotPosnOfs_C;/* Referenced by: '<S13>/Model' */

/* Motor position offset. */
extern __attribute__ ((section (".cal_data"))) boolean_T MotPosnSenMeth_C;/* Referenced by: '<S13>/Model' */

/* Motor position sensing method: 0 = encoder, 1 = resolver. */
extern __attribute__ ((section (".cal_data"))) boolean_T MotPosnTrigDialEna_C;/* Referenced by: '<S14>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T MotPosnTrigDialVal_CA[6];/* Referenced by: '<S14>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) boolean_T MotSpdDialEna_C;/* Referenced by: '<S13>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) int16_T MotSpdDialVal_C;/* Referenced by: '<S13>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T MotSpdFilTiCon_C;/* Referenced by: '<S13>/Model' */

/* Low pass filter time constant for this signal */
extern __attribute__ ((section (".cal_data"))) boolean_T MotSpdMagDialEna_C;/* Referenced by: '<S13>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T MotSpdMagDialVal_C;/* Referenced by: '<S13>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T MotSpdRateLim_C;/* Referenced by: '<S20>/Model' */

/* The maximum rate at which the motor speed command is allowed to change */
extern __attribute__ ((section (".cal_data"))) int16_T MotSpdReqCanDft_C;/* Referenced by: '<S18>/Model' */

/* The default value used for this signal when the message has timedout */
extern __attribute__ ((section (".cal_data"))) boolean_T MotSpdReqCanDialEna_C;/* Referenced by: '<S18>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) int16_T MotSpdReqCanDialVal_C;/* Referenced by: '<S18>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) int16_T MotSpdReqMax_C;/* Referenced by: '<S20>/Model' */

/* The maximum magnitued of the speed command the control will attempt to control to */
extern __attribute__ ((section (".cal_data"))) uint16_T MotSpdReqThdModChg_C;/* Referenced by: '<S15>/Model' */

/* The motor speed request below which the drive is allowed to change modes */
extern __attribute__ ((section (".cal_data"))) uint16_T MotSpdThdModChg_C;/* Referenced by: '<S15>/Model' */

/* The motor speed below which the drive is allowed to change modes */
extern __attribute__ ((section (".cal_data"))) boolean_T MotTqCmdSpdCtlDialEna_C;/* Referenced by: '<S20>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T MotTqCmdSpdCtlDialVal_C;/* Referenced by: '<S20>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T MotTqCon_C;/* Referenced by: '<S21>/Model' */

/* The motor constant that maps between current and torque */
extern __attribute__ ((section (".cal_data"))) real32_T MotTqGainBdT1_Ax[5];/* Referenced by: '<S21>/Model' */

/* The axis for the table that maps between the board temperature and the gain that limits the maximum motor torque */
extern __attribute__ ((section (".cal_data"))) real32_T MotTqGainBdT1_T[5];/* Referenced by: '<S21>/Model' */

/* The table values for the table that maps between the board temperature and the gain that limits the maximum motor torque */
extern __attribute__ ((section (".cal_data"))) real32_T MotTqGainBdT2_Ax[5];/* Referenced by: '<S21>/Model' */

/* The axis for the table that maps between the board temperature and the gain that limits the maximum motor torque */
extern __attribute__ ((section (".cal_data"))) real32_T MotTqGainBdT2_T[5];/* Referenced by: '<S21>/Model' */

/* The table values for the table that maps between the board temperature and the gain that limits the maximum motor torque */
extern __attribute__ ((section (".cal_data"))) real32_T MotTqGainI_C;/* Referenced by: '<S20>/Model' */

/* Integral gain for motor speed control */
extern __attribute__ ((section (".cal_data"))) real32_T MotTqGainP_C;/* Referenced by: '<S20>/Model' */

/* Proportional gain for motor speed control */
extern __attribute__ ((section (".cal_data"))) boolean_T MotTqMaxDialEna_C;/* Referenced by: '<S21>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T MotTqMaxDialVal_C;/* Referenced by: '<S21>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T MotTqMaxMotSpd_Ax[5];/* Referenced by: '<S21>/Model' */

/* The axis values for the table that maps between the motor speed and the maximum motor torque */
extern __attribute__ ((section (".cal_data"))) real32_T MotTqMaxMotSpd_T[5];/* Referenced by: '<S21>/Model' */

/* The table values for the table that maps between the motor speed and the maximum motor torque */
extern __attribute__ ((section (".cal_data"))) real32_T MotTqReqCanDft_C;/* Referenced by: '<S18>/Model' */

/* The default value used for this signal when the message has timedout */
extern __attribute__ ((section (".cal_data"))) boolean_T MotTqReqCanDialEna_C;/* Referenced by: '<S18>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T MotTqReqCanDialVal_C;/* Referenced by: '<S18>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T MotTqReqThdModChg_C;/* Referenced by: '<S15>/Model' */

/* The motor torque request below which the drive is allowed to change modes */
extern __attribute__ ((section (".cal_data"))) boolean_T MtrPwrPwmEna_C;/* Referenced by: '<S17>/Model' */

/* Enable MtrPwr modulation output: 0 = disable, 1 = enable. */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaAPwmDcDialEna_C;/* Referenced by: '<S11>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) uint16_T PhaAPwmDcDialVal_C;/* Referenced by: '<S11>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaBPwmDcDialEna_C;/* Referenced by: '<S11>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) uint16_T PhaBPwmDcDialVal_C;/* Referenced by: '<S11>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaCPwmDcDialEna_C;/* Referenced by: '<S11>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) uint16_T PhaCPwmDcDialVal_C;/* Referenced by: '<S11>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaCurADialEna_C;/* Referenced by: '<S8>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurADialVal_C;/* Referenced by: '<S8>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurAFilTiCon_C;/* Referenced by: '<S8>/Model' */

/* Low pass filter time constant for signal input processing */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurAGain_C;/* Referenced by: '<S8>/Model' */

/* Gain to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurAOfs_C;/* Referenced by: '<S8>/Model' */

/* Offset to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaCurBDialEna_C;/* Referenced by: '<S8>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurBDialVal_C;/* Referenced by: '<S8>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurBFilTiCon_C;/* Referenced by: '<S8>/Model' */

/* Low pass filter time constant for signal input processing */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurBGain_C;/* Referenced by: '<S8>/Model' */

/* Gain to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurBOfs_C;/* Referenced by: '<S8>/Model' */

/* Offset to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaCurCDialEna_C;/* Referenced by: '<S8>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurCDialVal_C;/* Referenced by: '<S8>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurCFilTiCon_C;/* Referenced by: '<S8>/Model' */

/* Low pass filter time constant for signal input processing */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurCGain_C;/* Referenced by: '<S8>/Model' */

/* Gain to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurCOfs_C;/* Referenced by: '<S8>/Model' */

/* Offset to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaCurDDialEna_C;/* Referenced by: '<S9>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurDDialVal_C;/* Referenced by: '<S9>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurDTarVal_C;/* Referenced by: '<S21>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaCurQDialEna_C;/* Referenced by: '<S9>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurQDialVal_C;/* Referenced by: '<S9>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaCurQTarDialEna_C;/* Referenced by: '<S21>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurQTarDialVal_C;/* Referenced by: '<S21>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaPwmEnaDialEna_C;/* Referenced by: '<S17>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaPwmEnaDialVal_C;/* Referenced by: '<S17>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaUACmdDialEna_C;/* Referenced by: '<S12>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUACmdDialVal_C;/* Referenced by: '<S12>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUAFilTiCon_C;/* Referenced by: '<S8>/Model' */

/* Low pass filter time constant for signal input processing */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUAGain_C;/* Referenced by: '<S8>/Model' */

/* Gain to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUAOfs_C;/* Referenced by: '<S8>/Model' */

/* Offset to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaUBCmdDialEna_C;/* Referenced by: '<S12>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUBCmdDialVal_C;/* Referenced by: '<S12>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUBFilTiCon_C;/* Referenced by: '<S8>/Model' */

/* Low pass filter time constant for signal input processing */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUBGain_C;/* Referenced by: '<S8>/Model' */

/* Gain to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUBOfs_C;/* Referenced by: '<S8>/Model' */

/* Offset to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaUCCmdDialEna_C;/* Referenced by: '<S12>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUCCmdDialVal_C;/* Referenced by: '<S12>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUCFilTiCon_C;/* Referenced by: '<S8>/Model' */

/* Low pass filter time constant for signal input processing */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUCGain_C;/* Referenced by: '<S8>/Model' */

/* Gain to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUCOfs_C;/* Referenced by: '<S8>/Model' */

/* Offset to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUDAntiWindupGain_C;/* Referenced by: '<S10>/Model' */

/* Gain used to attenuate the integrated error when the output voltage command is saturated to avoid integral windup  */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaUDCmdDialEna_C;/* Referenced by: '<S10>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUDCmdDialVal_C;/* Referenced by: '<S10>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUDCmdOpenLoop_C;/* Referenced by: '<S10>/Model' */

/* The d-axis phase voltage command in open loop mode */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUDGainI_C;/* Referenced by: '<S10>/Model' */

/* Integral control gain for d-axis current control */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUDGainP_C;/* Referenced by: '<S10>/Model' */

/* Proportional control gain for d-axis current control */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUMaxVal_C;/* Referenced by: '<S10>/Model' */

/* The smallest value the maximum phase voltage is allowed to take on for current control calculations */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUQAntiWindupGain_C;/* Referenced by: '<S10>/Model' */

/* Gain used to attenuate the integrated error when the output voltage command is saturated to avoid integral windup */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaUQCmdDialEna_C;/* Referenced by: '<S10>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUQCmdDialVal_C;/* Referenced by: '<S10>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUQCmdOpenLoop_C;/* Referenced by: '<S10>/Model' */

/* The q-axis phase voltage command in open loop mode */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUQGainI_C;/* Referenced by: '<S10>/Model' */

/* Integral control gain for q-axis current control */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUQGainP_C;/* Referenced by: '<S10>/Model' */

/* Proportional control gain for q-axis current control */
extern __attribute__ ((section (".cal_data"))) real32_T PlsOffTi_C;/* Referenced by: '<S17>/Model' */

/* The time the LED is off between two pulses */
extern __attribute__ ((section (".cal_data"))) real32_T PlsOnTi_C;/* Referenced by: '<S17>/Model' */

/* The time the LED is on during a pulse */
extern __attribute__ ((section (".cal_data"))) boolean_T PwrCmdDialEna_C;/* Referenced by: '<S15>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) boolean_T PwrCmdDialVal_C;/* Referenced by: '<S15>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) boolean_T RedLedDialEna_C;/* Referenced by: '<S17>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) boolean_T RedLedDialVal_C;/* Referenced by: '<S17>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) boolean_T RedLedIvt_C;/* Referenced by: '<S17>/Model' */

/* Invert the LED command */
extern __attribute__ ((section (".cal_data"))) int16_T ReloadRegisterMax_C;/* Referenced by: '<S11>/Model' */

/* The maximum value of the register used by the hardware PWM generator */
extern __attribute__ ((section (".cal_data"))) real32_T ResolverCosFilTiCon_C;/* Referenced by: '<S8>/Model' */

/* Low pass filter time constant for signal input processing */
extern __attribute__ ((section (".cal_data"))) real32_T ResolverCosGain_C;/* Referenced by: '<S8>/Model' */

/* Gain to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T ResolverCosOfs_C;/* Referenced by: '<S8>/Model' */

/* Offset to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) boolean_T ResolverExctEna_C;/* Referenced by: '<S17>/Model' */

/* Command to enable resolver excitation waveform generation: 0 = disable, 1 = enable. */
extern __attribute__ ((section (".cal_data"))) boolean_T ResolverSinCosDialEna_C;/* Referenced by: '<S8>/Model' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T
  ResolverSinCosDialVal_CA[2];         /* Referenced by: '<S8>/Model' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T ResolverSinFilTiCon_C;/* Referenced by: '<S8>/Model' */

/* Low pass filter time constant for signal input processing */
extern __attribute__ ((section (".cal_data"))) real32_T ResolverSinGain_C;/* Referenced by: '<S8>/Model' */

/* Gain to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T ResolverSinOfs_C;/* Referenced by: '<S8>/Model' */

/* Offset to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T StatorInductanceD_C;/* Referenced by: '<S10>/Model' */

/* The motor stator d-axis inductance */
extern __attribute__ ((section (".cal_data"))) real32_T StatorInductanceQ_C;/* Referenced by: '<S10>/Model' */

/* The motor stator q-axis inductance */
extern __attribute__ ((section (".cal_data"))) boolean_T SwPwrPwmEna_C;/* Referenced by: '<S17>/Model' */

/* Enable SwPwr modulation output: 0 = disable, 1 = enable. */
extern __attribute__ ((section (".cal_data"))) boolean_T WakeRetry_C;/* Referenced by: '<S15>/Model' */

/* Flag used to force the drive to try and rewake the board by activiting the power command */
extern __attribute__ ((section (".cal_data"))) real32_T WakeTout_C;/* Referenced by: '<S15>/Model' */

/* The amount of time the control waits for the power activation signal before shutting off the power command and terminating the wake attempt */
extern __attribute__ ((section (".cal_data"))) boolean_T YellowLedCmd_C;/* Referenced by: '<S17>/Model' */

/* Yellow LED activation command. */

/* Real-time Model object */
extern RT_MODEL_P2319ASW01_T *const P2319ASW01_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'P2319ASW01'
 * '<S1>'   : 'P2319ASW01/Current_Control'
 * '<S2>'   : 'P2319ASW01/InputBusManagement'
 * '<S3>'   : 'P2319ASW01/OutputBusManagement1'
 * '<S4>'   : 'P2319ASW01/OutputBusManagement2'
 * '<S5>'   : 'P2319ASW01/OutputBusManagement3'
 * '<S6>'   : 'P2319ASW01/Supervisor'
 * '<S7>'   : 'P2319ASW01/Torque_Speed_Control'
 * '<S8>'   : 'P2319ASW01/Current_Control/ADCINP'
 * '<S9>'   : 'P2319ASW01/Current_Control/CLAPAR'
 * '<S10>'  : 'P2319ASW01/Current_Control/CURCTL'
 * '<S11>'  : 'P2319ASW01/Current_Control/GATOUP'
 * '<S12>'  : 'P2319ASW01/Current_Control/INVCPA'
 * '<S13>'  : 'P2319ASW01/Current_Control/POSINP'
 * '<S14>'  : 'P2319ASW01/Current_Control/POSTRG'
 * '<S15>'  : 'P2319ASW01/Supervisor/MODCTL'
 * '<S16>'  : 'P2319ASW01/Supervisor/SLWINP'
 * '<S17>'  : 'P2319ASW01/Supervisor/SLWOUP'
 * '<S18>'  : 'P2319ASW01/Torque_Speed_Control/MEDINP'
 * '<S19>'  : 'P2319ASW01/Torque_Speed_Control/MEDOUP'
 * '<S20>'  : 'P2319ASW01/Torque_Speed_Control/SPDCTL'
 * '<S21>'  : 'P2319ASW01/Torque_Speed_Control/TRQCTL'
 */
#endif                                 /* RTW_HEADER_P2319ASW01_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
