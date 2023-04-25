#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <ctime>

class Exception: public std::exception
{
protected:
    std::string _error_message;
public:
    Exception(std::string file, std::string class_name, size_t line)
    {
        time_t error_time = time(nullptr);

        _error_message = "File name: " + file + " in line " + std::to_string(line) + " in class " + class_name
                          + "\nTime: " + std::to_string(error_time) + "Info: ";
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
    std::string _special_error_message =" (error type: index error)\n";
public:
    ExceptionIndex(std::string file, std::string class_name, size_t line, std::string message = ""):
        Exception(file, class_name, line)
    {
        _error_message += message + _special_error_message + "\"";
    }
};


class ExceptionDataExpaired: public Exception
{
private:
    std::string _special_error_message =" (error type: data is expired)\n";
public:
    ExceptionDataExpaired(std::string file, std::string class_name, size_t line, std::string message = ""):
        Exception(file, class_name, line)
    {
        _error_message += message + _special_error_message + "\n";
    }
};

class ExceptionBadAllocate: public Exception
{
private:
    std::string _special_error_message =" (error type: bad Allocate)\n";
public:
    ExceptionBadAllocate(std::string file, std::string class_name, size_t line, std::string message = ""):
        Exception(file, class_name, line)
    {
        _error_message += message + _special_error_message + "\n";
    }
};

#include "exceptionmatrix.hpp"

#endif // EXCEPTION_H
