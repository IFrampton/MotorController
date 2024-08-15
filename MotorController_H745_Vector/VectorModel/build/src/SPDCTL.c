/*
 * File: SPDCTL.c
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

#include "SPDCTL.h"
#include "rtwtypes.h"
#include "SPDCTL_types.h"
#include "RateLimit_8K29mxJB.h"
#include <math.h>
#include "rt_nonfinite.h"
#include "SPDCTL_private.h"

/* Exported block signals */
int16_T MotSpdCmd;                     /* '<Root>/Data Type Conversion1'
                                        * The motor speed command the controller is controlling to
                                        */
MdlrefDW_SPDCTL_T SPDCTL_MdlrefDW;

/* Block states (default storage) */
DW_SPDCTL_f_T SPDCTL_DW;

/* Output and update for referenced model: 'SPDCTL' */
void SPDCTL(const int16_T *rtu_MotSpd, const DRIVEMODE *rtu_DrvMod, const
            int16_T *rtu_MotSpdReqCan, const real32_T *rtu_MotTqMax)
{
  real32_T rtb_Accumulator;
  real32_T rtb_Add;
  int16_T rtb_UnaryMinus3;
  boolean_T rtb_LowerRelop1;

  /* RelationalOperator: '<S6>/LowerRelop1' incorporates:
   *  Constant: '<Root>/Constant11'
   */
  rtb_LowerRelop1 = (*rtu_MotSpdReqCan > MotSpdReqMax_C);

  /* Switch: '<S6>/Switch2' incorporates:
   *  Constant: '<Root>/Constant11'
   */
  if (rtb_LowerRelop1) {
    rtb_UnaryMinus3 = MotSpdReqMax_C;
  } else {
    /* UnaryMinus: '<Root>/Unary Minus3' incorporates:
     *  Constant: '<Root>/Constant11'
     */
    rtb_UnaryMinus3 = (int16_T)-MotSpdReqMax_C;

    /* RelationalOperator: '<S6>/UpperRelop' incorporates:
     *  Constant: '<Root>/Constant11'
     *  UnaryMinus: '<Root>/Unary Minus3'
     */
    rtb_LowerRelop1 = (*rtu_MotSpdReqCan < (int16_T)-MotSpdReqMax_C);

    /* Switch: '<S6>/Switch' */
    if (!rtb_LowerRelop1) {
      rtb_UnaryMinus3 = *rtu_MotSpdReqCan;
    }

    /* End of Switch: '<S6>/Switch' */
  }

  /* End of Switch: '<S6>/Switch2' */

  /* Outputs for Atomic SubSystem: '<Root>/RateLimit' */
  /* Constant: '<Root>/Constant8' incorporates:
   *  Constant: '<Root>/Constant7'
   */
  RateLimit_8K29mxJB(rtb_UnaryMinus3, MotSpdRateLim_C, 0.01F, &rtb_Accumulator,
                     &SPDCTL_DW.RateLimit);

  /* End of Outputs for SubSystem: '<Root>/RateLimit' */

  /* DataTypeConversion: '<Root>/Data Type Conversion1' */
  rtb_Accumulator = floorf(rtb_Accumulator);
  if (rtIsNaNF(rtb_Accumulator) || rtIsInfF(rtb_Accumulator)) {
    rtb_Accumulator = 0.0F;
  } else {
    rtb_Accumulator = fmodf(rtb_Accumulator, 65536.0F);
  }

  /* DataTypeConversion: '<Root>/Data Type Conversion1' */
  MotSpdCmd = (int16_T)(rtb_Accumulator < 0.0F ? (int32_T)(int16_T)-(int16_T)
                        (uint16_T)-rtb_Accumulator : (int32_T)(int16_T)(uint16_T)
                        rtb_Accumulator);

  /* Sum: '<Root>/Subtract' */
  rtb_UnaryMinus3 = (int16_T)(MotSpdCmd - *rtu_MotSpd);

  /* Switch: '<Root>/Switch2' incorporates:
   *  Constant: '<Root>/Constant17'
   *  Constant: '<Root>/Constant4'
   *  Product: '<Root>/Product1'
   *  UnitDelay: '<Root>/Unit Delay'
   */
  if (SPDCTL_DW.UnitDelay_DSTATE) {
    rtb_Accumulator = (real32_T)rtb_UnaryMinus3 * 0.01F;
  } else {
    rtb_Accumulator = 0.0F;
  }

  /* End of Switch: '<Root>/Switch2' */

  /* RelationalOperator: '<Root>/Relational Operator' incorporates:
   *  Constant: '<S1>/Constant'
   */
  rtb_LowerRelop1 = (*rtu_DrvMod != SPD_CTRL);

  /* DiscreteIntegrator: '<Root>/Accumulator' */
  if (rtb_LowerRelop1 || (SPDCTL_DW.Accumulator_PrevResetState != 0)) {
    SPDCTL_DW.Accumulator_DSTATE = 0.0F;
  }

  /* Sum: '<Root>/Add' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Constant: '<Root>/Constant5'
   *  DiscreteIntegrator: '<Root>/Accumulator'
   *  Product: '<Root>/Product'
   *  Product: '<Root>/Product2'
   */
  rtb_Add = (real32_T)rtb_UnaryMinus3 * MotTqGainP_C +
    SPDCTL_DW.Accumulator_DSTATE * MotTqGainI_C;

  /* Switch: '<Root>/Switch3' incorporates:
   *  Constant: '<Root>/Constant2'
   *  RelationalOperator: '<S5>/LowerRelop1'
   *  RelationalOperator: '<S5>/UpperRelop'
   *  Switch: '<Root>/Switch'
   *  Switch: '<S5>/Switch'
   *  Switch: '<S5>/Switch2'
   *  UnaryMinus: '<Root>/Unary Minus1'
   */
  if (MotTqCmdSpdCtlDialEna_C) {
    /* Switch: '<Root>/Switch3' incorporates:
     *  Constant: '<Root>/Constant6'
     */
    MotTqCmdSpdCtl = MotTqCmdSpdCtlDialVal_C;
  } else if (rtb_LowerRelop1) {
    /* Switch: '<Root>/Switch' incorporates:
     *  Constant: '<Root>/Constant3'
     *  Switch: '<Root>/Switch3'
     */
    MotTqCmdSpdCtl = 0.0F;
  } else if (rtb_Add > *rtu_MotTqMax) {
    /* Switch: '<S5>/Switch2' incorporates:
     *  Switch: '<Root>/Switch'
     *  Switch: '<Root>/Switch3'
     */
    MotTqCmdSpdCtl = *rtu_MotTqMax;
  } else if (rtb_Add < -*rtu_MotTqMax) {
    /* Switch: '<S5>/Switch' incorporates:
     *  Switch: '<Root>/Switch'
     *  Switch: '<Root>/Switch3'
     *  Switch: '<S5>/Switch2'
     *  UnaryMinus: '<Root>/Unary Minus1'
     */
    MotTqCmdSpdCtl = -*rtu_MotTqMax;
  } else {
    /* Switch: '<Root>/Switch3' incorporates:
     *  Switch: '<Root>/Switch'
     *  Switch: '<S5>/Switch'
     *  Switch: '<S5>/Switch2'
     */
    MotTqCmdSpdCtl = rtb_Add;
  }

  /* End of Switch: '<Root>/Switch3' */

  /* Update for UnitDelay: '<Root>/Unit Delay' incorporates:
   *  Logic: '<S2>/FixPt Logical Operator'
   *  RelationalOperator: '<S2>/Lower Test'
   *  RelationalOperator: '<S2>/Upper Test'
   *  UnaryMinus: '<Root>/Unary Minus2'
   */
  SPDCTL_DW.UnitDelay_DSTATE = ((-*rtu_MotTqMax <= rtb_Add) && (rtb_Add <=
    *rtu_MotTqMax));

  /* Update for DiscreteIntegrator: '<Root>/Accumulator' */
  if (!rtb_LowerRelop1) {
    SPDCTL_DW.Accumulator_DSTATE += rtb_Accumulator;
  }

  SPDCTL_DW.Accumulator_PrevResetState = (int8_T)rtb_LowerRelop1;

  /* End of Update for DiscreteIntegrator: '<Root>/Accumulator' */
}

/* Model initialize function */
void SPDCTL_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_SPDCTL_T *const SPDCTL_M = &(SPDCTL_MdlrefDW.rtm);

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize error status */
  rtmSetErrorStatusPointer(SPDCTL_M, rt_errorStatus);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
