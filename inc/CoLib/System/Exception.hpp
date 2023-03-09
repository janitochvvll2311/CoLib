#ifndef COLIB_EXCEPTION_HPP
#define COLIB_EXCEPTION_HPP

#include <exception>
#include <string>
#include <CoLib/System/Export.hpp>
#include <CoLib/System/Constants.hpp>

namespace co
{

    class COLIB_SYSTEM_API Exception
        : public std::exception
    {

    public:
        const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override final;
        const s8t getReason() const;
        Exception(const Exception &other) = delete;
        Exception(const std::string &reason = UNKNOWN_EXCEPTION_MESSAGE);
        virtual ~Exception();

    private:
        std::string m_reason;
    };

    ///////////////////////////////////////////////////////////////////////////////////////////

    class NotImplementedException : public Exception
    {
    public:
        NotImplementedException(const std::string &reason = NOT_IMPLEMENTED_EXCEPTION_MESSAGE)
            : Exception(reason) {}
    };

    class InvalidValueException : public Exception
    {
    public:
        InvalidValueException(const std::string &reason = INVALID_VALUE_EXCEPTION_MESSAGE)
            : Exception(reason) {}
    };

    class InvalidOperationException : public Exception
    {
    public:
        InvalidOperationException(const std::string &reason = INVALID_OPERATION_EXCEPTION_MESSAGE)
            : Exception(reason) {}
    };

    class InvalidJobStateException : public Exception
    {
    public:
        InvalidJobStateException(const std::string &reason = INVALID_JOB_STATE_EXCEPTION_MESSAGE)
            : Exception(reason) {}
    };

}

#endif // COLIB_EXCEPTION_HPP