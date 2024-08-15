/*
 * File: CURCTL.h
 *
 * Code generated for Simulink model 'CURCTL'.
 *
 * Model version                  : 1.185
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:11:53 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_CURCTL_h_
#define RTW_HEADER_CURCTL_h_
#ifndef CURCTL_COMMON_INCLUDES_
#define CURCTL_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* CURCTL_COMMON_INCLUDES_ */

#include "CURCTL_types.h"

/* Block states (default storage) for model 'CURCTL' */
#ifndef CURCTL_MDLREF_HIDE_CHILD_

typedef struct {
  real32_T Accumulator2_DSTATE;        /* '<Root>/Accumulator2' */
  real32_T Accumulator1_DSTATE;        /* '<Root>/Accumulator1' */
  real32_T UnitDelay1_DSTATE;          /* '<Root>/Unit Delay1' */
  real32_T UnitDelay_DSTATE;           /* '<Root>/Unit Delay' */
  int8_T Accumulator2_PrevResetState;  /* '<Root>/Accumulator2' */
  int8_T Accumulator1_PrevResetState;  /* '<Root>/Accumulator1' */
} DW_CURCTL_f_T;

#endif                                 /*CURCTL_MDLREF_HIDE_CHILD_*/

#ifndef CURCTL_MDLREF_HIDE_CHILD_

/* Real-time Model Data Structure */
struct tag_RTM_CURCTL_T {
  const char_T **errorStatus;
};

#endif                                 /*CURCTL_MDLREF_HIDE_CHILD_*/

#ifndef CURCTL_MDLREF_HIDE_CHILD_

typedef struct {
  RT_MODEL_CURCTL_T rtm;
} MdlrefDW_CURCTL_T;

#endif                                 /*CURCTL_MDLREF_HIDE_CHILD_*/

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real32_T PhaUQCmd;              /* '<Root>/Switch3'
                                        * Commanded q-axis phase voltage
                                        */
extern real32_T PhaUDCmd;              /* '<Root>/Switch1'
                                        * Commanded d-axis phase voltage
                                        */
extern void CURCTL(const real32_T *rtu_PhaCurD, const real32_T *rtu_PhaCurDTar,
                   const real32_T *rtu_HvBusU, const DRIVEMODE *rtu_DrvMod,
                   const real32_T *rtu_PhaCurQ, const real32_T *rtu_PhaCurQTar,
                   const real32_T *rtu_MotSpdMag);

/* Model reference registration function */
extern void CURCTL_initialize(const char_T **rt_errorStatus);

/* Exported data declaration */

/* Calibration memory section */
/* Declaration for custom storage class: Calibration */
extern __attribute__ ((section (".cal_data"))) real32_T FluxLinkage_C;/* Referenced by: '<Root>/Constant11' */

/* The permanent magnet flux linkage of the motor */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUDAntiWindupGain_C;/* Referenced by: '<Root>/Constant21' */

/* Gain used to attenuate the integrated error when the output voltage command is saturated to avoid integral windup  */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaUDCmdDialEna_C;/* Referenced by: '<Root>/Constant2' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUDCmdDialVal_C;/* Referenced by: '<Root>/Constant3' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUDCmdOpenLoop_C;/* Referenced by: '<Root>/Constant13' */

/* The d-axis phase voltage command in open loop mode */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUDGainI_C;/* Referenced by: '<Root>/Constant4' */

/* Integral control gain for d-axis current control */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUDGainP_C;/* Referenced by: '<Root>/Constant1' */

/* Proportional control gain for d-axis current control */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUMaxVal_C;/* Referenced by: '<Root>/Constant20' */

/* The smallest value the maximum phase voltage is allowed to take on for current control calculations */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUQAntiWindupGain_C;/* Referenced by: '<Root>/Constant19' */

/* Gain used to attenuate the integrated error when the output voltage command is saturated to avoid integral windup */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaUQCmdDialEna_C;/* Referenced by: '<Root>/Constant15' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUQCmdDialVal_C;/* Referenced by: '<Root>/Constant16' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUQCmdOpenLoop_C;/* Referenced by: '<Root>/Constant18' */

/* The q-axis phase voltage command in open loop mode */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUQGainI_C;/* Referenced by: '<Root>/Constant10' */

/* Integral control gain for q-axis current control */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUQGainP_C;/* Referenced by: '<Root>/Constant8' */

/* Proportional control gain for q-axis current control */
extern __attribute__ ((section (".cal_data"))) real32_T StatorInductanceD_C;/* Referenced by: '<Root>/Constant7' */

/* The motor stator d-axis inductance */
extern __attribute__ ((section (".cal_data"))) real32_T StatorInductanceQ_C;/* Referenced by: '<Root>/Constant6' */

/* The motor stator q-axis inductance */
#ifndef CURCTL_MDLREF_HIDE_CHILD_

extern MdlrefDW_CURCTL_T CURCTL_MdlrefDW;

#endif                                 /*CURCTL_MDLREF_HIDE_CHILD_*/

#ifndef CURCTL_MDLREF_HIDE_CHILD_

/* Block states (default storage) */
extern DW_CURCTL_f_T CURCTL_DW;

#endif                                 /*CURCTL_MDLREF_HIDE_CHILD_*/

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S3>/Data Type Duplicate' : Unused code path elimination
 * Block '<S3>/Data Type Propagation' : Unused code path elimination
 * Block '<S4>/Data Type Duplicate' : Unused code path elimination
 * Block '<S4>/Data Type Propagation' : Unused code path elimination
 * Block '<Root>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<Root>/Data Type Conversion1' : Eliminate redundant data type conversion
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
 * '<Root>' : 'CURCTL'
 * '<S1>'   : 'CURCTL/Enumerated Constant1'
 * '<S2>'   : 'CURCTL/Model Info'
 * '<S3>'   : 'CURCTL/Saturation Dynamic'
 * '<S4>'   : 'CURCTL/Saturation Dynamic1'
 */
#endif                                 /* RTW_HEADER_CURCTL_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
