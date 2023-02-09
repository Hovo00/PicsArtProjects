#ifndef CONVERTFUNCTION_H
#define CONVERTFUNCTION_H
#include <vector>
#include <string>
#include <iostream>

namespace ConvertFunctions {
    double stringToFloat(const std::string& number);
    std::vector<std::vector<double> > stringToMatrix(const std::string& number);
};

#endif
