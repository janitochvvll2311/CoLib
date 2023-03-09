#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <CoLib/Graphics/Geometry.hpp>
#include <CoLib/Graphics/Utils.hpp>

namespace co
{

    void setPoints(
        sf::Vertex *array,
        szt count,
        const Geometry &geometry,
        szt index,
        szt precision)
    {
        if (precision == 0)
        {
            precision = 1;
        }
        for (szt i = 0; i < count; i++)
        {
            array[i].position = geometry.getPoint(index + i, precision);
        }
    }

    void setPoints(
        sf::VertexArray &array,
        const Geometry &geometry,
        szt precision)
    {
        if (precision == 0)
        {
            precision = 1;
        }
        auto pCount = geometry.getPointCount() * precision;
        array.resize(pCount);
        setPoints(&array[0], pCount, geometry, 0, precision);
    }

    ///////////////////////////////////////////////////////////////////

    void fitPoints(
        sf::Vertex *array,
        szt count,
        const sf::FloatRect &srcRect,
        const sf::FloatRect &dstRect)
    {
        for (szt i = 0; i < count; i++)
        {
            array[i].position.x = (array[i].position.x - srcRect.left) / srcRect.width * dstRect.width + dstRect.left;
            array[i].position.y = (array[i].position.y - srcRect.top) / srcRect.height * dstRect.height + dstRect.top;
        }
    }

    void fitPoints(
        sf::VertexArray &array,
        const sf::FloatRect &dstRect)
    {
        fitPoints(&array[0], array.getVertexCount(), array.getBounds(), dstRect);
    }

    //////////////////////////////////////////////////////////////////////////////////////

    void setColors(
        sf::Vertex *array,
        szt count,
        const sf::Color &color)
    {
        for (szt i = 0; i < count; i++)
        {
            array[i].color = color;
        }
    }

    void setColors(
        sf::VertexArray &array,
        const sf::Color &color)
    {
        setColors(&array[0], array.getVertexCount(), color);
    }

    /////////////////////////////////////////////////////////////////////////

    void setTexCoords(
        sf::Vertex *array,
        szt count,
        const sf::FloatRect &srcRect,
        const sf::FloatRect &dstRect)
    {
        for (szt i = 0; i < count; i++)
        {
            array[i].texCoords.x = (array[i].position.x - srcRect.left) / srcRect.width * dstRect.width + dstRect.left;
            array[i].texCoords.y = (array[i].position.y - srcRect.top) / srcRect.height * dstRect.height + dstRect.top;
        }
    }

    void setTexCoords(
        sf::VertexArray &array,
        const sf::FloatRect &dstRect)
    {
        setTexCoords(&array[0], array.getVertexCount(), array.getBounds(), dstRect);
    }

}