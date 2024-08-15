/*
 * File: SLWOUP.c
 *
 * Code generated for Simulink model 'SLWOUP'.
 *
 * Model version                  : 1.65
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:12:28 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "SLWOUP.h"
#include "rtwtypes.h"
#include "SLWOUP_types.h"
#include "SLWOUP_private.h"

/* Named constants for Chart: '<Root>/BlinkController' */
#define SLWOUP_IN_NO_ACTIVE_CHILD      ((uint8_T)0U)
#define SLWOUP_IN_OFF                  ((uint8_T)1U)
#define SLWOUP_IN_PULSE                ((uint8_T)2U)
#define SLWOUP_IN_PULSE_OFF            ((uint8_T)1U)
#define SLWOUP_IN_PULSE_ON             ((uint8_T)2U)

MdlrefDW_SLWOUP_T SLWOUP_MdlrefDW;

/* Block signals (default storage) */
B_SLWOUP_c_T SLWOUP_B;

/* Block states (default storage) */
DW_SLWOUP_f_T SLWOUP_DW;

/* Output and update for referenced model: 'SLWOUP' */
void SLWOUP(const DRIVEMODE *rtu_DrvMod, const real32_T *rtu_BdT1, const
            real32_T *rtu_BdT2, const real32_T *rtu_McuT)
{
  int32_T i;
  uint8_T rtb_MultiportSwitch;

  /* S-Function (scanpack): '<Root>/CAN P1ack' */
  /* S-Function (scanpack): '<Root>/CAN P1ack' */
  SLWOUP_B.CANP1ack.ID = 1105U;
  SLWOUP_B.CANP1ack.Length = 8U;
  SLWOUP_B.CANP1ack.Extended = 0U;
  SLWOUP_B.CANP1ack.Remote = 0;
  SLWOUP_B.CANP1ack.Data[0] = 0;
  SLWOUP_B.CANP1ack.Data[1] = 0;
  SLWOUP_B.CANP1ack.Data[2] = 0;
  SLWOUP_B.CANP1ack.Data[3] = 0;
  SLWOUP_B.CANP1ack.Data[4] = 0;
  SLWOUP_B.CANP1ack.Data[5] = 0;
  SLWOUP_B.CANP1ack.Data[6] = 0;
  SLWOUP_B.CANP1ack.Data[7] = 0;

  {
    /* --------------- START Packing signal 0 ------------------
     *  startBit                = 0
     *  length                  = 8
     *  desiredSignalByteLayout = LITTLEENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = -40.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/
    {
      real32_T outValue = 0;

      {
        real32_T result = (*rtu_BdT1);

        /* no factor to apply */
        result = result - -40.0F;

        /* round to closest integer value for integer CAN signal */
        outValue = roundf(result);
      }

      {
        uint8_T packedValue;
        if (outValue > (real32_T)(255)) {
          packedValue = (uint8_T) 255;
        } else if (outValue < (real32_T)(0)) {
          packedValue = (uint8_T) 0;
        } else {
          packedValue = (uint8_T) (outValue);
        }

        {
          {
            SLWOUP_B.CANP1ack.Data[0] = SLWOUP_B.CANP1ack.Data[0] | (uint8_T)
              (packedValue);
          }
        }
      }
    }

    /* --------------- START Packing signal 1 ------------------
     *  startBit                = 8
     *  length                  = 8
     *  desiredSignalByteLayout = LITTLEENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = -40.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/
    {
      real32_T outValue = 0;

      {
        real32_T result = (*rtu_BdT2);

        /* no factor to apply */
        result = result - -40.0F;

        /* round to closest integer value for integer CAN signal */
        outValue = roundf(result);
      }

      {
        uint8_T packedValue;
        if (outValue > (real32_T)(255)) {
          packedValue = (uint8_T) 255;
        } else if (outValue < (real32_T)(0)) {
          packedValue = (uint8_T) 0;
        } else {
          packedValue = (uint8_T) (outValue);
        }

        {
          {
            SLWOUP_B.CANP1ack.Data[1] = SLWOUP_B.CANP1ack.Data[1] | (uint8_T)
              (packedValue);
          }
        }
      }
    }

    /* --------------- START Packing signal 2 ------------------
     *  startBit                = 16
     *  length                  = 8
     *  desiredSignalByteLayout = LITTLEENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = -40.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/
    {
      real32_T outValue = 0;

      {
        real32_T result = (*rtu_McuT);

        /* no factor to apply */
        result = result - -40.0F;

        /* round to closest integer value for integer CAN signal */
        outValue = roundf(result);
      }

      {
        uint8_T packedValue;
        if (outValue > (real32_T)(255)) {
          packedValue = (uint8_T) 255;
        } else if (outValue < (real32_T)(0)) {
          packedValue = (uint8_T) 0;
        } else {
          packedValue = (uint8_T) (outValue);
        }

        {
          {
            SLWOUP_B.CANP1ack.Data[2] = SLWOUP_B.CANP1ack.Data[2] | (uint8_T)
              (packedValue);
          }
        }
      }
    }
  }

  for (i = 0; i < 8; i++) {
    /* Switch: '<Root>/Switch' incorporates:
     *  Constant: '<Root>/Constant15'
     */
    if (McuData2DaDialEna_C) {
      /* Switch: '<Root>/Switch' incorporates:
       *  Constant: '<Root>/Constant16'
       */
      ASWOUT_McuData2Da[i] = McuData2DaDialVal_CA[i];
    } else {
      /* Switch: '<Root>/Switch' */
      ASWOUT_McuData2Da[i] = SLWOUP_B.CANP1ack.Data[i];
    }

    /* End of Switch: '<Root>/Switch' */
  }

  /* MultiPortSwitch: '<Root>/Multiport Switch' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Constant: '<Root>/Constant2'
   *  Constant: '<Root>/Constant3'
   *  Constant: '<Root>/Constant4'
   */
  switch (*rtu_DrvMod) {
   case OPEN_LOOP:
    rtb_MultiportSwitch = LedPlsCtOpenLoop_C;
    break;

   case TQ_CTRL:
    rtb_MultiportSwitch = LedPlsCtTqCtl_C;
    break;

   case SPD_CTRL:
    rtb_MultiportSwitch = LedPlsCtSpdCtl_C;
    break;

   default:
    rtb_MultiportSwitch = LedPlsCtDft_C;
    break;
  }

  /* End of MultiPortSwitch: '<Root>/Multiport Switch' */

  /* Chart: '<Root>/BlinkController' incorporates:
   *  Constant: '<Root>/Constant6'
   *
   * Block description for '<Root>/BlinkController':
   *  Blink Controller
   */
  if (SLWOUP_DW.is_active_c3_SLWOUP == 0U) {
    SLWOUP_DW.is_active_c3_SLWOUP = 1U;
    SLWOUP_DW.is_c3_SLWOUP = SLWOUP_IN_OFF;
    SLWOUP_DW.OffTmr = 0.0F;
    SLWOUP_DW.PlsCtr = 0U;
  } else if (SLWOUP_DW.is_c3_SLWOUP == SLWOUP_IN_OFF) {
    if ((SLWOUP_DW.OffTmr >= LedOffTi_C) && (SLWOUP_DW.PlsCtr <
         rtb_MultiportSwitch)) {
      SLWOUP_DW.is_c3_SLWOUP = SLWOUP_IN_PULSE;
      SLWOUP_DW.is_PULSE = SLWOUP_IN_PULSE_ON;
      SLWOUP_DW.PlsOnTmr = 0.0F;
    } else {
      SLWOUP_DW.OffTmr += 0.1F;
      SLWOUP_B.Led = false;
    }

    /* case IN_PULSE: */
  } else if (SLWOUP_DW.PlsCtr >= rtb_MultiportSwitch) {
    SLWOUP_DW.is_PULSE = SLWOUP_IN_NO_ACTIVE_CHILD;
    SLWOUP_DW.is_c3_SLWOUP = SLWOUP_IN_OFF;
    SLWOUP_DW.OffTmr = 0.0F;
    SLWOUP_DW.PlsCtr = 0U;
  } else if (SLWOUP_DW.is_PULSE == SLWOUP_IN_PULSE_OFF) {
    if (SLWOUP_DW.PlsOffTmr >= PlsOffTi_C) {
      SLWOUP_DW.is_PULSE = SLWOUP_IN_PULSE_ON;
      SLWOUP_DW.PlsOnTmr = 0.0F;
    } else {
      SLWOUP_DW.PlsOffTmr += 0.1F;
      SLWOUP_B.Led = false;
    }

    /* case IN_PULSE_ON: */
  } else if (SLWOUP_DW.PlsOnTmr >= PlsOnTi_C) {
    SLWOUP_DW.is_PULSE = SLWOUP_IN_PULSE_OFF;
    SLWOUP_DW.PlsOffTmr = 0.0F;
    SLWOUP_DW.PlsCtr++;
  } else {
    SLWOUP_DW.PlsOnTmr += 0.1F;
    SLWOUP_B.Led = true;
  }

  /* End of Chart: '<Root>/BlinkController' */

  /* Switch: '<Root>/Switch1' incorporates:
   *  Constant: '<Root>/Constant9'
   */
  if (RedLedDialEna_C) {
    /* Switch: '<Root>/Switch1' incorporates:
     *  Constant: '<Root>/Constant10'
     */
    ASWOUT_RedLed = RedLedDialVal_C;
  } else {
    /* Switch: '<Root>/Switch1' incorporates:
     *  Constant: '<Root>/Constant5'
     *  Logic: '<Root>/Logical Operator1'
     */
    ASWOUT_RedLed = SLWOUP_B.Led ^ RedLedIvt_C;
  }

  /* End of Switch: '<Root>/Switch1' */

  /* Switch: '<Root>/Switch2' incorporates:
   *  Constant: '<Root>/Constant7'
   */
  if (GreenLedDialEna_C) {
    /* Switch: '<Root>/Switch2' incorporates:
     *  Constant: '<Root>/Constant8'
     */
    ASWOUT_GreenLed = GreenLedDialVal_C;
  } else {
    /* Switch: '<Root>/Switch2' incorporates:
     *  Constant: '<Root>/Constant'
     *  Constant: '<S2>/Constant'
     *  Logic: '<Root>/Logical Operator'
     *  RelationalOperator: '<S2>/Compare'
     */
    ASWOUT_GreenLed = (*rtu_DrvMod != DISABLED) ^ GreenLedIvt_C;
  }

  /* End of Switch: '<Root>/Switch2' */

  /* Switch: '<Root>/Switch3' incorporates:
   *  Constant: '<Root>/Constant33'
   */
  if (PhaPwmEnaDialEna_C) {
    /* Switch: '<Root>/Switch3' incorporates:
     *  Constant: '<Root>/Constant34'
     */
    ASWOUT_PhaPwmEna = PhaPwmEnaDialVal_C;
  } else {
    /* MultiPortSwitch: '<Root>/Multiport Switch1' */
    switch (*rtu_DrvMod) {
     case OPEN_LOOP:
      /* Switch: '<Root>/Switch3' incorporates:
       *  Constant: '<Root>/Constant35'
       */
      ASWOUT_PhaPwmEna = true;
      break;

     case TQ_CTRL:
      /* Switch: '<Root>/Switch3' incorporates:
       *  Constant: '<Root>/Constant35'
       */
      ASWOUT_PhaPwmEna = true;
      break;

     case SPD_CTRL:
      /* Switch: '<Root>/Switch3' incorporates:
       *  Constant: '<Root>/Constant35'
       */
      ASWOUT_PhaPwmEna = true;
      break;

     default:
      /* Switch: '<Root>/Switch3' incorporates:
       *  Constant: '<Root>/Constant32'
       */
      ASWOUT_PhaPwmEna = false;
      break;
    }

    /* End of MultiPortSwitch: '<Root>/Multiport Switch1' */
  }

  /* End of Switch: '<Root>/Switch3' */

  /* Constant: '<Root>/Constant17' */
  ASWOUT_YellowLed = YellowLedCmd_C;

  /* Constant: '<Root>/Constant18' */
  ASWOUT_ResolverExctEna = ResolverExctEna_C;

  /* Constant: '<Root>/Constant22' */
  ASWOUT_CanPwrPwmEna = CanPwrPwmEna_C;

  /* Constant: '<Root>/Constant14' */
  ASWOUT_InPwrPwmEna = InPwrPwmEna_C;

  /* Constant: '<Root>/Constant12' */
  ASWOUT_MtrPwrPwmEna = MtrPwrPwmEna_C;

  /* Constant: '<Root>/Constant11' */
  ASWOUT_SwPwrPwmEna = SwPwrPwmEna_C;
}

/* Model initialize function */
void SLWOUP_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_SLWOUP_T *const SLWOUP_M = &(SLWOUP_MdlrefDW.rtm);

  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatusPointer(SLWOUP_M, rt_errorStatus);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
