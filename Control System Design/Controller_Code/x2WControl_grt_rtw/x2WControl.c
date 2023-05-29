/*
 * x2WControl.c
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

#include "x2WControl.h"
#include "rtwtypes.h"
#include <stddef.h>
#include "x2WControl_private.h"
#include <string.h>
#include "rt_nonfinite.h"

/* Block signals (default storage) */
B_x2WControl_T x2WControl_B;

/* Continuous states */
X_x2WControl_T x2WControl_X;

/* Block states (default storage) */
DW_x2WControl_T x2WControl_DW;

/* Real-time model */
static RT_MODEL_x2WControl_T x2WControl_M_;
RT_MODEL_x2WControl_T *const x2WControl_M = &x2WControl_M_;

/* Projection for root system: '<Root>' */
void x2WControl_projection(void)
{
  NeslSimulationData *simulationData;
  NeslSimulator *simulator;
  NeuDiagnosticManager *diagnosticManager;
  NeuDiagnosticTree *diagnosticTree;
  char *msg;
  real_T tmp_0[4];
  real_T time;
  int32_T tmp_2;
  int_T tmp_1[2];
  boolean_T tmp;

  /* Projection for SimscapeExecutionBlock: '<S60>/STATE_1' */
  simulationData = (NeslSimulationData *)x2WControl_DW.STATE_1_SimData;
  time = x2WControl_M->Timing.t[0];
  simulationData->mData->mTime.mN = 1;
  simulationData->mData->mTime.mX = &time;
  simulationData->mData->mContStates.mN = 4;
  simulationData->mData->mContStates.mX =
    &x2WControl_X.x2WControlPrismatic_Joint1Pzp[0];
  simulationData->mData->mDiscStates.mN = 0;
  simulationData->mData->mDiscStates.mX = &x2WControl_DW.STATE_1_Discrete;
  simulationData->mData->mModeVector.mN = 0;
  simulationData->mData->mModeVector.mX = &x2WControl_DW.STATE_1_Modes;
  tmp = false;
  simulationData->mData->mFoundZcEvents = tmp;
  simulationData->mData->mIsMajorTimeStep = rtmIsMajorTimeStep(x2WControl_M);
  tmp = false;
  simulationData->mData->mIsSolverAssertCheck = tmp;
  simulationData->mData->mIsSolverCheckingCIC = false;
  tmp = rtsiIsSolverComputingJacobian(&x2WControl_M->solverInfo);
  simulationData->mData->mIsComputingJacobian = tmp;
  simulationData->mData->mIsEvaluatingF0 = false;
  simulationData->mData->mIsSolverRequestingReset = false;
  simulationData->mData->mIsModeUpdateTimeStep = rtsiIsModeUpdateTimeStep
    (&x2WControl_M->solverInfo);
  tmp_1[0] = 0;
  tmp_0[0] = x2WControl_B.INPUT_1_1_1[0];
  tmp_0[1] = x2WControl_B.INPUT_1_1_1[1];
  tmp_0[2] = x2WControl_B.INPUT_1_1_1[2];
  tmp_0[3] = x2WControl_B.INPUT_1_1_1[3];
  tmp_1[1] = 4;
  simulationData->mData->mInputValues.mN = 4;
  simulationData->mData->mInputValues.mX = &tmp_0[0];
  simulationData->mData->mInputOffsets.mN = 2;
  simulationData->mData->mInputOffsets.mX = &tmp_1[0];
  simulator = (NeslSimulator *)x2WControl_DW.STATE_1_Simulator;
  diagnosticManager = (NeuDiagnosticManager *)x2WControl_DW.STATE_1_DiagMgr;
  diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
  tmp_2 = ne_simulator_method(simulator, NESL_SIM_PROJECTION, simulationData,
    diagnosticManager);
  if (tmp_2 != 0) {
    tmp = error_buffer_is_empty(rtmGetErrorStatus(x2WControl_M));
    if (tmp) {
      msg = rtw_diagnostics_msg(diagnosticTree);
      rtmSetErrorStatus(x2WControl_M, msg);
    }
  }

  /* End of Projection for SimscapeExecutionBlock: '<S60>/STATE_1' */
}

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 8;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  x2WControl_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  x2WControl_step();
  x2WControl_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  x2WControl_step();
  x2WControl_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  x2WControl_step();
  x2WControl_projection();
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void x2WControl_step(void)
{
  if (rtmIsMajorTimeStep(x2WControl_M)) {
    /* set solver stop time */
    if (!(x2WControl_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&x2WControl_M->solverInfo,
                            ((x2WControl_M->Timing.clockTickH0 + 1) *
        x2WControl_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&x2WControl_M->solverInfo,
                            ((x2WControl_M->Timing.clockTick0 + 1) *
        x2WControl_M->Timing.stepSize0 + x2WControl_M->Timing.clockTickH0 *
        x2WControl_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(x2WControl_M)) {
    x2WControl_M->Timing.t[0] = rtsiGetT(&x2WControl_M->solverInfo);
  }

  {
    NeslSimulationData *simulationData;
    NeslSimulator *simulator;
    NeuDiagnosticManager *diagnosticManager;
    NeuDiagnosticTree *diagnosticTree;
    char *msg;
    real_T tmp_2[8];
    real_T tmp[4];
    real_T currentTime;
    real_T time;
    real_T time_0;
    real_T time_1;
    real_T time_2;
    int32_T tmp_1;
    int_T tmp_3[3];
    int_T tmp_0[2];
    boolean_T first_output;

    /* SimscapeExecutionBlock: '<S60>/STATE_1' */
    simulationData = (NeslSimulationData *)x2WControl_DW.STATE_1_SimData;
    time = x2WControl_M->Timing.t[0];
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time;
    simulationData->mData->mContStates.mN = 4;
    simulationData->mData->mContStates.mX =
      &x2WControl_X.x2WControlPrismatic_Joint1Pzp[0];
    simulationData->mData->mDiscStates.mN = 0;
    simulationData->mData->mDiscStates.mX = &x2WControl_DW.STATE_1_Discrete;
    simulationData->mData->mModeVector.mN = 0;
    simulationData->mData->mModeVector.mX = &x2WControl_DW.STATE_1_Modes;
    first_output = false;
    simulationData->mData->mFoundZcEvents = first_output;
    simulationData->mData->mIsMajorTimeStep = rtmIsMajorTimeStep(x2WControl_M);
    first_output = false;
    simulationData->mData->mIsSolverAssertCheck = first_output;
    simulationData->mData->mIsSolverCheckingCIC = false;
    first_output = rtsiIsSolverComputingJacobian(&x2WControl_M->solverInfo);
    simulationData->mData->mIsComputingJacobian = first_output;
    simulationData->mData->mIsEvaluatingF0 = false;
    simulationData->mData->mIsSolverRequestingReset = false;
    simulationData->mData->mIsModeUpdateTimeStep = rtsiIsModeUpdateTimeStep
      (&x2WControl_M->solverInfo);
    tmp_0[0] = 0;
    tmp[0] = x2WControl_B.INPUT_1_1_1[0];
    tmp[1] = x2WControl_B.INPUT_1_1_1[1];
    tmp[2] = x2WControl_B.INPUT_1_1_1[2];
    tmp[3] = x2WControl_B.INPUT_1_1_1[3];
    tmp_0[1] = 4;
    simulationData->mData->mInputValues.mN = 4;
    simulationData->mData->mInputValues.mX = &tmp[0];
    simulationData->mData->mInputOffsets.mN = 2;
    simulationData->mData->mInputOffsets.mX = &tmp_0[0];
    simulationData->mData->mOutputs.mN = 4;
    simulationData->mData->mOutputs.mX = &x2WControl_B.STATE_1[0];
    simulationData->mData->mTolerances.mN = 0;
    simulationData->mData->mTolerances.mX = NULL;
    simulationData->mData->mCstateHasChanged = false;
    time_0 = x2WControl_M->Timing.t[0];
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time_0;
    simulationData->mData->mSampleHits.mN = 0;
    simulationData->mData->mSampleHits.mX = NULL;
    simulationData->mData->mIsFundamentalSampleHit = false;
    simulator = (NeslSimulator *)x2WControl_DW.STATE_1_Simulator;
    diagnosticManager = (NeuDiagnosticManager *)x2WControl_DW.STATE_1_DiagMgr;
    diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    tmp_1 = ne_simulator_method(simulator, NESL_SIM_OUTPUTS, simulationData,
      diagnosticManager);
    if (tmp_1 != 0) {
      first_output = error_buffer_is_empty(rtmGetErrorStatus(x2WControl_M));
      if (first_output) {
        msg = rtw_diagnostics_msg(diagnosticTree);
        rtmSetErrorStatus(x2WControl_M, msg);
      }
    }

    /* End of SimscapeExecutionBlock: '<S60>/STATE_1' */

    /* SimscapeExecutionBlock: '<S60>/OUTPUT_1_0' */
    simulationData = (NeslSimulationData *)x2WControl_DW.OUTPUT_1_0_SimData;
    time_1 = x2WControl_M->Timing.t[0];
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time_1;
    simulationData->mData->mContStates.mN = 0;
    simulationData->mData->mContStates.mX = NULL;
    simulationData->mData->mDiscStates.mN = 0;
    simulationData->mData->mDiscStates.mX = &x2WControl_DW.OUTPUT_1_0_Discrete;
    simulationData->mData->mModeVector.mN = 0;
    simulationData->mData->mModeVector.mX = &x2WControl_DW.OUTPUT_1_0_Modes;
    first_output = false;
    simulationData->mData->mFoundZcEvents = first_output;
    simulationData->mData->mIsMajorTimeStep = rtmIsMajorTimeStep(x2WControl_M);
    first_output = false;
    simulationData->mData->mIsSolverAssertCheck = first_output;
    simulationData->mData->mIsSolverCheckingCIC = false;
    simulationData->mData->mIsComputingJacobian = false;
    simulationData->mData->mIsEvaluatingF0 = false;
    simulationData->mData->mIsSolverRequestingReset = false;
    simulationData->mData->mIsModeUpdateTimeStep = rtsiIsModeUpdateTimeStep
      (&x2WControl_M->solverInfo);
    tmp_3[0] = 0;
    tmp_2[0] = x2WControl_B.INPUT_1_1_1[0];
    tmp_2[1] = x2WControl_B.INPUT_1_1_1[1];
    tmp_2[2] = x2WControl_B.INPUT_1_1_1[2];
    tmp_2[3] = x2WControl_B.INPUT_1_1_1[3];
    tmp_3[1] = 4;
    tmp_2[4] = x2WControl_B.STATE_1[0];
    tmp_2[5] = x2WControl_B.STATE_1[1];
    tmp_2[6] = x2WControl_B.STATE_1[2];
    tmp_2[7] = x2WControl_B.STATE_1[3];
    tmp_3[2] = 8;
    simulationData->mData->mInputValues.mN = 8;
    simulationData->mData->mInputValues.mX = &tmp_2[0];
    simulationData->mData->mInputOffsets.mN = 3;
    simulationData->mData->mInputOffsets.mX = &tmp_3[0];
    simulationData->mData->mOutputs.mN = 1;

    /* SimscapeExecutionBlock: '<S60>/OUTPUT_1_0' */
    simulationData->mData->mOutputs.mX = &x2WControl_B.OUTPUT_1_0;

    /* SimscapeExecutionBlock: '<S60>/OUTPUT_1_0' */
    simulationData->mData->mTolerances.mN = 0;
    simulationData->mData->mTolerances.mX = NULL;
    simulationData->mData->mCstateHasChanged = false;
    time_2 = x2WControl_M->Timing.t[0];
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time_2;
    simulationData->mData->mSampleHits.mN = 0;
    simulationData->mData->mSampleHits.mX = NULL;
    simulationData->mData->mIsFundamentalSampleHit = false;
    simulator = (NeslSimulator *)x2WControl_DW.OUTPUT_1_0_Simulator;
    diagnosticManager = (NeuDiagnosticManager *)x2WControl_DW.OUTPUT_1_0_DiagMgr;
    diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    tmp_1 = ne_simulator_method(simulator, NESL_SIM_OUTPUTS, simulationData,
      diagnosticManager);
    if (tmp_1 != 0) {
      first_output = error_buffer_is_empty(rtmGetErrorStatus(x2WControl_M));
      if (first_output) {
        msg = rtw_diagnostics_msg(diagnosticTree);
        rtmSetErrorStatus(x2WControl_M, msg);
      }
    }

    /* Gain: '<Root>/Gain' */
    x2WControl_B.Gain = x2WControl_P.Gain_Gain * x2WControl_B.OUTPUT_1_0;
    if (rtmIsMajorTimeStep(x2WControl_M)) {
    }

    /* Step: '<Root>/Step' */
    currentTime = x2WControl_M->Timing.t[0];
    if (currentTime < x2WControl_P.Step_Time) {
      /* Step: '<Root>/Step' */
      x2WControl_B.Step = x2WControl_P.Step_Y0;
    } else {
      /* Step: '<Root>/Step' */
      x2WControl_B.Step = x2WControl_P.Step_YFinal;
    }

    /* End of Step: '<Root>/Step' */
    if (rtmIsMajorTimeStep(x2WControl_M)) {
    }

    /* Sum: '<Root>/Sum' */
    x2WControl_B.Sum = x2WControl_B.Step - x2WControl_B.Gain;

    /* Gain: '<S35>/Derivative Gain' */
    x2WControl_B.DerivativeGain = x2WControl_P.PIDController_D *
      x2WControl_B.Sum;

    /* Integrator: '<S36>/Filter' */
    x2WControl_B.Filter = x2WControl_X.Filter_CSTATE;

    /* Sum: '<S36>/SumD' */
    x2WControl_B.SumD = x2WControl_B.DerivativeGain - x2WControl_B.Filter;

    /* Gain: '<S38>/Integral Gain' */
    x2WControl_B.IntegralGain = x2WControl_P.PIDController_I * x2WControl_B.Sum;

    /* Integrator: '<S41>/Integrator' */
    x2WControl_B.Integrator = x2WControl_X.Integrator_CSTATE;

    /* Gain: '<S44>/Filter Coefficient' */
    x2WControl_B.FilterCoefficient = x2WControl_P.PIDController_N *
      x2WControl_B.SumD;

    /* Gain: '<S46>/Proportional Gain' */
    x2WControl_B.ProportionalGain = x2WControl_P.PIDController_P *
      x2WControl_B.Sum;

    /* Sum: '<S50>/Sum' */
    x2WControl_B.Sum_k = (x2WControl_B.ProportionalGain +
                          x2WControl_B.Integrator) +
      x2WControl_B.FilterCoefficient;

    /* SimscapeInputBlock: '<S60>/INPUT_1_1_1' */
    if (x2WControl_DW.INPUT_1_1_1_FirstOutput == 0.0) {
      x2WControl_DW.INPUT_1_1_1_FirstOutput = 1.0;
      x2WControl_X.x2WControlSimulink_PS_Converter[0] = x2WControl_B.Sum_k;
      x2WControl_X.x2WControlSimulink_PS_Converter[1] = 0.0;
    }

    x2WControl_B.INPUT_1_1_1[0] = x2WControl_X.x2WControlSimulink_PS_Converter[0];
    x2WControl_B.INPUT_1_1_1[1] = x2WControl_X.x2WControlSimulink_PS_Converter[1];
    x2WControl_B.INPUT_1_1_1[2] = ((x2WControl_B.Sum_k -
      x2WControl_X.x2WControlSimulink_PS_Converter[0]) * 1000.0 - 2.0 *
      x2WControl_X.x2WControlSimulink_PS_Converter[1]) * 1000.0;
    x2WControl_B.INPUT_1_1_1[3] = 0.0;

    /* End of SimscapeInputBlock: '<S60>/INPUT_1_1_1' */
  }

  if (rtmIsMajorTimeStep(x2WControl_M)) {
    /* Matfile logging */
    rt_UpdateTXYLogVars(x2WControl_M->rtwLogInfo, (x2WControl_M->Timing.t));
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(x2WControl_M)) {
    NeslSimulationData *simulationData;
    NeslSimulator *simulator;
    NeuDiagnosticManager *diagnosticManager;
    NeuDiagnosticTree *diagnosticTree;
    char *msg;
    real_T tmp_0[4];
    real_T time;
    int32_T tmp_2;
    int_T tmp_1[2];
    boolean_T tmp;

    /* Update for SimscapeExecutionBlock: '<S60>/STATE_1' */
    simulationData = (NeslSimulationData *)x2WControl_DW.STATE_1_SimData;
    time = x2WControl_M->Timing.t[0];
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time;
    simulationData->mData->mContStates.mN = 4;
    simulationData->mData->mContStates.mX =
      &x2WControl_X.x2WControlPrismatic_Joint1Pzp[0];
    simulationData->mData->mDiscStates.mN = 0;
    simulationData->mData->mDiscStates.mX = &x2WControl_DW.STATE_1_Discrete;
    simulationData->mData->mModeVector.mN = 0;
    simulationData->mData->mModeVector.mX = &x2WControl_DW.STATE_1_Modes;
    tmp = false;
    simulationData->mData->mFoundZcEvents = tmp;
    simulationData->mData->mIsMajorTimeStep = rtmIsMajorTimeStep(x2WControl_M);
    tmp = false;
    simulationData->mData->mIsSolverAssertCheck = tmp;
    simulationData->mData->mIsSolverCheckingCIC = false;
    tmp = rtsiIsSolverComputingJacobian(&x2WControl_M->solverInfo);
    simulationData->mData->mIsComputingJacobian = tmp;
    simulationData->mData->mIsEvaluatingF0 = false;
    simulationData->mData->mIsSolverRequestingReset = false;
    simulationData->mData->mIsModeUpdateTimeStep = rtsiIsModeUpdateTimeStep
      (&x2WControl_M->solverInfo);
    tmp_1[0] = 0;
    tmp_0[0] = x2WControl_B.INPUT_1_1_1[0];
    tmp_0[1] = x2WControl_B.INPUT_1_1_1[1];
    tmp_0[2] = x2WControl_B.INPUT_1_1_1[2];
    tmp_0[3] = x2WControl_B.INPUT_1_1_1[3];
    tmp_1[1] = 4;
    simulationData->mData->mInputValues.mN = 4;
    simulationData->mData->mInputValues.mX = &tmp_0[0];
    simulationData->mData->mInputOffsets.mN = 2;
    simulationData->mData->mInputOffsets.mX = &tmp_1[0];
    simulator = (NeslSimulator *)x2WControl_DW.STATE_1_Simulator;
    diagnosticManager = (NeuDiagnosticManager *)x2WControl_DW.STATE_1_DiagMgr;
    diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    tmp_2 = ne_simulator_method(simulator, NESL_SIM_UPDATE, simulationData,
      diagnosticManager);
    if (tmp_2 != 0) {
      tmp = error_buffer_is_empty(rtmGetErrorStatus(x2WControl_M));
      if (tmp) {
        msg = rtw_diagnostics_msg(diagnosticTree);
        rtmSetErrorStatus(x2WControl_M, msg);
      }
    }

    /* End of Update for SimscapeExecutionBlock: '<S60>/STATE_1' */
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(x2WControl_M)) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal(x2WControl_M)!=-1) &&
          !((rtmGetTFinal(x2WControl_M)-(((x2WControl_M->Timing.clockTick1+
               x2WControl_M->Timing.clockTickH1* 4294967296.0)) * 0.2)) >
            (((x2WControl_M->Timing.clockTick1+x2WControl_M->Timing.clockTickH1*
               4294967296.0)) * 0.2) * (DBL_EPSILON))) {
        rtmSetErrorStatus(x2WControl_M, "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&x2WControl_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++x2WControl_M->Timing.clockTick0)) {
      ++x2WControl_M->Timing.clockTickH0;
    }

    x2WControl_M->Timing.t[0] = rtsiGetSolverStopTime(&x2WControl_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.2s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.2, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      x2WControl_M->Timing.clockTick1++;
      if (!x2WControl_M->Timing.clockTick1) {
        x2WControl_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void x2WControl_derivatives(void)
{
  NeslSimulationData *simulationData;
  NeslSimulator *simulator;
  NeuDiagnosticManager *diagnosticManager;
  NeuDiagnosticTree *diagnosticTree;
  XDot_x2WControl_T *_rtXdot;
  char *msg;
  real_T tmp_0[4];
  real_T time;
  int32_T tmp_2;
  int_T tmp_1[2];
  boolean_T tmp;
  _rtXdot = ((XDot_x2WControl_T *) x2WControl_M->derivs);

  /* Derivatives for SimscapeExecutionBlock: '<S60>/STATE_1' */
  simulationData = (NeslSimulationData *)x2WControl_DW.STATE_1_SimData;
  time = x2WControl_M->Timing.t[0];
  simulationData->mData->mTime.mN = 1;
  simulationData->mData->mTime.mX = &time;
  simulationData->mData->mContStates.mN = 4;
  simulationData->mData->mContStates.mX =
    &x2WControl_X.x2WControlPrismatic_Joint1Pzp[0];
  simulationData->mData->mDiscStates.mN = 0;
  simulationData->mData->mDiscStates.mX = &x2WControl_DW.STATE_1_Discrete;
  simulationData->mData->mModeVector.mN = 0;
  simulationData->mData->mModeVector.mX = &x2WControl_DW.STATE_1_Modes;
  tmp = false;
  simulationData->mData->mFoundZcEvents = tmp;
  simulationData->mData->mIsMajorTimeStep = rtmIsMajorTimeStep(x2WControl_M);
  tmp = false;
  simulationData->mData->mIsSolverAssertCheck = tmp;
  simulationData->mData->mIsSolverCheckingCIC = false;
  tmp = rtsiIsSolverComputingJacobian(&x2WControl_M->solverInfo);
  simulationData->mData->mIsComputingJacobian = tmp;
  simulationData->mData->mIsEvaluatingF0 = false;
  simulationData->mData->mIsSolverRequestingReset = false;
  simulationData->mData->mIsModeUpdateTimeStep = rtsiIsModeUpdateTimeStep
    (&x2WControl_M->solverInfo);
  tmp_1[0] = 0;
  tmp_0[0] = x2WControl_B.INPUT_1_1_1[0];
  tmp_0[1] = x2WControl_B.INPUT_1_1_1[1];
  tmp_0[2] = x2WControl_B.INPUT_1_1_1[2];
  tmp_0[3] = x2WControl_B.INPUT_1_1_1[3];
  tmp_1[1] = 4;
  simulationData->mData->mInputValues.mN = 4;
  simulationData->mData->mInputValues.mX = &tmp_0[0];
  simulationData->mData->mInputOffsets.mN = 2;
  simulationData->mData->mInputOffsets.mX = &tmp_1[0];
  simulationData->mData->mDx.mN = 4;
  simulationData->mData->mDx.mX = &_rtXdot->x2WControlPrismatic_Joint1Pzp[0];
  simulator = (NeslSimulator *)x2WControl_DW.STATE_1_Simulator;
  diagnosticManager = (NeuDiagnosticManager *)x2WControl_DW.STATE_1_DiagMgr;
  diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
  tmp_2 = ne_simulator_method(simulator, NESL_SIM_DERIVATIVES, simulationData,
    diagnosticManager);
  if (tmp_2 != 0) {
    tmp = error_buffer_is_empty(rtmGetErrorStatus(x2WControl_M));
    if (tmp) {
      msg = rtw_diagnostics_msg(diagnosticTree);
      rtmSetErrorStatus(x2WControl_M, msg);
    }
  }

  /* End of Derivatives for SimscapeExecutionBlock: '<S60>/STATE_1' */

  /* Derivatives for Integrator: '<S36>/Filter' */
  _rtXdot->Filter_CSTATE = x2WControl_B.FilterCoefficient;

  /* Derivatives for Integrator: '<S41>/Integrator' */
  _rtXdot->Integrator_CSTATE = x2WControl_B.IntegralGain;

  /* Derivatives for SimscapeInputBlock: '<S60>/INPUT_1_1_1' */
  _rtXdot->x2WControlSimulink_PS_Converter[0] =
    x2WControl_X.x2WControlSimulink_PS_Converter[1];
  _rtXdot->x2WControlSimulink_PS_Converter[1] = ((x2WControl_B.Sum_k -
    x2WControl_X.x2WControlSimulink_PS_Converter[0]) * 1000.0 - 2.0 *
    x2WControl_X.x2WControlSimulink_PS_Converter[1]) * 1000.0;
}

/* Model initialize function */
void x2WControl_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)x2WControl_M, 0,
                sizeof(RT_MODEL_x2WControl_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&x2WControl_M->solverInfo,
                          &x2WControl_M->Timing.simTimeStep);
    rtsiSetTPtr(&x2WControl_M->solverInfo, &rtmGetTPtr(x2WControl_M));
    rtsiSetStepSizePtr(&x2WControl_M->solverInfo,
                       &x2WControl_M->Timing.stepSize0);
    rtsiSetdXPtr(&x2WControl_M->solverInfo, &x2WControl_M->derivs);
    rtsiSetContStatesPtr(&x2WControl_M->solverInfo, (real_T **)
                         &x2WControl_M->contStates);
    rtsiSetNumContStatesPtr(&x2WControl_M->solverInfo,
      &x2WControl_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&x2WControl_M->solverInfo,
      &x2WControl_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&x2WControl_M->solverInfo,
      &x2WControl_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&x2WControl_M->solverInfo,
      &x2WControl_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&x2WControl_M->solverInfo, (&rtmGetErrorStatus
      (x2WControl_M)));
    rtsiSetRTModelPtr(&x2WControl_M->solverInfo, x2WControl_M);
  }

  rtsiSetSimTimeStep(&x2WControl_M->solverInfo, MAJOR_TIME_STEP);
  x2WControl_M->intgData.y = x2WControl_M->odeY;
  x2WControl_M->intgData.f[0] = x2WControl_M->odeF[0];
  x2WControl_M->intgData.f[1] = x2WControl_M->odeF[1];
  x2WControl_M->intgData.f[2] = x2WControl_M->odeF[2];
  x2WControl_M->contStates = ((X_x2WControl_T *) &x2WControl_X);
  rtsiSetSolverData(&x2WControl_M->solverInfo, (void *)&x2WControl_M->intgData);
  rtsiSetIsMinorTimeStepWithModeChange(&x2WControl_M->solverInfo, false);
  rtsiSetSolverName(&x2WControl_M->solverInfo,"ode3");
  rtmSetTPtr(x2WControl_M, &x2WControl_M->Timing.tArray[0]);
  rtmSetTFinal(x2WControl_M, 10.0);
  x2WControl_M->Timing.stepSize0 = 0.2;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (NULL);
    x2WControl_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(x2WControl_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(x2WControl_M->rtwLogInfo, (NULL));
    rtliSetLogT(x2WControl_M->rtwLogInfo, "tout");
    rtliSetLogX(x2WControl_M->rtwLogInfo, "");
    rtliSetLogXFinal(x2WControl_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(x2WControl_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(x2WControl_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(x2WControl_M->rtwLogInfo, 10000);
    rtliSetLogDecimation(x2WControl_M->rtwLogInfo, 1);
    rtliSetLogY(x2WControl_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(x2WControl_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(x2WControl_M->rtwLogInfo, (NULL));
  }

  /* block I/O */
  (void) memset(((void *) &x2WControl_B), 0,
                sizeof(B_x2WControl_T));

  /* states (continuous) */
  {
    (void) memset((void *)&x2WControl_X, 0,
                  sizeof(X_x2WControl_T));
  }

  /* states (dwork) */
  (void) memset((void *)&x2WControl_DW, 0,
                sizeof(DW_x2WControl_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(x2WControl_M->rtwLogInfo, 0.0, rtmGetTFinal
    (x2WControl_M), x2WControl_M->Timing.stepSize0, (&rtmGetErrorStatus
    (x2WControl_M)));

  {
    NeModelParameters modelParameters;
    NeModelParameters modelParameters_0;
    NeslSimulationData *tmp;
    NeslSimulator *simulator;
    NeuDiagnosticManager *diagnosticManager;
    NeuDiagnosticTree *diagnosticTree;
    char *msg;
    real_T tmp_0;
    int32_T tmp_1;
    boolean_T zcDisabled;

    /* Start for SimscapeExecutionBlock: '<S60>/STATE_1' */
    simulator = nesl_lease_simulator("x2WControl/Solver Configuration_1", 0, 0);
    x2WControl_DW.STATE_1_Simulator = (void *)simulator;
    zcDisabled = pointer_is_null(x2WControl_DW.STATE_1_Simulator);
    if (zcDisabled) {
      x2WControl_a151ee3d_1_gateway();
      simulator = nesl_lease_simulator("x2WControl/Solver Configuration_1", 0, 0);
      x2WControl_DW.STATE_1_Simulator = (void *)simulator;
    }

    tmp = nesl_create_simulation_data();
    x2WControl_DW.STATE_1_SimData = (void *)tmp;
    diagnosticManager = rtw_create_diagnostics();
    x2WControl_DW.STATE_1_DiagMgr = (void *)diagnosticManager;
    modelParameters.mSolverType = NE_SOLVER_TYPE_DAE;
    modelParameters.mSolverAbsTol = 0.001;
    modelParameters.mSolverRelTol = 0.001;
    modelParameters.mSolverModifyAbsTol = NE_MODIFY_ABS_TOL_NO;
    modelParameters.mStartTime = 0.0;
    modelParameters.mLoadInitialState = false;
    modelParameters.mUseSimState = false;
    modelParameters.mLinTrimCompile = false;
    modelParameters.mLoggingMode = SSC_LOGGING_ON;
    modelParameters.mRTWModifiedTimeStamp = 6.07273323E+8;
    modelParameters.mUseModelRefSolver = false;
    tmp_0 = 0.001;
    modelParameters.mSolverTolerance = tmp_0;
    tmp_0 = 0.2;
    modelParameters.mFixedStepSize = tmp_0;
    zcDisabled = false;
    modelParameters.mVariableStepSolver = zcDisabled;
    zcDisabled = false;
    modelParameters.mIsUsingODEN = zcDisabled;
    modelParameters.mZcDisabled = true;
    simulator = (NeslSimulator *)x2WControl_DW.STATE_1_Simulator;
    diagnosticManager = (NeuDiagnosticManager *)x2WControl_DW.STATE_1_DiagMgr;
    diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    tmp_1 = nesl_initialize_simulator(simulator, &modelParameters,
      diagnosticManager);
    if (tmp_1 != 0) {
      zcDisabled = error_buffer_is_empty(rtmGetErrorStatus(x2WControl_M));
      if (zcDisabled) {
        msg = rtw_diagnostics_msg(diagnosticTree);
        rtmSetErrorStatus(x2WControl_M, msg);
      }
    }

    /* End of Start for SimscapeExecutionBlock: '<S60>/STATE_1' */

    /* Start for SimscapeExecutionBlock: '<S60>/OUTPUT_1_0' */
    simulator = nesl_lease_simulator("x2WControl/Solver Configuration_1", 1, 0);
    x2WControl_DW.OUTPUT_1_0_Simulator = (void *)simulator;
    zcDisabled = pointer_is_null(x2WControl_DW.OUTPUT_1_0_Simulator);
    if (zcDisabled) {
      x2WControl_a151ee3d_1_gateway();
      simulator = nesl_lease_simulator("x2WControl/Solver Configuration_1", 1, 0);
      x2WControl_DW.OUTPUT_1_0_Simulator = (void *)simulator;
    }

    tmp = nesl_create_simulation_data();
    x2WControl_DW.OUTPUT_1_0_SimData = (void *)tmp;
    diagnosticManager = rtw_create_diagnostics();
    x2WControl_DW.OUTPUT_1_0_DiagMgr = (void *)diagnosticManager;
    modelParameters_0.mSolverType = NE_SOLVER_TYPE_DAE;
    modelParameters_0.mSolverAbsTol = 0.001;
    modelParameters_0.mSolverRelTol = 0.001;
    modelParameters_0.mSolverModifyAbsTol = NE_MODIFY_ABS_TOL_NO;
    modelParameters_0.mStartTime = 0.0;
    modelParameters_0.mLoadInitialState = false;
    modelParameters_0.mUseSimState = false;
    modelParameters_0.mLinTrimCompile = false;
    modelParameters_0.mLoggingMode = SSC_LOGGING_ON;
    modelParameters_0.mRTWModifiedTimeStamp = 6.07273323E+8;
    modelParameters_0.mUseModelRefSolver = false;
    tmp_0 = 0.001;
    modelParameters_0.mSolverTolerance = tmp_0;
    tmp_0 = 0.2;
    modelParameters_0.mFixedStepSize = tmp_0;
    zcDisabled = false;
    modelParameters_0.mVariableStepSolver = zcDisabled;
    zcDisabled = false;
    modelParameters_0.mIsUsingODEN = zcDisabled;
    modelParameters_0.mZcDisabled = true;
    simulator = (NeslSimulator *)x2WControl_DW.OUTPUT_1_0_Simulator;
    diagnosticManager = (NeuDiagnosticManager *)x2WControl_DW.OUTPUT_1_0_DiagMgr;
    diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    tmp_1 = nesl_initialize_simulator(simulator, &modelParameters_0,
      diagnosticManager);
    if (tmp_1 != 0) {
      zcDisabled = error_buffer_is_empty(rtmGetErrorStatus(x2WControl_M));
      if (zcDisabled) {
        msg = rtw_diagnostics_msg(diagnosticTree);
        rtmSetErrorStatus(x2WControl_M, msg);
      }
    }

    /* End of Start for SimscapeExecutionBlock: '<S60>/OUTPUT_1_0' */
  }

  /* InitializeConditions for Integrator: '<S36>/Filter' */
  x2WControl_X.Filter_CSTATE = x2WControl_P.PIDController_InitialConditionF;

  /* InitializeConditions for Integrator: '<S41>/Integrator' */
  x2WControl_X.Integrator_CSTATE = x2WControl_P.PIDController_InitialConditio_m;
}

/* Model terminate function */
void x2WControl_terminate(void)
{
  NeslSimulationData *simulationData;
  NeuDiagnosticManager *diagnosticManager;

  /* Terminate for SimscapeExecutionBlock: '<S60>/STATE_1' */
  diagnosticManager = (NeuDiagnosticManager *)x2WControl_DW.STATE_1_DiagMgr;
  neu_destroy_diagnostic_manager(diagnosticManager);
  simulationData = (NeslSimulationData *)x2WControl_DW.STATE_1_SimData;
  nesl_destroy_simulation_data(simulationData);
  nesl_erase_simulator("x2WControl/Solver Configuration_1");
  nesl_destroy_registry();

  /* Terminate for SimscapeExecutionBlock: '<S60>/OUTPUT_1_0' */
  diagnosticManager = (NeuDiagnosticManager *)x2WControl_DW.OUTPUT_1_0_DiagMgr;
  neu_destroy_diagnostic_manager(diagnosticManager);
  simulationData = (NeslSimulationData *)x2WControl_DW.OUTPUT_1_0_SimData;
  nesl_destroy_simulation_data(simulationData);
  nesl_erase_simulator("x2WControl/Solver Configuration_1");
  nesl_destroy_registry();
}
