#ifndef SET_SEQUENCE_H
#define SET_SEQUENCE_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include <vector>
#include <string>
#include <fstream>
#include "phase.hpp"

void set_sequence(std::vector<double>& start_times, std::vector<double>& time_table, unsigned long number_of_modules);
void set_sequence2(std::vector<double>& start_times, std::vector<double>& time_table, unsigned long number_of_modules);

#endif // SET_SEQUENCE_H
