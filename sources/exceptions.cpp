#include "exceptions.hpp"
const char *BadRequestException::what() const noexcept
{
    return "Bad Request";
}
const char *NotFoundException::what() const noexcept
{
    return "Not Found";
}
const char *PermissionDeniedException::what() const noexcept
{
    return "Permission Denied";
}
const char *EmptyException::what() const noexcept
{
    return "Empty";
}
const char *LevelMisMatch::what() const noexcept
{
    return "Level Mismatch";
} 