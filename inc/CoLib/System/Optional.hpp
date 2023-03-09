#ifndef COLIB_OPTIONAL_HPP
#define COLIB_OPTIONAL_HPP

#include <CoLib/Config.hpp>

namespace co
{

    template <typename T>
    class Optional
    {

    public:
        bool isValid() const;
        void invalidate();

        const T &getValue() const;
        void setValue(const T &value);

        Optional(std::nullptr_t = 0);
        Optional(const T &value);

    private:
        bool m_isValid;
        T m_value;
    };

}

#include <CoLib/System/Optional.inl>

#endif // COLIB_OPTIONAL_HPP