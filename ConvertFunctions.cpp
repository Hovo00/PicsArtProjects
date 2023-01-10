#include "ConvertFunctions.hpp"

 double ConvertFunctions::stringToFloat(const std::string& number ) {
    return std::stof(number);
}
std::vector<std::vector<double> > ConvertFunctions::stringToMatrix(const std::string& matrixStr) {
    int sign = 1;
    if (matrixStr[0] == '-') {
        sign = -1;
    }
    std::vector<std::vector<double> > matrix;
    matrix.resize(matrixStr.size());
    int rowCount = 0;
    int colCount = 0;
    for (int i = 1; i < matrixStr.size(); ++i) {
        if (std::isdigit(matrixStr[i]) || matrixStr[i] == '-') {
            std::string numb;
            while(i < matrixStr.size() && (std::isdigit(matrixStr[i]) || matrixStr[i] == '.' || matrixStr[i] == '-')) {
                numb.push_back(matrixStr[i++]);
            }
            matrix[rowCount].push_back(sign * std::stof(numb));
        }
        if (matrixStr[i] == '}') {
            ++rowCount;
        }
    }
    --rowCount;
    matrix.resize(rowCount);
    return matrix;
}
