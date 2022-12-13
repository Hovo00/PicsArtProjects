#include "ExpressionTree.h"

bool ExpressionTree::buildExpressionTree(ExpressionTree::VectorOfLexems lexems) {
    std::stack<std::shared_ptr<Expression> > treeStack;
    for (auto& lexem : lexems) {   
        //std::cout << lexem.first << " " << lexem.second << std::endl;
        if (lexem.first == "oper") {
            std::vector<std::shared_ptr<Expression> > arguments;
            std::cout << TypeInfo::argCount[lexem.second] << std::endl ;
            for (int i = 0; i < TypeInfo::argCount[lexem.second]; ++i) {
                arguments.push_back(treeStack.top());
                treeStack.pop();
            }
            treeStack.push(makeExpression(lexem, arguments));
        }
        else {
            treeStack.push(makeExpression(lexem));
        }
    }
    head = treeStack.top();
    treeStack.pop(); 
    return true;
}

std::shared_ptr<Expression>& ExpressionTree::getHead() {
    return head;
}
 std::shared_ptr<Expression> ExpressionTree::makeExpression(std::pair<std::string, std::string> lexem, std::vector<std::shared_ptr<Expression> > arguments) {
    if (lexem.first == "oper") {
        return std::make_shared<Operator>(lexem.second, arguments);
    }
    if (lexem.first == "matrix") {
        return std::make_shared<Matrix>(lexem.second);
    }
    if (lexem.first == "float") {
        return std::make_shared<Float>(lexem.second);
    }
 }
 std::shared_ptr<Operand> ExpressionTree::evaluate(std::shared_ptr<Expression>& head){
    OperationRegistry::initializeOperationMap();
    return head->evaluate();
 }