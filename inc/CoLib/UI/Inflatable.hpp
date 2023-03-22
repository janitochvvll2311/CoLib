#ifndef COLIB_INFLATABLE_HPP
#define COLIB_INFLATABLE_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace co
{

    class Inflatable
    {

    public:
        virtual sf::Vector2f compact() = 0;
        virtual sf::Vector2f inflate(const sf::Vector2f &size) = 0;
        virtual void place(const sf::Vector2f &position) = 0;

        Inflatable() = default;
        virtual ~Inflatable() = default;
    };

}

#endif // COLIB_INFLATABLE_HPP