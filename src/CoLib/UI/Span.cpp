#include <SFML/Graphics/RenderTarget.hpp>
#include <CoLib/UI/Span.hpp>

namespace co
{

    sf::Text &Span::getText()
    {
        return m_text;
    }

    const sf::Text &Span::getText() const
    {
        return m_text;
    }

    ///////////////////////////////////////////////////////////////////

    void Span::compact()
    {
        Widget::compact();
        auto bounds = m_text.getLocalBounds();
        setWidth(bounds.width);
        setHeight(bounds.height);
    }

    void Span::inflate(const sf::Vector2f &size)
    {
        auto bounds = m_text.getLocalBounds();
        Widget::inflate({bounds.width, bounds.height});
    }

    Span::Span()
        : m_text() {}

    Span::~Span() {}

    ////////////////////////////////////////////////////////

    void Span::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        auto _states = states;
        auto bounds = m_text.getLocalBounds();
        _states.transform.translate({-bounds.left, -bounds.top});
        target.draw(m_text, _states);
    }

}