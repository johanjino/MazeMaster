/*
 * x2WControl.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "x2WControl".
 *
 * Model version              : 1.9
 * Simulink Coder version : 9.9 (R2023a) 19-Nov-2022
 * C source code generated on : Mon May 29 16:02:07 2023
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objective: Debugging
 * Validation result: Not run
 */

#ifndef RTW_HEADER_x2WControl_h_
#define RTW_HEADER_x2WControl_h_
#ifndef x2WControl_COMMON_INCLUDES_
#define x2WControl_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#include "nesl_rtw.h"
#include "x2WControl_a151ee3d_1_gateway.h"
#endif                                 /* x2WControl_COMMON_INCLUDES_ */

#include "x2WControl_types.h"
#include <float.h>
#include <string.h>
#include <stddef.h>
#include "rt_nonfinite.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContStateDisabled
#define rtmGetContStateDisabled(rtm)   ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
#define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
#define rtmGetContStates(rtm)          ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
#define rtmSetContStates(rtm, val)     ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
#define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
#define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetIntgData
#define rtmGetIntgData(rtm)            ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
#define rtmSetIntgData(rtm, val)       ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
#define rtmGetOdeF(rtm)                ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
#define rtmSetOdeF(rtm, val)           ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
#define rtmGetOdeY(rtm)                ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
#define rtmSetOdeY(rtm, val)           ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
#define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
#define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
#define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
#define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetRTWLogInfo
#define rtmGetRTWLogInfo(rtm)          ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetZCCacheNeedsReset
#define rtmGetZCCacheNeedsReset(rtm)   ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
#define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
#define rtmGetdX(rtm)                  ((rtm)->derivs)
#endif

#ifndef rtmSetdX
#define rtmSetdX(rtm, val)             ((rtm)->derivs = (val))
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T STATE_1[4];                   /* '<S60>/STATE_1' */
  real_T OUTPUT_1_0;                   /* '<S60>/OUTPUT_1_0' */
  real_T Gain;                         /* '<Root>/Gain' */
  real_T Step;                         /* '<Root>/Step' */
  real_T Sum;                          /* '<Root>/Sum' */
  real_T DerivativeGain;               /* '<S35>/Derivative Gain' */
  real_T Filter;                       /* '<S36>/Filter' */
  real_T SumD;                         /* '<S36>/SumD' */
  real_T IntegralGain;                 /* '<S38>/Integral Gain' */
  real_T Integrator;                   /* '<S41>/Integrator' */
  real_T FilterCoefficient;            /* '<S44>/Filter Coefficient' */
  real_T ProportionalGain;             /* '<S46>/Proportional Gain' */
  real_T Sum_k;                        /* '<S50>/Sum' */
  real_T INPUT_1_1_1[4];               /* '<S60>/INPUT_1_1_1' */
} B_x2WControl_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T INPUT_1_1_1_Discrete;         /* '<S60>/INPUT_1_1_1' */
  real_T INPUT_1_1_1_FirstOutput;      /* '<S60>/INPUT_1_1_1' */
  real_T STATE_1_Discrete;             /* '<S60>/STATE_1' */
  real_T OUTPUT_1_0_Discrete;          /* '<S60>/OUTPUT_1_0' */
  void* STATE_1_Simulator;             /* '<S60>/STATE_1' */
  void* STATE_1_SimData;               /* '<S60>/STATE_1' */
  void* STATE_1_DiagMgr;               /* '<S60>/STATE_1' */
  void* STATE_1_ZcLogger;              /* '<S60>/STATE_1' */
  void* STATE_1_TsInfo;                /* '<S60>/STATE_1' */
  void* OUTPUT_1_0_Simulator;          /* '<S60>/OUTPUT_1_0' */
  void* OUTPUT_1_0_SimData;            /* '<S60>/OUTPUT_1_0' */
  void* OUTPUT_1_0_DiagMgr;            /* '<S60>/OUTPUT_1_0' */
  void* OUTPUT_1_0_ZcLogger;           /* '<S60>/OUTPUT_1_0' */
  void* OUTPUT_1_0_TsInfo;             /* '<S60>/OUTPUT_1_0' */
  void* SINK_1_RtwLogger;              /* '<S60>/SINK_1' */
  void* SINK_1_RtwLogBuffer;           /* '<S60>/SINK_1' */
  void* SINK_1_RtwLogFcnManager;       /* '<S60>/SINK_1' */
  int_T STATE_1_Modes;                 /* '<S60>/STATE_1' */
  int_T OUTPUT_1_0_Modes;              /* '<S60>/OUTPUT_1_0' */
  boolean_T STATE_1_FirstOutput;       /* '<S60>/STATE_1' */
  boolean_T OUTPUT_1_0_FirstOutput;    /* '<S60>/OUTPUT_1_0' */
} DW_x2WControl_T;

/* Continuous states (default storage) */
typedef struct {
  real_T x2WControlPrismatic_Joint1Pzp[4];/* '<S60>/STATE_1' */
  real_T Filter_CSTATE;                /* '<S36>/Filter' */
  real_T Integrator_CSTATE;            /* '<S41>/Integrator' */
  real_T x2WControlSimulink_PS_Converter[2];/* '<S60>/INPUT_1_1_1' */
} X_x2WControl_T;

/* State derivatives (default storage) */
typedef struct {
  real_T x2WControlPrismatic_Joint1Pzp[4];/* '<S60>/STATE_1' */
  real_T Filter_CSTATE;                /* '<S36>/Filter' */
  real_T Integrator_CSTATE;            /* '<S41>/Integrator' */
  real_T x2WControlSimulink_PS_Converter[2];/* '<S60>/INPUT_1_1_1' */
} XDot_x2WControl_T;

/* State disabled  */
typedef struct {
  boolean_T x2WControlPrismatic_Joint1Pzp[4];/* '<S60>/STATE_1' */
  boolean_T Filter_CSTATE;             /* '<S36>/Filter' */
  boolean_T Integrator_CSTATE;         /* '<S41>/Integrator' */
  boolean_T x2WControlSimulink_PS_Converter[2];/* '<S60>/INPUT_1_1_1' */
} XDis_x2WControl_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Parameters (default storage) */
struct P_x2WControl_T_ {
  real_T PIDController_D;              /* Mask Parameter: PIDController_D
                                        * Referenced by: '<S35>/Derivative Gain'
                                        */
  real_T PIDController_I;              /* Mask Parameter: PIDController_I
                                        * Referenced by: '<S38>/Integral Gain'
                                        */
  real_T PIDController_InitialConditionF;
                              /* Mask Parameter: PIDController_InitialConditionF
                               * Referenced by: '<S36>/Filter'
                               */
  real_T PIDController_InitialConditio_m;
                              /* Mask Parameter: PIDController_InitialConditio_m
                               * Referenced by: '<S41>/Integrator'
                               */
  real_T PIDController_N;              /* Mask Parameter: PIDController_N
                                        * Referenced by: '<S44>/Filter Coefficient'
                                        */
  real_T PIDController_P;              /* Mask Parameter: PIDController_P
                                        * Referenced by: '<S46>/Proportional Gain'
                                        */
  real_T Gain_Gain;                    /* Expression: 180/pi
                                        * Referenced by: '<Root>/Gain'
                                        */
  real_T Step_Time;                    /* Expression: 0.01
                                        * Referenced by: '<Root>/Step'
                                        */
  real_T Step_Y0;                      /* Expression: 50
                                        * Referenced by: '<Root>/Step'
                                        */
  real_T Step_YFinal;                  /* Expression: 0
                                        * Referenced by: '<Root>/Step'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_x2WControl_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;
  RTWSolverInfo solverInfo;
  X_x2WControl_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_x2WControl_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[8];
  real_T odeF[3][8];
  ODE3_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block parameters (default storage) */
extern P_x2WControl_T x2WControl_P;

/* Block signals (default storage) */
extern B_x2WControl_T x2WControl_B;

/* Continuous states (default storage) */
extern X_x2WControl_T x2WControl_X;

/* Block states (default storage) */
extern DW_x2WControl_T x2WControl_DW;

/* Model entry point functions */
extern void x2WControl_initialize(void);
extern void x2WControl_step(void);
extern void x2WControl_terminate(void);

/* Real-time Model object */
extern RT_MODEL_x2WControl_T *const x2WControl_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S58>/RESHAPE' : Reshape block reduction
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
 * '<Root>' : 'x2WControl'
 * '<S1>'   : 'x2WControl/Cart'
 * '<S2>'   : 'x2WControl/Chassis'
 * '<S3>'   : 'x2WControl/PID Controller'
 * '<S4>'   : 'x2WControl/PS-Simulink Converter1'
 * '<S5>'   : 'x2WControl/Simulink-PS Converter1'
 * '<S6>'   : 'x2WControl/Solver Configuration'
 * '<S7>'   : 'x2WControl/Cart/Left Wheel '
 * '<S8>'   : 'x2WControl/Cart/Right Wheel'
 * '<S9>'   : 'x2WControl/Chassis/Rods'
 * '<S10>'  : 'x2WControl/PID Controller/Anti-windup'
 * '<S11>'  : 'x2WControl/PID Controller/D Gain'
 * '<S12>'  : 'x2WControl/PID Controller/Filter'
 * '<S13>'  : 'x2WControl/PID Controller/Filter ICs'
 * '<S14>'  : 'x2WControl/PID Controller/I Gain'
 * '<S15>'  : 'x2WControl/PID Controller/Ideal P Gain'
 * '<S16>'  : 'x2WControl/PID Controller/Ideal P Gain Fdbk'
 * '<S17>'  : 'x2WControl/PID Controller/Integrator'
 * '<S18>'  : 'x2WControl/PID Controller/Integrator ICs'
 * '<S19>'  : 'x2WControl/PID Controller/N Copy'
 * '<S20>'  : 'x2WControl/PID Controller/N Gain'
 * '<S21>'  : 'x2WControl/PID Controller/P Copy'
 * '<S22>'  : 'x2WControl/PID Controller/Parallel P Gain'
 * '<S23>'  : 'x2WControl/PID Controller/Reset Signal'
 * '<S24>'  : 'x2WControl/PID Controller/Saturation'
 * '<S25>'  : 'x2WControl/PID Controller/Saturation Fdbk'
 * '<S26>'  : 'x2WControl/PID Controller/Sum'
 * '<S27>'  : 'x2WControl/PID Controller/Sum Fdbk'
 * '<S28>'  : 'x2WControl/PID Controller/Tracking Mode'
 * '<S29>'  : 'x2WControl/PID Controller/Tracking Mode Sum'
 * '<S30>'  : 'x2WControl/PID Controller/Tsamp - Integral'
 * '<S31>'  : 'x2WControl/PID Controller/Tsamp - Ngain'
 * '<S32>'  : 'x2WControl/PID Controller/postSat Signal'
 * '<S33>'  : 'x2WControl/PID Controller/preSat Signal'
 * '<S34>'  : 'x2WControl/PID Controller/Anti-windup/Passthrough'
 * '<S35>'  : 'x2WControl/PID Controller/D Gain/Internal Parameters'
 * '<S36>'  : 'x2WControl/PID Controller/Filter/Cont. Filter'
 * '<S37>'  : 'x2WControl/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S38>'  : 'x2WControl/PID Controller/I Gain/Internal Parameters'
 * '<S39>'  : 'x2WControl/PID Controller/Ideal P Gain/Passthrough'
 * '<S40>'  : 'x2WControl/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S41>'  : 'x2WControl/PID Controller/Integrator/Continuous'
 * '<S42>'  : 'x2WControl/PID Controller/Integrator ICs/Internal IC'
 * '<S43>'  : 'x2WControl/PID Controller/N Copy/Disabled'
 * '<S44>'  : 'x2WControl/PID Controller/N Gain/Internal Parameters'
 * '<S45>'  : 'x2WControl/PID Controller/P Copy/Disabled'
 * '<S46>'  : 'x2WControl/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S47>'  : 'x2WControl/PID Controller/Reset Signal/Disabled'
 * '<S48>'  : 'x2WControl/PID Controller/Saturation/Passthrough'
 * '<S49>'  : 'x2WControl/PID Controller/Saturation Fdbk/Disabled'
 * '<S50>'  : 'x2WControl/PID Controller/Sum/Sum_PID'
 * '<S51>'  : 'x2WControl/PID Controller/Sum Fdbk/Disabled'
 * '<S52>'  : 'x2WControl/PID Controller/Tracking Mode/Disabled'
 * '<S53>'  : 'x2WControl/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S54>'  : 'x2WControl/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S55>'  : 'x2WControl/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S56>'  : 'x2WControl/PID Controller/postSat Signal/Forward_Path'
 * '<S57>'  : 'x2WControl/PID Controller/preSat Signal/Forward_Path'
 * '<S58>'  : 'x2WControl/PS-Simulink Converter1/EVAL_KEY'
 * '<S59>'  : 'x2WControl/Simulink-PS Converter1/EVAL_KEY'
 * '<S60>'  : 'x2WControl/Solver Configuration/EVAL_KEY'
 */
#endif                                 /* RTW_HEADER_x2WControl_h_ */
