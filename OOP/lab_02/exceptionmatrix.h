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

class ExceptionOutOfIndex: public Exception
{
private:
    std::string _special_error_message = " (error type: index error)\n";
public:
    ExceptionOutOfIndex(std::string file, size_t line, std::string message = ""):
        Exception(file, line)
    {
        std::strncat(_error_message, message.data(), sizeof(_error_message) - strlen(_error_message));
        std::strncat(_error_message, _special_error_message.data(), sizeof(_error_message) - strlen(_error_message));
    }
};


class ExceptionDataExpaired: public Exception
{
private:
    std::string _special_error_message = " (error type: data is expired)\n";
public:
    ExceptionDataExpaired(std::string file, size_t line, std::string message = ""):
        Exception(file, line)
    {
        std::strncat(_error_message, message.data(), sizeof(_error_message) - strlen(_error_message));
        std::strncat(_error_message, _special_error_message.data(), sizeof(_error_message) - strlen(_error_message));
    }
};

class ExceptionBadAllocate: public Exception
{
private:
    std::string _special_error_message = " (error type: bad Allocate)\n";
public:
    ExceptionBadAllocate(std::string file, size_t line, std::string message = ""):
        Exception(file, line)
    {
        std::strncat(_error_message, message.data(), sizeof(_error_message) - strlen(_error_message));
        std::strncat(_error_message, _special_error_message.data(), sizeof(_error_message) - strlen(_error_message));
    }
};

class ExceptionNowMatrixIsFree: public Exception
{
private:
    std::string _special_error_message = " (error type: matrix is free)\n";
public:
    ExceptionNowMatrixIsFree(std::string file, size_t line, std::string message = ""):
        Exception(file, line)
    {
        std::strncat(_error_message, message.data(), sizeof(_error_message) - strlen(_error_message));
        std::strncat(_error_message, _special_error_message.data(), sizeof(_error_message) - strlen(_error_message));
    }
};

class ExceptionIncorrectSourceSizeParams: public Exception
{
private:
    std::string _special_error_message = " (error type: source object has incorrect params)\n";
public:
    ExceptionIncorrectSourceSizeParams(std::string file, size_t line, std::string message = ""):
        Exception(file, line)
    {
        std::strncat(_error_message, message.data(), sizeof(_error_message) - strlen(_error_message));
        std::strncat(_error_message, _special_error_message.data(), sizeof(_error_message) - strlen(_error_message));
    }
};

class ExceptionImpossibleOperation: public Exception
{
private:
    std::string _special_error_message = " (error type: this operation is impossible for objects.)\n";
public:
    ExceptionImpossibleOperation(std::string file, size_t line, std::string message = ""):
        Exception(file, line)
    {
        std::strncat(_error_message, message.data(), sizeof(_error_message) - strlen(_error_message));
        std::strncat(_error_message, _special_error_message.data(), sizeof(_error_message) - strlen(_error_message));
    }
};

class ExceptionImpossibleToDivide: public Exception
{
private:
    std::string _special_error_message = " (error type: there was no way to divide objects)\n";
public:
    ExceptionImpossibleToDivide(std::string file, size_t line, std::string message = ""):
        Exception(file, line)
    {
        std::strncat(_error_message, message.data(), sizeof(_error_message) - strlen(_error_message));
        std::strncat(_error_message, _special_error_message.data(), sizeof(_error_message) - strlen(_error_message));
    }
};

#include "exceptionmatrix.hpp"

#endif // EXCEPTION_H
