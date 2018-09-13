#ifndef COMPUTE_ACTUAL_RADII_H
#define COMPUTE_ACTUAL_RADII_H

#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include <algorithm>
#include <iostream>

void compute_actual_radii(std::vector<double>& radii, const std::vector<double>& initial_radii, const std::vector<double>& max_radii,
                          double t, const std::vector<double> start_times, const std::vector<double> time_table);
double R(double t);
#endif // COMPUTE_ACTUAL_RADII_H
