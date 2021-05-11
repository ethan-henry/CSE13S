#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#define EPSILON 0.000001
#define OPTIONS "sctea"

double Sin(double);
double Tan(double);
double Exp(double);
void All(void);
double Cos(double);

// Main Function
// Chooses which approximation to run based on command line arguments
int32_t main(int32_t argc, char **argv) {
  int32_t c = 0;
  while (((c = getopt(argc, argv, OPTIONS)) != -1) && (argc < 3))  {
    switch (c) {
    case 's':
      printf(
          "x\tSin\t\tLibrary\t\tDifference\n-\t---\t\t-------\t\t----------\n");
      for (double n = (-2 * M_PI); n <= 2 * M_PI; n += M_PI * 0.0625) {

        printf("% .4lf\t% .8lf\t% .8lf\t% .10lf\t\n", n, Sin(n), sin(n),
            Sin(n) - sin(n));
      }
      break;
    case 'c':
      printf(
          "x\tCos\t\tLibrary\t\tDifference\n-\t---\t\t-------\t\t----------\n");
      for (double n = -2 * M_PI; n <= 2 * M_PI; n += M_PI * 0.0625) {
        printf("% .4lf\t% .8lf\t% .8lf\t% .10lf\t\n", n, Cos(n), cos(n),
            Cos(n) - cos(n));
      }
      break;
    case 't':
      printf(
          "x\tTan\t\tLibrary\t\tDifference\n-\t---\t\t-------\t\t----------\n");
      for (double n = -(M_PI_2 - 0.001); n <= (M_PI_2 - 0.001);
           n += M_PI * 0.0625) {
        printf("% .4lf\t% .8lf\t% .8lf\t% .10lf\t\n", n, Tan(n), tan(n),
            Tan(n) - tan(n));
      }
      break;
    case 'e':
      printf(
          "x\tExp\t\tLibrary\t\tDifference\n-\t---\t\t-------\t\t----------\n");
      for (double n = 0; n <= 10; n += 0.1) {
        printf("% .4lf\t% .8lf\t% .8lf\t% .10lf\n", n, Exp(n), exp(n),
            Exp(n) - exp(n));
      }
      break;
    case 'a':
      All();
      break;
    default:
      break;
    }
  }

  return 0;
}

// Calculates the approximation of e^x
double Exp(double x) {
  double output = 1.0;
  double c = 1.0;
  double d = 1.0;
  double a = 0.0;
  for (double n = 1.0; c > EPSILON; n++) {
    c = (x / n);
    a = c * d;
    output = output + a;
    d = a;
  }
  return output;
}

// Calculates the approximation of sin(x)
double Sin(double x) {
  double sum = x;
  double numerator = x;
  double denominator = 1;
  for (double k = 3.0; k < 100; k += 2) {
    numerator *= -x * x;
    denominator *= k * (k - 1.0);
    sum += numerator / denominator;
  }
  return sum;
}

// Calculates the approximation of tan(x)
double Tan(double x) {
  double output = 0;
  double z = pow(x, 2);
  double top = x * (((z * (z - 990) + 135135) * z - 4729725) * z + 34459425);
  double bottom = 45 * (((z * (z - 308) + 21021) * z - 360360) * z + 765765);
  output = top / bottom;
  return output;
}

// Calculates the approximation of cos(x)
double Cos(double x) {
  double sum = 1;
  double numerator = 1;
  double denominator = 1;
  for (double k = 2.0; k <= 100; k += 2.0) {
    numerator *= -x * x;
    denominator *= k * (k - 1.0);
    sum += numerator / denominator;
  }
  return sum;
}

// Runs all the approximations
void All(void) {
  printf("x\tSin\t\tLibrary\t\tDifference\n-\t---\t\t-------\t\t----------\n");
  for (double n = (-2 * M_PI); n <= 2 * M_PI; n += M_PI * 0.0625) {
    printf(
        "% .4lf\t% .8lf\t% .8lf\t% .10lf\t\n", n, Sin(n), sin(n), Sin(n) - sin(n));
  }
  printf("x\tCos\t\tLibrary\t\tDifference\n-\t---\t\t-------\t\t----------\n");
  for (double n = (-2 * M_PI); n <= 2 * M_PI; n += M_PI * 0.0625) {
    printf(
        "% .4lf\t% .8lf\t% .8lf\t% .10lf\t\n", n, Cos(n), cos(n), Cos(n) - cos(n));
  }
  printf("x\tTan\t\tLibrary\t\tDifference\n-\t---\t\t-------\t\t----------\n");
  for (double n = -(M_PI_2 - 0.001); n <= (M_PI_2 - 0.001);
       n += M_PI * 0.0625) {
    printf(
        "% .4lf\t% .8lf\t% .8lf\t% .10lf\t\n", n, Tan(n), tan(n), Tan(n) - tan(n));
  }
  printf("x\tExp\t\tLibrary\t\tDifference\n-\t---\t\t-------\t\t----------\n");
  for (double n = 0; n <= 10; n += 0.1) {
    printf(
        "% .4lf\t% .8lf\t% .8lf\t% .10lf\t\n", n, Exp(n), exp(n), Exp(n) - exp(n));
  }
  return;
}
