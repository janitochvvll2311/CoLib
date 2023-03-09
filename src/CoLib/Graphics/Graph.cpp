#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <CoLib/Graphics/PointSource.hpp>
#include <CoLib/Graphics/Utils.hpp>
#include <CoLib/Graphics/Graph.hpp>

namespace co
{

    void Graph::setPrimitiveType(sf::PrimitiveType type)
    {
        m_array.setPrimitiveType(type);
    }

    void Graph::setPoints(const PointSource &source, szt precision)
    {
        co::setPoints(m_array, source, precision);
    }

    void Graph::setColor(const sf::Color &color)
    {
        co::setColors(m_array, color);
    }

    void Graph::setTextureRect(const sf::FloatRect &texRect)
    {
        co::setTexCoords(m_array, texRect);
    }

    void Graph::setTexture(const sf::Texture *const texture)
    {
        m_texture = texture;
    }

    void Graph::fitPoints(const sf::FloatRect &bounds)
    {
        co::fitPoints(m_array, bounds);
    }

    Graph::Graph()
        : m_array(), m_color(sf::Color::White), m_texture(nullptr) {}

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