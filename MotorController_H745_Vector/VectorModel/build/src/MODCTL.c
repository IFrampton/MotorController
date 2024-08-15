/*
 * File: MODCTL.c
 *
 * Code generated for Simulink model 'MODCTL'.
 *
 * Model version                  : 1.60
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:12:12 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "MODCTL.h"
#include "MODCTL_types.h"
#include "rtwtypes.h"
#include <math.h>
#include "MODCTL_private.h"

/* Named constants for Chart: '<Root>/DriveModeControl' */
#define MODCTL_IN_ACTIVE               ((uint8_T)1U)
#define MODCTL_IN_DISABLED             ((uint8_T)1U)
#define MODCTL_IN_NO_ACTIVE_CHILD      ((uint8_T)0U)
#define MODCTL_IN_OPEN_LOOP            ((uint8_T)2U)
#define MODCTL_IN_POWER_ERROR          ((uint8_T)2U)
#define MODCTL_IN_SPEED                ((uint8_T)3U)
#define MODCTL_IN_TORQUE               ((uint8_T)4U)
#define MODCTL_IN_WAKE                 ((uint8_T)3U)

MdlrefDW_MODCTL_T MODCTL_MdlrefDW;

/* Block signals (default storage) */
B_MODCTL_c_T MODCTL_B;

/* Block states (default storage) */
DW_MODCTL_f_T MODCTL_DW;

/* Output and update for referenced model: 'MODCTL' */
void MODCTL(const DRIVEMODE *rtu_DrvModReq, const int16_T *rtu_MotSpd, const
            int16_T *rtu_MotSpdReqCan, const real32_T *rtu_MotTqReqCan, const
            boolean_T *rtu_MainPwrAcv, const boolean_T *rtu_AuxPwrAcv)
{
  int16_T u;
  int16_T u_0;
  boolean_T rtb_LogicalOperator1;
  boolean_T rtb_RelationalOperator;

  /* Abs: '<Root>/Abs' */
  u = *rtu_MotSpd;

  /* Abs: '<Root>/Abs1' */
  u_0 = *rtu_MotSpdReqCan;

  /* Abs: '<Root>/Abs' */
  if (u < 0) {
    u = (int16_T)-u;
  }

  /* Abs: '<Root>/Abs1' */
  if (u_0 < 0) {
    u_0 = (int16_T)-u_0;
  }

  /* Logic: '<Root>/Logical Operator' incorporates:
   *  Abs: '<Root>/Abs'
   *  Abs: '<Root>/Abs1'
   *  Abs: '<Root>/Abs2'
   *  Constant: '<Root>/Constant'
   *  Constant: '<Root>/Constant2'
   *  Constant: '<Root>/Constant3'
   *  RelationalOperator: '<Root>/Relational Operator'
   *  RelationalOperator: '<Root>/Relational Operator1'
   *  RelationalOperator: '<Root>/Relational Operator2'
   */
  rtb_RelationalOperator = ((u < MotSpdThdModChg_C) && (u_0 <
    MotSpdReqThdModChg_C) && (fabsf(*rtu_MotTqReqCan) < MotTqReqThdModChg_C));

  /* Logic: '<Root>/Logical Operator1' */
  rtb_LogicalOperator1 = ((*rtu_MainPwrAcv) && (*rtu_AuxPwrAcv));

  /* Chart: '<Root>/DriveModeControl' incorporates:
   *  Constant: '<Root>/Constant7'
   *  RelationalOperator: '<S1>/FixPt Relational Operator'
   *  UnitDelay: '<S1>/Delay Input1'
   *
   * Block description for '<Root>/DriveModeControl':
   *  Drive Mode Control
   *
   * Block description for '<S1>/Delay Input1':
   *
   *  Store in Global RAM
   */
  if (MODCTL_DW.is_active_c3_MODCTL == 0U) {
    MODCTL_DW.is_active_c3_MODCTL = 1U;
    MODCTL_DW.is_c3_MODCTL = MODCTL_IN_WAKE;
    MODCTL_DW.Tmr = 0.0F;
  } else {
    boolean_T guard1;
    boolean_T guard2;
    boolean_T guard3;
    guard1 = false;
    guard2 = false;
    guard3 = false;
    switch (MODCTL_DW.is_c3_MODCTL) {
     case MODCTL_IN_ACTIVE:
      if (!rtb_LogicalOperator1) {
        MODCTL_DW.is_ACTIVE = MODCTL_IN_NO_ACTIVE_CHILD;
        MODCTL_DW.is_c3_MODCTL = MODCTL_IN_POWER_ERROR;
      } else {
        MODCTL_B.PwrCmd_g = true;
        switch (MODCTL_DW.is_ACTIVE) {
         case MODCTL_IN_DISABLED:
          if ((*rtu_DrvModReq != DISABLED) && rtb_RelationalOperator) {
            if (*rtu_DrvModReq == SPD_CTRL) {
              MODCTL_DW.is_ACTIVE = MODCTL_IN_SPEED;
              MODCTL_B.DrvMod_b = SPD_CTRL;
            } else if (*rtu_DrvModReq == TQ_CTRL) {
              MODCTL_DW.is_ACTIVE = MODCTL_IN_TORQUE;
              MODCTL_B.DrvMod_b = TQ_CTRL;
            } else if (*rtu_DrvModReq == OPEN_LOOP) {
              MODCTL_DW.is_ACTIVE = MODCTL_IN_OPEN_LOOP;
              MODCTL_B.DrvMod_b = OPEN_LOOP;
            } else {
              MODCTL_DW.is_ACTIVE = MODCTL_IN_DISABLED;
              MODCTL_B.DrvMod_b = DISABLED;
            }
          } else {
            MODCTL_B.DrvMod_b = DISABLED;
          }
          break;

         case MODCTL_IN_OPEN_LOOP:
          if (*rtu_DrvModReq != OPEN_LOOP) {
            if (rtb_RelationalOperator) {
              if (*rtu_DrvModReq == SPD_CTRL) {
                MODCTL_DW.is_ACTIVE = MODCTL_IN_SPEED;
                MODCTL_B.DrvMod_b = SPD_CTRL;
              } else if (*rtu_DrvModReq == TQ_CTRL) {
                MODCTL_DW.is_ACTIVE = MODCTL_IN_TORQUE;
                MODCTL_B.DrvMod_b = TQ_CTRL;
              } else if (*rtu_DrvModReq == OPEN_LOOP) {
                MODCTL_DW.is_ACTIVE = MODCTL_IN_OPEN_LOOP;
                MODCTL_B.DrvMod_b = OPEN_LOOP;
              } else {
                guard2 = true;
              }
            } else {
              guard2 = true;
            }
          } else {
            MODCTL_B.DrvMod_b = OPEN_LOOP;
          }
          break;

         case MODCTL_IN_SPEED:
          if (*rtu_DrvModReq != SPD_CTRL) {
            if (rtb_RelationalOperator) {
              if (*rtu_DrvModReq == SPD_CTRL) {
                MODCTL_DW.is_ACTIVE = MODCTL_IN_SPEED;
                MODCTL_B.DrvMod_b = SPD_CTRL;
              } else if (*rtu_DrvModReq == TQ_CTRL) {
                MODCTL_DW.is_ACTIVE = MODCTL_IN_TORQUE;
                MODCTL_B.DrvMod_b = TQ_CTRL;
              } else if (*rtu_DrvModReq == OPEN_LOOP) {
                MODCTL_DW.is_ACTIVE = MODCTL_IN_OPEN_LOOP;
                MODCTL_B.DrvMod_b = OPEN_LOOP;
              } else {
                guard3 = true;
              }
            } else {
              guard3 = true;
            }
          } else {
            MODCTL_B.DrvMod_b = SPD_CTRL;
          }
          break;

         default:
          /* case IN_TORQUE: */
          if (*rtu_DrvModReq != TQ_CTRL) {
            if (rtb_RelationalOperator) {
              if (*rtu_DrvModReq == SPD_CTRL) {
                MODCTL_DW.is_ACTIVE = MODCTL_IN_SPEED;
                MODCTL_B.DrvMod_b = SPD_CTRL;
              } else if (*rtu_DrvModReq == TQ_CTRL) {
                MODCTL_DW.is_ACTIVE = MODCTL_IN_TORQUE;
                MODCTL_B.DrvMod_b = TQ_CTRL;
              } else if (*rtu_DrvModReq == OPEN_LOOP) {
                MODCTL_DW.is_ACTIVE = MODCTL_IN_OPEN_LOOP;
                MODCTL_B.DrvMod_b = OPEN_LOOP;
              } else {
                guard1 = true;
              }
            } else {
              guard1 = true;
            }
          } else {
            MODCTL_B.DrvMod_b = TQ_CTRL;
          }
          break;
        }
      }
      break;

     case MODCTL_IN_POWER_ERROR:
      if ((int32_T)WakeRetry_C > (int32_T)MODCTL_DW.DelayInput1_DSTATE) {
        MODCTL_DW.is_c3_MODCTL = MODCTL_IN_WAKE;
        MODCTL_DW.Tmr = 0.0F;
      } else {
        MODCTL_B.DrvMod_b = DISABLED;
        MODCTL_B.PwrCmd_g = false;
      }
      break;

     default:
      /* case IN_WAKE: */
      if (MODCTL_DW.Tmr >= WakeTout_C) {
        MODCTL_DW.is_c3_MODCTL = MODCTL_IN_POWER_ERROR;
      } else if (rtb_LogicalOperator1) {
        MODCTL_DW.is_c3_MODCTL = MODCTL_IN_ACTIVE;
        MODCTL_DW.is_ACTIVE = MODCTL_IN_DISABLED;
        MODCTL_B.DrvMod_b = DISABLED;
      } else {
        MODCTL_B.DrvMod_b = DISABLED;
        MODCTL_B.PwrCmd_g = true;
        MODCTL_DW.Tmr += 0.1F;
      }
      break;
    }

    if (guard3) {
      MODCTL_DW.is_ACTIVE = MODCTL_IN_DISABLED;
      MODCTL_B.DrvMod_b = DISABLED;
    }

    if (guard2) {
      MODCTL_DW.is_ACTIVE = MODCTL_IN_DISABLED;
      MODCTL_B.DrvMod_b = DISABLED;
    }

    if (guard1) {
      MODCTL_DW.is_ACTIVE = MODCTL_IN_DISABLED;
      MODCTL_B.DrvMod_b = DISABLED;
    }
  }

  /* End of Chart: '<Root>/DriveModeControl' */

  /* Switch: '<Root>/Switch1' incorporates:
   *  Constant: '<Root>/Constant5'
   */
  if (PwrCmdDialEna_C) {
    /* Switch: '<Root>/Switch1' incorporates:
     *  Constant: '<Root>/Constant6'
     */
    PwrCmd = PwrCmdDialVal_C;
  } else {
    /* Switch: '<Root>/Switch1' */
    PwrCmd = MODCTL_B.PwrCmd_g;
  }

  /* End of Switch: '<Root>/Switch1' */

  /* Switch: '<Root>/Switch2' incorporates:
   *  Constant: '<Root>/Constant1'
   */
  if (DrvModDialEna_C) {
    /* Switch: '<Root>/Switch2' incorporates:
     *  Constant: '<Root>/Constant4'
     */
    DrvMod = DrvModDialVal_C;
  } else {
    /* Switch: '<Root>/Switch2' */
    DrvMod = MODCTL_B.DrvMod_b;
  }

  /* End of Switch: '<Root>/Switch2' */

  /* Update for UnitDelay: '<S1>/Delay Input1' incorporates:
   *  Constant: '<Root>/Constant7'
   *
   * Block description for '<S1>/Delay Input1':
   *
   *  Store in Global RAM
   */
  MODCTL_DW.DelayInput1_DSTATE = WakeRetry_C;
}

/* Model initialize function */
void MODCTL_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_MODCTL_T *const MODCTL_M = &(MODCTL_MdlrefDW.rtm);

  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatusPointer(MODCTL_M, rt_errorStatus);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
