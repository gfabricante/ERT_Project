#ifndef TEST_J_H_
#define TEST_J_H_

const double a  = 0.0081;
const double b  = 0.6;
const double g  = 9.807;
const double gC = 5.87;
const double aC = 0.0317;
const double saC = 0.0547;
const double saX = 0.32;
const double sbC = 0.0783;
const double sbX = 0.16;

void calculateConstants();

double function_j(double f,
                  double fp,
                  double fptilde);

#endif // TEST_J_H_
