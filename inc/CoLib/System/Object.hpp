#ifndef COLIB_OBJECT_HPP
#define COLIB_OBJECT_HPP

#include <memory>
#include <CoLib/System/Export.hpp>

namespace co
{

    class Object;
    using WeakObject = std::weak_ptr<Object>;

    ////////////////////////////////////////////

    class COLIB_SYSTEM_API Object
    {

    public:
        template <typename T>
        std::shared_ptr<T> cast();

        template <typename T>
        std::shared_ptr<const T> cast() const;

        Object();
        virtual ~Object();

        template <typename T, typename... As>
        static std::shared_ptr<T> create(As &&...args);

    private:
        WeakObject m_self;
    };

    ////////////////////////////////////////////////////////////

    template <typename T, typename... As>
    std::shared_ptr<T> create(As &&...args);

}

#include <CoLib/System/Object.inl>

#endif // COLIB_OBJECT_HPP