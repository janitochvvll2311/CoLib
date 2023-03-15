#include <algorithm>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <CoLib/System/Exception.hpp>
#include <CoLib/UI/LinearLayout.hpp>

namespace co
{

    LinearLayout::Alignment LinearLayout::getAlignment(const SharedWidget &widget) const
    {
        auto holder = getHolder(widget);
        if (!holder)
        {
            throw InvalidOperationException();
        }
        return holder->getAlignment();
    }

    void LinearLayout::setAlignment(const SharedWidget &widget, Alignment value)
    {
        auto holder = getHolder(widget);
        if (!holder)
        {
            throw InvalidOperationException();
        }
        holder->setAlignment(value);
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

    LinearLayout::Alignment LinearLayout::getContentAlignment() const
    {
        return m_cAlignment;
    }

    void LinearLayout::setContentAlignment(Alignment value)
    {
        m_cAlignment = value;
    }

    void LinearLayout::compact()
    {
        sf::Vector2f size(0, 0);
        switch (m_orientation)
        {
        case Horizontal:
            for (auto &holder : m_holders)
            {
                auto &widget = holder->getWidget();
                widget->compact();
                size.x += widget->getWidth();
                size.y = std::max(size.y, widget->getHeight());
            }
            break;
        case Vertical:
            for (auto &holder : m_holders)
            {
                auto &widget = holder->getWidget();
                widget->compact();
                size.y += widget->getHeight();
                size.x = std::max(size.x, widget->getWidth());
            }
            break;
        }
        Block::compact();
        auto &margin = getMargin();
        auto &padding = getPadding();
        setWidth(std::max(size.x, getMinWidth()) + margin.getHorizontal() + padding.getHorizontal());
        setHeight(std::max(size.y, getMinHeight()) + margin.getVertical() + padding.getVertical());
    }

    void LinearLayout::inflate(const sf::Vector2f &size)
    {
        Block::inflate(size);
        sf::Vector2f _size(getInnerWidth(), getInnerHeight());
        f32t length = 0;
        switch (m_orientation)
        {
        case Horizontal:
        {
            for (auto &holder : m_holders)
            {
                auto &widget = holder->getWidget();
                widget->inflate({0, _size.y});
                length += widget->getOuterWidth();
            }
            f32t offset = _size.x - length;
            if (offset > 0)
            {
                switch (m_cAlignment)
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
                for (auto iterator = m_holders.rbegin(); iterator != m_holders.rend(); iterator++)
                {
                    auto &holder = *iterator;
                    auto &widget = holder->getWidget();
                    widget->setLeft(widget->getLeft() + offset);
                    offset += widget->getOuterWidth();
                    f32t spacing = _size.y - widget->getOuterHeight();
                    switch (holder->getAlignment())
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
                for (auto iterator = m_holders.begin(); iterator != m_holders.end(); iterator++)
                {
                    auto &holder = *iterator;
                    auto &widget = holder->getWidget();
                    widget->setLeft(widget->getLeft() + offset);
                    offset += widget->getOuterWidth();
                    f32t spacing = _size.y - widget->getOuterHeight();
                    switch (holder->getAlignment())
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
            for (auto &holder : m_holders)
            {
                auto &widget = holder->getWidget();
                widget->inflate({_size.x, 0});
                length += widget->getOuterHeight();
            }
            f32t offset = _size.y - length;
            if (offset > 0)
            {
                switch (m_cAlignment)
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
                for (auto iterator = m_holders.rbegin(); iterator != m_holders.rend(); iterator++)
                {
                    auto &holder = *iterator;
                    auto &widget = holder->getWidget();
                    widget->setTop(widget->getTop() + offset);
                    offset += widget->getOuterHeight();
                    f32t spacing = _size.x - widget->getOuterWidth();
                    switch (holder->getAlignment())
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
                for (auto iterator = m_holders.begin(); iterator != m_holders.end(); iterator++)
                {
                    auto &holder = *iterator;
                    auto &widget = holder->getWidget();
                    widget->setTop(widget->getTop() + offset);
                    offset += widget->getOuterHeight();
                    f32t spacing = _size.x - widget->getOuterWidth();
                    switch (holder->getAlignment())
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

    //////////////////////////////////////////////////////////////////////////////////

    bool LinearLayout::dispatchEvent(Widget *target, const sf::Event &event)
    {
        bool handled = false;
        for (auto &holder : m_holders)
        {
            if (dispatchInnerEvent(holder->getWidget(), target, event))
            {
                handled = true;
            }
        }
        return (handled || handleEvent(target, event));
    }

    bool LinearLayout::bubbleEvent(Widget *target, const sf::Event &event)
    {
        if (event.type == sf::Event::GainedFocus)
        {
            for (auto &holder : m_holders)
            {
                auto &widget = holder->getWidget();
                if (widget.get() != target)
                {
                    dispatchInnerEvent(widget, target, event);
                }
            }
        }
        return Block::bubbleEvent(target, event);
    }

    LinearLayout::LinearLayout()
        : m_orientation(Horizontal), m_isReverse(false), m_cAlignment(Start), m_holders() {}

    LinearLayout::~LinearLayout() {}

    //////////////////////////////////////////////////////////////////////

    void LinearLayout::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        Block::onDraw(target, states);
        if (m_holders.size() > 0)
        {
            auto &padding = getPadding();
            auto _states = states;
            _states.transform.translate({padding.left, padding.top});
            for (auto &holder : m_holders)
            {
                target.draw(*holder->getWidget(), _states);
            }
        }
    }

    void LinearLayout::onUpdate() const
    {
        Block::onUpdate();
        for (auto &holder : m_holders)
        {
            holder->getWidget()->update(true);
        }
    }

    void LinearLayout::onAttach(const SharedWidget &widget)
    {
        auto holder = std::make_shared<WidgetHolder>();
        holder->setWidget(widget);
        m_holders.push_back(holder);
    }

    void LinearLayout::onDetach(const SharedWidget &widget)
    {
        m_holders.remove_if([&](auto &holder)
                            { return holder->getWidget() == widget; });
    }

    //////////////////////////////////////////////////////////////////////////

    LinearLayout::SharedHolder LinearLayout::getHolder(const SharedWidget &widget) const
    {
        auto iterator = std::find_if(m_holders.begin(), m_holders.end(), [&](auto &holder)
                                     { return holder->getWidget() == widget; });
        if (iterator != m_holders.end())
        {
            return *iterator;
        }
        return nullptr;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////

    LinearLayout::Alignment LinearLayout::WidgetHolder::getAlignment() const
    {
        return m_alignment;
    }

    void LinearLayout::WidgetHolder::setAlignment(Alignment value)
    {
        m_alignment = value;
    }

    LinearLayout::WidgetHolder::WidgetHolder()
        : m_alignment(Start) {}

    LinearLayout::WidgetHolder::~WidgetHolder() {}
}