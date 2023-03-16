#ifndef COLIB_SYSTEM_UTILS_HPP
#define COLIB_SYSTEM_UTILS_HPP

#include <functional>
#include <CoLib/System/Export.hpp>

namespace co
{

    class Exception;

    void COLIB_SYSTEM_API runCatching(const std::function<void()> &callable, const std::function<void(const Exception &)> &handler);

}

#endif // COLIB_SYSTEM_UTILS_HPP