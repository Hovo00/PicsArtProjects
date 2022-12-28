#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H
#include "Expression.h"
#include "Operator.h"
#include "ConvertFunctions.h"
#include "Lexer.h"
#include "Float.h"
#include "Matrix.h"
#include "Bool.h"


class ExpressionTree {
public:
    ExpressionTree(const OperationRegistry& registry);
    using VectorOfLexems = std::vector<std::pair<std::string, std::string> >;
    void buildExpressionTree(std::string& inputExpression);
    std::shared_ptr<Expression>& getHead();
    std::shared_ptr<Operand> evaluate(const std::shared_ptr<Expression>& head);
private:
    std::shared_ptr<Expression> makeExpression(const std::pair<std::string, std::string>&  lexem, 
                                               const std::vector<std::shared_ptr<Expression> >& arguments = {});
private:
    const OperationRegistry& _operationRegistry;
    Lexer _lexer;
    std::shared_ptr<Expression> _head;
};
#endif
