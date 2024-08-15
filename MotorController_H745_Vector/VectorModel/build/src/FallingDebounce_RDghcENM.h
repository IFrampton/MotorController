/*
 * File: FallingDebounce_RDghcENM.h
 *
 * Code generated for Simulink model 'MEDINP'.
 *
 * Model version                  : 1.36
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:12:04 2024
 */

#ifndef RTW_HEADER_FallingDebounce_RDghcENM_h_
#define RTW_HEADER_FallingDebounce_RDghcENM_h_
#include "rtwtypes.h"

/* Block states (default storage) for system 'FallingDebounce' ('BlockLibrary:92') */
typedef struct {
  real32_T Tmr;                        /* 'Debounce' ('BlockLibrary:97') */
  uint8_T is_c1_BlockLibrary;          /* 'Debounce' ('BlockLibrary:97') */
  uint8_T is_active_c1_BlockLibrary;   /* 'Debounce' ('BlockLibrary:97') */
} DW_FallingDebounce_RDghcENM_T;

extern void FallingDebounce_RDghcENM_Init(boolean_T *rty_Out);
extern void FallingDebounce_RDghcENM(boolean_T rtu_In, real32_T
  rtu_DebounceFalling, real32_T rtu_SampTi, boolean_T *rty_Out,
  DW_FallingDebounce_RDghcENM_T *localDW);

#endif                              /* RTW_HEADER_FallingDebounce_RDghcENM_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
