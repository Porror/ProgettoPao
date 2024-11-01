#ifndef ERROR_H
#define ERROR_H

#include <string>

class Error
{
private:
    unsigned int code;
public:
    Error(const unsigned int&);
    std::string correspondingString() const;
    int getCode()const;
};

#endif // ERROR_H
