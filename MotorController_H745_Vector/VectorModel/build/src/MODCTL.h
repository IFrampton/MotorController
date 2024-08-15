/*
 * File: MODCTL.h
 *
 * Code generated for Simulink model 'MODCTL'.
 *
 * Model version                  : 1.60
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:12:12 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_MODCTL_h_
#define RTW_HEADER_MODCTL_h_
#ifndef MODCTL_COMMON_INCLUDES_
#define MODCTL_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* MODCTL_COMMON_INCLUDES_ */

#include "MODCTL_types.h"

/* Block signals for model 'MODCTL' */
#ifndef MODCTL_MDLREF_HIDE_CHILD_

typedef struct {
  boolean_T PwrCmd_g;                  /* '<Root>/DriveModeControl' */
  DRIVEMODE DrvMod_b;                  /* '<Root>/DriveModeControl' */
} B_MODCTL_c_T;

#endif                                 /*MODCTL_MDLREF_HIDE_CHILD_*/

/* Block states (default storage) for model 'MODCTL' */
#ifndef MODCTL_MDLREF_HIDE_CHILD_

typedef struct {
  real32_T Tmr;                        /* '<Root>/DriveModeControl' */
  boolean_T DelayInput1_DSTATE;        /* '<S1>/Delay Input1' */
  uint8_T is_c3_MODCTL;                /* '<Root>/DriveModeControl' */
  uint8_T is_ACTIVE;                   /* '<Root>/DriveModeControl' */
  uint8_T is_active_c3_MODCTL;         /* '<Root>/DriveModeControl' */
} DW_MODCTL_f_T;

#endif                                 /*MODCTL_MDLREF_HIDE_CHILD_*/

#ifndef MODCTL_MDLREF_HIDE_CHILD_

/* Real-time Model Data Structure */
struct tag_RTM_MODCTL_T {
  const char_T **errorStatus;
};

#endif                                 /*MODCTL_MDLREF_HIDE_CHILD_*/

#ifndef MODCTL_MDLREF_HIDE_CHILD_

typedef struct {
  RT_MODEL_MODCTL_T rtm;
} MdlrefDW_MODCTL_T;

#endif                                 /*MODCTL_MDLREF_HIDE_CHILD_*/

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern boolean_T PwrCmd;               /* '<Root>/Switch1'
                                        * The command to activate the auxilary power supplies
                                        */
extern DRIVEMODE DrvMod;               /* '<Root>/Switch2'
                                        * The active drive mode
                                        */
extern void MODCTL(const DRIVEMODE *rtu_DrvModReq, const int16_T *rtu_MotSpd,
                   const int16_T *rtu_MotSpdReqCan, const real32_T
                   *rtu_MotTqReqCan, const boolean_T *rtu_MainPwrAcv, const
                   boolean_T *rtu_AuxPwrAcv);

/* Model reference registration function */
extern void MODCTL_initialize(const char_T **rt_errorStatus);

/* Exported data declaration */

/* Calibration memory section */
/* Declaration for custom storage class: Calibration */
extern __attribute__ ((section (".cal_data"))) boolean_T DrvModDialEna_C;/* Referenced by: '<Root>/Constant1' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) DRIVEMODE DrvModDialVal_C;/* Referenced by: '<Root>/Constant4' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) uint16_T MotSpdReqThdModChg_C;/* Referenced by: '<Root>/Constant2' */

/* The motor speed request below which the drive is allowed to change modes */
extern __attribute__ ((section (".cal_data"))) uint16_T MotSpdThdModChg_C;/* Referenced by: '<Root>/Constant' */

/* The motor speed below which the drive is allowed to change modes */
extern __attribute__ ((section (".cal_data"))) real32_T MotTqReqThdModChg_C;/* Referenced by: '<Root>/Constant3' */

/* The motor torque request below which the drive is allowed to change modes */
extern __attribute__ ((section (".cal_data"))) boolean_T PwrCmdDialEna_C;/* Referenced by: '<Root>/Constant5' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) boolean_T PwrCmdDialVal_C;/* Referenced by: '<Root>/Constant6' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) boolean_T WakeRetry_C;/* Referenced by: '<Root>/Constant7' */

/* Flag used to force the drive to try and rewake the board by activiting the power command */
extern __attribute__ ((section (".cal_data"))) real32_T WakeTout_C;
                                  /* Referenced by: '<Root>/DriveModeControl' */

/* The amount of time the control waits for the power activation signal before shutting off the power command and terminating the wake attempt */
#ifndef MODCTL_MDLREF_HIDE_CHILD_

extern MdlrefDW_MODCTL_T MODCTL_MdlrefDW;

#endif                                 /*MODCTL_MDLREF_HIDE_CHILD_*/

#ifndef MODCTL_MDLREF_HIDE_CHILD_

/* Block signals (default storage) */
extern B_MODCTL_c_T MODCTL_B;

/* Block states (default storage) */
extern DW_MODCTL_f_T MODCTL_DW;

#endif                                 /*MODCTL_MDLREF_HIDE_CHILD_*/

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
 * '<Root>' : 'MODCTL'
 * '<S1>'   : 'MODCTL/Detect Increase'
 * '<S2>'   : 'MODCTL/DriveModeControl'
 * '<S3>'   : 'MODCTL/Model Info'
 */
#endif                                 /* RTW_HEADER_MODCTL_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
