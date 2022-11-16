#include "Lexer.h"

std::vector<std::string > Lexer::divideTolexems(std::string& inpStr) {
    std::vector<std::string> lexems;
    lexems.resize(inpStr.size());
    int count = 0;
    for (int i = 0; i < inpStr.size(); ++i) {
         if (is_digit(inpStr[i])) {
            lexems[count].push_back('n');
            while (is_digit(inpStr[i])) {
                lexems[count].push_back(inpStr[i++]);
            }
            ++count;
         } 
         if (is_letter(inpStr[i])) {
            lexems[count].push_back('v');
            while (is_letter(inpStr[i])) {
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
         if (is_operator(inpStr[i])) {
            //lexems[count].push_back('o');
            lexems[count].push_back(inpStr[i++]);
            ++count;
         }
    }
    lexems.resize(count);
    //return lexems;
    return infixToPostfix(lexems);
}
bool Lexer::is_letter(char lett) {
    return (lett <= 'z' && lett >= 'A')  ? true : false;
}
bool Lexer::is_symbol(char symb) {
    return (symb == '{'|| symb == '}' || symb == ',') ? true : false;
}
bool Lexer::is_operator(char oper) {
    return (oper == '+' || oper == '-' || oper == '/' || oper == '*' || oper == '(' || oper == ')') ? true : false;
}
bool Lexer::is_digit(char digit) {
    return (digit <= '9' && digit >= '1') ? true : false;
}

std::vector<std::string> Lexer::infixToPostfix(std::vector<std::string>& infix) {
    std::vector<std::string> postfix;
    std::stack<std::string> st;
    for (auto& lexem : infix) {
        if (is_operator(lexem[0])) {
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
            if (prec(st.top()) < prec(lexem)) {
                st.push(lexem);
            }
            else {
                while (!st.empty() && (prec(st.top()) >= prec(lexem))) {
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

int Lexer::prec(std::string oper) {
    if (oper == "+" || oper == "-") {
        return 1;
    }
    if (oper == "*" || oper == "/") {
        return 2;
    }
    return -1;
}
