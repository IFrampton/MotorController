/*
 * File: CLAPAR.h
 *
 * Code generated for Simulink model 'CLAPAR'.
 *
 * Model version                  : 1.48
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:11:50 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_CLAPAR_h_
#define RTW_HEADER_CLAPAR_h_
#ifndef CLAPAR_COMMON_INCLUDES_
#define CLAPAR_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* CLAPAR_COMMON_INCLUDES_ */

#include "CLAPAR_types.h"

/* Invariant block signals for model 'CLAPAR' */
#ifndef CLAPAR_MDLREF_HIDE_CHILD_

typedef struct {
  const real32_T Reshape2[3];          /* '<Root>/Reshape2' */
} ConstB_CLAPAR_h_T;

#endif                                 /*CLAPAR_MDLREF_HIDE_CHILD_*/

#ifndef CLAPAR_MDLREF_HIDE_CHILD_

/* Real-time Model Data Structure */
struct tag_RTM_CLAPAR_T {
  const char_T **errorStatus;
};

#endif                                 /*CLAPAR_MDLREF_HIDE_CHILD_*/

#ifndef CLAPAR_MDLREF_HIDE_CHILD_

typedef struct {
  RT_MODEL_CLAPAR_T rtm;
} MdlrefDW_CLAPAR_T;

#endif                                 /*CLAPAR_MDLREF_HIDE_CHILD_*/

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real32_T PhaCurD;               /* '<Root>/Switch1'
                                        * The motor current in the rotating d axis direction (non-torque producing).
                                        */
extern real32_T PhaCurQ;               /* '<Root>/Switch2'
                                        * The motor current in the rotating q axis direction (torque producing).
                                        */
extern void CLAPAR(const real32_T *rtu_PhaCurA, const real32_T *rtu_PhaCurB,
                   const real32_T *rtu_PhaCurC, const real32_T rtu_MotPosnTrig[6]);

/* Model reference registration function */
extern void CLAPAR_initialize(const char_T **rt_errorStatus);

/* Exported data declaration */

/* Calibration memory section */
/* Declaration for custom storage class: Calibration */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaCurDDialEna_C;/* Referenced by: '<Root>/Constant2' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurDDialVal_C;/* Referenced by: '<Root>/Constant3' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaCurQDialEna_C;/* Referenced by: '<Root>/Constant1' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurQDialVal_C;/* Referenced by: '<Root>/Constant4' */

/* Signal override value */
#ifndef CLAPAR_MDLREF_HIDE_CHILD_

extern MdlrefDW_CLAPAR_T CLAPAR_MdlrefDW;

#endif                                 /*CLAPAR_MDLREF_HIDE_CHILD_*/

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<Root>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<Root>/Reshape' : Reshape block reduction
 * Block '<Root>/Reshape1' : Reshape block reduction
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
 * '<Root>' : 'CLAPAR'
 * '<S1>'   : 'CLAPAR/Model Info'
 */
#endif                                 /* RTW_HEADER_CLAPAR_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
