/*
 * File: MEDOUP.c
 *
 * Code generated for Simulink model 'MEDOUP'.
 *
 * Model version                  : 1.21
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:12:09 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "MEDOUP.h"
#include "rtwtypes.h"
#include "MEDOUP_types.h"
#include "MEDOUP_private.h"

MdlrefDW_MEDOUP_T MEDOUP_MdlrefDW;

/* Block signals (default storage) */
B_MEDOUP_c_T MEDOUP_B;

/* Block states (default storage) */
DW_MEDOUP_f_T MEDOUP_DW;

/* Output and update for referenced model: 'MEDOUP' */
void MEDOUP(const real32_T *rtu_HvBusCur, const real32_T *rtu_HvBusU, const
            real32_T *rtu_PhaCurQ, const int16_T *rtu_MotSpd, const DRIVEMODE
            *rtu_DrvMod)
{
  int32_T i;

  /* MultiPortSwitch: '<Root>/Multiport Switch' */
  switch (*rtu_DrvMod) {
   case TQ_CTRL:
    /* MultiPortSwitch: '<Root>/Multiport Switch' incorporates:
     *  Constant: '<Root>/Constant5'
     */
    MEDOUP_B.MultiportSwitch = 1U;
    break;

   case SPD_CTRL:
    /* MultiPortSwitch: '<Root>/Multiport Switch' incorporates:
     *  Constant: '<Root>/Constant4'
     */
    MEDOUP_B.MultiportSwitch = 2U;
    break;

   case OPEN_LOOP:
    /* MultiPortSwitch: '<Root>/Multiport Switch' incorporates:
     *  Constant: '<Root>/Constant3'
     */
    MEDOUP_B.MultiportSwitch = 3U;
    break;

   default:
    /* MultiPortSwitch: '<Root>/Multiport Switch' incorporates:
     *  Constant: '<Root>/Constant2'
     */
    MEDOUP_B.MultiportSwitch = 0U;
    break;
  }

  /* End of MultiPortSwitch: '<Root>/Multiport Switch' */

  /* S-Function (scanpack): '<Root>/CAN Pack' */
  /* S-Function (scanpack): '<Root>/CAN Pack' */
  MEDOUP_B.CANPack.ID = 1104U;
  MEDOUP_B.CANPack.Length = 8U;
  MEDOUP_B.CANPack.Extended = 0U;
  MEDOUP_B.CANPack.Remote = 0;
  MEDOUP_B.CANPack.Data[0] = 0;
  MEDOUP_B.CANPack.Data[1] = 0;
  MEDOUP_B.CANPack.Data[2] = 0;
  MEDOUP_B.CANPack.Data[3] = 0;
  MEDOUP_B.CANPack.Data[4] = 0;
  MEDOUP_B.CANPack.Data[5] = 0;
  MEDOUP_B.CANPack.Data[6] = 0;
  MEDOUP_B.CANPack.Data[7] = 0;

  {
    /* --------------- START Packing signal 0 ------------------
     *  startBit                = 16
     *  length                  = 16
     *  desiredSignalByteLayout = LITTLEENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 0.02
     *  offset                  = -650.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/
    {
      real32_T outValue = 0;

      {
        real32_T result = (*rtu_HvBusCur);

        /* full scaling operation */
        result = (result - -650.0F) * (1 / 0.02F);

        /* round to closest integer value for integer CAN signal */
        outValue = roundf(result);
      }

      {
        uint16_T packedValue;
        if (outValue > (real32_T)(65535)) {
          packedValue = (uint16_T) 65535;
        } else if (outValue < (real32_T)(0)) {
          packedValue = (uint16_T) 0;
        } else {
          packedValue = (uint16_T) (outValue);
        }

        {
          {
            MEDOUP_B.CANPack.Data[2] = MEDOUP_B.CANPack.Data[2] | (uint8_T)
              ((uint16_T)(packedValue & (uint16_T)0xFFU));
            MEDOUP_B.CANPack.Data[3] = MEDOUP_B.CANPack.Data[3] | (uint8_T)
              ((uint16_T)((uint16_T)(packedValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    /* --------------- START Packing signal 1 ------------------
     *  startBit                = 0
     *  length                  = 12
     *  desiredSignalByteLayout = LITTLEENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 0.1
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/
    {
      real32_T outValue = 0;

      {
        real32_T result = (*rtu_HvBusU);

        /* no offset to apply */
        result = result * (1 / 0.1F);

        /* round to closest integer value for integer CAN signal */
        outValue = roundf(result);
      }

      {
        uint16_T packedValue;
        if (outValue > (real32_T)(4095)) {
          packedValue = (uint16_T) 4095;
        } else if (outValue < (real32_T)(0)) {
          packedValue = (uint16_T) 0;
        } else {
          packedValue = (uint16_T) (outValue);
        }

        {
          {
            MEDOUP_B.CANPack.Data[0] = MEDOUP_B.CANPack.Data[0] | (uint8_T)
              ((uint16_T)(packedValue & (uint16_T)0xFFU));
            MEDOUP_B.CANPack.Data[1] = MEDOUP_B.CANPack.Data[1] | (uint8_T)
              ((uint16_T)((uint16_T)(packedValue & (uint16_T)0xF00U) >> 8));
          }
        }
      }
    }

    /* --------------- START Packing signal 2 ------------------
     *  startBit                = 32
     *  length                  = 16
     *  desiredSignalByteLayout = LITTLEENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 0.02
     *  offset                  = -650.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/
    {
      real32_T outValue = 0;

      {
        real32_T result = (*rtu_PhaCurQ);

        /* full scaling operation */
        result = (result - -650.0F) * (1 / 0.02F);

        /* round to closest integer value for integer CAN signal */
        outValue = roundf(result);
      }

      {
        uint16_T packedValue;
        if (outValue > (real32_T)(65535)) {
          packedValue = (uint16_T) 65535;
        } else if (outValue < (real32_T)(0)) {
          packedValue = (uint16_T) 0;
        } else {
          packedValue = (uint16_T) (outValue);
        }

        {
          {
            MEDOUP_B.CANPack.Data[4] = MEDOUP_B.CANPack.Data[4] | (uint8_T)
              ((uint16_T)(packedValue & (uint16_T)0xFFU));
            MEDOUP_B.CANPack.Data[5] = MEDOUP_B.CANPack.Data[5] | (uint8_T)
              ((uint16_T)((uint16_T)(packedValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    /* --------------- START Packing signal 3 ------------------
     *  startBit                = 48
     *  length                  = 16
     *  desiredSignalByteLayout = LITTLEENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = -32500.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/
    {
      int32_T packingValue = 0;

      {
        int32_T result = (int32_T) ((*rtu_MotSpd));

        /* no factor to apply */
        result = (int32_T) (result - -32500);
        packingValue = result;
      }

      if (packingValue < 0) {
        packingValue = 0;
      }

      {
        uint16_T packedValue;
        if (packingValue > (int32_T)(65535)) {
          packedValue = (uint16_T) 65535;
        } else if (packingValue < (int32_T)(0)) {
          packedValue = (uint16_T) 0;
        } else {
          packedValue = (uint16_T) (packingValue);
        }

        {
          {
            MEDOUP_B.CANPack.Data[6] = MEDOUP_B.CANPack.Data[6] | (uint8_T)
              ((uint16_T)(packedValue & (uint16_T)0xFFU));
            MEDOUP_B.CANPack.Data[7] = MEDOUP_B.CANPack.Data[7] | (uint8_T)
              ((uint16_T)((uint16_T)(packedValue & (uint16_T)0xFF00U) >> 8));
          }
        }
      }
    }

    /* --------------- START Packing signal 4 ------------------
     *  startBit                = 12
     *  length                  = 2
     *  desiredSignalByteLayout = LITTLEENDIAN
     *  dataType                = UNSIGNED
     *  factor                  = 1.0
     *  offset                  = 0.0
     *  minimum                 = 0.0
     *  maximum                 = 0.0
     * -----------------------------------------------------------------------*/
    {
      uint32_T packingValue = 0;

      {
        uint32_T result = (uint32_T) (MEDOUP_B.MultiportSwitch);

        /* no scaling required */
        packingValue = result;
      }

      {
        uint8_T packedValue;
        if (packingValue > (uint8_T)(3)) {
          packedValue = (uint8_T) 3;
        } else {
          packedValue = (uint8_T) (packingValue);
        }

        {
          {
            MEDOUP_B.CANPack.Data[1] = MEDOUP_B.CANPack.Data[1] | (uint8_T)
              ((uint8_T)((uint8_T)(packedValue & (uint8_T)0x3U) << 4));
          }
        }
      }
    }
  }

  for (i = 0; i < 8; i++) {
    /* Switch: '<Root>/Switch' incorporates:
     *  Constant: '<Root>/Constant'
     */
    if (McuData1DaDialEna_C) {
      /* Switch: '<Root>/Switch' incorporates:
       *  Constant: '<Root>/Constant1'
       */
      ASWOUT_McuData1Da[i] = McuData1DaDialVal_CA[i];
    } else {
      /* Switch: '<Root>/Switch' */
      ASWOUT_McuData1Da[i] = MEDOUP_B.CANPack.Data[i];
    }

    /* End of Switch: '<Root>/Switch' */
  }
}

/* Model initialize function */
void MEDOUP_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_MEDOUP_T *const MEDOUP_M = &(MEDOUP_MdlrefDW.rtm);

  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatusPointer(MEDOUP_M, rt_errorStatus);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
