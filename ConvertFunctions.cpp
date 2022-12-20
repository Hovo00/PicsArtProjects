#include "ConvertFunctions.h"

 float ConvertFunctions::stringToFloat(const std::string& number ) {
    return std::stof(number);
}    
std::vector<std::vector<float> > ConvertFunctions::stringToMatrix(const std::string& matrixStr) {
    std::vector<std::vector<float> > matrix;
    matrix.resize(matrixStr.size());
    int rowCount = 0;
    int colCount = 0;
    for (int i = 0; i < matrixStr.size(); ++i) {
        if (std::isdigit(matrixStr[i]) || matrixStr[i] == '-') {
            std::string numb;
            while(i < matrixStr.size() && (std::isdigit(matrixStr[i]) || matrixStr[i] == '.' || matrixStr[i] == '-')) {
                numb.push_back(matrixStr[i++]);
            }
            matrix[rowCount].push_back(std::stof(numb));            
        }
        if (matrixStr[i] == '}') {
            ++rowCount;
        }
    }
    --rowCount;
    matrix.resize(rowCount);
    return matrix;
}
