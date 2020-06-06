#ifndef C_LOGGER_HPP
#define C_LOGGER_HPP

#include<iostream>

namespace stk
{

class COutputNewLine {};

using endl = COutputNewLine;

enum class LOG_LEVEL : std::uint8_t
{
    UNDEF = 0U,
    DEBUG = 1U,
    INFO  = 2U,
    WARN  = 4U,
    ERROR = 8U
};

class CLogger
{

public:
    CLogger(LOG_LEVEL const & _level = LOG_LEVEL::UNDEF, std::string const & _mode = "TK");
    ~CLogger() = default;

    CLogger& operator<<(int _i);
    CLogger& operator<<(float _f);
    CLogger& operator<<(char _c);
    CLogger& operator<<(COutputNewLine);
    CLogger& operator<<(std::string const & _str);

    static void SetColorfull(bool _color);
    bool IsColorfull();

private:
    void showTag(LOG_LEVEL const & _level = LOG_LEVEL::UNDEF, std::string const & _mode = "");
    std::string getColorStr(LOG_LEVEL const & _level);
    std::string getLevelStr(LOG_LEVEL const & _level);

private:
    static bool m_color;
};

class CLogD final : public CLogger
{

public:
    CLogD(std::string const & _mode = "TK");

};

class CLogI final : public CLogger
{

public:
    CLogI(std::string const & _mode = "TK");

};

class CLogW final : public CLogger
{

public:
    CLogW(std::string const & _mode = "TK");

};

class CLogE final : public CLogger
{

public:
    CLogE(std::string const & _mode = "TK");

};

}


#endif