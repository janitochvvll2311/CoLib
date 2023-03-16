#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <CoLib/System/Exception.hpp>
#include <CoLib/UI/AnchorLayout.hpp>

namespace co
{

    AnchorLayout::Anchor AnchorLayout::getHorizontalAnchor(const SharedWidget &widget) const
    {
        auto holder = std::dynamic_pointer_cast<WidgetHolder>(getHolder(widget));
        if (!holder)
        {
            throw InvalidOperationException();
        }
        return holder->getHorizontalAnchor();
    }

    void AnchorLayout::setHorizontalAnchor(const SharedWidget &widget, Anchor value)
    {
        auto holder = std::dynamic_pointer_cast<WidgetHolder>(getHolder(widget));
        if (!holder)
        {
            throw InvalidOperationException();
        }
        holder->setHorizontalAnchor(value);
    }

    AnchorLayout::Anchor AnchorLayout::getVerticalAnchor(const SharedWidget &widget) const
    {
        auto holder = std::dynamic_pointer_cast<WidgetHolder>(getHolder(widget));
        if (!holder)
        {
            throw InvalidOperationException();
        }
        return holder->getVerticalAnchor();
    }

    void AnchorLayout::setVerticalAnchor(const SharedWidget &widget, Anchor value)
    {
        auto holder = std::dynamic_pointer_cast<WidgetHolder>(getHolder(widget));
        if (!holder)
        {
            throw InvalidOperationException();
        }
        holder->setVerticalAnchor(value);
    }

    void AnchorLayout::compact()
    {
        sf::Vector2f size(0, 0);
        auto &holders = getHolders();
        for (auto &holder : holders)
        {
            auto &widget = holder->getWidget();
            widget->compact();
            size.x = std::max(size.x, widget->getWidth());
            size.y = std::max(size.y, widget->getHeight());
        }
        GroupLayout::compact(size);
    }

    void AnchorLayout::inflate(const sf::Vector2f &size)
    {
        GroupLayout::inflate(size);
        sf::Vector2f _size(getInnerWidth(), getInnerHeight());
        auto &holders = getHolders();
        for (auto &holder : holders)
        {
            auto _holder = std::dynamic_pointer_cast<WidgetHolder>(holder);
            auto &widget = _holder->getWidget();
            widget->inflate(_size);
            sf::Vector2f spacing(getInnerWidth() - widget->getOuterWidth(),
                                 getInnerHeight() - widget->getOuterHeight());
            switch (_holder->getHorizontalAnchor())
            {
            case Start:
                break;
            case End:
                widget->setLeft(widget->getLeft() + spacing.x);
                break;
            case Center:
                widget->setLeft(widget->getLeft() + spacing.x / 2);
                break;
            }
            switch (_holder->getVerticalAnchor())
            {
            case Start:
                break;
            case End:
                widget->setTop(widget->getTop() + spacing.y);
                break;
            case Center:
                widget->setTop(widget->getTop() + spacing.y / 2);
                break;
            }
        }
    }

    AnchorLayout::AnchorLayout() {}

    AnchorLayout::~AnchorLayout() {}

    ///////////////////////////////////////////////////////////////////////////////////////////////

    SharedHolder AnchorLayout::createHolder() const
    {
        return std::make_shared<WidgetHolder>();
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