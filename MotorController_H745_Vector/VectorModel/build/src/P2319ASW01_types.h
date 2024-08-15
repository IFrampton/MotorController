/*
 * File: P2319ASW01_types.h
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

#ifndef RTW_HEADER_P2319ASW01_types_h_
#define RTW_HEADER_P2319ASW01_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_ASWIN_Supervisor_
#define DEFINED_TYPEDEF_FOR_ASWIN_Supervisor_

typedef struct {
  boolean_T ASWIN_MaiPwrSts;
  boolean_T ASWIN_AuxPwrSts;
  uint16_T ASWIN_BdT1;
  uint16_T ASWIN_BdT2;
  uint16_T ASWIN_McuT;
  uint16_T ASWIN_McuURef;
  uint16_T ASWIN_McuUBat;
} ASWIN_Supervisor;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ASWIN_TqSpdCtrl_
#define DEFINED_TYPEDEF_FOR_ASWIN_TqSpdCtrl_

typedef struct {
  uint8_T ASWIN_McuReqDa[8];
  uint8_T ASWIN_McuReqCt;
} ASWIN_TqSpdCtrl;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ASWIN_CurCtrl_
#define DEFINED_TYPEDEF_FOR_ASWIN_CurCtrl_

typedef struct {
  uint16_T ASWIN_HvBusU;
  uint16_T ASWIN_PhaCurA;
  uint16_T ASWIN_PhaCurB;
  uint16_T ASWIN_PhaCurC;
  int16_T ASWIN_EncoderCt;
  boolean_T ASWIN_EncoderZ;
  uint16_T ASWIN_HvBusCur;
  uint16_T ASWIN_PhaUA;
  uint16_T ASWIN_PhaUB;
  uint16_T ASWIN_PhaUC;
  uint16_T ASWIN_ResolverSin;
  uint16_T ASWIN_ResolverCos;
} ASWIN_CurCtrl;

#endif

#ifndef DEFINED_TYPEDEF_FOR_DRIVEMODE_
#define DEFINED_TYPEDEF_FOR_DRIVEMODE_

typedef uint8_T DRIVEMODE;

/* enum DRIVEMODE */
#define DISABLED                       ((DRIVEMODE)0U)           /* Default value */
#define TQ_CTRL                        ((DRIVEMODE)1U)
#define SPD_CTRL                       ((DRIVEMODE)2U)
#define OPEN_LOOP                      ((DRIVEMODE)3U)
#endif

#ifndef DEFINED_TYPEDEF_FOR_ASWOUT_Supervisor_
#define DEFINED_TYPEDEF_FOR_ASWOUT_Supervisor_

typedef struct {
  boolean_T ASWOUT_GreenLed;
  boolean_T ASWOUT_RedLed;
  boolean_T ASWOUT_YellowLed;
  boolean_T ASWOUT_ResolverExctEna;
  uint8_T ASWOUT_McuData2Da[8];
  boolean_T ASWOUT_CanPwrPwmEna;
  boolean_T ASWOUT_InPwrPwmEna;
  boolean_T ASWOUT_MtrPwrPwmEna;
  boolean_T ASWOUT_SwPwrPwmEna;
  boolean_T ASWOUT_PhaPwmEna;
} ASWOUT_Supervisor;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ASWOUT_TqSpdCtrl_
#define DEFINED_TYPEDEF_FOR_ASWOUT_TqSpdCtrl_

typedef struct {
  uint8_T ASWOUT_McuData1Da[8];
} ASWOUT_TqSpdCtrl;

#endif

#ifndef DEFINED_TYPEDEF_FOR_ASWOUT_CurCtrl_
#define DEFINED_TYPEDEF_FOR_ASWOUT_CurCtrl_

typedef struct {
  uint16_T ASWOUT_PhaAPwmDc;
  uint16_T ASWOUT_PhaBPwmDc;
  uint16_T ASWOUT_PhaCPwmDc;
} ASWOUT_CurCtrl;

#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_P2319ASW01_T RT_MODEL_P2319ASW01_T;

#endif                                 /* RTW_HEADER_P2319ASW01_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
