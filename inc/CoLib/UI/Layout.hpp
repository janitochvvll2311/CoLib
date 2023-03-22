#ifndef COLIB_LAYOUT_HPP
#define COLIB_LAYOUT_HPP

#include <SFML/System/Vector2.hpp>

namespace co
{

    class Layout
    {
    public:
        virtual sf::Vector2f getAbsolutePlace() const = 0;
        Layout() = default;
        virtual ~Layout() = default;
    };

}

#endif // COLIB_LAYOUT_HPP