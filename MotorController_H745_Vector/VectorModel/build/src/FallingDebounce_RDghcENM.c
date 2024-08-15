/*
 * File: FallingDebounce_RDghcENM.c
 *
 * Code generated for Simulink model 'MEDINP'.
 *
 * Model version                  : 1.36
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:12:04 2024
 */

#include "rtwtypes.h"
#include "FallingDebounce_RDghcENM.h"

/* Named constants for Chart: '<S2>/Debounce' */
#define MEDINP_IN_ACTIVE               ((uint8_T)1U)
#define MEDINP_IN_ACTIVE_WAIT          ((uint8_T)2U)
#define MEDINP_IN_INACTIVE             ((uint8_T)3U)

/* System initialize for atomic system: 'FallingDebounce' ('BlockLibrary:92') */
void FallingDebounce_RDghcENM_Init(boolean_T *rty_Out)
{
  /* SystemInitialize for Chart: 'Debounce' ('BlockLibrary:97') */
  *rty_Out = false;
}

/* Output and update for atomic system: 'FallingDebounce' ('BlockLibrary:92') */
void FallingDebounce_RDghcENM(boolean_T rtu_In, real32_T rtu_DebounceFalling,
  real32_T rtu_SampTi, boolean_T *rty_Out, DW_FallingDebounce_RDghcENM_T
  *localDW)
{
  /* Chart: 'Debounce' ('BlockLibrary:97') */
  if (localDW->is_active_c1_BlockLibrary == 0U) {
    localDW->is_active_c1_BlockLibrary = 1U;
    localDW->is_c1_BlockLibrary = MEDINP_IN_INACTIVE;
    *rty_Out = false;
    localDW->Tmr = 0.0F;
  } else {
    switch (localDW->is_c1_BlockLibrary) {
     case MEDINP_IN_ACTIVE:
      if (!rtu_In) {
        localDW->is_c1_BlockLibrary = MEDINP_IN_ACTIVE_WAIT;
      } else {
        *rty_Out = true;
        localDW->Tmr = 0.0F;
      }
      break;

     case MEDINP_IN_ACTIVE_WAIT:
      if (rtu_In) {
        localDW->is_c1_BlockLibrary = MEDINP_IN_ACTIVE;
        *rty_Out = true;
        localDW->Tmr = 0.0F;
      } else if (localDW->Tmr >= rtu_DebounceFalling) {
        localDW->is_c1_BlockLibrary = MEDINP_IN_INACTIVE;
        *rty_Out = false;
        localDW->Tmr = 0.0F;
      } else {
        *rty_Out = true;
        localDW->Tmr += rtu_SampTi;
      }
      break;

     default:
      /* case IN_INACTIVE: */
      if (rtu_In) {
        localDW->is_c1_BlockLibrary = MEDINP_IN_ACTIVE;
        *rty_Out = true;
        localDW->Tmr = 0.0F;
      } else {
        *rty_Out = false;
        localDW->Tmr = 0.0F;
      }
      break;
    }
  }

  /* End of Chart: 'Debounce' ('BlockLibrary:97') */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
