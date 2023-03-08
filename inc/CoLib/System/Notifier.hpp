#ifndef COLIB_NOTIFIER_HPP
#define COLIB_NOTIFIER_HPP

#include <functional>
#include <memory>
#include <list>
#include <CoLib/Config.hpp>

namespace co
{

    template <typename R, typename... As>
    using SharedFunction = std::shared_ptr<std::function<R(As...)>>;

    template <typename C, typename T>
    class Notifier;

    ///////////////////////////////////////

    template <typename R, typename... As>
    class Notifier<void, R(As...)>
    {

    public:
        void notify(const As &...args) const;

        template <typename F>
        void notify(const As &...args, const F &callback) const;

        void add(const SharedFunction<R, As...> &function);
        void remove(const SharedFunction<R, As...> &function);

        Notifier(std::nullptr_t = 0);

    private:
        std::list<SharedFunction<R, As...>> m_functions;
    };

    /////////////////////////////////////////////////////////////////

    template <typename C, typename R, typename... As>
    class Notifier<C, R(As...)> : private Notifier<void, R(As...)>
    {

        friend C;

    public:
        using Notifier<void, R(As...)>::add;
        using Notifier<void, R(As...)>::remove;

        Notifier(std::nullptr_t = 0);
    };

}

#include <CoLib/System/Notifier.inl>

#endif // COLIB_NOTIFIER_HPP