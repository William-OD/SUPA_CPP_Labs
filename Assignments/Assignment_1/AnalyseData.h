#ifndef ANALYSEDATA_H
#define ANALYSEDATA_H
#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <cmath>

void task_1();

std::tuple<std::vector<double>, std::vector<double>> read_data(const std::string & filename, char delimiter = ',');

void print_vectors(const std::vector<double> & x_array, const std::vector<double> & y_array, std::size_t n, bool useFull_flag);

std::tuple<std::vector<double>, std::vector<double>, std::vector<double>> vectorMag(const std::vector<double> & x_array, const std::vector<double> & y_array);

std::tuple<double, double> least_squares(const std::vector<double> & x, const std::vector<double> & y);

void writeStringToFile(const std::string& content, const std::string& filename);

#endif // ANALYSEDATA_H