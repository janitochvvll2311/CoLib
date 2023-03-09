#include <math.h>
#include <limits>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <CoLib/Graphics/Utils.hpp>
#include <CoLib/UI/Widget.hpp>

namespace co
{

    const sf::Color &Widget::getColor() const
    {
        return m_color;
    }

    void Widget::setColor(const sf::Color &value)
    {
        m_color = value;
    }

    /////////////////////////////////////////////////////////////

    f32t Widget::getMinWidth() const
    {
        return m_minWidth;
    }
    
    void Widget::setMinWidth(f32t value)
    {
        m_minWidth = value;
    }

    f32t Widget::getMaxWidth() const
    {
        return m_maxWidth;
    }

    void Widget::setMaxWidth(f32t value)
    {
        m_maxWidth = value;
    }

    f32t Widget::getMinHeight() const
    {
        return m_minHeight;
    }

    void Widget::setMinHeight(f32t value)
    {
        m_minHeight = value;
    }

    f32t Widget::getMaxHeight() const
    {
        return m_maxHeight;
    }

    void Widget::setMaxHeight(f32t value)
    {
        m_maxHeight = value;
    }

    ////////////////////////////////////////////////////////////////

    void Widget::invalidate()
    {
        m_isValid = false;
    }

    void Widget::compact()
    {
        setWidth(m_minWidth);
        setHeight(m_minHeight);
    }

    void Widget::inflate(const Box &box)
    {
        setWidth(std::min(std::max(m_minWidth, box.getWidth()), m_maxWidth));
        setHeight(std::min(std::max(m_minHeight, box.getHeight()), m_maxHeight));
    }

    Widget::Widget()
        : Box(),
          m_isValid(false), m_array(), m_color(sf::Color::White),
          m_minWidth(0), m_maxWidth(std::numeric_limits<f32t>::infinity()),
          m_minHeight(0), m_maxHeight(std::numeric_limits<f32t>::infinity())
    {
    }

    Widget::Widget(f32t width, f32t height)
        : Widget()
    {
        setWidth(m_minWidth = m_maxWidth = width);
        setHeight(m_minHeight = m_maxHeight = height);
    }

    ////////////////////////////////////////////////

    void Widget::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        if (!m_isValid)
        {
            onUpdate(m_array);
            m_isValid = true;
        }
        auto _states = states;
        _states.transform.combine(getTransform());
        target.draw(m_array, _states);
    }

    void Widget::onUpdate(sf::VertexArray &array) const
    {
        array.setPrimitiveType(sf::PrimitiveType::TriangleFan);
        array.resize(4);
        array[0].position = sf::Vector2f(getLeft(), getTop());
        array[1].position = sf::Vector2f(getRight(), getTop());
        array[2].position = sf::Vector2f(getRight(), getBottom());
        array[3].position = sf::Vector2f(getLeft(), getBottom());
        setColors(m_array, m_color);
    }

}