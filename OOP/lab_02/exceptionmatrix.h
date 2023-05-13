#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <locale>

class Exception: public std::exception
{
protected:
    std::string _error_message;
public:
    Exception(std::string file, size_t line)
    {
        auto error_time = std::time(nullptr);
        auto tm = *std::localtime(&error_time);
        std::ostringstream ss;
        ss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
        ss.imbue(std::locale("ru_RU.utf-8"));

        _error_message = "\nFile name: " + file + "\nIn line " + std::to_string(line)
                         + "\nTime: " + ss.str() + "\nInfo: ";
    }

    virtual ~Exception() {};

    virtual const char *what() const noexcept override
    {
        return _error_message.c_str();
    };
};

class ExceptionIndex: public Exception
{
private:
    std::string _special_error_message = " (error type: index error)\n";
public:
    ExceptionIndex(std::string file, size_t line, std::string message = ""):
        Exception(file, line)
    {
        _error_message += message + _special_error_message + "\"";
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
        _error_message += message + _special_error_message + "\n";
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
        _error_message += message + _special_error_message + "\n";
    }
};

class ExceptionEmptyObject: public Exception
{
private:
    std::string _special_error_message = " (error type: object (matrix ro row) free)\n";
public:
    ExceptionEmptyObject(std::string file, size_t line, std::string message = ""):
        Exception(file, line)
    {
        _error_message += message + _special_error_message + "\n";
    }
};

class ExceptionIncorrectSrcParams: public Exception
{
private:
    std::string _special_error_message = " (error type: source object has incorrect params)\n";
public:
    ExceptionIncorrectSrcParams(std::string file, size_t line, std::string message = ""):
        Exception(file, line)
    {
        _error_message += message + _special_error_message + "\n";
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
        _error_message += message + _special_error_message + "\n";
    }
};

class ExceptionNullObjectPointer: public Exception
{
private:
    std::string _special_error_message = " (error type: there was met null pointer)\n";
public:
    ExceptionNullObjectPointer(std::string file, size_t line, std::string message = ""):
        Exception(file, line)
    {
        _error_message += message + _special_error_message + "\n";
    }
};

class ExceptionRowNotIterrable: public Exception
{
private:
    std::string _special_error_message = " (error type: there was no iterable row)\n";
public:
    ExceptionRowNotIterrable(std::string file, size_t line, std::string message = ""):
        Exception(file, line)
    {
        _error_message += message + _special_error_message + "\n";
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
        _error_message += message + _special_error_message + "\n";
    }
};

#include "exceptionmatrix.hpp"

#endif // EXCEPTION_H
