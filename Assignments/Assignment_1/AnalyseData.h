/* William O'Donnell 
24/11/23
C++ SUPA Course
Assignment 1 - Header file
*/
#ifndef ANALYSEDATA_H
#define ANALYSEDATA_H
#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <cmath>
#include <limits>

void task_1();

std::tuple<std::vector<double>, std::vector<double>> read_data(const std::string & filename, char delimiter = ',');

void print_vectors(const std::string &, const std::vector<double> & x_array);
void print_vectors(const std::string &, const std::vector<double> & x_array, const std::vector<double> & y_array, std::size_t n);

std::vector<double> vectorMag(const std::vector<double> & x_array, const std::vector<double> & y_array);

std::tuple<double, double, double, double> leastsq_chisq(std::vector<double> x, std::vector<double> y, std::vector<double> x_err, std::vector<double> y_err);

void XpowY(const std::vector<double> & x_arr, const std::vector<double> & y_arr, std::vector<double> & xpowy_arr, std::size_t i = 0);

void writeToFile(const std::string & filename, const std::string &);
void writeToFile(const std::string & filename, const std::string & , const std::vector<double> &);
void writeToFile(const std::string & filename, const std::string & , const std::vector<double> &, const std::vector<double> &, std::size_t);

#endif // ANALYSEDATA_H