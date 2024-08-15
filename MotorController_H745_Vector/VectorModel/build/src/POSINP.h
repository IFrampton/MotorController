/*
 * File: POSINP.h
 *
 * Code generated for Simulink model 'POSINP'.
 *
 * Model version                  : 1.188
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:12:15 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_POSINP_h_
#define RTW_HEADER_POSINP_h_
#ifndef POSINP_COMMON_INCLUDES_
#define POSINP_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* POSINP_COMMON_INCLUDES_ */

#include "POSINP_types.h"
#include "LowPassFilter_0O6LwJpz.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"

/* Block states (default storage) for model 'POSINP' */
#ifndef POSINP_MDLREF_HIDE_CHILD_

typedef struct {
  real32_T UnitDelay1_DSTATE;          /* '<Root>/Unit Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE;/* '<Root>/Discrete-Time Integrator' */
  real32_T UnitDelay5_DSTATE;          /* '<Root>/Unit Delay5' */
  int32_T Accumulator_DSTATE;          /* '<Root>/Accumulator' */
  boolean_T DelayInput1_DSTATE;        /* '<S1>/Delay Input1' */
  int8_T Accumulator_PrevResetState;   /* '<Root>/Accumulator' */
  DW_LowPassFilter_0O6LwJpz_T LowPassFilter;/* '<Root>/LowPassFilter' */
} DW_POSINP_f_T;

#endif                                 /*POSINP_MDLREF_HIDE_CHILD_*/

#ifndef POSINP_MDLREF_HIDE_CHILD_

/* Real-time Model Data Structure */
struct tag_RTM_POSINP_T {
  const char_T **errorStatus;
};

#endif                                 /*POSINP_MDLREF_HIDE_CHILD_*/

#ifndef POSINP_MDLREF_HIDE_CHILD_

typedef struct {
  RT_MODEL_POSINP_T rtm;
} MdlrefDW_POSINP_T;

#endif                                 /*POSINP_MDLREF_HIDE_CHILD_*/

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern int16_T ASWIN_EncoderCt;        /* '<Root>/ASWIN_EncoderCt'
                                        * The raw encoder count input
                                        */
extern boolean_T ASWIN_EncoderZ;       /* '<Root>/ASWIN_EncoderZ'
                                        * The raw encoder z signal
                                        */
extern real32_T MotPosnMagMeasd;       /* '<Root>/Math Function1'
                                        * The measured magnetic motor position. Can be used in open loop control to verify position measurement.
                                        */
extern real32_T MotPosnErr;            /* '<Root>/Add1'
                                        * Motor position error.
                                        */
extern real32_T MotPosnMag;            /* '<Root>/Switch4'
                                        * The magnetic rotor position. Zero degrees represents the rotor magnetic field aligned with the stator's A phase.
                                        */
extern real32_T MotSpdMag;             /* '<Root>/Switch1'
                                        * The magnetic motor speed
                                        */
extern int16_T MotSpd;                 /* '<Root>/Switch2'
                                        * The mechanical motor speed
                                        */
extern void POSINP_Init(void);
extern void POSINP(const DRIVEMODE *rtu_DrvMod, const int16_T *rtu_MotSpdReqCan,
                   const real32_T rtu_ResolverSinCos[2]);

/* Model reference registration function */
extern void POSINP_initialize(const char_T **rt_errorStatus);

/* Exported data declaration */

/* Calibration memory section */
/* Declaration for custom storage class: Calibration */
extern __attribute__ ((section (".cal_data"))) uint16_T EncoderCtPerRev_C;/* Referenced by:
                                                                      * '<Root>/Constant1'
                                                                      * '<Root>/Constant2'
                                                                      */

/* The number of encoder counts per mechanical revolution */
extern __attribute__ ((section (".cal_data"))) real32_T EncoderOfs_C;/* Referenced by: '<Root>/Constant10' */

/* Offset used to align the encoder z signal with the true zero angle */
extern __attribute__ ((section (".cal_data"))) uint8_T MotPolePairs_C;/* Referenced by:
                                                                      * '<Root>/Constant'
                                                                      * '<Root>/Constant13'
                                                                      */

/* The number of pole pairs in the motor */
extern __attribute__ ((section (".cal_data"))) real32_T MotPosnEstimrGainI_C;/* Referenced by: '<Root>/Constant21' */

/* Integral gain for MotPosn estimator. */
extern __attribute__ ((section (".cal_data"))) real32_T MotPosnEstimrGainP_C;/* Referenced by: '<Root>/Constant15' */

/* Proportional gain for MotPosn estimator. */
extern __attribute__ ((section (".cal_data"))) boolean_T MotPosnEstimrIntglEna_C;/* Referenced by: '<Root>/Constant18' */

/* MotPosn estimator integral enable: 0 = disable, 1 = enable. */
extern __attribute__ ((section (".cal_data"))) boolean_T MotPosnMagDialEna_C;/* Referenced by: '<Root>/Constant16' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T MotPosnMagDialVal_C;/* Referenced by: '<Root>/Constant17' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T MotPosnOfs_C;/* Referenced by: '<Root>/Constant23' */

/* Motor position offset. */
extern __attribute__ ((section (".cal_data"))) boolean_T MotPosnSenMeth_C;/* Referenced by:
                                                                      * '<Root>/Constant24'
                                                                      * '<Root>/Constant25'
                                                                      * '<Root>/Constant26'
                                                                      */

/* Motor position sensing method: 0 = encoder, 1 = resolver. */
extern __attribute__ ((section (".cal_data"))) boolean_T MotSpdDialEna_C;/* Referenced by: '<Root>/Constant8' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) int16_T MotSpdDialVal_C;/* Referenced by: '<Root>/Constant9' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T MotSpdFilTiCon_C;/* Referenced by: '<Root>/Constant5' */

/* Low pass filter time constant for this signal */
extern __attribute__ ((section (".cal_data"))) boolean_T MotSpdMagDialEna_C;/* Referenced by: '<Root>/Constant6' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T MotSpdMagDialVal_C;/* Referenced by: '<Root>/Constant7' */

/* Signal override value */
#ifndef POSINP_MDLREF_HIDE_CHILD_

extern MdlrefDW_POSINP_T POSINP_MdlrefDW;

#endif                                 /*POSINP_MDLREF_HIDE_CHILD_*/

#ifndef POSINP_MDLREF_HIDE_CHILD_

/* Block states (default storage) */
extern DW_POSINP_f_T POSINP_DW;

#endif                                 /*POSINP_MDLREF_HIDE_CHILD_*/

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<Root>/Data Type Conversion3' : Eliminate redundant data type conversion
 */

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
 * '<Root>' : 'POSINP'
 * '<S1>'   : 'POSINP/Detect Change'
 * '<S2>'   : 'POSINP/Enumerated Constant'
 * '<S3>'   : 'POSINP/LowPassFilter'
 * '<S4>'   : 'POSINP/Model Info'
 */
#endif                                 /* RTW_HEADER_POSINP_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
