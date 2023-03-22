#ifndef COLIB_EXCEPTION_HPP
#define COLIB_EXCEPTION_HPP

#include <string>
#include <exception>
#include <functional>
#include <CoLib/System/Constants.hpp>

namespace co
{

    class Exception;

    using Action = std::function<void()>;
    using ExceptionHandler = std::function<void(const Exception &)>;

    void COLIB_SYSTEM_API runCatching(const Action &action, const ExceptionHandler &handler);

    ///////////////////////////////////////////////////////////////////////////////////////////

    class COLIB_SYSTEM_API Exception
        : public std::exception
    {
    public:
        const std::string &getReason() const;

        Exception(const std::string &reason = UNKNOWN_EXCEPTION_STRING);
        virtual ~Exception();

    private:
        const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT override;

        std::string m_reason;
    };

    /////////////////////////////////////////////////////////////////////////////////////

    class NotImplementedException
        : public Exception
    {
    public:
        NotImplementedException(const std::string &reason = NOT_IMPLEMENTED_EXCEPTION_STRING) : Exception(reason) {}
        virtual ~NotImplementedException() {}
    };

    class InvalidOperationException
        : public Exception
    {
    public:
        InvalidOperationException(const std::string &reason = INVALID_OPERATION_EXCEPTION_STRING) : Exception(reason) {}
        virtual ~InvalidOperationException() {}
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif // COLIB_EXCEPTION_HPP