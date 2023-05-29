/*
 * x2WControl_data.c
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

/* Block parameters (default storage) */
P_x2WControl_T x2WControl_P = {
  /* Mask Parameter: PIDController_D
   * Referenced by: '<S35>/Derivative Gain'
   */
  0.01,

  /* Mask Parameter: PIDController_I
   * Referenced by: '<S38>/Integral Gain'
   */
  0.25,

  /* Mask Parameter: PIDController_InitialConditionF
   * Referenced by: '<S36>/Filter'
   */
  0.0,

  /* Mask Parameter: PIDController_InitialConditio_m
   * Referenced by: '<S41>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController_N
   * Referenced by: '<S44>/Filter Coefficient'
   */
  100.0,

  /* Mask Parameter: PIDController_P
   * Referenced by: '<S46>/Proportional Gain'
   */
  0.5,

  /* Expression: 180/pi
   * Referenced by: '<Root>/Gain'
   */
  57.295779513082323,

  /* Expression: 0.01
   * Referenced by: '<Root>/Step'
   */
  0.01,

  /* Expression: 50
   * Referenced by: '<Root>/Step'
   */
  50.0,

  /* Expression: 0
   * Referenced by: '<Root>/Step'
   */
  0.0
};
