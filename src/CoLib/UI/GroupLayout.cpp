#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <CoLib/System/Exception.hpp>
#include <CoLib/UI/WidgetHolder.hpp>
#include <CoLib/UI/GroupLayout.hpp>

namespace co
{

    szt GroupLayout::getChildCount() const
    {
        return m_holders.size();
    }

    SharedNode GroupLayout::getChild(szt index) const
    {
        if (index < m_holders.size())
        {
            auto iterator = m_holders.begin();
            std::advance(iterator, index);
            return (*iterator)->getWidget();
        }
        return NoNode;
    }

    bool GroupLayout::dispatchEvent(Node *target, const sf::Event &event)
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

    bool GroupLayout::bubbleEvent(Node *target, const sf::Event &event)
    {
        if (event.type == sf::Event::GainedFocus)
        {
            for (auto &holder : m_holders)
            {
                auto &widget = holder->getWidget();
                if (widget.get() != target)
                {
                    widget->dispatchEvent(target, event);
                }
            }
        }
        return Block::bubbleEvent(target, event);
    }

    GroupLayout::GroupLayout()
        : m_holders() {}

    GroupLayout::~GroupLayout() {}

    //////////////////////////////////////////////////////////////////////

    void GroupLayout::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
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

    void GroupLayout::onUpdate() const
    {
        Block::onUpdate();
        for (auto &holder : m_holders)
        {
            holder->getWidget()->update(true);
        }
    }

    void GroupLayout::onAppend(const SharedNode &node)
    {
        SharedWidget widget = std::dynamic_pointer_cast<Widget>(node);
        if (widget)
        {
            auto holder = createHolder();
            holder->setWidget(widget);
            m_holders.push_back(holder);
        }
        else
        {
            throw InvalidOperationException("This node is not a widget");
        }
    }

    void GroupLayout::onRemove(const SharedNode &node)
    {
        m_holders.remove_if([&](auto &holder)
                            { return holder->getWidget() == node; });
    }

    //////////////////////////////////////////////////////////////////////////

    SharedHolder GroupLayout::getHolder(const SharedWidget &widget) const
    {
        auto iterator = std::find_if(m_holders.begin(), m_holders.end(), [&](auto &holder)
                                     { return holder->getWidget() == widget; });
        if (iterator != m_holders.end())
        {
            return *iterator;
        }
        return nullptr;
    }

    const std::list<SharedHolder> &GroupLayout::getHolders() const
    {
        return m_holders;
    }

    SharedHolder GroupLayout::createHolder() const
    {
        return std::make_shared<WidgetHolder>();
    }

}