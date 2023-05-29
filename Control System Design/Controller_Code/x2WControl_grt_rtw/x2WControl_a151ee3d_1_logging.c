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

PmfMessageId x2WControl_a151ee3d_1_recordLog(const RuntimeDerivedValuesBundle
  *rtdv, const int *eqnEnableFlags, const double *state, const int *modeVector,
  const double *input, const double *inputDot, const double *inputDdot, double
  *logVector, double *errorResult, NeuDiagnosticManager *neDiagMgr)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  int ii[1];
  double xx[49];
  (void) rtdvd;
  (void) rtdvi;
  (void) eqnEnableFlags;
  (void) modeVector;
  (void) inputDot;
  (void) inputDdot;
  (void) neDiagMgr;
  xx[0] = 57.29577951308232;
  xx[1] = 2.0;
  xx[2] = 0.7070996124424118;
  xx[3] = 0.5 * state[2];
  xx[4] = cos(xx[3]);
  xx[5] = 3.184035771019137e-3;
  xx[6] = sin(xx[3]);
  xx[3] = xx[2] * xx[4] - xx[5] * xx[6];
  xx[7] = xx[2] * xx[6];
  xx[2] = xx[5] * xx[4];
  xx[4] = xx[7] + xx[2];
  xx[5] = xx[2] + xx[7];
  xx[2] = 2.538659245956119e-3;
  xx[6] = state[3] * state[3];
  xx[7] = xx[2] * xx[6];
  xx[8] = 4.281311158152548e-3;
  xx[9] = xx[8] * xx[6];
  xx[6] = (5.729577951308231e-3 * state[3] + 7.996472092178835e-3 * xx[7] -
           4.741612338356592e-3 * xx[9]) / 2.343295585686667e-3;
  xx[10] = xx[7] - xx[8] * xx[6];
  xx[7] = xx[10] * xx[4];
  xx[8] = xx[9] + xx[2] * xx[6];
  xx[11] = - xx[7];
  xx[12] = xx[10] * xx[3] - xx[5] * xx[8];
  xx[13] = xx[4] * xx[8];
  pm_math_Vector3_cross_ra(xx + 3, xx + 11, xx + 14);
  xx[2] = xx[3] * xx[3];
  xx[9] = 1.0;
  xx[10] = (xx[2] + xx[2]) * xx[1] - xx[9];
  xx[11] = xx[4] * xx[3];
  xx[12] = xx[5] * xx[3];
  xx[13] = xx[11] - xx[12];
  xx[15] = (xx[12] + xx[11]) * xx[1];
  xx[16] = (xx[11] + xx[12]) * xx[1];
  xx[17] = (xx[2] + xx[4] * xx[4]) * xx[1] - xx[9];
  xx[18] = xx[5] * xx[4];
  xx[19] = xx[1] * (xx[18] - xx[2]);
  xx[20] = xx[1] * (xx[12] - xx[11]);
  xx[11] = xx[18] + xx[2];
  xx[12] = (xx[2] + xx[5] * xx[5]) * xx[1] - xx[9];
  xx[21] = xx[10];
  xx[22] = xx[1] * xx[13];
  xx[23] = xx[15];
  xx[24] = xx[16];
  xx[25] = xx[17];
  xx[26] = xx[19];
  xx[27] = xx[20];
  xx[28] = xx[11] * xx[1];
  xx[29] = xx[12];
  xx[2] = 0.5326496893663588;
  xx[9] = 4.638249746573962e-3;
  xx[18] = 1.0708;
  xx[30] = 0.5275778433139708;
  xx[31] = xx[2] * xx[10] + xx[9] * xx[15];
  xx[32] = xx[2] * xx[16] + xx[9] * xx[19];
  xx[33] = xx[2] * xx[20] + xx[9] * xx[12];
  xx[34] = xx[18] * xx[13];
  xx[35] = 0.5354 * xx[17];
  xx[36] = xx[11] * xx[18];
  xx[37] = xx[9] * xx[10] + xx[30] * xx[15];
  xx[38] = xx[9] * xx[16] + xx[30] * xx[19];
  xx[39] = xx[9] * xx[20] + xx[30] * xx[12];
  pm_math_Matrix3x3_compose_ra(xx + 21, xx + 31, xx + 40);
  xx[2] = 0.1566 + xx[40];
  memcpy(xx + 9, xx + 2, 1 * sizeof(double));
  ii[0] = factorSymmetricPosDef(xx + 9, 1, xx + 10);
  if (ii[0] != 0) {
    return sm_ssci_recordRunTimeError(
      "physmod:sm:core:compiler:mechanism:mechanism:degenerateMassFoll",
      "'x2WControl/Prismatic Joint1' has a degenerate mass distribution on its follower side.",
      neDiagMgr);
  }

  xx[10] = 9.806650000000001;
  xx[11] = 1.77635683940025e-15;
  xx[12] = (input[0] + xx[1] * (xx[14] - xx[7] * xx[3]) - xx[8]) / xx[9] + xx[10]
    * xx[46] / xx[9] - xx[11] * xx[2] / xx[9];
  xx[2] = xx[4] * xx[10];
  xx[7] = xx[11] + xx[12];
  xx[8] = xx[4] * xx[7];
  xx[13] = xx[2];
  xx[14] = - (xx[5] * xx[7] + xx[10] * xx[3]);
  xx[15] = xx[8];
  pm_math_Vector3_cross_ra(xx + 3, xx + 13, xx + 16);
  logVector[0] = state[0];
  logVector[1] = state[1];
  logVector[2] = xx[0] * state[2];
  logVector[3] = xx[0] * state[3];
  logVector[4] = xx[12];
  logVector[5] = - ((xx[6] + (xx[1] * (xx[16] - xx[2] * xx[3]) - xx[7]) *
                     1.083371326034485 - (xx[10] + (xx[18] - xx[8] * xx[3]) *
    xx[1]) * 1.827046994968829) * xx[0]);
  errorResult[0] = 0.0;
  return NULL;
}
