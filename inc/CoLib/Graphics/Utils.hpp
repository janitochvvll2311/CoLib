#ifndef COLIB_GRAPHICS_UTILS_HPP
#define COLIB_GRAPHICS_UTILS_HPP

#include <SFML/Graphics/Rect.hpp>
#include <CoLib/Graphics/Export.hpp>

namespace sf
{
    class Vertex;
    class VertexArray;
    class Color;
    class Glyph;
    class String;
    class Font;
}

namespace co
{

    class PointSource;

    void COLIB_GRAPHICS_API setPoints(
        sf::Vertex *array,
        szt count,
        const PointSource &source,
        szt index = 0,
        szt precision = 1);

    void COLIB_GRAPHICS_API setPoints(
        sf::VertexArray &array,
        const PointSource &source,
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

    ////////////////////////////////////////////////

    void COLIB_GRAPHICS_API setColors(
        sf::Vertex *array,
        szt count,
        const sf::Color &color);

    void COLIB_GRAPHICS_API setColors(
        sf::VertexArray &array,
        const sf::Color &color);

    ////////////////////////////////////////////////

    void COLIB_GRAPHICS_API setTexCoords(
        sf::Vertex *array,
        szt count,
        const sf::FloatRect &srcRect,
        const sf::FloatRect &dstRect);

    void COLIB_GRAPHICS_API setTexCoords(
        sf::VertexArray &array,
        const sf::FloatRect &dstRect);

    ////////////////////////////////////////////////

    void COLIB_GRAPHICS_API setGlyphs(
        sf::Vertex *array,
        szt vCount,
        const sf::Glyph *const glyphs,
        szt gCount);

    void COLIB_GRAPHICS_API setGlyphs(
        sf::VertexArray &array,
        const sf::Glyph *const glyphs,
        szt gCount);

    /////////////////////////////////////////////////

    void COLIB_GRAPHICS_API setText(
        sf::Vertex *array,
        szt vCount,
        const sf::String &text,
        const sf::Font &font,
        f32t cSize);

    void COLIB_GRAPHICS_API setText(
        sf::VertexArray &array,
        const sf::String &text,
        const sf::Font &font,
        f32t cSize);

}

#endif // COLIB_GRAPHICS_UTILS_HPP