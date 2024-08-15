/*
 * File: MODCTL_types.h
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

#ifndef RTW_HEADER_MODCTL_types_h_
#define RTW_HEADER_MODCTL_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_DRIVEMODE_
#define DEFINED_TYPEDEF_FOR_DRIVEMODE_

typedef uint8_T DRIVEMODE;

/* enum DRIVEMODE */
#define DISABLED                       ((DRIVEMODE)0U)           /* Default value */
#define TQ_CTRL                        ((DRIVEMODE)1U)
#define SPD_CTRL                       ((DRIVEMODE)2U)
#define OPEN_LOOP                      ((DRIVEMODE)3U)
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_MODCTL_T RT_MODEL_MODCTL_T;

#endif                                 /* RTW_HEADER_MODCTL_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
