#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <CoLib/System/Exception.hpp>
#include <CoLib/UI/Block.hpp>
#include <CoLib/UI/FrameLayout.hpp>

namespace co
{

    FrameLayout::Anchor FrameLayout::getHorizontalAnchor(const SharedWidget &widget) const
    {
        if (!m_holder || getWidget() != widget)
        {
            throw InvalidOperationException();
        }
        return m_holder->getHorizontalAnchor();
    }

    void FrameLayout::setHorizontalAnchor(const SharedWidget &widget, Anchor value) const
    {
        if (!m_holder || getWidget() != widget)
        {
            throw InvalidOperationException();
        }
        m_holder->setHorizontalAnchor(value);
    }

    FrameLayout::Anchor FrameLayout::getVerticalAnchor(const SharedWidget &widget) const
    {
        if (!m_holder || getWidget() != widget)
        {
            throw InvalidOperationException();
        }
        return m_holder->getVerticalAnchor();
    }

    void FrameLayout::setVerticalAnchor(const SharedWidget &widget, Anchor value) const
    {
        if (!m_holder || getWidget() != widget)
        {
            throw InvalidOperationException();
        }
        m_holder->setVerticalAnchor(value);
    }

    ////////////////////////////////////////////////////////////////

    void FrameLayout::compact()
    {
        if (m_holder)
        {
            auto widget = getWidget();
            widget->compact();
        }
        Block::compact();
    }

    void FrameLayout::inflate(const sf::Vector2f &size)
    {
        Block::inflate(size);
        if (m_holder)
        {
            sf::Vector2f _size(getInnerWidth(), getInnerHeight());
            auto widget = getWidget();
            widget->inflate(_size);
            switch (m_holder->getHorizontalAnchor())
            {
            case Start:
                break;
            case End:
                widget->setLeft(widget->getLeft() + _size.x - widget->getOuterWidth());
                break;
            case Center:
                widget->setLeft(widget->getLeft() + (_size.x - widget->getOuterWidth()) / 2);
                break;
            }
            switch (m_holder->getVerticalAnchor())
            {
            case Start:
                break;
            case End:
                widget->setTop(widget->getTop() + _size.y - widget->getOuterHeight());
                break;
            case Center:
                widget->setTop(widget->getTop() + (_size.y - widget->getOuterHeight()) / 2);
                break;
            }
        }
    }

    SharedWidget FrameLayout::getWidget() const
    {
        if (m_holder)
        {
            return m_holder->getWidget();
        }
        return nullptr;
    }

    //////////////////////////////////////////////////////////////////////////////////

    szt FrameLayout::getChildCount() const
    {
        return m_holder ? 1 : 0;
    }

    SharedNode FrameLayout::getChild(szt index) const
    {
        if (m_holder && index == 0)
        {
            return m_holder->getWidget();
        }
        return NoNode;
    }

    bool FrameLayout::dispatchEvent(Node *target, const sf::Event &event)
    {
        return ((m_holder && dispatchInnerEvent(getWidget(), target, event)) || handleEvent(target, event));
    }

    FrameLayout::FrameLayout()
        : m_holder(nullptr) {}

    FrameLayout::~FrameLayout() {}

    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::Vector2f FrameLayout::getContentSize() const
    {
        if (m_holder)
        {
            auto widget = getWidget();
            return {widget->getWidth(), widget->getHeight()};
        }
        else
        {
            return {0, 0};
        }
    }

    void FrameLayout::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        Block::onDraw(target, states);
        if (m_holder)
        {
            auto &padding = getPadding();
            auto _states = states;
            _states.transform.translate({padding.left, padding.top});
            target.draw(*getWidget(), _states);
        }
    }

    void FrameLayout::onUpdate() const
    {
        Block::onUpdate();
        if (m_holder)
        {
            getWidget()->update(true);
        }
    }

    void FrameLayout::onAppend(const SharedNode &node)
    {
        SharedWidget widget = std::dynamic_pointer_cast<Widget>(node);
        if (widget)
        {
            m_holder.reset(new WidgetHolder());
            m_holder->setWidget(widget);
        }
        else
        {
            throw InvalidOperationException("This node is not a widget");
        }
    }

    void FrameLayout::onRemove(const SharedNode &node)
    {
        if (getWidget() != node)
        {
            throw InvalidOperationException("This node is not a child of the parent node");
        }
        m_holder.reset();
    }

    /////////////////////////////////////////////////////////////////////////////////////////

    FrameLayout::Anchor FrameLayout::WidgetHolder::getHorizontalAnchor() const
    {
        return m_hAnchor;
    }

    void FrameLayout::WidgetHolder::setHorizontalAnchor(Anchor value)
    {
        m_hAnchor = value;
    }

    FrameLayout::Anchor FrameLayout::WidgetHolder::getVerticalAnchor() const
    {
        return m_vAnchor;
    }

    void FrameLayout::WidgetHolder::setVerticalAnchor(Anchor value)
    {
        m_vAnchor = value;
    }

    FrameLayout::WidgetHolder::WidgetHolder()
        : m_hAnchor(Start), m_vAnchor(Start) {}

    FrameLayout::WidgetHolder::~WidgetHolder() {}

}