#include <CoLib/System/Constants.hpp>
#include <CoLib/System/Exception.hpp>

namespace co
{

    const char *Exception::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW
    {
        return getReason();
    }

    const s8t Exception::getReason() const
    {
        return UNKNOWN_EXCEPTION;
    }

    Exception::Exception() = default;
    Exception::~Exception() = default;

}