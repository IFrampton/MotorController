/*
 * File: GATOUP.h
 *
 * Code generated for Simulink model 'GATOUP'.
 *
 * Model version                  : 1.75
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:11:56 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_GATOUP_h_
#define RTW_HEADER_GATOUP_h_
#ifndef GATOUP_COMMON_INCLUDES_
#define GATOUP_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* GATOUP_COMMON_INCLUDES_ */

#include "GATOUP_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#ifndef GATOUP_MDLREF_HIDE_CHILD_

/* Real-time Model Data Structure */
struct tag_RTM_GATOUP_T {
  const char_T **errorStatus;
};

#endif                                 /*GATOUP_MDLREF_HIDE_CHILD_*/

#ifndef GATOUP_MDLREF_HIDE_CHILD_

typedef struct {
  RT_MODEL_GATOUP_T rtm;
} MdlrefDW_GATOUP_T;

#endif                                 /*GATOUP_MDLREF_HIDE_CHILD_*/

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern uint16_T ASWOUT_PhaAPwmDc;      /* '<Root>/Switch'
                                        * The raw modulation command used by the hardware PWM generator
                                        */
extern uint16_T ASWOUT_PhaBPwmDc;      /* '<Root>/Switch1'
                                        * The raw modulation command used by the hardware PWM generator
                                        */
extern uint16_T ASWOUT_PhaCPwmDc;      /* '<Root>/Switch2'
                                        * The raw modulation command used by the hardware PWM generator
                                        */
extern void GATOUP(const real32_T *rtu_PhaUACmd, const real32_T *rtu_PhaUBCmd,
                   const real32_T *rtu_PhaUCCmd, const real32_T *rtu_HvBusU);

/* Model reference registration function */
extern void GATOUP_initialize(const char_T **rt_errorStatus);

/* Exported data declaration */

/* Calibration memory section */
/* Declaration for custom storage class: Calibration */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaAPwmDcDialEna_C;/* Referenced by: '<Root>/Constant' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) uint16_T PhaAPwmDcDialVal_C;/* Referenced by: '<Root>/Constant1' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaBPwmDcDialEna_C;/* Referenced by: '<Root>/Constant2' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) uint16_T PhaBPwmDcDialVal_C;/* Referenced by: '<Root>/Constant3' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaCPwmDcDialEna_C;/* Referenced by: '<Root>/Constant4' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) uint16_T PhaCPwmDcDialVal_C;/* Referenced by: '<Root>/Constant5' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) int16_T ReloadRegisterMax_C;/* Referenced by:
                                                                      * '<Root>/Constant10'
                                                                      * '<Root>/Constant11'
                                                                      * '<Root>/Constant6'
                                                                      * '<Root>/Constant8'
                                                                      */

/* The maximum value of the register used by the hardware PWM generator */
#ifndef GATOUP_MDLREF_HIDE_CHILD_

extern MdlrefDW_GATOUP_T GATOUP_MdlrefDW;

#endif                                 /*GATOUP_MDLREF_HIDE_CHILD_*/

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/Data Type Duplicate' : Unused code path elimination
 * Block '<S2>/Data Type Propagation' : Unused code path elimination
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
 * '<Root>' : 'GATOUP'
 * '<S1>'   : 'GATOUP/Model Info'
 * '<S2>'   : 'GATOUP/Saturation Dynamic'
 */
#endif                                 /* RTW_HEADER_GATOUP_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
