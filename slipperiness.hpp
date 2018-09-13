#ifndef SLIPPERINESS_H
#define SLIPPERINESS_H

#include <tuple>
#include <cmath>
#include <iostream>

std::pair<double,double> slipperiness(double x1, double x2, double xg);
std::pair<double,double> slipperiness2(double x1, double x2, double xg);
std::pair<double,double> slipperiness3(double x1, double x2, double xg);
std::pair<double,double> slipperiness4(double x1, double x2, double xg);
double f(double x);
double g(double C,double alpha, double beta, double x);
#endif // SLIPPERINESS_H
