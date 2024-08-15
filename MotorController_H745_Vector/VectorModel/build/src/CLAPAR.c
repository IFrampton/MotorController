/*
 * File: CLAPAR.c
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

#include "CLAPAR.h"
#include "rtwtypes.h"
#include "CLAPAR_private.h"

MdlrefDW_CLAPAR_T CLAPAR_MdlrefDW;

/* Output and update for referenced model: 'CLAPAR' */
void CLAPAR(const real32_T *rtu_PhaCurA, const real32_T *rtu_PhaCurB, const
            real32_T *rtu_PhaCurC, const real32_T rtu_MotPosnTrig[6])
{
  int32_T i;
  real32_T rtb_Gain[9];
  real32_T rtb_MatrixMultiply[3];
  real32_T rtb_Reshape3_idx_0;
  real32_T rtb_Reshape3_idx_1;
  real32_T rtb_Reshape3_idx_2;

  /* Concatenate: '<Root>/Matrix Concatenate' incorporates:
   *  Gain: '<Root>/Gain'
   *  Reshape: '<Root>/Reshape2'
   *
   * Block description for '<Root>/Gain':
   *  sqrt(2/3)
   */
  rtb_Gain[0] = rtu_MotPosnTrig[0];
  rtb_Gain[1] = rtu_MotPosnTrig[3];
  rtb_Gain[2] = CLAPAR_ConstB.Reshape2[0];
  rtb_Gain[3] = rtu_MotPosnTrig[1];
  rtb_Gain[4] = rtu_MotPosnTrig[4];
  rtb_Gain[5] = CLAPAR_ConstB.Reshape2[1];
  rtb_Gain[6] = rtu_MotPosnTrig[2];
  rtb_Gain[7] = rtu_MotPosnTrig[5];
  rtb_Gain[8] = CLAPAR_ConstB.Reshape2[2];

  /* Reshape: '<Root>/Reshape3' */
  rtb_Reshape3_idx_0 = *rtu_PhaCurA;
  rtb_Reshape3_idx_1 = *rtu_PhaCurB;
  rtb_Reshape3_idx_2 = *rtu_PhaCurC;

  /* Product: '<Root>/Matrix Multiply' incorporates:
   *  Gain: '<Root>/Gain'
   *  Reshape: '<Root>/Reshape3'
   *
   * Block description for '<Root>/Gain':
   *  sqrt(2/3)
   */
  for (i = 0; i < 3; i++) {
    rtb_MatrixMultiply[i] = 0.0F;
    rtb_MatrixMultiply[i] += 0.8165F * rtb_Gain[i] * rtb_Reshape3_idx_0;
    rtb_MatrixMultiply[i] += rtb_Gain[i + 3] * 0.8165F * rtb_Reshape3_idx_1;
    rtb_MatrixMultiply[i] += rtb_Gain[i + 6] * 0.8165F * rtb_Reshape3_idx_2;
  }

  /* End of Product: '<Root>/Matrix Multiply' */

  /* Switch: '<Root>/Switch1' incorporates:
   *  Constant: '<Root>/Constant2'
   */
  if (PhaCurDDialEna_C) {
    /* Switch: '<Root>/Switch1' incorporates:
     *  Constant: '<Root>/Constant3'
     */
    PhaCurD = PhaCurDDialVal_C;
  } else {
    /* Switch: '<Root>/Switch1' */
    PhaCurD = rtb_MatrixMultiply[0];
  }

  /* End of Switch: '<Root>/Switch1' */

  /* Switch: '<Root>/Switch2' incorporates:
   *  Constant: '<Root>/Constant1'
   */
  if (PhaCurQDialEna_C) {
    /* Switch: '<Root>/Switch2' incorporates:
     *  Constant: '<Root>/Constant4'
     */
    PhaCurQ = PhaCurQDialVal_C;
  } else {
    /* Switch: '<Root>/Switch2' */
    PhaCurQ = rtb_MatrixMultiply[1];
  }

  /* End of Switch: '<Root>/Switch2' */
}

/* Model initialize function */
void CLAPAR_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_CLAPAR_T *const CLAPAR_M = &(CLAPAR_MdlrefDW.rtm);

  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatusPointer(CLAPAR_M, rt_errorStatus);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
