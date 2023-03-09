#ifndef COLIB_GRAPHICS_UTILS_HPP
#define COLIB_GRAPHICS_UTILS_HPP

#include <SFML/Graphics/Rect.hpp>
#include <CoLib/Graphics/Export.hpp>

namespace sf
{
    class Vertex;
    class VertexArray;
}

namespace co
{

    class Geometry;

    void COLIB_GRAPHICS_API setPoints(
        sf::Vertex *array,
        szt count,
        const Geometry &geometry,
        szt index = 0,
        szt precision = 1);

    void COLIB_GRAPHICS_API setPoints(
        sf::VertexArray &array,
        const Geometry &geometry,
        szt precision = 1);

    ///////////////////////////////////////////////

    void COLIB_GRAPHICS_API fitPoints(
        sf::Vertex *array,
        szt count,
        const sf::FloatRect &srcRect,
        const sf::FloatRect &dstRect);

    void COLIB_GRAPHICS_API fitPoints(
        sf::VertexArray &array,
        const sf::FloatRect &dstRect);

}

#endif // COLIB_GRAPHICS_UTILS_HPP