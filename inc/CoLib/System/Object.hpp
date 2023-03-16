#ifndef COLIB_OBJECT_HPP
#define COLIB_OBJECT_HPP

#include <memory>
#include <CoLib/Config.hpp>

namespace co
{

    template <typename T>
    class Object : public T
    {

    public:
        template <typename... Args>
        static std::shared_ptr<Object<T>> create(Args &&...args);

        std::shared_ptr<Object<T>> getSelf();
        std::shared_ptr<Object<const T>> getSelf() const;

    private:
        template <typename... Args>
        Object(Args &&...args);

        ~Object();

        std::weak_ptr<Object<T>> m_self;
    };

}

#include <CoLib/System/Object.inl>

#endif // COLIB_OBJECT_HPP