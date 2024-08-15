/*
 * File: GATOUP.c
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

#include "GATOUP.h"
#include "rtwtypes.h"
#include <math.h>
#include "rt_nonfinite.h"
#include "GATOUP_private.h"

MdlrefDW_GATOUP_T GATOUP_MdlrefDW;

/* Output and update for referenced model: 'GATOUP' */
void GATOUP(const real32_T *rtu_PhaUACmd, const real32_T *rtu_PhaUBCmd, const
            real32_T *rtu_PhaUCCmd, const real32_T *rtu_HvBusU)
{
  real32_T rtb_Gain;
  real32_T rtb_Gain1;
  real32_T rtb_Subtract_idx_0;
  real32_T rtb_Subtract_idx_1;
  real32_T rtb_Subtract_idx_2;
  int16_T rtb_Gain2_n;
  int16_T tmp;
  int16_T tmp_0;

  /* Gain: '<Root>/Gain4' */
  rtb_Subtract_idx_0 = 1000.0F * *rtu_PhaUACmd;
  rtb_Subtract_idx_1 = 1000.0F * *rtu_PhaUBCmd;
  rtb_Subtract_idx_2 = 1000.0F * *rtu_PhaUCCmd;

  /* Gain: '<Root>/Gain1' incorporates:
   *  MinMax: '<Root>/Max'
   *  MinMax: '<Root>/Max1'
   *  Sum: '<Root>/Add'
   */
  rtb_Gain1 = (fmaxf(fmaxf(rtb_Subtract_idx_0, rtb_Subtract_idx_1),
                     rtb_Subtract_idx_2) + fminf(fminf(rtb_Subtract_idx_0,
    rtb_Subtract_idx_1), rtb_Subtract_idx_2)) * 0.5F;

  /* Gain: '<Root>/Gain5' */
  rtb_Gain = 1000.0F * *rtu_HvBusU;

  /* Gain: '<Root>/Gain' incorporates:
   *  Constant: '<Root>/Constant7'
   *  MinMax: '<Root>/Max2'
   */
  rtb_Gain = 0.5F * fmaxf(rtb_Gain, 10.0F);

  /* Product: '<Root>/Divide3' incorporates:
   *  Constant: '<Root>/Constant10'
   *  Sum: '<Root>/Subtract'
   */
  rtb_Subtract_idx_0 = floorf((rtb_Subtract_idx_0 - rtb_Gain1) / rtb_Gain);
  if (rtIsNaNF(rtb_Subtract_idx_0) || rtIsInfF(rtb_Subtract_idx_0)) {
    rtb_Subtract_idx_0 = 0.0F;
  } else {
    rtb_Subtract_idx_0 = fmodf(rtb_Subtract_idx_0, 65536.0F);
  }

  rtb_Gain2_n = (int16_T)((rtb_Subtract_idx_0 < 0.0F ? (int32_T)(int16_T)
    -(int16_T)(uint16_T)-rtb_Subtract_idx_0 : (int32_T)(int16_T)(uint16_T)
    rtb_Subtract_idx_0) * ReloadRegisterMax_C);

  /* Switch: '<S2>/Switch2' incorporates:
   *  Constant: '<Root>/Constant6'
   *  Constant: '<Root>/Constant8'
   *  RelationalOperator: '<S2>/LowerRelop1'
   *  RelationalOperator: '<S2>/UpperRelop'
   *  Switch: '<S2>/Switch'
   *  UnaryMinus: '<Root>/Unary Minus'
   */
  if (rtb_Gain2_n > ReloadRegisterMax_C) {
    tmp = ReloadRegisterMax_C;
  } else if (rtb_Gain2_n < (int16_T)-ReloadRegisterMax_C) {
    /* Switch: '<S2>/Switch' incorporates:
     *  Constant: '<Root>/Constant6'
     *  UnaryMinus: '<Root>/Unary Minus'
     */
    tmp = (int16_T)-ReloadRegisterMax_C;
  } else {
    tmp = rtb_Gain2_n;
  }

  /* Product: '<Root>/Divide3' incorporates:
   *  Constant: '<Root>/Constant10'
   *  Sum: '<Root>/Subtract'
   */
  rtb_Subtract_idx_0 = floorf((rtb_Subtract_idx_1 - rtb_Gain1) / rtb_Gain);
  if (rtIsNaNF(rtb_Subtract_idx_0) || rtIsInfF(rtb_Subtract_idx_0)) {
    rtb_Subtract_idx_0 = 0.0F;
  } else {
    rtb_Subtract_idx_0 = fmodf(rtb_Subtract_idx_0, 65536.0F);
  }

  rtb_Gain2_n = (int16_T)((rtb_Subtract_idx_0 < 0.0F ? (int32_T)(int16_T)
    -(int16_T)(uint16_T)-rtb_Subtract_idx_0 : (int32_T)(int16_T)(uint16_T)
    rtb_Subtract_idx_0) * ReloadRegisterMax_C);

  /* Switch: '<S2>/Switch2' incorporates:
   *  Constant: '<Root>/Constant6'
   *  Constant: '<Root>/Constant8'
   *  RelationalOperator: '<S2>/LowerRelop1'
   *  RelationalOperator: '<S2>/UpperRelop'
   *  Switch: '<S2>/Switch'
   *  UnaryMinus: '<Root>/Unary Minus'
   */
  if (rtb_Gain2_n > ReloadRegisterMax_C) {
    tmp_0 = ReloadRegisterMax_C;
  } else if (rtb_Gain2_n < (int16_T)-ReloadRegisterMax_C) {
    /* Switch: '<S2>/Switch' incorporates:
     *  Constant: '<Root>/Constant6'
     *  UnaryMinus: '<Root>/Unary Minus'
     */
    tmp_0 = (int16_T)-ReloadRegisterMax_C;
  } else {
    tmp_0 = rtb_Gain2_n;
  }

  /* Product: '<Root>/Divide3' incorporates:
   *  Constant: '<Root>/Constant10'
   *  Sum: '<Root>/Subtract'
   */
  rtb_Subtract_idx_0 = floorf((rtb_Subtract_idx_2 - rtb_Gain1) / rtb_Gain);
  if (rtIsNaNF(rtb_Subtract_idx_0) || rtIsInfF(rtb_Subtract_idx_0)) {
    rtb_Subtract_idx_0 = 0.0F;
  } else {
    rtb_Subtract_idx_0 = fmodf(rtb_Subtract_idx_0, 65536.0F);
  }

  rtb_Gain2_n = (int16_T)((rtb_Subtract_idx_0 < 0.0F ? (int32_T)(int16_T)
    -(int16_T)(uint16_T)-rtb_Subtract_idx_0 : (int32_T)(int16_T)(uint16_T)
    rtb_Subtract_idx_0) * ReloadRegisterMax_C);

  /* Switch: '<Root>/Switch' incorporates:
   *  Constant: '<Root>/Constant'
   */
  if (PhaAPwmDcDialEna_C) {
    /* Switch: '<Root>/Switch' incorporates:
     *  Constant: '<Root>/Constant1'
     */
    ASWOUT_PhaAPwmDc = PhaAPwmDcDialVal_C;
  } else {
    /* Switch: '<Root>/Switch' incorporates:
     *  Constant: '<Root>/Constant11'
     *  DataTypeConversion: '<Root>/Data Type Conversion'
     *  Gain: '<Root>/Gain2'
     *  Sum: '<Root>/Add1'
     *  Switch: '<S2>/Switch2'
     */
    ASWOUT_PhaAPwmDc = (uint16_T)((int16_T)(tmp + ReloadRegisterMax_C) >> 1);
  }

  /* End of Switch: '<Root>/Switch' */

  /* Switch: '<Root>/Switch1' incorporates:
   *  Constant: '<Root>/Constant2'
   */
  if (PhaBPwmDcDialEna_C) {
    /* Switch: '<Root>/Switch1' incorporates:
     *  Constant: '<Root>/Constant3'
     */
    ASWOUT_PhaBPwmDc = PhaBPwmDcDialVal_C;
  } else {
    /* Switch: '<Root>/Switch1' incorporates:
     *  Constant: '<Root>/Constant11'
     *  DataTypeConversion: '<Root>/Data Type Conversion'
     *  Gain: '<Root>/Gain2'
     *  Sum: '<Root>/Add1'
     *  Switch: '<S2>/Switch2'
     */
    ASWOUT_PhaBPwmDc = (uint16_T)((int16_T)(tmp_0 + ReloadRegisterMax_C) >> 1);
  }

  /* End of Switch: '<Root>/Switch1' */

  /* Switch: '<Root>/Switch2' incorporates:
   *  Constant: '<Root>/Constant4'
   *  Constant: '<Root>/Constant6'
   *  Constant: '<Root>/Constant8'
   *  RelationalOperator: '<S2>/LowerRelop1'
   *  RelationalOperator: '<S2>/UpperRelop'
   *  Switch: '<S2>/Switch'
   *  Switch: '<S2>/Switch2'
   *  UnaryMinus: '<Root>/Unary Minus'
   */
  if (PhaCPwmDcDialEna_C) {
    /* Switch: '<Root>/Switch2' incorporates:
     *  Constant: '<Root>/Constant5'
     */
    ASWOUT_PhaCPwmDc = PhaCPwmDcDialVal_C;
  } else {
    if (rtb_Gain2_n > ReloadRegisterMax_C) {
      /* Switch: '<S2>/Switch2' incorporates:
       *  Constant: '<Root>/Constant8'
       */
      rtb_Gain2_n = ReloadRegisterMax_C;
    } else if (rtb_Gain2_n < (int16_T)-ReloadRegisterMax_C) {
      /* Switch: '<S2>/Switch' incorporates:
       *  Constant: '<Root>/Constant6'
       *  Switch: '<S2>/Switch2'
       *  UnaryMinus: '<Root>/Unary Minus'
       */
      rtb_Gain2_n = (int16_T)-ReloadRegisterMax_C;
    }

    /* Switch: '<Root>/Switch2' incorporates:
     *  Constant: '<Root>/Constant11'
     *  Constant: '<Root>/Constant6'
     *  DataTypeConversion: '<Root>/Data Type Conversion'
     *  Gain: '<Root>/Gain2'
     *  RelationalOperator: '<S2>/UpperRelop'
     *  Sum: '<Root>/Add1'
     *  Switch: '<S2>/Switch'
     *  Switch: '<S2>/Switch2'
     *  UnaryMinus: '<Root>/Unary Minus'
     */
    ASWOUT_PhaCPwmDc = (uint16_T)((int16_T)(rtb_Gain2_n + ReloadRegisterMax_C) >>
      1);
  }

  /* End of Switch: '<Root>/Switch2' */
}

/* Model initialize function */
void GATOUP_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_GATOUP_T *const GATOUP_M = &(GATOUP_MdlrefDW.rtm);

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize error status */
  rtmSetErrorStatusPointer(GATOUP_M, rt_errorStatus);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
