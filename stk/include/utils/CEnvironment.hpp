#ifndef C_ENVIRONMENT_HPP
#define C_ENVIRONMENT_HPP

#include <map>
#include <string>

namespace stk /* software tool kit */
{

#ifndef ENV
#define ENV() CEnvironment::GetInstance()
#endif

#ifndef ENVGET
#define ENVGET(k) ENV()->Get(#k)
#endif

#ifndef ENVSET
#define ENVSET(k, v) ENV()->Set(#k, v)
#endif

class CEnvironment final
{

public:

    ~CEnvironment() = default;

    static CEnvironment* GetInstance();

    /*!
     * \brief Load config file to initialize config module.
     */
    bool Init(std::string const & _config_file);

    /*!
     * \brief Get value by key.
     */
    std::string Get(std::string const & _key);

    void Set(std::string const & _key, std::string const & _val);

private:
    CEnvironment();

    bool isSpace(char _c);

    bool isComment(char _c);

    /*!
     * \brief Remove all spaces int the string.
     */
    void trim(std::string & _str);

    bool readLine(std::string const & _line, std::string & _tag, std::string & _key, std::string & _val);

private:
    bool m_inited { false };

    std::map<std::string, std::map<std::string, std::string> > m_tkv; /* tag, <key, value> */ 
};

}

#endif /* C_CONFIG_HPP */