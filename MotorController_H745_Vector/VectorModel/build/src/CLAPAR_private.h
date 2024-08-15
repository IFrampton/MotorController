/*
 * File: CLAPAR_private.h
 *
 * Code generated for Simulink model 'CLAPAR'.
 *
 * Model version                  : 1.48
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:11:50 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_CLAPAR_private_h_
#define RTW_HEADER_CLAPAR_private_h_
#include "rtwtypes.h"
#include "CLAPAR.h"
#include "CLAPAR_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         (*((rtm)->errorStatus))
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    (*((rtm)->errorStatus) = (val))
#endif

#ifndef rtmGetErrorStatusPointer
#define rtmGetErrorStatusPointer(rtm)  (rtm)->errorStatus
#endif

#ifndef rtmSetErrorStatusPointer
#define rtmSetErrorStatusPointer(rtm, val) ((rtm)->errorStatus = (val))
#endif

/* Invariant block signals (default storage) */
extern const ConstB_CLAPAR_h_T CLAPAR_ConstB;

#endif                                 /* RTW_HEADER_CLAPAR_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
