#ifndef _EXCEPTIONS_HPP
#define _EXCEPTIONS_HPP

#include <exception>

class BadRequestException : public std::exception
{
public:
    const char *what() const noexcept;
};

class NotFoundException : public std::exception
{
public:
    const char *what() const noexcept;
};

class PermissionDeniedException : public std::exception
{
public:
    const char *what() const noexcept;
};

class EmptyException : public std::exception
{
public:
    const char *what() const noexcept;
};

class LevelMisMatch : public std::exception
{
public:
    const char *what() const noexcept;
};

#endif