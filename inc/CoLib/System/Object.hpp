#ifndef COLIB_OBJECT_HPP
#define COLIB_OBJECT_HPP

#include <memory>
#include <CoLib/System/Export.hpp>

namespace co
{

    class COLIB_SYSTEM_API Object
    {

    public:
        template <typename T>
        std::shared_ptr<T> cast();

        template <typename T>
        std::shared_ptr<const T> cast() const;

        Object();
        virtual ~Object();

        template <typename T, typename...As>
        static std::shared_ptr<T> create(As&&... args);

    private:
        std::weak_ptr<Object> m_self;
    };

}

#include <CoLib/System/Object.inl>

#endif // COLIB_OBJECT_HPP