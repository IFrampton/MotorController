/*
 * File: RateLimit_8K29mxJB.c
 *
 * Code generated for Simulink model 'SPDCTL'.
 *
 * Model version                  : 1.79
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:12:30 2024
 */

#include "rtwtypes.h"
#include "RateLimit_8K29mxJB.h"

/* Output and update for atomic system: 'RateLimit' ('BlockLibrary:35') */
void RateLimit_8K29mxJB(int16_T rtu_In, real32_T rtu_RateLimit, real32_T
  rtu_SampTi, real32_T *rty_Out, DW_RateLimit_8K29mxJB_T *localDW)
{
  real32_T rtb_Add_o;
  real32_T rtb_Product_n;

  /* Sum: 'Add' ('BlockLibrary:44') incorporates:
   *  UnitDelay: 'Unit Delay' ('BlockLibrary:42')
   */
  rtb_Add_o = (real32_T)rtu_In - localDW->UnitDelay_DSTATE;

  /* Product: 'Product' ('BlockLibrary:43') */
  rtb_Product_n = rtu_RateLimit * rtu_SampTi;

  /* Switch: 'Switch2' ('simulink:63:17:8') incorporates:
   *  RelationalOperator: 'LowerRelop1' ('simulink:63:17:6')
   */
  if (!(rtb_Add_o > rtb_Product_n)) {
    /* Switch: 'Switch' ('simulink:63:17:7') incorporates:
     *  RelationalOperator: 'UpperRelop' ('simulink:63:17:9')
     *  UnaryMinus: 'Unary Minus' ('BlockLibrary:47')
     */
    if (rtb_Add_o < -rtb_Product_n) {
      rtb_Product_n = -rtb_Product_n;
    } else {
      rtb_Product_n = rtb_Add_o;
    }

    /* End of Switch: 'Switch' ('simulink:63:17:7') */
  }

  /* End of Switch: 'Switch2' ('simulink:63:17:8') */

  /* Sum: 'Add1' ('BlockLibrary:45') incorporates:
   *  UnitDelay: 'Unit Delay' ('BlockLibrary:42')
   */
  *rty_Out = rtb_Product_n + localDW->UnitDelay_DSTATE;

  /* Update for UnitDelay: 'Unit Delay' ('BlockLibrary:42') */
  localDW->UnitDelay_DSTATE = *rty_Out;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
