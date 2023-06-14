#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>
#include <ctime>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <locale>

class Exception: public std::exception
{
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
protected:
    char _error_message[512];
};

class CreateButtonException: public Exception
{
public:
    CreateButtonException(std::string file, size_t line, std::string message = ""):
        Exception(file, line)
    {
        std::strncat(_error_message, message.data(), sizeof(_error_message) - strlen(_error_message));
        std::strncat(_error_message, _special_error_message.data(), sizeof(_error_message) - strlen(_error_message));
    }
private:
    std::string _special_error_message = " (error type: impossible to create button.)\n";
};

#endif // EXCEPTIONS_H
