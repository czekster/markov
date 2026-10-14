/*
Unit tests for the "Markov Chains for programmers" code (project01).
Copyright (C) 2022-  Ricardo M. Czekster -- GPLv3, see ../LICENSE

Build and run from this folder:  make unit
*/

#include "../challenges/project01/defs.h"

static int failures = 0, checks = 0;

#define CHECK(cond, msg) do { checks++; \
   if (!(cond)) { failures++; printf("  FAIL %s:%d  %s\n", __FILE__, __LINE__, msg); } } while (0)
#define CHECK_NEAR(a, b, tol, msg) do { double _a = (a), _b = (b); checks++; \
   if (!(fabs(_a - _b) <= (tol))) { failures++; \
      printf("  FAIL %s:%d  %s (got %.7f, expected %.7f, tol %g)\n", __FILE__, __LINE__, msg, _a, _b, (double)(tol)); } } while (0)

/* build a size x size matrix from a flat row-major array */
static float** mat(int size, const float* v) {
   float** m = create_matrix(size);
   for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++)
         m[i][j] = v[i * size + j];
   return m;
}

static const float GENERIC[16] = {   /* Generic CTMC, diagonal not yet fixed */
    0, 1, 5, 4,
    2, 0, 0, 0,
    0, 9, 0, 2,
    7, 0, 1, 0 };

static const float BELFAST[9] = {
   0.80f, 0.15f, 0.05f,
   0.70f, 0.20f, 0.10f,
   0.50f, 0.30f, 0.20f };

/* ---------------------------------------------------------------- validation */
static void test_validate_dtmc(void) {
   int st;
   float** m = mat(3, BELFAST);
   CHECK(validate_mc(m, 3, &st, 'd') == SUCCESS, "Belfast DTMC is well-formed");
   destroy_matrix(m, 3);

   const float bad_sum[9] = { 0.5f, 0.4f, 0,   0.2f, 0.8f, 0,   0.3f, 0.3f, 0.4f };
   m = mat(3, bad_sum);
   CHECK(validate_mc(m, 3, &st, 'd') == ERR_LINE_SUM, "row summing to 0.9 is rejected");
   CHECK(st == 0, "row-sum error reports row 0");
   destroy_matrix(m, 3);

   const float absorbing[9] = { 0.5f, 0.5f, 0,   0, 1, 0,   0.3f, 0.3f, 0.4f };
   m = mat(3, absorbing);
   CHECK(validate_mc(m, 3, &st, 'd') == ERR_ABSORBING, "self-loop of 1 is absorbing");
   CHECK(st == 1, "absorbing state is state 1");
   destroy_matrix(m, 3);

   /* a state with no incoming transitions is NOT absorbing */
   const float unreachable[9] = { 0, 0.5f, 0.5f,   0, 0.5f, 0.5f,   0, 0.5f, 0.5f };
   m = mat(3, unreachable);
   CHECK(validate_mc(m, 3, &st, 'd') == SUCCESS, "unreachable state is not flagged as absorbing");
   destroy_matrix(m, 3);

   /* rows written with 5 decimals (1/3 = 0.33333) are accepted and normalised */
   const float thirds[9] = { 0.33333f, 0.33333f, 0.33333f,   0.5f, 0.5f, 0,   0, 0.5f, 0.5f };
   m = mat(3, thirds);
   CHECK(validate_mc(m, 3, &st, 'd') == SUCCESS, "0.33333 rows pass within tolerance");
   CHECK_NEAR(m[0][0] + m[0][1] + m[0][2], 1.0, 1e-6, "row is renormalised to sum 1");
   destroy_matrix(m, 3);
}

static void test_validate_ctmc(void) {
   int st;
   float** q = mat(4, GENERIC);
   CHECK(validate_mc(q, 4, &st, 'c') == SUCCESS, "Generic CTMC is well-formed");
   destroy_matrix(q, 4);

   const float dead[9] = { 0, 1, 0,   0, 0, 0,   2, 0, 0 };   /* state 1 has no exit */
   q = mat(3, dead);
   CHECK(validate_mc(q, 3, &st, 'c') == ERR_ABSORBING, "CTMC state without exit rate is absorbing");
   CHECK(st == 1, "absorbing CTMC state is state 1");
   destroy_matrix(q, 3);
}

/* ------------------------------------------------------ CTMC transformations */
static void test_ctmc_transformations(void) {
   float** q = mat(4, GENERIC);
   fix_ctmc(q, 4);
   const float diag[4] = { -10, -2, -11, -8 };
   for (int i = 0; i < 4; i++)
      CHECK_NEAR(q[i][i], diag[i], 1e-6, "fix_ctmc diagonal = -(row sum)");

   CHECK_NEAR(discover_lambda(q, 4), 11.0, 1e-6, "lambda = max |q_ii| = 11 (positive)");

   float** u = convert2dtmc(q, 4);   /* uniformised: I + Q/lambda */
   const float expect[16] = {
      1.0f/11, 1.0f/11, 5.0f/11, 4.0f/11,
      2.0f/11, 9.0f/11, 0,       0,
      0,       9.0f/11, 0,       2.0f/11,
      7.0f/11, 0,       1.0f/11, 3.0f/11 };
   for (int i = 0; i < 4; i++) {
      float s = 0;
      for (int j = 0; j < 4; j++) {
         CHECK_NEAR(u[i][j], expect[i * 4 + j], 1e-6, "uniformised DTMC entry");
         s += u[i][j];
      }
      CHECK_NEAR(s, 1.0, 1e-6, "uniformised DTMC row sums to 1");
   }

   float** qp = convert2ctmc_prime(q, 4);   /* Q + lambda*I */
   const float qpdiag[4] = { 1, 9, 0, 3 };
   for (int i = 0; i < 4; i++)
      CHECK_NEAR(qp[i][i], qpdiag[i], 1e-6, "Q' diagonal = q_ii + lambda");
   CHECK_NEAR(qp[0][2], 5.0, 1e-6, "Q' off-diagonal unchanged");

   /* fractional diagonal: integer abs() used to truncate this */
   const float frac[4] = { 0, 10.5f,   0.25f, 0 };
   float** f = mat(2, frac);
   fix_ctmc(f, 2);
   CHECK_NEAR(discover_lambda(f, 2), 10.5, 1e-6, "lambda keeps fractional rates");

   destroy_matrix(q, 4); destroy_matrix(u, 4); destroy_matrix(qp, 4); destroy_matrix(f, 2);
}

/* -------------------------------------------------------- numerical methods */
static void test_vmm_belfast(void) {
   float** m = mat(3, BELFAST);
   float v[3] = { 1, 0, 0 }, old[3];
   int runs = 0;
   do {
      memcpy(old, v, sizeof v);
      multiply_vector(v, m, 3);
   } while (!converge_vector(old, v, 3) && ++runs < MAXRUNS);
   CHECK(runs < MAXRUNS, "VMM converges on Belfast");
   CHECK_NEAR(v[0], 0.7625,  1e-4, "Belfast pi(Rainy)");
   CHECK_NEAR(v[1], 0.16875, 1e-4, "Belfast pi(Cloudy)");
   CHECK_NEAR(v[2], 0.06875, 1e-4, "Belfast pi(Sunny)");
   destroy_matrix(m, 3);
}

static void test_power_belfast(void) {
   float** m = mat(3, BELFAST);
   int runs = 0;
   do multiply_matrix(m, 3); while (!converge_matrix(m, 3) && ++runs < MAXRUNS);
   CHECK(runs < MAXRUNS, "Power converges on Belfast");
   for (int i = 0; i < 3; i++)
      CHECK_NEAR(m[i][0], 0.7625, 1e-4, "Power: every row -> pi");
   destroy_matrix(m, 3);
}

static void test_power_periodic(void) {
   /* periodic 2-state flip: P^k never converges; rows must stay stochastic (no drift to 0/inf/NaN) */
   const float flip[4] = { 0, 1,   1, 0 };
   float** m = mat(2, flip);
   int runs = 0;
   do multiply_matrix(m, 2); while (!converge_matrix(m, 2) && ++runs < 200);
   CHECK(runs >= 200, "periodic chain does not report convergence");
   CHECK_NEAR(m[0][0] + m[0][1], 1.0, 1e-5, "rows stay stochastic under repeated squaring");
   destroy_matrix(m, 2);

   /* drift case: rows that sum to 0.999999 */
   const float drift[4] = { 0.499999f, 0.5f,   0.5f, 0.499999f };
   m = mat(2, drift);
   for (int k = 0; k < 40; k++) multiply_matrix(m, 2);
   CHECK(m[0][0] == m[0][0], "no NaN after 40 squarings");
   CHECK_NEAR(m[0][0] + m[0][1], 1.0, 1e-5, "no decay to 0 after 40 squarings");
   destroy_matrix(m, 2);

   float** n = create_matrix(2);   /* NaN must never count as converged */
   for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) n[i][j] = NAN;
   CHECK(!converge_matrix(n, 2), "NaN matrix is not converged");
   destroy_matrix(n, 2);
}

/* -------------------------------------------------------- random / simulation */
static void test_exponential(void) {
   srandom(12345);
   const int N = 200000;
   double s = 0;
   for (int i = 0; i < N; i++) s += exponential(4.0f);
   CHECK_NEAR(s / N, 0.25, 0.005, "mean of Exp(4) is 1/4");
}

static void test_race(void) {
   /* rates 4, 9, 1, 5 (book Figure 3.6): winner j with prob q_j/19; time advances by the winner only */
   srandom(2024);
   float line[4] = { 4, 9, 1, 5 };
   int wins[4] = { 0 };
   const int N = 200000;
   float t = 0;
   for (int i = 0; i < N; i++) {
      float before = t;
      wins[lowest_not_zero(line, 4, &t)]++;
      if (i < 1000) CHECK(t - before > 0 && t - before < 50, "one race adds one positive time");
   }
   CHECK_NEAR(wins[0] / (double)N, 4.0 / 19, 0.005, "P(state 0 wins) = 4/19");
   CHECK_NEAR(wins[1] / (double)N, 9.0 / 19, 0.005, "P(state 1 wins) = 9/19");
   CHECK_NEAR(wins[2] / (double)N, 1.0 / 19, 0.005, "P(state 2 wins) = 1/19");
   CHECK_NEAR(wins[3] / (double)N, 5.0 / 19, 0.005, "P(state 3 wins) = 5/19");
   CHECK_NEAR(t / N, 1.0 / 19, 0.002, "mean race time = 1/sum(rates)");

   float zeros[3] = { 0, 2, 0 };   /* zero rates never win */
   int w = 0;
   for (int i = 0; i < 1000; i++) w += (lowest_not_zero(zeros, 3, &t) == 1);
   CHECK(w == 1000, "zero-rate transitions never win");
}

int main(void) {
   test_validate_dtmc();
   test_validate_ctmc();
   test_ctmc_transformations();
   test_vmm_belfast();
   test_power_belfast();
   test_power_periodic();
   test_exponential();
   test_race();
   printf("unit tests: %d checks, %d failed\n", checks, failures);
   return failures ? 1 : 0;
}
