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

    f32t LinearLayout::getWeight(const SharedWidget &widget) const
    {
        auto holder = std::dynamic_pointer_cast<WidgetHolder>(getHolder(widget));
        if (!holder)
        {
            throw InvalidOperationException();
        }
        return holder->getWeight();
    }

    void LinearLayout::setWeight(const SharedWidget &widget, f32t value)
    {
        auto holder = std::dynamic_pointer_cast<WidgetHolder>(getHolder(widget));
        if (!holder)
        {
            throw InvalidOperationException();
        }
        holder->setWeight(value);
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
        GroupLayout::compact(size);
    }

    void LinearLayout::inflate(const sf::Vector2f &size)
    {
        GroupLayout::inflate(size);
        sf::Vector2f _size(getInnerWidth(), getInnerHeight());
        f32t length = 0;
        f32t offset = 0;
        auto fixOffset = [&]()
        {
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
            else
            {
                offset = 0;
            }
        };
        auto aligHorizontal = [&](SharedHolder holder)
        {
            auto _holder = std::dynamic_pointer_cast<WidgetHolder>(holder);
            auto &widget = _holder->getWidget();
            widget->setLeft(widget->getLeft() + offset);
            offset += widget->getOuterWidth();
            f32t spacing = _size.y - widget->getOuterHeight();
            switch (_holder->getAnchor())
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
        };
        auto alignVertical = [&](SharedHolder holder)
        {
            auto _holder = std::dynamic_pointer_cast<WidgetHolder>(holder);
            auto &widget = _holder->getWidget();
            widget->setTop(widget->getTop() + offset);
            offset += widget->getOuterHeight();
            f32t spacing = _size.x - widget->getOuterWidth();
            switch (_holder->getAnchor())
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
        };
        auto &holders = getHolders();
        switch (m_orientation)
        {
        case Horizontal:
        {
            for (auto &holder : holders)
            {
                auto _holder = std::dynamic_pointer_cast<WidgetHolder>(holder);
                auto &widget = _holder->getWidget();
                auto weight = _holder->getWeight();
                widget->inflate({_size.x * weight, _size.y});
                length += widget->getOuterWidth();
            }
            offset = _size.x - length;
            fixOffset();
            if (m_isReverse)
            {
                for (auto iterator = holders.rbegin(); iterator != holders.rend(); iterator++)
                {
                    aligHorizontal(*iterator);
                }
            }
            else
            {
                for (auto iterator = holders.begin(); iterator != holders.end(); iterator++)
                {
                    aligHorizontal(*iterator);
                }
            }
        }
        break;
        case Vertical:
        {
            for (auto &holder : holders)
            {
                auto _holder = std::dynamic_pointer_cast<WidgetHolder>(holder);
                auto &widget = holder->getWidget();
                widget->inflate({_size.x, 0});
                auto weight = _holder->getWeight();
                widget->inflate({_size.x, _size.y * weight});
                length += widget->getOuterHeight();
            }
            offset = _size.y - length;
            fixOffset();
            if (m_isReverse)
            {
                for (auto iterator = holders.rbegin(); iterator != holders.rend(); iterator++)
                {
                    alignVertical(*iterator);
                }
            }
            else
            {
                for (auto iterator = holders.begin(); iterator != holders.end(); iterator++)
                {
                    alignVertical(*iterator);
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

    f32t LinearLayout::WidgetHolder::getWeight() const
    {
        return m_weight;
    }

    void LinearLayout::WidgetHolder::setWeight(f32t value)
    {
        m_weight = value;
    }

    LinearLayout::WidgetHolder::WidgetHolder()
        : m_anchor(Start), m_weight(0) {}

    LinearLayout::WidgetHolder::~WidgetHolder() {}
}