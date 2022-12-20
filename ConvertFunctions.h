#ifndef CONVERTFUNCTION_H
#define CONVERTFUNCTION_H
#include <vector>
#include <string>

namespace ConvertFunctions {
    float stringToFloat(const std::string& number);
    std::vector<std::vector<float> > stringToMatrix(const std::string& number);
};

#endif