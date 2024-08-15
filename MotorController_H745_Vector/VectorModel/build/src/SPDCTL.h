/*
 * File: SPDCTL.h
 *
 * Code generated for Simulink model 'SPDCTL'.
 *
 * Model version                  : 1.79
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:12:30 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_SPDCTL_h_
#define RTW_HEADER_SPDCTL_h_
#ifndef SPDCTL_COMMON_INCLUDES_
#define SPDCTL_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* SPDCTL_COMMON_INCLUDES_ */

#include "SPDCTL_types.h"
#include "RateLimit_8K29mxJB.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"

/* Block states (default storage) for model 'SPDCTL' */
#ifndef SPDCTL_MDLREF_HIDE_CHILD_

typedef struct {
  real32_T Accumulator_DSTATE;         /* '<Root>/Accumulator' */
  boolean_T UnitDelay_DSTATE;          /* '<Root>/Unit Delay' */
  int8_T Accumulator_PrevResetState;   /* '<Root>/Accumulator' */
  DW_RateLimit_8K29mxJB_T RateLimit;   /* '<Root>/RateLimit' */
} DW_SPDCTL_f_T;

#endif                                 /*SPDCTL_MDLREF_HIDE_CHILD_*/

#ifndef SPDCTL_MDLREF_HIDE_CHILD_

/* Real-time Model Data Structure */
struct tag_RTM_SPDCTL_T {
  const char_T **errorStatus;
};

#endif                                 /*SPDCTL_MDLREF_HIDE_CHILD_*/

#ifndef SPDCTL_MDLREF_HIDE_CHILD_

typedef struct {
  RT_MODEL_SPDCTL_T rtm;
} MdlrefDW_SPDCTL_T;

#endif                                 /*SPDCTL_MDLREF_HIDE_CHILD_*/

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real32_T MotTqCmdSpdCtl;        /* '<Root>/Switch3'
                                        * The motor torque commanded by the motor speed controller
                                        */
extern int16_T MotSpdCmd;              /* '<Root>/Data Type Conversion1'
                                        * The motor speed command the controller is controlling to
                                        */
extern void SPDCTL(const int16_T *rtu_MotSpd, const DRIVEMODE *rtu_DrvMod, const
                   int16_T *rtu_MotSpdReqCan, const real32_T *rtu_MotTqMax);

/* Model reference registration function */
extern void SPDCTL_initialize(const char_T **rt_errorStatus);

/* Exported data declaration */

/* Calibration memory section */
/* Declaration for custom storage class: Calibration */
extern __attribute__ ((section (".cal_data"))) real32_T MotSpdRateLim_C;/* Referenced by: '<Root>/Constant8' */

/* The maximum rate at which the motor speed command is allowed to change */
extern __attribute__ ((section (".cal_data"))) int16_T MotSpdReqMax_C;/* Referenced by: '<Root>/Constant11' */

/* The maximum magnitued of the speed command the control will attempt to control to */
extern __attribute__ ((section (".cal_data"))) boolean_T MotTqCmdSpdCtlDialEna_C;/* Referenced by: '<Root>/Constant2' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T MotTqCmdSpdCtlDialVal_C;/* Referenced by: '<Root>/Constant6' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T MotTqGainI_C;/* Referenced by: '<Root>/Constant5' */

/* Integral gain for motor speed control */
extern __attribute__ ((section (".cal_data"))) real32_T MotTqGainP_C;/* Referenced by: '<Root>/Constant1' */

/* Proportional gain for motor speed control */
#ifndef SPDCTL_MDLREF_HIDE_CHILD_

extern MdlrefDW_SPDCTL_T SPDCTL_MdlrefDW;

#endif                                 /*SPDCTL_MDLREF_HIDE_CHILD_*/

#ifndef SPDCTL_MDLREF_HIDE_CHILD_

/* Block states (default storage) */
extern DW_SPDCTL_f_T SPDCTL_DW;

#endif                                 /*SPDCTL_MDLREF_HIDE_CHILD_*/

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S7>/Data Type Duplicate' : Unused code path elimination
 * Block '<S7>/Data Type Propagation' : Unused code path elimination
 * Block '<S5>/Data Type Duplicate' : Unused code path elimination
 * Block '<S5>/Data Type Propagation' : Unused code path elimination
 * Block '<S6>/Data Type Duplicate' : Unused code path elimination
 * Block '<S6>/Data Type Propagation' : Unused code path elimination
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
 * '<Root>' : 'SPDCTL'
 * '<S1>'   : 'SPDCTL/Enumerated Constant'
 * '<S2>'   : 'SPDCTL/Interval Test Dynamic'
 * '<S3>'   : 'SPDCTL/Model Info'
 * '<S4>'   : 'SPDCTL/RateLimit'
 * '<S5>'   : 'SPDCTL/Saturation Dynamic'
 * '<S6>'   : 'SPDCTL/Saturation Dynamic1'
 * '<S7>'   : 'SPDCTL/RateLimit/Saturation Dynamic'
 */
#endif                                 /* RTW_HEADER_SPDCTL_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
