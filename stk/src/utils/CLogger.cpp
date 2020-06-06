#include <utils/CLogger.hpp>

namespace stk
{

static const std::string LOG_CTX_INFO  = " I ";
static const std::string LOG_CTX_DEBUG = " D ";
static const std::string LOG_CTX_WARN  = " W ";
static const std::string LOG_CTX_ERR   = " E ";

static const std::string LOG_COLOR_RED    = "\033[31m";
static const std::string LOG_COLOR_GREEN  = "\033[32m";
static const std::string LOG_COLOR_YELLOW = "\033[33m";
static const std::string LOG_COLOR_GRAY   = "\033[38;2;128;128;128m";

bool CLogger::m_color { false };

CLogger::CLogger(LOG_LEVEL const & _level, std::string const & _mode)
{
    showTag(_level, _mode);
}

CLogger& CLogger::operator<<(int _i)
{
    std::cout << _i;

    return *this;
}

CLogger& CLogger::operator<<(float _f)
{
    std::cout << _f;

    return *this;
}

CLogger& CLogger::operator<<(char _c)
{
    std::cout << _c;

    return *this;
}

CLogger& CLogger::operator<<(std::string const & _str)
{
    std::cout << _str;

    return *this;
}

CLogger& CLogger::operator<<(COutputNewLine)
{
    std::cout << "\033[0m\n";

    return *this;
}

void CLogger::SetColorfull(bool _color)
{
    m_color = _color;
}

void CLogger::showTag(LOG_LEVEL const & _level, std::string const & _mode)
{
    if (IsColorfull())
    {
        std::cout << getColorStr(_level);
    }

    std::cout << getLevelStr(_level);

    if (_mode.empty())
    {
        std::cout << " | ";
    }
    else
    {
        std::cout << _mode << " | ";
    }
}

std::string CLogger::getColorStr(LOG_LEVEL const & _level)
{
    switch(_level)
    {
        case LOG_LEVEL::DEBUG:  return LOG_COLOR_GRAY;
        case LOG_LEVEL::INFO:   return LOG_COLOR_GREEN;
        case LOG_LEVEL::WARN:   return LOG_COLOR_YELLOW;
        case LOG_LEVEL::ERROR:  return LOG_COLOR_RED;
        default: return "";
    }
}

std::string CLogger::getLevelStr(LOG_LEVEL const & _level)
{
    switch(_level)
    {
        case LOG_LEVEL::DEBUG:  return LOG_CTX_DEBUG;
        case LOG_LEVEL::INFO:   return LOG_CTX_INFO;
        case LOG_LEVEL::WARN:   return LOG_CTX_WARN;
        case LOG_LEVEL::ERROR:  return LOG_CTX_ERR;
        default: return "";
    }
}

bool CLogger::IsColorfull()
{
    return m_color;
}

CLogD::CLogD(std::string const & _mode)
    : CLogger(LOG_LEVEL::DEBUG, _mode)
{

}

CLogI::CLogI(std::string const & _mode)
    : CLogger(LOG_LEVEL::INFO, _mode)
{
    
}

CLogW::CLogW(std::string const & _mode)
    : CLogger(LOG_LEVEL::WARN, _mode)
{
    
}

CLogE::CLogE(std::string const & _mode)
    : CLogger(LOG_LEVEL::ERROR, _mode)
{
    
}

}