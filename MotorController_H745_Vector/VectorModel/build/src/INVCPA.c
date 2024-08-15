/*
 * File: INVCPA.c
 *
 * Code generated for Simulink model 'INVCPA'.
 *
 * Model version                  : 1.40
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:11:58 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "INVCPA.h"
#include "rtwtypes.h"
#include "INVCPA_private.h"

MdlrefDW_INVCPA_T INVCPA_MdlrefDW;

/* Output and update for referenced model: 'INVCPA' */
void INVCPA(const real32_T *rtu_PhaUDCmd, const real32_T *rtu_PhaUQCmd, const
            real32_T rtu_MotPosnTrig[6])
{
  int32_T i;
  real32_T rtb_MatrixConcatenate[9];
  real32_T rtb_MatrixMultiply[3];
  real32_T rtb_Reshape3_idx_0;
  real32_T rtb_Reshape3_idx_1;

  /* SignalConversion generated from: '<Root>/Matrix Concatenate' incorporates:
   *  Reshape: '<Root>/Reshape1'
   */
  rtb_MatrixConcatenate[6] = INVCPA_ConstB.Reshape1[0];

  /* Reshape: '<Root>/Reshape4' */
  rtb_MatrixConcatenate[0] = rtu_MotPosnTrig[0];

  /* Reshape: '<Root>/Reshape2' */
  rtb_MatrixConcatenate[3] = rtu_MotPosnTrig[3];

  /* SignalConversion generated from: '<Root>/Matrix Concatenate' incorporates:
   *  Reshape: '<Root>/Reshape1'
   */
  rtb_MatrixConcatenate[7] = INVCPA_ConstB.Reshape1[1];

  /* Reshape: '<Root>/Reshape4' */
  rtb_MatrixConcatenate[1] = rtu_MotPosnTrig[1];

  /* Reshape: '<Root>/Reshape2' */
  rtb_MatrixConcatenate[4] = rtu_MotPosnTrig[4];

  /* SignalConversion generated from: '<Root>/Matrix Concatenate' incorporates:
   *  Reshape: '<Root>/Reshape1'
   */
  rtb_MatrixConcatenate[8] = INVCPA_ConstB.Reshape1[2];

  /* Reshape: '<Root>/Reshape4' */
  rtb_MatrixConcatenate[2] = rtu_MotPosnTrig[2];

  /* Reshape: '<Root>/Reshape2' */
  rtb_MatrixConcatenate[5] = rtu_MotPosnTrig[5];

  /* Reshape: '<Root>/Reshape3' */
  rtb_Reshape3_idx_0 = *rtu_PhaUDCmd;
  rtb_Reshape3_idx_1 = *rtu_PhaUQCmd;

  /* Product: '<Root>/Matrix Multiply' incorporates:
   *  Concatenate: '<Root>/Matrix Concatenate'
   *  Gain: '<Root>/Gain'
   *  Reshape: '<Root>/Reshape3'
   *
   * Block description for '<Root>/Gain':
   *  sqrt(2/3)
   */
  for (i = 0; i < 3; i++) {
    rtb_MatrixMultiply[i] = 0.0F;
    rtb_MatrixMultiply[i] += 0.8165F * rtb_MatrixConcatenate[i] *
      rtb_Reshape3_idx_0;
    rtb_MatrixMultiply[i] += rtb_MatrixConcatenate[i + 3] * 0.8165F *
      rtb_Reshape3_idx_1;
    rtb_MatrixMultiply[i] += rtb_MatrixConcatenate[i + 6] * 0.8165F * 0.0F;
  }

  /* End of Product: '<Root>/Matrix Multiply' */

  /* Switch: '<Root>/Switch1' incorporates:
   *  Constant: '<Root>/Constant2'
   */
  if (PhaUACmdDialEna_C) {
    /* Switch: '<Root>/Switch1' incorporates:
     *  Constant: '<Root>/Constant3'
     */
    PhaUACmd = PhaUACmdDialVal_C;
  } else {
    /* Switch: '<Root>/Switch1' */
    PhaUACmd = rtb_MatrixMultiply[0];
  }

  /* End of Switch: '<Root>/Switch1' */

  /* Switch: '<Root>/Switch2' incorporates:
   *  Constant: '<Root>/Constant1'
   */
  if (PhaUBCmdDialEna_C) {
    /* Switch: '<Root>/Switch2' incorporates:
     *  Constant: '<Root>/Constant4'
     */
    PhaUBCmd = PhaUBCmdDialVal_C;
  } else {
    /* Switch: '<Root>/Switch2' */
    PhaUBCmd = rtb_MatrixMultiply[1];
  }

  /* End of Switch: '<Root>/Switch2' */

  /* Switch: '<Root>/Switch3' incorporates:
   *  Constant: '<Root>/Constant5'
   */
  if (PhaUCCmdDialEna_C) {
    /* Switch: '<Root>/Switch3' incorporates:
     *  Constant: '<Root>/Constant6'
     */
    PhaUCCmd = PhaUCCmdDialVal_C;
  } else {
    /* Switch: '<Root>/Switch3' */
    PhaUCCmd = rtb_MatrixMultiply[2];
  }

  /* End of Switch: '<Root>/Switch3' */
}

/* Model initialize function */
void INVCPA_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_INVCPA_T *const INVCPA_M = &(INVCPA_MdlrefDW.rtm);

  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatusPointer(INVCPA_M, rt_errorStatus);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
