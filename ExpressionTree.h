#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H
#include "Expression.h"
#include "Matrix.h"
#include "TypeInfo.h"
#include "Operator.h"

class ExpressionTree {
public:
    using VectorOfLexems = std::vector<std::pair<std::string, std::string> >;
    void buildExpressionTree(VectorOfLexems lexems);
    std::shared_ptr<Expression>& getHead();
    std::shared_ptr<Operand> evaluate(std::shared_ptr<Expression>& head);
private:
    std::shared_ptr<Expression> makeExpression(std::pair<std::string, std::string>  lexem, std::vector<std::shared_ptr<Expression> > arguments = {});
private:
    std::shared_ptr<Expression> _head;
};
#endif
