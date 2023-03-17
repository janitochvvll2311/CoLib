#include <CoLib/System/Object.hpp>

namespace co
{

    template <typename T>
    inline std::shared_ptr<T> Object::cast()
    {
        return std::dynamic_pointer_cast<T>(m_self.lock());
    }

    template <typename T>
    inline std::shared_ptr<const T> Object::cast() const
    {
        return std::dynamic_pointer_cast<const T>(m_self.lock());
    }

    template <typename T, typename... As>
    inline std::shared_ptr<T> Object::create(As &&...args)
    {
        auto object = std::make_shared<T>(args...);
        object->m_self = object;
        return object;
    }

    ////////////////////////////////////////////////////////////

    template <typename T, typename... As>
    inline std::shared_ptr<T> create(As &&...args)
    {
        return Object::create<T>(args...);
    }

}