/*
 * File: ADCINP.c
 *
 * Code generated for Simulink model 'ADCINP'.
 *
 * Model version                  : 1.80
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:11:44 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ADCINP.h"
#include "LowPassFilter_0O6LwJpz.h"
#include "rtwtypes.h"
#include "ADCINP_private.h"

/* Exported block signals */
real32_T PhaUA;                        /* '<Root>/LowPassFilter5'
                                        * Phase A voltage
                                        */
real32_T PhaUB;                        /* '<Root>/LowPassFilter6'
                                        * Phase B voltage
                                        */
real32_T PhaUC;                        /* '<Root>/LowPassFilter7'
                                        * Phase C voltage
                                        */
MdlrefDW_ADCINP_T ADCINP_MdlrefDW;

/* Block states (default storage) */
DW_ADCINP_f_T ADCINP_DW;

/* Output and update for referenced model: 'ADCINP' */
void ADCINP(void)
{
  real32_T rtb_Product7;
  real32_T rtb_Subtract3;

  /* Outputs for Atomic SubSystem: '<Root>/LowPassFilter8'
   *
   * Block description for '<Root>/LowPassFilter8':
   *  Low-Pass Filter
   */
  /* Sum: '<Root>/Add8' incorporates:
   *  Constant: '<Root>/Constant44'
   *  Constant: '<Root>/Constant45'
   *  Constant: '<Root>/Constant46'
   *  Constant: '<Root>/Constant47'
   *  Inport generated from: '<Root>/ASWIN_ResolverSin'
   *  Product: '<Root>/Product8'
   */
  LowPassFilter_0O6LwJpz((real32_T)ASWIN_ResolverSin * ResolverSinGain_C +
    ResolverSinOfs_C, ResolverSinFilTiCon_C, 0.0001F, &rtb_Subtract3,
    &ADCINP_DW.LowPassFilter8);

  /* End of Outputs for SubSystem: '<Root>/LowPassFilter8' */

  /* Product: '<Root>/Product9' incorporates:
   *  Constant: '<Root>/Constant52'
   *  Inport generated from: '<Root>/ASWIN_ResolverCos'
   */
  rtb_Product7 = (real32_T)ASWIN_ResolverCos * ResolverCosGain_C;

  /* Outputs for Atomic SubSystem: '<Root>/LowPassFilter9'
   *
   * Block description for '<Root>/LowPassFilter9':
   *  Low-Pass Filter
   */
  /* Sum: '<Root>/Add9' incorporates:
   *  Constant: '<Root>/Constant50'
   *  Constant: '<Root>/Constant51'
   *  Constant: '<Root>/Constant53'
   */
  LowPassFilter_0O6LwJpz(rtb_Product7 + ResolverCosOfs_C, ResolverCosFilTiCon_C,
    0.0001F, &rtb_Product7, &ADCINP_DW.LowPassFilter9);

  /* End of Outputs for SubSystem: '<Root>/LowPassFilter9' */

  /* Switch: '<Root>/Switch5' incorporates:
   *  Constant: '<Root>/Constant42'
   */
  if (ResolverSinCosDialEna_C) {
    /* Switch: '<Root>/Switch5' incorporates:
     *  Constant: '<Root>/Constant43'
     */
    ResolverSinCos[0] = ResolverSinCosDialVal_CA[0];
    ResolverSinCos[1] = ResolverSinCosDialVal_CA[1];
  } else {
    /* Switch: '<Root>/Switch5' */
    ResolverSinCos[0] = rtb_Subtract3;
    ResolverSinCos[1] = rtb_Product7;
  }

  /* End of Switch: '<Root>/Switch5' */

  /* Outputs for Atomic SubSystem: '<Root>/LowPassFilter3'
   *
   * Block description for '<Root>/LowPassFilter3':
   *  Low-Pass Filter
   */
  /* Sum: '<Root>/Add3' incorporates:
   *  Constant: '<Root>/Constant2'
   *  Constant: '<Root>/Constant32'
   *  Constant: '<Root>/Constant33'
   *  Constant: '<Root>/Constant9'
   *  Inport generated from: '<Root>/ASWIN_HvBusU'
   *  Product: '<Root>/Product'
   */
  LowPassFilter_0O6LwJpz((real32_T)ASWIN_HvBusU * HvBusUGain_C + HvBusUOfs_C,
    HvBusUFilTiCon_C, 0.0001F, &rtb_Subtract3, &ADCINP_DW.LowPassFilter3);

  /* End of Outputs for SubSystem: '<Root>/LowPassFilter3' */

  /* Switch: '<Root>/Switch' incorporates:
   *  Constant: '<Root>/Constant'
   */
  if (HvBusUDialEna_C) {
    /* Switch: '<Root>/Switch' incorporates:
     *  Constant: '<Root>/Constant1'
     */
    HvBusU = HvBusUDialVal_C;
  } else {
    /* Switch: '<Root>/Switch' */
    HvBusU = rtb_Subtract3;
  }

  /* End of Switch: '<Root>/Switch' */

  /* Outputs for Atomic SubSystem: '<Root>/LowPassFilter2'
   *
   * Block description for '<Root>/LowPassFilter2':
   *  Low-Pass Filter
   */
  /* Sum: '<Root>/Add' incorporates:
   *  Constant: '<Root>/Constant3'
   *  Constant: '<Root>/Constant30'
   *  Constant: '<Root>/Constant31'
   *  Constant: '<Root>/Constant6'
   *  Inport generated from: '<Root>/ASWIN_PhaCurA'
   *  Product: '<Root>/Product1'
   */
  LowPassFilter_0O6LwJpz((real32_T)ASWIN_PhaCurA * PhaCurAGain_C + PhaCurAOfs_C,
    PhaCurAFilTiCon_C, 0.0001F, &rtb_Subtract3, &ADCINP_DW.LowPassFilter2);

  /* End of Outputs for SubSystem: '<Root>/LowPassFilter2' */

  /* Switch: '<Root>/Switch1' incorporates:
   *  Constant: '<Root>/Constant10'
   */
  if (PhaCurADialEna_C) {
    /* Switch: '<Root>/Switch1' incorporates:
     *  Constant: '<Root>/Constant11'
     */
    PhaCurA = PhaCurADialVal_C;
  } else {
    /* Switch: '<Root>/Switch1' */
    PhaCurA = rtb_Subtract3;
  }

  /* End of Switch: '<Root>/Switch1' */

  /* Outputs for Atomic SubSystem: '<Root>/LowPassFilter1'
   *
   * Block description for '<Root>/LowPassFilter1':
   *  Low-Pass Filter
   */
  /* Sum: '<Root>/Add1' incorporates:
   *  Constant: '<Root>/Constant28'
   *  Constant: '<Root>/Constant29'
   *  Constant: '<Root>/Constant4'
   *  Constant: '<Root>/Constant7'
   *  Inport generated from: '<Root>/ASWIN_PhaCurB'
   *  Product: '<Root>/Product2'
   */
  LowPassFilter_0O6LwJpz((real32_T)ASWIN_PhaCurB * PhaCurBGain_C + PhaCurBOfs_C,
    PhaCurBFilTiCon_C, 0.0001F, &rtb_Subtract3, &ADCINP_DW.LowPassFilter1);

  /* End of Outputs for SubSystem: '<Root>/LowPassFilter1' */

  /* Switch: '<Root>/Switch2' incorporates:
   *  Constant: '<Root>/Constant12'
   */
  if (PhaCurBDialEna_C) {
    /* Switch: '<Root>/Switch2' incorporates:
     *  Constant: '<Root>/Constant13'
     */
    PhaCurB = PhaCurBDialVal_C;
  } else {
    /* Switch: '<Root>/Switch2' */
    PhaCurB = rtb_Subtract3;
  }

  /* End of Switch: '<Root>/Switch2' */

  /* Outputs for Atomic SubSystem: '<Root>/LowPassFilter'
   *
   * Block description for '<Root>/LowPassFilter':
   *  Low-Pass Filter
   */
  /* Sum: '<Root>/Add2' incorporates:
   *  Constant: '<Root>/Constant26'
   *  Constant: '<Root>/Constant27'
   *  Constant: '<Root>/Constant5'
   *  Constant: '<Root>/Constant8'
   *  Inport generated from: '<Root>/ASWIN_PhaCurC'
   *  Product: '<Root>/Product3'
   */
  LowPassFilter_0O6LwJpz((real32_T)ASWIN_PhaCurC * PhaCurCGain_C + PhaCurCOfs_C,
    PhaCurCFilTiCon_C, 0.0001F, &rtb_Subtract3, &ADCINP_DW.LowPassFilter);

  /* End of Outputs for SubSystem: '<Root>/LowPassFilter' */

  /* Switch: '<Root>/Switch3' incorporates:
   *  Constant: '<Root>/Constant14'
   */
  if (PhaCurCDialEna_C) {
    /* Switch: '<Root>/Switch3' incorporates:
     *  Constant: '<Root>/Constant15'
     */
    PhaCurC = PhaCurCDialVal_C;
  } else {
    /* Switch: '<Root>/Switch3' */
    PhaCurC = rtb_Subtract3;
  }

  /* End of Switch: '<Root>/Switch3' */

  /* Outputs for Atomic SubSystem: '<Root>/LowPassFilter4'
   *
   * Block description for '<Root>/LowPassFilter4':
   *  Low-Pass Filter
   */
  /* Sum: '<Root>/Add4' incorporates:
   *  Constant: '<Root>/Constant18'
   *  Constant: '<Root>/Constant19'
   *  Constant: '<Root>/Constant34'
   *  Constant: '<Root>/Constant35'
   *  Inport generated from: '<Root>/ASWIN_HvBusCur'
   *  Product: '<Root>/Product4'
   */
  LowPassFilter_0O6LwJpz((real32_T)ASWIN_HvBusCur * HvBusCurGain_C +
    HvBusCurOfs_C, HvBusCurFilTiCon_C, 0.0001F, &rtb_Subtract3,
    &ADCINP_DW.LowPassFilter4);

  /* End of Outputs for SubSystem: '<Root>/LowPassFilter4' */

  /* Switch: '<Root>/Switch4' incorporates:
   *  Constant: '<Root>/Constant16'
   */
  if (HvBusCurDialEna_C) {
    /* Switch: '<Root>/Switch4' incorporates:
     *  Constant: '<Root>/Constant17'
     */
    HvBusCur = HvBusCurDialVal_C;
  } else {
    /* Switch: '<Root>/Switch4' */
    HvBusCur = rtb_Subtract3;
  }

  /* End of Switch: '<Root>/Switch4' */

  /* Outputs for Atomic SubSystem: '<Root>/LowPassFilter5'
   *
   * Block description for '<Root>/LowPassFilter5':
   *  Low-Pass Filter
   */
  /* Sum: '<Root>/Add5' incorporates:
   *  Constant: '<Root>/Constant22'
   *  Constant: '<Root>/Constant23'
   *  Constant: '<Root>/Constant36'
   *  Constant: '<Root>/Constant37'
   *  Inport generated from: '<Root>/ASWIN_PhaUA'
   *  Product: '<Root>/Product5'
   */
  LowPassFilter_0O6LwJpz((real32_T)ASWIN_PhaUA * PhaUAGain_C + PhaUAOfs_C,
    PhaUAFilTiCon_C, 0.0001F, &rtb_Subtract3, &ADCINP_DW.LowPassFilter5);

  /* End of Outputs for SubSystem: '<Root>/LowPassFilter5' */

  /* SignalConversion generated from: '<Root>/LowPassFilter5'
   *
   * Block description for SignalConversion generated from '<Root>/LowPassFilter5':
   *  Low-Pass Filter
   */
  PhaUA = rtb_Subtract3;

  /* Outputs for Atomic SubSystem: '<Root>/LowPassFilter6'
   *
   * Block description for '<Root>/LowPassFilter6':
   *  Low-Pass Filter
   */
  /* Sum: '<Root>/Add6' incorporates:
   *  Constant: '<Root>/Constant20'
   *  Constant: '<Root>/Constant21'
   *  Constant: '<Root>/Constant38'
   *  Constant: '<Root>/Constant39'
   *  Inport generated from: '<Root>/ASWIN_PhaUB'
   *  Product: '<Root>/Product6'
   */
  LowPassFilter_0O6LwJpz((real32_T)ASWIN_PhaUB * PhaUBGain_C + PhaUBOfs_C,
    PhaUBFilTiCon_C, 0.0001F, &rtb_Subtract3, &ADCINP_DW.LowPassFilter6);

  /* End of Outputs for SubSystem: '<Root>/LowPassFilter6' */

  /* SignalConversion generated from: '<Root>/LowPassFilter6'
   *
   * Block description for SignalConversion generated from '<Root>/LowPassFilter6':
   *  Low-Pass Filter
   */
  PhaUB = rtb_Subtract3;

  /* Outputs for Atomic SubSystem: '<Root>/LowPassFilter7'
   *
   * Block description for '<Root>/LowPassFilter7':
   *  Low-Pass Filter
   */
  /* Sum: '<Root>/Add7' incorporates:
   *  Constant: '<Root>/Constant24'
   *  Constant: '<Root>/Constant25'
   *  Constant: '<Root>/Constant40'
   *  Constant: '<Root>/Constant41'
   *  Inport generated from: '<Root>/ASWIN_PhaUC'
   *  Product: '<Root>/Product7'
   */
  LowPassFilter_0O6LwJpz((real32_T)ASWIN_PhaUC * PhaUCGain_C + PhaUCOfs_C,
    PhaUCFilTiCon_C, 0.0001F, &rtb_Subtract3, &ADCINP_DW.LowPassFilter7);

  /* End of Outputs for SubSystem: '<Root>/LowPassFilter7' */

  /* SignalConversion generated from: '<Root>/LowPassFilter7'
   *
   * Block description for SignalConversion generated from '<Root>/LowPassFilter7':
   *  Low-Pass Filter
   */
  PhaUC = rtb_Subtract3;
}

/* Model initialize function */
void ADCINP_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_ADCINP_T *const ADCINP_M = &(ADCINP_MdlrefDW.rtm);

  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatusPointer(ADCINP_M, rt_errorStatus);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
