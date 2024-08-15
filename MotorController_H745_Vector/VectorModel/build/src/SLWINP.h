/*
 * File: SLWINP.h
 *
 * Code generated for Simulink model 'SLWINP'.
 *
 * Model version                  : 1.60
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Jul 15 12:12:21 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_SLWINP_h_
#define RTW_HEADER_SLWINP_h_
#ifndef SLWINP_COMMON_INCLUDES_
#define SLWINP_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* SLWINP_COMMON_INCLUDES_ */

#include "SLWINP_types.h"
#include "LowPassFilter_0O6LwJpz.h"
#include "Debounce_G4uuGAfd.h"

/* Block signals for model 'SLWINP' */
#ifndef SLWINP_MDLREF_HIDE_CHILD_

typedef struct {
  boolean_T Out;                       /* '<S2>/Debounce' */
  boolean_T Out_a;                     /* '<S1>/Debounce' */
} B_SLWINP_c_T;

#endif                                 /*SLWINP_MDLREF_HIDE_CHILD_*/

/* Block states (default storage) for model 'SLWINP' */
#ifndef SLWINP_MDLREF_HIDE_CHILD_

typedef struct {
  DW_LowPassFilter_0O6LwJpz_T LowPassFilter4;/* '<Root>/LowPassFilter4' */
  DW_LowPassFilter_0O6LwJpz_T LowPassFilter3;/* '<Root>/LowPassFilter3' */
  DW_LowPassFilter_0O6LwJpz_T LowPassFilter2;/* '<Root>/LowPassFilter2' */
  DW_LowPassFilter_0O6LwJpz_T LowPassFilter1;/* '<Root>/LowPassFilter1' */
  DW_LowPassFilter_0O6LwJpz_T LowPassFilter;/* '<Root>/LowPassFilter' */
  DW_Debounce_G4uuGAfd_T Debounce1;    /* '<Root>/Debounce1' */
  DW_Debounce_G4uuGAfd_T Debounce;     /* '<Root>/Debounce' */
} DW_SLWINP_f_T;

#endif                                 /*SLWINP_MDLREF_HIDE_CHILD_*/

#ifndef SLWINP_MDLREF_HIDE_CHILD_

/* Real-time Model Data Structure */
struct tag_RTM_SLWINP_T {
  const char_T **errorStatus;
};

#endif                                 /*SLWINP_MDLREF_HIDE_CHILD_*/

#ifndef SLWINP_MDLREF_HIDE_CHILD_

typedef struct {
  RT_MODEL_SLWINP_T rtm;
} MdlrefDW_SLWINP_T;

#endif                                 /*SLWINP_MDLREF_HIDE_CHILD_*/

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern boolean_T ASWIN_MaiPwrSts;      /* '<Root>/ASWIN_MaiPwrSts'
                                        * The raw input value
                                        */
extern boolean_T ASWIN_AuxPwrSts;      /* '<Root>/ASWIN_AuxPwrSts'
                                        * The raw input value
                                        */
extern uint16_T ASWIN_BdT1;            /* '<Root>/ASWIN_BdT1'
                                        * The raw ADC input value
                                        */
extern uint16_T ASWIN_BdT2;            /* '<Root>/ASWIN_BdT2'
                                        * The raw ADC input value
                                        */
extern uint16_T ASWIN_McuURef;         /* '<Root>/ASWIN_McuURef'
                                        * The raw ADC input value
                                        */
extern uint16_T ASWIN_McuT;            /* '<Root>/ASWIN_McuT'
                                        * The raw ADC input value
                                        */
extern uint16_T ASWIN_McuUBat;         /* '<Root>/ASWIN_McuUBat'
                                        * The raw ADC input value
                                        */
extern real32_T BdT1;                  /* '<Root>/Switch2'
                                        * Board temperature 1
                                        */
extern real32_T BdT2;                  /* '<Root>/Switch3'
                                        * Board temperature 2
                                        */
extern real32_T McuT;                  /* '<Root>/Switch5'
                                        * Microcontroller temperature
                                        */
extern real32_T McuURef;               /* '<Root>/LowPassFilter3'
                                        * Microcontroller voltage VREFINT
                                        */
extern real32_T McuUBat;               /* '<Root>/LowPassFilter4'
                                        * Microcontroller voltage VBAT
                                        */
extern boolean_T MaiPwrAcv;            /* '<Root>/Switch4'
                                        * Main power active flag
                                        */
extern boolean_T AuxPwrAcv;            /* '<Root>/Switch1'
                                        * Auxilary power active flag
                                        */
extern void SLWINP_Init(void);
extern void SLWINP(void);

/* Model reference registration function */
extern void SLWINP_initialize(const char_T **rt_errorStatus);

/* Exported data declaration */

/* Calibration memory section */
/* Declaration for custom storage class: Calibration */
extern __attribute__ ((section (".cal_data"))) real32_T AuxPwrAcvDebFall_C;/* Referenced by: '<Root>/Constant8' */

/* Falling edge debounce time for input processing */
extern __attribute__ ((section (".cal_data"))) real32_T AuxPwrAcvDebRisng_C;/* Referenced by: '<Root>/Constant5' */

/* Rising edge debounce time for input processing */
extern __attribute__ ((section (".cal_data"))) boolean_T AuxPwrAcvDialEna_C;/* Referenced by: '<Root>/Constant6' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) boolean_T AuxPwrAcvDialVal_C;/* Referenced by: '<Root>/Constant7' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) boolean_T AuxPwrStsIvt_C;/* Referenced by: '<Root>/Constant4' */

/* Invert the auxilary power status input */
extern __attribute__ ((section (".cal_data"))) boolean_T BdT1DialEna_C;/* Referenced by: '<Root>/Constant10' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T BdT1DialVal_C;/* Referenced by: '<Root>/Constant11' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T BdT1FilTiCon_C;/* Referenced by: '<Root>/Constant13' */

/* Low pass filter time constant for signal input processing */
extern __attribute__ ((section (".cal_data"))) real32_T BdT1Gain_C;/* Referenced by: '<Root>/Constant22' */

/* Gain to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T BdT1Ofs_C;/* Referenced by: '<Root>/Constant23' */

/* Offset to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) boolean_T BdT2DialEna_C;/* Referenced by: '<Root>/Constant14' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T BdT2DialVal_C;/* Referenced by: '<Root>/Constant15' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T BdT2FilTiCon_C;/* Referenced by: '<Root>/Constant19' */

/* Low pass filter time constant for signal input processing */
extern __attribute__ ((section (".cal_data"))) real32_T BdT2Gain_C;/* Referenced by: '<Root>/Constant20' */

/* Gain to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T BdT2Ofs_C;/* Referenced by: '<Root>/Constant21' */

/* Offset to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T MaiPwrAcvDebFall_C;/* Referenced by: '<Root>/Constant2' */

/* Falling edge debounce time for input processing */
extern __attribute__ ((section (".cal_data"))) real32_T MaiPwrAcvDebRisng_C;/* Referenced by: '<Root>/Constant1' */

/* Rising edge debounce time for input processing */
extern __attribute__ ((section (".cal_data"))) boolean_T MaiPwrAcvDialEna_C;/* Referenced by: '<Root>/Constant16' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) boolean_T MaiPwrAcvDialVal_C;/* Referenced by: '<Root>/Constant17' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) boolean_T MaiPwrStsIvt_C;/* Referenced by: '<Root>/Constant' */

/* Invert the main power status input */
extern __attribute__ ((section (".cal_data"))) boolean_T McuTDialEna_C;/* Referenced by: '<Root>/Constant24' */

/* Signal override enable */
extern __attribute__ ((section (".cal_data"))) real32_T McuTDialVal_C;/* Referenced by: '<Root>/Constant25' */

/* Signal override value */
extern __attribute__ ((section (".cal_data"))) real32_T McuTFilTiCon_C;/* Referenced by: '<Root>/Constant27' */

/* Low pass filter time constant for signal input processing */
extern __attribute__ ((section (".cal_data"))) real32_T McuTGain_C;/* Referenced by: '<Root>/Constant28' */

/* Gain to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T McuTOfs_C;/* Referenced by: '<Root>/Constant29' */

/* Offset to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T McuUBatFilTiCon_C;/* Referenced by: '<Root>/Constant35' */

/* Low pass filter time constant for signal input processing */
extern __attribute__ ((section (".cal_data"))) real32_T McuUBatGain_C;/* Referenced by: '<Root>/Constant36' */

/* Gain to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T McuUBatOfs_C;/* Referenced by: '<Root>/Constant37' */

/* Offset to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T McuURefFilTiCon_C;/* Referenced by: '<Root>/Constant31' */

/* Low pass filter time constant for signal input processing */
extern __attribute__ ((section (".cal_data"))) real32_T McuURefGain_C;/* Referenced by: '<Root>/Constant32' */

/* Gain to convert raw input to engineering units */
extern __attribute__ ((section (".cal_data"))) real32_T McuURefOfs_C;/* Referenced by: '<Root>/Constant33' */

/* Offset to convert raw input to engineering units */
#ifndef SLWINP_MDLREF_HIDE_CHILD_

extern MdlrefDW_SLWINP_T SLWINP_MdlrefDW;

#endif                                 /*SLWINP_MDLREF_HIDE_CHILD_*/

#ifndef SLWINP_MDLREF_HIDE_CHILD_

/* Block signals (default storage) */
extern B_SLWINP_c_T SLWINP_B;

/* Block states (default storage) */
extern DW_SLWINP_f_T SLWINP_DW;

#endif                                 /*SLWINP_MDLREF_HIDE_CHILD_*/

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<Root>/Data Type Conversion1' : Eliminate redundant data type conversion
 * Block '<Root>/Data Type Conversion2' : Eliminate redundant data type conversion
 */

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
 * '<Root>' : 'SLWINP'
 * '<S1>'   : 'SLWINP/Debounce'
 * '<S2>'   : 'SLWINP/Debounce1'
 * '<S3>'   : 'SLWINP/LowPassFilter'
 * '<S4>'   : 'SLWINP/LowPassFilter1'
 * '<S5>'   : 'SLWINP/LowPassFilter2'
 * '<S6>'   : 'SLWINP/LowPassFilter3'
 * '<S7>'   : 'SLWINP/LowPassFilter4'
 * '<S8>'   : 'SLWINP/Model Info'
 * '<S9>'   : 'SLWINP/Debounce/Debounce'
 * '<S10>'  : 'SLWINP/Debounce1/Debounce'
 */
#endif                                 /* RTW_HEADER_SLWINP_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
