#ifndef C_AES_HPP
#define C_AES_HPP

#include <memory>

namespace stk
{

enum class AES_MODE : std::uint32_t
{
    ECB = 0U,
    CBC,
    CTR,
    CFB,
    OFB,
    MAX
};

enum class AES_PADDING : std::uint32_t
{
    NO = 0U,
    PKCS5,
    ISO10126,
    MAX
};

enum class AES_KEY_LEN : std::uint32_t
{
    AES128 = 128U,
    AES192 = 192U,
    AES256 = 256U,
};

class CAES
{

    void Encrypt();
    void Decryption();

    // iv
};

}

#endif /* C_AES_HPP */