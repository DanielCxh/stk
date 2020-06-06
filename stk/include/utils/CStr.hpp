#ifndef C_STR_HPP
#define C_STR_HPP

#include <vector>
#include <string>

class CStr
{

public:

    static std::vector<std::string> Split(std::string const & _str, const char const * _delim);

    static std::string Trim();
    static std::string TrimL();
    static std::string TrimR();

private:
    CStr() {}
    ~CStr() {}
};

#endif /* C_STR_HPP */