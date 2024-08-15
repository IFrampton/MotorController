/*
 * File: Debounce_G4uuGAfd.h
 *
 * Code generated for Simulink model 'SLWINP'.
 *
 * Model version                  : 1.60
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:12:21 2024
 */

#ifndef RTW_HEADER_Debounce_G4uuGAfd_h_
#define RTW_HEADER_Debounce_G4uuGAfd_h_
#include "rtwtypes.h"

/* Block states (default storage) for system 'Debounce' ('BlockLibrary:55') */
typedef struct {
  real32_T Tmr;                        /* 'Debounce' ('BlockLibrary:67') */
  uint8_T is_c3_BlockLibrary;          /* 'Debounce' ('BlockLibrary:67') */
  uint8_T is_active_c3_BlockLibrary;   /* 'Debounce' ('BlockLibrary:67') */
} DW_Debounce_G4uuGAfd_T;

extern void Debounce_G4uuGAfd_Init(boolean_T *rty_Out);
extern void Debounce_G4uuGAfd(boolean_T rtu_In, real32_T rtu_DebounceRising,
  real32_T rtu_DebounceFalling, real32_T rtu_SampTi, boolean_T *rty_Out,
  DW_Debounce_G4uuGAfd_T *localDW);

#endif                                 /* RTW_HEADER_Debounce_G4uuGAfd_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
