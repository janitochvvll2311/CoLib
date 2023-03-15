#include <SFML/Graphics/RenderStates.hpp>
#include <CoLib/UI/Layout.hpp>
#include <CoLib/UI/Widget.hpp>

namespace co
{

    f32t Widget::getOuterWidth() const
    {
        return getWidth();
    }

    f32t Widget::getInnerWidth() const
    {
        return getWidth();
    }

    f32t Widget::getOuterHeight() const
    {
        return getHeight();
    }

    f32t Widget::getInnerHeight() const
    {
        return getHeight();
    }

    ////////////////////////////////////////////////////////

    bool Widget::isValid() const
    {
        return m_isValid;
    }

    void Widget::invalidate()
    {
        m_isValid = false;
        if (m_parent)
        {
            auto *widget = dynamic_cast<Widget *>(m_parent);
            if (widget)
            {
                widget->invalidate();
            }
        }
    }

    void Widget::compact()
    {
        setLeft(0);
        setTop(0);
        setWidth(0);
        setHeight(0);
    }

    void Widget::inflate(const sf::Vector2f &size)
    {
        setLeft(0);
        setTop(0);
        setWidth(size.x);
        setHeight(size.y);
    }

    void Widget::update(bool force) const
    {
        if (!m_isValid || force)
        {
            onUpdate();
            m_isValid = true;
        }
    }

    ///////////////////////////////////////////////////////////////////////

    bool Widget::dispatchEvent(Widget *target, const sf::Event &event)
    {
        return handleEvent(target, event);
    }

    bool Widget::bubbleEvent(Widget *target, const sf::Event &event)
    {
        auto *widget = dynamic_cast<Widget *>(m_parent);
        return (handleEvent(target, event) || (widget && widget->bubbleEvent(target, event)));
    }

    bool Widget::handleEvent(Widget *target, const sf::Event &event)
    {
        return false;
    }

    Widget::Widget()
        : m_isValid(false), m_parent(nullptr) {}

    Widget::~Widget() {}

    /////////////////////////////////////////////////////////////////////////////////////////

    void Widget::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        update(false);
        auto _states = states;
        _states.transform.translate({getLeft(), getTop()});
        onDraw(target, _states);
    }

    void Widget::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const {}
    void Widget::onUpdate() const {}

}