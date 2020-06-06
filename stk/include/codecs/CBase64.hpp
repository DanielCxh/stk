#ifndef C_BASE_64_HPP
#define C_BASE_64_HPP

#include <string>

class CBase64
{

public:
    CBase64()
    {
        /* This is the standard dictionary used for Base64 encoding. */
        m_base64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    }

    std::string Encode(const unsigned char * _str, int _bytes);
    std::string Decode(const char * _str, int _bytes);

private:
    std::string m_base64_table;
};

#endif /* C_BASE_64_HPP */