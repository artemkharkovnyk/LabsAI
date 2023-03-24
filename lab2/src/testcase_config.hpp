#include <math.h>

double f(double x){
    return - std::pow((3 * std::pow(x, 2) - 12), 2) / 256;
}

int n = 34;
double pc = 0.75;
double pm = 0.001;