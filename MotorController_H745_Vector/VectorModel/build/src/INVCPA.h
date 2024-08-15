/*
 * File: INVCPA.h
 *
 * Code generated for Simulink model 'INVCPA'.
 *
 * Model version                  : 1.40
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:11:58 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_INVCPA_h_
#define RTW_HEADER_INVCPA_h_
#ifndef INVCPA_COMMON_INCLUDES_
#define INVCPA_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* INVCPA_COMMON_INCLUDES_ */

#include "INVCPA_types.h"

/* Invariant block signals for model 'INVCPA' */
#ifndef INVCPA_MDLREF_HIDE_CHILD_

typedef struct {
  const real32_T Reshape1[3];          /* '<Root>/Reshape1' */
} ConstB_INVCPA_h_T;

#endif                                 /*INVCPA_MDLREF_HIDE_CHILD_*/

#ifndef INVCPA_MDLREF_HIDE_CHILD_

/* Real-time Model Data Structure */
struct tag_RTM_INVCPA_T {
  const char_T **errorStatus;
};

#endif                                 /*INVCPA_MDLREF_HIDE_CHILD_*/

#ifndef INVCPA_MDLREF_HIDE_CHILD_

typedef struct {
  RT_MODEL_INVCPA_T rtm;
} MdlrefDW_INVCPA_T;

#endif                                 /*INVCPA_MDLREF_HIDE_CHILD_*/

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real32_T PhaUACmd;              /* '<Root>/Switch1'
                                        * Phase A voltage command
                                        */
extern real32_T PhaUBCmd;              /* '<Root>/Switch2'
                                        * Phase B voltage command
                                        */
extern real32_T PhaUCCmd;              /* '<Root>/Switch3'
                                        * Phase C voltage command
                                        */
extern void INVCPA(const real32_T *rtu_PhaUDCmd, const real32_T *rtu_PhaUQCmd,
                   const real32_T rtu_MotPosnTrig[6]);

/* Model reference registration function */
extern void INVCPA_initialize(const char_T **rt_errorStatus);

/* Exported data declaration */

/* Calibration memory section */
/* Declaration for custom storage class: Calibration */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaUACmdDialEna_C;/* Referenced by: '<Root>/Constant2' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUACmdDialVal_C;/* Referenced by: '<Root>/Constant3' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaUBCmdDialEna_C;/* Referenced by: '<Root>/Constant1' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUBCmdDialVal_C;/* Referenced by: '<Root>/Constant4' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaUCCmdDialEna_C;/* Referenced by: '<Root>/Constant5' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUCCmdDialVal_C;/* Referenced by: '<Root>/Constant6' */

/* Signal override value */
#ifndef INVCPA_MDLREF_HIDE_CHILD_

extern MdlrefDW_INVCPA_T INVCPA_MdlrefDW;

#endif                                 /*INVCPA_MDLREF_HIDE_CHILD_*/

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
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
 * '<Root>' : 'INVCPA'
 * '<S1>'   : 'INVCPA/Model Info'
 */
#endif                                 /* RTW_HEADER_INVCPA_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
