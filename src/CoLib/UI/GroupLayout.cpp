#define COLIB_UI_EXPORTS
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <CoLib/UI/GroupLayout.hpp>

namespace co
{

    szt GroupLayout::getChildCount() const
    {
        return m_holders.size();
    }

    SharedNode GroupLayout::getChild(szt index) const
    {
        auto holder = getHolder(index);
        if (holder)
        {
            return holder->child;
        }
        return nullptr;
    }

    sf::Vector2f GroupLayout::getAbsolutePlace() const
    {
        auto parent = getParent();
        while (parent)
        {
            auto layout = dynamic_cast<Layout *>(parent);
            if (layout)
            {
                auto place = layout->getAbsolutePlace();
                return {place.x + getLeft(), place.y + getTop()};
            }
            parent = parent->getParent();
        }
        return {getLeft(), getTop()};
    }

    GroupLayout::GroupLayout()
        : m_holders() {}

    GroupLayout::~GroupLayout() {}

    //////////////////////////////////////////////////////////

    void GroupLayout::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        if (m_holders.size() > 0)
        {
            auto &padding = getPadding();
            auto _states = states;
            _states.transform.translate({getLeft() + padding.left, getTop() + padding.top});
            for (auto &holder : m_holders)
            {
                auto drawable = std::dynamic_pointer_cast<sf::Drawable>(holder->child);
                if (drawable)
                {
                    target.draw(*drawable, _states);
                }
            }
        }
    }

    void GroupLayout::onAppend(const SharedNode &child)
    {
        auto holder = createHolder();
        holder->child = child;
        m_holders.push_back(holder);
    }

    void GroupLayout::onRemove(const SharedNode &child)
    {
        m_holders.remove_if([=](auto &holder)
                            { return holder->child == child; });
    }

    bool GroupLayout::dispatchChildrenEvents(Node *target, const sf::Event &event) const
    {
        bool handled = false;
        for (auto &holder : m_holders)
        {
            if (holder->child->dispatchEvent(target, event))
            {
                handled = true;
            }
        }
        return handled;
    }

    GroupLayout::SharedHolder GroupLayout::createHolder() const
    {
        return std::make_shared<Holder>();
    }

    GroupLayout::SharedHolder GroupLayout::getHolder(szt index) const
    {
        if (index >= 0 && index < m_holders.size())
        {
            auto iterator = m_holders.begin();
            std::advance(iterator, index);
            if (iterator != m_holders.end())
            {
                return *iterator;
            }
        }
        return nullptr;
    }

    GroupLayout::SharedHolder GroupLayout::getHolder(const SharedNode &child) const
    {
        for (auto &holder : m_holders)
        {
            if (holder->child == child)
            {
                return holder;
            }
        }
        return nullptr;
    }

}