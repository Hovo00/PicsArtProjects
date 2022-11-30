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
            continue;
         } 
         if (TypeInfo::isLetter(inpStr[i])) {
            lexems[count].push_back('v');
            while (TypeInfo::isLetter(inpStr[i])) {
                lexems[count].push_back(inpStr[i++]);
            }
            ++count;
            continue;
         }
         if (inpStr[i] == '{') {
            lexems[count].push_back('m');
            lexems[count].push_back(inpStr[i++]);
            int cCount = 1;
            while (cCount != 0) {
                if(!TypeInfo::isValidMatrixSymbol(inpStr[i])) {
                    throw invalidMatrixOperand(i);
                }
                if (inpStr[i] == '{') { ++cCount; }
                if (inpStr[i] == '}') { --cCount; }
                lexems[count].push_back(inpStr[i++]);
            }
            ++count;
            continue;
         }
         if (TypeInfo::isOperator(inpStr[i])) {
            //lexems[count].push_back('o');
            lexems[count].push_back(inpStr[i]);
            ++count;
            continue;
         }
    }
    lexems.resize(count);
    std::cout << "more " << std::endl;
    for(auto & i : lexems) {
        std::cout << i << std::endl;
    }
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
                while (!st.empty() && st.top() != "(") {
                    postfix.push_back(st.top());
                    st.pop();
                }
                if (!st.empty()) {
                    st.pop();
                }
                continue;
            }
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
    }
    while (!st.empty()) {
        postfix.push_back(st.top());
        st.pop();
    }
    return postfix;
}

