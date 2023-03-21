#ifndef COLIB_INFLATABLE_HPP
#define COLIB_INFLATABLE_HPP

#include <SFML/System/Vector2.hpp>

namespace co
{

    class Inflatable
    {

    public:
        virtual void compact() = 0;
        virtual void inflate(const sf::Vector2f &size) = 0;

        Inflatable() = default;
        virtual ~Inflatable() = default;
    };

}

#endif // COLIB_INFLATABLE_HPP