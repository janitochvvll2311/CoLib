#include <CoLib/UI/Aligner.hpp>
#include <CoLib/UI/Widget.hpp>

namespace co
{

    bool Widget::isValid() const
    {
        return m_isValid;
    }

    void Widget::invalidate()
    {
        m_isValid = false;
    }

    void Widget::compact()
    {
        setLeft(0);
        setTop(0);
        setWidth(0);
        setHeight(0);
    }

    void Widget::inflate(const sf::Vector2f &size, const Aligner *const aligner)
    {
        setWidth(size.x);
        setHeight(size.y);
        if (aligner)
        {
            aligner->align(*this);
        }
    }

    Widget::Widget()
        : m_isValid(false) {}

    Widget::~Widget() {}

    /////////////////////////////////////////////////////////////////////////////////////////

    void Widget::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        if (!m_isValid)
        {
            onUpdate();
            m_isValid = true;
        }
        onDraw(target, states);
    }

}