#include <CoLib/System/Object.hpp>

namespace co
{

    template <typename T>
    template <typename... Args>
    inline std::shared_ptr<Object<T>> Object<T>::create(Args &&...args)
    {
        std::shared_ptr<Object<T>> object(
            new Object(args...),
            [](auto *object)
            {
                delete object;
            });
        object->m_self = object;
        return object;
    }

    template <typename T>
    inline std::shared_ptr<Object<T>> Object<T>::getSelf()
    {
        return m_self.lock();
    }

    template <typename T>
    inline std::shared_ptr<Object<const T>> Object<T>::getSelf() const
    {
        return m_self.lock();
    }

    //////////////////////////////////////////////////////////////////////

    template <typename T>
    template <typename... Args>
    inline Object<T>::Object(Args &&...args) : T(args...), m_self() {}

    template <typename T>
    inline Object<T>::~Object() {}

}