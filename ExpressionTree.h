#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H
#include "Expression.h"
#include "Matrix.h"
#include "TypeInfo.h"
#include "Add.h"
#include "Mul.h"
#include "Sub.h"

class ExpressionTree {
public:
    bool buildExpressionTree(std::vector<std::string>);
    std::shared_ptr<Expression> makeExpression(std::string, std::vector<std::shared_ptr<Expression> > = {});
    std::shared_ptr<Expression>& getHead();
    std::shared_ptr<Operand> evaluate(std::shared_ptr<Expression>);
private:
    std::shared_ptr<Expression> head;

};
#endif