#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <CoLib/System/Exception.hpp>
#include <CoLib/UI/AnchorLayout.hpp>

namespace co
{

    AnchorLayout::Anchor AnchorLayout::getHorizontalAnchor(const SharedWidget &widget) const
    {
        auto holder = getHolder(widget);
        if (!holder)
        {
            throw InvalidOperationException();
        }
        return holder->getHorizontalAnchor();
    }

    void AnchorLayout::setHorizontalAnchor(const SharedWidget &widget, Anchor value)
    {
        auto holder = getHolder(widget);
        if (!holder)
        {
            throw InvalidOperationException();
        }
        holder->setHorizontalAnchor(value);
    }

    AnchorLayout::Anchor AnchorLayout::getVerticalAnchor(const SharedWidget &widget) const
    {
        auto holder = getHolder(widget);
        if (!holder)
        {
            throw InvalidOperationException();
        }
        return holder->getVerticalAnchor();
    }

    void AnchorLayout::setVerticalAnchor(const SharedWidget &widget, Anchor value)
    {
        auto holder = getHolder(widget);
        if (!holder)
        {
            throw InvalidOperationException();
        }
        holder->setVerticalAnchor(value);
    }

    void AnchorLayout::compact()
    {
    }

    void AnchorLayout::inflate(const sf::Vector2f &size)
    {
        }

    //////////////////////////////////////////////////////////////////////////////////

    bool AnchorLayout::dispatchEvent(Widget *target, const sf::Event &event)
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

    bool AnchorLayout::bubbleEvent(Widget *target, const sf::Event &event)
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

    AnchorLayout::AnchorLayout()
        : m_holders() {}

    AnchorLayout::~AnchorLayout() {}

    ////////////////////////////////////////////////////////////////////////////////////////////////

    void AnchorLayout::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
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

    void AnchorLayout::onUpdate() const
    {
        Block::onUpdate();
        for (auto &holder : m_holders)
        {
            holder->getWidget()->update(true);
        }
    }

    void AnchorLayout::onAttach(const SharedWidget &widget)
    {
        auto holder = std::make_shared<WidgetHolder>();
        holder->setWidget(widget);
        m_holders.push_back(holder);
    }

    void AnchorLayout::onDetach(const SharedWidget &widget)
    {
        m_holders.remove_if([&](auto &holder)
                            { return holder->getWidget() == widget; });
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////

    AnchorLayout::SharedHolder AnchorLayout::getHolder(const SharedWidget &widget) const
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

    AnchorLayout::Anchor AnchorLayout::WidgetHolder::getHorizontalAnchor() const
    {
        return m_hAnchor;
    }

    void AnchorLayout::WidgetHolder::setHorizontalAnchor(Anchor value)
    {
        m_hAnchor = value;
    }

    AnchorLayout::Anchor AnchorLayout::WidgetHolder::getVerticalAnchor() const
    {
        return m_vAnchor;
    }

    void AnchorLayout::WidgetHolder::setVerticalAnchor(Anchor value)
    {
        m_vAnchor = value;
    }

    AnchorLayout::WidgetHolder::WidgetHolder()
        : m_hAnchor(Start), m_vAnchor(Start) {}

    AnchorLayout::WidgetHolder::~WidgetHolder() {}

}