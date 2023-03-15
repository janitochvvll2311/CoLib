#include <algorithm>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <CoLib/System/Exception.hpp>
#include <CoLib/UI/LinearLayout.hpp>

namespace co
{

    LinearLayout::Anchor LinearLayout::getAnchor(const SharedWidget &widget) const
    {
        auto holder = std::dynamic_pointer_cast<WidgetHolder>(getHolder(widget));
        if (!holder)
        {
            throw InvalidOperationException();
        }
        return holder->getAnchor();
    }

    void LinearLayout::setAnchor(const SharedWidget &widget, Anchor value)
    {
        auto holder = std::dynamic_pointer_cast<WidgetHolder>(getHolder(widget));
        if (!holder)
        {
            throw InvalidOperationException();
        }
        holder->setAnchor(value);
    }

    LinearLayout::Orientation LinearLayout::getOrientation() const
    {
        return m_orientation;
    }

    void LinearLayout::setOritentation(Orientation value)
    {
        m_orientation = value;
    }

    bool LinearLayout::isReverse() const
    {
        return m_isReverse;
    }

    void LinearLayout::setReverse(bool value)
    {
        m_isReverse = value;
    }

    LinearLayout::Anchor LinearLayout::getContentAnchor() const
    {
        return m_cAnchor;
    }

    void LinearLayout::setContentAnchor(Anchor value)
    {
        m_cAnchor = value;
    }

    void LinearLayout::compact()
    {
        sf::Vector2f size(0, 0);
        auto &holders = getHolders();
        switch (m_orientation)
        {
        case Horizontal:
            for (auto &holder : holders)
            {
                auto &widget = holder->getWidget();
                widget->compact();
                size.x += widget->getWidth();
                size.y = std::max(size.y, widget->getHeight());
            }
            break;
        case Vertical:
            for (auto &holder : holders)
            {
                auto &widget = holder->getWidget();
                widget->compact();
                size.y += widget->getHeight();
                size.x = std::max(size.x, widget->getWidth());
            }
            break;
        }
        setWidth(size.x);
        setHeight(size.y);
        Block::compact();
    }

    void LinearLayout::inflate(const sf::Vector2f &size)
    {
        Block::inflate(size);
        sf::Vector2f _size(getInnerWidth(), getInnerHeight());
        f32t length = 0;
        auto &holders = getHolders();
        switch (m_orientation)
        {
        case Horizontal:
        {
            for (auto &holder : holders)
            {
                auto &widget = holder->getWidget();
                widget->inflate({0, _size.y});
                length += widget->getOuterWidth();
            }
            f32t offset = _size.x - length;
            if (offset > 0)
            {
                switch (m_cAnchor)
                {
                case Start:
                    offset = 0;
                    break;
                case End:
                    break;
                case Center:
                    offset /= 2;
                }
            }
            if (m_isReverse)
            {
                for (auto iterator = holders.rbegin(); iterator != holders.rend(); iterator++)
                {
                    auto holder = std::dynamic_pointer_cast<WidgetHolder>(*iterator);
                    auto &widget = holder->getWidget();
                    widget->setLeft(widget->getLeft() + offset);
                    offset += widget->getOuterWidth();
                    f32t spacing = _size.y - widget->getOuterHeight();
                    switch (holder->getAnchor())
                    {
                    case Start:
                        break;
                    case End:
                        widget->setTop(widget->getTop() + spacing);
                        break;
                    case Center:
                        widget->setTop(widget->getTop() + spacing / 2);
                        break;
                    }
                }
            }
            else
            {
                for (auto iterator = holders.begin(); iterator != holders.end(); iterator++)
                {
                    auto holder = std::dynamic_pointer_cast<WidgetHolder>(*iterator);
                    auto &widget = holder->getWidget();
                    widget->setLeft(widget->getLeft() + offset);
                    offset += widget->getOuterWidth();
                    f32t spacing = _size.y - widget->getOuterHeight();
                    switch (holder->getAnchor())
                    {
                    case Start:
                        break;
                    case End:
                        widget->setTop(widget->getTop() + spacing);
                        break;
                    case Center:
                        widget->setTop(widget->getTop() + spacing / 2);
                        break;
                    }
                }
            }
        }
        break;
        case Vertical:
        {
            for (auto &holder : holders)
            {
                auto &widget = holder->getWidget();
                widget->inflate({_size.x, 0});
                length += widget->getOuterHeight();
            }
            f32t offset = _size.y - length;
            if (offset > 0)
            {
                switch (m_cAnchor)
                {
                case Start:
                    offset = 0;
                    break;
                case End:
                    break;
                case Center:
                    offset /= 2;
                }
            }
            if (m_isReverse)
            {
                for (auto iterator = holders.rbegin(); iterator != holders.rend(); iterator++)
                {
                    auto holder = std::dynamic_pointer_cast<WidgetHolder>(*iterator);
                    auto &widget = holder->getWidget();
                    widget->setTop(widget->getTop() + offset);
                    offset += widget->getOuterHeight();
                    f32t spacing = _size.x - widget->getOuterWidth();
                    switch (holder->getAnchor())
                    {
                    case Start:
                        break;
                    case End:
                        widget->setLeft(widget->getLeft() + spacing);
                        break;
                    case Center:
                        widget->setLeft(widget->getLeft() + spacing / 2);
                        break;
                    }
                }
            }
            else
            {
                for (auto iterator = holders.begin(); iterator != holders.end(); iterator++)
                {
                    auto holder = std::dynamic_pointer_cast<WidgetHolder>(*iterator);
                    auto &widget = holder->getWidget();
                    widget->setTop(widget->getTop() + offset);
                    offset += widget->getOuterHeight();
                    f32t spacing = _size.x - widget->getOuterWidth();
                    switch (holder->getAnchor())
                    {
                    case Start:
                        break;
                    case End:
                        widget->setLeft(widget->getLeft() + spacing);
                        break;
                    case Center:
                        widget->setLeft(widget->getLeft() + spacing / 2);
                        break;
                    }
                }
            }
        }
        break;
        }
    }

    LinearLayout::LinearLayout()
        : m_orientation(Horizontal), m_isReverse(false), m_cAnchor(Start) {}

    LinearLayout::~LinearLayout() {}

    //////////////////////////////////////////////////////////////////////

    sf::Vector2f LinearLayout::getContentSize() const
    {
        return {getWidth(), getHeight()};
    }

    SharedHolder LinearLayout::createHolder() const
    {
        return std::make_shared<WidgetHolder>();
    }

    //////////////////////////////////////////////////////////////////////

    LinearLayout::Anchor LinearLayout::WidgetHolder::getAnchor() const
    {
        return m_anchor;
    }

    void LinearLayout::WidgetHolder::setAnchor(Anchor value)
    {
        m_anchor = value;
    }

    LinearLayout::WidgetHolder::WidgetHolder()
        : m_anchor(Start) {}

    LinearLayout::WidgetHolder::~WidgetHolder() {}
}