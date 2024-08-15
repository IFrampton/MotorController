/*
 * File: LowPassFilter_0O6LwJpz.c
 *
 * Code generated for Simulink model 'ADCINP'.
 *
 * Model version                  : 1.80
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:11:44 2024
 */

#include "rtwtypes.h"
#include "LowPassFilter_0O6LwJpz.h"
#include <math.h>

/*
 * Output and update for atomic system:
 *    'LowPassFilter' ('BlockLibrary:10')
 *    'LowPassFilter' ('BlockLibrary:10')
 *    'LowPassFilter' ('BlockLibrary:10')
 *    'LowPassFilter' ('BlockLibrary:10')
 *    'LowPassFilter' ('BlockLibrary:10')
 *    'LowPassFilter' ('BlockLibrary:10')
 *    'LowPassFilter' ('BlockLibrary:10')
 *    'LowPassFilter' ('BlockLibrary:10')
 *    'LowPassFilter' ('BlockLibrary:10')
 *    'LowPassFilter' ('BlockLibrary:10')
 * Common block description:
 *   Low-Pass Filter
 */
void LowPassFilter_0O6LwJpz(real32_T rtu_In, real32_T rtu_TiCon, real32_T
  rtu_SampTi, real32_T *rty_Out, DW_LowPassFilter_0O6LwJpz_T *localDW)
{
  /* Sum: 'Subtract3' ('BlockLibrary:21') incorporates:
   *  MinMax: 'Max' ('BlockLibrary:24')
   *  Product: 'Product1' ('BlockLibrary:19')
   *  Sum: 'Subtract2' ('BlockLibrary:20')
   *  UnitDelay: 'Unit Delay1' ('BlockLibrary:22')
   */
  *rty_Out = 1.0F / fmaxf(rtu_TiCon, rtu_SampTi) * rtu_SampTi * (rtu_In -
    localDW->UnitDelay1_DSTATE) + localDW->UnitDelay1_DSTATE;

  /* Update for UnitDelay: 'Unit Delay1' ('BlockLibrary:22') */
  localDW->UnitDelay1_DSTATE = *rty_Out;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
