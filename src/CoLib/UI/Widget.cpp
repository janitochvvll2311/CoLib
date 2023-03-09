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

    void Widget::invalidate()
    {
        m_isValid = false;
    }

    Widget::Widget(f32t width, f32t heigth)
        : Box(width, heigth), m_isValid(false), m_array()
    {
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