/*
 * File: SLWINP.c
 *
 * Code generated for Simulink model 'SLWINP'.
 *
 * Model version                  : 1.60
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:12:21 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "SLWINP.h"
#include "Debounce_G4uuGAfd.h"
#include "LowPassFilter_0O6LwJpz.h"
#include "rtwtypes.h"
#include "SLWINP_private.h"

/* Exported block signals */
real32_T McuURef;                      /* '<Root>/LowPassFilter3'
                                        * Microcontroller voltage VREFINT
                                        */
real32_T McuUBat;                      /* '<Root>/LowPassFilter4'
                                        * Microcontroller voltage VBAT
                                        */
MdlrefDW_SLWINP_T SLWINP_MdlrefDW;

/* Block signals (default storage) */
B_SLWINP_c_T SLWINP_B;

/* Block states (default storage) */
DW_SLWINP_f_T SLWINP_DW;

/* System initialize for referenced model: 'SLWINP' */
void SLWINP_Init(void)
{
  /* SystemInitialize for Atomic SubSystem: '<Root>/Debounce1'
   *
   * Block description for '<Root>/Debounce1':
   *  Debounce
   */
  Debounce_G4uuGAfd_Init(&SLWINP_B.Out);

  /* End of SystemInitialize for SubSystem: '<Root>/Debounce1' */

  /* SystemInitialize for Atomic SubSystem: '<Root>/Debounce'
   *
   * Block description for '<Root>/Debounce':
   *  Debounce
   */
  Debounce_G4uuGAfd_Init(&SLWINP_B.Out_a);

  /* End of SystemInitialize for SubSystem: '<Root>/Debounce' */
}

/* Output and update for referenced model: 'SLWINP' */
void SLWINP(void)
{
  real32_T rtb_Subtract3;

  /* Outputs for Atomic SubSystem: '<Root>/Debounce1'
   *
   * Block description for '<Root>/Debounce1':
   *  Debounce
   */
  /* Logic: '<Root>/Logical Operator' incorporates:
   *  Constant: '<Root>/Constant'
   *  Constant: '<Root>/Constant1'
   *  Constant: '<Root>/Constant2'
   *  Constant: '<Root>/Constant3'
   *  Inport generated from: '<Root>/ASWIN_MaiPwrSts'
   */
  Debounce_G4uuGAfd((boolean_T)(ASWIN_MaiPwrSts ^ MaiPwrStsIvt_C),
                    MaiPwrAcvDebRisng_C, MaiPwrAcvDebFall_C, 0.1F, &SLWINP_B.Out,
                    &SLWINP_DW.Debounce1);

  /* End of Outputs for SubSystem: '<Root>/Debounce1' */

  /* Switch: '<Root>/Switch4' incorporates:
   *  Constant: '<Root>/Constant16'
   */
  if (MaiPwrAcvDialEna_C) {
    /* Switch: '<Root>/Switch4' incorporates:
     *  Constant: '<Root>/Constant17'
     */
    MaiPwrAcv = MaiPwrAcvDialVal_C;
  } else {
    /* Switch: '<Root>/Switch4' */
    MaiPwrAcv = SLWINP_B.Out;
  }

  /* End of Switch: '<Root>/Switch4' */

  /* Outputs for Atomic SubSystem: '<Root>/Debounce'
   *
   * Block description for '<Root>/Debounce':
   *  Debounce
   */
  /* Logic: '<Root>/Logical Operator1' incorporates:
   *  Constant: '<Root>/Constant4'
   *  Constant: '<Root>/Constant5'
   *  Constant: '<Root>/Constant8'
   *  Constant: '<Root>/Constant9'
   *  Inport generated from: '<Root>/ASWIN_AuxPwrSts'
   */
  Debounce_G4uuGAfd((boolean_T)(ASWIN_AuxPwrSts ^ AuxPwrStsIvt_C),
                    AuxPwrAcvDebRisng_C, AuxPwrAcvDebFall_C, 0.1F,
                    &SLWINP_B.Out_a, &SLWINP_DW.Debounce);

  /* End of Outputs for SubSystem: '<Root>/Debounce' */

  /* Switch: '<Root>/Switch1' incorporates:
   *  Constant: '<Root>/Constant6'
   */
  if (AuxPwrAcvDialEna_C) {
    /* Switch: '<Root>/Switch1' incorporates:
     *  Constant: '<Root>/Constant7'
     */
    AuxPwrAcv = AuxPwrAcvDialVal_C;
  } else {
    /* Switch: '<Root>/Switch1' */
    AuxPwrAcv = SLWINP_B.Out_a;
  }

  /* End of Switch: '<Root>/Switch1' */

  /* Product: '<Root>/Product5' incorporates:
   *  Constant: '<Root>/Constant22'
   *  Inport generated from: '<Root>/ASWIN_BdT1'
   */
  rtb_Subtract3 = (real32_T)ASWIN_BdT1 * BdT1Gain_C;

  /* Outputs for Atomic SubSystem: '<Root>/LowPassFilter1'
   *
   * Block description for '<Root>/LowPassFilter1':
   *  Low-Pass Filter
   */
  /* Sum: '<Root>/Add5' incorporates:
   *  Constant: '<Root>/Constant12'
   *  Constant: '<Root>/Constant13'
   *  Constant: '<Root>/Constant23'
   */
  LowPassFilter_0O6LwJpz(rtb_Subtract3 + BdT1Ofs_C, BdT1FilTiCon_C, 0.1F,
    &rtb_Subtract3, &SLWINP_DW.LowPassFilter1);

  /* End of Outputs for SubSystem: '<Root>/LowPassFilter1' */

  /* Switch: '<Root>/Switch2' incorporates:
   *  Constant: '<Root>/Constant10'
   */
  if (BdT1DialEna_C) {
    /* Switch: '<Root>/Switch2' incorporates:
     *  Constant: '<Root>/Constant11'
     */
    BdT1 = BdT1DialVal_C;
  } else {
    /* Switch: '<Root>/Switch2' */
    BdT1 = rtb_Subtract3;
  }

  /* End of Switch: '<Root>/Switch2' */

  /* Product: '<Root>/Product1' incorporates:
   *  Constant: '<Root>/Constant20'
   *  Inport generated from: '<Root>/ASWIN_BdT2'
   */
  rtb_Subtract3 = (real32_T)ASWIN_BdT2 * BdT2Gain_C;

  /* Outputs for Atomic SubSystem: '<Root>/LowPassFilter'
   *
   * Block description for '<Root>/LowPassFilter':
   *  Low-Pass Filter
   */
  /* Sum: '<Root>/Add1' incorporates:
   *  Constant: '<Root>/Constant18'
   *  Constant: '<Root>/Constant19'
   *  Constant: '<Root>/Constant21'
   */
  LowPassFilter_0O6LwJpz(rtb_Subtract3 + BdT2Ofs_C, BdT2FilTiCon_C, 0.1F,
    &rtb_Subtract3, &SLWINP_DW.LowPassFilter);

  /* End of Outputs for SubSystem: '<Root>/LowPassFilter' */

  /* Switch: '<Root>/Switch3' incorporates:
   *  Constant: '<Root>/Constant14'
   */
  if (BdT2DialEna_C) {
    /* Switch: '<Root>/Switch3' incorporates:
     *  Constant: '<Root>/Constant15'
     */
    BdT2 = BdT2DialVal_C;
  } else {
    /* Switch: '<Root>/Switch3' */
    BdT2 = rtb_Subtract3;
  }

  /* End of Switch: '<Root>/Switch3' */

  /* Product: '<Root>/Product2' incorporates:
   *  Constant: '<Root>/Constant28'
   *  Inport generated from: '<Root>/ASWIN_McuT'
   */
  rtb_Subtract3 = (real32_T)ASWIN_McuT * McuTGain_C;

  /* Outputs for Atomic SubSystem: '<Root>/LowPassFilter2'
   *
   * Block description for '<Root>/LowPassFilter2':
   *  Low-Pass Filter
   */
  /* Sum: '<Root>/Add2' incorporates:
   *  Constant: '<Root>/Constant26'
   *  Constant: '<Root>/Constant27'
   *  Constant: '<Root>/Constant29'
   */
  LowPassFilter_0O6LwJpz(rtb_Subtract3 + McuTOfs_C, McuTFilTiCon_C, 0.1F,
    &rtb_Subtract3, &SLWINP_DW.LowPassFilter2);

  /* End of Outputs for SubSystem: '<Root>/LowPassFilter2' */

  /* Switch: '<Root>/Switch5' incorporates:
   *  Constant: '<Root>/Constant24'
   */
  if (McuTDialEna_C) {
    /* Switch: '<Root>/Switch5' incorporates:
     *  Constant: '<Root>/Constant25'
     */
    McuT = McuTDialVal_C;
  } else {
    /* Switch: '<Root>/Switch5' */
    McuT = rtb_Subtract3;
  }

  /* End of Switch: '<Root>/Switch5' */

  /* Product: '<Root>/Product3' incorporates:
   *  Constant: '<Root>/Constant32'
   *  Inport generated from: '<Root>/ASWIN_McuURef'
   */
  rtb_Subtract3 = (real32_T)ASWIN_McuURef * McuURefGain_C;

  /* Outputs for Atomic SubSystem: '<Root>/LowPassFilter3'
   *
   * Block description for '<Root>/LowPassFilter3':
   *  Low-Pass Filter
   */
  /* Sum: '<Root>/Add3' incorporates:
   *  Constant: '<Root>/Constant30'
   *  Constant: '<Root>/Constant31'
   *  Constant: '<Root>/Constant33'
   */
  LowPassFilter_0O6LwJpz(rtb_Subtract3 + McuURefOfs_C, McuURefFilTiCon_C, 0.1F,
    &rtb_Subtract3, &SLWINP_DW.LowPassFilter3);

  /* End of Outputs for SubSystem: '<Root>/LowPassFilter3' */

  /* SignalConversion generated from: '<Root>/LowPassFilter3'
   *
   * Block description for SignalConversion generated from '<Root>/LowPassFilter3':
   *  Low-Pass Filter
   */
  McuURef = rtb_Subtract3;

  /* Product: '<Root>/Product4' incorporates:
   *  Constant: '<Root>/Constant36'
   *  Inport generated from: '<Root>/ASWIN_McuUBat'
   */
  rtb_Subtract3 = (real32_T)ASWIN_McuUBat * McuUBatGain_C;

  /* Outputs for Atomic SubSystem: '<Root>/LowPassFilter4'
   *
   * Block description for '<Root>/LowPassFilter4':
   *  Low-Pass Filter
   */
  /* Sum: '<Root>/Add4' incorporates:
   *  Constant: '<Root>/Constant34'
   *  Constant: '<Root>/Constant35'
   *  Constant: '<Root>/Constant37'
   */
  LowPassFilter_0O6LwJpz(rtb_Subtract3 + McuUBatOfs_C, McuUBatFilTiCon_C, 0.1F,
    &rtb_Subtract3, &SLWINP_DW.LowPassFilter4);

  /* End of Outputs for SubSystem: '<Root>/LowPassFilter4' */

  /* SignalConversion generated from: '<Root>/LowPassFilter4'
   *
   * Block description for SignalConversion generated from '<Root>/LowPassFilter4':
   *  Low-Pass Filter
   */
  McuUBat = rtb_Subtract3;
}

/* Model initialize function */
void SLWINP_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_SLWINP_T *const SLWINP_M = &(SLWINP_MdlrefDW.rtm);

  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatusPointer(SLWINP_M, rt_errorStatus);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
