#include <SFML/Graphics/RenderTarget.hpp>
#include <CoLib/Graphics/Rectangle.hpp>
#include <CoLib/UI/Background.hpp>

namespace co
{

    Graph &Background::getGraph()
    {
        return m_graph;
    }

    const Graph &Background::getGraph() const
    {
        return m_graph;
    }

    Background::Background()
        : m_graph()
    {
        co::Rectangle rectangle(1, 1);
        m_graph.setPrimitiveType(sf::PrimitiveType::TriangleFan);
        m_graph.setPoints(rectangle);
    }

    Background::~Background() {}

    ///////////////////////////////////////////////////

    void Background::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        if (getWidth() > 0 && getHeight() > 0)
        {
            target.draw(m_graph, states);
        }
    }

    void Background::onUpdate() const
    {
        if (getWidth() > 0 && getHeight() > 0)
        {
            m_graph.fitPoints({{0, 0}, {getWidth(), getHeight()}});
        }
    }

}