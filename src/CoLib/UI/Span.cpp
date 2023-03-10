#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <CoLib/UI/Span.hpp>

namespace co
{

    const sf::Text &Span::getText() const
    {
        return m_text;
    }

    void Span::setText(const sf::Text &value)
    {
        m_text = value;
    }

    void Span::compact(const sf::Vector2f &size)
    {
        auto bounds = m_text.getLocalBounds();
        setWidth(bounds.width + getHorizontalSpacing());
        setHeight(bounds.height + getVerticalSpacing());
    };

    void Span::inflate(const Box &box)
    {
        compact({0, 0});
        alignHorizontal(box, getHorizontalAlignment());
        alignVertical(box, getVerticalAlignment());
        shrink(getMargin());
    };

    Span::Span()
        : m_text() {}

    Span::~Span() {}

    //////////////////////////////////////////////////////

    void Span::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        Widget::onDraw(target, states);
        auto _states = states;
        auto bounds = m_text.getLocalBounds();
        _states.transform.translate({-bounds.left, -bounds.top});
        target.draw(m_text, _states);
    }

}