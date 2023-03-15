#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <CoLib/Graphics/PointSource.hpp>
#include <CoLib/Graphics/Utils.hpp>
#include <CoLib/Graphics/Graph.hpp>

namespace co
{

    sf::PrimitiveType Graph::getPrimitiveType() const
    {
        return m_array.getPrimitiveType();
    }

    void Graph::setPrimitiveType(sf::PrimitiveType type)
    {
        m_array.setPrimitiveType(type);
    }

    ///////////////////////////////////////////////////////////////////////

    const sf::VertexArray &Graph::getVertexes() const
    {
        return m_array;
    }

    void Graph::setPoints(const PointSource &source, szt precision)
    {
        co::setPoints(m_array, source, precision);
    }

    ///////////////////////////////////////////////////////////////////////

    const sf::Color &Graph::getColor() const
    {
        return m_color;
    }

    void Graph::setColor(const sf::Color &color)
    {
        m_color = color;
        co::setColors(m_array, m_color);
    }

    ///////////////////////////////////////////////////////////////////////

    const sf::FloatRect &Graph::getTextureRect() const
    {
        return m_texRect;
    }

    void Graph::setTextureRect(const sf::FloatRect &texRect)
    {
        m_texRect = texRect;
        co::setTexCoords(m_array, m_texRect);
    }

    ///////////////////////////////////////////////////////////////////////

    const sf::Texture *const Graph::getTexture() const
    {
        return m_texture;
    }

    void Graph::setTexture(const sf::Texture *const texture, bool reset)
    {
        m_texture = texture;
        if (m_texture && reset)
        {
            setTextureRect({{0, 0}, sf::Vector2f(m_texture->getSize())});
        }
    }

    ///////////////////////////////////////////////////////////////////////

    void Graph::fitPoints(const sf::FloatRect &bounds)
    {
        co::fitPoints(m_array, bounds);
    }

    ///////////////////////////////////////////////////////////////////////

    void Graph::setGlyphs(const sf::Glyph *const glyphs, szt count)
    {
        co::setGlyphs(m_array, glyphs, count);
    }

    void Graph::setText(const sf::String &text, const sf::Font &font, f32t size)
    {
        co::setText(m_array, text, font, size);
        m_texture = &font.getTexture(size);
    }

    Graph::Graph()
        : m_array(), m_color(sf::Color::White), m_texRect(), m_texture(nullptr) {}

    Graph::~Graph() {}

    //////////////////////////////////////////////////////////////////////////////////

    void Graph::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        auto _states = states;
        _states.transform.combine(getTransform());
        _states.texture = m_texture;
        target.draw(m_array, _states);
    }

}