#ifndef C_FILE_HPP
#define C_FILE_HPP

#include <string>

class CFile
{

public:
    static bool CreateFile(std::string const & _filePath);
    static bool DeleteFile(std::string const & _filePath);

    static bool IsFile(std::string const & _path);
    static bool IsDir(std::string const & _path);

public:
    CFile();
    ~CFile();
};

#endif /* C_FILE_HPP */