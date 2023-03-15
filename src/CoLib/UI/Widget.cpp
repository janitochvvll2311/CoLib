#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
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
        auto *parent = getParent();
        if (parent)
        {
            auto *widget = dynamic_cast<Widget *>(parent);
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

    sf::Vector2f Widget::getInnerPoint(const sf::Vector2f &point) const
    {
        return point;
    }

    Node *Widget::getParent() const
    {
        return m_parent;
    }

    Widget::Widget()
        : m_isValid(false), m_parent(nullptr) {}

    Widget::~Widget() {}

    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Widget::onAttach(Node *node)
    {
        m_parent = node;
    }

    bool Widget::dispatchInnerEvent(const SharedWidget &widget, Node *target, const sf::Event &event) const
    {
        switch (event.type)
        {
        case sf::Event::MouseButtonPressed:
        case sf::Event::MouseButtonReleased:
        {
            auto _event = event;
            sf::Vector2f point(getInnerPoint({f32t(_event.mouseButton.x), f32t(_event.mouseButton.y)}));
            _event.mouseButton.x = point.x;
            _event.mouseButton.y = point.y;
            return widget->dispatchEvent(target, _event);
        }
        default:
            return widget->dispatchEvent(target, event);
        }
    }

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