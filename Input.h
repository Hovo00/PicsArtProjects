#ifndef INPUTClASS_H
#define INPUTClASS_H
#include <iostream>
#include <string>

class InputBase {
public:
    virtual void getInput(std::string& inpStr) = 0;
};

class ConsoleInput : public InputBase {
public:
    virtual void getInput(std::string& inpStr) override;
};

#endif
