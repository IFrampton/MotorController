/*
 * File: POSINP.c
 *
 * Code generated for Simulink model 'POSINP'.
 *
 * Model version                  : 1.188
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:12:15 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "POSINP.h"
#include "POSINP_types.h"
#include "rtwtypes.h"
#include "rt_modf_snf.h"
#include <math.h>
#include "LowPassFilter_0O6LwJpz.h"
#include "rt_nonfinite.h"
#include "POSINP_private.h"

/* Exported block signals */
real32_T MotPosnMagMeasd;              /* '<Root>/Math Function1'
                                        * The measured magnetic motor position. Can be used in open loop control to verify position measurement.
                                        */
real32_T MotPosnErr;                   /* '<Root>/Add1'
                                        * Motor position error.
                                        */
MdlrefDW_POSINP_T POSINP_MdlrefDW;

/* Block states (default storage) */
DW_POSINP_f_T POSINP_DW;

/* System initialize for referenced model: 'POSINP' */
void POSINP_Init(void)
{
  /* InitializeConditions for DiscreteIntegrator: '<Root>/Accumulator' */
  POSINP_DW.Accumulator_PrevResetState = 2;
}

/* Output and update for referenced model: 'POSINP' */
void POSINP(const DRIVEMODE *rtu_DrvMod, const int16_T *rtu_MotSpdReqCan, const
            real32_T rtu_ResolverSinCos[2])
{
  real32_T DiscreteTimeIntegrator;
  real32_T rtb_Add2;
  real32_T rtb_MathFunction;
  real32_T rtb_MathFunction2;
  real32_T rtb_Subtract3;
  real32_T tmp;

  /* DiscreteIntegrator: '<Root>/Accumulator' incorporates:
   *  Inport generated from: '<Root>/ASWIN_EncoderZ'
   */
  if (ASWIN_EncoderZ && (POSINP_DW.Accumulator_PrevResetState <= 0)) {
    POSINP_DW.Accumulator_DSTATE = 0;
  }

  /* Math: '<Root>/Math Function1' incorporates:
   *  Constant: '<Root>/Constant'
   *  Constant: '<Root>/Constant10'
   *  Constant: '<Root>/Constant12'
   *  Constant: '<Root>/Constant2'
   *  DiscreteIntegrator: '<Root>/Accumulator'
   *  Gain: '<Root>/Gain2'
   *  Product: '<Root>/Divide1'
   *  Sum: '<Root>/Add'
   *
   * Block description for '<Root>/Constant12':
   *  2*pi
   *
   * Block description for '<Root>/Gain2':
   *  2*pi
   */
  MotPosnMagMeasd = rt_modf_snf((real32_T)MotPolePairs_C * (real32_T)
    POSINP_DW.Accumulator_DSTATE / (real32_T)EncoderCtPerRev_C * 6.2832F +
    EncoderOfs_C, 6.2832F);

  /* Sum: '<Root>/Add1' incorporates:
   *  Product: '<Root>/Product1'
   *  Product: '<Root>/Product3'
   *  Trigonometry: '<Root>/Trigonometric Function'
   *  UnitDelay: '<Root>/Unit Delay1'
   */
  MotPosnErr = cosf(POSINP_DW.UnitDelay1_DSTATE) * rtu_ResolverSinCos[0] -
    rtu_ResolverSinCos[1] * sinf(POSINP_DW.UnitDelay1_DSTATE);

  /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator' incorporates:
   *  Constant: '<Root>/Constant18'
   *  RelationalOperator: '<S1>/FixPt Relational Operator'
   *  UnitDelay: '<S1>/Delay Input1'
   *
   * Block description for '<S1>/Delay Input1':
   *
   *  Store in Global RAM
   */
  if (MotPosnEstimrIntglEna_C != POSINP_DW.DelayInput1_DSTATE) {
    POSINP_DW.DiscreteTimeIntegrator_DSTATE = 0.0F;
  }

  /* Switch: '<Root>/Switch5' incorporates:
   *  Constant: '<Root>/Constant18'
   *  Constant: '<Root>/Constant19'
   */
  if (MotPosnEstimrIntglEna_C) {
    tmp = MotPosnErr;
  } else {
    tmp = 0.0F;
  }

  /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator' incorporates:
   *  Switch: '<Root>/Switch5'
   */
  DiscreteTimeIntegrator = POSINP_DW.DiscreteTimeIntegrator_DSTATE + tmp;

  /* Sum: '<Root>/Add2' incorporates:
   *  Constant: '<Root>/Constant15'
   *  Constant: '<Root>/Constant20'
   *  Constant: '<Root>/Constant21'
   *  Product: '<Root>/Product4'
   *  Product: '<Root>/Product5'
   */
  rtb_Add2 = MotPosnEstimrGainI_C * DiscreteTimeIntegrator * 0.0001F +
    MotPosnEstimrGainP_C * MotPosnErr;

  /* Math: '<Root>/Math Function2' incorporates:
   *  Constant: '<Root>/Constant20'
   *  Constant: '<Root>/Constant22'
   *  Product: '<Root>/Product6'
   *  Sum: '<Root>/Add3'
   *  UnitDelay: '<Root>/Unit Delay1'
   *
   * Block description for '<Root>/Constant22':
   *  2*pi
   */
  rtb_MathFunction2 = rt_modf_snf(rtb_Add2 * 0.0001F +
    POSINP_DW.UnitDelay1_DSTATE, 6.2832F);

  /* UnitDelay: '<Root>/Unit Delay5' */
  rtb_Subtract3 = POSINP_DW.UnitDelay5_DSTATE;

  /* Math: '<Root>/Math Function' incorporates:
   *  Constant: '<Root>/Constant11'
   *  Constant: '<Root>/Constant13'
   *  Constant: '<Root>/Constant14'
   *  DataTypeConversion: '<Root>/Data Type Conversion2'
   *  Gain: '<Root>/Gain3'
   *  Product: '<Root>/Product2'
   *  Sum: '<Root>/Add5'
   *  UnitDelay: '<Root>/Unit Delay5'
   *
   * Block description for '<Root>/Constant11':
   *  2*pi
   *
   * Block description for '<Root>/Gain3':
   *  (rad/s)/rpm
   */
  rtb_MathFunction = rt_modf_snf(0.10472F * (real32_T)*rtu_MotSpdReqCan *
    (real32_T)MotPolePairs_C * 0.0001F + POSINP_DW.UnitDelay5_DSTATE, 6.2832F);

  /* Switch: '<Root>/Switch4' incorporates:
   *  Constant: '<Root>/Constant16'
   *  Constant: '<S2>/Constant'
   *  RelationalOperator: '<Root>/Relational Operator'
   *  Switch: '<Root>/Switch3'
   */
  if (MotPosnMagDialEna_C) {
    /* Switch: '<Root>/Switch4' incorporates:
     *  Constant: '<Root>/Constant17'
     */
    MotPosnMag = MotPosnMagDialVal_C;
  } else if (*rtu_DrvMod != OPEN_LOOP) {
    /* Switch: '<Root>/Switch8' incorporates:
     *  Constant: '<Root>/Constant26'
     *  Switch: '<Root>/Switch3'
     */
    if (MotPosnSenMeth_C) {
      /* Switch: '<Root>/Switch4' incorporates:
       *  Constant: '<Root>/Constant'
       *  Constant: '<Root>/Constant23'
       *  Product: '<Root>/Product7'
       *  Sum: '<Root>/Add4'
       */
      MotPosnMag = (rtb_MathFunction2 - MotPosnOfs_C) * (real32_T)MotPolePairs_C;
    } else {
      /* Switch: '<Root>/Switch4' */
      MotPosnMag = MotPosnMagMeasd;
    }

    /* End of Switch: '<Root>/Switch8' */
  } else {
    /* Switch: '<Root>/Switch4' incorporates:
     *  Switch: '<Root>/Switch3'
     */
    MotPosnMag = rtb_MathFunction;
  }

  /* End of Switch: '<Root>/Switch4' */

  /* Outputs for Atomic SubSystem: '<Root>/LowPassFilter' */
  /* Product: '<Root>/Divide' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Constant: '<Root>/Constant3'
   *  Constant: '<Root>/Constant4'
   *  Constant: '<Root>/Constant5'
   *  Inport generated from: '<Root>/ASWIN_EncoderCt'
   */
  LowPassFilter_0O6LwJpz((real32_T)ASWIN_EncoderCt / (real32_T)EncoderCtPerRev_C
    / 0.0001F, MotSpdFilTiCon_C, 0.0001F, &rtb_Subtract3,
    &POSINP_DW.LowPassFilter);

  /* End of Outputs for SubSystem: '<Root>/LowPassFilter' */

  /* Switch: '<Root>/Switch2' incorporates:
   *  Constant: '<Root>/Constant24'
   *  Constant: '<Root>/Constant8'
   *  Switch: '<Root>/Switch6'
   */
  if (MotSpdDialEna_C) {
    /* Switch: '<Root>/Switch2' incorporates:
     *  Constant: '<Root>/Constant9'
     */
    MotSpd = MotSpdDialVal_C;
  } else {
    if (MotPosnSenMeth_C) {
      /* Switch: '<Root>/Switch6' incorporates:
       *  Gain: '<Root>/Gain4'
       *
       * Block description for '<Root>/Gain4':
       *  rpm/(rad/s)
       */
      tmp = 9.5493F * rtb_Add2;
    } else {
      /* Switch: '<Root>/Switch6' incorporates:
       *  Gain: '<Root>/Gain1'
       *
       * Block description for '<Root>/Gain1':
       *  sec/min
       */
      tmp = 60.0F * rtb_Subtract3;
    }

    /* DataTypeConversion: '<Root>/Data Type Conversion' incorporates:
     *  Switch: '<Root>/Switch6'
     */
    tmp = floorf(tmp);
    if (rtIsNaNF(tmp) || rtIsInfF(tmp)) {
      tmp = 0.0F;
    } else {
      tmp = fmodf(tmp, 65536.0F);
    }

    /* Switch: '<Root>/Switch2' incorporates:
     *  DataTypeConversion: '<Root>/Data Type Conversion'
     */
    MotSpd = (int16_T)(tmp < 0.0F ? (int32_T)(int16_T)-(int16_T)(uint16_T)-tmp :
                       (int32_T)(int16_T)(uint16_T)tmp);
  }

  /* End of Switch: '<Root>/Switch2' */

  /* Switch: '<Root>/Switch1' incorporates:
   *  Constant: '<Root>/Constant25'
   *  Constant: '<Root>/Constant6'
   *  Switch: '<Root>/Switch7'
   */
  if (MotSpdMagDialEna_C) {
    /* Switch: '<Root>/Switch1' incorporates:
     *  Constant: '<Root>/Constant7'
     */
    MotSpdMag = MotSpdMagDialVal_C;
  } else {
    if (!MotPosnSenMeth_C) {
      /* Switch: '<Root>/Switch7' incorporates:
       *  Gain: '<Root>/Gain'
       *
       * Block description for '<Root>/Gain':
       *  2*pi
       */
      rtb_Add2 = 6.2832F * rtb_Subtract3;
    }

    /* Switch: '<Root>/Switch1' incorporates:
     *  Constant: '<Root>/Constant'
     *  Product: '<Root>/Product'
     */
    MotSpdMag = rtb_Add2 * (real32_T)MotPolePairs_C;
  }

  /* End of Switch: '<Root>/Switch1' */

  /* Update for DiscreteIntegrator: '<Root>/Accumulator' incorporates:
   *  Inport generated from: '<Root>/ASWIN_EncoderCt'
   *  Inport generated from: '<Root>/ASWIN_EncoderZ'
   */
  POSINP_DW.Accumulator_DSTATE += ASWIN_EncoderCt;
  POSINP_DW.Accumulator_PrevResetState = (int8_T)ASWIN_EncoderZ;

  /* Update for UnitDelay: '<Root>/Unit Delay1' */
  POSINP_DW.UnitDelay1_DSTATE = rtb_MathFunction2;

  /* Update for UnitDelay: '<S1>/Delay Input1' incorporates:
   *  Constant: '<Root>/Constant18'
   *
   * Block description for '<S1>/Delay Input1':
   *
   *  Store in Global RAM
   */
  POSINP_DW.DelayInput1_DSTATE = MotPosnEstimrIntglEna_C;

  /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
  POSINP_DW.DiscreteTimeIntegrator_DSTATE = DiscreteTimeIntegrator;

  /* Update for UnitDelay: '<Root>/Unit Delay5' */
  POSINP_DW.UnitDelay5_DSTATE = rtb_MathFunction;
}

/* Model initialize function */
void POSINP_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_POSINP_T *const POSINP_M = &(POSINP_MdlrefDW.rtm);

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize error status */
  rtmSetErrorStatusPointer(POSINP_M, rt_errorStatus);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
