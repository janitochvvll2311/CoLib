#ifndef COLIB_OPTIONAL_INL
#define COLIB_OPTIONAL_INL

#include <CoLib/System/Exception.hpp>
#include <CoLib/System/Optional.hpp>

namespace co
{

    template <typename T>
    inline bool Optional<T>::isValid() const
    {
        return m_isValid;
    }

    template <typename T>
    inline void Optional<T>::invalidate()
    {
        m_isValid = false;
    }

    template <typename T>
    inline const T &Optional<T>::getValue() const
    {
        if (!m_isValid)
        {
            throw InvalidValueException();
        }
        return m_value;
    }

    template <typename T>
    inline void Optional<T>::setValue(const T &value)
    {
        m_value = value;
        m_isValid = true;
    }

    template <typename T>
    inline Optional<T>::Optional(std::nullptr_t)
        : m_isValid(false),
          m_value() {}

    template <typename T>
    inline Optional<T>::Optional(const T &value)
        : m_isValid(true),
          m_value(value) {}

}

#endif // COLIB_OPTIONAL_INL