/*
 * File: MEDINP.c
 *
 * Code generated for Simulink model 'MEDINP'.
 *
 * Model version                  : 1.36
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:12:04 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "MEDINP.h"
#include "rtwtypes.h"
#include "FallingDebounce_RDghcENM.h"
#include <math.h>
#include "rt_nonfinite.h"
#include "MEDINP_types.h"
#include "MEDINP_private.h"

MdlrefDW_MEDINP_T MEDINP_MdlrefDW;

/* Block signals (default storage) */
B_MEDINP_c_T MEDINP_B;

/* Block states (default storage) */
DW_MEDINP_f_T MEDINP_DW;

/* System initialize for referenced model: 'MEDINP' */
void MEDINP_Init(void)
{
  /* SystemInitialize for Atomic SubSystem: '<Root>/FallingDebounce' */
  FallingDebounce_RDghcENM_Init(&MEDINP_B.Out);

  /* End of SystemInitialize for SubSystem: '<Root>/FallingDebounce' */
}

/* Start for referenced model: 'MEDINP' */
void MEDINP_Start(void)
{
  /* Start for S-Function (scanunpack): '<Root>/CAN Unpack' */

  /*-----------S-Function Block: <Root>/CAN Unpack -----------------*/
}

/* Output and update for referenced model: 'MEDINP' */
void MEDINP(void)
{
  /* S-Function (scanpack): '<Root>/CAN Pack' incorporates:
   *  Inport generated from: '<Root>/ASWIN_McuReqDa'
   */
  /* S-Function (scanpack): '<Root>/CAN Pack' */
  MEDINP_B.CANPack.ID = 1024U;
  MEDINP_B.CANPack.Length = 8U;
  MEDINP_B.CANPack.Extended = 0U;
  MEDINP_B.CANPack.Remote = 0;
  MEDINP_B.CANPack.Data[0] = 0;
  MEDINP_B.CANPack.Data[1] = 0;
  MEDINP_B.CANPack.Data[2] = 0;
  MEDINP_B.CANPack.Data[3] = 0;
  MEDINP_B.CANPack.Data[4] = 0;
  MEDINP_B.CANPack.Data[5] = 0;
  MEDINP_B.CANPack.Data[6] = 0;
  MEDINP_B.CANPack.Data[7] = 0;

  {
    (void) memcpy((MEDINP_B.CANPack.Data), &ASWIN_McuReqDa[0],
                  8 * sizeof(uint8_T));
  }

  /* S-Function (scanunpack): '<Root>/CAN Unpack' */
  {
    /* S-Function (scanunpack): '<Root>/CAN Unpack' */
    if ((8 == MEDINP_B.CANPack.Length) && (MEDINP_B.CANPack.ID != INVALID_CAN_ID)
        ) {
      if ((1024 == MEDINP_B.CANPack.ID) && (0U == MEDINP_B.CANPack.Extended) ) {
        {
          /* --------------- START Unpacking signal 0 ------------------
           *  startBit                = 0
           *  length                  = 2
           *  desiredSignalByteLayout = LITTLEENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = 0.0
           * -----------------------------------------------------------------------*/
          {
            real64_T outValue = 0;

            {
              uint8_T unpackedValue = 0;

              {
                uint8_T tempValue = (uint8_T) (0);

                {
                  tempValue = tempValue | (uint8_T)((uint8_T)
                    (MEDINP_B.CANPack.Data[0]) & (uint8_T)(0x3U));
                }

                unpackedValue = tempValue;
              }

              outValue = (real64_T) (unpackedValue);
            }

            {
              real64_T result = (real64_T) outValue;
              MEDINP_B.CANUnpack_o1 = result;
            }
          }

          /* --------------- START Unpacking signal 1 ------------------
           *  startBit                = 8
           *  length                  = 16
           *  desiredSignalByteLayout = LITTLEENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 1.0
           *  offset                  = -32500.0
           * -----------------------------------------------------------------------*/
          {
            real64_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(MEDINP_B.CANPack.Data[1]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (MEDINP_B.CANPack.Data[2]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (real64_T) (unpackedValue);
            }

            {
              real64_T result = (real64_T) outValue;
              result = result + -32500.0;
              MEDINP_B.CANUnpack_o2 = result;
            }
          }

          /* --------------- START Unpacking signal 2 ------------------
           *  startBit                = 24
           *  length                  = 16
           *  desiredSignalByteLayout = LITTLEENDIAN
           *  dataType                = UNSIGNED
           *  factor                  = 0.1
           *  offset                  = -3250.0
           * -----------------------------------------------------------------------*/
          {
            real64_T outValue = 0;

            {
              uint16_T unpackedValue = 0;

              {
                uint16_T tempValue = (uint16_T) (0);

                {
                  tempValue = tempValue | (uint16_T)(MEDINP_B.CANPack.Data[3]);
                  tempValue = tempValue | (uint16_T)((uint16_T)
                    (MEDINP_B.CANPack.Data[4]) << 8);
                }

                unpackedValue = tempValue;
              }

              outValue = (real64_T) (unpackedValue);
            }

            {
              real64_T result = (real64_T) outValue;
              result = (result * 0.1) + -3250.0;
              MEDINP_B.CANUnpack_o3 = result;
            }
          }
        }
      }
    }
  }

  /* Outputs for Atomic SubSystem: '<Root>/FallingDebounce' */
  /* RelationalOperator: '<S1>/FixPt Relational Operator' incorporates:
   *  Constant: '<Root>/Constant'
   *  Constant: '<Root>/Constant1'
   *  Inport generated from: '<Root>/ASWIN_McuReqCt'
   *  UnitDelay: '<S1>/Delay Input1'
   *
   * Block description for '<S1>/Delay Input1':
   *
   *  Store in Global RAM
   */
  FallingDebounce_RDghcENM((ASWIN_McuReqCt != MEDINP_DW.DelayInput1_DSTATE),
    McuReqTout_C, 0.01F, &MEDINP_B.Out, &MEDINP_DW.FallingDebounce);

  /* End of Outputs for SubSystem: '<Root>/FallingDebounce' */

  /* Switch: '<Root>/Switch3' incorporates:
   *  Constant: '<Root>/Constant6'
   *  Switch: '<Root>/Switch'
   */
  if (DrvModReqDialEna_C) {
    /* Switch: '<Root>/Switch3' incorporates:
     *  Constant: '<Root>/Constant7'
     */
    DrvModReq = DrvModReqDialVal_C;
  } else if (MEDINP_B.Out) {
    /* MultiPortSwitch: '<Root>/Multiport Switch' incorporates:
     *  Switch: '<Root>/Switch'
     */
    switch ((int32_T)MEDINP_B.CANUnpack_o1) {
     case 0:
      /* Switch: '<Root>/Switch3' incorporates:
       *  Constant: '<Root>/Constant12'
       */
      DrvModReq = DISABLED;
      break;

     case 1:
      /* Switch: '<Root>/Switch3' incorporates:
       *  Constant: '<Root>/Constant13'
       */
      DrvModReq = TQ_CTRL;
      break;

     case 2:
      /* Switch: '<Root>/Switch3' incorporates:
       *  Constant: '<Root>/Constant14'
       */
      DrvModReq = SPD_CTRL;
      break;

     case 3:
      /* Switch: '<Root>/Switch3' incorporates:
       *  Constant: '<Root>/Constant16'
       */
      DrvModReq = OPEN_LOOP;
      break;

     default:
      /* Switch: '<Root>/Switch3' incorporates:
       *  Constant: '<Root>/Constant15'
       */
      DrvModReq = DISABLED;
      break;
    }

    /* End of MultiPortSwitch: '<Root>/Multiport Switch' */
  } else {
    /* Switch: '<Root>/Switch3' incorporates:
     *  Constant: '<Root>/Constant3'
     *  Switch: '<Root>/Switch'
     */
    DrvModReq = DrvModReqDft_C;
  }

  /* End of Switch: '<Root>/Switch3' */

  /* Switch: '<Root>/Switch4' incorporates:
   *  Constant: '<Root>/Constant8'
   *  Switch: '<Root>/Switch1'
   */
  if (MotTqReqCanDialEna_C) {
    /* Switch: '<Root>/Switch4' incorporates:
     *  Constant: '<Root>/Constant9'
     */
    MotTqReqCan = MotTqReqCanDialVal_C;
  } else if (MEDINP_B.Out) {
    /* Switch: '<Root>/Switch1' incorporates:
     *  Switch: '<Root>/Switch4'
     */
    MotTqReqCan = (real32_T)MEDINP_B.CANUnpack_o3;
  } else {
    /* Switch: '<Root>/Switch4' incorporates:
     *  Constant: '<Root>/Constant4'
     *  Switch: '<Root>/Switch1'
     */
    MotTqReqCan = MotTqReqCanDft_C;
  }

  /* End of Switch: '<Root>/Switch4' */

  /* Switch: '<Root>/Switch5' incorporates:
   *  Constant: '<Root>/Constant10'
   *  Switch: '<Root>/Switch2'
   */
  if (MotSpdReqCanDialEna_C) {
    /* Switch: '<Root>/Switch5' incorporates:
     *  Constant: '<Root>/Constant11'
     */
    MotSpdReqCan = MotSpdReqCanDialVal_C;
  } else if (MEDINP_B.Out) {
    real_T tmp;

    /* Switch: '<Root>/Switch2' incorporates:
     *  Switch: '<Root>/Switch5'
     */
    tmp = floor(MEDINP_B.CANUnpack_o2);
    if (rtIsNaN(tmp) || rtIsInf(tmp)) {
      tmp = 0.0;
    } else {
      tmp = fmod(tmp, 65536.0);
    }

    MotSpdReqCan = (int16_T)(tmp < 0.0 ? (int32_T)(int16_T)-(int16_T)(uint16_T)
      -tmp : (int32_T)(int16_T)(uint16_T)tmp);
  } else {
    /* Switch: '<Root>/Switch5' incorporates:
     *  Constant: '<Root>/Constant5'
     *  Switch: '<Root>/Switch2'
     */
    MotSpdReqCan = MotSpdReqCanDft_C;
  }

  /* End of Switch: '<Root>/Switch5' */

  /* Update for UnitDelay: '<S1>/Delay Input1' incorporates:
   *  Inport generated from: '<Root>/ASWIN_McuReqCt'
   *
   * Block description for '<S1>/Delay Input1':
   *
   *  Store in Global RAM
   */
  MEDINP_DW.DelayInput1_DSTATE = ASWIN_McuReqCt;
}

/* Model initialize function */
void MEDINP_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_MEDINP_T *const MEDINP_M = &(MEDINP_MdlrefDW.rtm);

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize error status */
  rtmSetErrorStatusPointer(MEDINP_M, rt_errorStatus);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
