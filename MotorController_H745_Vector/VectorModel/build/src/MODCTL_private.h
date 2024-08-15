/*
 * File: MODCTL_private.h
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

#ifndef RTW_HEADER_MODCTL_private_h_
#define RTW_HEADER_MODCTL_private_h_
#include "rtwtypes.h"
#include "MODCTL_types.h"

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
#endif                                 /* RTW_HEADER_MODCTL_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
