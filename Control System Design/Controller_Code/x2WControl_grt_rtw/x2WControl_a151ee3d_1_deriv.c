/* Simscape target specific file.
 * This file is generated for the Simscape network associated with the solver block 'x2WControl/Solver Configuration'.
 */

#include <math.h>
#include <string.h>
#include "pm_std.h"
#include "sm_std.h"
#include "ne_std.h"
#include "ne_dae.h"
#include "sm_ssci_run_time_errors.h"
#include "sm_RuntimeDerivedValuesBundle.h"
#include "x2WControl_a151ee3d_1_geometries.h"

PmfMessageId x2WControl_a151ee3d_1_compDerivs(const RuntimeDerivedValuesBundle
  *rtdv, const int *eqnEnableFlags, const double *state, const int *modeVector,
  const double *input, const double *inputDot, const double *inputDdot, const
  double *discreteState, double *deriv, double *errorResult,
  NeuDiagnosticManager *neDiagMgr)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  int ii[1];
  double xx[48];
  (void) rtdvd;
  (void) rtdvi;
  (void) eqnEnableFlags;
  (void) modeVector;
  (void) inputDot;
  (void) inputDdot;
  (void) discreteState;
  (void) neDiagMgr;
  xx[0] = 2.0;
  xx[1] = 0.7070996124424118;
  xx[2] = 0.5 * state[2];
  xx[3] = cos(xx[2]);
  xx[4] = 3.184035771019137e-3;
  xx[5] = sin(xx[2]);
  xx[2] = xx[1] * xx[3] - xx[4] * xx[5];
  xx[6] = xx[1] * xx[5];
  xx[1] = xx[4] * xx[3];
  xx[3] = xx[6] + xx[1];
  xx[4] = xx[1] + xx[6];
  xx[1] = 2.538659245956119e-3;
  xx[5] = state[3] * state[3];
  xx[6] = xx[1] * xx[5];
  xx[7] = 4.281311158152548e-3;
  xx[8] = xx[7] * xx[5];
  xx[5] = (5.729577951308231e-3 * state[3] + 7.996472092178835e-3 * xx[6] -
           4.741612338356592e-3 * xx[8]) / 2.343295585686667e-3;
  xx[9] = xx[6] - xx[7] * xx[5];
  xx[6] = xx[9] * xx[3];
  xx[7] = xx[8] + xx[1] * xx[5];
  xx[10] = - xx[6];
  xx[11] = xx[9] * xx[2] - xx[4] * xx[7];
  xx[12] = xx[3] * xx[7];
  pm_math_Vector3_cross_ra(xx + 2, xx + 10, xx + 13);
  xx[1] = xx[2] * xx[2];
  xx[8] = 1.0;
  xx[9] = (xx[1] + xx[1]) * xx[0] - xx[8];
  xx[10] = xx[3] * xx[2];
  xx[11] = xx[4] * xx[2];
  xx[12] = xx[10] - xx[11];
  xx[14] = (xx[11] + xx[10]) * xx[0];
  xx[15] = (xx[10] + xx[11]) * xx[0];
  xx[16] = (xx[1] + xx[3] * xx[3]) * xx[0] - xx[8];
  xx[17] = xx[4] * xx[3];
  xx[18] = xx[0] * (xx[17] - xx[1]);
  xx[19] = xx[0] * (xx[11] - xx[10]);
  xx[10] = xx[17] + xx[1];
  xx[11] = (xx[1] + xx[4] * xx[4]) * xx[0] - xx[8];
  xx[20] = xx[9];
  xx[21] = xx[0] * xx[12];
  xx[22] = xx[14];
  xx[23] = xx[15];
  xx[24] = xx[16];
  xx[25] = xx[18];
  xx[26] = xx[19];
  xx[27] = xx[10] * xx[0];
  xx[28] = xx[11];
  xx[1] = 0.5326496893663588;
  xx[8] = 4.638249746573962e-3;
  xx[17] = 1.0708;
  xx[29] = 0.5275778433139708;
  xx[30] = xx[1] * xx[9] + xx[8] * xx[14];
  xx[31] = xx[1] * xx[15] + xx[8] * xx[18];
  xx[32] = xx[1] * xx[19] + xx[8] * xx[11];
  xx[33] = xx[17] * xx[12];
  xx[34] = 0.5354 * xx[16];
  xx[35] = xx[10] * xx[17];
  xx[36] = xx[8] * xx[9] + xx[29] * xx[14];
  xx[37] = xx[8] * xx[15] + xx[29] * xx[18];
  xx[38] = xx[8] * xx[19] + xx[29] * xx[11];
  pm_math_Matrix3x3_compose_ra(xx + 20, xx + 30, xx + 39);
  xx[1] = 0.1566 + xx[39];
  memcpy(xx + 8, xx + 1, 1 * sizeof(double));
  ii[0] = factorSymmetricPosDef(xx + 8, 1, xx + 9);
  if (ii[0] != 0) {
    return sm_ssci_recordRunTimeError(
      "physmod:sm:core:compiler:mechanism:mechanism:degenerateMassFoll",
      "'x2WControl/Prismatic Joint1' has a degenerate mass distribution on its follower side.",
      neDiagMgr);
  }

  xx[9] = 9.806650000000001;
  xx[10] = 1.77635683940025e-15;
  xx[11] = (input[0] + xx[0] * (xx[13] - xx[6] * xx[2]) - xx[7]) / xx[8] + xx[9]
    * xx[45] / xx[8] - xx[10] * xx[1] / xx[8];
  xx[1] = xx[3] * xx[9];
  xx[6] = xx[10] + xx[11];
  xx[7] = xx[3] * xx[6];
  xx[12] = xx[1];
  xx[13] = - (xx[4] * xx[6] + xx[9] * xx[2]);
  xx[14] = xx[7];
  pm_math_Vector3_cross_ra(xx + 2, xx + 12, xx + 15);
  deriv[0] = state[1];
  deriv[1] = xx[11];
  deriv[2] = state[3];
  deriv[3] = - (xx[5] + (xx[0] * (xx[15] - xx[1] * xx[2]) - xx[6]) *
                1.083371326034485 - (xx[9] + (xx[17] - xx[7] * xx[2]) * xx[0]) *
                1.827046994968829);
  errorResult[0] = 0.0;
  return NULL;
}

PmfMessageId x2WControl_a151ee3d_1_numJacPerturbLoBounds(const
  RuntimeDerivedValuesBundle *rtdv, const int *eqnEnableFlags, const double
  *state, const int *modeVector, const double *input, const double *inputDot,
  const double *inputDdot, const double *discreteState, double *bounds, double
  *errorResult, NeuDiagnosticManager *neDiagMgr)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  double xx[2];
  (void) rtdvd;
  (void) rtdvi;
  (void) eqnEnableFlags;
  (void) state;
  (void) modeVector;
  (void) input;
  (void) inputDot;
  (void) inputDdot;
  (void) discreteState;
  (void) neDiagMgr;
  xx[0] = 1.0e-9;
  xx[1] = 1.0e-8;
  bounds[0] = xx[0];
  bounds[1] = xx[0];
  bounds[2] = xx[1];
  bounds[3] = xx[1];
  errorResult[0] = 0.0;
  return NULL;
}

PmfMessageId x2WControl_a151ee3d_1_numJacPerturbHiBounds(const
  RuntimeDerivedValuesBundle *rtdv, const int *eqnEnableFlags, const double
  *state, const int *modeVector, const double *input, const double *inputDot,
  const double *inputDdot, const double *discreteState, double *bounds, double
  *errorResult, NeuDiagnosticManager *neDiagMgr)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  double xx[1];
  (void) rtdvd;
  (void) rtdvi;
  (void) eqnEnableFlags;
  (void) state;
  (void) modeVector;
  (void) input;
  (void) inputDot;
  (void) inputDdot;
  (void) discreteState;
  (void) neDiagMgr;
  xx[0] = +pmf_get_inf();
  bounds[0] = xx[0];
  bounds[1] = xx[0];
  bounds[2] = 1.0;
  bounds[3] = xx[0];
  errorResult[0] = 0.0;
  return NULL;
}
