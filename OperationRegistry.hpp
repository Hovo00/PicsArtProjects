#ifndef OPERATIONREGISTRY_H
#define OPERATIONREGISTRY_H

#include "OperationInfo.hpp"

class OperationRegistry {
public:
    using OperationHandler = std::function<std::shared_ptr<const Operand>(std::vector<std::shared_ptr<const Operand> >)>;
    using OverloadInfo = std::vector<std::vector<std::string> >;
    using OperationInfo = std::pair<OverloadInfo, OperationProperties>;
    using ReturnType = std::string;
    using HandlerInfo = std::pair<ReturnType, OperationHandler>;
public:
    void addOperator(const OperationSigniture& sign, const std::string& returnType, OperationHandler handler, Properties);
    void addFunction(const OperationSigniture& sign, const std::string& returnType, OperationHandler handler);
    void addConversion(const std::string& operandType1, const std::string& operandType2, OperationHandler conversion);

    HandlerInfo handlerInfo(const OperationSigniture& sign) const;
    const OperationInfo& operationInfo(const std::string& OperationHandler) const;
    const std::vector<std::string>& conversionInfo(const std::string& typeName) const;
public:
    bool areConvertableTypes(const std::string& operandType1, const std::string& operandType2) const;
    bool existSigniture(const OperationSigniture& sign) const;
    bool existOperation(const std::string& operationName) const;
private:
    std::unordered_map<std::string, std::vector<std::string> > _conversionInfoMap;
    std::unordered_map<OperationSigniture, HandlerInfo > _operationMap;
    std::unordered_map<std::string, OperationInfo> _operationInfoMap;
};

#endif
