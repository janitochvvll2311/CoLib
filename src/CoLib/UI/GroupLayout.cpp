#define COLIB_UI_EXPORTS
#include <SFML/Window/Event.hpp>
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

    GroupLayout::GroupLayout()
        : m_holders() {}

    GroupLayout::~GroupLayout() {}

    //////////////////////////////////////////////////////////

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
        if (m_holders.size() > 0)
        {
            auto handled = false;
            for (auto &holder : m_holders)
            {
                if (holder->child->dispatchEvent(target, event))
                {
                    handled = true;
                }
            }
            return handled;
        }
        return false;
    }

    void GroupLayout::updateContent() const {
        if (m_holders.size() > 0)
        {
            for (auto &holder : m_holders)
            {
                auto updatable = std::dynamic_pointer_cast<Updatable>(holder->child);
                if (updatable)
                {
                    updatable->update(true);
                }
            }
        }
    }

    void GroupLayout::drawContent(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        if (m_holders.size() > 0)
        {
            for (auto &holder : m_holders)
            {
                auto drawable = std::dynamic_pointer_cast<sf::Drawable>(holder->child);
                if (drawable)
                {
                    target.draw(*drawable, states);
                }
            }
        }
    }

    GroupLayout::SharedHolder GroupLayout::createHolder() const
    {
        return std::make_shared<Holder>();
    }

    const std::list<GroupLayout::SharedHolder> &GroupLayout::getHolders() const
    {
        return m_holders;
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