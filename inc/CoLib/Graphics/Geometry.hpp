#ifndef COLIB_GEOMENTRY_HPP
#define COLIB_GEOMENTRY_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <CoLib/Graphics/Export.hpp>

namespace co
{

    class COLIB_GRAPHICS_API Geometry
    {

    public:
        virtual szt getPointCount() const = 0;
        virtual sf::Vector2f getPoint(szt index, szt precision = 1) const = 0;
        virtual bool contains(const sf::Vector2f &point) const = 0;
        virtual sf::FloatRect getBounds(szt precision = 1) const;

        Geometry() = default;
        virtual ~Geometry() = default;
    };

}

#endif // COLIB_GEOMENTRY_HPP