/*
 * File: CURCTL.c
 *
 * Code generated for Simulink model 'CURCTL'.
 *
 * Model version                  : 1.185
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:11:53 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "CURCTL.h"
#include "rtwtypes.h"
#include "CURCTL_types.h"
#include <math.h>
#include "CURCTL_private.h"

MdlrefDW_CURCTL_T CURCTL_MdlrefDW;

/* Block states (default storage) */
DW_CURCTL_f_T CURCTL_DW;

/* Output and update for referenced model: 'CURCTL' */
void CURCTL(const real32_T *rtu_PhaCurD, const real32_T *rtu_PhaCurDTar, const
            real32_T *rtu_HvBusU, const DRIVEMODE *rtu_DrvMod, const real32_T
            *rtu_PhaCurQ, const real32_T *rtu_PhaCurQTar, const real32_T
            *rtu_MotSpdMag)
{
  real32_T rtb_PhaURatio;
  real32_T rtb_Product3;
  real32_T rtb_Product4;
  real32_T rtb_Product8;
  real32_T rtb_Subtract3;
  real32_T rtb_UnaryMinus;
  boolean_T rtb_OpenLoop;

  /* UnaryMinus: '<Root>/Unary Minus' */
  rtb_UnaryMinus = -*rtu_MotSpdMag;

  /* Product: '<Root>/Product3' incorporates:
   *  Constant: '<Root>/Constant6'
   */
  rtb_Product3 = rtb_UnaryMinus * *rtu_PhaCurQTar * StatorInductanceQ_C;

  /* Sum: '<Root>/Subtract' */
  rtb_UnaryMinus = *rtu_PhaCurDTar - *rtu_PhaCurD;

  /* RelationalOperator: '<Root>/Relational Operator1' incorporates:
   *  Constant: '<S1>/Constant'
   */
  rtb_OpenLoop = (*rtu_DrvMod == OPEN_LOOP);

  /* DiscreteIntegrator: '<Root>/Accumulator2' */
  if (rtb_OpenLoop || (CURCTL_DW.Accumulator2_PrevResetState != 0)) {
    CURCTL_DW.Accumulator2_DSTATE = 0.0F;
  }

  /* Sum: '<Root>/Add' incorporates:
   *  Constant: '<Root>/Constant1'
   *  DiscreteIntegrator: '<Root>/Accumulator2'
   *  Product: '<Root>/Product'
   */
  rtb_Product3 = (rtb_UnaryMinus * PhaUDGainP_C + rtb_Product3) +
    CURCTL_DW.Accumulator2_DSTATE;

  /* Product: '<Root>/Product8' incorporates:
   *  Constant: '<Root>/Constant11'
   */
  rtb_Product8 = *rtu_MotSpdMag * FluxLinkage_C;

  /* Product: '<Root>/Product4' incorporates:
   *  Constant: '<Root>/Constant7'
   */
  rtb_Product4 = *rtu_MotSpdMag * *rtu_PhaCurDTar * StatorInductanceD_C;

  /* Sum: '<Root>/Subtract3' */
  rtb_Subtract3 = *rtu_PhaCurQTar - *rtu_PhaCurQ;

  /* DiscreteIntegrator: '<Root>/Accumulator1' */
  if (rtb_OpenLoop || (CURCTL_DW.Accumulator1_PrevResetState != 0)) {
    CURCTL_DW.Accumulator1_DSTATE = 0.0F;
  }

  /* Sum: '<Root>/Add1' incorporates:
   *  Constant: '<Root>/Constant8'
   *  DiscreteIntegrator: '<Root>/Accumulator1'
   *  Product: '<Root>/Product5'
   *  Sum: '<Root>/Add2'
   */
  rtb_Product8 = ((rtb_Product8 + rtb_Product4) + rtb_Subtract3 * PhaUQGainP_C)
    + CURCTL_DW.Accumulator1_DSTATE;

  /* Gain: '<Root>/Gain'
   *
   * Block description for '<Root>/Gain':
   *  2/3
   */
  rtb_PhaURatio = 0.6667F * *rtu_HvBusU;

  /* Product: '<Root>/Divide' incorporates:
   *  Constant: '<Root>/Constant'
   *  Constant: '<Root>/Constant20'
   *  Math: '<Root>/Square'
   *  Math: '<Root>/Square1'
   *  MinMax: '<Root>/Max'
   *  MinMax: '<Root>/Max1'
   *  Sqrt: '<Root>/Square Root'
   *  Sum: '<Root>/Add3'
   */
  rtb_PhaURatio = fminf(rtb_PhaURatio, PhaUMaxVal_C) / fmaxf(sqrtf(rtb_Product3 *
    rtb_Product3 + rtb_Product8 * rtb_Product8), 0.1F);

  /* Product: '<Root>/Product10' incorporates:
   *  Abs: '<Root>/Abs1'
   */
  rtb_Product4 = rtb_PhaURatio * fabsf(rtb_Product8);

  /* Switch: '<S4>/Switch2' incorporates:
   *  RelationalOperator: '<S4>/LowerRelop1'
   */
  if (!(rtb_Product8 > rtb_Product4)) {
    /* Switch: '<S4>/Switch' incorporates:
     *  RelationalOperator: '<S4>/UpperRelop'
     *  UnaryMinus: '<Root>/Unary Minus2'
     */
    if (rtb_Product8 < -rtb_Product4) {
      rtb_Product4 = -rtb_Product4;
    } else {
      rtb_Product4 = rtb_Product8;
    }

    /* End of Switch: '<S4>/Switch' */
  }

  /* End of Switch: '<S4>/Switch2' */

  /* Switch: '<Root>/Switch3' incorporates:
   *  Constant: '<Root>/Constant15'
   *  Switch: '<Root>/Switch2'
   */
  if (PhaUQCmdDialEna_C) {
    /* Switch: '<Root>/Switch3' incorporates:
     *  Constant: '<Root>/Constant16'
     */
    PhaUQCmd = PhaUQCmdDialVal_C;
  } else if (rtb_OpenLoop) {
    /* Switch: '<Root>/Switch2' incorporates:
     *  Constant: '<Root>/Constant18'
     *  Switch: '<Root>/Switch3'
     */
    PhaUQCmd = PhaUQCmdOpenLoop_C;
  } else {
    /* Switch: '<Root>/Switch3' incorporates:
     *  Switch: '<Root>/Switch2'
     */
    PhaUQCmd = rtb_Product4;
  }

  /* End of Switch: '<Root>/Switch3' */

  /* Product: '<Root>/Product9' incorporates:
   *  Abs: '<Root>/Abs'
   */
  rtb_PhaURatio *= fabsf(rtb_Product3);

  /* Switch: '<S3>/Switch2' incorporates:
   *  RelationalOperator: '<S3>/LowerRelop1'
   */
  if (!(rtb_Product3 > rtb_PhaURatio)) {
    /* Switch: '<S3>/Switch' incorporates:
     *  RelationalOperator: '<S3>/UpperRelop'
     *  UnaryMinus: '<Root>/Unary Minus1'
     */
    if (rtb_Product3 < -rtb_PhaURatio) {
      rtb_PhaURatio = -rtb_PhaURatio;
    } else {
      rtb_PhaURatio = rtb_Product3;
    }

    /* End of Switch: '<S3>/Switch' */
  }

  /* End of Switch: '<S3>/Switch2' */

  /* Switch: '<Root>/Switch1' incorporates:
   *  Constant: '<Root>/Constant2'
   *  Switch: '<Root>/Switch4'
   */
  if (PhaUDCmdDialEna_C) {
    /* Switch: '<Root>/Switch1' incorporates:
     *  Constant: '<Root>/Constant3'
     */
    PhaUDCmd = PhaUDCmdDialVal_C;
  } else if (rtb_OpenLoop) {
    /* Switch: '<Root>/Switch4' incorporates:
     *  Constant: '<Root>/Constant13'
     *  Switch: '<Root>/Switch1'
     */
    PhaUDCmd = PhaUDCmdOpenLoop_C;
  } else {
    /* Switch: '<Root>/Switch1' incorporates:
     *  Switch: '<Root>/Switch4'
     */
    PhaUDCmd = rtb_PhaURatio;
  }

  /* End of Switch: '<Root>/Switch1' */

  /* Update for DiscreteIntegrator: '<Root>/Accumulator2' incorporates:
   *  Constant: '<Root>/Constant17'
   *  Constant: '<Root>/Constant4'
   *  Product: '<Root>/Product1'
   *  Product: '<Root>/Product2'
   *  Sum: '<Root>/Add5'
   *  UnitDelay: '<Root>/Unit Delay'
   */
  if (!rtb_OpenLoop) {
    CURCTL_DW.Accumulator2_DSTATE += rtb_UnaryMinus * 0.0001F * (PhaUDGainI_C -
      CURCTL_DW.UnitDelay_DSTATE);
  }

  CURCTL_DW.Accumulator2_PrevResetState = (int8_T)rtb_OpenLoop;

  /* End of Update for DiscreteIntegrator: '<Root>/Accumulator2' */

  /* Update for DiscreteIntegrator: '<Root>/Accumulator1' incorporates:
   *  Constant: '<Root>/Constant10'
   *  Constant: '<Root>/Constant9'
   *  Product: '<Root>/Product11'
   *  Product: '<Root>/Product6'
   *  Sum: '<Root>/Add4'
   *  UnitDelay: '<Root>/Unit Delay1'
   */
  if (!rtb_OpenLoop) {
    CURCTL_DW.Accumulator1_DSTATE += rtb_Subtract3 * 0.0001F * (PhaUQGainI_C -
      CURCTL_DW.UnitDelay1_DSTATE);
  }

  CURCTL_DW.Accumulator1_PrevResetState = (int8_T)rtb_OpenLoop;

  /* End of Update for DiscreteIntegrator: '<Root>/Accumulator1' */

  /* Update for UnitDelay: '<Root>/Unit Delay1' incorporates:
   *  Constant: '<Root>/Constant19'
   *  Product: '<Root>/Product7'
   *  Sum: '<Root>/Subtract1'
   */
  CURCTL_DW.UnitDelay1_DSTATE = (rtb_Product8 - rtb_Product4) *
    PhaUQAntiWindupGain_C;

  /* Update for UnitDelay: '<Root>/Unit Delay' incorporates:
   *  Constant: '<Root>/Constant21'
   *  Product: '<Root>/Product12'
   *  Sum: '<Root>/Subtract2'
   */
  CURCTL_DW.UnitDelay_DSTATE = (rtb_Product3 - rtb_PhaURatio) *
    PhaUDAntiWindupGain_C;
}

/* Model initialize function */
void CURCTL_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_CURCTL_T *const CURCTL_M = &(CURCTL_MdlrefDW.rtm);

  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatusPointer(CURCTL_M, rt_errorStatus);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
