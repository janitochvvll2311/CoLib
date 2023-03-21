#define COLIB_UI_EXPORTS
#include <SFML/Graphics/RenderStates.hpp>
#include <CoLib/UI/Widget.hpp>

namespace co
{

    Node *Widget::getParent() const
    {
        return m_parent;
    }

    bool Widget::isValid() const
    {
        return m_isValid;
    }

    void Widget::invalidate()
    {
        m_isValid = false;
        auto parent = dynamic_cast<Widget *>(getParent());
        if (parent)
        {
            parent->invalidate();
        }
    }

    void Widget::update(bool force) const
    {
        if (!m_isValid || force)
        {
            onUpdate();
            m_isValid = true;
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

    Widget::Widget()
        : m_isValid(false), m_parent(nullptr) {}

    Widget::~Widget() {}

    ////////////////////////////////////////////////

    void Widget::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        update(false);
        auto _states = states;
        _states.transform.translate({getLeft(), getTop()});
        onDraw(target, _states);
    }

    void Widget::onAttach(Node *parent)
    {
        m_parent = parent;
    }

    void Widget::onDetach()
    {
        m_parent = nullptr;
    }

    void Widget::onUpdate() const {}
    void Widget::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const {}

}