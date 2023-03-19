#include <SFML/System/String.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Glyph.hpp>
#include <SFML/Graphics/Font.hpp>
#include <CoLib/Graphics/PointSource.hpp>
#include <CoLib/Graphics/Utils.hpp>

namespace co
{

    void setPoints(
        sf::Vertex *array,
        szt count,
        const PointSource &source,
        szt index,
        szt precision)
    {
        if (precision == 0)
        {
            precision = 1;
        }
        for (szt i = 0; i < count; i++)
        {
            array[i].position = source.getPoint(index + i, precision);
        }
    }

    void setPoints(
        sf::VertexArray &array,
        const PointSource &source,
        szt precision)
    {
        if (precision == 0)
        {
            precision = 1;
        }
        auto pCount = source.getPointCount() * precision;
        array.resize(pCount);
        setPoints(&array[0], pCount, source, 0, precision);
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
            auto &vertex = array[i];
            vertex.position.x = (vertex.position.x - srcRect.left) / srcRect.width * dstRect.width + dstRect.left;
            vertex.position.y = (vertex.position.y - srcRect.top) / srcRect.height * dstRect.height + dstRect.top;
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
            auto &vertex = array[i];
            vertex.texCoords.x = (vertex.position.x - srcRect.left) / srcRect.width * dstRect.width + dstRect.left;
            vertex.texCoords.y = (vertex.position.y - srcRect.top) / srcRect.height * dstRect.height + dstRect.top;
        }
    }

    void setTexCoords(
        sf::VertexArray &array,
        const sf::FloatRect &dstRect)
    {
        setTexCoords(&array[0], array.getVertexCount(), array.getBounds(), dstRect);
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void setGlyphs(
        sf::Vertex *array,
        szt vCount,
        const sf::Glyph *const glyphs,
        szt gCount)
    {
        gCount = vCount / 6;
        vCount -= vCount % 6;
        f32t offset = 0;
        for (szt i = 0; i < gCount; i++)
        {
            auto &glyph = glyphs[i];
            auto bounds = glyph.bounds;
            auto texRect = sf::FloatRect(glyph.textureRect);
            //
            sf::Vector2f points[] = {
                {bounds.left + offset, bounds.top},
                {bounds.left + bounds.width + offset, bounds.top},
                {bounds.left + bounds.width + offset, bounds.top + bounds.height},
                {bounds.left + offset, bounds.top + bounds.height}};
            sf::Vector2f texCoords[] = {
                {texRect.left, texRect.top},
                {texRect.left + texRect.width, texRect.top},
                {texRect.left + texRect.width, texRect.top + texRect.height},
                {texRect.left, texRect.top + texRect.height}};
            //
            auto base = i * 6;

            array[base + 0].position = points[0];
            array[base + 1].position = points[1];
            array[base + 2].position = points[2];
            array[base + 3].position = points[0];
            array[base + 4].position = points[3];
            array[base + 5].position = points[2];

            array[base + 0].texCoords = texCoords[0];
            array[base + 1].texCoords = texCoords[1];
            array[base + 2].texCoords = texCoords[2];
            array[base + 3].texCoords = texCoords[0];
            array[base + 4].texCoords = texCoords[3];
            array[base + 5].texCoords = texCoords[2];

            offset += glyph.advance;
        }
    }

    void setGlyphs(
        sf::VertexArray &array,
        const sf::Glyph *const glyphs,
        szt gCount)
    {
        array.setPrimitiveType(sf::PrimitiveType::Triangles);
        array.resize(gCount * 6);
        setGlyphs(&array[0], array.getVertexCount(), glyphs, gCount);
    }

    //////////////////////////////////////////////////////////////////////////////

    void setText(
        sf::Vertex *array,
        szt vCount,
        const sf::String &text,
        const sf::Font &font,
        f32t cSize)
    {
        std::vector<sf::Glyph> glyphs;
        for (auto &c : text)
        {
            glyphs.push_back(font.getGlyph(c, cSize, false, 0));
        }
        setGlyphs(array, vCount, &glyphs.front(), glyphs.size());
    }

    void setText(
        sf::VertexArray &array,
        const sf::String &text,
        const sf::Font &font,
        f32t cSize)
    {
        array.setPrimitiveType(sf::PrimitiveType::Triangles);
        array.resize(text.getSize() * 6);
        setText(&array[0], array.getVertexCount(), text, font, cSize);
    }

}