#include <CoLib/System/Exception.hpp>

namespace co
{

    const char *Exception::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW
    {
        return getReason();
    }

    const s8t Exception::getReason() const
    {
        return m_reason;
    }

    Exception::Exception(const s8t reason) 
        : m_reason(reason)
    {}

    Exception::~Exception() = default;

}