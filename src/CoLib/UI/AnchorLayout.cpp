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


    AnchorLayout::AnchorLayout()
        : m_holders() {}

    AnchorLayout::~AnchorLayout() {}

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