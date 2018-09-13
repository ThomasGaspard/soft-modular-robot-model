#ifndef FIND_CONTACT_POINTS_H
#define FIND_CONTACT_POINTS_H

#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include <limits>
#include <algorithm>
#include <cmath>
#include <tuple>
#include <thread>
#include <chrono>

double find_center_mass(const std::vector<double>& centers);
std::tuple<long,long,double> find_contact_points(std::vector<double>& position_of_the_centers, std::vector<double>& radii);


#endif // FIND_CONTACT_POINTS_H
