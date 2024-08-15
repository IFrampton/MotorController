/*
 * File: ADCINP.h
 *
 * Code generated for Simulink model 'ADCINP'.
 *
 * Model version                  : 1.80
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:11:44 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_ADCINP_h_
#define RTW_HEADER_ADCINP_h_
#ifndef ADCINP_COMMON_INCLUDES_
#define ADCINP_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* ADCINP_COMMON_INCLUDES_ */

#include "ADCINP_types.h"
#include "LowPassFilter_0O6LwJpz.h"

/* Block states (default storage) for model 'ADCINP' */
#ifndef ADCINP_MDLREF_HIDE_CHILD_

typedef struct {
  DW_LowPassFilter_0O6LwJpz_T LowPassFilter9;/* '<Root>/LowPassFilter9' */
  DW_LowPassFilter_0O6LwJpz_T LowPassFilter8;/* '<Root>/LowPassFilter8' */
  DW_LowPassFilter_0O6LwJpz_T LowPassFilter7;/* '<Root>/LowPassFilter7' */
  DW_LowPassFilter_0O6LwJpz_T LowPassFilter6;/* '<Root>/LowPassFilter6' */
  DW_LowPassFilter_0O6LwJpz_T LowPassFilter5;/* '<Root>/LowPassFilter5' */
  DW_LowPassFilter_0O6LwJpz_T LowPassFilter4;/* '<Root>/LowPassFilter4' */
  DW_LowPassFilter_0O6LwJpz_T LowPassFilter3;/* '<Root>/LowPassFilter3' */
  DW_LowPassFilter_0O6LwJpz_T LowPassFilter2;/* '<Root>/LowPassFilter2' */
  DW_LowPassFilter_0O6LwJpz_T LowPassFilter1;/* '<Root>/LowPassFilter1' */
  DW_LowPassFilter_0O6LwJpz_T LowPassFilter;/* '<Root>/LowPassFilter' */
} DW_ADCINP_f_T;

#endif                                 /*ADCINP_MDLREF_HIDE_CHILD_*/

#ifndef ADCINP_MDLREF_HIDE_CHILD_

/* Real-time Model Data Structure */
struct tag_RTM_ADCINP_T {
  const char_T **errorStatus;
};

#endif                                 /*ADCINP_MDLREF_HIDE_CHILD_*/

#ifndef ADCINP_MDLREF_HIDE_CHILD_

typedef struct {
  RT_MODEL_ADCINP_T rtm;
} MdlrefDW_ADCINP_T;

#endif                                 /*ADCINP_MDLREF_HIDE_CHILD_*/

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern uint16_T ASWIN_HvBusU;          /* '<Root>/ASWIN_HvBusU'
                                        * The raw ADC input value
                                        */
extern uint16_T ASWIN_PhaCurA;         /* '<Root>/ASWIN_PhaCurA'
                                        * The raw ADC input value
                                        */
extern uint16_T ASWIN_PhaCurB;         /* '<Root>/ASWIN_PhaCurB'
                                        * The raw ADC input value
                                        */
extern uint16_T ASWIN_PhaCurC;         /* '<Root>/ASWIN_PhaCurC'
                                        * The raw ADC input value
                                        */
extern uint16_T ASWIN_HvBusCur;        /* '<Root>/ASWIN_HvBusCur'
                                        * The raw ADC input value
                                        */
extern uint16_T ASWIN_PhaUA;           /* '<Root>/ASWIN_PhaUA'
                                        * The raw ADC input value
                                        */
extern uint16_T ASWIN_PhaUB;           /* '<Root>/ASWIN_PhaUB'
                                        * The raw ADC input value
                                        */
extern uint16_T ASWIN_PhaUC;           /* '<Root>/ASWIN_PhaUC'
                                        * The raw ADC input value
                                        */
extern uint16_T ASWIN_ResolverSin;     /* '<Root>/ASWIN_ResolverSin'
                                        * The raw ADC input value
                                        */
extern uint16_T ASWIN_ResolverCos;     /* '<Root>/ASWIN_ResolverCos'
                                        * The raw ADC input value
                                        */
extern real32_T ResolverSinCos[2];     /* '<Root>/Switch5'
                                        * Resolver sine and cosine signals.
                                        */
extern real32_T HvBusU;                /* '<Root>/Switch'
                                        * The DC bus voltage into the inverter
                                        */
extern real32_T PhaCurA;               /* '<Root>/Switch1'
                                        * Phase A current
                                        */
extern real32_T PhaCurB;               /* '<Root>/Switch2'
                                        * Phase B current
                                        */
extern real32_T PhaCurC;               /* '<Root>/Switch3'
                                        * Phase C current
                                        */
extern real32_T HvBusCur;              /* '<Root>/Switch4'
                                        * The DC bus current into the inverter
                                        */
extern real32_T PhaUA;                 /* '<Root>/LowPassFilter5'
                                        * Phase A voltage
                                        */
extern real32_T PhaUB;                 /* '<Root>/LowPassFilter6'
                                        * Phase B voltage
                                        */
extern real32_T PhaUC;                 /* '<Root>/LowPassFilter7'
                                        * Phase C voltage
                                        */
extern void ADCINP(void);

/* Model reference registration function */
extern void ADCINP_initialize(const char_T **rt_errorStatus);

/* Exported data declaration */

/* Calibration memory section */
/* Declaration for custom storage class: Calibration */
extern __attribute__ ((section (".cal_data"))) boolean_T HvBusCurDialEna_C;/* Referenced by: '<Root>/Constant16' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T HvBusCurDialVal_C;/* Referenced by: '<Root>/Constant17' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T HvBusCurFilTiCon_C;/* Referenced by: '<Root>/Constant35' */

/* Low pass filter time constant for signal input processing */
extern __attribute__ ((section (".cal_data"))) real32_T HvBusCurGain_C;/* Referenced by: '<Root>/Constant18' */

/* Gain to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T HvBusCurOfs_C;/* Referenced by: '<Root>/Constant19' */

/* Offset to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) boolean_T HvBusUDialEna_C;/* Referenced by: '<Root>/Constant' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T HvBusUDialVal_C;/* Referenced by: '<Root>/Constant1' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T HvBusUFilTiCon_C;/* Referenced by: '<Root>/Constant33' */

/* Low pass filter time constant for signal input processing */
extern __attribute__ ((section (".cal_data"))) real32_T HvBusUGain_C;/* Referenced by: '<Root>/Constant2' */

/* Gain to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T HvBusUOfs_C;/* Referenced by: '<Root>/Constant9' */

/* Offset to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaCurADialEna_C;/* Referenced by: '<Root>/Constant10' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurADialVal_C;/* Referenced by: '<Root>/Constant11' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurAFilTiCon_C;/* Referenced by: '<Root>/Constant31' */

/* Low pass filter time constant for signal input processing */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurAGain_C;/* Referenced by: '<Root>/Constant3' */

/* Gain to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurAOfs_C;/* Referenced by: '<Root>/Constant6' */

/* Offset to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaCurBDialEna_C;/* Referenced by: '<Root>/Constant12' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurBDialVal_C;/* Referenced by: '<Root>/Constant13' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurBFilTiCon_C;/* Referenced by: '<Root>/Constant29' */

/* Low pass filter time constant for signal input processing */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurBGain_C;/* Referenced by: '<Root>/Constant4' */

/* Gain to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurBOfs_C;/* Referenced by: '<Root>/Constant7' */

/* Offset to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) boolean_T PhaCurCDialEna_C;/* Referenced by: '<Root>/Constant14' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurCDialVal_C;/* Referenced by: '<Root>/Constant15' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurCFilTiCon_C;/* Referenced by: '<Root>/Constant27' */

/* Low pass filter time constant for signal input processing */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurCGain_C;/* Referenced by: '<Root>/Constant5' */

/* Gain to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T PhaCurCOfs_C;/* Referenced by: '<Root>/Constant8' */

/* Offset to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUAFilTiCon_C;/* Referenced by: '<Root>/Constant37' */

/* Low pass filter time constant for signal input processing */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUAGain_C;/* Referenced by: '<Root>/Constant22' */

/* Gain to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUAOfs_C;/* Referenced by: '<Root>/Constant23' */

/* Offset to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUBFilTiCon_C;/* Referenced by: '<Root>/Constant39' */

/* Low pass filter time constant for signal input processing */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUBGain_C;/* Referenced by: '<Root>/Constant20' */

/* Gain to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUBOfs_C;/* Referenced by: '<Root>/Constant21' */

/* Offset to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUCFilTiCon_C;/* Referenced by: '<Root>/Constant41' */

/* Low pass filter time constant for signal input processing */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUCGain_C;/* Referenced by: '<Root>/Constant24' */

/* Gain to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T PhaUCOfs_C;/* Referenced by: '<Root>/Constant25' */

/* Offset to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T ResolverCosFilTiCon_C;/* Referenced by: '<Root>/Constant51' */

/* Low pass filter time constant for signal input processing */
extern __attribute__ ((section (".cal_data"))) real32_T ResolverCosGain_C;/* Referenced by: '<Root>/Constant52' */

/* Gain to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T ResolverCosOfs_C;/* Referenced by: '<Root>/Constant53' */

/* Offset to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) boolean_T ResolverSinCosDialEna_C;/* Referenced by: '<Root>/Constant42' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T
  ResolverSinCosDialVal_CA[2];         /* Referenced by: '<Root>/Constant43' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T ResolverSinFilTiCon_C;/* Referenced by: '<Root>/Constant45' */

/* Low pass filter time constant for signal input processing */
extern __attribute__ ((section (".cal_data"))) real32_T ResolverSinGain_C;/* Referenced by: '<Root>/Constant46' */

/* Gain to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T ResolverSinOfs_C;/* Referenced by: '<Root>/Constant47' */

/* Offset to convert raw input to engineering units */
#ifndef ADCINP_MDLREF_HIDE_CHILD_

extern MdlrefDW_ADCINP_T ADCINP_MdlrefDW;

#endif                                 /*ADCINP_MDLREF_HIDE_CHILD_*/

#ifndef ADCINP_MDLREF_HIDE_CHILD_

/* Block states (default storage) */
extern DW_ADCINP_f_T ADCINP_DW;

#endif                                 /*ADCINP_MDLREF_HIDE_CHILD_*/

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'ADCINP'
 * '<S1>'   : 'ADCINP/LowPassFilter'
 * '<S2>'   : 'ADCINP/LowPassFilter1'
 * '<S3>'   : 'ADCINP/LowPassFilter2'
 * '<S4>'   : 'ADCINP/LowPassFilter3'
 * '<S5>'   : 'ADCINP/LowPassFilter4'
 * '<S6>'   : 'ADCINP/LowPassFilter5'
 * '<S7>'   : 'ADCINP/LowPassFilter6'
 * '<S8>'   : 'ADCINP/LowPassFilter7'
 * '<S9>'   : 'ADCINP/LowPassFilter8'
 * '<S10>'  : 'ADCINP/LowPassFilter9'
 * '<S11>'  : 'ADCINP/Model Info'
 */
#endif                                 /* RTW_HEADER_ADCINP_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
