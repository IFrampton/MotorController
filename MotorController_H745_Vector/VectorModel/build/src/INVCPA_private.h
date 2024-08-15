/*
 * File: INVCPA_private.h
 *
 * Code generated for Simulink model 'INVCPA'.
 *
 * Model version                  : 1.40
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:11:58 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_INVCPA_private_h_
#define RTW_HEADER_INVCPA_private_h_
#include "rtwtypes.h"
#include "INVCPA.h"
#include "INVCPA_types.h"

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
extern const ConstB_INVCPA_h_T INVCPA_ConstB;

#endif                                 /* RTW_HEADER_INVCPA_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
