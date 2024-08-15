/*
 * File: SLWOUP.h
 *
 * Code generated for Simulink model 'SLWOUP'.
 *
 * Model version                  : 1.65
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:12:28 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_SLWOUP_h_
#define RTW_HEADER_SLWOUP_h_
#ifndef SLWOUP_COMMON_INCLUDES_
#define SLWOUP_COMMON_INCLUDES_
#include <math.h>
#include "rtwtypes.h"
#endif                                 /* SLWOUP_COMMON_INCLUDES_ */

#include "SLWOUP_types.h"

/* Block signals for model 'SLWOUP' */
#ifndef SLWOUP_MDLREF_HIDE_CHILD_

typedef struct {
  CAN_MESSAGE_BUS CANP1ack;            /* '<Root>/CAN P1ack' */
  boolean_T Led;                       /* '<Root>/BlinkController' */
} B_SLWOUP_c_T;

#endif                                 /*SLWOUP_MDLREF_HIDE_CHILD_*/

/* Block states (default storage) for model 'SLWOUP' */
#ifndef SLWOUP_MDLREF_HIDE_CHILD_

typedef struct {
  real32_T OffTmr;                     /* '<Root>/BlinkController' */
  real32_T PlsOnTmr;                   /* '<Root>/BlinkController' */
  real32_T PlsOffTmr;                  /* '<Root>/BlinkController' */
  int_T CANP1ack_ModeSignalID;         /* '<Root>/CAN P1ack' */
  uint8_T is_c3_SLWOUP;                /* '<Root>/BlinkController' */
  uint8_T is_PULSE;                    /* '<Root>/BlinkController' */
  uint8_T PlsCtr;                      /* '<Root>/BlinkController' */
  uint8_T is_active_c3_SLWOUP;         /* '<Root>/BlinkController' */
} DW_SLWOUP_f_T;

#endif                                 /*SLWOUP_MDLREF_HIDE_CHILD_*/

#ifndef SLWOUP_MDLREF_HIDE_CHILD_

/* Real-time Model Data Structure */
struct tag_RTM_SLWOUP_T {
  const char_T **errorStatus;
};

#endif                                 /*SLWOUP_MDLREF_HIDE_CHILD_*/

#ifndef SLWOUP_MDLREF_HIDE_CHILD_

typedef struct {
  RT_MODEL_SLWOUP_T rtm;
} MdlrefDW_SLWOUP_T;

#endif                                 /*SLWOUP_MDLREF_HIDE_CHILD_*/

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern uint8_T ASWOUT_McuData2Da[8];   /* '<Root>/Switch'
                                        * The raw message data frame
                                        */
extern boolean_T ASWOUT_RedLed;        /* '<Root>/Switch1'
                                        * The raw output value
                                        */
extern boolean_T ASWOUT_GreenLed;      /* '<Root>/Switch2'
                                        * The raw output value
                                        */
extern boolean_T ASWOUT_PhaPwmEna;     /* '<Root>/Switch3'
                                        * The raw modulation enable command used by the hardware PWM generator: 0 = disable, 1 = enable.
                                        */
extern boolean_T ASWOUT_YellowLed;     /* '<Root>/Constant17'
                                        * The raw output value
                                        */
extern boolean_T ASWOUT_ResolverExctEna;/* '<Root>/Constant18'
                                         * The raw output value
                                         */
extern boolean_T ASWOUT_CanPwrPwmEna;  /* '<Root>/Constant22'
                                        * The raw output value
                                        */
extern boolean_T ASWOUT_InPwrPwmEna;   /* '<Root>/Constant14'
                                        * The raw output value
                                        */
extern boolean_T ASWOUT_MtrPwrPwmEna;  /* '<Root>/Constant12'
                                        * The raw output value
                                        */
extern boolean_T ASWOUT_SwPwrPwmEna;   /* '<Root>/Constant11'
                                        * The raw output value
                                        */
extern void SLWOUP(const DRIVEMODE *rtu_DrvMod, const real32_T *rtu_BdT1, const
                   real32_T *rtu_BdT2, const real32_T *rtu_McuT);

/* Model reference registration function */
extern void SLWOUP_initialize(const char_T **rt_errorStatus);

/* Exported data declaration */

/* Calibration memory section */
/* Declaration for custom storage class: Calibration */
extern __attribute__ ((section (".cal_data"))) boolean_T CanPwrPwmEna_C;/* Referenced by: '<Root>/Constant22' */

/* Enable CanPwr modulation output: 0 = disable, 1 = enable. */
extern __attribute__ ((section (".cal_data"))) boolean_T GreenLedDialEna_C;/* Referenced by: '<Root>/Constant7' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) boolean_T GreenLedDialVal_C;/* Referenced by: '<Root>/Constant8' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) boolean_T GreenLedIvt_C;/* Referenced by: '<Root>/Constant' */

/* Invert the LED command */
extern __attribute__ ((section (".cal_data"))) boolean_T InPwrPwmEna_C;/* Referenced by: '<Root>/Constant14' */

/* Enable InPwr modulation output: 0 = disable, 1 = enable. */
extern __attribute__ ((section (".cal_data"))) real32_T LedOffTi_C;
                                   /* Referenced by: '<Root>/BlinkController' */

/* The time the LED is off between pulse groups */
extern __attribute__ ((section (".cal_data"))) uint8_T LedPlsCtDft_C;/* Referenced by: '<Root>/Constant4' */

/* The number of on pulses for the LED while in this mode */
extern __attribute__ ((section (".cal_data"))) uint8_T LedPlsCtOpenLoop_C;/* Referenced by: '<Root>/Constant1' */

/* The number of on pulses for the LED while in this mode */
extern __attribute__ ((section (".cal_data"))) uint8_T LedPlsCtSpdCtl_C;/* Referenced by: '<Root>/Constant3' */

/* The number of on pulses for the LED while in this mode */
extern __attribute__ ((section (".cal_data"))) uint8_T LedPlsCtTqCtl_C;/* Referenced by: '<Root>/Constant2' */

/* The number of on pulses for the LED while in this mode */
extern __attribute__ ((section (".cal_data"))) boolean_T McuData2DaDialEna_C;/* Referenced by: '<Root>/Constant15' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) uint8_T McuData2DaDialVal_CA[8];/* Referenced by: '<Root>/Constant16' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) boolean_T MtrPwrPwmEna_C;/* Referenced by: '<Root>/Constant12' */

/* Enable MtrPwr modulation output: 0 = disable, 1 = enable. */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaPwmEnaDialEna_C;/* Referenced by: '<Root>/Constant33' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaPwmEnaDialVal_C;/* Referenced by: '<Root>/Constant34' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T PlsOffTi_C;
                                   /* Referenced by: '<Root>/BlinkController' */

/* The time the LED is off between two pulses */
extern __attribute__ ((section (".cal_data"))) real32_T PlsOnTi_C;
                                   /* Referenced by: '<Root>/BlinkController' */

/* The time the LED is on during a pulse */
extern __attribute__ ((section (".cal_data"))) boolean_T RedLedDialEna_C;/* Referenced by: '<Root>/Constant9' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) boolean_T RedLedDialVal_C;/* Referenced by: '<Root>/Constant10' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) boolean_T RedLedIvt_C;/* Referenced by: '<Root>/Constant5' */

/* Invert the LED command */
extern __attribute__ ((section (".cal_data"))) boolean_T ResolverExctEna_C;/* Referenced by: '<Root>/Constant18' */

/* Command to enable resolver excitation waveform generation: 0 = disable, 1 = enable. */
extern __attribute__ ((section (".cal_data"))) boolean_T SwPwrPwmEna_C;/* Referenced by: '<Root>/Constant11' */

/* Enable SwPwr modulation output: 0 = disable, 1 = enable. */
extern __attribute__ ((section (".cal_data"))) boolean_T YellowLedCmd_C;/* Referenced by: '<Root>/Constant17' */

/* Yellow LED activation command. */
#ifndef SLWOUP_MDLREF_HIDE_CHILD_

extern MdlrefDW_SLWOUP_T SLWOUP_MdlrefDW;

#endif                                 /*SLWOUP_MDLREF_HIDE_CHILD_*/

#ifndef SLWOUP_MDLREF_HIDE_CHILD_

/* Block signals (default storage) */
extern B_SLWOUP_c_T SLWOUP_B;

/* Block states (default storage) */
extern DW_SLWOUP_f_T SLWOUP_DW;

#endif                                 /*SLWOUP_MDLREF_HIDE_CHILD_*/

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
 * '<Root>' : 'SLWOUP'
 * '<S1>'   : 'SLWOUP/BlinkController'
 * '<S2>'   : 'SLWOUP/Compare To Constant'
 * '<S3>'   : 'SLWOUP/Model Info'
 */
#endif                                 /* RTW_HEADER_SLWOUP_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
