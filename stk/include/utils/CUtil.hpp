#ifndef C_UTIL_HPP
#define C_UTIL_HPP

/* prohibition of copying for class */
class CNoCopyable
{

protected:
    CNoCopyable() {}
    ~CNoCopyable() {}

private:
    CNoCopyable(CNoCopyable const & that) = delete;
    CNoCopyable(CNoCopyable && that) = delete;
    CNoCopyable &operator=(CNoCopyable const & that) = delete;
    CNoCopyable &operator=(CNoCopyable && that) = delete;
};

#endif /* C_UTIL_HPP */