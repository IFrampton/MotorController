/*
 * File: MEDOUP.h
 *
 * Code generated for Simulink model 'MEDOUP'.
 *
 * Model version                  : 1.21
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:12:09 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_MEDOUP_h_
#define RTW_HEADER_MEDOUP_h_
#ifndef MEDOUP_COMMON_INCLUDES_
#define MEDOUP_COMMON_INCLUDES_
#include <math.h>
#include "rtwtypes.h"
#endif                                 /* MEDOUP_COMMON_INCLUDES_ */

#include "MEDOUP_types.h"

/* Block signals for model 'MEDOUP' */
#ifndef MEDOUP_MDLREF_HIDE_CHILD_

typedef struct {
  CAN_MESSAGE_BUS CANPack;             /* '<Root>/CAN Pack' */
  uint8_T MultiportSwitch;             /* '<Root>/Multiport Switch' */
} B_MEDOUP_c_T;

#endif                                 /*MEDOUP_MDLREF_HIDE_CHILD_*/

/* Block states (default storage) for model 'MEDOUP' */
#ifndef MEDOUP_MDLREF_HIDE_CHILD_

typedef struct {
  int_T CANPack_ModeSignalID;          /* '<Root>/CAN Pack' */
} DW_MEDOUP_f_T;

#endif                                 /*MEDOUP_MDLREF_HIDE_CHILD_*/

#ifndef MEDOUP_MDLREF_HIDE_CHILD_

/* Real-time Model Data Structure */
struct tag_RTM_MEDOUP_T {
  const char_T **errorStatus;
};

#endif                                 /*MEDOUP_MDLREF_HIDE_CHILD_*/

#ifndef MEDOUP_MDLREF_HIDE_CHILD_

typedef struct {
  RT_MODEL_MEDOUP_T rtm;
} MdlrefDW_MEDOUP_T;

#endif                                 /*MEDOUP_MDLREF_HIDE_CHILD_*/

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern uint8_T ASWOUT_McuData1Da[8];   /* '<Root>/Switch'
                                        * The raw message data frame
                                        */
extern void MEDOUP(const real32_T *rtu_HvBusCur, const real32_T *rtu_HvBusU,
                   const real32_T *rtu_PhaCurQ, const int16_T *rtu_MotSpd, const
                   DRIVEMODE *rtu_DrvMod);

/* Model reference registration function */
extern void MEDOUP_initialize(const char_T **rt_errorStatus);

/* Exported data declaration */

/* Calibration memory section */
/* Declaration for custom storage class: Calibration */
extern __attribute__ ((section (".cal_data"))) boolean_T McuData1DaDialEna_C;/* Referenced by: '<Root>/Constant' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) uint8_T McuData1DaDialVal_CA[8];/* Referenced by: '<Root>/Constant1' */

/* Signal override value */
#ifndef MEDOUP_MDLREF_HIDE_CHILD_

extern MdlrefDW_MEDOUP_T MEDOUP_MdlrefDW;

#endif                                 /*MEDOUP_MDLREF_HIDE_CHILD_*/

#ifndef MEDOUP_MDLREF_HIDE_CHILD_

/* Block signals (default storage) */
extern B_MEDOUP_c_T MEDOUP_B;

/* Block states (default storage) */
extern DW_MEDOUP_f_T MEDOUP_DW;

#endif                                 /*MEDOUP_MDLREF_HIDE_CHILD_*/

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<Root>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<Root>/Data Type Conversion2' : Eliminate redundant data type conversion
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
 * '<Root>' : 'MEDOUP'
 * '<S1>'   : 'MEDOUP/Model Info'
 */
#endif                                 /* RTW_HEADER_MEDOUP_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
