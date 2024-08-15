/*
 * File: Debounce_G4uuGAfd.c
 *
 * Code generated for Simulink model 'SLWINP'.
 *
 * Model version                  : 1.60
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:12:21 2024
 */

#include "rtwtypes.h"
#include "Debounce_G4uuGAfd.h"

/* Named constants for Chart: '<S1>/Debounce' */
#define SLWINP_IN_ACTIVE               ((uint8_T)1U)
#define SLWINP_IN_ACTIVE_WAIT          ((uint8_T)2U)
#define SLWINP_IN_INACTIVE             ((uint8_T)3U)
#define SLWINP_IN_INACTIVE_WAIT        ((uint8_T)4U)

/*
 * System initialize for atomic system:
 *    'Debounce' ('BlockLibrary:55')
 *    'Debounce' ('BlockLibrary:55')
 */
void Debounce_G4uuGAfd_Init(boolean_T *rty_Out)
{
  /* SystemInitialize for Chart: 'Debounce' ('BlockLibrary:67') */
  *rty_Out = false;
}

/*
 * Output and update for atomic system:
 *    'Debounce' ('BlockLibrary:55')
 *    'Debounce' ('BlockLibrary:55')
 * Common block description:
 *   Debounce
 */
void Debounce_G4uuGAfd(boolean_T rtu_In, real32_T rtu_DebounceRising, real32_T
  rtu_DebounceFalling, real32_T rtu_SampTi, boolean_T *rty_Out,
  DW_Debounce_G4uuGAfd_T *localDW)
{
  /* Chart: 'Debounce' ('BlockLibrary:67') */
  if (localDW->is_active_c3_BlockLibrary == 0U) {
    localDW->is_active_c3_BlockLibrary = 1U;
    localDW->is_c3_BlockLibrary = SLWINP_IN_INACTIVE;
    *rty_Out = false;
    localDW->Tmr = 0.0F;
  } else {
    switch (localDW->is_c3_BlockLibrary) {
     case SLWINP_IN_ACTIVE:
      if (!rtu_In) {
        localDW->is_c3_BlockLibrary = SLWINP_IN_ACTIVE_WAIT;
      } else {
        *rty_Out = true;
        localDW->Tmr = 0.0F;
      }
      break;

     case SLWINP_IN_ACTIVE_WAIT:
      if (rtu_In) {
        localDW->is_c3_BlockLibrary = SLWINP_IN_ACTIVE;
        *rty_Out = true;
        localDW->Tmr = 0.0F;
      } else if (localDW->Tmr >= rtu_DebounceFalling) {
        localDW->is_c3_BlockLibrary = SLWINP_IN_INACTIVE;
        *rty_Out = false;
        localDW->Tmr = 0.0F;
      } else {
        *rty_Out = true;
        localDW->Tmr += rtu_SampTi;
      }
      break;

     case SLWINP_IN_INACTIVE:
      if (rtu_In) {
        localDW->is_c3_BlockLibrary = SLWINP_IN_INACTIVE_WAIT;
        *rty_Out = false;
        localDW->Tmr += rtu_SampTi;
      } else {
        *rty_Out = false;
        localDW->Tmr = 0.0F;
      }
      break;

     default:
      /* case IN_INACTIVE_WAIT: */
      if (!rtu_In) {
        localDW->is_c3_BlockLibrary = SLWINP_IN_INACTIVE;
        *rty_Out = false;
        localDW->Tmr = 0.0F;
      } else if (localDW->Tmr >= rtu_DebounceRising) {
        localDW->is_c3_BlockLibrary = SLWINP_IN_ACTIVE;
        *rty_Out = true;
        localDW->Tmr = 0.0F;
      } else {
        *rty_Out = false;
        localDW->Tmr += rtu_SampTi;
      }
      break;
    }
  }

  /* End of Chart: 'Debounce' ('BlockLibrary:67') */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
