/*
 * File: POSTRG.c
 *
 * Code generated for Simulink model 'POSTRG'.
 *
 * Model version                  : 1.184
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:12:17 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "POSTRG.h"
#include "rtwtypes.h"
#include <math.h>
#include "POSTRG_private.h"

MdlrefDW_POSTRG_T POSTRG_MdlrefDW;

/* Output and update for referenced model: 'POSTRG' */
void POSTRG(const real32_T *rtu_MotPosnMag)
{
  int32_T i;

  /* Switch: '<Root>/Switch2' incorporates:
   *  Constant: '<Root>/Constant1'
   */
  if (MotPosnTrigDialEna_C) {
    /* Switch: '<Root>/Switch2' incorporates:
     *  Constant: '<Root>/Constant4'
     */
    for (i = 0; i < 6; i++) {
      MotPosnTrig[i] = MotPosnTrigDialVal_CA[i];
    }
  } else {
    real32_T rtb_CosCordic6;
    real32_T rtb_Product3;
    real32_T rtb_Product4;
    real32_T rtb_Product5;

    /* Trigonometry: '<Root>/Cos Cordic6' */
    rtb_CosCordic6 = cosf(*rtu_MotPosnMag);

    /* Trigonometry: '<Root>/Cos Cordic7' */
    rtb_Product4 = sinf(*rtu_MotPosnMag);

    /* Product: '<Root>/Product3' incorporates:
     *  Constant: '<Root>/Constant7'
     *
     * Block description for '<Root>/Constant7':
     *  sin(2*pi/3)
     */
    rtb_Product3 = rtb_Product4 * 0.866F;

    /* Product: '<Root>/Product2' incorporates:
     *  Constant: '<Root>/Constant3'
     *
     * Block description for '<Root>/Constant3':
     *  cos(2*pi/3)
     */
    rtb_Product5 = rtb_CosCordic6 * -0.5F;

    /* Switch: '<Root>/Switch2' incorporates:
     *  Sum: '<Root>/Add6'
     *  Sum: '<Root>/Add7'
     *  UnaryMinus: '<Root>/Unary Minus3'
     */
    MotPosnTrig[2] = rtb_Product5 - rtb_Product3;
    MotPosnTrig[1] = rtb_Product5 + rtb_Product3;
    MotPosnTrig[3] = -rtb_Product4;

    /* Product: '<Root>/Product5' incorporates:
     *  Constant: '<Root>/Constant7'
     *
     * Block description for '<Root>/Constant7':
     *  sin(2*pi/3)
     */
    rtb_Product5 = rtb_CosCordic6 * 0.866F;

    /* Product: '<Root>/Product4' incorporates:
     *  Constant: '<Root>/Constant3'
     *
     * Block description for '<Root>/Constant3':
     *  cos(2*pi/3)
     */
    rtb_Product4 *= -0.5F;

    /* Switch: '<Root>/Switch2' incorporates:
     *  Sum: '<Root>/Add8'
     *  Sum: '<Root>/Add9'
     *  UnaryMinus: '<Root>/Unary Minus4'
     *  UnaryMinus: '<Root>/Unary Minus5'
     */
    MotPosnTrig[0] = rtb_CosCordic6;
    MotPosnTrig[4] = -(rtb_Product4 - rtb_Product5);
    MotPosnTrig[5] = -(rtb_Product4 + rtb_Product5);
  }

  /* End of Switch: '<Root>/Switch2' */
}

/* Model initialize function */
void POSTRG_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_POSTRG_T *const POSTRG_M = &(POSTRG_MdlrefDW.rtm);

  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatusPointer(POSTRG_M, rt_errorStatus);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
