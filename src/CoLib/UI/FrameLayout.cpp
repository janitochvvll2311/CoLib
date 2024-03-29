#define COLIB_UI_EXPORTS
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <CoLib/System/Exception.hpp>
#include <CoLib/UI/Constants.hpp>
#include <CoLib/UI/FrameLayout.hpp>

namespace co
{

    szt FrameLayout::getChildCount() const
    {
        if (m_holder)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    SharedNode FrameLayout::getChild(szt index) const
    {
        if (index == 0 && m_holder != nullptr)
        {
            return m_holder->child;
        }
        return nullptr;
    }

    FrameLayout::Anchor FrameLayout::getHorizontalAnchor(const SharedNode &child) const
    {
        if (!m_holder || m_holder->child != child)
        {
            throw InvalidOperationException(NOT_CHILD_NODE_STTRING);
        }
        return m_holder->hAnchor;
    }

    void FrameLayout::setHorizontalAnchor(const SharedNode &child, Anchor value)
    {
        if (!m_holder || m_holder->child != child)
        {
            throw InvalidOperationException(NOT_CHILD_NODE_STTRING);
        }
        m_holder->hAnchor = value;
    }

    FrameLayout::Anchor FrameLayout::getVerticalAnchor(const SharedNode &child) const
    {
        if (!m_holder || m_holder->child != child)
        {
            throw InvalidOperationException(NOT_CHILD_NODE_STTRING);
        }
        return m_holder->vAnchor;
    }

    void FrameLayout::setVerticalAnchor(const SharedNode &child, Anchor value)
    {
        if (!m_holder || m_holder->child != child)
        {
            throw InvalidOperationException(NOT_CHILD_NODE_STTRING);
        }
        m_holder->vAnchor = value;
    }

    FrameLayout::FrameLayout()
        : m_holder(nullptr) {}

    FrameLayout::~FrameLayout() {}

    //////////////////////////////////////////////////////////////////

    void FrameLayout::onAppend(const SharedNode &child)
    {
        if (m_holder != nullptr)
        {
            throw InvalidOperationException(CHILD_NODE_ALREADY_ATTACHED_STRING);
        }
        m_holder.reset(new Holder());
        m_holder->child = child;
        m_holder->hAnchor = Start;
        m_holder->vAnchor = Start;
    }

    void FrameLayout::onRemove(const SharedNode &child)
    {
        if (m_holder == nullptr || m_holder->child != child)
        {
            throw InvalidOperationException(CHILD_NODE_ALREADY_ATTACHED_STRING);
        }
        m_holder.reset();
    }

    bool FrameLayout::dispatchChildrenEvents(Node *target, const sf::Event &event) const
    {
        return (m_holder && m_holder->child->dispatchEvent(target, event));
    }

    sf::Vector2f FrameLayout::compactContent() const
    {
        if (m_holder)
        {
            auto inflatable = std::dynamic_pointer_cast<Inflatable>(m_holder->child);
            if (inflatable)
            {
                return inflatable->compact();
            }
        }
        return {0, 0};
    }

    void FrameLayout::inflateContent() const
    {
        if (m_holder)
        {
            auto inflatable = std::dynamic_pointer_cast<Inflatable>(m_holder->child);
            if (inflatable)
            {
                sf::Vector2f innerSize = getInnerSize();
                m_holder->size = inflatable->inflate(innerSize);
            }
        }
    }

    void FrameLayout::placeContent(const sf::Vector2f &origin) const
    {
        if (m_holder)
        {
            auto inflatable = std::dynamic_pointer_cast<Inflatable>(m_holder->child);
            if (inflatable)
            {
                auto innerSize = getInnerSize();
                auto &size = m_holder->size;
                sf::Vector2f position(origin);
                switch (m_holder->hAnchor)
                {
                case Start:
                    break;
                case End:
                    position.x += innerSize.x - size.x;
                    break;
                case Center:
                    position.x += (innerSize.x - size.x) / 2;
                    break;
                }
                switch (m_holder->vAnchor)
                {
                case Start:
                    break;
                case End:
                    position.y += innerSize.y - size.y;
                    break;
                case Center:
                    position.y += (innerSize.y - size.y) / 2;
                    break;
                }
                inflatable->place(position);
            }
        }
    }

    void FrameLayout::updateContent() const
    {
        if (m_holder)
        {
            auto updatable = std::dynamic_pointer_cast<Updatable>(m_holder->child);
            if (updatable)
            {
                updatable->update(true);
            }
        }
    }

    void FrameLayout::drawContent(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        if (m_holder)
        {
            auto drawable = std::dynamic_pointer_cast<sf::Drawable>(m_holder->child);
            if (drawable)
            {
                target.draw(*drawable, states);
            }
        }
    }

    FrameLayout::SharedHolder FrameLayout::getHolder() const
    {
        return m_holder;
    }

}