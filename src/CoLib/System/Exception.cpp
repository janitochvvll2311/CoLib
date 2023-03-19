#include <CoLib/System/Exception.hpp>

namespace co
{

    void runCatching(const Action &action, const ExceptionHandler &handler)
    {
        try
        {
            action();
        }
        catch (const std::exception &exception)
        {
            handler(Exception(exception.what()));
        }
        catch (const std::string &exception)
        {
            handler(Exception(exception));
        }
        catch (const s8t exception)
        {
            handler(Exception(exception));
        }
        catch (...)
        {
            handler(Exception(UNKNOWN_EXCEPTION_STRING));
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////

    const std::string &Exception::getReason() const
    {
        return m_reason;
    }

    Exception::Exception(const std::string &reason)
        : m_reason(reason) {}

    Exception::~Exception() {}

    const char *Exception::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT
    {
        return m_reason.c_str();
    }

}