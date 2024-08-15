/*
 * File: MEDINP.h
 *
 * Code generated for Simulink model 'MEDINP'.
 *
 * Model version                  : 1.36
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:12:04 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_MEDINP_h_
#define RTW_HEADER_MEDINP_h_
#ifndef MEDINP_COMMON_INCLUDES_
#define MEDINP_COMMON_INCLUDES_
#include <math.h>
#include "rtwtypes.h"
#include "can_message.h"
#endif                                 /* MEDINP_COMMON_INCLUDES_ */

#include "MEDINP_types.h"
#include "FallingDebounce_RDghcENM.h"
#include <string.h>
#include "rtGetInf.h"
#include "rt_nonfinite.h"

/* Block signals for model 'MEDINP' */
#ifndef MEDINP_MDLREF_HIDE_CHILD_

typedef struct {
  CAN_MESSAGE_BUS CANPack;             /* '<Root>/CAN Pack' */
  real_T CANUnpack_o1;                 /* '<Root>/CAN Unpack' */
  real_T CANUnpack_o2;                 /* '<Root>/CAN Unpack' */
  real_T CANUnpack_o3;                 /* '<Root>/CAN Unpack' */
  boolean_T Out;                       /* '<S2>/Debounce' */
} B_MEDINP_c_T;

#endif                                 /*MEDINP_MDLREF_HIDE_CHILD_*/

/* Block states (default storage) for model 'MEDINP' */
#ifndef MEDINP_MDLREF_HIDE_CHILD_

typedef struct {
  int_T CANUnpack_ModeSignalID;        /* '<Root>/CAN Unpack' */
  int_T CANUnpack_StatusPortID;        /* '<Root>/CAN Unpack' */
  uint8_T DelayInput1_DSTATE;          /* '<S1>/Delay Input1' */
  DW_FallingDebounce_RDghcENM_T FallingDebounce;/* '<Root>/FallingDebounce' */
} DW_MEDINP_f_T;

#endif                                 /*MEDINP_MDLREF_HIDE_CHILD_*/

#ifndef MEDINP_MDLREF_HIDE_CHILD_

/* Real-time Model Data Structure */
struct tag_RTM_MEDINP_T {
  const char_T **errorStatus;
};

#endif                                 /*MEDINP_MDLREF_HIDE_CHILD_*/

#ifndef MEDINP_MDLREF_HIDE_CHILD_

typedef struct {
  RT_MODEL_MEDINP_T rtm;
} MdlrefDW_MEDINP_T;

#endif                                 /*MEDINP_MDLREF_HIDE_CHILD_*/

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern uint8_T ASWIN_McuReqDa[8];      /* '<Root>/ASWIN_McuReqDa'
                                        * The raw message data frame
                                        */
extern uint8_T ASWIN_McuReqCt;         /* '<Root>/ASWIN_McuReqCt'
                                        * The raw message counter used to indicate message freshness
                                        */
extern real32_T MotTqReqCan;           /* '<Root>/Switch4'
                                        * The requested motor torque
                                        */
extern int16_T MotSpdReqCan;           /* '<Root>/Switch5'
                                        * The requested motor speed
                                        */
extern DRIVEMODE DrvModReq;            /* '<Root>/Switch3'
                                        * The requested drive mode
                                        */
extern void MEDINP_Init(void);
extern void MEDINP_Start(void);
extern void MEDINP(void);

/* Model reference registration function */
extern void MEDINP_initialize(const char_T **rt_errorStatus);

/* Exported data declaration */

/* Calibration memory section */
/* Declaration for custom storage class: Calibration */
extern __attribute__ ((section (".cal_data"))) DRIVEMODE DrvModReqDft_C;/* Referenced by: '<Root>/Constant3' */

/* The default value used for this signal when the message has timedout */
extern __attribute__ ((section (".cal_data"))) boolean_T DrvModReqDialEna_C;/* Referenced by: '<Root>/Constant6' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) DRIVEMODE DrvModReqDialVal_C;/* Referenced by: '<Root>/Constant7' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T McuReqTout_C;/* Referenced by: '<Root>/Constant1' */

/* Timeout time for the MCUReq message */
extern __attribute__ ((section (".cal_data"))) int16_T MotSpdReqCanDft_C;/* Referenced by: '<Root>/Constant5' */

/* The default value used for this signal when the message has timedout */
extern __attribute__ ((section (".cal_data"))) boolean_T MotSpdReqCanDialEna_C;/* Referenced by: '<Root>/Constant10' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) int16_T MotSpdReqCanDialVal_C;/* Referenced by: '<Root>/Constant11' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T MotTqReqCanDft_C;/* Referenced by: '<Root>/Constant4' */

/* The default value used for this signal when the message has timedout */
extern __attribute__ ((section (".cal_data"))) boolean_T MotTqReqCanDialEna_C;/* Referenced by: '<Root>/Constant8' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T MotTqReqCanDialVal_C;/* Referenced by: '<Root>/Constant9' */

/* Signal override value */
#ifndef MEDINP_MDLREF_HIDE_CHILD_

extern MdlrefDW_MEDINP_T MEDINP_MdlrefDW;

#endif                                 /*MEDINP_MDLREF_HIDE_CHILD_*/

#ifndef MEDINP_MDLREF_HIDE_CHILD_

/* Block signals (default storage) */
extern B_MEDINP_c_T MEDINP_B;

/* Block states (default storage) */
extern DW_MEDINP_f_T MEDINP_DW;

#endif                                 /*MEDINP_MDLREF_HIDE_CHILD_*/

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
 * '<Root>' : 'MEDINP'
 * '<S1>'   : 'MEDINP/Detect Change'
 * '<S2>'   : 'MEDINP/FallingDebounce'
 * '<S3>'   : 'MEDINP/Model Info'
 * '<S4>'   : 'MEDINP/FallingDebounce/Debounce'
 */
#endif                                 /* RTW_HEADER_MEDINP_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
