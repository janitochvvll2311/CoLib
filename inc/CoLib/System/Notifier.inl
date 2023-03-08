#ifndef COLIB_NOTIFIER_INL
#define COLIB_NOTIFIER_INL

#include <CoLib/System/Notifier.hpp>

namespace co
{

    template <typename R, typename... As>
    inline void Notifier<void, R(As...)>::notify(const As &...args) const
    {
        for (auto &function : m_functions)
        {
            (*function)(args...);
        }
    }

    template <typename R, typename... As>
    template <typename F>
    inline void Notifier<void, R(As...)>::notify(const As &...args, const F &callback) const
    {
        for (auto &function : m_functions)
        {
            callback((*function)(args...));
        }
    }

    template <typename R, typename... As>
    inline void Notifier<void, R(As...)>::add(const SharedFunction<R, As...> &function)
    {
        m_functions.push_back(function);
    }

    template <typename R, typename... As>
    inline void Notifier<void, R(As...)>::remove(const SharedFunction<R, As...> &function)
    {
        m_functions.remove(function);
    }

    template <typename R, typename... As>
    inline Notifier<void, R(As...)>::Notifier(std::nullptr_t)
        : m_functions() {}

    //////////////////////////////////////////////////////////////////////////////////////////

    template <typename C, typename R, typename... As>
    inline Notifier<C, R(As...)>::Notifier(std::nullptr_t) {}

}

#endif // COLIB_NOTIFIER_INL