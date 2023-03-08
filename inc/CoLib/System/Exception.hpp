#ifndef COLIB_EXCEPTION_HPP
#define COLIB_EXCEPTION_HPP

#include <exception>
#include <CoLib/System/Export.hpp>

namespace co
{

    class COLIB_SYSTEM_API Exception
        : public std::exception
    {

    public:
        const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override final;
        virtual const s8t getReason() const;
        Exception(const Exception &other) = delete;
        Exception();
        virtual ~Exception();
    };

}

#endif // COLIB_EXCEPTION_HPP