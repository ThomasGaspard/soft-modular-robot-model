#ifndef SET_ROBOT_HPP
#define SET_ROBOT_HPP

#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include <fstream>
#include <thread>
#include <chrono>


void set_robot(std::vector<double>& centers, std::vector<double>& default_radii, std::vector<double>& max_radii);
void set_robot2(std::vector<double>& centers, std::vector<double>& default_radii, std::vector<double>& max_radii);
#endif // SET_ROBOT_HPP
