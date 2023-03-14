#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <CoLib/System/Exception.hpp>
#include <CoLib/UI/Block.hpp>
#include <CoLib/UI/FrameLayout.hpp>

namespace co
{

    FrameLayout::Alignment FrameLayout::getHorizontalAlignment(const SharedWidget &widget) const
    {
        if (!m_holder || getWidget() != widget)
        {
            throw InvalidOperationException();
        }
        return m_holder->getHorizontalAlignment();
    }

    void FrameLayout::setHorizontalAlignment(const SharedWidget &widget, Alignment value) const
    {
        if (!m_holder || getWidget() != widget)
        {
            throw InvalidOperationException();
        }
        m_holder->setHorizontalAlignment(value);
    }

    FrameLayout::Alignment FrameLayout::getVerticalAlignment(const SharedWidget &widget) const
    {
        if (!m_holder || getWidget() != widget)
        {
            throw InvalidOperationException();
        }
        return m_holder->getVerticalAlignment();
    }

    void FrameLayout::setVerticalAlignment(const SharedWidget &widget, Alignment value) const
    {
        if (!m_holder || getWidget() != widget)
        {
            throw InvalidOperationException();
        }
        m_holder->setVerticalAlignment(value);
    }

    ////////////////////////////////////////////////////////////////

    bool FrameLayout::isValid() const
    {
        return (Block::isValid() && (!m_holder || getWidget()->isValid()));
    }

    void FrameLayout::invalidate()
    {
        Block::invalidate();
        if (m_holder)
        {
            getWidget()->invalidate();
        }
    }

    void FrameLayout::compact()
    {
        sf::Vector2f size(0, 0);
        if (m_holder)
        {
            auto &widget = getWidget();
            widget->compact();
            size.x = widget->getWidth();
            size.y = widget->getHeight();
        }
        Block::compact();
    }

    void FrameLayout::inflate(const sf::Vector2f &size)
    {
        Block::inflate(size);
        if (m_holder)
        {
            sf::Vector2f _size(getInnerWidth(), getInnerHeight());
            auto &widget = getWidget();
            widget->inflate(_size);
            switch (m_holder->getHorizontalAlignment())
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
            switch (m_holder->getVerticalAlignment())
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

    const SharedWidget &FrameLayout::getWidget() const
    {
        if (m_holder)
        {
            return m_holder->getWidget();
        }
        return NoWidget;
    }

    //////////////////////////////////////////////////////////////////////////////////

    bool FrameLayout::handleEvent(const sf::Event &event)
    {
        return ((m_holder && handleInnerEvent(getWidget(), event)) || Block::handleEvent(event));
    }

    FrameLayout::FrameLayout()
        : m_holder(nullptr) {}

    FrameLayout::~FrameLayout() {}

    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::Vector2f FrameLayout::getContentSize() const
    {
        if (m_holder)
        {
            auto &widget = getWidget();
            return {widget->getOuterWidth(), widget->getOuterHeight()};
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

    void FrameLayout::onAttach(const SharedWidget &widget)
    {
        m_holder.reset(new WidgetHolder());
        m_holder->setWidget(widget);
    }

    void FrameLayout::onDetach(const SharedWidget &widget)
    {
        m_holder.reset();
    }

    /////////////////////////////////////////////////////////////////////////////////////////

    FrameLayout::Alignment FrameLayout::WidgetHolder::getHorizontalAlignment() const
    {
        return m_hAlignment;
    }

    void FrameLayout::WidgetHolder::setHorizontalAlignment(Alignment value)
    {
        m_hAlignment = value;
    }

    FrameLayout::Alignment FrameLayout::WidgetHolder::getVerticalAlignment() const
    {
        return m_vAlignment;
    }

    void FrameLayout::WidgetHolder::setVerticalAlignment(Alignment value)
    {
        m_vAlignment = value;
    }

    FrameLayout::WidgetHolder::WidgetHolder()
        : m_hAlignment(Start), m_vAlignment(Start) {}

    FrameLayout::WidgetHolder::~WidgetHolder() {}

}