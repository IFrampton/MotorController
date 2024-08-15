/*
 * File: rtmodel.c
 *
 * Code generated for Simulink model 'P2319ASW01'.
 *
 * Model version                  : 1.229
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:12:40 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "rtmodel.h"

/* Use this function only if you need to maintain compatibility with an existing static main program. */
void P2319ASW01_step(int_T tid)
{
  switch (tid) {
   case 0 :
    P2319ASW01_step0();
    break;

   case 1 :
    P2319ASW01_step1();
    break;

   case 2 :
    P2319ASW01_step2();
    break;

   default :
    /* do nothing */
    break;
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
