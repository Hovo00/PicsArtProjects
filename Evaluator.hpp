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
    Evaluator(const OperationRegistry& registry);
    //using VectorOfLexems = std::vector<std::pair<std::string, std::string> >;
    std::shared_ptr<const Operand> evaluate(std::string& inputExpression);
    const std::shared_ptr<Expression>& getHead() const;
private:
    void buildExpressionTree(std::string& inputExpression);
    std::shared_ptr<Expression> makeExpression(const std::pair<std::string, std::string>&  lexem,
                                               const std::vector<std::shared_ptr<Expression> >& arguments = {});
    std::shared_ptr<const Operand> _evaluate(const std::shared_ptr<Expression>& head) const;
private:
    const OperationRegistry& _operationRegistry;
    Lexer _lexer;
    std::shared_ptr<Expression> _head;
};
#endif
