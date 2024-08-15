/*
 * File: TRQCTL.h
 *
 * Code generated for Simulink model 'TRQCTL'.
 *
 * Model version                  : 1.70
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:12:33 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_TRQCTL_h_
#define RTW_HEADER_TRQCTL_h_
#ifndef TRQCTL_COMMON_INCLUDES_
#define TRQCTL_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* TRQCTL_COMMON_INCLUDES_ */

#include "TRQCTL_types.h"
#ifndef TRQCTL_MDLREF_HIDE_CHILD_

/* Real-time Model Data Structure */
struct tag_RTM_TRQCTL_T {
  const char_T **errorStatus;
};

#endif                                 /*TRQCTL_MDLREF_HIDE_CHILD_*/

#ifndef TRQCTL_MDLREF_HIDE_CHILD_

typedef struct {
  RT_MODEL_TRQCTL_T rtm;
} MdlrefDW_TRQCTL_T;

#endif                                 /*TRQCTL_MDLREF_HIDE_CHILD_*/

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real32_T MotTqMax;              /* '<Root>/Switch1'
                                        * The maximum motor torque after derates
                                        */
extern real32_T MotTqCmd;              /* '<S2>/Switch2'
                                        * The commanded motor torque after arbitration and limitations
                                        */
extern real32_T PhaCurQTar;            /* '<Root>/Switch3'
                                        * The target q-axis current
                                        */
extern real32_T PhaCurDTar;            /* '<Root>/Constant3'
                                        * The target d-axis current
                                        */
extern void TRQCTL(const real32_T *rtu_MotTqCmdSpdCtl, const DRIVEMODE
                   *rtu_DrvMod, const real32_T *rtu_MotTqReqCan, const real32_T *
                   rtu_BdT1, const real32_T *rtu_BdT2, const int16_T *rtu_MotSpd);

/* Model reference registration function */
extern void TRQCTL_initialize(const char_T **rt_errorStatus);

/* Exported data declaration */

/* Calibration memory section */
/* Declaration for custom storage class: Calibration */
extern __attribute__ ((section (".cal_data"))) real32_T MotTqCon_C;/* Referenced by: '<Root>/Constant1' */

/* The motor constant that maps between current and torque */
extern __attribute__ ((section (".cal_data"))) real32_T MotTqGainBdT1_Ax[5];
                                 /* Referenced by: '<Root>/1-D Lookup Table1' */

/* The axis for the table that maps between the board temperature and the gain that limits the maximum motor torque */
extern __attribute__ ((section (".cal_data"))) real32_T MotTqGainBdT1_T[5];
                                 /* Referenced by: '<Root>/1-D Lookup Table1' */

/* The table values for the table that maps between the board temperature and the gain that limits the maximum motor torque */
extern __attribute__ ((section (".cal_data"))) real32_T MotTqGainBdT2_Ax[5];
                                 /* Referenced by: '<Root>/1-D Lookup Table3' */

/* The axis for the table that maps between the board temperature and the gain that limits the maximum motor torque */
extern __attribute__ ((section (".cal_data"))) real32_T MotTqGainBdT2_T[5];
                                 /* Referenced by: '<Root>/1-D Lookup Table3' */

/* The table values for the table that maps between the board temperature and the gain that limits the maximum motor torque */
extern __attribute__ ((section (".cal_data"))) boolean_T MotTqMaxDialEna_C;/* Referenced by: '<Root>/Constant4' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T MotTqMaxDialVal_C;/* Referenced by: '<Root>/Constant5' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T MotTqMaxMotSpd_Ax[5];
                                 /* Referenced by: '<Root>/1-D Lookup Table2' */

/* The axis values for the table that maps between the motor speed and the maximum motor torque */
extern __attribute__ ((section (".cal_data"))) real32_T MotTqMaxMotSpd_T[5];
                                 /* Referenced by: '<Root>/1-D Lookup Table2' */

/* The table values for the table that maps between the motor speed and the maximum motor torque */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurDTarVal_C;/* Referenced by: '<Root>/Constant3' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaCurQTarDialEna_C;/* Referenced by: '<Root>/Constant2' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurQTarDialVal_C;/* Referenced by: '<Root>/Constant6' */

/* Signal override value */
#ifndef TRQCTL_MDLREF_HIDE_CHILD_

extern MdlrefDW_TRQCTL_T TRQCTL_MdlrefDW;

#endif                                 /*TRQCTL_MDLREF_HIDE_CHILD_*/

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/Data Type Duplicate' : Unused code path elimination
 * Block '<S2>/Data Type Propagation' : Unused code path elimination
 * Block '<Root>/Data Type Conversion' : Eliminate redundant data type conversion
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
 * '<Root>' : 'TRQCTL'
 * '<S1>'   : 'TRQCTL/Model Info'
 * '<S2>'   : 'TRQCTL/Saturation Dynamic'
 */
#endif                                 /* RTW_HEADER_TRQCTL_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
