/*
 * File: POSTRG.h
 *
 * Code generated for Simulink model 'POSTRG'.
 *
 * Model version                  : 1.184
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:12:17 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_POSTRG_h_
#define RTW_HEADER_POSTRG_h_
#ifndef POSTRG_COMMON_INCLUDES_
#define POSTRG_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* POSTRG_COMMON_INCLUDES_ */

#include "POSTRG_types.h"
#ifndef POSTRG_MDLREF_HIDE_CHILD_

/* Real-time Model Data Structure */
struct tag_RTM_POSTRG_T {
  const char_T **errorStatus;
};

#endif                                 /*POSTRG_MDLREF_HIDE_CHILD_*/

#ifndef POSTRG_MDLREF_HIDE_CHILD_

typedef struct {
  RT_MODEL_POSTRG_T rtm;
} MdlrefDW_POSTRG_T;

#endif                                 /*POSTRG_MDLREF_HIDE_CHILD_*/

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real32_T MotPosnTrig[6];        /* '<Root>/Switch2'
                                        * The results of the trig calculations that are used in the reference frame transforms
                                        */
extern void POSTRG(const real32_T *rtu_MotPosnMag);

/* Model reference registration function */
extern void POSTRG_initialize(const char_T **rt_errorStatus);

/* Exported data declaration */

/* Calibration memory section */
/* Declaration for custom storage class: Calibration */
extern __attribute__ ((section (".cal_data"))) boolean_T MotPosnTrigDialEna_C;/* Referenced by: '<Root>/Constant1' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T MotPosnTrigDialVal_CA[6];/* Referenced by: '<Root>/Constant4' */

/* Signal override value */
#ifndef POSTRG_MDLREF_HIDE_CHILD_

extern MdlrefDW_POSTRG_T POSTRG_MdlrefDW;

#endif                                 /*POSTRG_MDLREF_HIDE_CHILD_*/

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<Root>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<Root>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<Root>/Data Type Conversion4' : Eliminate redundant data type conversion
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
 * '<Root>' : 'POSTRG'
 * '<S1>'   : 'POSTRG/Model Info'
 */
#endif                                 /* RTW_HEADER_POSTRG_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
