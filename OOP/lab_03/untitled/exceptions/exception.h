#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <ctime>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <locale>

class Exception: public std::exception
{
protected:
    char _error_message[512];
public:
    Exception(std::string file, size_t line)
    {
        auto error_time = std::time(nullptr);
        auto tm = *std::localtime(&error_time);
        std::ostringstream ss;
        ss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
        ss.imbue(std::locale("ru_RU.utf-8"));

        snprintf(_error_message, sizeof(_error_message), "filename: %.*s\nline: %zu\ntime: %.*s\ninfo: ",
                 (int) file.size(), file.data(),
                 line,
                 (int) ss.str().size() , ss.str().data());
    }

    virtual ~Exception() {};

    virtual const char *what() const noexcept override
    {
        return _error_message;
    };
};

#endif // EXCEPTION_H
