#ifndef FUNCTIONS
#define FUNCTIONS
#include <iostream>
#include <cmath>
#include <array>
#include <fstream>
#define A 1
#define C 1
#define B 3
#define D 5
std::array<double, 3> GLOBAL_point;
double GLOBAL_I_ext;
double GLOBAL_r;
double GLOBAL_s;
double GLOBAL_x0;
double derivative_x(double x, double y, double z);
double derivative_y(double x, double y, double z);
double derivative_z(double x, double y, double z);
double Butcher_DP5[6][6] = {{0.2}, {0.075, 0.225}, {0.9777777777777777, -3.7333333333333333, 3.555555555555555}, 
{2.9525986892242035, -11.595793324188385, 9.822892851699436, -0.2908093278463649 }, 
{2.8462752525252526, -10.757575757575758, 8.906422717743473, 0.2784090909090909, -0.2735313036020583},
{0.09114583333333333, 0, 0.44923629829290207, 0.6510416666666666, -0.322376179245283, 0.13095238095238096}};
double K_X[6] = {};
double K_Y[6] = {};
double K_Z[6] = {};
double TMP[3] = {};
void RK(double h);
double sum(double k[6], int ind, double h);
void merrygoround(double h, int num_of_iter, std::string filename);
#endif