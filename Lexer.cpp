#include "Lexer.h"

std::vector<std::string > Lexer::divideTolexems(std::string& inpStr) {
    std::vector<std::string> lexems;
    lexems.resize(inpStr.size());
    int count = 0;
    for (int i = 0; i < inpStr.size(); ++i) {
         if (TypeInfo::isDigit(inpStr[i])) {
            lexems[count].push_back('n');
            while (TypeInfo::isDigit(inpStr[i])) {
                lexems[count].push_back(inpStr[i++]);
            }
            ++count;
         } 
         if (TypeInfo::isLetter(inpStr[i])) {
            lexems[count].push_back('v');
            while (TypeInfo::isLetter(inpStr[i])) {
                lexems[count].push_back(inpStr[i++]);
            }
            ++count;
         }
         if (inpStr[i] == '{') {
            lexems[count].push_back('m');
            lexems[count].push_back(inpStr[i++]);
            int cCount = 1;
            while (cCount != 0) {
                if (inpStr[i] == '{') { ++cCount; }
                if (inpStr[i] == '}') { --cCount; }
                lexems[count].push_back(inpStr[i++]);
            }
            ++count;
         }
         if (TypeInfo::isOperator(inpStr[i])) {
            //lexems[count].push_back('o');
            lexems[count].push_back(inpStr[i++]);
            ++count;
         }
    }
    lexems.resize(count);
    //return lexems;
    return infixToPostfix(lexems);
}

std::vector<std::string> Lexer::infixToPostfix(std::vector<std::string>& infix) {
    std::vector<std::string> postfix;
    std::stack<std::string> st;
    for (auto& lexem : infix) {
        if (TypeInfo::isOperator(lexem[0])) {
            if (lexem[0] == '(') {
                st.push(lexem);
                continue;
            }
            if (lexem[0] == ')') {
//May cause seg fault in feuture (stack empty not checked )CHECK 
                while (st.top() != "(") {
                    postfix.push_back(st.top());
                    st.pop();
                }
                st.pop();
                continue;
            }
            //change here for associativity
            //
            //std::cout << " bxdooo" << std::endl;
            if (st.empty()) {
                st.push(lexem);
                continue;
            }
            if (TypeInfo::operPrec(st.top()) < TypeInfo::operPrec(lexem)) {
                st.push(lexem);
            }
            else {
                while (!st.empty() && (TypeInfo::operPrec(st.top()) >= TypeInfo::operPrec(lexem))) {
                    postfix.push_back(st.top());
                    st.pop();
                }
                st.push(lexem);
            }
        }
        else {
            postfix.push_back(lexem);
        }
        //std::cout << " still okey";
    }
    while (!st.empty()) {
        postfix.push_back(st.top());
        st.pop();
    }
    
    return postfix;
}

// int Lexer::prec(std::string oper) {
//     if (oper == "+" || oper == "-") {
//         return 1;
//     }
//     if (oper == "*" || oper == "/") {
//         return 2;
//     }
//     return -1;
//}
