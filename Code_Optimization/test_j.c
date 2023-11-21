#include <stdio.h>
#include <math.h>
#include <time.h>
#include "test_j.h"
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

// gcc -lm test_j.c -o test_j

// since these variables appear to be only within the scope of function_j(), declare them as
// global so we can declare and/or define them elsewhere while preserving their usage in function_j()
double fptildemin, aX, gX, fpt, alpha, gamma1, sigma_a, sigma_b, exp1arg, sigma, exp2arg;

double function_j(double f, double fp, double fptilde)
{
  fptildemin = (1.0/2.0/M_PI) * pow((4.0 * b / 5.0), (1.0/4.0));
  aX  = (log(a)-log(aC))/log(fptildemin);
  gX  = -log(gC)/log(fptildemin);

  fpt = MAX(fptilde, fptildemin);

  alpha   = aC  * pow(fpt, aX);
  gamma1   = gC  * pow(fpt, gX);
  sigma_a = saC * pow(fpt, saX);
  sigma_b = sbC * pow(fpt, sbX);

  exp1arg = -1.25 * pow((f/fp),-4);
  sigma   = (f <= fp) * sigma_a + (f > fp) * sigma_b;

  exp2arg = -0.5 * pow((f-fp)/(sigma*fp), 2);

  // also, simply return value of equation rather than declaring/defining a variable for that
  return alpha * pow(g, 2) * pow((2*M_PI), -4) * pow(f,-5) * exp(exp1arg) * pow(gamma1, exp(exp2arg));
}

// driver code for demonstration
int main()
{
  clock_t startTime = clock(); // start time

  double S, f, fp, fptilde;

  for (f = -5.; f <= 5.; f += 0.01)
  {
    for (fp = 0.; fp <= 10.; fp += 0.01)
    {
      for (fptilde = 0.; fptilde <= 10.; fptilde += 0.01)
      {
        S = function_j(f, fp, fptilde);
      }
    }
  }

  clock_t endTime = clock(); // end time
  double elapsedTime = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;

  printf("Elapsed time: %f seconds\n", elapsedTime);
  return 0;
}
