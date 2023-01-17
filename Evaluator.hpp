#ifndef EVALUATOR_H
#define EVALUATOR_H
#include "Expression.hpp"
#include "Operator.hpp"
#include "ConvertFunctions.hpp"
#include "Lexer.hpp"
#include "Float.hpp"
#include "Matrix.hpp"
#include "Bool.hpp"


class Evaluator {
public:
    using OperandRef = std::shared_ptr<const Operand>;
    using Operation = std::function<std::shared_ptr<const Operand>(std::vector<OperandRef>)>;
    using OverloadInfo = std::vector<std::vector<std::string> >;
public:
    std::shared_ptr<const Operand> evaluate(std::string& inputExpression);

    void addOperator(Operation Operator, const OperationKey& key, int precedence,
                     Associativity associativity, Notation notation);
    void addFunction(Operation Function, const OperationKey& key);
    void addConversion(const std::string& operandType1, const std::string& operandType2, Operation convertFunction);
private:
    void buildExpressionTree(std::string& inputExpression);
    std::shared_ptr<Expression> makeExpression(const std::pair<std::string, std::string>&  lexem,
                                               const std::vector<std::shared_ptr<Expression> >& arguments = {});
    std::shared_ptr<const Operand> _evaluate(const std::shared_ptr<Expression>& head) const;
private:
    OperationRegistry _operationRegistry;
    Lexer _lexer;
    std::shared_ptr<Expression> _head;
};
#endif
