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

}