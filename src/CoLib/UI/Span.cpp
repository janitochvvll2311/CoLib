#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <CoLib/UI/Span.hpp>

namespace co
{

    const sf::String &Span::getString() const
    {
        return m_text.getString();
    }

    void Span::setString(const sf::String &value)
    {
        m_text.setString(value);
    }

    const sf::Font *Span::getFont() const
    {
        return m_text.getFont();
    }

    void Span::setFont(const sf::Font &value)
    {
        m_text.setFont(value);
    }

    f32t Span::getCharacterSize() const
    {
        return m_text.getCharacterSize();
    }

    void Span::setCharacterSize(f32t value)
    {
        m_text.setCharacterSize(value);
    }

    const sf::Color &Span::getFillColor() const
    {
        return m_text.getFillColor();
    }

    void Span::setFillColor(const sf::Color &value)
    {
        m_text.setFillColor(value);
    }

    sf::Uint32 Span::getStyle() const
    {
        return m_text.getStyle();
    }

    void Span::setStyle(sf::Uint32 value)
    {
        m_text.setStyle(value);
    }

    f32t Span::getOutlineThickness() const
    {
        return m_text.getOutlineThickness();
    }

    void Span::setOutlineThickness(f32t value)
    {
        m_text.setOutlineThickness(value);
    }

    const sf::Color &Span::getOutlineColor() const
    {
        return m_text.getOutlineColor();
    }

    void Span::setOutlineColor(const sf::Color &value)
    {
        m_text.setOutlineColor(value);
    }

    ////////////////////////////////////////////////////////

    const sf::Text &Span::getText() const
    {
        return m_text;
    }

    void Span::setText(const sf::Text &value)
    {
        m_text = value;
    }

    void Span::compact()
    {
        auto bounds = m_text.getLocalBounds();
        setWidth(bounds.width + getHorizontalSpacing());
        setHeight(bounds.height + getVerticalSpacing());
    };

    void Span::inflate(const Box &box)
    {
        compact();
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