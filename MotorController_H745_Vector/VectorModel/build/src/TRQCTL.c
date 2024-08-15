/*
 * File: TRQCTL.c
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

#include "TRQCTL.h"
#include "rtwtypes.h"
#include "TRQCTL_types.h"
#include <math.h>
#include "look1_iflf_binlxpw.h"
#include "TRQCTL_private.h"

/* Exported block signals */
real32_T MotTqCmd;                     /* '<S2>/Switch2'
                                        * The commanded motor torque after arbitration and limitations
                                        */
MdlrefDW_TRQCTL_T TRQCTL_MdlrefDW;

/* Output and update for referenced model: 'TRQCTL' */
void TRQCTL(const real32_T *rtu_MotTqCmdSpdCtl, const DRIVEMODE *rtu_DrvMod,
            const real32_T *rtu_MotTqReqCan, const real32_T *rtu_BdT1, const
            real32_T *rtu_BdT2, const int16_T *rtu_MotSpd)
{
  real32_T rtb_uDLookupTable3;

  /* Switch: '<Root>/Switch1' incorporates:
   *  Constant: '<Root>/Constant4'
   */
  if (MotTqMaxDialEna_C) {
    /* Switch: '<Root>/Switch1' incorporates:
     *  Constant: '<Root>/Constant5'
     */
    MotTqMax = MotTqMaxDialVal_C;
  } else {
    real32_T rtb_uDLookupTable1;
    int16_T tmp;

    /* Lookup_n-D: '<Root>/1-D Lookup Table3' */
    rtb_uDLookupTable3 = look1_iflf_binlxpw(*rtu_BdT2, &MotTqGainBdT2_Ax[0],
      &MotTqGainBdT2_T[0], 4U);

    /* Lookup_n-D: '<Root>/1-D Lookup Table1' */
    rtb_uDLookupTable1 = look1_iflf_binlxpw(*rtu_BdT1, &MotTqGainBdT1_Ax[0],
      &MotTqGainBdT1_T[0], 4U);

    /* Abs: '<Root>/Abs' */
    if (*rtu_MotSpd < 0) {
      tmp = (int16_T)-*rtu_MotSpd;
    } else {
      tmp = *rtu_MotSpd;
    }

    /* Switch: '<Root>/Switch1' incorporates:
     *  Abs: '<Root>/Abs'
     *  DataTypeConversion: '<Root>/Data Type Conversion1'
     *  Lookup_n-D: '<Root>/1-D Lookup Table2'
     *  MinMax: '<Root>/Min'
     *  Product: '<Root>/Product1'
     */
    MotTqMax = look1_iflf_binlxpw(tmp, &MotTqMaxMotSpd_Ax[0], &MotTqMaxMotSpd_T
      [0], 4U) * fminf(rtb_uDLookupTable1, rtb_uDLookupTable3);
  }

  /* End of Switch: '<Root>/Switch1' */

  /* MultiPortSwitch: '<Root>/Multiport Switch' incorporates:
   *  Constant: '<Root>/Constant'
   */
  switch (*rtu_DrvMod) {
   case TQ_CTRL:
    rtb_uDLookupTable3 = *rtu_MotTqReqCan;
    break;

   case SPD_CTRL:
    rtb_uDLookupTable3 = *rtu_MotTqCmdSpdCtl;
    break;

   default:
    rtb_uDLookupTable3 = 0.0F;
    break;
  }

  /* End of MultiPortSwitch: '<Root>/Multiport Switch' */

  /* Switch: '<S2>/Switch2' incorporates:
   *  RelationalOperator: '<S2>/LowerRelop1'
   *  RelationalOperator: '<S2>/UpperRelop'
   *  Switch: '<S2>/Switch'
   *  UnaryMinus: '<Root>/Unary Minus'
   */
  if (rtb_uDLookupTable3 > MotTqMax) {
    /* Switch: '<S2>/Switch2' */
    MotTqCmd = MotTqMax;
  } else if (rtb_uDLookupTable3 < -MotTqMax) {
    /* Switch: '<S2>/Switch' incorporates:
     *  Switch: '<S2>/Switch2'
     *  UnaryMinus: '<Root>/Unary Minus'
     */
    MotTqCmd = -MotTqMax;
  } else {
    /* Switch: '<S2>/Switch2' incorporates:
     *  Switch: '<S2>/Switch'
     */
    MotTqCmd = rtb_uDLookupTable3;
  }

  /* End of Switch: '<S2>/Switch2' */

  /* Switch: '<Root>/Switch3' incorporates:
   *  Constant: '<Root>/Constant2'
   */
  if (PhaCurQTarDialEna_C) {
    /* Switch: '<Root>/Switch3' incorporates:
     *  Constant: '<Root>/Constant6'
     */
    PhaCurQTar = PhaCurQTarDialVal_C;
  } else {
    /* Switch: '<Root>/Switch3' incorporates:
     *  Constant: '<Root>/Constant1'
     *  Product: '<Root>/Product'
     */
    PhaCurQTar = MotTqCmd / MotTqCon_C;
  }

  /* End of Switch: '<Root>/Switch3' */

  /* Constant: '<Root>/Constant3' */
  PhaCurDTar = PhaCurDTarVal_C;
}

/* Model initialize function */
void TRQCTL_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_TRQCTL_T *const TRQCTL_M = &(TRQCTL_MdlrefDW.rtm);

  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatusPointer(TRQCTL_M, rt_errorStatus);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
