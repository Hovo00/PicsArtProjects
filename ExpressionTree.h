#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H
#include "Expression.h"
#include "Matrix.h"
#include "TypeInfo.h"
#include "Operator.h"
#include "ConvertFunctions.h"

class ExpressionTree {
public:
    using VectorOfLexems = std::vector<std::pair<std::string, std::string> >;
    void buildExpressionTree(const VectorOfLexems& lexems);
    std::shared_ptr<Expression>& getHead();
    std::shared_ptr<Operand> evaluate(const std::shared_ptr<Expression>& head);
private:
    std::shared_ptr<Expression> makeExpression(const std::pair<std::string, std::string>&  lexem, 
                                               const std::vector<std::shared_ptr<Expression> >& arguments = {});
private:
    std::shared_ptr<Expression> _head;
};
#endif
